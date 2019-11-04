#ifndef __SNMP_CONFIG__
#define __SNMP_CONFIG__

#define SNMP_CONFIG_ZLOG                         1
#define SNMP_LOG_LENGTH                                     512
#define SNMP_LIMIT_NUM   				16
#define SNMP_COMMUNITY_NAME_LEN  	32
#define SNMP_COMMUNITY_IPADDR_LEN      32
#define SNMP_GROUP_NAME_LEN          		32
#define SNMP_VIEW_NAME_LEN            		32
#define SNMP_ENGINEID_NAME_LEN     		32
#define SNMP_CONTACT_LEN                 		32
#define SNMP_LOCATION_LEN                	32
#define SNMP_TRAPHOST_NAME_LEN            32
#define SNMP_TRAP_SECURITY_NAME_LEN  32
#define SNMP_USER_NAME_LEN           		32
#define SNMP_AUTH_PARA_LEN                    32
#define SNMP_PRIVACY_PARA_LEN               32
#define SNMP_VIEW_MIB_NAME_LEN    		50
#define SNMP_STD_MIN_ACL_NUM                0/*0-- not use acl role*/
#define SNMP_STD_MAX_ACL_NUM               99
#define SNMP_PACKET_LEN_LIMIT_MAX       17940
#define SNMP_PACKET_LEN_LIMIT_MIN       484
#define SNMP_COMM_PORT_LIMIT_MAX        65535
#define SNMP_COMM_PORT_LIMIT_MIN        1
#define SNMP_COMM_DEFAULT_PORT           161
#define SNMP_TRAP_DEFAULT_PORT            162
/*the snmp config record info types*/

#define snmp_config_error_logging(fmt, args...)   zlog_msg("snmp_config", ZLOG_ERROR, fmt, ##args)

typedef enum snmp_record_info_type
{
	snmp_config_commport_type = 0,
	snmp_config_community_type,
	snmp_config_view_type,
	snmp_config_group_type,
	snmp_config_user_type,
	snmp_config_traphost_type,
	snmp_config_server,
}snmp_record_info_type;

typedef enum trap_types
{
	trap_coldstart_type = 0,
	trap_warmstart_type,
	trap_auth_type,
	trap_max_type,         /*验证类型的最大值*/
}trap_types;

typedef enum auth_types
{
	auth_no_type = 0,
	auth_md5_type,
	auth_sha_type,
	auth_max_type,
}auth_types;

typedef enum access_types
{
	read_only_type = 0,
	read_write_type,
	access_max_type,
}access_types;

typedef enum version_types
{
	version_1 = 0,
	version_2,
	version_3,
	version_max,
}version_types;

typedef enum security_models
{
	auth_security_model = 0,
	noauth_security_model,
	privacy_security_model,
	max_security_model,
}security_models;

/*the struct of community information*/
typedef struct community_info_node {
	char community_name[SNMP_COMMUNITY_NAME_LEN + 1];
	char view_name[SNMP_VIEW_NAME_LEN + 1];
	char community_ipaddr[SNMP_COMMUNITY_IPADDR_LEN + 1];
	unsigned int   rw_option;/*0----ro,1-----rw*/
	unsigned int   acl_num;
	struct community_info_node * next; /*下一个节点指针*/	
}community_info_node;

/*the struct of group information*/
typedef struct group_info_node{
	char group_name[SNMP_GROUP_NAME_LEN + 1];
	//u_char    view_type;/*1---read view,2----write view  3 ---notify view*/
	char read_view_name[SNMP_VIEW_NAME_LEN + 1];
	char write_view_name[SNMP_VIEW_NAME_LEN + 1];
	char notify_view_name[SNMP_VIEW_NAME_LEN + 1];
	unsigned int    ver_type; /*0----v1,1-----v2c,2------v3*/
	unsigned int 	security_model;/*1---auth 2---noauth 3--- privacy*/
	unsigned int    acl_num;	
	struct group_info_node * next; /*下一个节点指针*/	
}group_info_node;

/*the struct of view information*/
typedef struct view_info_node{
	char view_name[SNMP_VIEW_NAME_LEN + 1];
	char mib_oid_name[SNMP_VIEW_MIB_NAME_LEN + 1];
	unsigned int included; /*included----->1,0-----excluded*/
	struct view_info_node * next; /*下一个节点指针*/	
}view_info_node;

