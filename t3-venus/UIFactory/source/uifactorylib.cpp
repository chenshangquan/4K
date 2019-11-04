// uifactorylib.cpp: implementation of the CUIFactoryLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "uifactorylib.h"
#include "SystemInfoManage.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUIFactoryLib::CUIFactoryLib()
{

}

CUIFactoryLib::~CUIFactoryLib()
{

}




void CUIFactoryLib::InitUIFactory( String strSystemName )
{
    if (  CSystem::GetSingletonPtr() == NULL  ) 
    {
        new CSystem( strSystemName );
		CSystem::GetSingletonPtr()->Launch();
    }  
}


void CUIFactoryLib::UnInitUIFactory()
{
    CSystem *pSystem = CSystem::GetSingletonPtr();
    if (  pSystem ) 
    {
        delete pSystem ;
        pSystem = NULL;
    }
}
 

bool  CUIFactoryLib::SetPropertyValue( const IValue& value,   String strWndName, const IWndTree* pWndTree /*= NULL */)
{
    const IWndTree *pItem = GetWindow ( strWndName , pWndTree );
    if ( pItem == NULL )
    {
        return false;
    }
    
    return SetPropertyValue( value, pItem->m_ptItemData->pWnd , pItem->m_ptItemData->strType );
}

bool  CUIFactoryLib::SetPropertyValue( const IValue& value, const Window* window,  const String& strWndType )
{
    return CPropertyAssist::GetSingletonPtr()->SetProperty( value,  window, strWndType );
}


bool  CUIFactoryLib::GetPropertyValue( IValue& value ,   String strWndName,  const IWndTree* pWndTree /*= NULL */)
{
    const IWndTree *pItem =  GetWindow ( strWndName ,pWndTree );
    if ( pItem == NULL )
    {
        return false;
    }
    
    return GetPropertyValue( value, pItem->m_ptItemData->pWnd , pItem->m_ptItemData->strType );
}


bool  CUIFactoryLib::GetPropertyValue(   IValue& value, const Window* window,  const String& strWndType )
{
    return	 CPropertyAssist::GetSingletonPtr()->GetValue(  value,  window, strWndType );
}

bool  CUIFactoryLib::HandleMsg( WindowMsg* pMsg )
{
    return CWndMsgEventManage::GetSingletonPtr()->TransMsg( pMsg );
}

void  CUIFactoryLib::UpdateUI(  IWndTree* pWndTree )
{
    if ( pWndTree != 0 )
    {
        WndInfo* pInfo = pWndTree->GetItemData();
        if ( pInfo != 0 )
        {
			HWND hWnd = 0;
			CWnd* pWnd = pInfo->pWnd->GetParent();
			if ( pWnd != NULL && pInfo->pWnd->GetStyle() & WS_CHILD )
			{
				hWnd = pInfo->pWnd->m_hWnd;
				pWnd->PostMessage( WM_REDRAW_UI, 0, (LPARAM)hWnd );
			}
			else
			{
				pInfo->pWnd->PostMessage( WM_REDRAW_UI, 0, (LPARAM)0 );
			}
        }
    }
}

void  CUIFactoryLib::UpdateUI( String strWndName,   IWndTree* pWndTree/* = NULL*/)
{
    const IWndTree*  p  =  GetWindow( strWndName, pWndTree);
    IWndTree* p2 = const_cast<IWndTree* > (p);
    UpdateUI( p2 );
}

short  CUIFactoryLib::ShowWindow( String strWndName, bool bShow /*= true */,const IWndTree* pWndTree /*= NULL */, BOOL bReDraw )
{ 

    if ( !strWndName.empty() )
    {
        pWndTree = const_cast<IWndTree* >(  GetWindow( strWndName,pWndTree ) );
    } 
    if ( pWndTree == 0   )
    {
        return false;
	}
    
    Value_WindowVisible valueVisible;
    valueVisible.bVisible = bShow;
	   
    bool re =   SetPropertyValue( valueVisible , pWndTree->m_ptItemData->pWnd , pWndTree->m_ptItemData->strType ); 

	if ( bReDraw )
	{
		UpdateUI( const_cast<IWndTree *>(pWndTree) );
	}

    short wRe = NO_ERROR;
    wRe = ( re == true? NO_ERROR:-1);
    return wRe;
}


