#include "BTManager.h"
#ifdef PICO

// Flags general discoverable
#define APP_AD_FLAGS 0x06

const uint8_t casioOS_service_id[16] = { 0xca, 0xb5, 0x66, 0x9c, 0x3c, 0xcf, 0x41, 0x89, 0xad, 0xdb, 0xb4, 0x53, 0x89, 0x99, 0x97, 0x17 };

// max length 31 bytes!
uint8_t adv_data[] = {
	// Flags general discoverable
	// 0x02, BLUETOOTH_DATA_TYPE_FLAGS, APP_AD_FLAGS,
	// Name
	0x08,
	BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME,
	'C',
	'a',
	's',
	'i',
	'o',
	'O',
	'S',
	// Incomplete List of 128-bit Service Class UUIDs
	0x11,
	BLUETOOTH_DATA_TYPE_INCOMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS,
	casioOS_service_id[15],
	casioOS_service_id[14],
	casioOS_service_id[13],
	casioOS_service_id[12],
	casioOS_service_id[11],
	casioOS_service_id[10],
	casioOS_service_id[9],
	casioOS_service_id[8],
	casioOS_service_id[7],
	casioOS_service_id[6],
	casioOS_service_id[5],
	casioOS_service_id[4],
	casioOS_service_id[3],
	casioOS_service_id[2],
	casioOS_service_id[1],
	casioOS_service_id[0],
};

// hci_event callback
btstack_packet_callback_registration_t hci_event_callback_registration;

// display notification state
uint16_t display_notification_enabled;
// display attribute handle
uint16_t display_attribute_handle;
// connection handle
hci_con_handle_t connection_handle;
// max ATT MTU - 1 for 0x00 packet header
uint16_t display_max_packet_len;

// frame chunks for sending display frame
std::vector<std::vector<uint8_t>> frame_chunks;
uint8_t frame_chunk_index = 0;

// window manager
WindowManager* _window_manager;

// keyboard instance
BTKeyboard* _bt_keyboard;


// workaround for first frame after connecting not being sent
bool first = true;


void send_frame_chunk();


/// <summary>
/// The packet handler is used track incoming connections and to stop notifications on disconnect
/// It is also a good place to request the connection parameter update
/// </summary>
void hci_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t* packet, uint16_t size)
{
	UNUSED(channel);
	UNUSED(size);

	if (packet_type != HCI_EVENT_PACKET) return;

	uint16_t conn_interval;
	hci_con_handle_t con_handle;
	static const char* const phy_names[] = { "1 M", "2 M", "Codec" };

	switch (hci_event_packet_get_type(packet)) {
	case BTSTACK_EVENT_STATE:
		// BTstack activated, get started
		if (btstack_event_state_get_state(packet) == HCI_STATE_WORKING) {
			printf("BTstack initialized.\n");
		} else if (btstack_event_state_get_state(packet) == HCI_STATE_OFF) {
			printf("BTstack shutting down.\n");
		}
		break;
	case HCI_EVENT_DISCONNECTION_COMPLETE:
		con_handle = hci_event_disconnection_complete_get_connection_handle(packet);
		printf("- LE Connection 0x%04x: disconnect, reason %02x\n", con_handle, hci_event_disconnection_complete_get_reason(packet));
		break;
	case HCI_EVENT_LE_META:
		switch (hci_event_le_meta_get_subevent_code(packet)) {
		case HCI_SUBEVENT_LE_CONNECTION_COMPLETE:
			// print connection parameters (without using float operations)
			con_handle = hci_subevent_le_connection_complete_get_connection_handle(packet);
			conn_interval = hci_subevent_le_connection_complete_get_conn_interval(packet);
			printf("- LE Connection 0x%04x: connected - connection interval %u.%02u ms, latency %u\n", con_handle, conn_interval * 125 / 100, 25 * (conn_interval & 3), hci_subevent_le_connection_complete_get_conn_latency(packet));

			// request min con interval 15 ms for iOS 11+
			printf("- LE Connection 0x%04x: request 15 ms connection interval\n", con_handle);
			gap_request_connection_parameter_update(con_handle, 12, 12, 4, 0x0048);
			break;
		case HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE:
			// print connection parameters (without using float operations)
			con_handle = hci_subevent_le_connection_update_complete_get_connection_handle(packet);
			conn_interval = hci_subevent_le_connection_update_complete_get_conn_interval(packet);
			printf("- LE Connection 0x%04x: connection update - connection interval %u.%02u ms, latency %u\n", con_handle, conn_interval * 125 / 100, 25 * (conn_interval & 3), hci_subevent_le_connection_update_complete_get_conn_latency(packet));
			break;
		case HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE:
			con_handle = hci_subevent_le_data_length_change_get_connection_handle(packet);
			printf("- LE Connection 0x%04x: data length change - max %u bytes per packet\n", con_handle, hci_subevent_le_data_length_change_get_max_tx_octets(packet));
			break;
		case HCI_SUBEVENT_LE_PHY_UPDATE_COMPLETE:
			con_handle = hci_subevent_le_phy_update_complete_get_connection_handle(packet);
			printf("- LE Connection 0x%04x: PHY update - using LE %s PHY now\n", con_handle, phy_names[hci_subevent_le_phy_update_complete_get_tx_phy(packet)]);
			break;
		default: break;
		}
		break;

	default: break;
	}
}

