#ifndef _h_tphandle_h__
#define _h_tphandle_h__


#include "tpobject.h"
class CTpHandler :public CTpLog
{
protected:
	CTpObject* m_pcInstance;
public:
	CTpHandler( CTpObject* pcObject){ m_pcInstance = pcObject;};
	virtual BOOL32 Handler( CTpMsg *const ptMsg ) = 0;

	virtual BOOL32 Create()	{ return TRUE; };
	virtual void Destroy(){};
	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );

	virtual u16  GetLogApp()	{ return m_pcInstance->GetAppID(); }	
	virtual u16  GetLogInst()	{ return m_pcInstance->GetInsID(); }
protected:
	int SetTimer(u32 nTimer, long nMilliSeconds, u32 nPara=0)
	{
		if( m_pcInstance )
			return m_pcInstance->SetTimer(nTimer ,nMilliSeconds ,nPara );
		return 0;
	};
	
	int KillTimer(u32 nTimerNo)
	{
		if( m_pcInstance )
			return m_pcInstance->KillTimer( nTimerNo);
		return 0;
	};
	
	CTpObject*   GetInstance(){return m_pcInstance;};
	
	virtual int NotifySelf( CTpMsg& cMsg )
	{//发送消息给自己
		return cMsg.Post( MAKEIID(m_pcInstance->GetAppID(),m_pcInstance->GetInsID() ) , 0 ,MAKEIID(m_pcInstance->GetAppID(),m_pcInstance->GetInsID() ) );
	};
};

#endif // _h_tphandle_h__