int CUIFactoryLib::Domodal( String strName, const IWndTree* pWndTree, BOOL bCenter )
{
	CWnd *p = GetWindowPtr( strName, pWndTree );
 
	if( NULL != p )
	{
        if ( bCenter )
        {
		    p->CenterWindow();
        }
		return	((CTransparentDlg*)p)->StartModalLoop();	 
	}
	return -1;
} 

int CUIFactoryLib::Domodal( Window* pWnd  )
{ 
	
	if( NULL != pWnd )
	{   
        CTransparentDlg* pTransWnd = (CTransparentDlg*)pWnd;

		if ( pTransWnd->IsInModalLoop() )
		{
			pTransWnd->StopModalLoop( -1 );
		}
		return 	pTransWnd->StartModalLoop();	 
	}

	return -1;
}

 
void CUIFactoryLib::Endmodal( int nResult, String strName, const IWndTree* pWndTree    )
{
	CWnd *p = GetWindowPtr( strName, pWndTree );
	
	if( NULL != p )
	{
		 ((CTransparentDlg*)p)->StopModalLoop( nResult);	 
	}
} 

void CUIFactoryLib::Endmodal( int nResult, Window* pWnd  )
{ 
	if( NULL != pWnd )
	{
		((CTransparentDlg*)pWnd)->StopModalLoop( nResult);	 
	}
}


bool  CUIFactoryLib::EnableWindow( String strWndName, bool bEnable /* = true */, const IWndTree* pWndTree /* = NULL */ )
{
	Value_WindowEnable valueEnable;
	valueEnable.bEnable = bEnable;
	
	bool bRet =  SetPropertyValue( valueEnable, strWndName, pWndTree );
	UpdateUI( strWndName, const_cast<IWndTree*>(pWndTree) );
	return bRet;
}


bool  CUIFactoryLib::SetCaption( String strWndName, String strCaption, const IWndTree* pWndTree /* = NULL */, BOOL bReDraw )
{
	Value_WindowCaption valueCaption;
    valueCaption.strCaption = strCaption;
	
	bool bRet =  SetPropertyValue( valueCaption, strWndName, pWndTree );
	if ( bReDraw )
	{
		UpdateUI( strWndName, const_cast<IWndTree*>(pWndTree) );
	}	
	return bRet;
}

bool  CUIFactoryLib::GetCaption( String strWndName, String& strCaption, const IWndTree* pWndTree /* = NULL */ )
{
	Value_WindowCaption valueCaption;
    valueCaption.strCaption = "";
	bool bRe =  GetPropertyValue( valueCaption, strWndName, pWndTree );
	
    strCaption = valueCaption.strCaption;
	
	return bRe;
}

bool  CUIFactoryLib::SetFocus( String strWndName, const IWndTree* pWndTree /* = NULL */ )
{
	Window* pWnd =  GetWindowPtr( strWndName, pWndTree );
	if ( pWnd != NULL )
	{
		pWnd->SetFocus();
	}
	return true;
}

bool  CUIFactoryLib::SetCheckState( String strWndName, int nCheckState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_CButtonCheckState valueCheckState;
	valueCheckState.nCheckState = nCheckState;
	
	return  SetPropertyValue( valueCheckState, strWndName, pWndTree );
}

bool  CUIFactoryLib::GetCheckState( String strWndName, int& nCheckState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_CButtonCheckState valueCheckState;
	valueCheckState.nCheckState = 0;
	bool bRe =  GetPropertyValue( valueCheckState, strWndName, pWndTree );

	nCheckState = valueCheckState.nCheckState;
	return  bRe;
}

bool  CUIFactoryLib::SetSwitchState( String strWndName, bool bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_SwitchState valueState;
	valueState.bState = bState;
	
	return  SetPropertyValue( valueState, strWndName, pWndTree );
}

bool  CUIFactoryLib::GetSwitchState( String strWndName, bool& bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_SwitchState valueState;
    valueState.bState = false;
	bool bRe =  GetPropertyValue( valueState, strWndName, pWndTree );
	
    bState = valueState.bState;	
	return bRe;
}

bool  CUIFactoryLib::SetTransparentDlgImage( String strWndName, String strPath, const IWndTree* pWndTree /* = NULL */ )
{
// 	Value_TransparentDlgImage valueImage;
// 	valueImage.strImage = strPath;
// 	bool bRe =  SetPropertyValue( valueImage, strWndName, pWndTree );
	return 0;
}

