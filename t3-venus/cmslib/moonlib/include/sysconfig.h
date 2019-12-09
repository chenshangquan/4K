// sysconfig.h: interface for the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SYSCONFIG_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_SYSCONFIG_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rkcSession.h"

class CSysConfig : public CSysConfigIF 
{  
    friend class CRkcSession;
/** @defgroup  操作用户接口实现部分
 *  @{
 */
public:

    CSysConfig( CRkcSession &cSession );
	virtual ~CSysConfig();

	//更新网络配置
	virtual const TTPEthnetInfo& GetEthnetCfg() const;

	/** 
	* 功能  输出视频格式设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode );

	/** 
	* 功能 图片翻转格式设置
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust );

	virtual u16 UpdateEthnetCfg( const TRK100NetParam& cfg );

    //获取网络配置
    virtual u16 GetNetWorkConfig();
    //获取网络配置内容
    virtual u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);

	virtual	u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate );

    //获取软件版本
    virtual u16 GetVersionInfo();

protected:
 
	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 

    void OnLinkBreak(const CMessage& cMsg);

	void OnSoftWareVerInfoNty(const CMessage& cMsg);

	void OnCamOutputInfoNty(const CMessage& cMsg);

	void OnCamImageAdjustNty(const CMessage& cMsg);

	void OnEthnetInfoInd(const CMessage& cMsg);

	void OnCamOutputInfoInd(const CMessage& cMsg);

	void OnCamImageAdjustInd(const CMessage& cMsg);

	void OnLVDBaudInd( const CMessage& cMsg );
	
	void OnLVDBaudNty( const CMessage& cMsg );

    void OnGetNetWorkConfigRsp( const CMessage& cMsg );

private:
 
	/**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();
   
private:
	CRkcSession *m_pSession; 
	TTPEthnetInfo m_tEthnetInfo;       //网络信息
    TRK100NetParam          m_tRK100NetParam;           //网络参数
/** @}*/ // 操作用户接口实现部分
};

#endif // !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
