/*=======================================================================
模块名      : 网管公用模块库
文件名      : nmscommon.cpp
相关文件    : 
文件实现功能: 
作者        : 李洪强
版本        : V4.0  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2004/07/16  3.0   李洪强  创建
2004/12/18  3.5   李洪强  增加TplArray模板类
2005/01/26  3.5   李洪强  修改TplArray插入操作的bug
=======================================================================*/

#include "stdafx.h"
#include "nmscommon.h"
#include "vccommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NMSCOMMON_VER   (LPCSTR)"nmscommonver version: 40.30.01.01.20061020"

//////////////////////////////////////////////////////////////////////////
//
//     安全注册ocx控件的辅助函数
//
// Helper function to create a component category and associated description
HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
    ICatRegister *pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409; // english

    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is
    size_t nLen = wcslen(catDescription);
    if ( nLen > 127 )
    {
        nLen = 127;
    }

    wcsncpy( catinfo.szDescription, catDescription, nLen );
    // Make sure the description is null terminated
    catinfo.szDescription[nLen] = '\0';

    hr = pcr->RegisterCategories( 1, &catinfo );
    pcr->Release();

    return hr;
}

// Helper function to register a CLSID as belonging to a component category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    // Register your component categories information.
    ICatRegister* pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( SUCCEEDED( hr ) )
    {
        // Register this category as being "implemented" by
        // the class.
        CATID rgcatid[1];
        rgcatid[0] = catid;
        hr = pcr->RegisterClassImplCategories( clsid, 1, rgcatid );
    }

    if ( pcr != NULL )
    {
        pcr->Release();
    }

    return hr;
}

// Helper function to unregister a CLSID as belonging to a component category
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    ICatRegister* pcr = NULL;
    HRESULT hr = S_OK;

    hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, 
                           NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister,
                           (void**)&pcr );
    if ( SUCCEEDED( hr ) )
    {
        // Unregister this category as being "implemented" by
        // the class.
        CATID rgcatid[1];
        rgcatid[0] = catid;
        hr = pcr->UnRegisterClassImplCategories( clsid, 1, rgcatid );
    }

    if (pcr != NULL)
    {
        pcr->Release();
    }

    return hr;
}

/*=============================================================================
函 数 名:nmscommonver
功    能:打印NmsCommon库的版本号
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  创建
=============================================================================*/
API void nmscommonver(void)
{
    OspPrintf( TRUE, FALSE, "%s compile time: %s %s\n", NMSCOMMON_VER,
               __DATE__, __TIME__ );
}

/*=============================================================================
函 数 名:GetConfBitrate
功    能:获取会议码率
参    数:u32 **ppdwBitrate              [out]   会议码率数组
         s32 &nNum                      [out]   数组大小
         u32 dwMCUType                  [in]    MCU类型
注    意:不需要给ppdwBitrate分配空间, 且不能delete ppdwBitrate
         8000C MCU只支持到4M
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/29  3.5     王昊    创建
2007/04/25  4.0     王廖荣  修改
=============================================================================*/
void GetConfBitrate(u32 **ppdwBitrate, s32 &nNum, u32 dwMCUType)
{
	static u32 adwBitrate8M[] = {384,
							512,
							768,
							1024,
							1216,
							1536,
							1792,
							2048,
							3072,
							4096,
							5120,
							6144,
							7168,
							8128};

	static u32 adwBitrate4M[] = {384,
							512,
							768,
							1024,
							1216,
							1536,
							1792,
							2048,
							3072,
							4096};

    if( MCU_TYPE_KDV8000C == dwMCUType)
    {
        *ppdwBitrate = adwBitrate4M;
        nNum = sizeof (adwBitrate4M) / sizeof (u32);
    }
	else
    {
        *ppdwBitrate = adwBitrate8M;
        nNum = sizeof (adwBitrate8M) / sizeof (u32);
    }
}

