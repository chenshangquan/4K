// pcmtsession.h: interface for the CPcmtSession class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _VCSLIB_H_
#define _VCSLIB_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "kdvtype.h"
#include "kdvsys.h"
#include "osp.h"
#include "evvcspcmt.h"

class CVcsLibMsgHandler;

class CPcmtSession  
{
public:
	CPcmtSession();
	virtual ~CPcmtSession();

    BOOL32 PostMsgToPcmt( u16 wEventID, const s8 *const pbyMsg = NULL, u16 wMsgLen = 0);
    void NotifyUI(u32 dwEvent, WPARAM wParam = 0, LPARAM lParam = 0);

    //deal msg
public:
    void OnDealMsg( CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );
    void OnVcsConnectAck( CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );
    void OnPcmtEntryConfNotify( CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );
	void OnPcmtQuitConfNotify( CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );
	void OnPcmtInitOkNotify( CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );

    void OnDisconnect(CMessage * const pMsg, CVcsLibMsgHandler *pMsgHandler );
    
    //cmd msg
public:
    void PowerOffPcmtCmd();
    BOOL32 SetVcsWndCmd( HWND hPreview, HWND hPrimo = NULL, HWND hSecond = NULL );
    BOOL32 PcmtQuitConfCmd();
	BOOL32 SetPcmtAnswerModeCmd( u8 byAnswerMode);
    BOOL32 CameralCtrCmd( emCammerCtrID emCtrId, BOOL32 bCtrState=FALSE );//bCtrState=false表示up， true表示按下down
	BOOL32 CameralCtrPreCmd();

    //init session
public:
	u16 ConnectPcmtReq(LPCTSTR pszMcuIP, u16 wPcmtListenPort);
    BOOL32 InitSession( HWND hWnd,  u16 wSessionId = 0 );
    
    HWND GetNotifyWnd() { return m_hWnd; }
    void SetNotifyWnd(HWND hWnd) { m_hWnd = hWnd; }
    
    void SetSessionId( u16 wSessionId ) { m_wSessionId = wSessionId; }
    u16 GetSessionId( void ) { return m_wSessionId; }

private:
    u32				m_dwPcmtNode;			
    u16             m_wSessionId;           //记录会话实例号，即目的的ins号
   
    HWND            m_hWnd;                 

public:
    
};

#endif /*_VCSLIB_H_*/
