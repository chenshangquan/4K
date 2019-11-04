/*****************************************************************************
模块名      : CPreWnd
文件名      : PreWnd.h
相关文件    : 
文件实现功能: 预览窗口（包含预览器所支持的ppt pdf xls png jpg txt等文件）(WS_CHILD)
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/6/03      1.0         刘德印      创建
******************************************************************************/
#ifndef PREWND_H
#define PREWND_H

class CBaseWindowWnd;
class UILIB_API CPreWnd : public CBaseWindowWnd
{
public:
	CPreWnd(CPaintManagerUI& paint_manager);
	LPCTSTR GetWindowClassName() const;
	virtual LRESULT OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled );
	virtual const TCHAR* GetSkinFile();

	void Init();
	void Notify(TNotifyUI& msg);


	 /*****************************************************************************
	* 功能:			显示prewnd窗口
	* @param		[in]	TRUE：显示     FALSE：隐藏
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	void ShowWnd(bool bShow = true);	

	 /*****************************************************************************
	* 功能:			移动prewnd窗口位置
	* @param		[in]	目标窗口位置POINT
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	void MoveWnd(POINT pt);		

	 /*****************************************************************************
	* 功能:			资源文件绘制
	* @param		[in]	const tString& strFile:文件路径
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/6/5       1.0         刘德印      创建
    ******************************************************************************/
	void Draw(const tString& strFile);

	 /*****************************************************************************
	* 功能:			显示图片
	* @param		[in]	const tString& strFile:文件路径
	* @param		[in]	BOOL bShow: TRUE 显示，FLASE 隐藏
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/6/5       1.0         刘德印      创建
    ******************************************************************************/
	void ShowImage( const tString& strFile, BOOL bShow = TRUE );

	void SetMainFrameWnd(HWND hWnd);

	void SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI);

	void ShowPageDown( const tString& strFile );

protected:
	CPaintManagerUI& m_cPaintMng;

private:
	HWND m_hWndMain;
	CPreviewIF g_clsPreview;	//预览接口

	CommonScrollContainerUI* m_pScrollContainerUI; 
	
	CLabelUI* m_pShowImgLabelUI;
};

#endif // PREWND_H