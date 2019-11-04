
#define SLL_HDR_LEN	14		/* total header length */
#define MAX_LINKHEADER_SIZE	1500

#define IPDEBUG_EXIT 1


typedef struct pcap_addr {
	struct pcap_addr *next;
	struct sockaddr *addr;		/* address */
	struct sockaddr *netmask;	/* netmask for that address */
	struct sockaddr *broadaddr;	/* broadcast address for that address */
	struct sockaddr *dstaddr;	/* P2P destination address for that address */
}pcap_addr_t;

struct bpf_insn {
	u_short	code;
	u_char 	jt;
	u_char 	jf;
	bpf_int32 k;
};

struct bpf_program {
	u_int bf_len;
	struct bpf_insn *bf_insns;
};

typedef struct pcap 
{
    int fd_arp;
    int fd_ip;
    int lo_ifindex;
    int bufsize;
    int snapshot;
    u_char *rcvbuf;
    struct bpf_program fcode;
}pcap_t;


