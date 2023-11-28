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

class PicoHttpClient: IHttpClient
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
    std::string serialize(HttpRequest req, std::string uri, HttpMethod method);
    ///<summary>
    ///altcp receive callback, look at the altcp doc for more info
    ///</summary>
    std::string recieve(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err);
    ///<summary>
    ///altcp connected callback
    ///</summary>
    err_t connected(void *arg, struct tcp_pcb *tpcb, err_t err;
    ///<summary>
    ///altcp dns callback
    ///</summary>
    err_t dn_found(const char* name, const ip_addr_t, void* callback_arg);
    ///<sumamry>
    ///altcp client error callback
    ///</sumamry>
    err_t client_error(void* arg, err_t err);
    
    
    std::string bearer_auth_token;
    std::string base_url;
    std::bool received = false;
    std::bool connected = false;
    const ip_addr_t* ip_addr;
    u16_t port = 443:
    struct altcp_tls_config* tls_config = NULL;
    struct altcp_pcb* tls_client = NULL;
};

enum HttpMethod {
    Get,
    Post,
};
