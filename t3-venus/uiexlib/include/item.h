
#ifndef ITEM_HEAD_H
#define ITEM_HEAD_H

#include "uiexBaseData.h" 
#include "iBaseItem.h"  
#include "templateClass.h"
 

class CImageItem : public IBaseItem
{
public: 
	CImageItem( Image* pImage, int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc, 
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal,
        bool bAlwaysShow = true, CPoint ptImgOffset = CPoint(0,0) );
	CImageItem( String strImageFolder, int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc, 
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal,
        bool bAlwaysShow = true, CPoint ptImgOffset = CPoint(0,0) );

	void Draw( IArgs* pArgs );
    virtual void  SetImageFolder( String strFolder );
	void SetImage( UINT nNormalImage, UINT nSelImage, const CString& strImgType, UINT nDownImage = 0 );

    void SetImageOffset( CPoint ptPoint ){ m_ptImgOffset = ptPoint; }

	IBaseItem* Clone();
    
protected:
    CPoint m_ptImgOffset;

    Image   *m_pImgNormal;	
    Image   *m_pImgDown;
    Image   *m_pImgDisable;
    Image   *m_pImgSel;
    Image   *m_pImgOver;
};

//图片居中显示的Item
class CMidImageItem : public IBaseItem
{
public:
	CMidImageItem( String strImageFolder, int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc, 
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );
	
	void Draw( IArgs* pArgs );
    void SetImageFolder( String strFolder );
 
	IBaseItem* Clone();
protected: 
    Image   *m_pImgNormal;	
    Image   *m_pImgDown;
    Image   *m_pImgDisable;
    Image   *m_pImgSel;
};

class CListItem : public IBaseItem
{
	static const String strNormalLeft;
	static const String strNormalMid;
	static const String strNormalRight;
 	static const String strFocusLeft;
 	static const String strFocusMid;
	static const String strFocusRight;
	static const String strCutLine;
public:
	CListItem( String strImageFolder, int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc, 
		String strLayout = IAlgorithm::strHori, String strSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );
	
	void Draw( IArgs* pArgs );
	virtual void SetImageFolder( String strFolder );
	void SetItemHeight( int nHeight );
	void SetImage( UINT nImgNormalLeft, UINT nImgNormalMiddle, UINT nImgNormalRight, 
		UINT nImgFocusLeft, UINT nImgFocusMiddle, UINT nImgFocusRight, UINT nImgCutLine );

	IBaseItem* Clone();
	
protected:
    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;
	
    Image   *m_pImgFocusLeft;
    Image   *m_pImgFocusMiddle;
    Image   *m_pImgFocusRight;
	Image   *m_pImgCutLine;
};

class CTextItem : public IBaseItem
{
public:
	CTextItem( String strText, int nWidht, int nHeight, Color coText = Color::Black, Color coSel = Color::Black, Font* pFont = 0, StringAlignment align = StringAlignmentCenter, StringAlignment aLinelign = StringAlignmentCenter,
		String strFunc = IBaseItem::strDefaultFunc, String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true  );
	void Draw( IArgs* pArgs );
	IBaseItem* Clone();

	void SetText( String strText ) { m_strText = strText; }
	String GetText(){ return m_strText; }
	void SetFont( Font* pFont );
	Font* GetFont(){ return m_pFont; }
	void SetFontColor( Color col ){ m_coText = col; m_coSel = col; }
	Color& GetFontColor(){ return m_coText; }
	void SetSelColor( Color col ){ m_coSel = col; }
	Color& GetSelColor(){ return m_coSel; }
	void SetAlignment( StringAlignment strAlign ) { m_Alignment = strAlign; }
	StringAlignment& GetAlignment(){ return m_Alignment; }
	void SetLineAlignment( StringAlignment strLineAlign ) { m_LineAlignment = strLineAlign; }    //设置字体垂直对齐方式
	StringAlignment& GetLineAlignment(){ return m_LineAlignment; }

