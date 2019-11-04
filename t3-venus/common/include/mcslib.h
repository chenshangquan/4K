/*=============================================================================
模   块   名: 会议控制台业务功能库
文   件   名: mcslib.h
相 关  文 件: mcslib.cpp
文件实现功能: mcslib上层接口实现
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/04/27  4.0     王昊        创建
=============================================================================*/

#ifndef _MCSLIB_20050427_H_
#define _MCSLIB_20050427_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>
#include <vector>
#include "osp.h"
#include "mcsstruct.h"
#include "vccommon.h"

using namespace std;

class CMsgHandler;
class CAddrMsgDeal;
class CConfControlMsgDeal;
class CConfManageMsgDeal;
class CConfOperateMsgDeal;
class CConnectMcuMsgDeal;
class CMcuOperateMsgDeal;
class CMtMsgDeal;
class CPeriMsgDeal;
class CUserMsgDeal;
class CMcuSession;

// 用于在线程间传递数据
typedef struct tagSessionHandler
{
    tagSessionHandler()
    {
        pSession = NULL;
        pHandler = NULL;
    }

    CMcuSession* pSession;
    CMsgHandler* pHandler;
} TSessionHandler;

class CMcuSession
{
public:
    CMcuSession();
    virtual ~CMcuSession();

    /*=============================================================================
    函 数 名:Create
    功    能:创建会话
    参    数:u16 wMonitorPort                   [in]    视频监控起始端口
             HWND hWnd                          [in]    上层应用程序句柄
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/06/27  4.0     王昊    创建
    =============================================================================*/
    u16 Create(u16 wMonitorPort, HWND hWnd, u32 dwMcuSessionAppID = AID_MCU_MCSSN);

    /*=============================================================================
    函 数 名:Free
    功    能:释放会话资源
    参    数:BOOL32 bMcslibQuit = FALSE         [in]    是否mcslib退出
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/06/27  4.0     王昊    创建
    2007/03/15  4.0     王昊    解决退出时的80字节泄露
    =============================================================================*/
    u16 Free(BOOL32 bMcslibQuit = FALSE);

//-----------------------------------------------------------------------------
//1. 数据读取
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:GetConfTable
    功    能:获取即时会议列表
    参    数:CConfTable * const pcConfTable     [out]   会议列表
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 GetConfTable(CConfTable * const pcConfTable);

    /*=============================================================================
    函 数 名:GetConfTemSchTable
    功    能:获取会议模板/预约会议列表
    参    数:CConfTemSchTable * const pcConfTemSchTable [out]   会议模板/预约会议列表
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/11/22  4.0     王昊    创建
    =============================================================================*/
    u16 GetConfTemSchTable(CConfTemSchTable * const pcConfTemSchTable);

    /*=============================================================================
    函 数 名:GetPeriTable
    功    能:获取外设列表
    参    数:CPeriTable * const pcPeriTable     [out]   外设列表
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 GetPeriTable(CPeriTable * const pcPeriTable);

    /*=============================================================================
    函 数 名:GetMcu
    功    能:获取Mcu信息
    参    数:TMcuExt * const ptMcuExt           [out]   TMcuExt
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcu(TMcuExt * const ptMcuExt);

    /*=============================================================================
    函 数 名:GetAddrBook
    功    能:获取地址簿
    参    数:CMcuAddrBook * const pcAddrbook       [out]   地址簿
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
	2006/02/16  4.0     顾振华  改用MCU提供的结构
    =============================================================================*/
    u16 GetAddrBook(CMcuAddrBook * const pcAddrbook);

    /*=============================================================================
    函 数 名:GetUserTable
    功    能:获取用户列表
    参    数:CUserTable * const pcUserTable     [out]   用户列表
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 GetUserManage(CUserManage * const pcUserManage);

    u16 GetVcsUserManage(CVcsUserManage * const pcUserManage);

    /*=============================================================================
    函 数 名:GetRecFileList
    功    能:获取录像文件列表
    参    数:TplArray<TRecFileInfo> &tplRecFileList [out]   录像文件列表
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败: MCSLIB_INVALID_PARAM               参数错误
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 GetRecFileList(TplArray<TRecFileInfo> &tplRecFileList);

    /*=============================================================================
    函 数 名:GetMtTestIpPort
    功    能:获取终端呼叫端口
    参    数:无
    注    意:无
    返 回 值:终端呼叫端口
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/12  4.0     王昊    创建
    =============================================================================*/
    u16 GetMtTestIpPort(void) const { return s_wMtTestIpPort; }

    /*=============================================================================
    函 数 名:GetCurUser
    功    能:获取当前用户
    参    数:无
    注    意:无
    返 回 值:当前用户名
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/29  4.0     王昊    创建
    =============================================================================*/
    LPCTSTR GetCurUser(void) const { return m_aszUserName; }

//-----------------------------------------------------------------------------
//2. 建链操作
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:ConnectMcuReq
    功    能:连接MCU
    参    数:LPCTSTR pszMcuIP                   [in]    连接MCU的IP地址字符串
             u16 wMcuListenPort                 [in]    MCU侦听端口
             LPCTSTR pszUserName                [in]    用户名
             LPCTSTR pszPwd                     [in]    密码
             u32 &dwLocalIpAddr                 [out]   本地接收码流IP地址
    注    意:无
    返 回 值:成功: MCSLIB_OK,
             失败:
             MCSLIB_INVALID_PARAM               参数错误
			 MCSLIB_NOT_IN_IDLE_STATE           链接还没有建立成功
			 MCSLIB_NOT_REGISTER_WINDOW         没有注册主窗口
			 MCSLIB_MUST_WAIT                   MCU忙,正在处理前一项请求
			 MCSLIB_FAIL_CONNECT_MCU            建链失败
			 MCSLIB_FAIL_SNDMSG_TO_MCU          向MCU发送消息失败
    相关消息:
	          MCS_DISP_CONNECT_ACK              连接MCU成功
			  MCS_DISP_CONNECT_NACK             连接MCU失败
	          MCS_DISP_CONNECT_MCU_TIMEOUT      连接MCU超时
	          MCS_DISP_OSP_DISCONNECT           osp断链
	          MCS_DISP_OSP_OVERFLOW             MCU上连接的会议控制台数超限 

			  MCS_DISP_SYNCTIME_ACK             系统时间同步成功
			  MCS_DISP_SYNCTIME_NACK            系统时间同步失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 ConnectMcuReq(LPCTSTR pszMcuIP, u16 wMcuListenPort, LPCTSTR pszUserName,
                      LPCTSTR pszPwd, u32 &dwLocalIpAddr);

//-----------------------------------------------------------------------------
//3. MCU操作
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:GetMcuMsStatusReq
    功    能:获取MCU的主备状态
    参    数:无
    注    意:Mcslib内部使用，当发生断链是发送
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/02/22  4.0     顾振华    创建
    =============================================================================*/
    u16 GetMcuMsStatusReq(void);

    
    /*=============================================================================
    函 数 名:GetMcuCpuUsageReq
    功    能:获取MCU的CPU使用率
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMCUCPUUSAGE_ACK    获取CPU使用率成功
             MCS_DISP_GETMCUCPUUSAGE_NACK   获取CPU使用率失败
             MCS_DISP_MCUCPUUSAGE_NOTIF     CPU使用率通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/30  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuCpuUsageReq(void);

    /*=============================================================================
    函 数 名:GetMcuStatusReq
    功    能:获取TMcuStatus
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMCUSTATUS_ACK      获取TMcuStatus成功
             MCS_DISP_GETMCUSTATUS_NACK     获取TMcuStatus失败
             MCS_DISP_MCUSTATUS_NOTIF       TMcuStatus通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/30  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuStatusReq(void);

    /*=============================================================================
    函 数 名:GetMcuCfgReq
    功    能:获取MCU外设配置
    参    数:无
    注    意:实际发送三条REQ请求, 由mcslib串消息
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMCUCFG_ACK         获取MCU配置成功
             MCS_DISP_GETMCUCFG_NACK        获取MCU配置失败
             MCS_DISP_MCUEQPCFG_NOTIF       MCU设备配置通知
             MCS_DISP_MCUBRDCFG_NOTIF       单板配置通知
             MCS_DISP_MCUGENERALCFG_NOTIF   MCU基本配置通知
             MCS_DISP_RECCFG_NOTIF          录像机配置通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/08  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuCfgReq(void);

    /*=============================================================================
    函 数 名:ModifyMcuEqpCfgReq
    功    能:设置MCU外设配置
    参    数:const TMcuEqpCfg &tMcuEqpCfg       [in]    MCU外设配置
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYMCUEQPCFG_ACK   修改MCU外设配置成功
             MCS_DISP_MODIFYMCUEQPCFG_NACK  修改MCU外设配置失败
             MCS_DISP_MCUEQPCFG_NOTIF       MCU外设配置通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/01  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyMcuEqpCfgReq(const TMcuEqpCfg &tMcuEqpCfg);
    
    //xst20090120修改电视墙预案配置
    u16 ChangeHDUSchemeInfoReq(const THduStyleCfgInfo *ptHduStyleCfgTable, s32 nStyleNum );

    /*=============================================================================
    函 数 名:ModifyMcuBrdCfgReq
    功    能:设置MCU单板
    参    数:const CBrdCfg *pcBrdCfgTable       [in]    MCU单板数组
             s32 nNum                           [in]    数组大小
             const TEqpRecCfgInfo *ptRecCfgTable[in]    录像机配置数组
             s32 nRecNum                        [in]    录像机个数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYMCUBRDCFG_ACK   修改MCU单板配置成功
             MCS_DISP_MODIFYMCUBRDCFG_NACK  修改MCU单板配置失败
             MCS_DISP_MCUBRDCFG_NOTIF       MCU单板配置通知
             MCS_DISP_RECCFG_NOTIF          录像机配置通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/31  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyMcuBrdCfgReq(const CBrdCfg *pcBrdCfgTable, s32 nNum,
                           const TEqpRecCfgInfo *ptRecCfgTable, s32 nRecNum,
                           const TEqpBasHDCfgInfo *ptHDBasCfgTable, s32 nHDBasNum,
                           const T8000BDscMod *pT8000BDscMod = NULL);

    /*=============================================================================
    函 数 名:ModifyMcuGeneralCfgReq
    功    能:设置MCU基本配置
    参    数:const TMcuGeneralCfg &tMcuCfg              [in]    MCU基本配置
             BOOL32 bApplyNow                           [in]    TRUE表示立即应用
    注    意:
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYMCUGENERALCFG_ACK   修改MCU基本配置成功
             MCS_DISP_MODIFYMCUGENERALCFG_NACK  修改MCU基本配置失败
             MCS_DISP_MCUGENERALCFG_NOTIF       MCU基本配置通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/31  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyMcuGeneralCfgReq(const TMcuGeneralCfg &tMcuCfg, BOOL32 bApplyNow);

    /*=============================================================================
    函 数 名:DisconnectMcuReq
    功    能:断开MCU连接
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    u16 DisconnectMcuReq(void);

    /*=============================================================================
    函 数 名:RebootMcuCmd
    功    能:重起MCU
    参    数:u32 dwMcuIP	  要重启的MCU的ip地址,如果是0,则主从同时重启 	
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/27  4.0     王昊    创建
	2006/2/16   4.0     顾振华  支持主从选择
    =============================================================================*/
    u16 RebootMcuCmd(u32 dwMcuIP);

    /*=============================================================================
    函 数 名:GetMcuTimeReq
    功    能:获取MCU时间
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMCUTIME_ACK        获取mcu系统时间成功
             MCS_DISP_GETMCUTIME_NACK       获取mcu系统时间失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/11/02  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuTimeReq(void);

    /*=============================================================================
    函 数 名:ModifyMcuTimeReq
    功    能:修改MCU时间
    参    数:const TKdvTime &tKdvTime           [in]    系统时间
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYMCUTIME_ACK     修改mcu系统时间成功
             MCS_DISP_MODIFYMCUTIME_NACK    修改mcu系统时间失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/11/01  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyMcuTimeReq(const TKdvTime &tKdvTime);

    /*=============================================================================
    函 数 名:RebootBrdReq
    功    能:重起MCU单板
    参    数:u8 byBrdId                         [in]    单板索引
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_REBOOTBRD_ACK         重起MCU单板成功
             MCS_DISP_REBOOTBRD_NACK        重起MCU单板失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/07  4.0     王昊    创建
    =============================================================================*/
    u16 RebootBrdReq(u8 byBrdId);

    /*=============================================================================
    函 数 名:UpdateBrdFileCmd
    功    能:更新单板业务文件
    参    数:u8 byBrdId                         [in]    单板索引
             const vector<CString> &vctFileName [in]    文件名
    注    意:Linux单板专用, 只能是.image和操作系统文件
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_UPDATEBRDFILE_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/08/16  4.0     王昊    创建
    =============================================================================*/
    u16 UpdateBrdFileCmd(u8 byBrdId, const vector<CString> &vctFileName);

    /*=============================================================================
    函 数 名:NPlusRollBackReq
    功    能:N+1备份 备份端 将数据同步到 N端
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_NPLUSROLLBACK_ACK     同步成功
             MCS_DISP_NPLUSROLLBACK_NACK    同步失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/12/15  4.0     王昊    创建
    =============================================================================*/
    u16 NPlusRollBackReq(void);

