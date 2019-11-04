#ifndef _TP_AUTH_H_
#define _TP_AUTH_H_

#include "kdvtype.h"


#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPAUTHDLL)

#ifdef TPAUTHDLL_EXPORTS
#define TPAUTH_API __declspec(dllexport)
#else
#define TPAUTH_API __declspec(dllimport)
#endif

#else  // 其他平台的，或者是静态链接

#define TPAUTH_API 

#endif// (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPAUTHDLL)

#ifndef TPIN
#define TPIN
#endif// TPIN

#ifndef TPOUT
#define TPOUT
#endif//TPOUT

#define TPAUTH_LISTEN_PORT		5050
#define TPAUTH_INNER_UDP_PORT	6666

typedef struct tagTTpAuthUserParam
{
	u32		m_dwAppCall;	//appcall (confid+epid)
	u32		m_dwPaCall;		//pacall
	u32		m_dwUserParam;  //扩展

	tagTTpAuthUserParam()
	{
		Clear();
	}

	void Clear()
	{
		m_dwAppCall = 0;
		m_dwPaCall = 0;
		m_dwUserParam = 0;
	}

	tagTTpAuthUserParam& operator = (const tagTTpAuthUserParam& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwAppCall = tRhs.m_dwAppCall;
		this->m_dwPaCall = tRhs.m_dwPaCall;
		this->m_dwUserParam = tRhs.m_dwUserParam;
		return *this;
	}

}TTpAuthUserParam;

enum EmTpAuthRes
{
	em_tp_auth_res_success = 0, // 认证成功
	em_tp_auth_res_fail,
	em_tp_auth_res_unreachable,
	em_tp_auth_res_localerror,
	em_tp_auth_res_paramerror,

	em_tp_auth_res_end = 100,
};
typedef void (*CBTpAuthRes) (TTpAuthUserParam tUsrParam, u32 dwLocalIp, u32 dwDstIp, EmTpAuthRes emRes);

//初始化，调用一次即可
//返回值为FALSE则为调用异常
TPAUTH_API BOOL32 InitTpAuth(CBTpAuthRes pcbFunRes);

// 认证请求
// 需要同时检查bWaitCB和返回值
//bWaitCB为TRUE,返回值为em_tp_auth_res_success,需要等待回调告知认证结果
//bWaitCB为TRUE,返回值为除em_tp_auth_res_success外其他,调用异常
//bWaitCB为FALSE,返回值即为认证结果
TPAUTH_API EmTpAuthRes TpAuthReq(TPIN TTpAuthUserParam tUsrParam, TPIN u32 dwLocalIp, TPIN u32 dwDstIp, TPOUT BOOL32& bWaitCB);


#endif //_TP_AUTH_H_