/*=============================================================================
函 数 名:GetModuleFullPath
功    能:获取模块所在文件夹全路径, 包括最后的\
参    数:无
注    意:例如 C:\
返 回 值:文件夹字符串
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
CString GetModuleFullPath(void)
{
	TCHAR achDllName[MAX_PATH] = _T("");
	CString csPath = _T("");

	GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));

	csPath = achDllName;
	csPath = csPath.Left( csPath.ReverseFind('\\') + 1 );

	return csPath;
}



 
CString GetModulePath(void)
{
    TCHAR achDllName[MAX_PATH] = _T("");
    CString csPath = _T("");
    
    //AfxGetInstanceHandle()可能获取失败
    // 	GetModuleFileName( AfxGetInstanceHandle(), achDllName, MAX_PATH);
    
    MEMORY_BASIC_INFORMATION mbi;   
    static int dummy; 
    u32 dwLength = sizeof(mbi); 
    if ( dwLength == VirtualQuery( &dummy, &mbi, dwLength ) )
    {
        GetModuleFileName( reinterpret_cast<HMODULE>(mbi.AllocationBase), achDllName, MAX_PATH ); 
    }
    
    csPath = achDllName;
    csPath = csPath.Left( csPath.ReverseFind('\\') + 1 );
    
    return csPath;

}



HWND GetWndByAppName( CString strAppname )
{
    if ( strAppname.IsEmpty() )
    {
        return 0;
    }

    HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, (LPCSTR)strAppname );   
    
    //   信号量存在，则程序已有一个实例运行   
    if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
    {  		
        //   关闭信号量句柄   
        CloseHandle(hSem);   
        //   寻找先前实例的主窗口   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   检查窗口是否有预设的标记?   
            //   有，则是我们寻找的主窗   
            if   (::GetProp(hWndPrevious, (LPCSTR)strAppname))   
            {  
                return   hWndPrevious;   
            }   
            //   继续寻找下一个窗口   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   前一实例已存在，但找不到其主窗   
        //   退出本实例   
        return   0;   
    } 

    return 0;
}


/*=============================================================================
函 数 名:ModuleRegToOsp
功    能:向OSP注册本模块
参    数:无
注    意:无
返 回 值:成功：TRUE; 失败：FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
BOOL32 ModuleRegToOsp(void)
{
	TCHAR achDllName[MAX_PATH] = _T("");
	GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
	return OspRegistModule(achDllName);
}

/*=============================================================================
函 数 名:GetUrl
功    能:获取IE地址栏内容
参    数:const COleControl *pcCtrl          [in]    ocx控件
         CString &cstrUrl                   [out]   地址栏内容
注    意:无
返 回 值:成功:TRUE; 失败:FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/08  4.0     王昊    创建
=============================================================================*/
BOOL32 GetUrl(const COleControl *pcCtrl, CString &cstrUrl)
{
    IWebBrowser2        *pBrowser = NULL;
    HRESULT             hr = S_OK;
    IServiceProvider    *pIsp1 = NULL;
    IServiceProvider    *pIsp2 = NULL;
    LPOLECLIENTSITE     pClientSite = ((COleControl*)pcCtrl)->GetClientSite();

    if ( pClientSite == NULL )
    {
        return FALSE;
    }

    hr = pClientSite->QueryInterface( IID_IServiceProvider,
                                       reinterpret_cast<void**>(&pIsp1) );
    if ( FAILED(hr) )
    {
		pIsp1->Release();
		pIsp1 = NULL;

        return FALSE;
    }

    hr = pIsp1->QueryService( SID_STopLevelBrowser, IID_IServiceProvider,
                              reinterpret_cast<void**>(&pIsp2) );
    if ( FAILED(hr) )
    {
        pClientSite->Release();
        return FALSE;
    }

    hr = pIsp2->QueryService( SID_SWebBrowserApp, IID_IWebBrowser2,
                              reinterpret_cast<void**>(&pBrowser) );
    if ( FAILED(hr) )
    {
        pClientSite->Release();
        pIsp1->Release();
		pIsp1 = NULL;
        return FALSE;
    }

    BSTR bstrUrl = NULL;
    pBrowser->get_LocationURL( &bstrUrl );
    cstrUrl = bstrUrl;
    ::SysFreeString( bstrUrl );

    pClientSite->Release();

	if ( NULL != pIsp2 )
	{
		pIsp2->Release();
		pIsp2 = NULL;
	}

    return TRUE;
}

