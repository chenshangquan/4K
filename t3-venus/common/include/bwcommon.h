#ifndef _BWCOMMON_H
#define _BWCOMMON_H


#define    BW_SERVER_TCPPORT    6001
#define    BW_CLIENT_UDPPORT    5001

#define    MAX_CTRL_MSG_SIZE    1000
#define    MIN_PACKAGE_SIZE      100
#define    MAX_PACKAGE_SIZE      1000
#define    MIN_TIME_INTERVAL      7


#define     MAX_TRAIN_NUM          5
#define     MAX_TRAIN_LEN          50
#define     MAX_FLEET_LEN          6
#define     MAX_STREAM_LEN          50


typedef enum
{
	SERV_ERRMSG                    =(u8)-1,
	SERV_SENDLATENCY_NOTIFY        =(u8)1,
	SERV_FINISHED_TRAIN_NOTIFY     =(u8)2,
	SERV_FINISHED_STREAM_NOTIFY    =(u8)3,
	SERV_SENDFLEET_ACK             =(u8)4,

}enumServerMsg;

typedef  enum
{
	CLNT_ERRMSG               =(u8)-1,
	CLNT_SENDTRAIN_REQ        =(u8)1,
    CLNT_SENDFLEET_REQ        =(u8)2,
	CLNT_BADTRAIN_NOTIFY      =(u8)3,
	CLNT_GOODTRAIN_NOTIFY     =(u8)4,
	CLNT_NEXTSTREAM_REQ       =(u8)5,
	CLNT_FINISHSTREAM_NOTIFY  =(u8)6,
	CLNT_TERMINATE_NOTIFY     =(u8)7,
}enumClientMsg;


typedef  struct 
{
	u32   dwPackSize;                 //包大小
	u32   dwTimeInterval;             //发送周期
	u32   dwStreamLen;	              //发送流长
}TFleetParam;

#endif   // _BWCOMMON_H