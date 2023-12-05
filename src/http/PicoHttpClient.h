#include "http/HttpRequest.h"
#include "http/HttpResponse.h"
#include "http/IHttpClient.h"
#include <string>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"
#include "lwip/dns.h"
#define CERT 

enum HttpMethod {
    Get,
    Post,
};

class PicoHttpClient: public IHttpClient
{
	public:
    PicoHttpClient(std::string baseUrl);
    HttpResponse get(HttpRequest req, std::string path){
        return send_request(req, path, HttpMethod::Get);
    };
    HttpResponse post(HttpRequest req, std::string path){
        return send_request(req, path, HttpMethod::Post);
    }
    void set_bearer_auth_token(std::string token){
        this->bearer_auth_token = token;

    };
    ~PicoHttpClient();

	private:
    ///<summary>
    ///sends a request get() and set() are just wrappers around this
    ///<param name='req'> the HttpRequest to send </param>
    ///<param name='uri'> the URI to send to</param>
    ///<param name='method'> the HttpMethod to use</param>
    ///</summary>
    HttpResponse send_request(HttpRequest req, std::string uri, HttpMethod method);
    ///<summary>
    ///serializes a raw data string into an HttpResponse
    ///<param name='data'> the data string to put into an HttpRequest
    ///</summary>
    HttpResponse deserialize(std::string data);
    ///<summary>
    ///serializes an HttpRequest into a raw data string
    ///<param name='req'> the request to convert </param>
    ///<param name='uri'> the URI of the request </param>
    ///<param name='method'> the method of the request </param>
    ///</summary>
    std::string serialize(HttpRequest& req, std::string uri, HttpMethod& method);
    ///<summary>
    ///altcp receive callback, look at the altcp doc for more info
    ///</summary>
    altcp_recv_fn receive;
    ///<summary>
    ///altcp connected callback
    ///</summary>
    altcp_connected_fn connected_fn;
    ///<summary>
    ///altcp dns callback
    ///</summary>
    dns_found_callback dn_found;
    ///<sumamry>
    ///altcp client error callback
    ///</sumamry>
    altcp_err_fn client_error;
    
    
    
    int content_l = 0;
    std::string bearer_auth_token;
    std::string base_url;

    int received = 0;
    bool connected = false;
    ip_addr_t* ip_addr;
    u16_t port = 443;
    struct altcp_tls_config* tls_config = NULL;
    struct altcp_pcb* tls_client = NULL;
};

