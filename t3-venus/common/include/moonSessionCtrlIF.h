/** @defgroup MoonLib控制接口
 *  @author  吴蒨蒨
 *  @version V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
 *  @date    2013-2014
 *  @{
 */

#if !defined(AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
#define AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "camconfigif.h"
#include "sysconfigif.h"


class CMoonSessionCtrlIF : public CKdvDispEvent 
{
public:
	
    /*功    能  初始化lib库环境
	参    数  dwAppID： 自身使用的appID
              dwDesIID: 目的appID,默认MAKEIID(AID_CN_UE, 1)
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_MOON_UE, 1) ) = 0;


	/** 功能  获取特定的控制接口 
	 *  @param[out] ppCtrl CCncAddrbookIF接口
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在连接到终端时,可以获取这些接口,在断开连接后,所有这些接口立刻失效
	 */
	virtual u16 MoonGetInterface(CCamConfigIF **ppCtrl) = 0;

	// important if not add F5 pass but have other effects 577
	virtual u16 MoonGetInterface(CSysConfigIF **ppCtrl) = 0;
	
	/** 功能  连接到Moon90三眼摄像机 
	 *  @param[in] dwIP	被连接CNS的IP地址
	 *  @param[in] dwPort  被连接CNS的端口
	 *  @param[in] strUser	用户名
	 *  @param[in] strPwd	密码
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect = TRUE) = 0;

	/** 功能  断开Moon90三眼摄像机连接 
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在没有连接到Moon90三眼摄像机时调用此方法，不起任何作用
	 */
	virtual u16 DisconnectMoon() = 0;

	/** 功能  查询是否已连接CNS 
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
	virtual BOOL IsConnectedMoon() = 0;

	/** 功能  登录CNS会场
	 *  @param[in] byIns	会场Ins
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 LoginMoonIns( u8 byIns ) = 0;

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
    
	 /** 功能 中控通知tpad 由tpad主动跟cns断链
	 *  @param[in] strSysName 设置的系统名称
	 *  @return  成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
//	virtual u16 DisConnectTpad() = 0;
};


#endif // !defined(AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