/// <summary>
/// The packet handler is used to track the ATT MTU Exchange and trigger ATT send
/// </summary>
void att_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t* packet, uint16_t size)
{
	UNUSED(channel);
	UNUSED(size);

	int mtu;
	switch (packet_type) {
	case HCI_EVENT_PACKET:
		switch (hci_event_packet_get_type(packet)) {
		case ATT_EVENT_CONNECTED:
			// setup new
			connection_handle = att_event_connected_get_handle(packet);
			display_max_packet_len = att_server_get_mtu(connection_handle) - 1;
			printf("ATT connected, handle 0x%04x, data len %u\n", connection_handle, display_max_packet_len);
			break;
		case ATT_EVENT_MTU_EXCHANGE_COMPLETE:
			mtu = att_event_mtu_exchange_complete_get_MTU(packet) - 3;
			display_max_packet_len = mtu - 1;
			printf("ATT MTU = %u => use data of len %u\n", mtu, display_max_packet_len);
			break;
		case ATT_EVENT_CAN_SEND_NOW:
			if (display_notification_enabled) send_frame_chunk();
			break;
		case ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE: printf("ATT Handle Value Indication complete\n"); break;
		case ATT_EVENT_DISCONNECTED:
			// free connection
			printf("ATT disconnected, handle 0x%04x\n", connection_handle);
			display_notification_enabled = 0;
			connection_handle = HCI_CON_HANDLE_INVALID;
			break;
		default: break;
		}
		break;
	default: break;
	}
}

/// <summary>
/// The ATT write is the Client Characteristic Configuration, which configures notification
/// and indication. If the ATT handle matches the client configuration handle, the new configuration value is stored.
/// If notifications get enabled, an ATT_EVENT_CAN_SEND_NOW is requested.
/// </summary>
int att_write_callback(hci_con_handle_t con_handle, uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t* buffer, uint16_t buffer_size)
{
	UNUSED(offset);

	if (transaction_mode != ATT_TRANSACTION_MODE_NONE) return 0;
	switch (att_handle) {
	// stdout characteristic notification
	case ATT_CHARACTERISTIC_205b0a33_bfaf_44ca_8c39_fd248f281f4f_01_CLIENT_CONFIGURATION_HANDLE: break;
	// display characteristic notification
	case ATT_CHARACTERISTIC_018ea0e5_77a0_424f_bd71_73a2ac1792dd_01_CLIENT_CONFIGURATION_HANDLE:
		display_notification_enabled = little_endian_read_16(buffer, 0) == GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;
		printf("display notification enabled: %u\n", display_notification_enabled);
		if (display_notification_enabled) {
			display_attribute_handle = ATT_CHARACTERISTIC_018ea0e5_77a0_424f_bd71_73a2ac1792dd_01_VALUE_HANDLE;
			first = true; // workaround for first frame after connecting not being sent
			att_server_request_can_send_now_event(connection_handle);
		}
		break;
		// stdout characteristic write
	case ATT_CHARACTERISTIC_205b0a33_bfaf_44ca_8c39_fd248f281f4f_01_VALUE_HANDLE:
		break;
		// display characteristic write
	case ATT_CHARACTERISTIC_018ea0e5_77a0_424f_bd71_73a2ac1792dd_01_VALUE_HANDLE:
		break;
		// keyboard characteristic write
	case ATT_CHARACTERISTIC_a0252185_c27f_47aa_84c9_82dd3e219375_01_VALUE_HANDLE: _bt_keyboard->handle_keyboard_press(buffer[0]); break;
	default: printf("Write to 0x%04x, len %u\n", att_handle, buffer_size); break;
	}
	return 0;
}


