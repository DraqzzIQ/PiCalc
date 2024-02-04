#include "http/PicoHttpClient.h"
#ifdef PICO

// I know what ur thinking and yes, all of the
// lwip calls have to be wrapped in cyw43_arch_lwip_begin()
// and "_end() because lwip API is not thread safe.
PicoHttpClient::PicoHttpClient(std::string baseUrl):
	IHttpClient(baseUrl)
{
	int code = cyw43_arch_init();
	if (code != 0) {
		std::cout << "Error initializing cyw43 code: " << code << std::endl;
	}
	cyw43_arch_enable_sta_mode();

	code = cyw43_arch_wifi_connect_timeout_ms(PICO_WIFI_SSID, PICO_WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30 * 1000);
	if (code != 0) {
		std::cout << "Error connecting to wifi " << code << std::endl;
	}

	this->base_url = baseUrl;
#ifdef TLS_CERT
	this->cert = TLS_CERT;
#else
	this->cert = get_cert(baseUrl);
#endif


	cyw43_arch_lwip_begin();
	tls_config = altcp_tls_create_config_client(cert, sizeof(*cert));
	cyw43_arch_lwip_end();


	cyw43_arch_lwip_begin();
	err_t dns_error = dns_gethostbyname(baseUrl.c_str(), this->ip_addr, (dns_found_callback)&dns_callback, this);
	if (dns_error != ERR_OK && dns_error != ERR_INPROGRESS) {
		std::cout << "error: lwIP error code " << dns_error << " during dns lookup" << std::endl;
	}
	cyw43_arch_lwip_end();
}

HttpResponse PicoHttpClient::send_request(HttpRequest req, std::string uri, HttpMethod method)
{
	this->error_msg.clear();
	this->content_l = 0;
	this->received = false;
	this->response_raw.clear();
	err_t write_err;

	create_tls_client();

	while (!this->dns_done) {
		sleep_ms(10);
	}
	err_t conn_err = altcp_connect(this->tls_client, this->ip_addr, this->port, (altcp_connected_fn)&connected_callback);
	while (!this->connected) {
		sleep_ms(10);
	}
	connected = false;
	if (!bearer_auth_token.empty()) {
		req.headers.insert(std::make_pair("Authorization", "Bearer " + bearer_auth_token));
	}
	req.headers.insert(std::make_pair("Host", this->base_url));
	req.headers.insert(std::make_pair("Accept", "*/*"));
	size_t data_pos = 0;
	std::string data = serialize(req, uri, method);

	cyw43_arch_lwip_begin();
	if (data.length() > altcp_sndbuf(this->tls_client)) {
		cyw43_arch_lwip_end();
		for (int i = 0; data_pos < data.length(); i++) {
			cyw43_arch_lwip_begin();
			data_pos += altcp_sndbuf(this->tls_client);

			write_err = altcp_write(tls_client, data.substr(data_pos, altcp_sndbuf(this->tls_client)).c_str(), altcp_sndbuf(this->tls_client), 0x00);
			if (write_err == ERR_CLSD || write_err == ERR_ABRT || write_err == ERR_CONN) {
				error_msg << "error: connection error while sending data, try again" << std::endl;
			} else if (write_err != ERR_OK && write_err != ERR_INPROGRESS) {
				error_msg << "error: lwIP error code " << write_err << " while sending data" << std::endl;
			}

			cyw43_arch_lwip_end();
		}
	} else {
		cyw43_arch_lwip_end();
		cyw43_arch_lwip_begin();
		write_err = altcp_write(tls_client, data.c_str(), data.length(), TCP_WRITE_FLAG_COPY);
		if (write_err == ERR_CLSD || write_err == ERR_ABRT || write_err == ERR_CONN) {
			error_msg << "error: connection error while sending data, try again" << std::endl;
		} else if (write_err != ERR_OK) {
			this->error_msg << "error: lwIP error code \n"
							<< write_err << " while sending data" << std::endl;
		}
		// altcp_output(tls_client);
		cyw43_arch_lwip_end();
	}

	while (!this->received)
		sleep_ms(10);

	HttpResponse response = deserialize(this->response_raw);
	return response;
}

std::string PicoHttpClient::serialize(HttpRequest& req, std::string uri, HttpMethod& method)
{
	std::string method_str;
	std::ostringstream result;
	if (method == HttpMethod::Get) {
		method_str = "GET";
	} else {
		method_str = "POST";
	}

	result << method_str << " " << uri;
	if (req.params.size() > 0) {
		result << "?";
		for (auto p : req.params) {
			result << p.first << "=" << url_encode(p.second) << "&";
		}
	}

	result << " " << http_version << "\r\n";
	for (auto h : req.headers) {
		result << h.first << ": " << h.second << "\r\n";
	}
	result << "\r\n";

	if (method == HttpMethod::Post)
		result << req.body << "\r\n";

	return result.str();
}