bool  CUIFactoryLib::SetTransStaticImage( String strWndName, String strPath, const IWndTree* pWndTree /* = NULL */ )
{
    Value_TransparentStaticImage valueImage;
	valueImage.strImage = strPath;

    bool bRe =  SetPropertyValue( valueImage, strWndName, pWndTree );
    return bRe;
}

void  CUIFactoryLib::ReleaseSingleImage( String strPath )
{
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + strPath;

	CSrcManage::ReleaseSingleImage(strFile.c_str());
}

bool  CUIFactoryLib::SetSelState( String strWndName, bool bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonSel valueSel;
	valueSel.bSel = bState;
	
	return  SetPropertyValue( valueSel, strWndName, pWndTree );
}

bool  CUIFactoryLib::GetSelState( String strWndName, bool& bState, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonSel valueSel;
    valueSel.bSel = false;
	bool bRe =  GetPropertyValue( valueSel, strWndName, pWndTree );
	bState = valueSel.bSel ;
	return bRe;
}

bool  CUIFactoryLib::SetDragBtnOnline( String strWndName, bool bOnline, const IWndTree* pWndTree /* = NULL */ )
{
	Value_DragButtonOnline valueOnline;
	valueOnline.bOnline = bOnline;
	
	return  SetPropertyValue( valueOnline, strWndName, pWndTree );
}
 
bool  CUIFactoryLib::IsVisible( String strWndName, const IWndTree* pWndTree /*= NULL*/ )
{
   Value_WindowVisible bVisble;
   bVisble.bVisible = false;
   bool re  =  GetPropertyValue( bVisble, strWndName, pWndTree );
   if ( re = false )
   {
//       TRACE("\n[ IsVisible]GetPropertyValue return false \n");
   }
   return bVisble.bVisible;
}




const IWndTree*  CUIFactoryLib::GetWindow( String strName, const IWndTree* pWndTree /* = NULL*/ )  
{     
    if ( strName.empty() )
    {
        return pWndTree;
    }


    if ( pWndTree == NULL  )
    {   
        char chPart = CWndTreeHelp::chPartitionChar;
        int size = strName.find( chPart ); 

        if ( size >= 0 ) 
        {
            String strFirstWnd = strName.substr(0,size);
            IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( strFirstWnd));
            if ( pTree ) 
            {
                String strWnd = strName.substr(size+1,strName.size());
                return GetWindow(strWnd,pTree);
            }
            
        }
        
        return  CWindowManage::GetSingletonPtr()->GetWindowTree( strName);
        
    } 


    
    return  CWndTreeHelp::GetWindow( strName,  pWndTree );	  
}




const IWndTree*  CUIFactoryLib::GetWindow( Window* pWnd, const IWndTree* pWndTree )
{
    return  CWndTreeHelp::GetWindow( pWnd,pWndTree );		  
}


Window*  CUIFactoryLib::GetWindowPtr( String strName, const IWndTree* pWndTree /* = NULL*/ )
{
    const IWndTree* pTreeInfo = GetWindow( strName, pWndTree );
    const WndInfo *pInfo = NULL;
    if ( pTreeInfo != NULL && NULL != ( pInfo = pTreeInfo->m_ptItemData ) )
    {
        return pInfo->pWnd;
    } 
    return NULL;
}

bool  CUIFactoryLib::LoadScheme( String strSchemeName,IWndTree* pWndTree /*= NULL*/ , String strWndName /*= ""*/ , bool bInvalidate /*= true */)
{
	if ( !strWndName.empty() )
	{
		pWndTree = const_cast<IWndTree* >(  GetWindow( strWndName,pWndTree ) );
	} 
	if ( pWndTree == 0   )
	{
		return false;
	}
	bool bRet = CSchemeHelp::LoadScheme(strSchemeName,pWndTree);
	
    if ( bInvalidate )
    {
        UpdateUI( pWndTree );
    }
	
	return bRet;
}

bool CUIFactoryLib::DestoryWnd( Window* pWnd )
{
	bool re = false;
	HWND hWd = 0;
	if ( pWnd && 0 != (hWd == pWnd->GetSafeHwnd() ) )
	{
		if ( !(::GetWindowLong( hWd, GWL_STYLE) & WS_CHILD) )
		{
			pWnd->PostMessage( WM_CLOSE );
			re = true;
		}
	}

	return re;
}

bool CUIFactoryLib::DestoryWnd( String strWndName )
{
    IWndTree *pWndtre = const_cast<IWndTree *>(GetWindow( strWndName  ));
	return DestoryWnd( pWndtre );
}