/*=============================================================================
函 数 名:EncryptPwd
功    能:密码加密
参    数:LPCSTR lpszPwd                     [in]    原始密码, 最长32位(包括'/0')
         s8 aszEncryptedPwd[64]             [out]   加密密码
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
=============================================================================*/
void EncryptPwd(LPCSTR lpszPwd, s8 aszEncryptedPwd[64])
{
    s32 nLen = strlen( lpszPwd );
    u8 abyPwd[32] = {0};

    if ( nLen == 0 )
    {
        ZeroMemory( aszEncryptedPwd, sizeof (aszEncryptedPwd) );
        strcpy( aszEncryptedPwd, "04AB3456C1234DDDD5567" );
        return;
    }

    for ( s32 nIndex = 0; nIndex < 32 / nLen; nIndex ++ )   //复制密码
    {
        memcpy( abyPwd + nLen * nIndex, lpszPwd, nLen );
    }

    if ( nLen * nIndex < 32 )   //  继续复制
    {
        memcpy( abyPwd + nLen * nIndex, lpszPwd, 32 - nIndex * nLen );
    }

    for ( nIndex = 0; nIndex < 32; nIndex ++ )  //  密码转换
    {
        switch ( abyPwd[nIndex] )
        {
        case 'a':
            abyPwd[nIndex] = 21;
            break;
        case 'b':
            abyPwd[nIndex] = 73;
            break;
        case 'c':
            abyPwd[nIndex] = 12;
            break;
        case 'd':
            abyPwd[nIndex] = 2;
            break;
        case 'e':
            abyPwd[nIndex] = 254;
            break;
        case 'f':
            abyPwd[nIndex] = 23;
            break;
        case 'g':
            abyPwd[nIndex] = 3;
            break;
        case 'h':
            abyPwd[nIndex] = 75;
            break;
        case 'i':
            abyPwd[nIndex] = 80;
            break;
        case 'j':
            abyPwd[nIndex] = 153;
            break;
        case 'k':
            abyPwd[nIndex] = 67;
            break;
        case 'l':
            abyPwd[nIndex] = 69;
            break;
        case 'm':
            abyPwd[nIndex] = 134;
            break;
        case 'n':
            abyPwd[nIndex] = 43;
            break;
        case 'o':
            abyPwd[nIndex] = 92;
            break;
        case 'p':
            abyPwd[nIndex] = 179;
            break;
        case 'q':
            abyPwd[nIndex] = 7;
            break;
        case 'r':
            abyPwd[nIndex] = 215;
            break;
        case 's':
            abyPwd[nIndex] = 44;
            break;
        case 't':
            abyPwd[nIndex] = 82;
            break;
        case 'u':
            abyPwd[nIndex] = 9;
            break;
        case 'v':
            abyPwd[nIndex] = 83;
            break;
        case 'w':
            abyPwd[nIndex] = 46;
            break;
        case 'x':
            abyPwd[nIndex] = 77;
            break;
        case 'y':
            abyPwd[nIndex] = 61;
            break;
        case 'z':
            abyPwd[nIndex] = 158;
            break;
        case '0':
            abyPwd[nIndex] = 144;
            break;
        case '1':
            abyPwd[nIndex] = 10;
            break;
        case '2':
            abyPwd[nIndex] = 25;
            break;
        case '3':
            abyPwd[nIndex] = 74;
            break;
        case '4':
            abyPwd[nIndex] = 152;
            break;
        case '5':
            abyPwd[nIndex] = 181;
            break;
        case '6':
            abyPwd[nIndex] = 193;
            break;
        case '7':
            abyPwd[nIndex] = 200;
            break;
        case '8':
            abyPwd[nIndex] = 201;
            break;
        case '9':
            abyPwd[nIndex] = 171;
            break;
        case '`':
            abyPwd[nIndex] = 178;
            break;
        case '~':
            abyPwd[nIndex] = 156;
            break;
        case '!':
            abyPwd[nIndex] = 27;
            break;
        case '@':
            abyPwd[nIndex] = 32;
            break;
        case '#':
            abyPwd[nIndex] = 90;
            break;
        case '$':
            abyPwd[nIndex] = 183;
            break;
        case '%':
            abyPwd[nIndex] = 138;
            break;
        case '^':
            abyPwd[nIndex] = 192;
            break;
        case '&':
            abyPwd[nIndex] = 222;
            break;
        case '*':
            abyPwd[nIndex] = 111;
            break;
        case '(':
            abyPwd[nIndex] = 205;
            break;
        case ')':
            abyPwd[nIndex] = 42;
            break;
        case '-':
            abyPwd[nIndex] = 76;
            break;
        case '_':
            abyPwd[nIndex] = 94;
            break;
        case '=':
            abyPwd[nIndex] = 99;
            break;
        case '+':
            abyPwd[nIndex] = 116;
            break;
        case '\\':
            abyPwd[nIndex] = 81;
            break;
        case '|':
            abyPwd[nIndex] = 86;
            break;
        case '[':
            abyPwd[nIndex] = 71;
            break;
        case '{':
            abyPwd[nIndex] = 66;
            break;
        case ']':
            abyPwd[nIndex] = 63;
            break;
        case '}':
            abyPwd[nIndex] = 60;
            break;
        case ';':
            abyPwd[nIndex] = 5;
            break;
        case ':':
            abyPwd[nIndex] = 84;
            break;
        case '\'':
            abyPwd[nIndex] = 8;
            break;
        case '"':
            abyPwd[nIndex] = 18;
            break;
        case ',':
            abyPwd[nIndex] = 95;
            break;
        case '<':
            abyPwd[nIndex] = 199;
            break;
        case '.':
            abyPwd[nIndex] = 110;
            break;
        case '>':
            abyPwd[nIndex] = 16;
            break;
        case '/':
            abyPwd[nIndex] = 65;
            break;
        case '?':
            abyPwd[nIndex] = 0;
            break;
        default:
            abyPwd[nIndex] = ~abyPwd[nIndex];
            break;
        }
    }

    for ( nIndex = 0; nIndex < 31; nIndex ++ )
    {
        aszEncryptedPwd[2 * nIndex] = (abyPwd[nIndex] >> 4) + '0';
        aszEncryptedPwd[2 * nIndex + 1] = (abyPwd[nIndex] & 0x0F) + '0';
        if ( aszEncryptedPwd[2 * nIndex] > '9'
             || aszEncryptedPwd[ 2 * nIndex] < '0' )
        {
            aszEncryptedPwd[2 * nIndex] += 'A' - '0' - 10;
        }
        if ( aszEncryptedPwd[2 * nIndex + 1] > '9'
             || aszEncryptedPwd[2 * nIndex + 1] < '0' )
        {
            aszEncryptedPwd[2 * nIndex + 1] += 'A' - '0' - 10;
        }
    }

    aszEncryptedPwd[62] = nLen + (nLen < 16 ? 'a' : 'A' - 16);  //字符长度位
    aszEncryptedPwd[63] = '\0';
}

