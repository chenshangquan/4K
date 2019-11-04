/*****************************************************************************
模块名      : GkcLib
文件名      : GkcLibDefine.h
相关文件    : 无
文件实现功能: 定义了CGkcLibInterface需要用的宏、结构、枚举等。
              同时定义了上行窗口消息。

作者        : 陈洪斌
模块版本    : V4.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期(n/m/d)      文件版本        修改人      修改内容
2005/08/08         1.0             陈洪斌     创建
******************************************************************************/
#ifndef GKCLIBDEFINE_H
#define GKCLIBDEFINE_H

#include "kdvgk.h"

//GkcLib内部应用号
#define AID_GKCONSOLE       AID_GKC_BGN
#define AID_INTE_TEST_GKC   AID_GKC_BGN + 1
#define AID_UNIT_TEST_GKC   AID_GKC_BGN + 2

//接口函数返回
#define GKC_OPERATE_SUCCESS				    		(u32)0 //操作成功
//消息发送或接口条件不满足时的错误号
#define OSP_ALWAYS_INIT								(u32)50	//已经初始化
#define NO_WINDOW_IS_SUCH_HWND						(u32)51	//窗口句柄不代表一个有效窗口
#define OSP_NOT_INIT								(u32)52	//没有初始化
#define FAIL_TO_CONNECT_GK							(u32)53	//主动与GK建链失败
#define FAIL_TO_SEND_MSG_TO_GK						(u32)54	//链路忙，发送消息给GK失败
#define OPERATE_MUST_IN_IDLE_STATE					(u32)55	//只有未成功与GK建链才能执行该操作
#define OPERATE_MUST_IN_NORMAL_STATE				(u32)56	//只有当成功与GK建链才能执行该操作
#define OPERATE_MUST_WAIT							(u32)57	//GK忙，正在处理前一个请求


//GKC等待GK回复时间，OSP定时(毫秒为单位)
#define DEFAULT_TIMEOUT         (DWORD)8000

//设置OSP定时器事件定义
#define EV_SET_TIMER			EV_MC_BGN
#define EV_KILL_TIMER			EV_MC_BGN + 1

//////////////////////////////////////////////////////////////////////////
// 相关结构定义
//////////////////////////////////////////////////////////////////////////

enum EGkcState //控制台状态定义
{
    GKC_STATE_IDLE                  = 0,
	GKC_STATE_NORMAL				= 1,
	GKC_WAIT_CONNECTTO_GK			= 2,
	GKC_WAIT_GET_USERLIST			= 3,
	GKC_WAIT_ADD_USER				= 4,
	GKC_WAIT_DEL_USER				= 5,
	GKC_WAIT_MODIFY_USER			= 6,
	GKC_WAIT_MODIFY_USERPASS		= 7,
	GKC_WAIT_USER_IS_EXIST			= 8,
	GKC_WAIT_GET_BASECFG			= 9,
	GKC_WAIT_SET_BASECFG			= 10,
	GKC_WAIT_GET_IPRNGLIST			= 11,
	GKC_WAIT_ADD_IPRNG				= 12,
	GKC_WAIT_DEL_IPRNG				= 13,
	GKC_WAIT_MODIFY_IPRNG			= 14,
	GKC_WAIT_GET_SUBNET_BANDLIST	= 15,
	GKC_WAIT_ADD_SUBNET_BANDWIDTH	= 16,
	GKC_WAIT_DEL_SUBNET_BANDWIDTH	= 17,
	GKC_WAIT_MODIFY_SUBNET_BANDWIDTH= 18,
	GKC_WAIT_SUBNET_BANDWIDTH		= 19,
	GKC_WAIT_GET_PASSWORD_LIST		= 20,
	GKC_WAIT_ADD_PASSWORD			= 21,
	GKC_WAIT_DEL_PASSWORD			= 22,
	GKC_WAIT_MODIFY_PASSWORD		= 23,
	GKC_WAIT_GET_ENDPOINTLIST		= 24,
	GKC_WAIT_ADD_ENDPOINT			= 25,
	GKC_WAIT_DEL_ENDPOINT			= 26,
	GKC_WAIT_MODIFY_ENDPOINT		= 27,
	GKC_WAIT_ENDPOINT				= 28,
	GKC_WAIT_GET_REG_ENDPOINTLIST	= 29,
	GKC_WAIT_DEL_REG_ENDPOINT		= 30,
	GKC_WAIT_GET_ENDPOINT_CALLLIST	= 31,
	GKC_WAIT_DEL_ENDPOINT_CALL	    = 32,
	GKC_WAIT_GET_PREFIX				= 33,
	GKC_WAIT_SET_PREFIX				= 34,
//	GKC_WAIT_GET_PREFIXRULES		= 35,
//	GKC_WAIT_SET_PREFIXRULES		= 36,
	GKC_WAIT_GET_GKREG_STATUS		= 37,   
	GKC_WAIT_ADD_PREFIX				= 38,
	GKC_WAIT_DEL_PREFIX				= 39,
	GKC_WAIT_ADD_NEIGHBORGK			= 40,
	GKC_WAIT_GET_NEIGHBORGK			= 41,
	GKC_WAIT_DEL_NEIGHBORGK			= 42,
	GKC_WAIT_GET_AUTHMETHOD			= 43,	
	GKC_WAIT_SET_AUTHMETHOD         = 44,
    GKC_WAIT_GET_ONEUSER			= 45,
    GKC_WAIT_GET_ETHNETPORT         = 46,
    GKC_WAIT_SET_ETHNETPORT         = 47,
    GKC_WAIT_SET_RADIUS             = 48,
    GKC_WAIT_GET_RADIUS             = 49,
	GKC_WAIT_GET_IPFORBIDLIST       = 50
};