bool CUIFactoryLib::DestoryWnd(   IWndTree* pWndTree )
{
	if ( NULL == pWndTree  )
	{
		return false;
	}
	IWndTree* pParent = pWndTree->GetParentItem();
	if ( pParent == 0 )
	{
		return false;
	}
	
	WndInfo* pWndInfo = pWndTree->GetItemData();
	Window* pWnd = NULL;;
	if (  NULL ==pWndInfo || NULL == (pWnd = pWndInfo->pWnd) )
	{
		return false;
	} 
	
	if ( 0 == pWnd->GetSafeHwnd() )
	{
	   return pParent->DeleteItem( pWndTree->GetItemName() );
	}
	
	bool bRe = false;
	
 
	DWORD dwStle = ::GetWindowLong(pWnd->GetSafeHwnd(),GWL_STYLE);
    
	//子窗口不需销毁 2012.12.12 by 俞锦锦
	if ( !(dwStle & WS_CHILD) )
	{   
		pWnd->PostMessage( WM_CLOSE, 0 , 6 );
		
		bRe = pParent->DeleteItem( pWndTree->GetItemName() );
		
	}  
	
	
	return bRe;	
}

bool CUIFactoryLib::DestoryAllWnd()
{
    IWndTree* pWndRoot = CWindowManage::GetSingletonPtr()->GetRoot();
	for ( int i = 0; i< pWndRoot->GetItemCount(); i++ )
	{
		IWndTree* pWnd = pWndRoot->GetItemByIndex( i );
		DestoryWnd( pWnd );
	}
	return true;
}
 

/**  最小化窗口
*  @return 是否最小化成功
*  @auth yjj 2012.12.12
*/
bool CUIFactoryLib::MinmizeWnd( )
{

	bool bRe = false;
    IWndTree* pWndTree = CWindowManage::GetSingletonPtr()->GetRoot();
    if ( NULL == pWndTree )
    {
        return false;
    }
    
    int count = pWndTree->GetItemCount();
	
    for ( int i = 0; i<count; i++ )
    {
		
        IWndTree* pSubWndTree = pWndTree->GetItemByIndex( i );
		WndInfo *pWdInfo = NULL;
        if ( NULL != pSubWndTree && NULL != ( pWdInfo = pSubWndTree->GetItemData()) )
        {
			
			CWnd *pWnd = pWdInfo->pWnd ;
			//如果窗口不是child类型，则进行隐藏 2012.12.12 by yjj
			if ( pWnd && 0 != pWnd->GetSafeHwnd() && pWnd->IsWindowVisible() )
			{	
				if( !(::GetWindowLong(pWnd->GetSafeHwnd(),GWL_STYLE)& WS_CHILD) )
				{
					pWnd->ShowWindow( SW_MINIMIZE );
					bRe = true;
				} 
			}
        } 
		
    } 
    
    return bRe; 
}

//strSavePropertyName 要保存的属性名，bForceSave 如果要保存的属性不在当前方案中，是否强制保存
bool  CUIFactoryLib::SaveToFile( String strWndName ,string strSaveWndName/* = ""*/,string strSavePropertyName/* = ""*/, BOOL  bForceSave/* = false*/)
{ 
 
   return CSaveXmlHelp::SaveXml( strWndName,strSaveWndName ,strSavePropertyName, bForceSave ); 
}


String  CUIFactoryLib::GetImagePath()
{
   return CSystem::GetSingletonPtr()->GetImagePath();
}



bool  CUIFactoryLib::HideAllWindow()
{
    bool bRe = false;
    IWndTree* pWndTree = CWindowManage::GetSingletonPtr()->GetRoot();
    if ( NULL == pWndTree )
    {
        return false;
    }
    
    int count = pWndTree->GetItemCount();
     
    for ( int i = 0; i<count; i++ )
    {

        IWndTree* pSubWndTree = pWndTree->GetItemByIndex( i );
		WndInfo *pWdInfo = NULL;
        if ( NULL != pSubWndTree && NULL != ( pWdInfo = pSubWndTree->GetItemData()) )
        {

			CWnd *pWnd = pWdInfo->pWnd ;
			//如果窗口不是child类型，则进行隐藏 2012.12.12 by yjj
			if ( pWnd && 0 != pWnd->GetSafeHwnd() && pWnd->IsWindowVisible() )
			{	
			  if( !(::GetWindowLong(pWnd->GetSafeHwnd(),GWL_STYLE)& WS_CHILD) )
			  {
			 	 pWnd->ShowWindow( SW_HIDE );
				 bRe = true;
			  } 
		   }
        } 
         
    } 
    
    return bRe;   
}

