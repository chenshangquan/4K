/*****************************************************************************
模块名      : UICommon
文件名      : UICommon.h
相关文件    : 
文件实现功能: 界面库中通用工具函数类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/6/06      1.0         刘德印      创建
******************************************************************************/
#ifndef __UICOMMON_H__
#define __UICOMMON_H__

namespace DuiLib {
//////////////////////////////////////////////////////////////////////////
//	公共函数类
typedef std::map<tString, Image*> ImageMap;
class UILIB_API CUICommon
{
	CUICommon();
	virtual ~CUICommon();

public:

	static BOOL IsImgFile( LPCTSTR szFile );				//检查文件是否为图片
	static TImageInfo* GetImgInfo( LPCTSTR szImgFile );		//获取图片信息（宽 高等）

	static Image* GetImage( tString strPath, BOOL bNewCreate = FALSE );

private:
/*
 *  全局的一个共享区，有些图片不需要加载多次\n 
 */

	static ImageMap m_mapImages;


};




};

#endif