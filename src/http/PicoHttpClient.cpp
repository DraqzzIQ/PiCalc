#include "http/PicoHttpClient.h"
#include <sstream>
#define HTTP_METHOD_GET 0
#define HTTP_METHOD_POST 1

PicoHttpClient::PicoHttpClient(std::string baseUrl)
{
	this->base_url = baseUrl;
	ip_addr = new ip_addr_t();
	tls_config = new altcp_tls_config();
	tls_client = altcp_tls_new(tls_config, IPADDR_TYPE_ANY);
	dns_getbyhostname(baseUrl, ip_addr, dn_found, NULL);
	altcp_err(tls_client, (tcp_err_fn)PicoHttpClient::client_error);
	altcp_recv(tls_client, (tcp_recv_fn)PicoHttpClient::recieve);
}

PicoHttpClient::send_request(HttpRequest req, std::string uri, HttpMethod method)
{
	while (!connected)
		sleep_ms(200);

	size_t data_pos = 0;
	std::string data = serialize(&req, uri, method);
	if (data.length() > altcp_sndbuf()) {
		for (int i = 0 : data_pos < data.length, i++) {
			data_pos += string.substr(data_pos, altcp_sndbuf()).length();
			altcp_write(tls_client, NULL, altcp_sndbuf(), string.substr(data_pos, altcp_sndbuf()));
			altcp_output(tls_client);
		}
	}

	while (true) {
		if (received) {
			received = false;
			// TODO
		}

		sleep_ms(200);
	}
}

PicoHttpClient::serialize(HttpRequest& req, std::string uri, HttpMethod& method)
{
	string data;
	string method_str;
	if (method == HttpMethod::Get) {
		method_str = "GET";
	} else {
		method_str = "POST";
	}

	data += method_str + " " + uri + " HTTP/1.1";
	for (auto& h : req.headers) {
		data += h.first + ": " + h.second + "\n";
	}
	data += "\n" + h.body;
	return data;
}

PicoHttpClient::deserialize(std::string data)
{
	HttpResponse res;
	u16_t status_code;
	istringstream data_s(data);
	string l;
	string key, value;

	data_s >> status_code >> std::endl;

	while (std::getline(data_s, l)) {
		if (l.empty()) {
			break;
		}

		istringstream tmp(l);

		tmp >> key >> ": " >> value >> std::endl;
	}

	data_s.read(&res.body, res.headers.find("Content-Length").next()))

    return res;
}

PicoHttpClient::recieve(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err)
{
	switch (err) {
	case ERR_OK:

		u16_t data_read = 0;
		std::string data(p->tot_len);
		struct pbuf* head;

		// Print packet buffer
		while (buf->len != buf->tot_len) {
			data += buf->payload;
			buf = buf->next;
		}
		data += buf->payload;

		// Advertise data reception
		altcp_recved(pcb, head->tot_len);
		received = true;
		break;


	case ERR_ABRT:
		pbuf_free(head);
		err = ERR_OK;
		break;
	}

	return err;
}


PicoHttpClient::client_error(void* arg, err_t err)
{
	// TODO
	return err;
}

PicoHttpClient::connected(void* arg, struct tcp_pcb* tpcb, err_t err)
{
	connected = true;
	return err
}

PicoHttpClient::dn_found(const char* name, const ip_addr_t, void* callback_arg)
{
	altcp_connect(tls_client, ip_addr, port, (tcp_connected_fn)PicoHttpClient::connected);
}


PicoHttpClient::~PicoHttpClient()
{
	altcp_tls_free_config(tls_config);
	altcp_shutdown(tls_client, 1, 1);
}