BTManager::BTManager(WindowManager* window_manager)
{
	_window_manager = window_manager;
	_bt_keyboard = new BTKeyboard(_window_manager);
	setup();
}

void BTManager::send_display_frame(std::vector<uint8_t> display_bytes, std::vector<uint8_t> symbol_bytes)
{
	if (!display_notification_enabled) return;
	frame_chunks.clear();
	frame_chunk_index = 0;

	// split display bytes into chunks of display_max_packet_len bytes
	for (uint16_t i = 0; i < display_bytes.size(); i += display_max_packet_len) {
		uint16_t len = std::min(display_max_packet_len, static_cast<uint16_t>(display_bytes.size() - i));
		std::vector<uint8_t> data_chunk(display_bytes.data() + i, display_bytes.data() + i + len);
		// packet header
		data_chunk.insert(data_chunk.begin(), 0x00);
		frame_chunks.push_back(data_chunk);
	}
	// packet header containing number of following chunks
	symbol_bytes.insert(symbol_bytes.begin(), frame_chunks.size());
	frame_chunks.insert(frame_chunks.begin(), symbol_bytes);

	att_server_request_can_send_now_event(connection_handle);
}

void send_frame_chunk()
{
	// workaround for first frame after connecting not being sent
	if (first) {
		first = false;
		_window_manager->update(true);
		return;
	}
	////////////////////////////////////////////

	if (frame_chunks.size() <= frame_chunk_index) return;

	std::vector<uint8_t>* data_chunk = &frame_chunks[frame_chunk_index];
	frame_chunk_index++;

	att_server_notify(connection_handle, display_attribute_handle, data_chunk->data(), data_chunk->size());

	if (frame_chunks.size() > frame_chunk_index) att_server_request_can_send_now_event(connection_handle);
}

void BTManager::get_mac(bd_addr_t mac)
{
	cyw43_hal_get_mac(0, mac); // gets mac address of wifi
	mac[5] = mac[5] + 1;       // increment last byte by 1 for bluetooth mac
}

char* BTManager::get_mac_string()
{
	bd_addr_t mac_bytes;
	get_mac(mac_bytes);
	return bd_addr_to_str(mac_bytes);
}

void BTManager::enable_bt()
{
	hci_power_control(HCI_POWER_ON);
}

void BTManager::disable_bt()
{
	hci_power_control(HCI_POWER_OFF);
}

void BTManager::setup()
{
	// initialize CYW43 driver architecture
	if (cyw43_arch_init()) {
		printf("failed to initialise cyw43_arch\n");
		return;
	}

	// initialize l2cap
	l2cap_init();

	// setup SM: Display only
	sm_init();

	// setup ATT server
	att_server_init(profile_data, NULL, att_write_callback);

	// register for HCI events
	hci_event_callback_registration.callback = &hci_packet_handler;
	hci_add_event_handler(&hci_event_callback_registration);

	// register for ATT events
	att_server_register_packet_handler(att_packet_handler);

	// setup advertisements
	uint16_t adv_int_min = 0x0030;
	uint16_t adv_int_max = 0x0030;
	uint8_t adv_type = 0;
	bd_addr_t null_addr;
	memset(null_addr, 0, 6);
	gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);
	gap_advertisements_set_data(sizeof(adv_data), (uint8_t*)adv_data);
	gap_advertisements_enable(1);
}

#endif