bool  CUIFactoryLib::SetComboText( String strWndName, String strText, const IWndTree* pWndTree /* = NULL */ )
{
	Value_TransparentComboBoxText valueText;
	valueText.strComboText = strText;
	return  SetPropertyValue( valueText, strWndName, pWndTree );
}

bool  CUIFactoryLib::GetComboText( String strWndName, String& strText, const IWndTree* pWndTree /* = NULL */ )
{
	Value_TransparentComboBoxText valueText;
	valueText.strComboText = "";
	bool bRe =  GetPropertyValue( valueText, strWndName, pWndTree );
	strText = valueText.strComboText ;
	return bRe;
}

bool CUIFactoryLib::SetComboListData( String strWndName, std::vector<CString> vecListData, const IWndTree* pWndTree /* = NULL */ )
{
	CWnd *p = GetWindowPtr( strWndName, pWndTree );
	
	if( NULL != p )
	{
		((CTransparentComboBox*)p)->UpdateComboList( &vecListData );
		
		if ( vecListData.size() > 0 )
		{
			((CTransparentComboBox*)p)->SetComboText("");
			((CTransparentComboBox*)p)->SetEnableWindow(TRUE);
	 	}
		else
		{
			((CTransparentComboBox*)p)->SetComboText("无");
			((CTransparentComboBox*)p)->SetEnableWindow(FALSE);
		}
	}

	return true;
}

bool CUIFactoryLib::CleanComboListData( String strWndName, const IWndTree* pWndTree /* = NULL */, String strDefText )
{
	std::vector<CString> vecListData;
	CWnd *p = GetWindowPtr( strWndName, pWndTree );
	
	if( NULL != p )
	{
		((CTransparentComboBox*)p)->SetComboText(strDefText.c_str());
		((CTransparentComboBox*)p)->UpdateComboList( &vecListData );	
		
		if ( "无" == strDefText )
		{
			((CTransparentComboBox*)p)->SetEnableWindow(FALSE);
		}
		else
		{
			((CTransparentComboBox*)p)->SetEnableWindow(TRUE);
		}
	}

	return true;
}


string CUIFactoryLib::GetVersion()
{
 
	return CSystemInfoManage::GetSingletonPtr()->GetVersion();
}


void CUIFactoryLib::SetWndPos(  POINT pt, String strWndName,   IWndTree* pWndTree/* = NULL*/, String strRelativeWnd/* = "" */)
{
	Window *pWnd = GetWindowPtr( strWndName, pWndTree );
	if ( NULL == pWnd )
	{
		return;
	}

	Window *pWndRelative = NULL;
	if ( !strRelativeWnd.empty() && NULL != (pWndRelative = GetWindowPtr( strRelativeWnd, pWndTree )) )
	{ 
	 
		ClientToScreen(pWndRelative->GetSafeHwnd(), &pt);	
	}
	
	
	if ( NULL != pWnd )
	{
		pWnd->SetWindowPos( NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE );
	}
}

void CUIFactoryLib::SetWndPos(POINT pt, String strWndName, int nWidth, int nHeight, IWndTree* pWndTree /*= NULL*/, String strRelativeWnd /*= "" */)
{
	Window *pWnd = GetWindowPtr( strWndName, pWndTree );
	
	if ( NULL == pWnd )
	{
		return;
	}

	Window *pWndRelative = NULL;
	if ( !strRelativeWnd.empty() && NULL != (pWndRelative = GetWindowPtr( strRelativeWnd, pWndTree )) )
	{ 
		
		ClientToScreen(pWndRelative->GetSafeHwnd(), &pt);	
	}

	if ( NULL != pWnd )
	{
		pWnd->SetWindowPos( NULL, pt.x, pt.y, nWidth, nHeight, SWP_SHOWWINDOW );
	}

}

bool CUIFactoryLib::SetEditFocusEnd( String strEditWndName, const IWndTree* pWndTree, BOOL bReDraw )
{
	Window* pWnd = GetWindowPtr( strEditWndName, pWndTree );
	if ( NULL != pWnd  )
	{ 
		((CEdit*) pWnd)->SetSel( -1 );        
    }

	return true;
}