/*=============================================================================
函 数 名:DecryptPwd
功    能:密码解密
参    数:s8 aszEncryptedPwd[64]             [in]    加密密码
         LPSTR lpszPwd                      [out]   原始密码, 最长32位(包括'/0')
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
=============================================================================*/
void DecryptPwd(s8 aszEncryptedPwd[64], LPSTR lpszPwd)
{
    s32 nLen = aszEncryptedPwd[62] - (aszEncryptedPwd[62] > 'Z' ? 'a' : 'A' - 16);
    u8 abyPwd[64] = {0};
    ZeroMemory( lpszPwd, 32 );

    if ( aszEncryptedPwd[62] == 0 )
    {
        return;
    }

    for ( s32 nIndex = 0; nIndex < nLen * 2; nIndex += 2 )
    {
        if ( aszEncryptedPwd[nIndex] < '0' || aszEncryptedPwd[nIndex] > '9' )
        {
            lpszPwd[nIndex/2] |= (aszEncryptedPwd[nIndex] - 'A' + 10) << 4;
        }
        else
        {
            lpszPwd[nIndex/2] |= (aszEncryptedPwd[nIndex] - '0') << 4;
        }
        if ( aszEncryptedPwd[nIndex+1] < '0' || aszEncryptedPwd[nIndex+1] > '9' )
        {
            lpszPwd[nIndex/2] |= (aszEncryptedPwd[nIndex+1] - 'A' + 10);
        }
        else
        {
            lpszPwd[nIndex/2] |= (aszEncryptedPwd[nIndex+1] - '0');
        }
    }

    for ( nIndex = 0; nIndex < nLen; nIndex ++ )  //  密码转换
    {
        switch ( (u8)lpszPwd[nIndex] )
        {
        case 21:
            lpszPwd[nIndex] = 'a';
            break;
        case 73:
            lpszPwd[nIndex] = 'b';
            break;
        case 12:
            lpszPwd[nIndex] = 'c';
            break;
        case 2:
            lpszPwd[nIndex] = 'd';
            break;
        case 254:
            lpszPwd[nIndex] = 'e';
            break;
        case 23:
            lpszPwd[nIndex] = 'f';
            break;
        case 3:
            lpszPwd[nIndex] = 'g';
            break;
        case 75:
            lpszPwd[nIndex] = 'h';
            break;
        case 80:
            lpszPwd[nIndex] = 'i';
            break;
        case 153:
            lpszPwd[nIndex] = 'j';
            break;
        case 67:
            lpszPwd[nIndex] = 'k';
            break;
        case 69:
            lpszPwd[nIndex] = 'l';
            break;
        case 134:
            lpszPwd[nIndex] = 'm';
            break;
        case 43:
            lpszPwd[nIndex] = 'n';
            break;
        case 92:
            lpszPwd[nIndex] = 'o';
            break;
        case 179:
            lpszPwd[nIndex] = 'p';
            break;
        case 7:
            lpszPwd[nIndex] = 'q';
            break;
        case 215:
            lpszPwd[nIndex] = 'r';
            break;
        case 44:
            lpszPwd[nIndex] = 's';
            break;
        case 82:
            lpszPwd[nIndex] = 't';
            break;
        case 9:
            lpszPwd[nIndex] = 'u';
            break;
        case 83:
            lpszPwd[nIndex] = 'v';
            break;
        case 46:
            lpszPwd[nIndex] = 'w';
            break;
        case 77:
            lpszPwd[nIndex] = 'x';
            break;
        case 61:
            lpszPwd[nIndex] = 'y';
            break;
        case 158:
            lpszPwd[nIndex] = 'z';
            break;
        case 144:
            lpszPwd[nIndex] = '0';
            break;
        case 10:
            lpszPwd[nIndex] = '1';
            break;
        case 25:
            lpszPwd[nIndex] = '2';
            break;
        case 74:
            lpszPwd[nIndex] = '3';
            break;
        case 152:
            lpszPwd[nIndex] = '4';
            break;
        case 181:
            lpszPwd[nIndex] = '5';
            break;
        case 193:
            lpszPwd[nIndex] = '6';
            break;
        case 200:
            lpszPwd[nIndex] = '7';
            break;
        case 201:
            lpszPwd[nIndex] = '8';
            break;
        case 171:
            lpszPwd[nIndex] = '9';
            break;
        case 178:
            lpszPwd[nIndex] = '`';
            break;
        case 156:
            lpszPwd[nIndex] = '~';
            break;
        case 27:
            lpszPwd[nIndex] = '!';
            break;
        case 32:
            lpszPwd[nIndex] = '@';
            break;
        case 90:
            lpszPwd[nIndex] = '#';
            break;
        case 183:
            lpszPwd[nIndex] = '$';
            break;
        case 138:
            lpszPwd[nIndex] = '%';
            break;
        case 192:
            lpszPwd[nIndex] = '^';
            break;
        case 222:
            lpszPwd[nIndex] = '&';
            break;
        case 111:
            lpszPwd[nIndex] = '*';
            break;
        case 205:
            lpszPwd[nIndex] = '(';
            break;
        case 42:
            lpszPwd[nIndex] = ')';
            break;
        case 76:
            lpszPwd[nIndex] = '-';
            break;
        case 94:
            lpszPwd[nIndex] = '_';
            break;
        case 99:
            lpszPwd[nIndex] = '=';
            break;
        case 116:
            lpszPwd[nIndex] = '+';
            break;
        case 81:
            lpszPwd[nIndex] = '\\';
            break;
        case 86:
            lpszPwd[nIndex] = '|';
            break;
        case 71:
            lpszPwd[nIndex] = '[';
            break;
        case 66:
            lpszPwd[nIndex] = '{';
            break;
        case 63:
            lpszPwd[nIndex] = ']';
            break;
        case 60:
            lpszPwd[nIndex] = '}';
            break;
        case 5:
            lpszPwd[nIndex] = ';';
            break;
        case 84:
            lpszPwd[nIndex] = ':';
            break;
        case 8:
            lpszPwd[nIndex] = '\'';
            break;
        case 18:
            lpszPwd[nIndex] = '"';
            break;
        case 95:
            lpszPwd[nIndex] = ',';
            break;
        case 199:
            lpszPwd[nIndex] = '<';
            break;
        case 110:
            lpszPwd[nIndex] = '.';
            break;
        case 16:
            lpszPwd[nIndex] = '>';
            break;
        case 65:
            lpszPwd[nIndex] = '/';
            break;
        case 0:
            lpszPwd[nIndex] = '?';
            break;
        default:
            lpszPwd[nIndex] = ~lpszPwd[nIndex];
            break;
        }
    }
}

