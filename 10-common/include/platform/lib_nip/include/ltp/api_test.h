/*=======================================================================
模块名      : API测试
文件名      : 
相关文件    : 
文件实现功能: 
作者        : Jin Feng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/03/03			1.0			Jin Feng					创建
=======================================================================*/

#ifndef _API_TEST_H_
#define _API_TEST_H_

#ifndef __NIP_API_H
#include "api/nip_api.h"
#endif

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    API_TST_SUCCEED = 0,   // 测试成功
    API_TST_WARNING,   // 警告
    API_TST_FAILED,    // 测试失败
};

#ifndef MAXAPILEN 
#define MAXAPILEN 256
#endif

#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL

/*------------------------------------*/

struct api_mac_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    char macaddr[MAXAPILEN];
    /* 预期结果 */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct api_mac_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    char macaddr[MAXAPILEN];
    int  opcode;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ftp_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  enable;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  len;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
 	int  service_type;
    char pstr_user[MAXAPILEN];
    char pstr_pass[MAXAPILEN];
    int  opcode;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  id;
    char pstr_user[MAXAPILEN];
    char pstr_pass[MAXAPILEN];
    int  opcode;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char pathname[MAXAPILEN];

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int opcode;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_general_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int opcode;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
  	char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 	

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    int  num;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];  
    int  ifunit;  
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];
    int  opcode;  	
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN]; 	
    int  opcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_07_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];
    int  opcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_08_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	   char ifname[MAXAPILEN];
       char ip_addr[MAXAPILEN];
       char ip_mask[MAXAPILEN];
	   int opcode; 
	   int status;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_09_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit;
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];	
    int  opcode;	
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_interface_10_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    char ip_addr[MAXAPILEN];
    char ip_mask[MAXAPILEN];	
    int  opcode;	
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_lib_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char  usrname[MAXAPILEN];
    int   virnum;
    int   opcode;	

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    int  ifunit;			
    char max_frags[MAXAPILEN];		// auto or <%d>
	int  handle_type;			

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	 char ifname[MAXAPILEN];
     int  ifunit;
     int  min_pktlen;
	 int  handle_type;	

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_04_t
{
    /* 预置条件 */      
    int setup_env; 
    /* 测试输入 */
       int   virnum;                // virtual interface number
       char  mluser[MAXAPILEN];     // usernames binded with the virtual interface
       int   num;                   // number of  users
       int   opcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    int  ifunit;            // intface number
	int  loopback;	        // loop back state

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
   	int  ifunit;	
   	char max_frags[MAXAPILEN];
	int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_mp_07_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
	char ifname[MAXAPILEN];
    int  ifunit;
    int  min_pktlen;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ping_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char Host[MAXAPILEN];		        // host to ping 
    int opt_packetsize;    // 
    int opt_timeout;
    int opt_ttl;
    int dwOptions;           // 标志位
    int echoid;            // user data information携带的用户数据
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  echo_interval;  
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];         // name of interface
    int  ifunit;                    // intface number 
    char pppauth_type[MAXAPILEN];   // authentication type
    int handle_type;	
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];       // name of interface        
    int  ifunit;                 // intface number           
    char username[MAXAPILEN];     // pap username             
    char password[MAXAPILEN];     // password of pap user     
    int  handle_type;            // add、delete  type   
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];         // name of interface
    int  ifunit;                    // intface number 
    char chap_hostname[MAXAPILEN];	// chap hostname
    int  handle_type;            // add、delete  type  
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_password[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];    // name of interface
    int  ifunit;                  // intface number 
    char peer_addr[MAXAPILEN];  // default ip addr of the peer 
    int  handle_type;             // add、delete  type

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_07_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_interval;
    int handle_type;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_08_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_maxretry;
    int handle_type;

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_09_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  lcp_maxwait;
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_10_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    int  multi_flag;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_11_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    char proto[MAXAPILEN];      // protocol
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_12_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN];  // name of interface 	
    int   ifunit; 	          // intface number 
    unsigned long   bandwidth;	      // bandwidth 1-10000000
    int  optcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_13_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit;      // intface number 	
    char mode[MAXAPILEN];
    int  handle_type;	// add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_14_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long  echo_interval;
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_15_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];        
    int  ifunit;      
    char pppauth_type[MAXAPILEN];
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_16_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN];       // name of interface        
    int   ifunit;                 // intface number           
    char  username[MAXAPILEN];     // pap username             
    char  password[MAXAPILEN];     // password of pap user     
    int   handle_type;            // add、delete  type     
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_17_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_hostname[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_18_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN];           // name of interface
    int   ifunit;                       // intface number 
    char  chap_password[MAXAPILEN];    // chap hostname
    int   handle_type;		            // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_19_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];       // name of interface        
    int  ifunit;                 // intface number           
    char username[MAXAPILEN];     // pap username             
    char password[MAXAPILEN];     // password of pap user     
    int  handle_type;            // add、delete  type    
    /* 预期结果 */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_20_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];    // name of interface
    int  ifunit;                  // intface number 
    char peer_addr[MAXAPILEN];  // default ip addr of the peer 
    int  handle_type;             // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_21_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];       // name of interface 
    int  ifunit;        // intface number
    unsigned long lcp_interval;  // interval of  lcp configure-request
    int	 handle_type;		    // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_22_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long lcp_maxretry;
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_23_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    unsigned long lcp_maxwait;
    int handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_24_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_25_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit; 		    
    char proto[MAXAPILEN];      // protocol
    int  optcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_26_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   bandwidth;	    // bandwidth 1-10000000
    int   optcode;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_27_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  ifunit;      // intface number 	
    char mode[MAXAPILEN];
    int  handle_type;	// add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_28_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   echo_maxretry;	    // echo_maxretry 1-256
    int   handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_29_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long   echo_maxretry;	    // echo_maxretry 1-256
    int   handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_30_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long echo_paddinglen;	    // bandwidth 1-10000000
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_31_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long echo_paddinglen;	    // bandwidth 1-10000000
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_32_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_interval;	    // ipcp_interval 1-30
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_33_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_interval;	    // ipcp_interval 1-30
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_34_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_maxretry;    // max configure-request retransmissions
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_35_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   ifunit; 	        // intface number 
    unsigned long ipcp_maxretry;    // max configure-request retransmissions
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_36_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   virtual; 	        // intface number 
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_ppp_37_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  ifname[MAXAPILEN]; // name of interface 	
    int   vir_unit; 	        // intface number 
    int  handle_type;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_38_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_39_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_40_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  handle_type; 
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_41_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  defaultroute;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_42_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  handle_type; 
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_43_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  shutdown;
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_44_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
       char ifname[MAXAPILEN]; // name of interface 	
       int  ifunit; 	        // intface number 
       int  virtual_unit; 	        // intface number 

    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_45_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; // name of interface 	
    int  ifunit; 	        // intface number 
    int  virtual_unit; 	        // intface number 
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_46_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int  virtual_unit;
    char ethname[MAXAPILEN];
    char eth_ip_addr[MAXAPILEN];
    char eth_ip_mask[MAXAPILEN];
    char username[MAXAPILEN];
    char password[MAXAPILEN];
    int  enable_defaultroute;
    int  echo_interval;  // 1-30
    int  echo_retry;     // 1-256
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_47_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char pppoe_ver[MAXAPILEN];
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_ppp_48_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int vunit;
    char pppoe_state[512];
    int handle;
    /* 预期结果 */
    int val;
    int rtn;
};

