#include "http/PicoHttpClient.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/dns.h"
#include "mbedtls/config.h"
#include "mbedtls/ssl.h"
#include "lwip/altcp.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include <sstream>

#define HTTP_METHOD_GET 0
#define HTTP_METHOD_POST 1
using namespace std;

PicoHttpClient::PicoHttpClient(std::string baseUrl): IHttpClient(baseUrl){
    lwip_init();
    baseUrl = baseUrl;
    this->tls_client = altcp_tls_new(tls_config, IPADDR_TYPE_ANY);
    dns_gethostbyname(baseUrl.c_str(), this->ip_addr, &PicoHttpClient::dn_found, NULL);
    altcp_err(this->tls_client, &PicoHttpClient::client_error);
    altcp_recv(this->tls_client, &PicoHttpClient::recieve);
}

HttpResponse PicoHttpClient::send_request(HttpRequest req, std::string uri, HttpMethod method)
{
	this->content_l = 0;
	this->received = 0;
	while (!connected)
		sleep_ms(200);

	size_t data_pos = 0;
	std::string data = serialize(req, uri, method);
	if (data.length() > altcp_sndbuf(this->tls_client)) {
		for (int i = 0 ; data_pos < data.length(); i++) {
			data_pos += altcp_sndbuf(this->tls_client);
            altcp_write(tls_client, NULL, altcp_sndbuf(this->tls_client), data.substr(data_pos, altcp_sndbuf(this->tls_client)));
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
	data += "\n" + h.body;
	return data;
}

HttpResponse PicoHttpClient::deserialize(std::string data)
{
	HttpResponse res;
	u16_t status_code;
	istringstream data_s(data);
    std::string l;
	std::string key, value;

	data_s >> status_code;
    data_s.ignore(numeric_limits<streamsize>::max(), '\n');

	while (std::getline(data_s, l)) {
		if (l.empty()) {
			break;
		}

		istringstream tmp(l);

		tmp >> key; 
        tmp.ignore(numeric_limits<streamsize>::max(), " ");
        tmp >> value;
        data_s.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	data_s.read(&res.body, res.headers.find("Content-Length").next()))

    return res;
}

err_t PicoHttpClient::recieve(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err)
{
	struct pbuf* buf = p;
	if (err == ERR_OK) {
		std::string data(p->tot_len);

		// Print packet buffer
		while (buf->len != buf->tot_len) {
			data += (std::string)buf->payload;
			buf = buf->next;
		}
		data += (std::string)buf->payload;

		// Advertise data reception
	    altcp_recved(tls_client, buf->tot_len);
		this->received += buf->tot_len;
		received = true;
	}

	pbuf_free(buf);
	return err;
}


err_t PicoHttpClient::client_error(void* arg, err_t err)
{
	// TODO
	return err;
}

err_t PicoHttpClient::connected_fn(void* arg, struct tcp_pcb* tpcb, err_t err)
{
	connected = true;
	return err;
}

err_t PicoHttpClient::dn_found(const char* name, const ip_addr_t, void* callback_arg)
{
	return altcp_connect(tls_client, ip_addr, port, &PicoHttpClient::connected_fn);
}


PicoHttpClient::~PicoHttpClient()
{
	altcp_shutdown(tls_client, 1, 1);
}