/*=============================================================================
函 数 名: GetModuleCfgFileFullName
功    能: 获取配置文件全路径
参    数: LPCSTR lptrFileName                   [in]    配置文件名
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/03/01  1.0     王昊    创建
=============================================================================*/
CString GetModuleCfgFileFullName(LPCSTR lptrFileName)
{
    CString cstrFullname = "";

    CString cstrFilePath = GetModuleFullPath();
    if ( cstrFilePath.GetLength() > 3 )
    {
        //去掉最后的'\\'
        cstrFilePath = cstrFilePath.Left( cstrFilePath.GetLength() - 1 );

        do
        {
            int nFind = cstrFilePath.ReverseFind( '\\' );
            if ( nFind == -1 )
            {
                break;
            }

            CString cstrTemp = cstrFilePath.Right( cstrFilePath.GetLength()
                                                        - nFind - 1 );
            s8 szString[MAX_PATH] = "conflict.";
            int nStringLen = strlen( szString );
            if (    cstrTemp.GetLength() <= nStringLen
                 || cstrTemp.Left( nStringLen ).CompareNoCase( szString ) != 0 )
            {
                break;
            }

            cstrTemp = cstrTemp.Right( cstrTemp.GetLength() - nStringLen );
            int nLen = cstrTemp.GetLength();
            for ( int nIndex = 0; nIndex < nLen; nIndex ++ )
            {
                if ( ! isdigit( cstrTemp[nIndex] ) )
                {
                    break;
                }
            }

            if ( nIndex != nLen )
            {
                break;
            }

            //文件夹末尾是"conflict.%d"
            GetSystemDirectory( szString, sizeof (szString) - 1 );
            strcat( szString, "\\Downloaded Program Files\\conflit." );
            strcat( szString, static_cast<LPCSTR>(cstrTemp) );
            //需要截断
            if ( cstrFilePath.CompareNoCase( szString ) == 0 )
            {
                cstrFilePath = cstrFilePath.Left( nFind );
            }

        } while ( FALSE );

        cstrFilePath += "\\";//补上最后的'\\'
    }

    cstrFullname = cstrFilePath + lptrFileName;

    return cstrFullname;
}