//为了上层方便使用,封装实体认证策略(方式)的操作
class CGkAuthMothod
{
public:
    CGkAuthMothod()
    {
        m_dwGkAuthMothod = 0;
    };
public:
    //设置认证策略的32位值
    void SetAuthMethod(u32 dwGkAuthMothod)
    {
        m_dwGkAuthMothod = dwGkAuthMothod;
    }

    /*=============================================================================
    函 数 名:GetNetAuthMethod
    功    能:获取网络序认证策略
    参    数:无
    注    意:无
    返 回 值:网络序认证策略
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2005/12/26  4.0     王昊    创建
    =============================================================================*/
    u32 GetNetAuthMethod(void) const
    { 
        return htonl( m_dwGkAuthMothod );
    }

    //获取认证策略的32位值
    u32 GetAuthMethod() const
    {
        return m_dwGkAuthMothod;
    }

    //设置不需要认证
    void SetNotAuth()
    {
        m_dwGkAuthMothod = 0;
    };
    
    //是否需要认证
    bool IsNeedAuth() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthIPForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthPassword
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    
    //设置ip认证允许生效
    void SetAuthIPAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPAllow;       
    };

    //设置ip认证禁止生效
    void SetAuthIPForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPForbid;
    };
    
    //是否ip认证允许生效
    bool IsAuthIPAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //是否ip认证禁止生效
    bool IsAuthIPForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //设置实体认证允许生效
    void SetAuthAliasAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasAllow;       
    };

    //设置实体认证禁止生效
    void SetAuthAliasForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasForbid;
    };
    
    //是否实体认证允许生效
    bool IsAuthAliasAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //是否实体认证禁止生效
    bool IsAuthAliasForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //设置密码认证
    void SetAuthPassword()
    {
        m_dwGkAuthMothod |= emAuthMethod_AuthPassword;
    };

    //是否密码认证
    bool IsAuthPassword() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthPassword) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    u32 m_dwGkAuthMothod; //认证策略32位值
};


//////////////////////////////////////////////////////////////////////////
// 上行自定义窗口消息，具体消息内容见接口说明书
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//登陆和注销
//////////////////////////////////////////////////////////////////////////
//登陆成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_CONNECT_GK_SUCCESS     WM_USER + 1
//登陆失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_CONNECT_GK_FAILED      WM_USER + 2
//断链检测通知(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DISCONNECT_FROM_GK_NOTIFY     WM_USER + 3

//////////////////////////////////////////////////////////////////////////
// 运行时消息
//////////////////////////////////////////////////////////////////////////
//获取已注册H323实体列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_REGISTER_ENDPOINT_LIST_SUCCESS    WM_USER + 10
//获取已注册H323实体列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_REGISTER_ENDPOINT_LIST_FAILED     WM_USER + 11

//强制注销已注册H323实体成功(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_UNREGISTER_ENDPOINT_SUCCESS    WM_USER + 12
//强制注销已注册H323实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_UNREGISTER_ENDPOINT_FAILED     WM_USER + 13

//获取实体呼叫列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_CALL_LIST_SUCCESS    WM_USER + 14
//获取实体呼叫列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_CALL_LIST_FAILED     WM_USER + 15

