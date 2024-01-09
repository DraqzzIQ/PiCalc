#include "http/PicoHttpClient.h"
#include "cyw43_ll.h"
#include "lwip/netif.h"
#include "lwip/dns.h"
#include "mbedtls/ssl.h"
#include "lwip/altcp.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/pbuf.h"
#include "pico/cyw43_arch.h"
#include <sstream>

#define PICO_WIFI_SSID "G-W0815"
#define PICO_WIFI_PASSWD "5681 7433 8133 7564"
#define PICO_WIFI_AUTH CYW43_AUTH_WPA2_AES_PSK
#define PICO_WIFI_TIMEOUT 200

#define HTTP_METHOD_GET 0
#define HTTP_METHOD_POST 1
using namespace std;

PicoHttpClient::PicoHttpClient(std::string baseUrl): IHttpClient(baseUrl){
    cyw43_arch_init();
    cyw43_arch_wifi_connect_timeout_ms(PICO_WIFI_SSID, PICO_WIFI_PASSWD, PICO_WIFI_AUTH, PICO_WIFI_TIMEOUT);
    cyw43_arch_lwip_begin();
    cyw43_arch_lwip_end();
    baseUrl = baseUrl;
    cyw43_arch_lwip_begin();
    this->tls_client = altcp_tls_new(tls_config, IPADDR_TYPE_ANY);
    cyw43_arch_lwip_end();
    cyw43_arch_lwip_begin();
    altcp_arg(this->tls_client, this);
    cyw43_arch_lwip_end();
    cyw43_arch_lwip_begin();
    dns_gethostbyname(baseUrl.c_str(), this->ip_addr, (dns_found_callback)&dns_callback, this);
    cyw43_arch_lwip_end();
    cyw43_arch_lwip_begin();
    altcp_err(this->tls_client, (altcp_err_fn)&err_callback);
    cyw43_arch_lwip_end();
    cyw43_arch_lwip_begin();
    altcp_recv(this->tls_client, (altcp_recv_fn)&recv_callback);
    cyw43_arch_lwip_end();
}

HttpResponse PicoHttpClient::send_request(HttpRequest req, std::string uri, HttpMethod method)
{
	this->content_l = 0;
	this->received = 0;
	while (!connected)
		sleep_ms(200);

	size_t data_pos = 0;
	std::string data = serialize(req, uri, method);
    cyw43_arch_lwip_begin();
	if (data.length() > altcp_sndbuf(this->tls_client)) {
        cyw43_arch_lwip_end();
		for (int i = 0 ; data_pos < data.length(); i++) {
            cyw43_arch_lwip_begin();
			data_pos += altcp_sndbuf(this->tls_client);
            cyw43_arch_lwip_end();
            cyw43_arch_lwip_begin();
            altcp_write(tls_client, data.substr(data_pos, altcp_sndbuf(this->tls_client)).c_str(), altcp_sndbuf(this->tls_client), 0x00);
            cyw43_arch_lwip_end();
            cyw43_arch_lwip_begin();
			altcp_output(tls_client);
            cyw43_arch_lwip_end();
		}
	}
    cyw43_arch_lwip_end();

}

std::string PicoHttpClient::serialize(HttpRequest& req, std::string uri, HttpMethod& method)
{
    std::string data;
	std::string method_str;
	if (method == HttpMethod::Get) {
		method_str = "GET";
	} else {
		method_str = "POST";
	}

	data += method_str + " " + uri + " HTTP/1.1";
	for (auto& h : req.headers) {
		data += h.first + ": " + h.second + "\n";
	}
	data += "\n" + req.body;
	return data;
}

/*
HttpResponse PicoHttpClient::deserialize(std::string data)
{
	HttpResponse res;
	u16_t status_code;
	istringstream data_s(data);
    std::string l;
	std::string key, value;
    std::streamsize lim = std::numeric_limits<std::streamsize>::max();

	data_s >> status_code;
    data_s.ignore(lim, '\n');

	while (std::getline(data_s, l)) {
		if (l.empty()) {
			break;
		}

		istringstream tmp(l);

		tmp >> key; 
        tmp.ignore(lim, " ");
        tmp >> value;
        data_s.ignore(lim, '\n');
	}

	data_s.read(&res.body, std::find(res.headers.begin(), res.headers.end(), "Content-Length").next()))

    return res;
}
*/

err_t PicoHttpClient::recieve(struct tcp_pcb* tpcb, struct pbuf* p, err_t err)
{
	struct pbuf* buf = p;
	if (err == ERR_OK) {
		std::string data;

		// Print packet buffer
		while (buf->len != buf->tot_len) {
			data.append(string((char*)buf->payload));
			buf = buf->next;
		}
		data.append(string((char*)buf->payload));

		// Advertise data reception
        cyw43_arch_lwip_begin();
	    altcp_recved(tls_client, buf->tot_len);
        cyw43_arch_lwip_end();
		this->received += buf->tot_len;
		received = true;
	}

	pbuf_free(buf);
	return err;
}


err_t PicoHttpClient::client_error(err_t err)
{
	// TODO
	return err;
}

err_t PicoHttpClient::connected_fn(struct tcp_pcb* tpcb, err_t err)
{
	connected = true;
	return err;
}

err_t PicoHttpClient::dn_found(const char* name, const ip_addr_t* addr)
{
    cyw43_arch_lwip_begin();
	return altcp_connect(tls_client, addr, port, (altcp_connected_fn)&connected_callback);
    cyw43_arch_lwip_end();
}


PicoHttpClient::~PicoHttpClient()
{
    cyw43_arch_lwip_begin();
	altcp_shutdown(tls_client, 1, 1);
    cyw43_arch_lwip_end();

    cyw43_arch_deinit();
}