/*the struct of traphost information*/
typedef struct traphost_info_node{
	char traphost_name[SNMP_TRAPHOST_NAME_LEN + 1];
	char trap_security_name[SNMP_TRAP_SECURITY_NAME_LEN + 1];
	unsigned int  trap_port;/*at default 162 */
	unsigned int  trap_ver;/*at default v1 1----v1; 2----v2c,3 ----v3*/;
	unsigned int  trap_security_model;/*1----auth,2---- noauth,3-----privacy*/
	struct traphost_info_node * next; /*下一个节点指针*/	
}traphost_info_node;

typedef struct user_info_node{
	char user_name[SNMP_USER_NAME_LEN + 1];
	char group_name[SNMP_GROUP_NAME_LEN + 1];
	char auth_parameters[SNMP_AUTH_PARA_LEN + 1];
	char privacy_parameters[SNMP_PRIVACY_PARA_LEN + 1];	
	unsigned int acl_num;
	unsigned int auth_type;/*0----md5, 1----sha*/
	unsigned int  ver_type;/*0 ---v1, 1----v2c,2----v3*/	
	struct user_info_node * next; /*下一个节点指针*/	
}user_info_node;



/*the struct of snmp config information*/
typedef struct snmp_config_info{
	unsigned int snmp_enable;
	unsigned int snmp_max_packetsize;	
	unsigned int snmp_comm_port;
	unsigned int snmp_debug_enable;
	char local_engineID[SNMP_ENGINEID_NAME_LEN + 1];
	char remote_engineID[SNMP_ENGINEID_NAME_LEN + 1];
	char sys_contact[SNMP_CONTACT_LEN + 1];
	char sys_location[SNMP_LOCATION_LEN + 1];
	
	unsigned int community_cur_nums;/*the current number of community ,SNMP_LIMIT_NUM*/
	struct community_info_node * community_phead;
	unsigned int group_cur_nums;
	struct group_info_node * group_phead;
	unsigned int view_cur_nums;
	struct view_info_node * view_phead;
	unsigned int  traphost_cur_nums;
	struct traphost_info_node * traphost_phead;
	unsigned int user_cur_nums;
	struct user_info_node * user_phead;
	
}snmp_config_info;

typedef struct snmp_config_req_msg{
	int type; /*see  snmp config record info types define */
	int option; /*0---add, 1---del*/
	int retval;/*OK---SUCCESS, ERROR-----FAILED*/
	int size;/*the size of record info*/
	void * pinfo; /*a snmp config record info pointer*/
}snmp_config_req_msg;


typedef struct snmp_config_ack_msg{
	int type; /*see  snmp config record info types define */
	int option; /*0---add, 1---del*/
	int retval;/*OK---SUCCESS, ERROR-----FAILED*/
}snmp_config_ack_msg;


extern struct snmp_config_info *  psnmp_config_info;

int  snmp_config_info_init();

/*community*/
int snmp_config_community_info_add( char * community_name, 
											char * community_ipaddr,
											 char * view_name,
											 unsigned int access_type,
											 unsigned int acl_num);

int snmp_config_community_info_del( char * community_name);


int snmp_config_community_info_get(struct community_info_node * com_info, 
										 char * community_name);

/*group*/
int snmp_config_group_info_add( char * group_name, 
											 u_char ver_type,
											 u_char auth_type,
											 char * read_view,
											 char * write_view,
											 char * notify_view,
											 u_short acl_num);

int snmp_config_group_info_del(char * group_name, u_char ver_type);

int snmp_config_group_info_get(char * group_name, u_char ver_type, group_info_node * pgroup_info);

/*view*/
int snmp_config_view_info_add( char * view_name, 
									u_char included,
									char * mib_name);

int snmp_config_view_info_del(char * view_name);

int snmp_config_view_mib_info_del(char * view_name,char * mib_name);

int snmp_config_view_info_get(char * view_name, char * mib_name);

/*snmp v3 user */
int snmp_config_user_info_add( char * user_name, 
									u_char auth_type,
									u_char ver_type,
									char * group_name,
									char * auth_paras,
									char * pri_paras,
									u_short acl_num);

int snmp_config_user_info_del(char * user_name);

/*int snmp_config_user_info_get(struct user_info_node * puser_info, 
									char * user_name);*/

int snmp_config_user_info_username_get(char * group_name,char * user_name);

/*trap host info */
int snmp_config_traphost_info_add( char * traphost_name, 
									char * trap_security_name,
									u_short  trap_port,
									u_char  trap_ver,
									u_char  trap_security_model);

int snmp_config_traphost_info_del(char * traphost_name, int port);

int snmp_config_trap_info_get(struct traphost_info_node * ptraphost_info, 
									char * traphost_name,int port);

/*other config info*/
/*snmp enable*/
int snmp_config_enable( );