//强制结束呼叫成功(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_STOP_CALL_SUCCESS    WM_USER + 16
//强制结束呼叫失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_STOP_CALL_FAILED     WM_USER + 17

//实体注册通知(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_ENDPOINT_REGISTER_NOTIFY   WM_USER + 20

//实体注销通知(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_ENDPOINT_UNREGISTER_NOTIFY   WM_USER + 21

//实体呼叫通知(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_CALL_NOTIFY   WM_USER + 22

//实体呼叫结束通知(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_STOP_CALL_NOTIFY   WM_USER + 23

//实体呼叫带宽改变通知(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_CALL_BANDWIDTH_CHANGE_NOTIFY   WM_USER + 24

//////////////////////////////////////////////////////////////////////////
// 配置消息 -- 基本配置
//////////////////////////////////////////////////////////////////////////
//获取GK基本配置成功(WPARAM)(BYTE*),(LPARAM)(NULL)
#define GKC_DISP_GET_BASECFG_SUCCESS    WM_USER + 30
//获取GK基本配置失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_BASECFG_FAILED     WM_USER + 31

//设置GK基本配置成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_BASECFG_SUCCESS    WM_USER + 32
//设置GK基本配置失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_SET_BASECFG_FAILED     WM_USER + 33

//获取GK区号列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_PREFIX_LIST_SUCCESS    WM_USER + 34
//获取GK区号列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_PREFIX_LIST_FAILED     WM_USER + 35

//新增区号成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_PREFIX_SUCCESS    WM_USER + 36
//新增区号失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_PREFIX_FAILED     WM_USER + 37

//删除区号成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_PREFIX_SUCCESS    WM_USER + 38
//删除区号失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_PREFIX_FAILED     WM_USER + 39

//获取临近GK服务器列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_NEIGHBOR_GK_LIST_SUCCESS    WM_USER + 40
//获取临近GK服务器列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_NEIGHBOR_GK_LIST_FAILED     WM_USER + 41

//新增临近GK服务器成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_NEIGHBOR_GK_SUCCESS    WM_USER + 42
//新增临近GK服务器失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_NEIGHBOR_GK_FAILED     WM_USER + 43

//删除临近GK服务器成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_NEIGHBOR_GK_SUCCESS    WM_USER + 44
//删除临近GK服务器失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_NEIGHBOR_GK_FAILED     WM_USER + 45

//获取GK认证方式成功(WPARAM)(u32),(LPARAM)(NULL)
#define GKC_DISP_GET_AUTH_METHOD_SUCCESS    WM_USER + 46
//获取GK认证方式失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_AUTH_METHOD_FAILED     WM_USER + 47

//设置GK认证方式成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_AUTH_METHOD_SUCCESS    WM_USER + 48
//设置GK认证方式失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_SET_AUTH_METHOD_FAILED     WM_USER + 49

//设置本地GK使用网口成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_ETH_NETPORT_SUCCESS    WM_USER + 50
//设置本地GK使用网口失败(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_SET_ETH_NETPORT_FAILED     WM_USER + 51

//获取本地GK使用网口成功(WPARAM)(u8),(LPARAM)(NULL)
#define GKC_DISP_GET_ETH_NETPORT_SUCCESS    WM_USER + 52
//获取本地GK使用网口失败(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_GET_ETH_NETPORT_FAILED     WM_USER + 53

//设置Radius服务器成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_SET_RADIUS_SUCCESS         WM_USER + 54
//设置Radius服务器失败(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_SET_RADIUS_FAILED          WM_USER + 55

//获取Radius服务器成功(WPARAM)(TRadiusConfigInfo),(LPARAM)(NULL)
#define GKC_DISP_GET_RADIUS_SUCCESS         WM_USER + 56
//获取Radius服务器失败(WPARAM)(BOOL32),(LPARAM)(u32)
#define GKC_DISP_GET_RADIUS_FAILED          WM_USER + 57

//////////////////////////////////////////////////////////////////////////
// 配置消息 -- 网段带宽配置
//////////////////////////////////////////////////////////////////////////
//获取网段间带宽列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_SUBNET_BANDWIDTH_LIST_SUCCESS    WM_USER + 60
//获取网段间带宽列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_SUBNET_BANDWIDTH_LIST_FAILED     WM_USER + 61

//新增网段间带宽成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 62
//新增网段间带宽失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_SUBNET_BANDWIDTH_FAILED     WM_USER + 63

