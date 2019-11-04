#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//
const static LPCTSTR pTopleft = _T("list_topleft.png");
const static LPCTSTR pTopmiddle = _T("list_topmiddle.png");
const static LPCTSTR pTopright = _T("list_topright.png");
const static LPCTSTR pMiddleleft = _T("list_middleleft.png");
const static LPCTSTR pMiddleright = _T("list_middleright.png");
const static LPCTSTR pBottomleft = _T("list_bottomleft.png");
const static LPCTSTR pBottommiddle = _T("list_bottommiddle.png");
const static LPCTSTR pBottomright = _T("list_bottomright.png");

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);
class CContainerUI;
class UILIB_API CControlUI
{
public:
    CControlUI();
    virtual ~CControlUI();

public:
    virtual /*CStdString*/tString GetName() const;
    virtual void SetName(LPCTSTR pstrName);
    virtual LPCTSTR GetClass() const;
    virtual LPVOID GetInterface(LPCTSTR pstrName);
    virtual UINT GetControlFlags() const;

    virtual bool Activate();
    virtual CPaintManagerUI* GetManager() const;
    virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
    virtual CControlUI* GetParent() const;

    // 文本相关
    virtual CStdString GetText() const;
    virtual void SetText(LPCTSTR pstrText);

    // 图形相关
    DWORD GetBkColor() const;
    void SetBkColor(DWORD dwBackColor);
    DWORD GetBkColor2() const;
    void SetBkColor2(DWORD dwBackColor);
    DWORD GetBkColor3() const;
    void SetBkColor3(DWORD dwBackColor);
    /*virtual*/ LPCTSTR GetBkImage();
    /*virtual*/ void SetBkImage(LPCTSTR pStrImage);
    DWORD GetBorderColor() const;
    void SetBorderColor(DWORD dwBorderColor);
	DWORD GetFocusBorderColor() const;
	void SetFocusBorderColor(DWORD dwBorderColor);
    bool IsColorHSL() const;
    void SetColorHSL(bool bColorHSL);
    int GetBorderSize() const;
    void SetBorderSize(int nSize);
    SIZE GetBorderRound() const;
    void SetBorderRound(SIZE cxyRound);
	void SetImageInfo(LPCTSTR pStrImage);

	//bool xtiled 水平拉伸   bool ytiled 垂直拉伸  默认false为拉伸 by ldy 2013.06.06
    bool DrawImage( HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL, bool bTiledX = false, bool bTiledY = false );

	//bool bRepeatDraw 重复绘制(若重复绘制，需手动调用SetImageInfo，避免多次获取图片信息)
	bool DrawImageGDIPlus( HDC hDC, TEventUI& event, CPoint ptInCtl = CPoint( 0, 0), bool bRepeatDraw = true, LPCTSTR pStrImage = NULL, bool bSuportGesture = false );

	//支持图片拼接(边框八张图片)  //by xhx
	virtual void DrawImageMosaicBk( HDC hDC );

	//由左中右三张图标 拼接 为一张图片   bDrawCorner 是否需要画边角  //by xhx
	BOOL MosaicHoriImage( HDC hDC, LPCTSTR pstrImgLeft, LPCTSTR pstrImgRight, LPCTSTR pstrImgMiddle, int nFixedWidth, BOOL bDrawCorner = TRUE, CPoint ptInCtl = CPoint( 0, 0) );

	//由上中下 三张图标 拼接 为一张图片  bDrawCorner 是否需要画边角  //by xhx
	BOOL MosaicVertImage( HDC hDC, LPCTSTR pstrImgTop, LPCTSTR pstrImgBottom, LPCTSTR pstrImgMiddle, int nFixedHeight, BOOL bDrawCorner = TRUE, CPoint ptInCtl = CPoint( 0, 0) );

    // 位置相关
    virtual const RECT& GetPos() const;
    virtual void SetPos(RECT rc);
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual int GetX() const;
    virtual int GetY() const;
    virtual RECT GetPadding() const;
    virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
    virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedXY(SIZE szXY);      // 仅float为true时有效
    virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedWidth(int cx);      // 预设的参考值
    virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
    virtual void SetFixedHeight(int cy);     // 预设的参考值
    virtual int GetMinWidth() const;
    virtual void SetMinWidth(int cx);
    virtual int GetMaxWidth() const;
    virtual void SetMaxWidth(int cx);
    virtual int GetMinHeight() const;
    virtual void SetMinHeight(int cy);
    virtual int GetMaxHeight() const;
    virtual void SetMaxHeight(int cy);
    virtual void SetRelativePos(SIZE szMove,SIZE szZoom);
    virtual void SetRelativeParentSize(SIZE sz);
    virtual TRelativePosUI GetRelativePos() const;
    virtual bool IsRelativePos() const;

