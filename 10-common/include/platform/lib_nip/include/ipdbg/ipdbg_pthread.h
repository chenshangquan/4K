
struct debug_ip_protocol_index
{
	unsigned char ptr;
	int           enable;
};

struct debug_ip_protocol
{
	unsigned int proto;
	int (*do_debug)(char *rcvbuf, unsigned char pstate);
};

#define PTR				debug_ip_protocol_index[proto].ptr
#define IPPROTO_NUM 	256
#define IP_INTERFACE_FORMAT_LEN		32
#define TCPHDRLEN       20
#define ICMPHDRLEN      8
#define IPHDRLEN        20
#define UDPHDRLEN       8

int debug_ip_enable; 
int debug_init; 
int sys_get_arp_debug;
int sys_get_ip_debug;
int sys_if_debug;