//删除网段间带宽成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 64
//删除网段间带宽失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_SUBNET_BANDWIDTH_FAILED     WM_USER + 65

//修改网段间带宽成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_SUBNET_BANDWIDTH_SUCCESS    WM_USER + 66
//修改网段间带宽失败
#define GKC_DISP_MODIFY_SUBNET_BANDWIDTH_FAILED     WM_USER + 67

//////////////////////////////////////////////////////////////////////////
// 配置消息 -- IP范围认证配置
//////////////////////////////////////////////////////////////////////////
//获取认证IP范围列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_LIST_SUCCESS    WM_USER + 70
//获取认证IP范围列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_LIST_FAILED     WM_USER + 71

//新增认证IP范围成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_IP_RANGE_SUCCESS    WM_USER + 72
//新增认证IP范围失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_IP_RANGE_FAILED     WM_USER + 73

//删除认证IP范围成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_IP_RANGE_SUCCESS    WM_USER + 74
//删除认证IP范围失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_IP_RANGE_FAILED     WM_USER + 75

//修改认证IP范围成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_IP_RANGE_SUCCESS    WM_USER + 76
//修改认证IP范围失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_IP_RANGE_FAILED     WM_USER + 77

//////////////////////////////////////////////////////////////////////////
// 配置消息 -- 实体认证配置
//////////////////////////////////////////////////////////////////////////
//获取认证实体列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_ENDPOINT_LIST_SUCCESS    WM_USER + 80
//获取认证实体列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_ENDPOINT_LIST_FAILED     WM_USER + 81

//新增认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_ENDPOINT_SUCCESS    WM_USER + 82
//新增认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_ENDPOINT_FAILED     WM_USER + 83

//删除认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_ENDPOINT_SUCCESS    WM_USER + 84
//删除认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_ENDPOINT_FAILED     WM_USER + 85

//修改认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_ENDPOINT_SUCCESS    WM_USER + 86
//修改认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_ENDPOINT_FAILED     WM_USER + 87

//////////////////////////////////////////////////////////////////////////
// 用户管理消息
//////////////////////////////////////////////////////////////////////////
//获取用户信息列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_USER_LIST_SUCCESS    WM_USER + 90
//获取用户信息列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_USER_LIST_FAILED     WM_USER + 91

//新增用户成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_USER_SUCCESS    WM_USER + 92
//新增用户失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_USER_FAILED     WM_USER + 93

//删除用户成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_USER_SUCCESS    WM_USER + 94
//删除用户失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_USER_FAILED     WM_USER + 95

//修改用户成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_USER_SUCCESS    WM_USER + 96
//修改用户失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_USER_FAILED     WM_USER + 97

//修改用户密码成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_USER_PASSWORD_SUCCESS    WM_USER + 98
//修改用户密码失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_USER_PASSWORD_FAILED     WM_USER + 99

//////////////////////////////////////////////////////////////////////////
// 配置消息 -- 实体认证配置
//////////////////////////////////////////////////////////////////////////
//获取认证实体列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_PASSWORD_LIST_SUCCESS    WM_USER + 100
//获取认证实体列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_PASSWORD_LIST_FAILED     WM_USER + 101

//新增认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_ADD_PASSWORD_SUCCESS    WM_USER + 102
//新增认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_ADD_PASSWORD_FAILED     WM_USER + 103

//删除认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_DEL_PASSWORD_SUCCESS    WM_USER + 104
//删除认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_DEL_PASSWORD_FAILED     WM_USER + 105

//修改认证实体成功(WPARAM)(NULL),(LPARAM)(NULL)
#define GKC_DISP_MODIFY_PASSWORD_SUCCESS    WM_USER + 106
//修改认证实体失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_MODIFY_PASSWORD_FAILED     WM_USER + 107

//获取认证IP范围列表成功(WPARAM)(BYTE*),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_FORBID_LIST_SUCCESS    WM_USER + 108
//获取认证IP范围列表失败(WPARAM)(bool),(LPARAM)(u32)
#define GKC_DISP_GET_IP_RANGE_FORBID_LIST_FAILED     WM_USER + 109


//内部dlg通信消息

#define GKC_SET_IP_AUTHOR			WM_USER + 200

#define GKC_SET_ENTITY_AUTHOR		WM_USER + 201

#define GKC_SET_PASSWORD_AUTHOR		WM_USER + 202

//日志文件名(相对路径)
#define GKC_LOG										(LPSTR)"gkc.txt"

#endif //#define GKCLIBDEFINE_H
