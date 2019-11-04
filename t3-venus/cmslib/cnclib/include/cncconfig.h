// cncconfig.h: interface for the CCncConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
#define AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncConfig : public CCncConfigIF 
{
	friend class CCnsSession;
public:
	CCncConfig(CCnsSession &cSession);
	virtual ~CCncConfig();

	//注册SIP服务
	virtual u16 RegSipService( const TTPSipRegistrarCfg& tSipCfg );
	virtual u16 UnRegSipService();
	virtual const TTPSipRegistrarCfg& GetSipRegCfg() const;


    //注册GK
    virtual u16 RegGk( const TTPGKCfg& tGkCfg );
    
 
    /** 功能   获得GK配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual  const TTPGKCfg& GetGkCfg() const ;

	//云服务器配置
	virtual u16 SetCloudServerInfo(const TTPCloudPlatServerCfg& tTpCloudServerInfo);
	virtual const TTPCloudPlatServerCfg& GetCloudServerInfo() const;

	/** 功能   更新CNS信息
	 *  @param[in] tInfo CNS信息  byIndex 消息来自哪里(0为cnc 1为维护工具)
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex ,EmTpIpNameNatSyn emTpIpType);

	virtual u16 SetMainCns( s8* pbyRoomName );

	virtual const s8* GetMainCnsName() const;

	//更新网络配置
	virtual const TTPEthnetInfo& GetEthnetCfg() const;
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg ,EmTpIpNameNatSyn emTpIpType);
	virtual u16 SaveWEthnetCfgCmd( const TTPWEthnetInfo& tTPWEthnetInfo, EmTpIpNameNatSyn emTpIpType );
	virtual const TTPCnsInfo& GetLocalCnsInfo() const;
	virtual const vector<TTPCnsInfo>& GetLocalCnsList() const;
    
	//更改NAT设置*******2012.11.1 JYY添加
	virtual u16 UpdateNATCfg( const TTPNatCfg& cfg,EmTpIpNameNatSyn emTpIpType);
	virtual const TTPNatCfg& GetNATCfg() const;

	virtual u16 SetAesEncrypCmd( const TTpEncryptKey& tEncryptKey );
	//设置系统时间
    virtual u16 UpdateSysTime( const TTPTime& time );
    //获取系统时间
    virtual u16 ReqSysTime(); 

    //设置双流源端口
    virtual u16 SelDualInputPort( EmVgaType emType );
    virtual u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault = FALSE );

    virtual const TDualSrcInfo& GetDualSrcInfo() const;
    virtual const TTPVgaMixInfo& GetVgaMixInfo() const;

	//设置系统待机端口
	virtual u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );
	virtual const TCenDevSleepInfo& GetSysSleepInfo() const;

    virtual u16 SetDataServerInfoCmd( u32 dwIp );

	virtual u16 SetLostPacketCmd( EmTpLostPackageRestore emLostPackage );

	virtual u16 SetFtpInfoRsq( const TTPFtpInfo &tTPFtpInfo );

	virtual u16 SetTelInfoRsp( const TTPTelnetInfo &tTPTelnetInfo);
protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void UpdateCnsList( TTPCnsInfo tCnsInfo );

	//消息处理
	void OnLinkBreak(const CMessage& cMsg);
	void OnCnsInfoNty(const CMessage& cMsg);
	void OnRegSipNty(const CMessage& cMsg);	
	void OnEthnetInfoInd(const CMessage& cMsg);
	void OnMainCnsInd(const CMessage& cMsg);
	//void OnCnsOnlineNty(const CMessage& cMsg);
	void OnCnsOfflineNty(const CMessage& cMsg);
    void OnSysTimeRsp(const CMessage& cMsg);
	void OnRegResultNty(const CMessage& cMsg);
	void OnRegResultFailNty(const CMessage& cMsg);
    void OnRegGkRsp(const CMessage& cMsg);
    void OnRegGkNty(const CMessage& cMsg);

	void OnSysSleepNty(const CMessage& cMsg);
	void OnRegNatNty(const CMessage& cMsg);
    void OnSetDualPortNameInd(const CMessage& cMsg);
    void OnSelDualInputPortInd(const CMessage& cMsg);
    void OnVgaInfoNty(const CMessage& cMsg);
    void OnConfVgaInfoNty(const CMessage& cMsg);
	void OnEncryptionInd( const CMessage &cMsg );
	void OnLostPackageInd( const CMessage &cMsg );

	//双网口和网口备份
	void OnSetCfgWEthnetNty( const CMessage &cMsg );
	void OnSetCfgWEthnetRsp( const CMessage &cMsg );
	void OnSetCfgEthnetStateNty( const CMessage &cMsg );

	//云平台服务器配置
    void OnSetCloudServerInd(const CMessage& cMsg);
    void OnSetCloudServerNty(const CMessage& cMsg);
private:
	CCnsSession        *m_pSession;
	TTPEthnetInfo       m_tEthnetInfo;       //网络信息
	TTPSipRegistrarCfg  m_tSipCfg;           //SIP注册信息
	TTPCnsInfo          m_tLocalCnsInfo;     //本地CNS信息
	vector<TTPCnsInfo>  m_vctCnsList;        //本CNS列表
	s8                  m_achMainRoom[TP_MAX_ALIAS_LEN+1];  //主会场名
    TTPGKCfg            m_tGkCfg;            //GK配置
    TDualSrcInfo        m_tDualSrcInfo;      //双流源信息
	TCenDevSleepInfo    m_tCenDevSleepInfo;  //系统待机信息
	TTPNatCfg			m_tNATCfg;			 //NAT信息
	TTPVgaMixInfo       m_tVgaMixInfo;       //演示源输出接口信息
    TTPCloudPlatServerCfg	m_tTpCloudServerInfo;//云平台配置信息
};

#endif // !defined(AFX_CNCCONFIG_H__40492EAF_0B43_4101_A0B9_FDD4C21B1D4A__INCLUDED_)
