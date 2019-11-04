#ifndef __UICOMMONCONTROLS_H__
#define __UICOMMONCONTROLS_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CLabelUI : public CControlUI
{
public:
    CLabelUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

    void SetTextStyle(UINT uStyle);
	UINT GetTextStyle() const;
    void SetTextColor(DWORD dwTextColor);
	DWORD GetTextColor() const;
    void SetDisabledTextColor(DWORD dwTextColor);
	DWORD GetDisabledTextColor() const;
    void SetFont(int index);
	int GetFont() const;
    RECT GetTextPadding() const;
    void SetTextPadding(RECT rc);
    bool IsShowHtml();
    void SetShowHtml(bool bShowHtml = true);

    SIZE EstimateSize(SIZE szAvailable);
    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void PaintText(HDC hDC);

	TCHAR* GetImage(){return m_chImage;};
	void SetImage( LPCTSTR pStrImage, bool bStretch = false );

	void PaintBkImage(HDC hDC);
	void SetLabelHorMosaic(bool bMosaic){ m_bIsLabelHorMosaic = bMosaic; };
	bool GetLabelHorMosaic(){ return m_bIsLabelHorMosaic; };

protected:
    DWORD m_dwTextColor;
    DWORD m_dwDisabledTextColor;
    int m_iFont;
    UINT m_uTextStyle;
    RECT m_rcTextPadding;
    bool m_bShowHtml;

	bool m_bTiledX;
	bool m_bTiledY;

	TCHAR m_chImage[MAX_PATH];

	bool m_bIsLabelHorMosaic;
	int  m_nLabelMosaicPos;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CListIconUI : public CLabelUI
{
public:
	CListIconUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	bool Activate();

	void PaintBkImage(HDC hDC);

	void SetLabelIndex(int nIndex){ m_nIndex = nIndex; };
	int GetLabelIndex(){ return m_nIndex; };
	void SetLabelSelState(bool bSelState);
	bool GetLabelSelState(){ return m_bSelState; };

	tString GetItemName(){return m_strItemName;};
	void SetItemName(const tString& strItemName){ m_strItemName = strItemName; };

	void SetManagerUI(CPaintManagerUI* pManageUI){ m_pManageUI = pManageUI;};

protected:
	TCHAR m_chSelImage[MAX_PATH];
	tString m_strItemName;
	int m_nIndex; 
	bool m_bSelState;

	CPaintManagerUI* m_pManageUI;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CButtonUI : public CLabelUI
{
public:
    CButtonUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

    bool Activate();
    void SetEnabled(bool bEnable = true);
    void DoEvent(TEventUI& event);

    LPCTSTR GetNormalImage();
    void SetNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetHotImage();
    void SetHotImage(LPCTSTR pStrImage);
    LPCTSTR GetPushedImage();
    void SetPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetFocusedImage();
    void SetFocusedImage(LPCTSTR pStrImage);
    LPCTSTR GetDisabledImage();
    void SetDisabledImage(LPCTSTR pStrImage);

    void SetHotTextColor(DWORD dwColor);
	DWORD GetHotTextColor() const;
    void SetPushedTextColor(DWORD dwColor);
	DWORD GetPushedTextColor() const;
    void SetFocusedTextColor(DWORD dwColor);
	DWORD GetFocusedTextColor() const;
    SIZE EstimateSize(SIZE szAvailable);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintText(HDC hDC);
    void PaintStatusImage(HDC hDC);

protected:
    UINT m_uButtonState;

	DWORD m_dwHotTextColor;
	DWORD m_dwPushedTextColor;
	DWORD m_dwFocusedTextColor;

    CStdString m_sNormalImage;
    CStdString m_sHotImage;
    CStdString m_sPushedImage;
    CStdString m_sFocusedImage;
    CStdString m_sDisabledImage;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API COptionUI : public CButtonUI
{
public:
    COptionUI();
    ~COptionUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);

    bool Activate();
    void SetEnabled(bool bEnable = true);

    LPCTSTR GetSelectedImage();
    void SetSelectedImage(LPCTSTR pStrImage);
	
	void SetSelectedTextColor(DWORD dwTextColor);
	DWORD GetSelectedTextColor();
		
	LPCTSTR GetForeImage();
	void SetForeImage(LPCTSTR pStrImage);

    LPCTSTR GetGroup() const;
    void SetGroup(LPCTSTR pStrGroupName = NULL);
    bool IsSelected() const;
    void Selected(bool bSelected);

    SIZE EstimateSize(SIZE szAvailable);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void PaintStatusImage(HDC hDC);
	void PaintText(HDC hDC);

protected:
    bool m_bSelected;
    CStdString m_sGroupName;

	DWORD m_dwSelectedTextColor;

    CStdString m_sSelectedImage;
	CStdString m_sForeImage;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CTextUI : public CLabelUI
{
public:
    CTextUI();
    ~CTextUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    CStdString* GetLinkContent(int iIndex);

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);

    void PaintText(HDC hDC);

protected:
    enum { MAX_LINK = 8 };
    int m_nLinks;
    RECT m_rcLinks[MAX_LINK];
    CStdString m_sLinks[MAX_LINK];
    int m_nHoverLink;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CProgressUI : public CLabelUI
{
public:
    CProgressUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    bool IsHorizontal();
    void SetHorizontal(bool bHorizontal = true);
    int GetMinValue() const;
    void SetMinValue(int nMin);
    int GetMaxValue() const;
    void SetMaxValue(int nMax);
	int GetValue() const;
	void SetValue(int nValue);
    LPCTSTR GetForeImage() const;
    void SetForeImage(LPCTSTR pStrImage);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    void PaintStatusImage(HDC hDC);

protected:
    bool m_bHorizontal;
    int m_nMax;
    int m_nMin;
    int m_nValue;

    CStdString m_sFgImage;
    CStdString m_sFgImageModify;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSliderUI : public CProgressUI
{
public:
    CSliderUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetEnabled(bool bEnable = true);

    int GetChangeStep();
    void SetChangeStep(int step);
    void SetThumbSize(SIZE szXY);
    RECT GetThumbRect() const;
    LPCTSTR GetThumbImage() const;
    void SetThumbImage(LPCTSTR pStrImage);
    LPCTSTR GetThumbHotImage() const;
    void SetThumbHotImage(LPCTSTR pStrImage);
    LPCTSTR GetThumbPushedImage() const;
    void SetThumbPushedImage(LPCTSTR pStrImage);

    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    void PaintStatusImage(HDC hDC);

protected:
    SIZE m_szThumb;
    UINT m_uButtonState;
    int m_nStep;

    CStdString m_sThumbImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;

    CStdString m_sImageModify;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CEditWnd;

class UILIB_API CEditUI : public CLabelUI
{
    friend CEditWnd;
public:
    CEditUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;

    void SetEnabled(bool bEnable = true);
    void SetText(LPCTSTR pstrText);
    void SetMaxChar(UINT uMax);
    UINT GetMaxChar();
    void SetReadOnly(bool bReadOnly);
    bool IsReadOnly() const;
    void SetPasswordMode(bool bPasswordMode);
    bool IsPasswordMode() const;
    void SetPasswordChar(TCHAR cPasswordChar);
    TCHAR GetPasswordChar() const;

    LPCTSTR GetNormalImage();
    void SetNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetHotImage();
    void SetHotImage(LPCTSTR pStrImage);
    LPCTSTR GetFocusedImage();
    void SetFocusedImage(LPCTSTR pStrImage);
    LPCTSTR GetDisabledImage();
    void SetDisabledImage(LPCTSTR pStrImage);
    void SetNativeEditBkColor(DWORD dwBkColor);
    DWORD GetNativeEditBkColor() const;

    void SetPos(RECT rc);
    void SetVisible(bool bVisible = true);
    void SetInternVisible(bool bVisible = true);
    SIZE EstimateSize(SIZE szAvailable);
    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void PaintStatusImage(HDC hDC);
    void PaintText(HDC hDC);

protected:
    CEditWnd* m_pWindow;

    UINT m_uMaxChar;
    bool m_bReadOnly;
    bool m_bPasswordMode;
    TCHAR m_cPasswordChar;
    UINT m_uButtonState;
    CStdString m_sNormalImage;
    CStdString m_sHotImage;
    CStdString m_sFocusedImage;
    CStdString m_sDisabledImage;
    DWORD m_dwEditbkColor;
};

/////////////////////////////////////////////////////////////////////////////////////
//
const static LPCTSTR pBkgBottom = _T("scroll_bkg_bottom.png");
const static LPCTSTR pBkgMiddle = _T("scroll_bkg_middle.png");
const static LPCTSTR pBkgTop = _T("scroll_bkg_top.png");

const static LPCTSTR pDownBottom = _T("scroll_down_bottom.png");
const static LPCTSTR pDownMiddle = _T("scroll_down_middle.png");
const static LPCTSTR pDownTop = _T("scroll_down_top.png");

const static LPCTSTR pNormalBottom = _T("scroll_normal_bottom.png");
const static LPCTSTR pNormalMiddle = _T("scroll_normal_middle.png");
const static LPCTSTR pNormalTop = _T("scroll_normal_top.png");

const static LPCTSTR pNormalBtn1 = _T("scroll_normal_btn1.png");
const static LPCTSTR pDownBtn1 = _T("scroll_down_btn1.png");
const static LPCTSTR pNormalBtn2 = _T("scroll_normal_btn2.png");
const static LPCTSTR pDownBtn2 = _T("scroll_down_btn2.png");

class UILIB_API CScrollBarUI : public CControlUI
{
public:
    CScrollBarUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    CContainerUI* GetOwner() const;
    void SetOwner(CContainerUI* pOwner);

    void SetEnabled(bool bEnable = true);
    void SetFocus();

    bool IsHorizontal();
    void SetHorizontal(bool bHorizontal = true);
    int GetScrollRange() const;
    void SetScrollRange(int nRange);
    int GetScrollPos() const;
    void SetScrollPos(int nPos);
    int GetLineSize() const;
    void SetLineSize(int nSize);

    bool GetShowButton1();
    void SetShowButton1(bool bShow);
    LPCTSTR GetButton1NormalImage();
    void SetButton1NormalImage(LPCTSTR pStrImage);
    LPCTSTR GetButton1HotImage();
    void SetButton1HotImage(LPCTSTR pStrImage);
    LPCTSTR GetButton1PushedImage();
    void SetButton1PushedImage(LPCTSTR pStrImage);
    LPCTSTR GetButton1DisabledImage();
    void SetButton1DisabledImage(LPCTSTR pStrImage);

    bool GetShowButton2();
    void SetShowButton2(bool bShow);
    LPCTSTR GetButton2NormalImage();
    void SetButton2NormalImage(LPCTSTR pStrImage);
    LPCTSTR GetButton2HotImage();
    void SetButton2HotImage(LPCTSTR pStrImage);
    LPCTSTR GetButton2PushedImage();
    void SetButton2PushedImage(LPCTSTR pStrImage);
    LPCTSTR GetButton2DisabledImage();
    void SetButton2DisabledImage(LPCTSTR pStrImage);

    LPCTSTR GetThumbNormalImage();
    void SetThumbNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetThumbHotImage();
    void SetThumbHotImage(LPCTSTR pStrImage);
    LPCTSTR GetThumbPushedImage();
    void SetThumbPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetThumbDisabledImage();
    void SetThumbDisabledImage(LPCTSTR pStrImage);

    LPCTSTR GetRailNormalImage();
    void SetRailNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetRailHotImage();
    void SetRailHotImage(LPCTSTR pStrImage);
    LPCTSTR GetRailPushedImage();
    void SetRailPushedImage(LPCTSTR pStrImage);
    LPCTSTR GetRailDisabledImage();
    void SetRailDisabledImage(LPCTSTR pStrImage);

    LPCTSTR GetBkNormalImage();
    void SetBkNormalImage(LPCTSTR pStrImage);
    LPCTSTR GetBkHotImage();
    void SetBkHotImage(LPCTSTR pStrImage);
    LPCTSTR GetBkPushedImage();
    void SetBkPushedImage(LPCTSTR pStrImage);
	LPCTSTR GetBkDisabledImage();
	void SetBkDisabledImage(LPCTSTR pStrImage);

	//////////////////////////////////////////////////////////////////////////
	LPCTSTR GetMosaicSliderImage();
	void SetMosaicSliderImage(LPCTSTR pStrImage);

	//////////////////////////////////////////////////////////////////////////

    void SetPos(RECT rc);
    void DoEvent(TEventUI& event);
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void DoPaint(HDC hDC, const RECT& rcPaint);

    void PaintBk(HDC hDC);
    void PaintButton1(HDC hDC);
    void PaintButton2(HDC hDC);
    void PaintThumb(HDC hDC);
    void PaintRail(HDC hDC);

	//////////////////////////////////////////////////////////////////////////
	//支持图片拼接的滚动条  //by xhx
	void PreDrawMosaicScroll();
	void PaintScrollBk(HDC hDC);
	void PaintScrollThumb(HDC hDC);
	void PaintScrollButton1(HDC hDC);
	void PaintScrollButton2(HDC hDC);

protected:

    enum { 
        DEFAULT_SCROLLBAR_SIZE = 16,
        DEFAULT_TIMERID = 10,
    };

    bool m_bHorizontal;
    int m_nRange;
    int m_nScrollPos;
    int m_nLineSize;
    CContainerUI* m_pOwner;
    POINT ptLastMouse;
    int m_nLastScrollPos;
    int m_nLastScrollOffset;
    int m_nScrollRepeatDelay;

    CStdString m_sBkNormalImage;
    CStdString m_sBkHotImage;
    CStdString m_sBkPushedImage;
    CStdString m_sBkDisabledImage;

    bool m_bShowButton1;
    RECT m_rcButton1;
    UINT m_uButton1State;
    CStdString m_sButton1NormalImage;
    CStdString m_sButton1HotImage;
    CStdString m_sButton1PushedImage;
    CStdString m_sButton1DisabledImage;

    bool m_bShowButton2;
    RECT m_rcButton2;
    UINT m_uButton2State;
    CStdString m_sButton2NormalImage;
    CStdString m_sButton2HotImage;
    CStdString m_sButton2PushedImage;
    CStdString m_sButton2DisabledImage;

    RECT m_rcThumb;
    UINT m_uThumbState;
    CStdString m_sThumbNormalImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;
    CStdString m_sThumbDisabledImage;

    CStdString m_sRailNormalImage;
    CStdString m_sRailHotImage;
    CStdString m_sRailPushedImage;
    CStdString m_sRailDisabledImage;

    CStdString m_sImageModify;

	//////////////////////////////////////////////////////////////////////////
	tString m_strBkgBottom;
	tString m_strBkgMiddle;
	tString m_strBkgTop;

	tString m_strDownBottom;
	tString m_strDownMiddle;
	tString m_strDownTop;

	tString m_strNormalBottom;
	tString m_strNormalMiddle;
	tString m_strNormalTop;

	tString m_strNormalBtn1;
	tString m_strDownBtn1;
	tString m_strNormalBtn2;
	tString m_strDownBtn2;

	tString m_strMosaicSliderImg;

	//bool m_bIsInitialized;

	//bool m_bIsMosaicSlider;     //绘制滑动条是否采用拼接
};

} // namespace DuiLib

#endif // __UICOMMONCONTROLS_H__