struct api_ppp_49_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */		
    int test_func;
    /* 预期结果 */		
    int val;
    int rtn;
};
/*------------------------------------*/

struct api_route_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
 	char ip_net[MAXAPILEN]; 		        // 静态路由前缀
	char ip_mask[MAXAPILEN]; 		        // 静态路由网络掩码 
	char intfName_or_address[MAXAPILEN];    // 下一跳,如果下一跳为目的地地址,则后边的unit变量必须置为NULL
	char if_unit[MAXAPILEN]; 		            // 下一跳接口的单元号 
	int  pri;                               // 此路由的优先级,如果没有配置,则必须置为0
	int  dsize;
	int  opcode;			                // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int   num;
    char  dest_str[MAXAPILEN];    // 目的路由
    char  mask_str[MAXAPILEN];    // 路由的网络掩码
    char  gate_str[MAXAPILEN];    // 路由的网关
    int   distance;             // 路由优先级
    int   opcode;                 // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
 	char ip_net[MAXAPILEN]; 		        // 静态路由前缀
	char ip_mask[MAXAPILEN]; 		        // 静态路由网络掩码 
	char intfName_or_address[MAXAPILEN];    // 下一跳,如果下一跳为目的地地址,则后边的unit变量必须置为NULL
	char unit[MAXAPILEN]; 		            // 下一跳接口的单元号 
	int  pri;                               // 此路由的优先级,如果没有配置,则必须置为0
	int  opcode;			                // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int   num;
    char  dest_str[MAXAPILEN];    // 目的路由
    char  mask_str[MAXAPILEN];    // 路由的网络掩码
    char  gate_str[MAXAPILEN];    // 路由的网关
    int   distance;              // 路由优先级
    int   opcode;                 // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  dest_str[MAXAPILEN];    // 目的路由
    char  mask_str[MAXAPILEN];    // 路由的网络掩码
    char  gate_str[MAXAPILEN];    // 路由的网关
    int   distance;              // 路由优先级
    int   num;
    int   opcode;                 // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_route_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char  dest_str[MAXAPILEN];    // 目的路由
    char  mask_str[MAXAPILEN];    // 路由的网络掩码
    char  gate_str[MAXAPILEN];    // 路由的网关
    int   distance;              // 路由优先级
    int   num;
    int   opcode;                 // add、delete  type
    /* 预期结果 */
    int val;
    int rtn;
};