/*=============================================================================
函 数 名: MakeFileFullName
功    能: 把当前相对路径文件 做成绝对路径
参    数: LPCSTR lptrFileName                   [in] 相对路径的文件名
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2012/8/01  1.0     俞锦锦    创建
=============================================================================*/
void MakeFileFullName( CString& strFileSubPath )
{ 
	TCHAR achDllName[MAX_PATH] = _T(""); 
    GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
    CString str( achDllName ); 
    
    int pos = str.ReverseFind('\\'); 
    CString strSub = str.Left( pos+1 );
    char strFullPath[MAX_PATH] = _T(""); 
	
    _snprintf(strFullPath , sizeof(strFullPath), "%s%s",strSub ,strFileSubPath );
	
    strFileSubPath = strFullPath ;
		
   
}





/*========================================================================
函 数 名：CheckIEBHOAvailable
功    能：检查IE中是否加载了和我们的OCX控件不兼容的插件
注    意：可以在控件的InitInstance()中进行调用，如返回FALSE则控件退出
          例如：
            BOOL CTestApp::InitInstance()
            {
	            BOOL bInit = COleControlModule::InitInstance();

	            if (bInit)
	            {
                    BOOL bBHOAvailable = CheckIEBHOAvailable( 0 );
                    if ( FALSE == bBHOAvailable )
                    {
                        return FALSE;
                    }
	            }

	            return bInit;
            }

参    数：u32 dwLanguage        [in]    语言类型    0为英文，1为中文
返 回 值：TRUE：    没有不兼容的插件或用户选择不卸载相应的插件
          FALSE：   检测到有不兼容的插件，且用户选择卸载相应的插件
相关消息：
--------------------------------------------------------------------------
修改记录：
日      期  版本    修改人  修改内容
2007/11/07  1.0     王廖荣    创建
========================================================================*/
BOOL32 CheckIEBHOAvailable( u32 dwLanguage )
{
    // 双语提示 0为英文，1为中文
    const char paszInfo[][256] = 
    {
        _T("Detect the Browser Helper Objects (BHO) below may cause an IE exception. You'd better uninstall them. Click 'YES' to uninstall them and rerun the program again manually.\n\n"),
        _T("检测到您当前的IE浏览器装的下列插件可能会引起IE异常，是否将其卸载？卸载后必须将IE关闭后重新运行程序。\n\n")
    };

    const char paszBHO[][50] =
    {
        _T("1. FlashGet BHO jccatch.dll\n"),
        _T("1. FlashGet插件jccatch.dll\n")
    };

    if ( dwLanguage >= sizeof( paszInfo ) / 256 )
    {
        dwLanguage = 0;
    }

    CString strInfo = paszInfo[dwLanguage];

    // 检测IE程序中是否已经加载了FlashGet插件
    // jccatch.dll的GUID：FB5DA724-162B-11D3-8B9B-AA70B4B0B524
    CString strBHOName = _T("");
    CString strSubKey;
    strSubKey = "CLSID\\{FB5DA724-162B-11D3-8B9B-AA70B4B0B524}\\InprocServer32";

    HKEY hKey = NULL;

    // 从注册表中读取FlashGet插件的文件名
    LONG lRet = RegOpenKeyEx( HKEY_CLASSES_ROOT, strSubKey,
                              0, KEY_READ, &hKey );
    if ( lRet == ERROR_SUCCESS )
    {
        char abyPath[MAX_PATH];
        DWORD dwSize = sizeof(abyPath) / sizeof(TCHAR);
        DWORD dwType = REG_SZ;
        lRet = RegQueryValueEx( hKey, NULL, NULL, &dwType, (unsigned char *)abyPath, &dwSize );
        if ( ERROR_SUCCESS == lRet )
        {
            strBHOName = abyPath;
            int nPos = strBHOName.ReverseFind( '\\' );
            strBHOName = strBHOName.Right( strBHOName.GetLength() - nPos - 1 );// .Left(nPos + 1);
        }
    }

    // 检查IE是否已经加载了
    HMODULE hModuleJccatch = GetModuleHandle( strBHOName );
    FARPROC pUninstallJccatch = GetProcAddress( hModuleJccatch, _T("DllUnregisterServer") );
    if ( NULL != hModuleJccatch )
    {
        // 第一个插件提示信息
        strInfo += paszBHO[0 + dwLanguage]; // 注意语言类型
    }

    /*
    将来如还有发现不兼容的插件添加到此处
    */

    if ( NULL != hModuleJccatch )
    {
        int dwResult = AfxMessageBox( strInfo, MB_YESNO );
        if ( dwResult == IDNO )
        {
            return TRUE;
        }

        if ( NULL != pUninstallJccatch )
        {
            // 卸载FlashGet插件
            pUninstallJccatch();
        }

        return FALSE;
    }

    return TRUE;
}



