/*****************************************************************************
模块名      : moon90 moonlib接口
文件名      : sysconfigif.h
相关文件    : 
文件实现功能: 系统设置
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2014/11/26  1.0         吴蒨蒨        创建
******************************************************************************/
#ifndef __SYSCONFIGIF_H__
#define __SYSCONFIGIF_H__

#include "kdvdispevent.h"
#include "moonstruct.h"
#include <vector>

class CSysConfigIF : public CKdvDispEvent
{
public:
	
	/** 功能   获得网络配置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual const TTPEthnetInfo& GetEthnetCfg() const = 0;

	/** 功能   视频输出格式设置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode ) = 0;

	/** 功能   图片翻转格式设置
	 *  @return tagTTPEthnetInfo 网络配置信息
	 */
	virtual u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust ) = 0;

	/** 功能   更新网络配置
	 *  @param[in] cfg 网络配置
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg ) = 0;
	/** 功能   设置LVDS波特率
	 *  @param[in] emBaudRate 波特率
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate ) = 0;
};

#endif