    // 鼠标提示
    virtual CStdString GetToolTip() const;
    virtual void SetToolTip(LPCTSTR pstrText);

    // 快捷键
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut(TCHAR ch);

    // 菜单
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed(bool bMenuUsed);

    // 用户属性
    virtual UINT_PTR GetTag() const;						// 附加数据，供用户使用
    virtual void SetTag(UINT_PTR pTag);						// 附加数据，供用户使用      line by ldy 130723: 对于列表则为点击ITEM数据

    // 一些重要的属性
    virtual bool IsVisible() const;
    virtual void SetVisible(bool bVisible = true);
    virtual void SetInternVisible(bool bVisible = true);	// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    virtual bool IsEnabled() const;
    virtual void SetEnabled(bool bEnable = true);
    virtual bool IsMouseEnabled() const;
    virtual void SetMouseEnabled(bool bEnable = true);
    virtual bool IsFocused() const;
    virtual void SetFocus();
    virtual bool IsFloat() const;
    virtual void SetFloat(bool bFloat = true);

	virtual bool IsGesture() const;
	virtual void SetGesture(bool bGetture = false);

	void SetMosaicBk(bool bIsMosaicBk){ m_bIsMosaicBk = bIsMosaicBk;};
	bool GetMosaicBk(){return m_bIsMosaicBk;};

	void SetScrollVisible(bool bVisible){ m_bScrollVisible = bVisible; };
	bool GetScrollVisible(){ return m_bScrollVisible; };


    virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

    void Invalidate();
    bool IsUpdateNeeded() const;
    void NeedUpdate();
    void NeedParentUpdate();
    DWORD GetAdjustColor(DWORD dwColor);

    virtual void Init();
    virtual void DoInit();

    virtual void Event(TEventUI& event);
    virtual void DoEvent(TEventUI& event);

    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    CControlUI* ApplyAttributeList(LPCTSTR pstrList);

    virtual SIZE EstimateSize(SIZE szAvailable);

    virtual void DoPaint(HDC hDC, const RECT& rcPaint);
    virtual void PaintBkColor(HDC hDC);
    virtual void PaintBkImage(HDC hDC);
    virtual void PaintStatusImage(HDC hDC);
    virtual void PaintText(HDC hDC);
    virtual void PaintBorder(HDC hDC);

    virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);


	//得到控件rect
	void SetControlRect(RECT rc){ m_rcItem= rc; };
	RECT GetControlRect(){ return m_rcItem;};
	RECT GetControlPaintRect(){ return m_rcPaint;};	

	//TImageInfo* GetScrollBkImgInfo(){return m_ImgInfoTop;};
	

public:
    CEventSource OnInit;
    CEventSource OnDestroy;
    CEventSource OnSize;
    CEventSource OnEvent;
    CEventSource OnNotify;

protected:

	//触摸消息处理分发   2013.07.24 by ldy
	virtual void OnGestureBeg( TEventUI& event );			//POINT ptFrom
	virtual void OnGestureEnd( TEventUI& event );			//POINT ptFrom
	virtual BOOL OnGestureZoom( TEventUI& event );			//POINT ptCenter, long lDelta
	virtual BOOL OnGesturePan( TEventUI& event );			//POINT ptFrom, POINT ptTo
	virtual BOOL OnGestureRotate( TEventUI& event );		//POINT ptCenter, double dblAngle
	virtual BOOL OnGestureTwoFingerTap( TEventUI& event );	//POINT ptCenter
	virtual BOOL OnGesturePressAndTap( TEventUI& event );	//POINT ptFirstFinger, long lDelta


protected:
	CPaintManagerUI* m_pManager;
	CControlUI* m_pParent;
	CStdString m_sName;
	bool m_bUpdateNeeded;
	bool m_bMenuUsed;
	RECT m_rcItem;
	RECT m_rcPadding;
	SIZE m_cXY;
	SIZE m_cxyFixed;
	SIZE m_cxyMin;
	SIZE m_cxyMax;
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bEnabled;
	bool m_bMouseEnabled;
	bool m_bFocused;
	bool m_bFloat;
    bool m_bSetPos; // 防止SetPos循环调用
    TRelativePosUI m_tRelativePos;

    CStdString m_sText;
    CStdString m_sToolTip;
    TCHAR m_chShortcut;
    CStdString m_sUserData;
    UINT_PTR m_pTag;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    CStdString m_sBkImage;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
    bool m_bColorHSL;
    int m_nBorderSize;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;

	bool m_bGesture;

	bool m_bIsMosaicBk;     //绘制背景是否采用拼接
	bool m_bScrollVisible;  //滚动条是否可见
	TImageInfo* m_ptImageInfo;
	Image* m_pImage;    
};

} // namespace DuiLib

#endif // __UICONTROL_H__