void PicoHttpClient::create_tls_client()
{
	cyw43_arch_lwip_begin();
	this->tls_client = altcp_tls_new(tls_config, IPADDR_TYPE_ANY);
	cyw43_arch_lwip_end();

	cyw43_arch_lwip_begin();
	altcp_arg(this->tls_client, this);
	cyw43_arch_lwip_end();

	cyw43_arch_lwip_begin();
	altcp_err(this->tls_client, (altcp_err_fn)&err_callback);
	cyw43_arch_lwip_end();

	cyw43_arch_lwip_begin();
	altcp_recv(this->tls_client, (altcp_recv_fn)&recv_callback);
	cyw43_arch_lwip_end();
}

std::string PicoHttpClient::url_encode(const std::string& value)
{
	std::ostringstream escaped;
	escaped.fill('0');
	escaped << std::hex;

	for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		std::string::value_type c = (*i);

		// Keep alphanumeric and other accepted characters intact
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}

		// Any other characters are percent-encoded
		escaped << std::uppercase;
		escaped << '%' << std::setw(2) << int((unsigned char)c);
		escaped << std::nouppercase;
	}

	return escaped.str();
}

u8_t* PicoHttpClient::get_cert(std::string baseUrl)
{
	// TODO: implement this
	return nullptr;
}

/*
 * TODO - this method will get the root certificate for the provided url
u8_t* PicoHttpClient::get_cert(std::string baseUrl)
{
}
*/

HttpResponse PicoHttpClient::deserialize(std::string data)
{
	int status_code;
	Headers headers;
	std::string body;
	std::string http_error_msg;
	std::istringstream data_stream(data);
	std::string line;
	std::string response_http_version;

	data_stream >> response_http_version >> status_code;
	std::getline(data_stream, line);
	http_error_msg = line.substr(1, line.length() - 1);
	int delim_pos = 0;

	line.clear();
	for (int i = 0; !data_stream.eof(); i++) {
		std::getline(data_stream, line);
		delim_pos = line.find_first_of(':');
		if (line == "\r\n" || delim_pos == std::string::npos) {
			break;
		}
		headers.insert(std::make_pair(line.substr(0, delim_pos), line.substr(delim_pos + 2, line.length() - (delim_pos + 2))));
		line.clear();
		delim_pos = 0;
	}

	while (!data_stream.fail() && !data_stream.eof() && !data_stream.bad()) {
		getline(data_stream, line);
		body.append(line);
		if (!data_stream.eof() && !data_stream.fail() && !data_stream.bad())
			body.append("\n");
	}

	HttpResponse result(headers, body, status_code);

	if (status_code < 200 || status_code >= 300)
		result.error_msg = error_msg.str() + "error: http code " + std::to_string(status_code) + http_error_msg + "\n";

	return result;
}


err_t PicoHttpClient::receive(struct tcp_pcb* tpcb, struct pbuf* p, err_t err)
{
	if (p == nullptr) {
		received = true;
		this->tls_client = nullptr;
		return ERR_OK;
	}

	if (err == ERR_OK && p->tot_len > 0) {
		char buffer[p->tot_len + 1];
		pbuf_copy_partial(p, buffer, p->tot_len, 0);
		buffer[p->tot_len] = 0;

		altcp_recved(tls_client, p->tot_len);
		this->response_raw += std::string(buffer);
	} else {
		error_msg << "error: lwIP error code " << err << " while receiving data" << std::endl;
	}

	if (p->tot_len == p->len) {
		received = true;
		this->tls_client = nullptr;
	}

	pbuf_free(p);
	return err;
}


err_t PicoHttpClient::client_error(err_t err)
{
	error_msg << "error: lwIP client error " << err << std::endl;
	return err;
}

err_t PicoHttpClient::connected_fn(struct tcp_pcb* tpcb, err_t err)
{
	if (err == ERR_TIMEOUT) {
		error_msg << "error: timeout when connecting, try again." << std::endl;
	} else if (err != ERR_OK && err != ERR_ISCONN) {
		error_msg << "error: lwIP error code " << err << " while connecting" << std::endl;
	}
	connected = true;
	return err;
}

err_t PicoHttpClient::dn_found(const char* name, const ip_addr_t* addr)
{
	this->ip_addr = (ip_addr_t*)addr;
	dns_done = true;
	return ERR_OK;
}


PicoHttpClient::~PicoHttpClient()
{
	cyw43_arch_lwip_begin();
	altcp_shutdown(tls_client, 1, 1);
	cyw43_arch_lwip_end();

	altcp_tls_free_config(tls_config);

	cyw43_arch_deinit();
}
#endif
