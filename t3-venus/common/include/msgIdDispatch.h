/*****************************************************************************
模块名      : 消息号分配
文件名      : msgIdDispatch.h
相关文件    : 
文件实现功能: 为防止70目录下的lib和应用程序中消息号重复，在此声明消息分段
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2022 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/7/19   1.0         俞锦锦      创建
*******************************************************************************/
#pragma once

#ifndef _MSGIDDISPATCH_20110179_H_
#define _MSGIDDISPATCH_20110179_H_

//UILib 内部消息



#define UILIB_MSG_BEGIN      WM_USER + 0x100 
#define UILIB_MSG_END        UILIB_MSG_BEGIN + 0x200

//slider 放开thumb通知
#define SLIDER_RELEASED_CAPTURE UILIB_MSG_END + 0x1
//slider thumb位置变化通知
#define SLIDER_CHANGED      SLIDER_RELEASED_CAPTURE + 0x1

//UIEXLib 内部消息   
#define UIEXLIB_MSG_BEGIN   SLIDER_CHANGED + 0x1
#define UIEXLIB_MSG_END     UIEXLIB_MSG_BEGIN + 0x200


// 网真控制台内部消息  
#define CMS_MSG_BEGIN		UIEXLIB_MSG_END + 0x1
#define CMS_MSG_END         CMS_MSG_BEGIN + 0x1000 

#define UPDATECMC_MSG_BEGIN  CMS_MSG_END + 0x01
#define UPDATECMC_MSG_END    UPDATECMC_MSG_BEGIN + 0x20

//TPad内部消息
#define TPAD_MSG_BEGIN		 UPDATECMC_MSG_END + 0x1
#define TPAD_MSG_END         TPAD_MSG_BEGIN + 0x200

//UMS WEB内部消息
#define UMSWEB_MSG_BEGIN		 TPAD_MSG_END + 0x1
#define UMSWEB_MSG_END         UMSWEB_MSG_BEGIN + 0x200

#define UMSTOOL_MSG_BEGIN		 UMSWEB_MSG_END + 0x1
#define UMSTOOL_MSG_END         UMSTOOL_MSG_BEGIN + 0x200

#define CNSTOOL_MSG_BEGIN		 UMSTOOL_MSG_END + 0x1
#define CNSTOOL_MSG_END         CNSTOOL_MSG_BEGIN + 0x200

#define TPTOOL_MSG_BEGIN		 CNSTOOL_MSG_END + 0x1
#define TPTOOL_MSG_END         TPTOOL_MSG_BEGIN + 0x32

#define MOONTOOL_MSG_BEGIN     TPTOOL_MSG_END + 0x1 
#define MOONTOOL_MSG_END	  MOONTOOL_MSG_BEGIN + 0x200

#endif 