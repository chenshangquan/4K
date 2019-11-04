#ifndef DRAGWINDOW_HEAD_H
#define DRAGWINDOW_HEAD_H 
#include "transparenBaseWnd.h"

class CDragWindow : public CTransparentBaseWnd
{
	// Construction
public:
	CDragWindow( CRect rcList, CWnd* pWnd = NULL, UINT nID = 0 );
	//CDragWindow(CWnd* pParent = NULL);   // standard constructor
		
protected:
	//{{AFX_MSG(CDragWindow)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	static CDragWindow* GetDragWindow();
	
	// 注册需要处理事件的窗口
	BOOL RegisterDropWindow( CWnd* pWnd );
	// 取消已注册的窗口
    BOOL UnRegisterDropWindow(CWnd* pWnd);		
	// 设置DragOver时一直通知的窗口	
    void SetNotifyWindow( CWnd* pWnd );
	
    /**  开始拖拽
     *  @param[in] pSrcWnd 源窗口
     *  @param[in] point 鼠标位置
     *  @param[in] pBitmap 拖拽的图片
     *  @param[in] pData 拖拽的数据
     *  @return 是否成功
     */
	BOOL BeginDrag( CWnd* pSrcWnd, CPoint point, Image* pBitmap, IData* pData = NULL );
	BOOL Draging( CPoint point );
	BOOL EndDrag( CPoint point );
    CWnd* GetSrcWnd(){ return m_pSrcWnd; }
	void ClearUserData(){ m_pUserData = NULL; }

protected:
    //获得当前所在的需要通知的窗口
    CWnd* GetActiveWindow( CPoint point );
    //拖拽时消息通知
    void ReportDragOver( CPoint point );
    
    //通知NotifyWnd
    void ReportNotifyWnd( UINT message, CPoint point );

private:	
	CWnd*   m_pLastWnd;                     //上次经过的窗口	
	IData*  m_pUserData;                    //拖拽的数据
                	
	vector<CWnd*> m_vctWnd;                 //注册的窗口	
	static CDragWindow* m_pcDragWindow;

    CPoint  m_pLastPoint;
    CWnd*   m_pSrcWnd;                      //源窗口

    CWnd*   m_pNotifyWnd;                   //DragOver时一直通知的窗口，暂时只有一个
};

#endif