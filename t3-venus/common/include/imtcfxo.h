// imtcfxo.h: interface for the IMtcFxo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMTCFXO_H__CB4EE46F_7D3F_4953_8689_1B571C0F6B67__INCLUDED_)
#define AFX_IMTCFXO_H__CB4EE46F_7D3F_4953_8689_1B571C0F6B67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dispevent.h"
#include "mtcmt.h"
class IMtcFxo : public CDispEvent  
{
public:
	public:
	/*功能	打电话
	参数	const char *pchFxoNo [in]   对方号码
	        const u16 wFxoNoLen  [in]   号码长度
	返回值	成功返回0
	说明	无*/
	virtual u16 MakeCall(const TMtAddr &tMtAddr,const char *pchFxoNo,const u16 wFxoNoLen) = 0;
	/*功能	挂断电话
	参数	
	返回值	成功返回0
	说明	无*/
	virtual u16 Hangup() = 0;
	/*功能	接受电话
	参数	
	返回值	成功返回0
	说明	无*/
	virtual u16 Accept() = 0;
	/*功能	是否正在呼叫
	参数	
	返回值	TRUE	正在呼叫
			FALSE	没在呼叫
	说明	无*/
	virtual BOOL32 IsCalling()  = 0;
	/*功能	是否在连线状态
	参数	
	返回值	TRUE	在连接中
			FALSE	不在连接中
	说明	无*/
	virtual BOOL32 IsConnect()  = 0;
	/*功能	是否在空闲状态
	参数	
	返回值	TRUE	在空闲中
			FALSE	不在空闲中
	说明	无*/
	virtual BOOL32 IsIdle()  = 0;
	/*功能	拒绝接听
	参数	
	返回值	TRUE	成功
			FALSE	失败
	说明	无*/
	virtual u16 Reject() = 0;

};

#endif // !defined(AFX_IMTCFXO_H__CB4EE46F_7D3F_4953_8689_1B571C0F6B67__INCLUDED_)
