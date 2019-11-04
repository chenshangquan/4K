/*****************************************************************************
模块名      : cmc cnclib接口
文件名      : cncconfigif.h
相关文件    : 
文件实现功能: cns配置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/30   1.0         肖楚然        创建
******************************************************************************/
#ifndef __CNCCONFIGIF_H__
#define __CNCCONFIGIF_H__

#include "kdvdispevent.h"
#include "cmsstruct.h"
#include <vector>

class CCncConfigIF : public CKdvDispEvent
{
public:
	/** 功能  注册SIP服务
	 *  @param[in] tSipCfg 配置信息
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 RegSipService(const TTPSipRegistrarCfg& tSipCfg) = 0;

	/** 功能  注销SIP服务
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UnRegSipService() = 0;

	/** 功能   获得SIP配置
	 *  @return TTPSipRegistrarCfg SIP信息
	 */
	virtual const TTPSipRegistrarCfg& GetSipRegCfg() const = 0;

	/** 功能   获得网络配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual const TTPEthnetInfo& GetEthnetCfg() const = 0;

	/** 功能   GK
	 *  @return tGkCfg 配置信息
	 */
    virtual u16 RegGk( const TTPGKCfg& tGkCfg ) = 0;

    /** 功能   获得GK配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual  const TTPGKCfg& GetGkCfg() const = 0;

	/** 功能   更新网络配置
	 *  @param[in] cfg 网络配置
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg ,EmTpIpNameNatSyn emTpIpType) = 0;

	virtual u16 SaveWEthnetCfgCmd( const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType ) = 0;
	
	/** 功能   获得本地CNS信息
	 *  @return TTPCnsInfo CNS信息
	 */
	virtual const TTPCnsInfo& GetLocalCnsInfo() const = 0;

	/** 功能   获得本地CNS列表
	 *  @return vector<TTPCnsInfo> CNS列表
	 */
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const = 0;

	/** 功能   更新CNS信息
	 *  @param[in] tInfo CNS信息 byIndex 消息来自哪里(0为cnc 1为维护工具)
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType) = 0;

	/** 功能   设置CNS主会场
	 *  @param[in] pbyRoomName 会场名
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetMainCns( s8* pbyRoomName ) = 0;

	/** 功能   获取CNS主会场名
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
	virtual const s8* GetMainCnsName() const = 0;
   
    /** 功能   设置系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */
    virtual u16 UpdateSysTime( const TTPTime& time ) = 0;
       
    /** 功能   获取系统时间
	 *  @return 成功返回会场名,失败返回NULL
	 *  @remarks 
	 */    
    virtual u16 ReqSysTime() = 0;

    /** 功能   获得双流源信息
	 *  @return TDualSrcInfo双流源信息
	 */
    virtual const TDualSrcInfo& GetDualSrcInfo() const = 0;

    /** 功能   获得演示源输出接口信息
	 *  @return TTPVgaMixInfo演示源输出接口信息
	 */
    virtual const TTPVgaMixInfo& GetVgaMixInfo() const = 0;

    /** 功能   选择双流源端口
	*  @param[out] emType 双流源类型
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SelDualInputPort( EmVgaType emType ) = 0;

    /** 功能   设置双流源信息
	*  @param[out] tVgaInfo 双流源信息
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault = FALSE ) = 0;

	/** 功能   更新NAT配置
	 *  @param[in] cfg NAT配置
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg,EmTpIpNameNatSyn emTpIpType) = 0;
	
	/** 功能   获得NAT配置
	 *  @return tagTTPNatCfg 网络配置信息
	 */
	virtual const TTPNatCfg& GetNATCfg() const = 0;
	
	/** 功能   设置加密
	 *  @param[in] 
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey ) = 0;
	
	/** 功能   设置系统待机信息
	*  @param[out] tTPSleepInfo 系统待机信息
	*  @return 成功返回0,失败返回非0错误码
	*/
    virtual u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo ) = 0;

	 /** 功能   获得系统待机信息
	 *  @return TTPSleepInfo 系统待机信息
	 */
    virtual const TCenDevSleepInfo& GetSysSleepInfo() const = 0;

    /**
	* 功能   白板服务器配置
	* @param [in]  dwIP	IP地址
	* @param [in] 
	* @param [in] 
	* @return u16 
	*/  
    virtual u16 SetDataServerInfoCmd( u32 dwIp ) =0 ;

	 /**
	* 功能   丢包恢复设置
	* @param [in]  emLostPackage 丢包参数
	* @return u16 
	*/  
	virtual u16 SetLostPacketCmd( EmTpLostPackageRestore emLostPackage ) = 0;

	virtual u16 SetFtpInfoRsq( const TTPFtpInfo &tTPFtpInfo ) = 0;
	
	virtual u16 SetTelInfoRsp( const TTPTelnetInfo &tTPTelnetInfo) = 0;

	//云服务器配置
	virtual u16 SetCloudServerInfo(const TTPCloudPlatServerCfg& tTpCloudServerInfo) = 0;
	virtual const TTPCloudPlatServerCfg& GetCloudServerInfo() const = 0;
};

#endif