#include <winable.h>
#include <atlconv.h>   

/*=============================================================================
函 数 名: SendAscii
功    能: 模拟键盘发送ascii
参    数: data:模拟键盘要发送的数据，shift：键盘是否按了shift键 
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2011/11/24  1.0     俞锦锦    创建
=============================================================================*/
void SendAscii(wchar_t data, BOOL shift)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));
    
    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        SendInput(1, input, sizeof(INPUT));
    }
    
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = data;
    SendInput(1, input , sizeof(INPUT));
    
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    
    SendInput(1, input+1, sizeof(INPUT));
    
    if (shift)
    {
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = VK_SHIFT;
        input[0].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, input, sizeof(INPUT));  
    }
}


/*=============================================================================
函 数 名: SendUnicode
功    能: 模拟键盘发送Unicode
参    数: data:模拟键盘要发送的数据 
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2011/11/24  1.0     俞锦锦    创建
=============================================================================*/
void SendUnicode(wchar_t data)
{
    INPUT input[2];
    memset(input, 0, 2 * sizeof(INPUT));
    
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = 0;
    input[0].ki.wScan = data;
    input[0].ki.dwFlags = 0x4;//KEYEVENTF_UNICODE;
    SendInput(1, input , sizeof(INPUT));

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = 0;
    input[1].ki.wScan = data;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | 0x4;//KEYEVENTF_UNICODE;
    SendInput(1, input+1 , sizeof(INPUT));
  //  SendInput(2, input, sizeof(INPUT));
}


/*=============================================================================
函 数 名: SendKeys
功    能: 模拟键盘发送Unicode/ascii，为方便使用，封装了SendUnicode() 和 SendAscii()两个函数
参    数: msg:要发送的字符串 
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2011/11/24  1.0     俞锦锦    创建
=============================================================================*/
void SendKeys(CString msg)
{
    short vk;
    BOOL shift;
    
    USES_CONVERSION;
    wchar_t* data = T2W(msg.GetBuffer(0));
    int len = wcslen(data);
    
    for(int i=0;i<len;i++)
    {
        if (data[i]>=0 && data[i]<256) //ascii字符
        {
            vk = VkKeyScanW(data[i]);
            
            if (vk == -1)
            {
                SendUnicode(data[i]);
            }
            else
            {
                if (vk < 0)
                {
                    vk = ~vk + 0x1;
                }
                
                shift = vk >> 8 & 0x1;
                
                if (GetKeyState(VK_CAPITAL) & 0x1)
                {
                    if (data[i]>='a' && data[i]<='z' || data[i]>='A' && data[i]<='Z')
                    {
                        shift = !shift;
                    }
                }
                
                SendAscii(vk & 0xFF, shift);
            }
        }
        else //unicode字符
        {
            SendUnicode(data[i]);
        }
    }
}