    /*=============================================================================
    函 数 名:NPlusResetCmd
    功    能:N+1备份 备份端 重置
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/12/15  4.0     王昊    创建
    =============================================================================*/
    u16 NPlusResetCmd(void);

//-----------------------------------------------------------------------------
//4. 会议管理
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:CreateConfReq
    功    能:创建会议
    参    数:const TConfInfo &tConfInfo         [in]    会议信息
	         const u8 *pbyPackInfo              [in]    打包的信息
              打包的信息结构(参见mcu定义)
                  2 byte(网络序,TMtAlias数组打包长度,即下面的n)
	              + n byte(TMtAlias数组打包,每包为 1byte(类型)+1byte(长度)+xbyte(字符串)+2byte(呼叫码率) 
	                  第1字节为TMtAlias类型,第2字节为长度x,下面的x字节为TMtAlias内容)
	              + TTvWallModule(可选字段，由会议属性中的是否有电视墙模板决定)
	              + TVmpModule(可选字段，由会议属性中的是否有画面合成墙模板决定)
			 s32 nPackBufLen                    [in]    信息包的长度
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CREATECONF_ACK        创建会议成功
			 MCS_DISP_CREATECONF_NACK       创建会议失败
             MCS_DISP_CONFINFO_NOTIF        会议信息通知(会议信息变化时发出)
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
             MCS_DISP_MTONLINECHANGE_NOTIF  终端在线状态变化通知(终端上下线时发出)
             MCS_DISP_CALLMTFAILURE_NOTIF   呼叫终端失败通知(呼叫终端失败时发出)
             MCS_DISP_TEMSCHCONFINFO_NOTIF  会议模板/预约会议信息通知(模板/预约会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 CreateConfReq(const TConfInfo &tConfInfo, const u8 *pbyPackInfo,
                      s32 nPackBufLen);

    /*=============================================================================
    函 数 名:HoldConfByTemplateReq
    功    能:根据模板召开(预约/即时)会议
    参    数:const CConfId &cConfId             [in]    会议号
             const TKdvTime *ptTime             [in]    为空则即时会议, 否则预约会议
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_HOLDCONF_BYTEMPLATE_ACK       根据模板创建会议成功
             MCS_DISP_HOLDCONF_BYTEMPLATE_NACK      根据模板创建会议失败
	         MCS_DISP_CONFINFO_NOTIF        会议信息通知(会议信息变化时发出)
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
             MCS_DISP_MTONLINECHANGE_NOTIF  终端在线状态变化通知(终端上下线时发出)
             MCS_DISP_CALLMTFAILURE_NOTIF   呼叫终端失败通知(呼叫终端失败时发出)
             MCS_DISP_TEMSCHCONFINFO_NOTIF  会议模板/预约会议信息通知(模板/预约会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 HoldConfByTemplateReq(CConfId &cConfId, const TKdvTime *ptTime = NULL);

    /*=============================================================================
    函 数 名:ReleaseConfReq
    功    能:结束会议
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byTakeMode                      [in]    CONF_TAKEMODE_ONGOING/
                                                        CONF_TAKEMODE_SCHEDULED/
                                                        CONF_TAKEMODE_TEMPLATE
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_RELEASECONF_ACK           结束会议成功
			 MCS_DISP_RELEASECONF_NACK          结束会议失败
	         MCS_DISP_RELEASECONF_NOTIF         结束会议通知(当有会议结束时产生)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ReleaseConfReq(const CConfId &cConfId, u8 byTakeMode);

    /*=============================================================================
    函 数 名:ChgConfLockModeReq
    功    能:修改会议锁定模式
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byLockMode                      [in]    会议锁定模式
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CHANGECONFLOCKMODE_ACK    修改会议锁定模式成功
			 MCS_DISP_CHANGECONFLOCKMODE_NACK   修改会议锁定模式失败
	         MCS_DISP_LOCKUSERINFO_NOTIF        锁定用户信息通知(锁定用户信息变化成功时产生)
             MCS_DISP_CONFLOCKMODE_NOTIF        会议锁定状态通知(锁定状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ChgConfLockModeReq(const CConfId &cConfId, u8 byLockMode);

    /*=============================================================================
    函 数 名:ChgConfPwdReq
    功    能:修改会议密码
    参    数:const CConfId &cConfId             [in]    会议号
             LPCTSTR pszPwd                     [in]    会议密码
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CHANGECONFPWD_ACK     修改会议密码成功
			 MCS_DISP_CHANGECONFPWD_NACK    修改会议密码失败
             MCS_DISP_CONFPWD_NOTIF         会议密码通知(会议密码变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ChgConfPwdReq(const CConfId &cConfId, LPCTSTR pszPwd);

    /*=============================================================================
    函 数 名:EnterConfPwdCmd
    功    能:输入会议密码
    参    数:const CConfId &cConfId             [in]    会议号
             LPCTSTR pszPwd                     [in]    会议密码
    注    意:接收到MCS_DISP_ENTERCONFPWD_REQ消息时, 调用此接口, 发送MCS_MCU_ENTERCONFPWD_ACK
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_WRONGCONFPWD_NOTIF    提示会议控制密码错误(密码错误时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 EnterConfPwdCmd(const CConfId &cConfId, LPCTSTR pszPwd);

    /*=============================================================================
    函 数 名:RefuseEnterConfPwdCmd
    功    能:拒绝输入会议密码
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:接收到MCS_DISP_ENTERCONFPWD_REQ消息时, 调用此接口, 发送MCS_MCU_ENTERCONFPWD_NACK
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 RefuseEnterConfPwdCmd(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:SaveConfReq
    功    能:保存会议
    参    数:const CConfId &cConfId             [in]    会议号
             BOOL32 bDefaultConf                [in]    是否存为缺省会议
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SAVECONF_ACK      保存会议成功
             MCS_DISP_SAVECONF_NACK     保存会议失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SaveConfReq(const CConfId &cConfId, BOOL32 bDefaultConf);

    /*=============================================================================
    函 数 名:ModifyConfReq
    功    能:修改会议(模板或预约会议)
    参    数:const TConfInfo &tConfInfo         [in]    会议信息
	         const u8 *pbyPackInfo              [in]    打包的信息
              打包的信息结构(参见mcu定义)
                  2 byte(网络序,TMtAlias数组打包长度,即下面的n)
	              + n byte(TMtAlias数组打包,每包为 1byte(类型)+1byte(长度)+xbyte(字符串)+2byte(呼叫码率) 
	                  第1字节为TMtAlias类型,第2字节为长度x,下面的x字节为TMtAlias内容)
	              + TTvWallModule(可选字段，由会议属性中的是否有电视墙模板决定)
	              + TVmpModule(可选字段，由会议属性中的是否有画面合成墙模板决定)
			 s32 nPackBufLen                    [in]    信息包的长度
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_RELEASECONF_NOTIF     结束会议通知(当有会议结束时产生)
             MCS_DISP_MODIFYCONF_ACK        修改会议成功
             MCS_DISP_MODIFYCONF_NACK       修改会议失败
             MCS_DISP_TEMSCHCONFINFO_NOTIF  会议模板/预约会议信息通知(模板/预约会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyConfReq(const TConfInfo &tConfInfo, const u8 *pbyPackInfo,
                      s32 nPackBufLen);

    /*=============================================================================
    函 数 名:DelayConfReq
    功    能:延长会议
    参    数:const CConfId &cConfId             [in]    会议号
	         u16 wAddTime                       [in]    会议延长时间,单位分钟
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_DELAYCONF_ACK     延长会议成功
             MCS_DISP_DELAYCONF_NACK    延长会议失败
             MCS_DISP_DELAYCONF_NOTIF   延长会议通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 DelayConfReq(const CConfId &cConfId, u16 wAddTime);

//-----------------------------------------------------------------------------
//5. 会议操作
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:SpecChairmanReq
    功    能:指定主席
    参    数:const CConfId &cConfId             [in]    会议号
	         const TMt &tMt                     [in]    主席终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SPECCHAIRMAN_ACK          指定主席成功
			 MCS_DISP_SPECCHAIRMAN_NACK         指定主席失败
			 MCS_DISP_SPECCHAIRMAN_NOTIF        指定主席通知(可以不处理, 实际无)
             MCS_DISP_SIMCONFINFO_NOTIF         简单会议信息通知(会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SpecChairmanReq(const CConfId &cConfId, const TMt &tMt);

    //主席选看vmp
    u16 VmpSelReq(const CConfId &cConfId, const TMt &tMt);
    /*=============================================================================
    函 数 名:CancelChairmanReq
    功    能:取消主席
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CANCELCHAIRMAN_ACK        取消主席成功
			 MCS_DISP_CANCELCHAIRMAN_NACK       取消主席失败
			 MCS_DISP_CANCELCHAIRMAN_NOTIF      取消主席通知(可以不处理, 实际无)
             MCS_DISP_SIMCONFINFO_NOTIF         简单会议信息通知(会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 CancelChairmanReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:SetChairmanModeCmd
    功    能:设置主席模式
    参    数:const CConfId &cConfId             [in]    会议号
             BOOL32 bHasChairman                [in]    是否有主席
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CONFCHAIRMODE_NOTIF       主席模式信息通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SetChairmanModeCmd(const CConfId &cConfId, BOOL32 bHasChairman);

    /*=============================================================================
    函 数 名:SpecSpeakerReq
    功    能:指定发言人
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    发言终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SPECSPEAKER_ACK           指定发言人成功
             MCS_DISP_SPECSPEAKER_NACK          指定发言人失败
             MCS_DISP_SPECSPEAKER_NOTIF         指定发言人通知(可以不处理, 实际无)
             MCS_DISP_CONFINFO_NOTIF            会议信息通知(会议信息变化时发出)
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SpecSpeakerReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:CancelSpeakerReq
    功    能:取消发言人
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CANCELSPEAKER_ACK         取消发言人成功
             MCS_DISP_CANCELSPEAKER_NACK        取消发言人失败
             MCS_DISP_CANCELSPEAKER_NOTIF       取消发言人通知(可以不处理, 实际无)
             MCS_DISP_CONFINFO_NOTIF            会议信息通知(会议信息变化时发出)
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 CancelSpeakerReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:ForceSeeSpeakerCmd
    功    能:是否强制会议与会终端接收发言人码流
    参    数:const CConfId &cConfId             [in]    会议号
             BOOL32 bForce                      [in]    是否强制
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CONFMODE_NOTIF    会议模式通知(会议模式变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ForceSeeSpeakerCmd(const CConfId &cConfId, BOOL32 bForce);

    /*=============================================================================
    函 数 名:AddMtReq
    功    能:增加终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    要增加的终端所属的MCU
             const TAddMtInfo *ptAddMtInfo      [in]    增加的终端信息
             s32 nMtNum                         [in]    终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDMT_ACK             增加终端成功
             MCS_DISP_ADDMT_NACK            增加终端失败
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 AddMtReq(const CConfId &cConfId, const TMcu &tMcu,
                 const TAddMtInfo *ptAddMtInfo, s32 nMtNum);

    /*=============================================================================
    函 数 名:AddMtReq
    功    能:增加终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    要增加的终端所属的MCU
             const TAddMtInfoEx *ptAddMtInfoEx  [in]    增加的终端信息
             s32 nMtNum                         [in]    终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDMT_ACK             增加终端成功
             MCS_DISP_ADDMT_NACK            增加终端失败
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2008/11/03  4.0     王廖荣    创建
    =============================================================================*/
    u16 AddMtReq(const CConfId &cConfId, const TMcu &tMcu,
                 const TAddMtInfoEx *ptAddMtInfoEx, s32 nMtNum);

    /*=============================================================================
    函 数 名:DelMtReq
    功    能:删除终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    要删除的终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_DELMT_ACK             增加终端成功
             MCS_DISP_DELMT_NACK            增加终端失败
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_CONFINFO_NOTIF        会议信息通知(会议信息变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 DelMtReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:StartMonitorReq
    功    能:开始监控
    参    数:u8 byIndex                         [in]    监控通道
             const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    监控终端
             u8 byMode		                    [in]    监控模式(MODE_BOTH、MODE_VIDEO、MODE_AUDIO)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTMONITOR_ACK      开始监控成功
             MCS_DISP_STARTMONITOR_NACK     开始监控失败
             MCS_DISP_STARTMONITOR_NOTIF    开始监控通知
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StartMonitorReq(u8 byIndex, const CConfId &cConfId, const TMt &tMt,
                        u8 byMode);

    /*=============================================================================
    函 数 名:StopMonitorReq
    功    能:停止监控
    参    数:u8 byIndex                         [in]    监控通道
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPMONITOR_ACK       停止监控成功
             MCS_DISP_STOPMONITOR_NACK      停止监控失败
             MCS_DISP_STOPMONITOR_NOTIF     停止监控通知
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StopMonitorReq(u8 byIndex);

    /*=============================================================================
    函 数 名:SwitchMonitorReq
    功    能:将其它监控通道和0通道对调
    参    数:u8 byIndex                         [in]    监控通道
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码。mcslib串了消息
    相关消息:MCS_DISP_STARTMONITOR_ACK      开始监控成功
             MCS_DISP_STARTMONITOR_NACK     开始监控失败
             MCS_DISP_STARTMONITOR_NOTIF    开始监控通知
             MCS_DISP_STOPMONITOR_ACK       停止监控成功
             MCS_DISP_STOPMONITOR_NACK      停止监控失败
             MCS_DISP_STOPMONITOR_NOTIF     停止监控通知
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/08/23  4.0     王昊    创建
    =============================================================================*/
    u16 SwitchMonitorReq(u8 byIndex);

    /*=============================================================================
    函 数 名:StopAllMonitorCmd
    功    能:停止所有监控
    参    数:无
    注    意:切换MCU或断开MCU时用到
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPMONITOR_ACK       停止监控成功
             MCS_DISP_STOPMONITOR_NACK      停止监控失败
             MCS_DISP_STOPMONITOR_NOTIF     停止监控通知
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/12  4.0     王昊    创建
    =============================================================================*/
    u16 StopAllMonitorCmd(void);

    /*=============================================================================
    函 数 名:SendMsgCmd
    功    能:发送会议短消息
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt *ptMtTable               [in]    终端列表
             u16 wMtNum                         [in]    终端的个数, 为0时表示所有本级终端该消息
             const CRollMsg &cRollMsg           [in]    短消息信息
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SENDRUNMSG_NOTIF      短消息通知(实际无)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SendMsgCmd(const CConfId &cConfId, const TMt *ptMtTable, u16 wMtNum,
                   const CRollMsg &cRollMsg);
    
    //mpu-vmp操作
    u16 SendMsgVmpPriseizeAck(const CConfId &cConfId, TMt &tSeizedMt, u16 wSeizeChoiceNum, TplArray<TSeizeChoice> &ptSeizeChoice);
    u16 SendMsgVmpPriseizeNAck(const CConfId &cConfId, TMt &tSeizedMt);

//-----------------------------------------------------------------------------
//6. 会议控制
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:StartConfPollCmd
    功    能:开始会议轮询
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byPollType                      [in]    轮循类型(MODE_VIDEO、MODE_BOTH)
             u32 dwPollTimers                   [in]    轮询次数
             const TMtPollParam *ptMtPoll       [in]    轮循终端数组
             u16 wMtNum                         [in]    轮循终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StartConfPollCmd(const CConfId &cConfId, u8 byPollType, u32 dwPollTimers,
                         const TMtPollParam *ptMtPoll, u16 wMtNum);

    /*=============================================================================
    函 数 名:PauseConfPollCmd
    功    能:暂停会议轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 PauseConfPollCmd(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:ResumeConfPollCmd
    功    能:恢复会议轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ResumeConfPollCmd(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:StopConfPollCmd
    功    能:停止会议轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StopConfPollCmd(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:ChangeConfPollParamCmd
    功    能:修改会议轮询参数
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byPollType                      [in]    轮循类型(MODE_VIDEO、MODE_BOTH)
             u32 dwPollTimers                   [in]    轮询次数
             const TMtPollParam *ptMtPoll       [in]    轮循终端数组
             u16 wMtNum                         [in]    轮循终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/03/28  4.0     王廖荣    创建
    =============================================================================*/
    u16 ChangeConfPollParamCmd(const CConfId &cConfId, u8 byPollType,
                               u32 dwPollTimers,
                               const TMtPollParam *ptMtPoll, u16 wMtNum);

    /*=============================================================================
    函 数 名:SpecPollPosReq
    功    能:指定当前轮询终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    当前轮询终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_POLLSTATE_NOTIF       轮询信息通知(轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/03/30  4.0     王廖荣    创建
    =============================================================================*/
    u16 SpecPollPosReq( const CConfId &cConfId, const TMt &tMt );

    /*=============================================================================
    函 数 名:GetConfPollParamReq
    功    能:获取会议轮询参数
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETPOLLPARAM_ACK      得到轮循状态成功
             MCS_DISP_GETPOLLPARAM_NACK     得到轮循状态失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 GetConfPollParamReq(const CConfId &cConfId);


    /*=============================================================================
    函 数 名:StartTwPollCmd
    功    能:开始电视墙轮询
    参    数:const CConfId &cConfId             [in]    会议号
             const TTvWallPollInfo &tTwPollInfo [in]    轮询信息
             const TMtPollParam *ptMtPoll       [in]    轮循终端数组
             u16 wMtNum                         [in]    轮循终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_TWPOLLSTATE_NOTIF     电视墙轮询信息通知(电视墙轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/22  4.0     顾振华    创建
    =============================================================================*/
    u16 StartTwPollCmd(const CConfId &cConfId, 
                       const TTvWallPollInfo &tTwPollInfo,
                       const TMtPollParam *ptMtPoll, u16 wMtNum);

    /*=============================================================================
    函 数 名:PauseTwPollCmd
    功    能:暂停电视墙轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_TWPOLLSTATE_NOTIF     电视墙轮询信息通知(电视墙轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/22  4.0     顾振华    创建
    =============================================================================*/
    u16 PauseTwPollCmd(const CConfId &cConfId, s8 byTwHduFlag = 0); //0--TW 1--Hdu

    /*=============================================================================
    函 数 名:ResumeTwPollCmd
    功    能:恢复电视墙轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_TWPOLLSTATE_NOTIF     电视墙轮询信息通知(电视墙轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/22  4.0     顾振华    创建
    =============================================================================*/
    u16 ResumeTwPollCmd(const CConfId &cConfId, s8 byTwHduFlag = 0);

    /*=============================================================================
    函 数 名:StopTwPollCmd
    功    能:停止电视墙轮询
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_TWPOLLSTATE_NOTIF     电视墙轮询信息通知(电视墙轮询信息变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/22  4.0     顾振华    创建
    =============================================================================*/
    u16 StopTwPollCmd(const CConfId &cConfId, s8 byTwHduFlag = 0); //0--TW 1--Hdu

    /*=============================================================================
    函 数 名:GetTwPollParamReq
    功    能:获取电视墙轮询参数
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETTWPOLLPARAM_ACK      得到轮循状态成功
             MCS_DISP_GETTWPOLLPARAM_NACK     得到轮循状态失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/22  4.0     顾振华    创建
    =============================================================================*/
    u16 GetTwPollParamReq(const CConfId &cConfId, s8 byTwHduFlag = 0);
    

    /*=============================================================================
    函 数 名:ChgVacHoldTimeReq
    功    能:修改语音激励时间
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byHoldTime                      [in]    新的语音激励最小持续时间
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CHANGEVACHOLDTIME_ACK     修改语音激励成功
             MCS_DISP_CHANGEVACHOLDTIME_NACK    修改语音激励失败
             MCS_DISP_CHANGEVACHOLDTIME_NOTIF   修改语音激励通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 ChgVacHoldTimeReq(const CConfId &cConfId, u8 byHoldTime);

    /*=============================================================================
    函 数 名:GetMtListCmd
    功    能:获取终端列表通知(刷新MCU)
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    刷新哪一个MCU的终端列表
    注    意:发出MCS_MCU_REFRESHMCU_CMD指令
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 GetMtListCmd(const CConfId &cConfId, const TMcu &tMcu);

//-----------------------------------------------------------------------------
//7. 终端操作
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:CallMtReq
    功    能:呼叫终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    呼叫的终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CALLMT_ACK            呼叫终端成功
             MCS_DISP_CALLMT_NACK           呼叫终端失败
             MCS_DISP_MTONLINECHANGE_NOTIF  终端在线状态变化通知(终端上下线时发出)
             MCS_DISP_CONFINFO_NOTIF        会议信息通知(会议信息变化时发出)
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
             MCS_DISP_MTLIST_NOTIF          终端列表通知(终端列表变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
             MCS_DISP_CALLMTFAILURE_NOTIF   呼叫终端失败通知(呼叫终端失败时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 CallMtReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:SetCallModeReq
    功    能:设置终端呼叫方式
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byCallMode                      [in]    终端呼叫模式CONF_CALLMODE_NONE、
                                                                    CONF_CALLMODE_TIMER
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SETMTCALLMODE_ACK     设置终端呼叫方式成功
             MCS_DISP_SETMTCALLMODE_NACK    设置终端呼叫方式失败
             MCS_DISP_MTCALLMODE_NOTIF      终端呼叫方式通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 SetCallModeReq(const CConfId &cConfId, const TMt &tMt, u8 byCallMode);

    /*=============================================================================
    函 数 名:DropMtReq
    功    能:挂断终端
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    挂断的终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_DROPMT_ACK            挂断终端成功
             MCS_DISP_DROPMT_NACK           挂断终端失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
             MCS_DISP_MTONLINECHANGE_NOTIF  终端在线状态变化通知(终端上下线时发出)
             MCS_DISP_CONFINFO_NOTIF        会议信息通知(会议信息变化时发出)
             MCS_DISP_CONFALLMTINFO_NOTIF   所有会议终端信息通知(终端列表变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 DropMtReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:StartMtSeeReq
    功    能:开始终端选看
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMtSrc                  [in]    被选看终端
             const TMt &tMtDst                  [in]    选看终端
             u8 byMode                          [in]    选看模式MODE_BOTH、
                                                                MODE_VIDEO、
                                                                MODE_AUDIO
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTMTSEE_ACK        开始终端选看成功
             MCS_DISP_STARTMTSEE_NACK       开始终端选看失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StartMtSeeReq(const CConfId &cConfId, const TMt &tMtSrc,
                      const TMt &tMtDst, u8 byMode);

    /*=============================================================================
    函 数 名:StopMtSeeReq
    功    能:停止终端选看
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    选看终端
             u8 byMode                          [in]    选看模式MODE_BOTH、
                                                                MODE_VIDEO、
                                                                MODE_AUDIO
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPMTSEE_ACK         停止终端选看成功
             MCS_DISP_STOPMTSEE_NACK        停止终端选看失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/05  4.0     王昊    创建
    =============================================================================*/
    u16 StopMtSeeReq(const CConfId &cConfId, const TMt &tMt, u8 byMode);

    /*=============================================================================
    函 数 名:GetMtAliasReq
    功    能:获取终端别名
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMTALIAS_ACK        获取终端别名成功
             MCS_DISP_GETMTALIAS_NACK       获取终端别名失败
             MCS_DISP_MTALIAS_NOTIF         终端别名通知(不会发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 GetMtAliasReq(const CConfId &cConfId, const TMt &tMt);

    // 高清电视墙音量调节请求   
    u16 SetChannelVolumeReq(const CConfId &cConfId, const THduVolumeInfo &tHduVolumeInfo);
    
    //高清电视墙预案通道批量轮询(REQ)

    //开始批量轮询
    u16 StartHduBatchPollReq(const CConfId &cConfId, const THduPollSchemeInfo &tPollSchemeInfo);

    //停止批量轮询
    u16 StopHduBatchPollReq(const CConfId &cConfId );

    //暂停批量轮询
    u16 PauseHduBatchPollReq(const CConfId &cConfId );

    //继续批量轮询
    u16 ResumeHduBatchPollReq(const CConfId &cConfId );

    /*=============================================================================
    函 数 名:SetMtBitrateCmd
    功    能:设置终端码率
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u16 wBitrate                       [in]    终端码率，单位kbps
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 SetMtBitrateCmd(const CConfId &cConfId, const TMt &tMt, u16 wBitrate);

    /*=============================================================================
    函 数 名:GetMtBitrateReq
    功    能:获取终端码率
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端, 为空则获取所有终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMTBITRATE_ACK      获取终端码率成功
             MCS_DISP_GETMTBITRATE_NACK     获取终端码率失败
             MCS_DISP_MTBITRATE_NOTIF       终端码率通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/11/17  4.0     王昊    创建
    =============================================================================*/
    u16 GetMtBitrateReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:GetMtVersionReq
    功    能:获取终端版本信息等
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端, 为空则获取所有终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCU_MCS_GETMTEXTINFO_ACK      获取终端版本信息成功
             MCU_MCS_GETMTEXTINFO_NACK     获取终端版本信息失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/12/27  4.0     王廖荣    创建
    =============================================================================*/
    u16 GetMtVersionReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:SetMtVideoSrcCmd
    功    能:设置终端视频源
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byPort                          [in]    视频源端口
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 SetMtVideoSrcCmd(const CConfId &cConfId, const TMt &tMt, u8 byPort);

    /*=============================================================================
    函 数 名:MtQuietReq
    功    能:终端静音
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byMtNum                         [in]    终端个数
             const TMt *ptMtList                [in]    终端数组
             BOOL32 bQuiet                      [in]    是否静音
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTAUDMUTE_ACK         终端静音成功
             MCS_DISP_MTAUDMUTE_NACK        终端静音失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 MtQuietReq(const CConfId &cConfId, u8 byMtNum,
                   const TMt *ptMtList, BOOL32 bQuiet = TRUE);

    /*=============================================================================
    函 数 名:MtDumbReq
    功    能:终端哑音
    参    数:const CConfId &cConfId             [in]    会议号
             u8 byMtNum                         [in]    终端个数
             const TMt *ptMtList                [in]    终端数组
             BOOL32 bDumb                       [in]    是否哑音
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTAUDMUTE_ACK         终端哑音成功
             MCS_DISP_MTAUDMUTE_NACK        终端哑音失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 MtDumbReq(const CConfId &cConfId, u8 byMtNum,
                  const TMt *ptMtList, BOOL32 bDumb = TRUE);

    /*=============================================================================
    函 数 名:CameraCtrlStartCmd
    功    能:摄像头控制开始
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byCtrlType                      [in]    控制类型CAMERA_CTRL_UP
                                                                CAMERA_CTRL_DOWN
                                                                CAMERA_CTRL_LEFT
                                                                CAMERA_CTRL_RIGHT
                                                                CAMERA_CTRL_ZOOMIN
                                                                CAMERA_CTRL_ZOOMOUT
                                                                CAMERA_CTRL_FOCUSIN
                                                                CAMERA_CTRL_FOCUSOUT
                                                                CAMERA_CTRL_BRIGHTUP
                                                                CAMERA_CTRL_BRIGHTDOWN
                                                                CAMERA_CTRL_AUTOFOCUS
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 CameraCtrlStartCmd(const CConfId &cConfId, const TMt &tMt, u8 byCtrlType);

    /*=============================================================================
    函 数 名:CameraCtrlStopCmd
    功    能:摄像头控制停止
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byCtrlType                      [in]    控制类型CAMERA_CTRL_UP
                                                                CAMERA_CTRL_DOWN
                                                                CAMERA_CTRL_LEFT
                                                                CAMERA_CTRL_RIGHT
                                                                CAMERA_CTRL_ZOOMIN
                                                                CAMERA_CTRL_ZOOMOUT
                                                                CAMERA_CTRL_FOCUSIN
                                                                CAMERA_CTRL_FOCUSOUT
                                                                CAMERA_CTRL_BRIGHTUP
                                                                CAMERA_CTRL_BRIGHTDOWN
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 CameraCtrlStopCmd(const CConfId &cConfId, const TMt &tMt, u8 byCtrlType);

    /*=============================================================================
    函 数 名:CameraMoveToPosCmd
    功    能:摄像头预置位回调
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byPos                           [in]    预设位置号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 CameraMoveToPosCmd(const CConfId &cConfId, const TMt &tMt, u8 byPos);

    /*=============================================================================
    函 数 名:CameraSaveToPosCmd
    功    能:摄像头预置位保存
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byPos                           [in]    预设位置号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 CameraSaveToPosCmd(const CConfId &cConfId, const TMt &tMt, u8 byPos);

    // 内置矩阵
    /*=============================================================================
    函 数 名:MatrixGetAllScheCmd
    功    能:请求所有矩阵方案
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIX_ALLSCHE_NOTIF      矩阵方案通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/30  4.0     顾振华  创建
    =============================================================================*/
    u16 MatrixGetAllScheCmd(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:MatrixGetOneScheCmd
    功    能:请求单个矩阵方案
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const u8 byIndex                   [in]    索引号 0 - 6
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIX_ONESCHE_NOTIF       矩阵方案通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/30  4.0     顾振华  创建
    =============================================================================*/
    u16 MatrixGetOneScheCmd(const CConfId &cConfId, const TMt &tMt, 
                            const u8 byIndex);

    /*=============================================================================
    函 数 名:MatriSaveScheCmd
    功    能:保存矩阵方案命令
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const ITInnerMatrixScheme &tSche   [in]    矩阵方案
    注    意:发送MCS_MCU_MATRIX_MODIFY_CMD
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIX_ONESCHE_NOTIF       矩阵方案通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/30  4.0     顾振华  创建
    =============================================================================*/
    u16 MatriSaveScheCmd( const CConfId &cConfId, const TMt &tMt,
                          const ITInnerMatrixScheme &tSche);

    /*=============================================================================
    函 数 名:MatrixSetCurScheCmd
    功    能:设置当前矩阵方案
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             u8 byIndex                         [in]    索引号 1-6
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIX_CURSCHE_NOTIF      当前矩阵信息通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/30  4.0     顾振华  创建
    =============================================================================*/
    u16 MatrixSetCurScheCmd(const CConfId &cConfId, const TMt &tMt, u8 byIndex);

    /*=============================================================================
    函 数 名:MatrixGetCurScheCmd
    功    能:获取当前矩阵方案
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIX_CURSCHE_NOTIF      当前矩阵信息通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/30  4.0     顾振华  创建
    =============================================================================*/
    u16 MatrixGetCurScheCmd(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:SetMtVolumeCmd
    功    能:控制终端音量
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const u8 byVolumeTypeIn            [in]    音量类型(VOLUME_TYPE_IN, VOLUME_TYPE_OUT)
             const u8 byVolume                  [in]    调整后的音量
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/12/28  4.0     王廖荣  创建
    =============================================================================*/
    u16 SetMtVolumeCmd(const CConfId &cConfId, const TMt &tMt, const u8 byVolumeTypeIn, const u8 byVolume);

    // 以下是外置矩阵,已经废弃
    /*=============================================================================
    函 数 名:GetMatrixExInfoCmd
    功    能:获取外置矩阵信息
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIXEXINFO_NOTIF   矩阵信息通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华  创建
    =============================================================================
    u16 GetMatrixExInfoCmd(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:SetMatrixExPortCmd
    功    能:设置外置矩阵连接端口号
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const u8  byPort                   [in]    连接端口号(1-64)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华  创建
    =============================================================================
    u16 SetMatrixExPortCmd(const CConfId &cConfId, const TMt &tMt, const u8 byPort);
    
    /*=============================================================================
    函 数 名:GetMatrixExPortReq
    功    能:请求外置矩阵连接端口号
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIXEXGETPORT_ACK       获取外置矩阵端口成功
             MCS_DISP_MATRIXEXGETPORT_NACK      获取外置矩阵端口失败
             MCS_DISP_MATRIXEXGETPORT_NOTIF     外置矩阵端口通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华  创建
    =============================================================================
    u16 GetMatrixExPortReq(const CConfId &cConfId, const TMt &tMt);
    
    /*=============================================================================
    函 数 名:SetMatrixExPortNameCmd
    功    能:设置外置矩阵端口名
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const u8  byPort                   [in]    连接端口号(1-64)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIXEXPORTNAME_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华  创建
    =============================================================================
    u16 SetMatrixExPortNameCmd(const CConfId &cConfId, const TMt &tMt, 
                               const u8 byPort, const s8 aszName[MAXLEN_MATRIXPORTNAME]);
    
    /*=============================================================================
    函 数 名:GetMatrixExAllPortNameCmd
    功    能:获取外置矩阵所有端口名
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MATRIXEXGETALLPORTNAME_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华  创建
    =============================================================================
    u16 GetMatrixExAllPortNameCmd(const CConfId &cConfId, const TMt &tMt);
    */

    // 扩展视频源
    /*=============================================================================
    函 数 名:GetMatrixExAllPortNameCmd
    功    能:获取扩展视频源所有端口名
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_VIDEOEXALLINFO_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/09  4.0     顾振华  创建
    =============================================================================*/
    u16 VideoExGetAllInfoCmd(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:ViedeoExSetInfoCmd
    功    能:设置扩展视频源端口名
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const ITVideoSourceInfo tInfo      [in]    连接端口
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_VIDEOEXINFO_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/09  4.0     顾振华  创建
    =============================================================================*/
    u16 ViedeoExSetInfoCmd(const CConfId &cConfId, const TMt &tMt, 
                           const ITVideoSourceInfo& tInfo);
    
    /*=============================================================================
    函 数 名:ViedeoExSelectSrcCmd
    功    能:选择扩展视频源输入端口
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             const u8  byPort                   [in]    连接端口号(10-73)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_VIDEOEXINFO_NOTIF
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/09  4.0     顾振华  创建
    =============================================================================*/
    u16 ViedeoExSelectSrcCmd(const CConfId &cConfId, const TMt &tMt, 
                             const u8 byPort);

    /*=============================================================================
    函 数 名:LockSMcuReq
    功    能:锁定下级MCU
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    锁定的MCU, 空则锁定所有
             BOOL32 bLock                       [in]    锁定/解锁
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_LOCKSMCU_ACK          锁定下级MCU成功
             MCS_DISP_LOCKSMCU_NACK         锁定下级MCU失败
             MCS_DISP_MCULOCKSTATUS_NOTIF   下级MCU锁定状态通知(锁定状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 LockSMcuReq(const CConfId &cConfId, const TMcu &tMcu, BOOL32 bLock);

//-----------------------------------------------------------------------------
//8. 外设操作
//-----------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    //8.1 录像

    /*=============================================================================
    函 数 名:StartRecReq
    功    能:开始录像
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端(IsNull表示会议录像)
             const TEqp &tEqp                   [in]    录像机
             const TRecStartPara &tRecParam     [in]    录像参数
             LPCTSTR pszFileName                [in]    录像文件名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTREC_ACK          开始录像成功
             MCS_DISP_STARTREC_NACK         开始录像失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_RECPROG_NOTIF         录像进度通知(录像时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartRecReq(const CConfId &cConfId, const TMt &tMt, const TEqp &tEqp,
		            const TRecStartPara &tRecParam, LPCTSTR pszFileName);

    /*=============================================================================
    函 数 名:PauseRecReq
    功    能:暂停录像
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端(IsNull表示会议录像)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_PAUSEREC_ACK          暂停录像成功
             MCS_DISP_PAUSEREC_NACK         暂停录像失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 PauseRecReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:ResumeRecReq
    功    能:恢复录像
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端(IsNull表示会议录像)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_RESUMEREC_ACK         恢复录像成功
             MCS_DISP_RESUMEREC_NACK        恢复录像失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_RECPROG_NOTIF         录像进度通知(录像时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 ResumeRecReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:StopRecReq
    功    能:停止录像
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端(IsNull表示会议录像)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPREC_ACK       停止录像成功
             MCS_DISP_STOPREC_NACK      停止录像失败
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopRecReq(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:GetRecProgCmd
    功    能:请求当前录像进度
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端(IsNull表示会议录像)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_RECPROG_NOTIF             录像进度通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/11  4.0     顾振华  创建
    =============================================================================*/
    u16 GetRecProgCmd(const CConfId &cConfId, const TMt &tMt);

    /*=============================================================================
    函 数 名:StartPlayReq
    功    能:开始放像
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    录像机
             BOOL32 bPlayDoubleBitrate          [in]    是否双流放像
             LPCTSTR pszFileName                [in]    录像文件名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTPLAY_ACK     开始放像成功
             MCS_DISP_STARTPLAY_NACK    开始放像失败
             MCS_DISP_CONFINFO_NOTIF    会议信息通知(会议信息变化时发出)
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_CONFMODE_NOTIF    会议模式通知(会议模式变化时发出)
             MCS_DISP_PLAYPROG_NOTIF    放像进度通知(放像时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartPlayReq(const CConfId &cConfId, const TEqp &tEqp,
                     BOOL32 bPlayDoubleBitrate, LPCTSTR pszFileName);

    /*=============================================================================
    函 数 名:PausePlayReq
    功    能:暂停放像
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    录像机
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_PAUSEPLAY_ACK     暂停放像成功
             MCS_DISP_PAUSEPLAY_NACK    暂停放像失败
             MCS_DISP_CONFMODE_NOTIF    会议模式通知(会议模式变化时发出)
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 PausePlayReq(const CConfId &cConfId, const TEqp &tEqp);

    /*=============================================================================
    函 数 名:ResumePlayReq
    功    能:恢复放像
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    录像机
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_RESUMEPLAY_ACK    恢复放像成功
             MCS_DISP_RESUMEPLAY_NACK   恢复放像失败
             MCS_DISP_CONFMODE_NOTIF    会议模式通知(会议模式变化时发出)
             MCS_DISP_PLAYPROG_NOTIF    放像进度通知(放像时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 ResumePlayReq(const CConfId &cConfId, const TEqp &tEqp);

    /*=============================================================================
    函 数 名:StopPlayReq
    功    能:停止放像
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    录像机
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPPLAY_ACK      停止放像成功
             MCS_DISP_STOPPLAY_NACK     停止放像失败
             MCS_DISP_CONFMODE_NOTIF    会议模式通知(会议模式变化时发出)
             MCS_DISP_CONFINFO_NOTIF    会议信息通知(会议信息变化时发出)
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopPlayReq(const CConfId &cConfId, const TEqp &tEqp);

    /*=============================================================================
    函 数 名:SeekPlayReq
    功    能:放像进度调节
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    录像机
             const TRecProg &tRecProg           [in]    放像进度
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SEEKPLAY_ACK          放像进度调节成功
             MCS_DISP_SEEKPLAY_NACK         放像进度调节失败
             MCS_DISP_PLAYPROG_NOTIF        放像进度通知(放像时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 SeekPlayReq(const CConfId &cConfId, const TEqp &tEqp,
                    const TRecProg &tRecProg);

    /*=============================================================================
    函 数 名:GetPlayProgCmd
    功    能:请求当前放像进度
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCU_MCS_PLAYPROG_NOTIF             录像进度通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/11  4.0     顾振华  创建
    =============================================================================*/
    u16 GetPlayProgCmd(const CConfId &cConfId);


    /*=============================================================================
    函 数 名:GetAllRecFileCmd
    功    能:列出录像机所有文件
    参    数:const TEqp &tEqp                   [in]    录像机
             const CConfId *pcConfId = NULL     [in]    会议号(空指针代表取所有文件)
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETRECFILELIST_ACK    列出录像机所有文件成功
             MCS_DISP_GETRECFILELIST_NACK   列出录像机所有文件失败
             MCS_DISP_RECFILELIST_NOTIF     录像文件列表通知 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    2005/08/19  4.0     王昊    改造成cmd接口
    =============================================================================*/
    u16 GetAllRecFileCmd(const TEqp &tEqp, const CConfId *pcConfId = NULL);

    /*=============================================================================
    函 数 名:DeleteRecFileReq
    功    能:删除录像文件
    参    数:const TEqp &tEqp                   [in]    录像机
             LPCTSTR pszFileName                [in]    录像文件名(pszConfName为空时不带路径)
             LPCTSTR pszConfName = NULL         [in]    会议名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_DELRECFILE_ACK      删除录像文件成功
             MCS_DISP_DELRECFILE_NACK     删除录像文件失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 DeleteRecFileReq(const TEqp &tEqp, LPCTSTR pszFileName,
                         LPCTSTR pszConfName = NULL);

    /*=============================================================================
    函 数 名:PublishRecFileReq
    功    能:发布录像文件
    参    数:const TEqp &tEqp                   [in]    录像机
             LPCTSTR pszFileName                [in]    录像文件名(pszConfName为空时不带路径)
             u8 byPublishLevel                  [in]    发布级别(PUBLISH_LEVEL_NORMAL、PUBLISH_LEVEL_SECRET)
             LPCTSTR pszConfName = NULL         [in]    会议名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_PUBLISHRECFILE_ACK    发布录像文件成功
             MCS_DISP_PUBLISHRECFILE_NACK   发布录像文件失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 PublishRecFileReq(const TEqp &tEqp, LPCTSTR pszFileName, u8 byPublishLevel,
                          LPCTSTR pszConfName = NULL);

    /*=============================================================================
    函 数 名:CancelRecFilePublishReq
    功    能:取消录像文件发布
    参    数:const TEqp &tEqp                   [in]    录像机
             LPCTSTR pszFileName                [in]    录像文件名(pszConfName为空时不带路径)
             LPCTSTR pszConfName = NULL         [in]    会议名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CANCELRECFILEPUBLISH_ACK      取消录像文件发布成功
             MCS_DISP_CANCELRECFILEPUBLISH_NACK     取消录像文件发布失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 CancelRecFilePublishReq(const TEqp &tEqp, LPCTSTR pszFileName,
                                LPCTSTR pszConfName = NULL);

    /*=============================================================================
    函 数 名:ModifyRecFileReq
    功    能:修改录像文件名
    参    数:const TEqp &tEqp                   [in]    录像机
             LPCTSTR pszOldName                 [in]    录像文件原名(pszConfName为空时不带路径)
             LPCTSTR pszNewName                 [in]    录像文件修改名(pszConfName为空时不带路径)
             LPCTSTR pszConfName = NULL         [in]    会议名
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYRECFILE_ACK     修改录像文件名成功
             MCS_DISP_MODIFYRECFILE_NACK    修改录像文件名失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/09/27  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyRecFileReq(const TEqp &tEqp, LPCTSTR pszOldName, LPCTSTR pszNewName,
                         LPCTSTR pszConfName = NULL);

    //-----------------------------------------------------------------------------
    //8.2 混音

    /*=============================================================================
    函 数 名:StartEntireMixReq
    功    能:开始本级智能混音
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTMIX_ACK          开始混音成功
             MCS_DISP_STARTMIX_NACK         开始混音失败
             MCS_DISP_STARTMIX_NOTIF        开始混音通知
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF        混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartEntireMixReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:StartPartMixReq
    功    能:开始本级部分混音
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt *ptMtTable               [in]    终端数组
             u8 byMtNum                         [in]    终端个数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTMIX_ACK      开始混音成功
             MCS_DISP_STARTMIX_NACK     开始混音失败
             MCS_DISP_STARTMIX_NOTIF    开始混音通知
             MCS_DISP_CONFSTATUS_NOTIF  会议状态通知(会议状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
//    u16 StartPartMixReq(const CConfId &cConfId, const TMt *ptMtTable, u8 byMtNum);

    /*=============================================================================
    函 数 名:StopMixReq
    功    能:停止本级混音(智能/部分)
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPMIX_ACK       停止混音成功
             MCS_DISP_STOPMIX_NACK      停止混音失败
             MCS_DISP_STOPMIX_NOTIF     停止混音通知
             MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF  会议状态通知(会议状态变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopMixReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:AddMixMemberCmd
    功    能:增加部分混音成员
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt *pTMt                    [in]    终端列表
             const u32 nMtNum                   [in]    终端数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddMixMemberCmd(const CConfId &cConfId, const TMt *pTMt, const u32 nMtNum);

    /*=============================================================================
    函 数 名:RemoveMixMemberCmd
    功    能:删除部分混音成员
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt *pTMt                    [in]    终端数组
             const u32 nMtNum                   [in]    终端个数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 RemoveMixMemberCmd(const CConfId &cConfId, const TMt *pTMt, const u32 nMtNum);

    /*=============================================================================
    函 数 名:ReplaceMixMemberCmd
    功    能:替换混音成员
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt *pTMtOld                 [in]    被替换终端
             const TMt *pTMtNew                 [in]    替换终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/11/21  4.0     王廖荣    创建
    =============================================================================*/
    u16 ReplaceMixMemberCmd(const CConfId &cConfId, const TMt *pTMtOld, const TMt *pTMtNew);

    /*=============================================================================
    函 数 名:StartSMcuMixCmd
    功    能:开始下级混音(智能/部分)
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    指定MCU
             const TMt *ptMtTable               [in]    终端数组
             u8 byMtNum                         [in]    终端个数
    注    意:ptMtTable为空则开启智能混音
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
//    u16 StartSMcuMixCmd(const CConfId &cConfId, const TMcu &tMcu,
//                        const TMt *ptMtTable, u8 byMtNum);

    /*=============================================================================
    函 数 名:StopSMcuMixCmd
    功    能:停止下级混音(智能/部分)
    参    数:const CConfId &cConfId             [in]    会议号
             const TMcu &tMcu                   [in]    指定MCU
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MTSTATUS_NOTIF    终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MIXPARAM_NOTIF    混音参数通知(混音参数变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
//    u16 StopSMcuMixCmd(const CConfId &cConfId, const TMcu &tMcu);

    /*=============================================================================
    函 数 名:ModifyMixDelayTimeReq
    功    能:修改混音延时时间
    参    数:const CConfId &cConfId             [in]    会议号
             u16 wDelayTime                     [in]    延时时间(毫秒)
    注    意:对部分和全体混音均有效
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYMIXDELAY_ACK    修改混音延时时间成功
             MCS_DISP_MODIFYMIXDELAY_NACK   修改混音延时时间失败
             MCS_DISP_MIXDELAY_NOTIF        混音延时时间通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/07  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyMixDelayTimeReq(const CConfId &cConfId, u16 wDelayTime);

    /*=============================================================================
    函 数 名:StartVacReq
    功    能:开始语音激励
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTVAC_ACK          开始语音激励成功
             MCS_DISP_STARTVAC_NACK         开始语音激励失败
             MCS_DISP_STARTVAC_NOTIF        开始语音激励通知
             MCS_DISP_CONFMODE_NOTIF        会议模式通知(会议模式变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartVacReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:StopVacReq
    功    能:停止语音激励
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPVAC_ACK           停止语音激励成功
             MCS_DISP_STOPVAC_NACK          停止语音激励失败
             MCS_DISP_STOPVAC_NOTIF         停止语音激励通知(不会发出)
             MCS_DISP_CONFMODE_NOTIF        会议模式通知(会议模式变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopVacReq(const CConfId &cConfId);

    //-----------------------------------------------------------------------------
    //8.3 画面合成

    /*=============================================================================
    函 数 名:StartVmpReq
    功    能:开始画面合成
    参    数:const CConfId &cConfId             [in]    会议号
             const TVMPParam &tVmpParam         [in]    画面合成参数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTVMP_ACK          开始画面合成成功
             MCS_DISP_STARTVMP_NACK         开始画面合成失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_VMPPARAM_NOTIF        画面合成参数通知(画面合成参数变化时发出, 不用处理)
             MCS_DISP_STARTVMP_NOTIF        开始画面合成通知
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartVmpReq(const CConfId &cConfId, const TVMPParam &tVmpParam);

    /*=============================================================================
    函 数 名:StopVmpReq
    功    能:停止画面合成
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPVMP_ACK           停止画面合成成功
             MCS_DISP_STOPVMP_NACK          停止画面合成失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_STOPVMP_NOTIF         停止画面合成通知
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopVmpReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:ChgVmpParamReq
    功    能:修改画面合成参数
    参    数:const CConfId &cConfId             [in]    会议号
             const TVMPParam &tVmpParam         [in]    画面合成参数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CHANGEVMPPARAM_ACK    修改画面合成参数成功
             MCS_DISP_CHANGEVMPPARAM_NACK   修改画面合成参数失败
             MCS_DISP_CONFSTATUS_NOTIF      会议状态通知(会议状态变化时发出)
             MCS_DISP_VMPPARAM_NOTIF        画面合成参数通知(画面合成参数变化时发出, 不用处理)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 ChgVmpParamReq(const CConfId &cConfId, const TVMPParam &tVmpParam);

    /*=============================================================================
    函 数 名:StartVmpBrdstReq
    功    能:开始画面合成广播
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTVMPBRDST_ACK     开始画面合成广播成功
             MCS_DISP_STARTVMPBRDST_NACK    开始画面合成广播失败
             MCS_DISP_VMPPARAM_NOTIF        画面合成通知(画面合成状态变化时发出)
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartVmpBrdstReq(const CConfId &cConfId);

    /*=============================================================================
    函 数 名:StopVmpBrdstReq
    功    能:停止画面合成广播
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTVMPBRDST_ACK     停止画面合成广播成功
             MCS_DISP_STARTVMPBRDST_NACK    停止画面合成广播失败
             MCS_DISP_MTSTATUS_NOTIF        终端状态通知(终端状态发生变化时发出)
             MCS_DISP_VMPPARAM_NOTIF        画面合成通知(画面合成状态变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopVmpBrdstReq(const CConfId &cConfId);

    //-----------------------------------------------------------------------------
    //8.4 电视墙

    /*=============================================================================
    函 数 名:StartTvWallReq
    功    能:开始电视墙
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    电视墙
             const TTWMember &tMember           [in]    电视墙成员
             u8 byIndex                         [in]    通道号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTTVWALL_ACK           开始电视墙成功
             MCS_DISP_STARTTVWALL_NACK          开始电视墙失败
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StartTvWallReq(const CConfId &cConfId, const TEqp &tEqp,
                       const TTWMember &tMember, u8 byIndex);
    //高清电视墙
    u16 StartHDTvWallReq(const CConfId &cConfId, const TEqp &tEqp,
                       const TTWMember &tMember, u8 byIndex, u8 byCurSelHduStyleID);


    /*=============================================================================
    函 数 名:StopTvWallReq
    功    能:停止电视墙
    参    数:const CConfId &cConfId             [in]    会议号
             const TEqp &tEqp                   [in]    电视墙
             u8 byIndex                         [in]    通道号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPTVWALL_ACK            停止电视墙成功
             MCS_DISP_STOPTVWALL_NACK           停止电视墙失败
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 StopTvWallReq(const CConfId &cConfId, const TEqp &tEqp, u8 byIndex);
    
    //高清电视墙
    u16 StopHDUTvWallReq(const CConfId &cConfId, const TEqp &tEqp, u8 byIndex);

    /*=============================================================================
    函 数 名:StartMultiTvWallReq
    功    能:开始多画面电视墙
    参    数:const CConfId &cConfId             [in]    会议号
             const TVMPParam &tTwParam          [in]    多画面电视墙参数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STARTMULTITVWALL_ACK      开始多画面电视墙成功
             MCS_DISP_STARTMULTITVWALL_NACK     开始多画面电视墙失败
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态发生变化时发出)
             MCS_DISP_MULTITVWALLPARAM_NOTIF    多画面电视墙参数通知(多画面电视墙参数变化时发出, 不用处理)
             MCS_DISP_STARTMULTITVWALL_NOTIF    开始多画面电视墙通知
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/13  4.0     王昊    创建
    =============================================================================*/
    u16 StartMultiTvWallReq(const CConfId &cConfId, const TVMPParam &tTwParam);

    /*=============================================================================
    函 数 名:ChgMultiTvWallParamReq
    功    能:修改多画面电视墙参数
    参    数:const CConfId &cConfId             [in]    会议号
             const TVMPParam &tTwParam          [in]    多画面电视墙参数
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_CHANGEMULTITVWALLPARAM_ACK    开始多画面电视墙成功
             MCS_DISP_CHANGEMULTITVWALLPARAM_NACK   开始多画面电视墙失败
             MCS_DISP_MULTITVWALLPARAM_NOTIF        多画面电视墙参数通知(多画面电视墙参数变化时发出, 不用处理)
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF        外设状态通知(外设状态发生变化时发出)
             MCS_DISP_MTSTATUS_NOTIF                终端状态通知(终端状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/13  4.0     王昊    创建
    =============================================================================*/
    u16 ChgMultiTvWallParamReq(const CConfId &cConfId, const TVMPParam &tTwParam);

    /*=============================================================================
    函 数 名:StopMultiTvWallReq
    功    能:停止多画面电视墙
    参    数:const CConfId &cConfId             [in]    会议号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_STOPMULTITVWALL_ACK       停止多画面电视墙成功
             MCS_DISP_STOPMULTITVWALL_NACK      停止多画面电视墙失败
             MCS_DISP_MTSTATUS_NOTIF            终端状态通知(终端状态发生变化时发出)
             MCS_DISP_STOPMULTITVWALL_NOTIF     停止多画面电视墙通知
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/13  4.0     王昊    创建
    =============================================================================*/
    u16 StopMultiTvWallReq(const CConfId &cConfId);

    //-----------------------------------------------------------------------------
    //8.5 外设状态

    /*=============================================================================
    函 数 名:GetPeriEqpReq
    功    能:获取外设状态
    参    数:const TEqp &tEqp                   [in]    外设
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_GETMCUPERIEQPSTATUS_ACK   获取外设状态成功
             MCS_DISP_GETMCUPERIEQPSTATUS_NACK  获取外设状态失败
             MCS_DISP_MCUPERIEQPSTATUS_NOTIF    外设状态通知(外设状态发生变化时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 GetPeriEqpReq(const TEqp &tEqp);

//-----------------------------------------------------------------------------
//9. 用户操作
//-----------------------------------------------------------------------------
// lrf [6/22/2006]

    /*函数名： AddUserGroupReq
    功    能： 增加用户组请求
    参    数： const TUsrGrpInfo& tUserGrpInfo [in]用户组信息
    返 回 值： u16 成功为MCSLIB_OK, 失败参见错误码
    说    明： */
	u16 AddUserGroupReq(const TUsrGrpInfo& tUserGrpInfo);

    /*函数名： DelUserGroupReq
    功    能： 删除用户组请求
    参    数： u8 byGroupId [in]用户ID
    返 回 值： u16 成功为MCSLIB_OK, 失败参见错误码
    说    明： */
	u16 DelUserGroupReq(u8 byGroupId);

    /*函数名： ModifyUserGroupReq
    功    能： 修改用户组信息
    参    数： const TUsrGrpInfo& tUserGrpInfo
    返 回 值： u16 成功为MCSLIB_OK, 失败参见错误码
    说    明： */
	u16 ModifyUserGroupReq(const TUsrGrpInfo& tUserGrpInfo);


    /*=============================================================================
    函 数 名:AddUserReq
    功    能:添加用户
    参    数:const CExUsrInfo &cUserFullInfo [in]    用户信息结构
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDUSER_ACK       添加用户成功
             MCS_DISP_ADDUSER_NACK      添加用户失败
             MCS_DISP_ADDUSER_NOTIF     添加用户通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddUserReq(const CExUsrInfo &cUserFullInfo);
    u16 AddUserReq(const CVCSUsrInfo &cVcsUserFullInfo);

    /*=============================================================================
    函 数 名:DelUserReq
    功    能:删除用户
    参    数:const CUserFullInfo &cUserFullInfo [in]    用户信息结构
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_DELUSER_ACK       删除用户成功
             MCS_DISP_DELUSER_NACK      删除用户失败
             MCS_DISP_DELUSER_NOTIF     删除用户通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 DelUserReq(const CExUsrInfo &cUserFullInfo);
    u16 DelUserReq(const CVCSUsrInfo &cVcsUserFullInfo);

    /*=============================================================================
    函 数 名:ModifyUserReq
    功    能:修改用户
    参    数:const CUserFullInfo &cUserFullInfo [in]    用户信息结构
    注    意:可以去掉
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MODIFYUSER_ACK   修改用户成功
             MCS_DISP_MODIFYUSER_NACK  修改用户失败
             MCS_DISP_MODIFYUSER_NOTIF 修改用户通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 ModifyUserReq(const CExUsrInfo &cUserFullInfo);
    u16 ModifyUserReq(const CVCSUsrInfo &cVcsUserFullInfo);

//-----------------------------------------------------------------------------
//10. 地址簿操作
//-----------------------------------------------------------------------------
	// 本部分操作2006.02.16起使用MCU的结构和接口，不再使用协议组的CAddrBook和相应结构

    /*=============================================================================
    函 数 名:UnregAddrBookReq
    功    能:注销地址簿
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
//     u16 UnregAddrBookReq(void);

    /*=============================================================================
    函 数 名:UnregAddrBookCmd
    功    能:注销地址簿(命令型，在MCS退出时调用)
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/12  4.0     顾振华  创建
    =============================================================================*/
//     u16 UnregAddrBookCmd(void);

    /*=============================================================================
    函 数 名:AddrAddEntryReq
    功    能:增加地址簿条目
    参    数:const TMcuAddrEntry &tAddrEntry       [in]    地址簿条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
             MCS_DISP_ADDRBOOK_ADDENTRY_ACK     增加地址簿条目成功
             MCS_DISP_ADDRBOOK_ADDENTRY_NACK    增加地址簿条目失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrAddEntryReq(const TMcuAddrEntry &tAddrEntry);

    /*=============================================================================
    函 数 名:AddrDelEntryReq
    功    能:删除地址簿条目
    参    数:u32 dwIndex                        [in]    地址簿条目索引号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_DELENTRY_ACK     删除地址簿条目成功
             MCS_DISP_ADDRBOOK_DELENTRY_NACK    删除地址簿条目失败
             MCS_DISP_ADDRBOOK_DELENTRY_NOTIF   删除地址簿条目通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrDelEntryReq(u32 dwIndex);

    /*=============================================================================
    函 数 名:AddrModifyEntryReq
    功    能:修改地址簿条目
    参    数:const TMcuAddrEntry &tAddrEntry       [in]    地址簿条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_REFRESHENTRY_NOTIF   地址簿条目通知(地址簿条目变化时发出)
             MCS_DISP_ADDRBOOK_MODIFYENTRY_ACK      修改地址簿条目成功
             MCS_DISP_ADDRBOOK_MODIFYENTRY_NACK     修改地址簿条目失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrModifyEntryReq(const TMcuAddrEntry &tAddrEntry);

    /*=============================================================================
    函 数 名:AddrAddGroupReq
    功    能:增加地址簿会议组
    参    数:const TMcuAddrGroup &tAddrGroup   [in]    会议组条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_REFRESHGROUP_NOTIF   地址簿会议组通知(地址簿会议组变化时发出)
             MCS_DISP_ADDRBOOK_ADDGROUP_ACK         增加地址簿会议组成功
             MCS_DISP_ADDRBOOK_ADDGROUP_NACK        增加地址簿会议组失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrAddGroupReq(const TMcuAddrGroup &tAddrGroup);

    /*=============================================================================
    函 数 名:AddrDelGroupReq
    功    能:删除地址簿会议组
    参    数:u32 dwIndex                        [in]    地址簿会议组条目索引号
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_DELGROUP_ACK     删除地址簿会议组成功
             MCS_DISP_ADDRBOOK_DELGROUP_NACK    删除地址簿会议组失败
             MCS_DISP_ADDRBOOK_DELGROUP_NOTIF   删除地址簿会议组通知(删除地址簿会议组成功时发出)
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrDelGroupReq(u32 dwIndex);

    /*=============================================================================
    函 数 名:AddrModifyGroupReq
    功    能:修改地址簿会议组
    参    数:const TMcuAddrGroup &tAddrGroup   [in]    地址簿会议组条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_REFRESHGROUP_NOTIF   地址簿会议组通知(地址簿会议组变化时发出)
             MCS_DISP_ADDRBOOK_MODIFYGROUP_ACK      修改地址簿会议组成功
             MCS_DISP_ADDRBOOK_MODIFYGROUP_NACK     修改地址簿会议组失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrModifyGroupReq(const TMcuAddrGroup &tAddrGroup);

    /*=============================================================================
    函 数 名:AddrAddGroupEntryReq
    功    能:向地址簿会议组增加条目
    参    数:const TMcuAddrGroup &tAddrGroup   [in]    地址簿会议组条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_REFRESHGROUP_NOTIF   地址簿会议组通知(地址簿会议组变化时发出)
             MCS_DISP_ADDRBOOK_ADDENTRYTOGROUP_ACK  向地址簿会议组增加条目成功
             MCS_DISP_ADDRBOOK_ADDENTRYTOGROUP_NACK 向地址簿会议组增加条目失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrAddGroupEntryReq(const TMcuAddrGroup &tAddrGroup);

    /*=============================================================================
    函 数 名:AddrDelGroupEntryReq
    功    能:从地址簿会议组删除条目
    参    数:const TMcuAddrGroup &tAddrGroup   [in]    地址簿会议组条目
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_ADDRBOOK_REFRESHGROUP_NOTIF   地址簿会议组通知(地址簿会议组变化时发出)
             MCS_DISP_ADDRBOOK_DELENTRYFROMGROUP_ACK    从地址簿会议组删除条目成功
             MCS_DISP_ADDRBOOK_DELENTRYFROMGROUP_NACK   从地址簿会议组删除条目失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    u16 AddrDelGroupEntryReq(const TMcuAddrGroup &tAddrGroup);

    /*=============================================================================
    函 数 名:SpecOutViewReq
    功    能:会议控制台指定本会场向上级回传的终端
    参    数:const CConfId &cConfId [in] 
             const TMt &tMt         [in]    指定本会场向上级回传的终端
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_SPECOUTVIEW_ACK    指定本会场向上级回传的终端成功
             MCS_DISP_SPECOUTVIEW_NACK   指定本会场向上级回传的终端失败
    -------------------------------------------------------------------------------
    修改纪录:MCU_MCS_SPECOUTVIEW_ACK
    日      期  版本    修改人  修改内容
    2007/05/09  4.0     王廖荣    创建
    =============================================================================*/
    u16 SpecOutViewReq(const CConfId &cConfId, const TMt &tMt);

//-----------------------------------------------------------------------------
//  别名读取
//-----------------------------------------------------------------------------

    /*=============================================================================
    函 数 名:GetMtAliasFromAddrBook
    功    能:从CMt结构中得终端别名，如果得不到则从地址簿中查找
    参    数:const CMt &cMt                         [in]    要查询的CMt对象
             CString &cstrAlias                     [out]   返回的终端别名
    注    意:无
    返 回 值:返回的别名的类型
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/11  4.0     王昊    创建
    =============================================================================*/
    u8 GetMtAliasFromAddrBook(const CMt &cMt, CString &cstrAlias);

    /*=============================================================================
    函 数 名:GetMtAliasFromAddrBook
    功    能:从CMt结构中得终端别名，如果得不到则从地址簿中查找
    参    数:const CMt &cMt                         [in]    要查询的CMt对象
    注    意:无
    返 回 值:终端别名的结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/11  4.0     王昊    创建
    =============================================================================*/
    TMtAlias GetMtAliasFromAddrBook(const CMt &cMt);

//public:
    /*=============================================================================
    函 数 名:UnitTestConnectMcu
    功    能:单元测试连接MCU
    参    数:LPCTSTR pszMcuIP                   [in]    连接MCU的IP地址字符串
             u16 wMcuListenPort                 [in]    MCU侦听端口
    注    意:为mcslib单元测试提供
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/08  4.0     王昊    创建
    =============================================================================*/
    void UnitTestConnectMcu(LPCTSTR pszMcuIP, u16 wMcuListenPort);

    /*=============================================================================
    函 数 名:OnDealMsg
    功    能:消息处理
    参    数:CMessage * const pMsg              [in]    回复消息
             CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    void OnDealMsg(CMessage * const pcMsg, CMsgHandler *pHandler);

    /*=============================================================================
    函 数 名:SetMtHasShow
    功    能:设定某一终端是否显示过无法呼叫的错误信息
    参    数:const CConfId &cConfId             [in]    会议号
             const TMt &tMt                     [in]    终端
             BOOL32 bHasShow                    [in]    是否显示过
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/10/11  4.0     王昊    创建
    =============================================================================*/
    void SetMtHasShow(const CConfId &cConfId, const TMt &tMt, BOOL32 bHasShow);

    /*=============================================================================
    函 数 名:IsBakMcuWork
    功    能:是否是备份MCU在工作
    参    数:
    注    意:无
    返 回 值:BOOL32
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/28  4.0     顾振华    创建
    =============================================================================*/
//    BOOL32 IsBakMcuWork()
//    {
//        // 已经废弃
//        return FALSE; 
//    }

    /*=============================================================================
    函 数 名:PrintInfo
    功    能:打印Session有关的信息
    参    数:
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/3/2    4.0     顾振华    创建
    =============================================================================*/
    void PrintInfo();
    
private:
    /*=============================================================================
    函 数 名:GetMcuCpuUsageCmd
    功    能:获取MCU的CPU使用率
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MCUCPUUSAGE_NOTIF     CPU使用率通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/30  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuCpuUsageCmd(void);

    /*=============================================================================
    函 数 名:GetMcuStatusCmd
    功    能:获取TMcuStatus
    参    数:无
    注    意:无
    返 回 值:成功为MCSLIB_OK, 失败参见错误码
    相关消息:MCS_DISP_MCUSTATUS_NOTIF       MCU状态通知
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/30  4.0     王昊    创建
    =============================================================================*/
    u16 GetMcuStatusCmd(void);

    /*=============================================================================
    函 数 名:GetMtTmpAlias
    功    能:得到终端的别名,如得不到，则从地址簿中得
    参    数:const CMt &cMt                         [in]    要得别名的终端
             TMtAlias &tMtAlias                     [out]   查到的别名
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/11  4.0     王昊    创建
    =============================================================================*/
    void GetMtTmpAlias(const CMt &cMt, TMtAlias &tMtAlias) const;

    /*=============================================================================
    函 数 名:ReadAliasFromAddrbook
    功    能:从地址簿中读出终端别名
    参    数:const CMt &cMt                         [in]    要查询的CMt对象
             u32 &dwIP                              [in]    终端的IP
             TMtAlias &tMtAlias                     [out]   终端的别名
    注    意:无
    返 回 值:终端别名的结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/12  4.0     王昊    创建
    2007/01/26  4.0     王廖荣  修改
    =============================================================================*/
    BOOL32 ReadAliasFromAddrbook(const CMt &cMt, u32 &dwIP,
                                 TMtAlias &tMtAlias) const;

    /*=============================================================================
    函 数 名:ReadAliasFromAddrbook
    功    能:从地址簿中读出终端别名
    参    数:const CMt &cMt                         [in]    要查询的CMt对象
             CString &cstrE164                      [in]    终端的E164号码
             TMtAlias &tMtAlias                     [out]   终端的别名
    注    意:无
    返 回 值:终端别名的结构
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/01/26  4.0     王廖荣    创建
    =============================================================================*/
    BOOL32 ReadAliasFromAddrbook(const CMt &cMt, CString &cstrE164,
                                 TMtAlias &tMtAlias) const;

//private:
    /*=============================================================================
    函 数 名:OnIdle
    功    能:处理IDLE状态下相关消息处理
    参    数:CMessage * const pMsg              [in]    回复消息
             CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    void OnIdle(CMessage * const pcMsg, CMsgHandler *pHandler);

    /*=============================================================================
    函 数 名:OnNormal
    功    能:正常状态下的消息处理, 分类并将结果发送给上层
    参    数:CMessage * const pMsg              [in]    回复消息
             CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/02  4.0     王昊    创建
    =============================================================================*/
    void OnNormal(CMessage * const pcMsg, CMsgHandler *pHandler);

//protected:
    /*=============================================================================
    函 数 名:IsSerialNoTrue
    功    能:ACK消息返回的序列号是否正确
    参    数:const CServMsg *pcMsg              [in]    返回的ACK消息
    注    意:无
    返 回 值:bool
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    bool IsSerialNoTrue(const CServMsg *pcMsg) const;

    /*=============================================================================
    函 数 名:NotifUI
    功    能:向界面发送消息
    参    数:u32 dwMsg                          [in]    消息号
             TMcsParam &tParam                  [in]    消息体
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    BOOL32 NotifUI(u32 dwMsg, TMcsParam &tParam);

    /*=============================================================================
    函 数 名:PostMsgToMcu
    功    能:向MCU发送消息
    参    数:CMsgHeadInfo &cMsgHeadInfo         [in]    消息头
             u8 * const pcMsg                   [in]    消息体
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    BOOL32 PostMsgToMcu(CMsgHeadInfo &cMsgHeadInfo, u8 * const pcMsg = NULL);

    /*=============================================================================
    函 数 名:PostMsgToAddrBook
    功    能:向地址簿发送消息
    参    数:CMsgHeadInfo &cMsgHeadInfo         [in]    消息头
             u8 * const pcMsg                   [in]    消息体
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/20  4.0     王昊    创建
    =============================================================================*/
    BOOL32 PostMsgToAddrBook(CMsgHeadInfo &cMsgHeadInfo, u8 * const pcMsg = NULL);

    /*=============================================================================
    函 数 名:CheckMsgLen
    功    能:检查MCU返回消息长度
    参    数:const CServMsg &cServMsg           [in]    返回消息
             s32 nMaxLen                        [in]    最大长度
             s32 nMinLen                        [in]    最小长度
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/21  4.0     王昊    创建
    =============================================================================*/
    BOOL32 CheckMsgLen(const CServMsg &cServMsg, s32 nMaxLen = BUF_SIZE_TO_UI,
                       s32 nMinLen = 0);

//protected:
    /*=============================================================================
    函 数 名:UpdateUserTable
    功    能:更新用户列表
    参    数:const CMessage *pcMsg              [in]    用户消息
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/21  4.0     王昊    创建
    =============================================================================*/
    void UpdateUserTable(const CMessage *pcMsg);

    /*函数名： UpdateUserGroupTable
    功    能： 更新用户组列表
    参    数： const CMessage *pcMsg		[in]    用户消息
    返 回 值： void 
    说    明： */
	void UpdateUserGroupTable( const CMessage *pcMsg );

    /*=============================================================================
    函 数 名:UpdateConfInfo
    功    能:更新会议信息
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
             BOOL32 bCheckLockSelf              [in]    是否检查会议是否是独享的
    注    意:bCheckLockSelf只有在MCU_MCS_CREATECONF_ACK消息处理时才能够设为TRUE
    返 回 值:TRUE: 会议已存在; FALSE: 会议不存在
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/21  4.0     王昊    创建
    =============================================================================*/
    BOOL32 UpdateConfInfo(CServMsg &cServMsg, TMcsParam &tMcsParam,
                          BOOL32 bCheckLockSelf = FALSE);

    /*=============================================================================
    函 数 名:UpdateConfAllMtInfo
    功    能:更新TConfAllMtInfo
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/21  4.0     王昊    创建
    =============================================================================*/
    void UpdateConfAllMtInfo(CServMsg &cServMsg, TMcsParam &tMcsParam);

    /*=============================================================================
    函 数 名:UpdateMtList
    功    能:更新终端列表
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/21  4.0     王昊    创建
    =============================================================================*/
    void UpdateMtList(CServMsg &cServMsg, TMcsParam &tMcsParam);

    /*=============================================================================
    函 数 名:UpdateLockInfo
    功    能:更新会议锁定信息
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/22  4.0     王昊    创建
    =============================================================================*/
    void UpdateLockInfo(CServMsg &cServMsg);

    /*=============================================================================
    函 数 名:UpdateMtStatus
    功    能:更新终端状态
    参    数:const CConfId &cConfId             [in]    会议号
             const TMtStatus *ptMtStatusTable   [in]    终端状态列表
             s32 nMtNum                         [in]    终端个数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/27  4.0     王昊    创建
    =============================================================================*/
    void UpdateMtStatus(const CConfId &cConfId, const TMtStatus *ptMtStatusTable,
                        s32 nMtNum);

    /*=============================================================================
    函 数 名:UpdateMtStatus
    功    能:更新终端状态
    参    数:const CConfId &cConfId             [in]    会议号
             const TMtStatus *ptMtStatusTable   [in]    终端状态列表
             s32 nMtNum                         [in]    终端个数
             u8* pbyBuf                         [in]    需要回传给界面的Buf
    注    意:无
    返 回 值:u16 回传的终端状态个数,如0则不需要通知界面
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/01/20  4.0     顾振华  创建
    =============================================================================*/
    u16 UpdateMtStatus(const CConfId &cConfId, const TMtStatus *ptMtStatusTable,
                       s32 nMtNum, 
                       u8* pbyBuf);

    /*=============================================================================
    函 数 名:UpdateMtVersion
    功    能:更新终端版本信息
    参    数:const CConfId &cConfId             [in]    会议号
             const TMtExt2 *ptMtExt2Table       [in]    终端状态列表
             s32 nMtNum                         [in]    终端个数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2007/12/27  4.0     王廖荣    创建
    =============================================================================*/
    void UpdateMtVersion(const CConfId &cConfId, const TMtExt2 *ptMtExt2Table,
                         s32 nMtNum);

    /*=============================================================================
    函 数 名:UpdateAllMtAlias
    功    能:更新所有终端别名
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/27  4.0     王昊    创建
    =============================================================================*/
    void UpdateAllMtAlias(CServMsg &cServMsg);

    /*=============================================================================
    函 数 名:UpdateMtAlias
    功    能:更新单个终端别名
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/27  4.0     王昊    创建
    =============================================================================*/
    void UpdateMtAlias(CServMsg &cServMsg, TMcsParam &tMcsParam );

    /*=============================================================================
    函 数 名:UpdateMcuMediaSrc
    功    能:更新MCU媒体源
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/03  4.0     王昊    创建
    =============================================================================*/
    BOOL32 UpdateMcuMediaSrc(CServMsg &cServMsg, TMcsParam &tMcsParam );

    /*=============================================================================
    函 数 名:UpdateSMcuLockStatus
    功    能:更新下级MCU锁定状态
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/27  4.0     王昊    创建
    =============================================================================*/
    void UpdateSMcuLockStatus(CServMsg &cServMsg, TMcsParam &tMcsParam);

    /*=============================================================================
    函 数 名:UpdateMixParam
    功    能:更新混音参数
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/07/27  4.0     王昊    创建
    =============================================================================*/
    void UpdateMixParam(CServMsg &cServMsg, TMcsParam &tMcsParam);

    /*=============================================================================
    函 数 名:UpdatePeriStatus
    功    能:更新外设状态
    参    数:TPeriEqpStatus *ptPeriEqpStatus    [in]    外设状态
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/02  4.0     王昊    创建
    =============================================================================*/
    void UpdatePeriStatus(TPeriEqpStatus *ptPeriEqpStatus);

    /*=============================================================================
    函 数 名:UpdateConfStatus
    功    能:更新会议状态
    参    数:CConfId &cConfId                   [in]    会议号
             TConfStatus &tConfStatus           [in]    会议状态
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/03  4.0     王昊    创建
    =============================================================================*/
    void UpdateConfStatus(CConfId &cConfId, TConfStatus &tConfStatus);

    /*=============================================================================
    函 数 名:UpdateTemSchInfo
    功    能:更新会议模板/预约会议信息
    参    数:CServMsg &cServMsg                 [in]    返回的MCU消息
             TMcsParam &tMcsParam               [out]   发往界面的参数
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/11/22  4.0     王昊    创建
    =============================================================================*/
    BOOL32 UpdateTemSchInfo(CServMsg &cServMsg, TMcsParam &tMcsParam);

//private:
    /*=============================================================================
    函 数 名:OnMcMsg
    功    能:mcslib自己设置的消息
    参    数:CMessage * const pMsg              [in]    自己设置消息
             CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/30  4.0     王昊    创建
    =============================================================================*/
    void OnMcMsg( CMessage * const pcMsg, CMsgHandler *pHandler );

    /*=============================================================================
    函 数 名:OnSetTimer
    功    能:设置定时器消息处理
    参    数:u32 dwTimeout                      [in]    超时时间
             CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/02  4.0     王昊    创建
    =============================================================================*/
    void OnSetTimer(u32 dwTimeout, CMsgHandler *pHandler);

    /*=============================================================================
    函 数 名:OnTimerReply
    功    能:超时消息处理
    参    数:CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/02  4.0     王昊    创建
    =============================================================================*/
    void OnTimerReply(CMsgHandler *pHandler);

    /*=============================================================================
    函 数 名:OnConnectBakMcu
    功    能:启动线程连接备份MCU
    参    数:CMsgHandler *pHandler              [in]    消息处理类的指针
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/26  4.0     王昊    创建
    =============================================================================*/
    void OnConnectBakMcu(CMsgHandler *pHandler);

    /*=============================================================================
    函 数 名:ConnectBckMcuThread
    功    能:用于连接备份MCU的线程
    参    数:TSessionHandler *lpData              [in]    指向自身session数据结构
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/29  4.0     顾振华  创建
    =============================================================================*/
    static DWORD WINAPI ConnectBckMcuThread(LPVOID lpData) ;

    /*=============================================================================
    函 数 名:OnDisconnect
    功    能:断链消息处理
    参    数:CMsgHandler *pHandler              [in]    消息处理类的指针
             u32 dwNode                         [in]    断链的节点
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/08/02  4.0     王昊    创建
    =============================================================================*/
    void OnDisconnect(CMsgHandler *pHandler, u32 dwNode);

    /*=============================================================================
    函 数 名:RefreshLockConfStatus()
    功    能:同步主备MCU对会议的锁定状态
    参    数:

    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2008/03/17  4.0     王廖荣    创建
    =============================================================================*/
    void RefreshLockConfStatus();

public:
	// liuruifei [4/4/2006]
    /*函数名： DownloadMcuCfg
    功    能： 会控请求下载MCU配置文件
    参    数： void
    返 回 值： u16 
    说    明： */
	u16 DownloadMcuCfg( void );

     /*函数名： UploadMcuCfg
    功    能：   会控请求上传配置文件
    参    数：  s8* pFileContent	[in]	文件内容
               u32 dwFileLength		[in]	文件长度
    返 回 值： u16 
    说    明： */
	u16 UploadMcuCfg( s8* pFileContent , u32 dwFileLength);

     /*函数名： UploadFileReq
    功    能：   会控请求更新DSC文件
    参    数：  u8 byEqpIdx	            [in]	待更新文件的单板索引
                vector<CString> &vctFileName   [in]	文件名列表
    返 回 值： u16 
    说    明： */
	u16 UploadFileReq( u8 byEqpIdx, vector<CString> &vctFileName );

     /*函数名： UploadFilePackageReq
    功    能：   会控向MCU发送升级文件数据包请求
    参    数：  u8 byEqpIndex                       [in]    单板索引
                TDscUpdateReqHead &tUpdateReqHead   [in]    消息包头
                s8* pFileContent	                [in]	文件内容
    返 回 值： u16 
    说    明： */
	u16 UploadFilePackageReq( u8 byEqpIndex, TDscUpdateReqHead &tUpdateReqHead, s8* pFileContent );

     /*函数名： UpdateTelnetLoginInfoReq
    功    能：  更新Telnet登录密码
    参    数：  TLoginInfo &tLoginInfo              [in]    Telnet登录信息
    返 回 值： u16 
    说    明： */
	u16 UpdateTelnetLoginInfoReq( TLoginInfo &tLoginInfo );

     /*函数名： StartRollCallReq
    功    能：  开始点名请求
    参    数：  const u8 byType             [in]    点名模式
    返 回 值： u16 
    说    明： */
	u16 StartRollCallReq( const CConfId &cConfId, const u8 byType );

     /*函数名： StopRollCallReq
    功    能：  停止点名请求
    参    数：  
    返 回 值： u16 
    说    明： */
	u16 StopRollCallReq( const CConfId &cConfId );

     /*函数名： ChangeRollCallReq
    功    能：  点名人员变更
    参    数：  const TMt &tMtCaller        [in]    点名人
                const TMt &tMtCalled        [in]    被点名人
    返 回 值： u16 
    说    明： */
	u16 ChangeRollCallReq(  const CConfId &cConfId, const TMt &tMtCaller, const TMt &tMtCalled);

	// liuruifei [4/13/2006]

    /*函数名： UpgradeNotify
    功    能： 上传完成改名通知
    参    数：  TBrdCfgInfo& tBrdInfo   [in] 标识唯一的单板	
                CString strName			[in] 需要改名的文件字符串
    返 回 值： u16 
    说    明： */
//	u16 UpgradeComplete(TBrdCfgInfo& tBrdInfo, const CString& strName );

	// lrf [6/13/2006]
    /*函数名： DcsStatusReq
    功    能： 获取Dcs外设状态的请求
    参    数： const TEqp &tEqp		[in]指定dcs外设的标识
    返 回 值： u16 
    说    明： */
	u16 DcsStatusReq( const TEqp &tEqp );

	// lrf [6/23/2006]
    /*函数名： SetUserGrpId
    功    能： 设置用户的用户组ID
    参    数： u8 byGrpId
    返 回 值： void 
    说    明： */
	void SetUserGrpId( u8 byGrpId )
	{
		m_byUserGrpId = byGrpId;
	}

    /*函数名： GetUserGrpId
    功    能： 获取用户属于哪一个用户组
    参    数： void
    返 回 值： u8 
    说    明： */
	u8 GetUserGrpId( void ) const
	{
		return m_byUserGrpId;
	}

	// lrf [7/18/2006]
	void SetMCUOsType( u8 byType )
	{
		m_byOsType = byType;
	}

	u8 GetMCUOsType() const
	{
		return m_byOsType;
	}
    
    /*函数名： GetDisconnectReason
    功    能： 获取断链的原因
    参    数： void
    返 回 值： BOOL32   False：非正常挂断；True：用户正常挂断
    说    明： */
    BOOL32 GetDisconnectReason()
    {
        return m_bUserDisconnect;
    }
public:
    // 会议调度的相关接口
    void SetMcuSessionAppID( u32 dwSessionID )
    {
        m_dwMcuSessionAppID = dwSessionID;
    }

    // 修改调度模式
    u16 VcsChangeModeReq( const CConfId &cConfId, const u8 byVcsConfMode );
    // 调度终端
    u16 VcsSchedulingMtReq( const CConfId &cConfId, const TMt &tMt , u8 byOprMode = VCS_VCTYPE_DEFAULT, u8 byCallMode = VCS_FORCECALL_REQ );
    // 开始调度会议
    u16 VcsEnterConfReq( const CConfId &cConfId );
    // 离开调度会议
    u16 VcsQuitConfReq( const CConfId &cConfId );
    // 声音控制
    u16 VcsSoundControl( const CConfId &cConfId, u8 byVcsMode, u8 byEnable, u8 byMtType, u8 bySoundType );

    u16 VcsChangeVcsName( const CString strName );
    
    u16 VcsCallGroupReq( const CConfId &cConfId, u8 byGroupNum, TCallGroupInfo *ptCallGroupInfo );
    //批量挂断组内所有终端
    u16 VcsDropCallGroupMtReq( const CConfId &cConfId, u8 byGroupNum, TCallGroupInfo *ptCallGroupInfo );

    //开启和关闭本地轮询
    u16 VcsStartChairPollReq( const CConfId &cConfId, const u8 byTime );
    u16 VcsStopChairPollReq( const CConfId &cConfId );

    //删除或添加临时终端
    u16 VcsAddMtReq( const CConfId &cConfId, const TAddMtInfo &tAddMt );
    u16 VcsDeleteMtReq( const CConfId &cConfId, const TMt &tMt );

    u16 VcsNotifSlaveMcuOprConf( const CConfId &cConfId );
	
    u16 VcsUserSettingReq( const s8* pbyBuffer, u32 dwBufLen );
    
    //平级强拆
    u16 VcsReleaseMtAck( const CConfId &cConfId, const TMt &tMt,  const s8 *pstrConfName );
    u16 VcsReleaseMtNack( const CConfId &cConfId, const TMt &tMt,  const s8 *pstrConfName );

public:
	CMcuCfg          m_cMcuCfg;				//  本次会话连接的MCU参数和配置
	TVmpStyleCfgInfo m_atVmpStyle [MAX_VMPSTYLE_NUM]; //本次会话所有画面合成方案(单独请求，为了方便用户数用)
    THduStyleCfgInfo m_atHduStyle [MAX_HDUSTYLE_NUM]; //本次会话所有高清电视墙方案(单独请求，为了方便用户数用)


public:
	// MCU上的会议、外设、用户、地址簿信息	
    CConfTable      m_cConfTable;       //  本次会话所有即时会议列表
    CConfTemSchTable m_cConfTemSchTable;    //本次会话所有预约会议/会议模板列表
    CPeriTable      m_cPeriTable;       //  本次会话所有外设列表
    CUserManage      m_cUserManage;       //  本次会话所有用户列表
    CVcsUserManage  m_cVcsUserManage;
    TplArray<TRecFileInfo>  m_tplRecFileInfo;   //  本次会话所有录像文件列表
    CMcuAddrBook    m_cAddrBook;        //  本次会话地址簿

	// 其他
    u32             m_dwMcuIp;          //  MCU的IP地址
	u32             m_dwBakMcuIp;       //  备份MCU的IP地址

    u16             m_wInsId;           //  本次会话实例号
    TMonitorParam   m_atMonitorMember[MAXNUM_MC_CHANNL];   //  监控参数

    TSwitchMonitor  m_tSwitchMonitorMain;   //切换监控窗口, 记录原始主窗口信息
    TSwitchMonitor  m_tSwitchMonitorSrc;    //切换监控窗口, 记录原始切换窗口信息

    // 以下两个变量用于第一次登录mcu时，自动启动配置向导
    // 当前界面是否已经刷新了MCU的配置信息，并且是否可以弹出MCU的配置向导了
    BOOL32  m_bBeReadyForWizard;
    // 是否已经启动过配置向导
    BOOL32  m_bHaveStartedWizard;
    // 配置向导是否是自动弹出
    BOOL32  m_bAutoStartedWizard;
    
    // MCU 8000B 能力限制逻辑
    TMcu8kbPfmFilter    m_tMcu8kbPfmFilter;

    // 8000B中未注册成功的DSC的类型
    u8  m_byTypeOfDsc;
    // 8000B中未注册成功的DSC的外部IP
    u32 m_dwDscIP;
    // 8000B中未注册成功的DSC的内部IP
    u32 m_dwDscInnerIP;
    // 8000B中未注册成功的DSC连接的本地MCU的内部IP
    u32 m_dwMcuInnerIP;
    // 8000B中未注册成功的DSC的内部IP的子网掩码
    u32 m_dwDscInnerMask;

public:
    s8  m_abyVCSName[64];
    u8  m_byHDUStyleID; //正在被使用的预案的ID
    vector<THideMtInfo> m_vctHideMt;    //配置的需要隐藏的终端
	BOOL32 m_dwDisplayFlag;

private:
    u32             m_dwMcuNode;        //  MCU节点
    u32             m_dwMsgId;          //  本会控发送消息的ID

    u32             m_dwBakMcuNode;     //  备份MCU节点
    u32             m_dwBakMcuMsgId;    //  备份MCU的会控发送消息的ID

    u16             m_wMcuPort;         //  MCU端口
    TCHAR           m_aszUserName[MAXLEN_PWD];  //  用户名
    TCHAR           m_aszPwd[MAXLEN_PWD];       //  密码
	u8				m_byUserGrpId;
	
	u8				m_byOsType;			//1-VxWorks, 2-Linux, 3-Win32

    CCriticalSection    m_csMcuLock;    //  用于控制数据同步问题
    EMTimerWaitState    m_emTimerState; //  定时状态
    EMTimerWaitState    m_emMcuMSTimerState;//  当MCU主备倒换时需要额外的定时状态
    u16             m_wState;           //  MCSLIB_STATE_IDLE/MCSLIB_STATE_NORMAL
    CMsgHeadInfo    m_cMsgHeadInfo;     //  用于收发的消息头

    u32             m_dwLocalIpAddr;            //  本级接收码流地址
    u16             m_wMonitorStartPort;        //  视频监控起始端口

    TMt             m_atMixMt[MAXNUM_SUB_MCU][MAXNUM_MIXER_CHNNL];//部分混音成员
    s32             m_anMixNum[MAXNUM_SUB_MCU];//混音成员个数

    HWND            m_hWnd;             //  上层应用程序句柄
    bool            m_bUnitTest;        //  是否是单元测试
    bool            m_bUserDisconnect;  //  是否用户主动断链
    u32             m_dwConnectSn;      //  连接时产生的随机序列号
    HANDLE          m_hConnectBakMcuThd;//  连接备份MCU的线程句柄
    TSessionHandler m_tHandler;         //  备份MCU的线程所需要的数据

    u32             m_dwConnectFlag;    //  连接MCU的标记，当主备时，该值发生变化则说明主备同时重启过，会控将主动断链

private:
    u32             m_dwMcuSessionAppID;

public:
    static bool s_bPrtConfMsg;          //  是否打印会议消息
    static bool s_bPrtPeriMsg;          //  是否打印外设消息
    static bool s_bPrtAddrMsg;          //  是否打印地址簿消息
    static bool s_bPrtUserMsg;          //  是否打印用户消息
    static bool s_bPrtMtMsg;            //  是否打印终端消息
    static bool s_bPrtMcuMsg;           //  是否打印MCU消息
    static bool s_bPrtIntTestMsg;       //  是否打印集成测试查询消息
    static bool s_bPrtMcsMsgBody;       //  是否打印MCS向MCU发送的消息体
    static bool s_bPrtMcuMsgBody;       //  是否打印MCU向MCS发送的消息体
    static u16  s_wMtTestIpPort;        //	呼叫端口号

    typedef void (*PFuncConnectMsgDeal)(CMcuSession *pcSession,
                                        CMsgHandler *pHandler,
                                        const CMessage *pcMsg);
    typedef void (*PFuncServMsgDeal)(CMcuSession *pcSession,
                                     CMsgHandler *pHandler,
                                     TMcsParam &tMcsParam,
                                     CServMsg &cServMsg);

    static TplHash<u16, PFuncConnectMsgDeal> s_hashConnectMsgFun;//处理连接消息函数
    static TplHash<u16, PFuncServMsgDeal> s_hashServMsgFunc;//处理MCU消息函数

    friend class CAddrMsgDeal;
    friend class CConfControlMsgDeal;
    friend class CConfManageMsgDeal;
    friend class CConfOperateMsgDeal;
    friend class CConnectMcuMsgDeal;
    friend class CMcuOperateMsgDeal;
    friend class CMtMsgDeal;
    friend class CPeriMsgDeal;
    friend class CUserMsgDeal;
    friend class CVcsConfMsgDeal;
    friend class CDebugOut;
};

#endif  //  _MCSLIB_20050427_H_