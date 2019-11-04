/** @defgroup CncLib控制接口
 *  @author  肖楚然
 *  @version V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 *  @date    2011-2012
 *  @{
 */

#if !defined(AFX_CNSSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
#define AFX_CNSSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cncaddrbookif.h"
#include "cncconfigif.h"
#include "cncconfctrlif.h"
#include "umcConfCtrlIF.h"
#include "cncuserctrlif.h"
#include "cncsipinfoctrlif.h"
#include "cnccenterctrlif.h"
#include "cncportdiagctrlif.h"
#include "cncsysctrlif.h"
#include "cncnetmngctrlif.h"
#include "tpadplatstuct.h"

class CCnsSessionCtrlIF : public CKdvDispEvent 
{
public:
	
    /*功    能  初始化lib库环境
	参    数  dwAppID： 自身使用的appID
              dwDesIID: 目的appID,默认MAKEIID(AID_CN_UE, 1)
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_CN_UE, 1) ) = 0;


	/** 功能  获取特定的控制接口 
	 *  @param[out] ppCtrl CCncAddrbookIF接口
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在连接到终端时,可以获取这些接口,在断开连接后,所有这些接口立刻失效
	 */
	virtual u16 CncGetInterface(CCncAddrbookIF **ppCtrl) = 0;
	virtual u16 CncGetInterface(CCncConfigIF **ppCtrl) = 0;	
	virtual u16 CncGetInterface(CCncConfCtrlIF **ppCtrl) = 0; 
	virtual u16 CncGetInterface(CCncUserCtrlIF **ppCtrl) = 0;
	virtual u16 CncGetInterface(CUmcConfCtrlIF **ppCtrl) = 0;
	virtual u16 CncGetInterface(CCncSipInfoCtrlIF **ppCtrl) = 0;
 	virtual u16 CncGetInterface(CCncSysCtrlIF **ppCtrl) = 0;
 	virtual u16 CncGetInterface(CCncPortDiagCtrlIF **ppCtrl) = 0;
 	virtual u16 CncGetInterface(CCncCenterCtrlIF **ppCtrl) = 0;
	virtual u16 CncGetInterface(CCncNetMngCtrlIF **ppCtrl) = 0;
	
    /** 功能  是否使用地址簿 名
	 *  @param[in] bUseAddrbook	 是否使用
	 *  @return  
	 *  @remarks  维护工具不需要是使用地址簿  2012.12.12
	 */
	virtual void SetUseAddrbook( BOOL bUseAddrbook) = 0;

	/** 功能  连接到CNS 
	 *  @param[in] dwIP	被连接CNS的IP地址
	 *  @param[in] dwPort  被连接CNS的端口
	 *  @param[in] strUser	用户名
	 *  @param[in] strPwd	密码
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort,
		const CString& strUser,
		const CString& strPwd, BOOL32 bConnect = TRUE) = 0;

	/** 功能  断开CNS连接 
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在没有连接到CNS时调用此方法，不起任何作用
	 */
	virtual u16 DisconnectCns() = 0;

	/** 功能  查询是否已连接CNS 
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
	virtual BOOL IsConnectedCns() = 0;

	/** 功能  查询连接的Cns列表
	 *  @return  TTPCnList Cns列表
	 *  @remarks 
	 */
	virtual const TTPCnList& GetConnectCnsList() const = 0;

	/** 功能  登录CNS会场
	 *  @param[in] byIns	会场Ins
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 LoginCnsIns( u8 byIns ) = 0;

    /** 功能  获取本地ip
	 *  @param[in] 
	 *  @return  本地ip 
	 *  @remarks 
	 */
    virtual u32 GetLocalHostIP() = 0;

    /** 功能  获取登陆ip
	 *  @param[in] 
	 *  @return  登陆ip
	 *  @remarks 
	 */
	virtual u32 GetLoginIp() = 0;
    
    /** 功能  连接到TPad
     *  @param[in] dwIP	被连接tpad的IP地址
	 *  @param[in] dwPort  被连接tpad的端口
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
    virtual u16 ConnectTPad( TTPadSubInfo tSubInfo /*u32 dwIP, u32 dwPort, emTPadSubType emSubType*/) = 0;

    /** 功能  pad版cnc对Tpad的系统名进行设置
	 *  @param[in] strSysName 设置的系统名称
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
    virtual u16 SetTpadSysName( string strSysName ) = 0;
	 /** 功能 中控通知tpad 由tpad主动跟cns断链
	 *  @param[in] strSysName 设置的系统名称
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 DisConnectTpad() = 0;
};


#endif // !defined(AFX_CNSSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