PVOID GetApiAddr(LPCSTR dllname, LPCSTR procname)
{
    HMODULE hDll = LoadLibraryA(dllname);
    if(NULL == hDll)
        return NULL;
    PVOID pProc = GetProcAddress(hDll, procname);
    FreeLibrary(hDll);
    return pProc;
}


/*=============================================================================
  函 数 名： GetIdlePort
  功    能： 获取指定端口区间的一个空闲端口
  算法实现： 
  全局变量： 
  参    数： wStartPort：起始监测端口，dwIP：本地ip，wEndPort：监测结束端口
  返 回 值： 空闲端口值 
=============================================================================*/
u16 GetIdlePort( u32 dwIP, u16 wStartPort, u16 wEndPort )
{
	u16 wPort = wStartPort;
	BOOL32 bContinue = TRUE;
	for (u16 wIndex = 0; bContinue; wIndex++)
	{
		SOCKET ListenSocket;
		ListenSocket = socket(AF_INET, SOCK_DGRAM, 0);
		if (ListenSocket != INVALID_SOCKET) 
		{
			sockaddr_in service;
			service.sin_family = AF_INET;
			service.sin_addr.s_addr = htonl(dwIP);
			wPort = wPort + wIndex;
			service.sin_port = htons(wPort);
			if (bind( ListenSocket, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) 
			{
				closesocket(ListenSocket);
				//超出wEndPort直接跳出循环,并返回无效端口
				if ( wPort > wEndPort )
				{
					wPort = 0xFFFF;
					bContinue = FALSE;
					break;
				}
				continue;
			}
			closesocket(ListenSocket);
			break;
		}
	}
	return wPort;
}




BOOL SaveBmp(HBITMAP hBitmap, CString FileName)
{
    HDC hDC; 
    //当前分辨率下每象素所占字节数 
    int iBits; 
    //位图中每象素所占字节数 
    WORD wBitCount; 
    //定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
    DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0; 
    //位图属性结构 
    BITMAP Bitmap; 
    //位图文件头结构 
    BITMAPFILEHEADER bmfHdr; 
    //位图信息头结构 
    BITMAPINFOHEADER bi; 
    //指向位图信息头结构 
    LPBITMAPINFOHEADER lpbi; 
    //定义文件，分配内存句柄，调色板句柄 
    HANDLE fh, hDib, hPal,hOldPal=NULL; 
	
    //计算位图文件每个像素所占字节数 
    hDC = CreateDC("DISPLAY", NULL, NULL, NULL); 
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
    DeleteDC(hDC); 
    if (iBits <= 1) wBitCount = 1; 
    else if (iBits <= 4) wBitCount = 4; 
    else if (iBits <= 8) wBitCount = 8; 
    else wBitCount = 24; 
	
    GetObject( hBitmap, sizeof( Bitmap ), ( LPSTR )&Bitmap ); 
    bi.biSize = sizeof( BITMAPINFOHEADER ); 
    bi.biWidth = Bitmap.bmWidth; 
    bi.biHeight = Bitmap.bmHeight; 
    bi.biPlanes = 1; 
    bi.biBitCount = wBitCount; 
    bi.biCompression = BI_RGB; 
    bi.biSizeImage = 0; 
    bi.biXPelsPerMeter = 0; 
    bi.biYPelsPerMeter = 0; 
    bi.biClrImportant = 0; 
    bi.biClrUsed = 0; 
	
    dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight; 
	
    //为位图内容分配内存 
    hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER)); 
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
    *lpbi = bi; 
	
    // 处理调色板 
    hPal = GetStockObject(DEFAULT_PALETTE); 
    if (hPal) 
    { 
        hDC = ::GetDC(NULL); 
        //hDC = m_pDc->GetSafeHdc(); 
        hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
        RealizePalette(hDC); 
    } 
    // 获取该调色板下新的像素值 
    GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
        +dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 
	
    //恢复调色板 
    if (hOldPal) 
    { 
        ::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
        RealizePalette(hDC); 
        ::ReleaseDC(NULL, hDC); 
    } 
	
	
    //创建位图文件 
    fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
	
    if (fh == INVALID_HANDLE_VALUE) return FALSE; 
	
    // 设置位图文件头 
    bmfHdr.bfType = 0x4D42; // "BM" 
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize; 
    bmfHdr.bfSize = dwDIBSize; 
    bmfHdr.bfReserved1 = 0; 
    bmfHdr.bfReserved2 = 0; 
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize; 
    // 写入位图文件头 
    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
    // 写入位图文件其余内容 
    WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL); 
    //清除 
    GlobalUnlock(hDib); 
    GlobalFree(hDib); 
    CloseHandle(fh); 
	
    return TRUE; 
}
