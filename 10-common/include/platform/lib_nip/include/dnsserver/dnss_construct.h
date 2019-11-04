#ifndef _DNS_SER_CONSTRUCT
#define _DNS_SER_CONSTRUCT

int dns_construct_header(dns_request_t *m);
void dns_construct_reply( dns_request_t *m);
void dns_construct_error_reply(dns_request_t *m);
#endif

