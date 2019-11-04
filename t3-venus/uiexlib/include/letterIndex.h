#ifndef LETTERINDEX_HEAD_H
#define LETTERINDEX_HEAD_H
#include "transparenBaseWnd.h"


#define LETTER_NUM   26

class CLetterIndex : public CTransparentBaseWnd
{
	// Construction
public:
	const static CString strBkg;
	const static CString strA;
	const static CString strB;
	const static CString strC;
	const static CString strD;
	const static CString strE;
	const static CString strF;
	const static CString strG;
	const static CString strH;
	const static CString strI;
	const static CString strJ;
	const static CString strK;
	const static CString strL;
	const static CString strM;
	const static CString strN;
	const static CString strO;
	const static CString strP;
	const static CString strQ;
	const static CString strR;
	const static CString strS;
	const static CString strT;
	const static CString strU;
	const static CString strV;
	const static CString strW;
	const static CString strX;
	const static CString strY;
	const static CString strZ;

	CLetterIndex( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CLetterIndex();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CLetterIndex)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void OnTimer(UINT nIDEvent) ;
	
	DECLARE_MESSAGE_MAP()
public:
	static CTransparentBaseWnd* GetLetterWindow();
    void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	void SetImage( int* pPngId, BOOL bInvalidate = FALSE );

    /**  根据点击位置获取点击的字母及图片
     *  @param[in] point  鼠标点击位置
     *  @param[out] nIndex  点中的字母索引
     *  @return  点中的字母图片
     */
	Image* GetClickLetter( CPoint point, int& nIndex );
    /**  设置绑定列表
     *  @param[in] pList  列表窗口指针
     *  @return  无
     */
	void SetBindList( CWnd* pList );
    void AddBindList( CWnd* pList );
	void SetLetterHeight( float fHeight );

	BOOL EnableWindow(BOOL bEnable = TRUE);

private:
    /**  通知绑定列表
     *  @param[in] nLetterIndex  点中的字母索引
     *  @return  无
     */
	void NotifyBindList( int nLetterIndex );

protected:
	CWnd          *m_pBindList;
	vector<CWnd*>  m_vcBindList;

	static  CTransparentBaseWnd  *m_pLetterWnd;
    Image  *m_pImgBkg;
	Image  *m_pImgLetter[LETTER_NUM];
	BOOL    m_bLBtnDown;
	BOOL    m_bTouchBtnDown;
	float   m_fLetterHeight; //使用浮点数，减少误差
	float   m_fOffSet;       //字母索引上下两端多出的长度
	BOOL    m_bStretch;      //贴图是否允许拉伸
};

#endif