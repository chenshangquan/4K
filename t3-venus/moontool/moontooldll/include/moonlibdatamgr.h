/*****************************************************************************
模块名      : 窗口相关的cnclib数据模块
文件名      : cnclibdatamgr.h
相关文件    : cnclib.h
文件实现功能: 转发来自cnclib的消息，提供访问cnclib的接口
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0						创建
******************************************************************************/
#include "moonToolDll.h"
#include "rkclib.h"
#include "msgdispatch.h"
#include "sessionmgr.h"

#ifndef CMOONLIBDATAMGR_H
#define CMOONLIBDATAMGR_H

class CMoonlibDataMgr : public CWnd
{
public:

	~CMoonlibDataMgr();
	/** 功能   初始化CCnclibDataMgr类
	*  @param[out]
	*  @return 
	*/
	void InitDataMgr();
	       
    	
	/** 功能   获得CCnclibDataMgr自身的指针
	*  @param[in] 
	*  @return 成功返回CCnclibDataMgr类型的指针
	*/
	static CMoonlibDataMgr* GetDataMgrIF();

	/**
	* 功能:	获取登录cns的IP
	*  @param[in] u32  IP
	*  @return  
    */
	u16 GetLoginIp( u32 &dwIP )const;

	/** 
	* 功能  获取摄像机参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamCfg( TTPMoonCamInfo &tMoonCameraCfg )const;

    /** 
	* 功能  设置所有机芯参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 SetAllCamCfg( TTPMoonCamInfo tCamInfo[] )const;

    /** 
	* 功能  获取所有机芯参数
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetAllCamCfg( TTPMoonCamInfo* ptCamInfo[] )const;

    u16 GetCurStatus( BOOL& bSetAllCamCfg )const;

    // 获取输出制式参数
    u16 GetOutputFormat( TPOutputFmt &tPOutputFmt )const;

	u16 GetCamZoom( u32& dwZoom )const;

	u16 GetExtCamZoom( u32& dwZoomPos )const;

	/** 
	* 功能  获取被选中的摄像机
	* @param [in] 	 
	* @return  成功返回0,失败返回非0错误码
	*/		
	u16 GetCamSel( u8& byCameraIndx )const;

	/** 
	* 功能  	获取曝光模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamMoonMode( EmTPMOOMMode& emExpMode )const;

	/** 
	* 功能  	获取光圈值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamAperture(EmTPAperture &emAper) const;

	/** 
	* 功能  	获取增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamGain(EmTPExpGain &emGain) const;

	/** 
	* 功能  	获取快门值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamShutSpd(TPSOrThShutter &tTPSOrThShutSpd) const;

	u16 GetTwCamShutSpd(TPFOrTwShutter &tTPFOrTwShutSpd) const;

	/** 
	* 功能 获取红色增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamRGain(u32& dwRGain) const;

	/** 
	* 功能 获取蓝色增益值
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamBGain(u32& dwBGain) const;

	u16 GetCamAdjustRange(u32 &dwAdjustRange) const;

	u16 GetCamHoriStretch(u32 &dwHoriStretch) const;

	/** 
	* 功能 获取白平衡模式
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamWBMode( EmTPMOOMMode& emWBMode )const;

	/** 
	* 功能 获取IP信息
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetEthnetCfg( TTPEthnetInfo &tEthnetInfo );

	TTPCamPre* GetCamPreInfo();


protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
private:
	CMoonlibDataMgr();

private:
	static CMoonlibDataMgr* m_pThis;
};

#define MOONLIBDATAMGRPTR   CMoonlibDataMgr::GetDataMgrIF()

#endif