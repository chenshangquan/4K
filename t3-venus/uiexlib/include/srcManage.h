
#ifndef SRCMANAGE_HEAD_H
#define SRCMANAGE_HEAD_H
#include "uiexBaseData.h"

//用于设置窗口背景图片的组合方式  2012.12.18 yjj
typedef enum EmImgCompType
{
	    emImgCompMasic,      //用于列表，各个方向共8张图片拼接而成
		emImgCompSingle,     //整张图片
		emImgCompLMR,		//需要 左中右 形式拼接的图片
		emImgCompTMB		//需要 上中下 形式拼接的图片
};

class CFontInfo
{
public:
	CFontInfo( CString strFontFamily, unsigned int wSize, FontStyle emStyle ) : 
      m_strFontFamily( strFontFamily ), m_wSize( wSize ), m_emFontStyle( emStyle ){}
	CString m_strFontFamily;
	unsigned int m_wSize;
    FontStyle m_emFontStyle;
	bool operator<( const CFontInfo& tag) const {
		if ( m_strFontFamily != tag.m_strFontFamily )
 		{
 			return true;
 		}
        if ( m_emFontStyle != tag.m_emFontStyle )
        {
            return true;
        }
		return m_wSize < tag.m_wSize;
	};
	
};
class CSrcManage 
{
    enum{STEPBK_VERT = 0, STEPBK_HORZ}; //渐进色的方向， DrawStepBk。
public:
    /*====================================================================
    函数名	：    CreateImage
    功能		：根据BMP资源号得到图片句柄
    算法实现	：（可选项）
    引用全局变量：无
    输入参数说明：nBitmap 图片资源号
    返回值说明：  图片句柄，不成功为NULL。
    ====================================================================*/
    static HBITMAP CreateImage(UINT nBitmap);

    /*====================================================================
    函数名	：    DrawStepBk
    功能		：画渐进色
    算法实现	：分三色计算颜色变换的速度，然后计算每次的颜色，为了提高效率
                    每次画两象素的线
    引用全局变量：无
    输入参数说明：pDC 作图的CDC指针
                  crFrom 开始的颜色，最上面（或最左边）的颜色。
                  crTo 结束的颜色，最下面（或最右边）的颜色。
                  rcAll  计算颜色渐变的整个区域范围。
                  rcItem 实际的作图的区域。
                  nStyle 渐变的方向STEPBK_VERT，从上到下，STEPBK_HORZ，从左到右。
    返回值说明：  无
    ====================================================================*/
    static void DrawStepBk(CDC *pDC, COLORREF crFrom, COLORREF crTo, CRect rcAll, CRect rcItem=CRect(0,0,0,0), UINT nStyle=STEPBK_VERT);

	static BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	static HRGN GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue);

/**  获得一个图片资源
 *  @param[in] strpath 路径
 *  @param[in] bNewCreate 是否需要重新加载，不用在全局共享区域获取
 *  @param[out] pImage 图片资源
 *  @return 是否成功
 */
	static Image* GetImage( CString strPath, BOOL bNewCreate = FALSE );

/**  重载获得图片资源
 *  @param[in] nID 资源ID
 *  @param[in] lpszType 图片格式，如"PNG"
 *  @param[in] hInstance 应用程序资源句柄，为空表示本程序
 *  @return pImage 图片资源
 */
	static Image*  GetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );
	static Image* LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );


/**   由左中右三张图标 拼接 为一张图片
 *  @param[in] Rect  所需要拼接的图片大小
 *  @param[in] pImgLeft  
 *  @param[in] pImgRight  
 *  @param[in] pImgMiddle
 *  @return pImage 拼接的图标
 */
    static Image* MosaicHoriImage(  CRect& cRect, Image* pImgLeft, Image* pImgRight, Image* pImgMiddle );


    /**   由上中下 三张图标 拼接 为一张图片
 *  @param[in] Rect  所需要拼接的图片大小
 *  @param[in] pImgTop  
 *  @param[in] pImgBottom  
 *  @param[in] pImgMiddle
 *  @return pImage 拼接的图标
 */ 
    static Image* MosaicVertImage(  CRect& cRect,  Image* pImgTop, Image* pImgBottom, Image* pImgMiddle );
	
/**  获取字体资源
 *  @param[in] strFontFamily 字体名称
 *  @param[in] wSize 字体大小
 *  @return 字体指针
 */
	static Font* GetFont( CString strFontFamily, unsigned int wSize, FontStyle emFontStyle = FontStyleRegular, BOOL bNewCreate = FALSE );
	static void GetChsAndEngCnt( CString cstrText, unsigned short& wChsCnt, unsigned short& wEngCnt);

/**  获取图片大小
 *  @param[in] strImgFullPath 图片全路径
 *  @return 图片大小
 */
	static CSize GetImageSize(CString strImgFullPath);

/**  在进程退出时释放m_smapImage图片资源
 *  @param[in] void
 *  @return void
 */
	static void ReleaseImage();

/**  在进程退出时释放m_smapFonts字体资源
 *  @param[in] void
 *  @return void
 */
	static void ReleaseFont();

	/**  释放改路径的图片资源，改图片需要未使用
 *  @param[in] void
 *  @return void
 */
	static	void ReleaseSingleImage( CString strPath );
private:
/*
 *  全局的一个共享区，有些图片不需要加载多次\n 
 */
	typedef std::map<CString, Image*> ImageMap;
	static ImageMap m_mapImages;

	typedef std::map<UINT, Image*> CImageMap;
	static CImageMap m_smapImage;

	typedef CFontInfo FontKey; 
	typedef std::map<FontKey, Font*> FontMap;
	static FontMap m_smapFonts;
};

#endif