    void AutoAdjustRect( HWND hWnd );  //根据文字设定Item大小
	//void CheckTextLength( CString& strText, CRect cRect, Graphics* pGraphics );

protected:
	String m_strText;
	Font* m_pFont;
	Color m_coText;
	Color m_coSel;
	StringAlignment m_Alignment;
	StringAlignment m_LineAlignment;
    String m_strFontName;
  
};

/*---------------------------------------------------------------------
* 类	名：CExTextItem
* 功    能：用于显示多行的条目
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/28	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CExTextItem : public CTextItem
{
	class CTextInfo
	{
	public:
		CTextInfo( String strText, Font* pFont, Color col, StringAlignment align ) : m_strText( strText ), m_pFont( pFont ), m_coText( col ), m_Alignment( align ){}
		String m_strText;
		Font* m_pFont;
		Color m_coText;
		StringAlignment m_Alignment;
	};
	public:
		CExTextItem( String strText, int nWidht, int nHeight, Color coText = Color::Black, Color coSel = Color::Black, Font* pFont = 0, 
			StringAlignment align = StringAlignmentCenter, StringAlignment aLinelign = StringAlignmentCenter, String strFunc = IBaseItem::strDefaultFunc,
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );
		void Draw( IArgs* pArgs );
		IBaseItem* Clone();
		void AddText( String strText, Font* pFont = 0, Color col = Color::Black, StringAlignment align = StringAlignmentCenter );
		void SetSecondText( String strText );
		//void CheckExTextLength( CString& strText, CRect cRect, StringFormat &strFormat, Graphics* pGraphics );
	protected:
		typedef vector<CTextInfo> TextInfoVec;
		TextInfoVec m_vecOtherText;
};

/*---------------------------------------------------------------------
* 类	名：CCheckItem
* 功    能：选中和非选中状态的条目
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/11/15	v1.0		肖楚然		创建
----------------------------------------------------------------------*/
class CCheckItem : public IBaseItem
{ 
	static const String strCutLine;
public:
	CCheckItem( String strImageFolder, int nWidht, int nHeight, BOOL bSel = FALSE, String strFunc = IBaseItem::strDefaultFunc, 
		String strLayout = IAlgorithm::strHori, String strSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );
	
	void Draw( IArgs* pArgs );
 
	IBaseItem* Clone();
	void Click();
    void SetImageFolder( String strFolder );
	void SetItemStatus( EmItemStatus emStatus = emItemStatusNormal );
	BOOL IsItemSel(){ return m_bSel; }
	
protected: 
    Image   *m_pImgNormal;	
    Image   *m_pImgDown;
    Image   *m_pImgDisable;
    Image   *m_pImgSel;
    Image   *m_pImgCutLine;
    BOOL    m_bSel;
};


class CButtonItem : public IBaseItem
{	
    static const String strCutLine;
	static const String strLftCutline;//左侧分割线，适用于横向列表  2012.12.20 by yjj
	static const String strRgtCutline;//右分割线，适用于横向列表  2012.12.20 by yjj
	static const String strDwnCutline;//下分割线，适用于竖向列表	
	static const String strUpCutline;//上分割线，适用于竖向列表	
public:
	CButtonItem( String strImageFolder, int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc, 
		String strLayout = IAlgorithm::strHori, String strSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );
	
	void Draw( IArgs* pArgs );
	virtual void SetImageFolder( String strFolder );
	IBaseItem* Clone();
	
protected:
    Image   *m_pImgNormal;	
    Image   *m_pImgDown;
    Image   *m_pImgDisable;
    Image   *m_pImgSel;
    Image   *m_pImgOver;
    
	Image   *m_pImgCutLine;
	Image 	*m_pRgtCutlineImg; //右分割线，适用于横向列表  2012.12.20 by yjj
	Image	*m_pLftCutlineImg; //左侧分割线，适用于横向列表  2012.12.20 by yjj
	Image	*m_pDwnCutlineImg; //下分割线，适用于竖向列表	
	Image	*m_pUpCutlineImg;  //上分割线，适用于竖向列表	
};

#endif