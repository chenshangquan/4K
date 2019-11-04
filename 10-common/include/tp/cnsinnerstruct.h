#ifndef _h_cnsinnerstruct_h__
#define _h_cnsinnerstruct_h__

#include "tpsys.h"
#include "tpstruct.h"
#include "md5.h"
#include "usermanage.h"


const int CN_MAX_FULLFILENAME_LEN = 128; // 完整文件名最大长度
const int CN_MAX_USER_NAME_LENGTH = 32; // 用户名长度
const int CN_MAX_PASSWORD_LENGTH  = 32; // 密码长度


//Added by meifang
//当前会场状态
typedef struct tagTTPCurCnsConfStatus
{		
	EmCALLSTATE	emCallState; //会场呼叫状态  
	BOOL        m_bJoinConf;//是否参会
	tm			m_tConfTime; 
	EmCnState   emCnsState; //会场运行状态
	s8			achConfName[TP_MAX_ALIAS_LEN+1];	//参与会议名称
public:
	tagTTPCurCnsConfStatus()
	{ 
		memset( this, 0, sizeof(struct tagTTPCurCnsConfStatus) );
	}
	u32 CalcElapseTime( const tm& tLaterTime )
	{
		u64 llOldTime = UnifyTimeBySec( m_tConfTime );
		u64 llLaterTime = UnifyTimeBySec( tLaterTime );
		u32 dwElapseTime = (u32)( llLaterTime - llOldTime );
		return dwElapseTime;
	}
	u64 UnifyTimeBySec( const tm& tTime )
	{
		int nPYRunYears = ( ( tTime.tm_year%4 ) ? ( tTime.tm_year/4 +1 ) : ( tTime.tm_year/4 ) );
		int nDays = tTime.tm_year*365 + nPYRunYears + tTime.tm_yday;
		u64 llHours = nDays*24 + tTime.tm_hour;
		u64 llMinutes = llHours*60 + tTime.tm_min;
		u64 llSeconds = llMinutes*60 + tTime.tm_sec;
		return llSeconds;
	}
}TTPCurCnsConfStatus;

//会场注册状态
typedef struct tagTTPCnsRegStatus
{
	BOOL    bIsSIPRegister;
	u32_ip  dwSIPIp;
	BOOL    bIsGKRegister;
	u32_ip  dwGkIp;

	public:
		tagTTPCnsRegStatus(){ memset( this, 0, sizeof(struct tagTTPCnsRegStatus) ); }
}TTPCnsRegStatus;

//TPad登录信息
typedef struct tagTTPTPadLoginRequest
{
	CLoginRequest     cLoginRequest;
	s8                achTPadVersion[MAX_DEVICEVER_LEN];

	public:
		tagTTPTPadLoginRequest(){ memset( this, 0, sizeof(struct tagTTPTPadLoginRequest) ); }
}TTPTPadLoginRequest;

//用户信息
typedef struct tagTTPUserInfo
{
	CUserFullInfo     cUserFullInfo;
	s8                achTPadVersion[MAX_DEVICEVER_LEN];

	public:
		tagTTPUserInfo(){ memset( this, 0, sizeof(struct tagTTPUserInfo) ); }
}TTPUserInfo;

//End to add


#endif // _h_tpinnerstruct_h__
