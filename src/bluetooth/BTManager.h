#pragma once
#ifdef PICO
#include "bluetooth/BTKeyboard.h"
#include "utils/Utils.h"
#include "windows/WindowManager.h"
#include "btstack.h"
#include "casio_os.h"
#include "pico/cyw43_arch.h"
#include <iostream>
#include <vector>

class BTManager
{
	public:
	BTManager(WindowManager* window_manager);
	/// <summary>
	/// Sends the current display frame to the connected device
	/// and splits it into
	/// </summary>
	void send_display_frame(std::vector<uint8_t> display_bytes, std::vector<uint8_t> symbol_bytes);
	void send_char(char c);
	void get_mac(bd_addr_t mac);
	char* get_mac_string();
	void enable_bt();
	void disable_bt();

	private:
	/// <summary>
	/// Initializes L2CAP, the Security Manager, and configures the ATT Server with the pre-compiled
	/// ATT Database generated from casio_os.gatt. Finally, it configures the advertisements
	/// and boots the Bluetooth stack.
	/// </summary>
	void setup();
};
#endif