/*****************************************************************************
模块名      : UICommonDef
文件名      : UICommonDef.h
相关文件    : 
文件实现功能: 界面库中公共预定义文件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/26      1.0         刘德印      创建
******************************************************************************/
#ifndef _UICOMMONDEF_H_
#define _UICOMMONDEF_H_

namespace DuiLib {
	/////////////////////////////////////////////////////////////////////////////////////
	//
enum EM_TIMER_ID
{
	TIMER_ID_DRAGWNDLIST = 200,       //点击CommonListUI绘制拖拽窗口定时器    收到UP后KillTimer
	TIMER_ID_REDRAWPREVIEW,

};

#define IMAGE_FILE_EXT _T(".bmp.jpg.jpeg.png.gif.svg.tiff.emf.dib")   // 图片类型的转换支持：bmp、dib、png、gif、jpeg/jpg、tiff、emf等

#define SAFE_RELEASE( X ) { if( X ) { delete X; X = NULL; } }
#define SAFE_RELEASE_ARRAY( X ) { if( X ) { delete[] X; X = NULL; } }

};

#endif