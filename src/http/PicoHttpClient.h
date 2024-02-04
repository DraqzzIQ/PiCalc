#ifdef PICO
#pragma once
#include "http/HttpParams.h"
#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "http/IHttpClient.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/dns.h"
#include "lwip/init.h"
#include "lwip/pbuf.h"
#include "mbedtls/ssl.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define HTTP_METHOD_GET 0
#define HTTP_METHOD_POST 1

enum HttpMethod {
	Get,
	Post,
};

class PicoHttpClient: public IHttpClient
{
	public:
	PicoHttpClient(std::string baseUrl);
	HttpResponse get(std::string path, HttpRequest req)
	{
		return send_request(req, path, HttpMethod::Get);
	};
	HttpResponse post(std::string path, HttpRequest req)
	{
		return send_request(req, path, HttpMethod::Post);
	}
	void set_bearer_auth_token(std::string token)
	{
		this->_bearer_auth_token = token;
	};

	void create_tls_client();

	/*
	 * These are the functions that initially get called by LWIP.
	 * They need to be static because LWIP is a C library so it cannot
	 * deal with objects and member functions. Therefore the 'arg'
	 * parameter (provided by lwIP) points to the object instance.
	 */
	static err_t recv_callback(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err)
	{
		return static_cast<PicoHttpClient*>(arg)->receive(tpcb, p, err);
	}

	static err_t err_callback(void* arg, err_t err)
	{
		return static_cast<PicoHttpClient*>(arg)->client_error(err);
	}

	static err_t connected_callback(void* arg, struct tcp_pcb* tpcb, err_t err)
	{
		return static_cast<PicoHttpClient*>(arg)->connected_fn(tpcb, err);
	}


	static err_t dns_callback(const char* name, const ip_addr_t* addr, void* callback_arg)
	{
		return static_cast<PicoHttpClient*>(callback_arg)->dn_found(name, addr);
	}


	~PicoHttpClient();

	private:
	///< summary>
	/// sends a request get() and set() are just wrappers around this
	///< param name='req'> the HttpRequest to send </param>
	///< param name='uri'> the URI to send to</param>
	///< param name='method'> the HttpMethod to use</param>
	///</summary>
	HttpResponse send_request(HttpRequest req, std::string uri, HttpMethod method);
	///< summary>
	/// serializes a raw data string into an HttpResponse
	///< param name='data'> the data string to put into an HttpRequest
	///</summary>
	HttpResponse deserialize(std::string data);
	///< summary>
	/// serializes an HttpRequest into a raw data string
	///< param name='req'> the request to convert </param>
	///< param name='uri'> the URI of the request </param>
	///< param name='method'> the method of the request </param>
	///</summary>
	std::string serialize(HttpRequest& req, std::string uri, HttpMethod& method);

	u8_t* get_cert(std::string baseUrl);

	///< summary>
	/// altcp receive callback, look at the altcp doc for more info
	///</summary>
	err_t receive(struct tcp_pcb* tpcb, struct pbuf* p, err_t err);

	///< summary>
	/// altcp connection callback
	///</summary>
	err_t connected_fn(struct tcp_pcb* tpcb, err_t err);

	///< summary>
	/// altcp dns callback
	///</summary>
	err_t dn_found(const char* name, const ip_addr_t* addr);

	///< sumamry>
	/// altcp client error callback
	///</sumamry>
	err_t client_error(err_t err);

	std::string url_encode(const std::string& value);

	std::string _http_version = "HTTP/1.0";
	std::string _response_raw;
	int _content_l = 0;
	std::string _bearer_auth_token;
	std::string _base_url;
	std::ostringstream _error_msg;
	u8_t* _cert;
	bool _received = false;
	bool _connected = false;
	bool _dns_done = false;
	ip_addr_t* _ip_addr = new ip_addr_t();
	u16_t _port = 443;
	struct altcp_tls_config* _tls_config = NULL;
	struct altcp_pcb* _tls_client = NULL;
};
#endif
