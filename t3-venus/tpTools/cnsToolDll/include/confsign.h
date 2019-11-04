// confsign.h: interface for the CConfSign class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFSIGN_H__C69B3E17_6270_4D7D_B207_A50E61AC663B__INCLUDED_)
#define AFX_CONFSIGN_H__C69B3E17_6270_4D7D_B207_A50E61AC663B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfSign : public ISingleTon<CConfSign>
{
public:
	CConfSign();
	virtual ~CConfSign();

	/**	 
	* 功能: 制作显示文字的图片
	* @param    const LPCTSTR strCharacters     [in]     文字内容
	* @param    const LPCTSTR strFontFamily     [in]     字体格式(宋体、微软雅黑等) 
	* @param    const FontStyle emFontStyle     [in]     字体结构(加粗、下划线等) 
	* @param    const Color clText				[in]     字体颜色 
	* @param    const Color clBorder			[in]     字体边界颜色 
	* @param    const Color clBkGrd				[in]     图片背景颜色 
	* @param    const int nFontSizeByPx			[in]     字体Px 
	* @param    const int borderWidthByPx		[in]     字体边界Px 
	* @param    const LPCTSTR strFileName		[in]     图片存储路径 
	* @return   bool
	* @remarks  
	*/
	BOOL MakeImgByChar( const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
		const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName);
	
	/**	 
	* 功能: 获取显示文字的大小
	* @param    const WCHAR * strCharacters     [in]     文字内容
	* @param    Font*pFont				        [in]     字体内容信息
	* @param    CSize& cSize					[out]    文字的大小
	* @return   
	* @remarks  
	*/
	void GetCharExtent(IN const WCHAR * strCharacters, Font*pFont, CSize& cSize);

	/**	 
	* 功能: 上传核心
	* @param    const String strRemotePath      [in]     linux端待存储路径
	* @param    const String strLocalFile       [in]     待传输的文件全路径 
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName ); 

private:
	CFtpCtrl m_cFtp;
};

#define	ConfSign     CConfSign::GetSingletonPtr()

#endif // !defined(AFX_CONFSIGN_H__C69B3E17_6270_4D7D_B207_A50E61AC663B__INCLUDED_)
