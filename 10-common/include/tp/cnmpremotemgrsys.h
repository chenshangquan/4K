#ifndef _CN_MPREMOTEMGR_SYS_H
#define _CN_MPREMOTEMGR_SYS_H
#include "kdvtype.h"

#ifdef WIN32

//#include <winsock2.h>
//#pragma comment(lib,"Ws2_32.lib")

#else

#include <arpa/inet.h>

#endif

#include <string.h>


#define MP_INVALID_U32_VALUE  ((u32)-1)
#define MP_INVALID_U16_VALUE  ((u16)-1)
#define MP_INVALID_U8_VALUE   ((u8)-1)


#define MP_DATA_MAX_SIZE  (u16)(57 * 1024)

#define MP_VIDEO_NUM_MAX  (u16)(4)

#define MP_CHECK_MSG_RCV_TIME  (u32)(3 * 1000)

#define MP_DATA_TRANS_MAX_SIZE (u16)(56 * 1024)
#define MP_FILEDATA_MAX_SIZE  (u32)(5 * 1024 * 1024)


const int  AID_MT_MPREMOTETER	=  65;    	     //X500终端的AID

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#define CNMP_ERR_SUCCESS 0
#define CNMP_ERR_FAIL 1

//const u32 g_nCnmpErrorCodeBeg = 1000;

//所有错误码，依次往下加 注意范围和结尾

// enum CNMP_ERR_XX_Code
// {
//     RK_ERR_IrCmd_Beg = g_nCnmpErrorCodeBeg,
//     RK_ERR_IrCmd_IDError,		//ID错误
//     RK_ERR_IrCmd_NoFind,		//ID不存在
//     RK_ERR_IrCmd_IDRepeat,		//ID重复
//     RK_ERR_IrCmd_NameRepeat,	//名称重复
//     RK_ERR_IrCmd_CfgError,		//配置错误
//     RK_ERR_IrCmd_MaxCount,		//上限
//     RK_ERR_IrCmd_End = RK_ERR_IrCmd_Beg + 10
// };


#endif // _CN_MPREMOTEMGR_SYS_H
