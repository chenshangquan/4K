// cnsSession.h: interface for the CCnsSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
#define AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_

#include "cnsSessionCtrlIF.h"
#include "cncmsgdriver.h"
#include "usermanage.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCnsSession : public CCnsSessionCtrlIF, 
					public CCncMsgDriver
{
public:
	CCnsSession();
	~CCnsSession();
   

    /*功    能  向服务器发送消息 
	参    数  dwType：消息类型，（TYPE_CMESSAGE：直接使用osp的post接口发送，TYPE_TPMSG：使用CKdvMsg的post接口发送）
	返 回 值  成功返回0，失败返回错误码 
	说    明  为便于统一控制是否向服务器发送消息，其它功能类需要与服务器通信时，均使用该接口*/ 
	u16 PostMsg( u32 dwType  = TYPE_CMESSAGE );

    /*功    能  初始化lib库环境
	参    数  wAppID:  自身使用的的appID
              dwDesIID: 目的appID
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_CN_UE, 1) );

   
	//获取接口 
	virtual u16 CncGetInterface(CCncAddrbookIF **ppCtrl);
	virtual u16 CncGetInterface(CCncConfigIF **ppCtrl);   
	virtual u16 CncGetInterface(CCncConfCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CUmcConfCtrlIF **ppCtrl); 
	virtual u16 CncGetInterface(CCncUserCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CCncSipInfoCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncSysCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncPortDiagCtrlIF **ppCtrl);
 	virtual u16 CncGetInterface(CCncCenterCtrlIF **ppCtrl);
	virtual u16 CncGetInterface(CCncNetMngCtrlIF **ppCtrl);

	virtual void SetUseAddrbook( BOOL bUse ){ m_bUseAdddr = bUse; }

	virtual u16 ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser,
        const CString &strPwd, BOOL32 bConnect = TRUE);
    virtual u16 DisconnectCns();
	virtual BOOL IsConnectedCns();

	virtual u16 LoginCnsIns( u8 byIns );

	virtual const TTPCnList& GetConnectCnsList() const;

	//获取连接的INST
	u8 GetInst(){ return m_uInst; }

	u32 GetLoginIp(){ return m_dwCnsIp; }
    u32 GetLocalHostIP(){ return m_dwLocalIP; }



	virtual u16 DisConnectTpad(); //577

    TTPadSubInfo GetTPadSubInfo(){ return m_tTPadSubInfo; }

    virtual u16 ConnectTPad( TTPadSubInfo tSubInfo );

    virtual u16 SetTpadSysName( string strSysName );//dyy 2013年8月29日
	
protected:
	// 初始化OSP 
	u16 InitializeOsp();
    // 构建消息映射表 
	void BuildEventsMap(); 	

	virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);

	//消息处理
	void OnLinkBreak(const CMessage& cMsg);
	void OnCnsLoginRsp(const CMessage& cMsg);
	void OnCnsRefuseLoginNty(const CMessage& cMsg);
	void OnCnsListNty(const CMessage& cMsg);
	void OnLoginCnsInsRsp(const CMessage& cMsg);
	void OnCnsOnlineNty(const CMessage& cMsg);
	void OnCnsOfflineNty(const CMessage& cMsg);
	void OnLoginByOtherNotify(const CMessage& cMsg);

    //中控待机消息
    void OnCentreSleepNty(const CMessage& cMsg);
    //TPad登录用户信息
    void OnTPadLoginUserNotify(const CMessage& cMsg);
    //TPad Home键响应通知
    void OnTPadHomeKeyNotify(const CMessage& cMsg);
    //白板会议状态通知
    void OnWBConfStateNty(const CMessage& cMsg);
    //开启数据会议提示
    void OnNewConfCallReq(const CMessage& cMsg);  

private:
	BOOL32 m_bInitOsp;
	u32    m_dwLocalIP;	  //本地ip
	u32	   m_dwCnsIp;	  //连接的CNS的IP
	BOOL   m_bLogin;      //是否登录成功
     
	// 各个功能类接口类
	CCncAddrbookIF *m_pAddrBookIF;
	CCncConfigIF   *m_pConfigIF;
	CCncConfCtrlIF *m_pConfCtrlIF;
    CUmcConfCtrlIF *m_pUmcConfCtrlIF;
	CCncUserCtrlIF *m_pUserCtrlIF;
	CCncSipInfoCtrlIF *m_pSipInfoCtrlIF;
	CCncPortDiagCtrlIF	*m_pPortDiagIF;
	CCncSysCtrlIF       *m_pSysCtrlIF;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;
	CCncNetMngCtrlIF    *m_pNetMngCtrlIF;

	CLoginRequest   m_cUser; //连接时登录的用户	
	TTPCnList       m_tCnList;
	u8              m_uInst;
	BOOL32          m_bUseAdddr;//是否使用地址簿,默认使用 2012.12.12 yjj
	TTPadSubInfo    m_tTPadSubInfo;//记录登陆Tpad时登陆信息,包括登陆IP、端口及登陆类型

public:
    static CCnsSession *s_pCnsSession;//指向自己的指针，调用timer

};

#endif // !defined(AFX_CNSSESSION_H__31AEC8FF_0148_4F53_91EB_A546B7C4AB49__INCLUDED_)