/*------------------------------------*/

struct api_vc_ioctl_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int   cmd;
    char  dest_str[MAXAPILEN];    // 目的路由         
    char  mask_str[MAXAPILEN];    // 路由的网络掩码   
    char  gate_str[MAXAPILEN];    // 路由的网关       
    int   distance;              // 路由优先级        
    int   opcode;                 // add、delete  type

	/* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_webserver_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int   opcode;                 // add、delete  type	
	
	/* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_webserver_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char path[MAXAPILEN];                // add、delete  type
	
	/* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_driver_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  channel;
    char timeslot[MAXAPILEN]; 
    int  serial;
    int  cmd;	
	/* 预期结果 */
    int val;
    int rtn;
};

/*------------------------------------*/

struct api_driver_02_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_03_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char mode[MAXAPILEN];
    int  serial;
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_04_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char frame[MAXAPILEN];
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_05_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char loop[MAXAPILEN];
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_06_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    /* 测试输入 */
    char  ifname[MAXAPILEN];
    int   e1;
    char  clock[MAXAPILEN];
    int   cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_07_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    /* 测试输入 */
    char ifname[MAXAPILEN]; 
    int  e1;
    int  channel;
    char timeslot[MAXAPILEN]; 
    int  serial;
    char cfg_str[MAXAPILEN]; 
    int  cmd;   
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_08_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char mode[MAXAPILEN];
    int  serial;
    int  cmd; 
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_09_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char frame[MAXAPILEN];
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_10_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char clock[MAXAPILEN];
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_11_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char ifname[MAXAPILEN];
    int  e1;
    char loop[MAXAPILEN];
    int  cmd;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_14_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    char  para[MAXAPILEN];
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_16_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    int  ret;
    char cpuinfo[128];	
    char binfo[64];	
    char kinfo[128];
    long memory_size;
    long flash_size;
    long cpu_frequency;
    long cpm_frequency;
    long bus_frequency;
	int eth_num;
	int v35_num;
	int e1_num;	
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_driver_17_t
{
    /* 预置条件 */
    	int setup_env;
    /* 测试输入 */
        char ifname[MAXAPILEN]; 
        int  e1;
        int  channel;
        char timeslot[MAXAPILEN]; 
        int  serial;
        char signal[MAXAPILEN]; 
        int  cmd;
    /* 预期结果 */
        int val;
        int  rtn;
};

/*------------------------------------*/

struct api_driver_18_t
{
  /* 预置条件 */
  	int setup_env;
  /* 测试输入 */
    char ifname[MAXAPILEN]; 
    int  e1;
    char signal[MAXAPILEN]; 
    int  cmd;
  /* 预期结果 */
    int val;
    int  rtn;
};

/*------------------------------------*/
struct api_ipcd_01_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */

	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct api_ipcd_02_t
{
    /* 预置条件 */      
    int  setup_env;
    /* 测试输入 */
    int time_to_detect;
	/* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/


struct api_dhcpc_01_t
{
    /* 预置条件 */
        int  setup_env;
    /* 测试输入 */
    	int enable;
        char ifname[MAXAPILEN];
	 int set_gateway;
    /* 预期结果 */
        int val;
		int rtn;
};

struct api_dhcpc_02_t
{
    /* 预置条件 */
        int  setup_env;
    /* 测试输入 */
        char ifname[MAXAPILEN];
    /* 预期结果 */
        int val;
		int rtn;
} ;

struct api_dhcpc_03_t
{
    /* 预置条件 */
        int  setup_env;
    /* 测试输入 */
        char ifname[MAXAPILEN];
    /* 预期结果 */
        int val;
		int rtn;
} ;

struct api_dhcpc_04_t
{
    /* 预置条件 */
    	int setup_env;
    /* 测试输入 */	 
	 int err;
    	 unsigned long ip;
        unsigned long mask;
        unsigned long gateway;	
        char ifname[MAXAPILEN];
	 
    /* 预期结果 */
        int val;
	 int rtn;

} ;
#endif