int snmp_config_no_enable();

int snmp_config_enable_get(unsigned int * snmp_enable);
/*packet size*/
int snmp_config_packetsize_add(unsigned int packetsize );

int snmp_config_packetsize_del();

int snmp_config_packetsize_get(unsigned int * packetsize);

/*engineID*/
int snmp_config_engineID_add(unsigned int local, char * local_engineID );

int snmp_config_engineID_del(unsigned int local);

int snmp_config_engineID_get(unsigned int local, char * local_engineID);

/*sys contact*/
int snmp_config_sys_contact_add(char * sys_contact );

int snmp_config_sys_contact_del();

int snmp_config_sys_contact_get(char * sys_contact);
/*sys location*/
int snmp_config_sys_location_add(char * sys_location );

int snmp_config_sys_location_del();

int snmp_config_sys_location_get(char * sys_location);

int snmp_config_comm_port_add(unsigned int port );

int snmp_config_comm_port_del();

int snmp_config_comm_port_get(unsigned short * port);


/*以下函数是跨进程接口函数 */
int snmp_config_resgister();

int snmp_config_comm_port_set_interproc(unsigned short port /*AGENT 与NMS通信的端口号，1-65535*/);

int snmp_config_community_info_add_interproc(
														char * community_name, /*共同体名，长度范围为1-32字节*/
														char * ipaddress ,/*NMS的IP地址，应该是
														A.B.C.D/M格式*/
														unsigned int acl_num/*acl 规则号 <1-99>*/
											    		);

int snmp_config_community_info_del_interproc(
														char * community_name /*共同体名，长度范围为1-32字节*/
													);

int snmp_config_view_info_add_interproc(
												char * view_name, /*视图名，长度范围为1-32字节*/
												u_char included,  /*这个视图是否包含mib_name的子树 1----包含，0---不包含*/
												char * mib_name /*视图所要包含的mib子树，长度范围为1-50字节*/
											   );

int snmp_config_view_info_del_interproc(
												char * view_name, /*视图名，长度范围为1-32字节*/
												char * mib_name /*视图所要包含的mib子树，长度范围为1-50字节*/
											);


int snmp_config_group_info_add_interproc(
												char * group_name, /*组名，长度范围为1-32字节*/
												u_char ver_type, /*snmp的版本号，0----v1,1-----v2c,2------v3 */
												u_char auth_type, /*是否需要验证和加密0-验证，1--不需要验证，2-需要验证和加密*/
												char * read_view, /*读权限的视图名，长度范围为1-32字节*/
												char * write_view, /*写权限的视图名，长度范围为1-32字节*/
												char * notify_view, /*通告的视图名，长度范围为1-32字节*/
												u_short acl_num /*acl的规则号，1-99*/
											);

int snmp_config_group_info_del_interproc(
												char * group_name, /*组名，长度范围为1-32字节*/
												u_char ver_type/*snmp的版本号，0----v1,1-----v2c,2------v3 */
											);


int snmp_config_user_info_add_interproc(
												char * user_name,/*用户名或共同体名，长度范围为1-32字节*/
												u_char auth_type, /*是否需要验证和加密0-验证，1--不需要验证，2-需要验证和加密*/

												u_char ver_type, /*snmp的版本号，0----v1,1-----v2c,2------v3 */

												char * group_name,/*与此用户名相关联的组，长度范围为1-32字节*/
												char * auth_paras, /*验证参数，长度范围为1-32字节*/
												char * pri_paras, /*加密参数，最大长度为32字节*/

												unsigned int acl_num/*acl规则号 1-99*/
											);
int snmp_config_user_info_del_interproc(
												char * user_name/*用户名或共同体名，长度范围为1-32字节*/
											);


int snmp_config_traphost_info_add_interproc(
												char * traphost_name, /*trap报文目的地的IP地址应该为1.1.1.1格式的有效的IP地址*/
												char * user_name,/* trap报文的用户名/共同体,* 长度范围为1-32字节*/
												u_short  trap_port, /* trap报文目的地的端口号1-65535*/
												u_char  trap_ver,/* trap报文的版本0-v1,1-v2,3-v3*/
												u_char  trap_security_model/*是否需要验证和加密0-验证，1--不需要验证，2-需要验证和加密*/
											);


int snmp_config_traphost_info_del_interproc(
												char * traphost_name, /*trap报文目的地的IP地址为1.1.1.1格式的有效的IP地址*/
												u_short  trap_port/* trap报文目的地的端口号<1-65535>*/
											);

int snmp_config_debug_output_enable( );

int snmp_config_debug_output_disable();

#endif

