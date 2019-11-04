// SystemInfoManage.h: interface for the CSystemInfoManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_)
#define AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace AutoUIFactory
{

class CSystemInfoManage : public IObserver, public Singleton<CSystemInfoManage>
{
public:
	static const String strSystemInfo;
	static const String strVersion;
	static const String strName;
	static const String strValue;
	static const String strImagePath;
	static const String strLayoutPath;
	static const String strItemInfo;
    static const String strResolution;//分辨率
    static const String strBeSelAdpResolution;
    static const String strEditInfo;
    static const String strStaticInfo;
	static const String strKeyValue;
public:
	CSystemInfoManage();
	virtual ~CSystemInfoManage();
public:
	/**  设置系统图片资源路径
	 *  @param[in] strPath 路径
	 *  @return 
	 */
	void SetImagePath( String strPath );

	String GetImagePath() { return m_strImagePath; }

	/**  设置系统布局文件路径
	 *  @param[in] strPath 路径
	 *  @return 
	 */
    void SetLayoutPath( String strPath );

	String GetLayoutPath() { return m_strLayoutPath; }

	/**  设置ItemInfo文件路径
	 *  @param[in] strPath 路径
	 *  @return 
	 */
    void SetItemInfoPath( String strPath );

	String GetItemInfoPath() { return m_strItemInfo; }

	void Update( IArgs* pArgs );
   
   //把某个文件的相对路径设置为绝对路径
    void MakeFullPath( String& strFileSubPath );
     
    void SetResolution( String strValue );
    void GetResolution( int &cx, int &cy ) ;
    String GetResolution(){ return m_strResolution;}
  
    //是否自适应分辨率
    void SetBeSelAdpResolution( String strValue );
    BOOL IsSelAdpResolution() ;

	//平板home键键值读取
	void SetPadKeyValue( String strValue );
	DWORD GetPadKeyValue();

    //Edit字体信息
    void SetFontInfo( TFontInfo &tFontInfo, XMLAttributes& xmlAttribs );
    TFontInfo GetEditFontInfo(){ return m_tEditFontInfo; }

    //Static字体信息   
    TFontInfo GetStaticFontInfo(){ return m_tStaticFontInfo; }

	string GetVersion(){ return m_strVersion; }

    void  SetVersion( string strVer );
protected:

	void UpdateSystemInfo( XMLAttributes& xmlAttribs );
	/*
	 * 主控文件路径
	 *  
	 */
	String m_strMainXml;

	/*
	 *  图片资源路径
	 */
	String m_strImagePath;

	/*
	 *  布局文件路径
	 */
	String m_strLayoutPath;

	
    /*
	 * 条目信息的路径\n 
	 */
	String m_strItemInfo;
    
    /*
	 * 分辨率 \n 
	 */
    String m_strResolution;

    /*
	 * 是否自适应分辨率 \n 
	 */
    BOOL m_bBeSelAdpResolution;

    /*
	 * 平板Home键键值 \n 
	 */
    DWORD m_dwKeyValue;

	/*
	 * 版本号 \n 
	 */
	String m_strVersion;

    /*
	 * Edit默认字体信息 \n 
	 */
    TFontInfo m_tEditFontInfo;

    /*
	 * Static默认字体信息 \n 
	 */
    TFontInfo m_tStaticFontInfo;
};

};
#endif // !defined(AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_)
