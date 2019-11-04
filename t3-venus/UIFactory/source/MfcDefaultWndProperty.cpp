// MfcDefaultWndProperty.cpp: implementation of the MfcDefaultWndProperty class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MfcDefaultWndProperty.h"
#include "PropertyHelp.h"
#include "System.h"
#include "WndTreeHelp.h"

//lint -e42    屏蔽pclint42错误

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

bool Property_WindowCaption::get( const Window* src, String& value ) const
{
	CString strName;
	static_cast<const Window*>(src)->GetWindowText( strName );
	value = strName;
    return true;
}

bool Property_WindowCaption::get( const Window* src, IValue& value ) const
{
	try
	{
		Value_WindowCaption& pValue = dynamic_cast<Value_WindowCaption&>(value);
		String strTemp;
		if ( get( src, strTemp ) == true )
		{
			pValue.strCaption = strTemp;
			return true;
		}
		else
		{
			return false;
		}
	}
	catch( bad_cast )
	{
		LOGEVENT( "Value_WindowCaptione::get 传入的参数不正确" );
		return false;
	}
}

bool Property_WindowCaption::set(Window* tag, const String& value)
{
	if (  (NULL != tag) && (NULL != tag->GetSafeHwnd()) )
	{
		tag->SetWindowText( value.c_str() );
	}
	return true;
}

bool Property_WindowCaption::set( Window* tag, const IValue& value )
{
	try
	{
		const Value_WindowCaption& pValue = dynamic_cast<const Value_WindowCaption&>(value); 	
		set( tag, pValue.strCaption );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowCaption::get 传入的参数不正确" );
		return false;
	}
}

bool Property_WindowPos::get( const Window* src, String& value ) const
{
	CRect rc;
	static_cast<const Window*>(src)->GetWindowRect( rc );
	Window* pWnd = static_cast<const Window*>(src)->GetParent();
	if ( pWnd != 0 )
	{
		pWnd->ScreenToClient( rc );
	}	
	value = CPropertyHelp::pointToString( rc.TopLeft() );
	return true;
}

bool Property_WindowPos::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_WindowPos& pValue = dynamic_cast<Value_WindowPos&>(value);
		CRect rc;
		static_cast<const Window*>(src)->GetWindowRect( rc );
		pValue.nX = rc.left;
		pValue.nY = rc.top;
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowPos::get 传入的参数不正确" );
		return false;
	}
	return false;
}

bool Property_WindowPos::set(Window* tag, const String& value)
{
	if (  (NULL == tag) && (NULL == tag->GetSafeHwnd()) )
	{
		return false;
	}
	POINT pt = CPropertyHelp::stringToPoint( value );
   
    //自适应分辨率
    CPropertyHelp::ResolutionAdp( pt.x, pt.y );
	return tag->SetWindowPos( NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE );
}

bool Property_WindowPos::set( Window* tag, const IValue& value )
{
	if (  (NULL == tag) && (NULL == tag->GetSafeHwnd()) )
	{
		return false;
	}
	try
	{
		const Value_WindowPos& pValue = dynamic_cast<const Value_WindowPos&>(value);
		tag->SetWindowPos( NULL, pValue.nX, pValue.nY, 0, 0, SWP_NOSIZE|SWP_NOACTIVATE);
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowPos::set 传入的参数不正确" );
		return false;
	}
}


bool Property_WindowSize::get( const Window* src, String& value ) const
{
	CRect rc;
	static_cast<const Window*>(src)->GetWindowRect( rc );
	value = CPropertyHelp::sizeToString( rc.Size() );
	return true;
}

bool Property_WindowSize::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_WindowSize& pValue = dynamic_cast<Value_WindowSize&>(value);
		CRect rc;
		static_cast<const Window*>(src)->GetWindowRect( rc );
		pValue.nWidth = rc.Width();
		pValue.nHeight = rc.Height();
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowSize::get 传入的参数不正确" );
		return false;
	}
}

bool Property_WindowSize::set(Window* tag, const String& value)
{
	SIZE sz = CPropertyHelp::stringToSize( value );
    //自适应分辨率
    CPropertyHelp::ResolutionAdp( sz.cx, sz.cy );
	return tag->SetWindowPos( NULL, 0, 0, sz.cx, sz.cy, SWP_NOMOVE|SWP_NOACTIVATE );
}

bool Property_WindowSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_WindowSize& pValue = dynamic_cast<const Value_WindowSize&>(value);
		tag->SetWindowPos( NULL, 0, 0, pValue.nWidth, pValue.nHeight, SWP_NOMOVE|SWP_NOACTIVATE );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowSize::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_WindowVisible::get( const Window* src, String& value ) const
{
	bool bVisible = (bool)const_cast<Window*>(src)->IsWindowVisible();
	value = CPropertyHelp::boolToString( bVisible );
	return true;
}

bool Property_WindowVisible::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_WindowVisible& pValue = dynamic_cast<Value_WindowVisible&>(value);
		pValue.bVisible = (bool)const_cast<Window*>(src)->IsWindowVisible();
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowVisable::get 传入的参数不正确" );
		return false;
	}
}

bool Property_WindowVisible::set(Window* tag, const String& value)
{
	bool bVisible = CPropertyHelp::stringToBool( value );
	if ( bVisible )
	{
		tag->ShowWindow( SW_SHOW );
	}
	else
	{
		tag->ShowWindow( SW_HIDE );
	}
	return true;
}

bool Property_WindowVisible::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_WindowVisible& pValue = dynamic_cast<const Value_WindowVisible&>(value);
		tag->ShowWindow( pValue.bVisible );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowVisable::set 传入的参数不正确" );
		return false;
	}
}

// window ower
bool Property_WindowOwer::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_WindowOwer::get( const Window* src, IValue& value ) const
{
	return false;
}

bool Property_WindowOwer::set(Window* tag, const String& value)
{
	return false;
}

bool Property_WindowOwer::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_WindowOwer& pValue = dynamic_cast<const Value_WindowOwer&>(value);
		tag->SetOwner( pValue.pWnd );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowOwer::set 传入的参数不正确" );
		return false;
	}
}

// window enable
bool Property_WindowEnable::get( const Window* src, String& value ) const
{
	bool bEnable = (bool)const_cast<Window*>(src)->IsWindowEnabled();
	value = CPropertyHelp::boolToString( bEnable );
	return true;
}

bool Property_WindowEnable::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_WindowEnable& pValue = dynamic_cast<Value_WindowEnable&>(value);
		pValue.bEnable = (bool)const_cast<Window*>(src)->IsWindowEnabled();
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowEnable::get 传入的参数不正确" );
		return false;
	}
}

bool Property_WindowEnable::set(Window* tag, const String& value)
{
	bool bEnable = CPropertyHelp::stringToBool( value );
    
	if (  (NULL != tag) && (NULL != tag->GetSafeHwnd()) )
	{
		tag->EnableWindow( bEnable );
	}
	
	
	return true;
}

bool Property_WindowEnable::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_WindowEnable& pValue = dynamic_cast<const Value_WindowEnable&>(value);
		tag->EnableWindow( pValue.bEnable );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_WindowEnable::set 传入的参数不正确" );
		return false;
	}
}
// window enable end


 // transparentDlg MoveStatus begin
 bool Property_TransparentDlgBaseMoveStatus::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgBaseMoveStatus::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgBaseMoveStatus::set(Window* tag, const String& value)
 {   
     if ( CTransparentDlgBase* pWnd = dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag)) )
     {
         pWnd->SetMoveStatus( CPropertyHelp::stringToBool( value ) );
         return true;
     }
     return false;
 }
 
 bool Property_TransparentDlgBaseMoveStatus::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgBaseMoveStatus& pValue = dynamic_cast<const Value_TransparentDlgBaseMoveStatus&>(value);
         
         if ( CTransparentDlgBase* pWnd = dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag)) )
         {
             pWnd->SetMoveStatus( pValue.bMove );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgMoveStatus::set 传入的参数不正确" );
         return false;
     }
 }
 
 
 // transparentDlg BkStretch begin
 bool Property_TransparentDlgBaseBkStretch::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgBaseBkStretch::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgBaseBkStretch::set(Window* tag, const String& value)
 {   
     if ( CTransparentDlgBase* pWnd = dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag)) )
     {
         pWnd->SetBkStretch( CPropertyHelp::stringToBool( value ) );
         return true;
     }
     return false;
 }
 
 bool Property_TransparentDlgBaseBkStretch::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgBaseBkStretch& pValue = dynamic_cast<const Value_TransparentDlgBaseBkStretch&>(value);
         
         if ( CTransparentDlgBase* pWnd = dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag)) )
         {
             pWnd->SetBkStretch( pValue.bIsBkStretch );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgBkStretch::set 传入的参数不正确" );
         return false;
     }
 } 
 
 
  // transparentDlg AutoHideStatus begin
 bool Property_TransparentDlgBaseAutoHideStatus::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgBaseAutoHideStatus::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgBaseAutoHideStatus::set(Window* tag, const String& value)
 {   
     try 
     {
         bool bAutoHide = CPropertyHelp::stringToBool( value );
         if ( CTransparentDlgBase* pWnd = (dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetAutoHideStatus( bAutoHide );
         }
         return true;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgAutoHideStatus::set 传入的参数不正确" );
         return false;
     }	
 }
 
 bool Property_TransparentDlgBaseAutoHideStatus::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgBaseAutoHideStatus& pValue = dynamic_cast<const Value_TransparentDlgBaseAutoHideStatus&>(value);		
         if ( CTransparentDlgBase* pWnd = (dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetAutoHideStatus( pValue.bHide );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgAutoHideStatus::set 传入的参数不正确" );
         return false;
     }
}




 // transparent wnd image begin
 bool Property_TransparentDlgBaseImage::get( const Window* src, IValue& value ) const
 {	
     return false;
 }
 
 bool Property_TransparentDlgBaseImage::get( const Window* src, String& value ) const
 {
     return false;
 }
 bool Property_TransparentDlgBaseImage::set(Window* tag, const String& value)
 {   
     try 
     {
         String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
         String strFile = strImageFolder + "//" + value;

         if ( CTransparentDlgBase* pWnd = (dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetImage( strFile.c_str() );
         }
         return true;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgImage::set 传入的参数不正确" );
         return false;
     }	
 }
 
 bool Property_TransparentDlgBaseImage::set( Window* tag, const IValue& value )
 {
     try 
     {
         const Value_TransparentDlgBaseImage& pValue = dynamic_cast<const Value_TransparentDlgBaseImage&>(value);
         String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
         String strFile = strImageFolder + "//" + pValue.strImage;
         
         if ( CTransparentDlgBase* pWnd = (dynamic_cast<CTransparentDlgBase*>(const_cast<Window*>(tag))) )
         {
             pWnd->SetImage( strFile.c_str() );
             return true;
         }
         return false;
     }
     catch( bad_cast )
     {
         LOGEVENT( "Property_TransparentDlgImage::set 传入的参数不正确" );
         return false;
     }
}


//IPAddressCtrlData begin
bool Property_CIPAddressCtrlData::get( const Window* src, String& value ) const
{
	DWORD dwAddress = 0; 
	(dynamic_cast<CIPAddressCtrl*>(const_cast<Window*>(src)))->GetAddress( dwAddress );
	value = CPropertyHelp::DWORDToString( dwAddress );
	return true;
}

bool Property_CIPAddressCtrlData::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_CIPAddressCtrlData& pValue = dynamic_cast<Value_CIPAddressCtrlData&>(value);
		DWORD dwAddress = 0; 
        Window*pSrc = const_cast<Window*>(src); 
       
		if ( CIPAddressCtrl * pIPCtrl = dynamic_cast< CIPAddressCtrl*>(pSrc) )
		{
			if (  pIPCtrl != NULL )
			{
				pIPCtrl->GetAddress( pValue.dwIP );
			}
		}
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::get 传入的参数不正确" );
		return false;
	}

    return true;
}

bool Property_CIPAddressCtrlData::set(Window* tag, const String& value)
{   
	DWORD dwAddress = CPropertyHelp::StringToDWORD( value );
	if ( CIPAddressCtrl * pIPCtrl = dynamic_cast<CIPAddressCtrl*>(const_cast<Window*>(tag)) )
	{
		pIPCtrl->SetAddress( dwAddress );
		return true;
	}
	return false;
}

bool Property_CIPAddressCtrlData::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_CIPAddressCtrlData& pValue = dynamic_cast<const Value_CIPAddressCtrlData&>(value);
		if ( CIPAddressCtrl * pIPCtrl = dynamic_cast<CIPAddressCtrl*>(const_cast<Window*>(tag)) )
		{
			pIPCtrl->SetAddress( pValue.dwIP );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}
}
/*
//IPAddressCtrlData end
//bmpwndimage begin
bool Property_BmpWndImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_BmpWndImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_BmpWndImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
	{
		pBmpWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_BmpWndImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_BmpWndImage& pValue = dynamic_cast<const Value_BmpWndImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}
}


//bmpwndimage end

// bmpmovestatus begin
bool Property_BmpWndMoveStatus::get( const Window* src, IValue& value ) const 
{	
	return false;
}

bool Property_BmpWndMoveStatus::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_BmpWndMoveStatus::set(Window* tag, const String& value)
{   
	try 
	{
		bool bMove = CPropertyHelp::stringToBool( value );
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetMoveStatus( bMove );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_BmpWndMoveStatus::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_BmpWndMoveStatus& pValue = dynamic_cast<const Value_BmpWndMoveStatus&>(value);
	
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetMoveStatus( pValue.bCanMove );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}
}

//bmpmovestatus end


// bmpstrethstatus begin
bool Property_BmpWndStrethStatus::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_BmpWndStrethStatus::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_BmpWndStrethStatus::set(Window* tag, const String& value)
{   
	try 
	{
		bool bStreth = CPropertyHelp::stringToBool( value );
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetStrethStatus( bStreth );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_BmpWndStrethStatus::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_BmpWndStrethStatus& pValue = dynamic_cast<const Value_BmpWndStrethStatus&>(value);
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetStrethStatus( pValue.bStreth );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IPAddressCtrlData::set 传入的参数不正确" );
		return false;
	}
}

//bmpmovestatus end

// bmpstrethstatus begin
bool Property_BmpWndChanageRgnStatus::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_BmpWndChanageRgnStatus::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_BmpWndChanageRgnStatus::set(Window* tag, const String& value)
{   
	try 
	{
		bool bChange = CPropertyHelp::stringToBool( value );
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetChangeRgnStatus( bChange );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_BmpWndChanageRgnStatus::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_BmpWndChanageRgnStatus::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_BmpWndChanageRgnStatus& pValue = dynamic_cast<const Value_BmpWndChanageRgnStatus&>(value);
		if ( CBmpWnd* pBmpWnd = dynamic_cast<CBmpWnd*>(const_cast<Window*>(tag)) )
		{
			pBmpWnd->SetChangeRgnStatus( pValue.bChanageRgn );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_BmpWndChanageRgnStatus::set 传入的参数不正确" );
		return false;
	}
}

//bmpmovestatus end
*/

//CButton check  状态   begin 
bool Property_CButtonCheckState::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_CButtonCheckState& pValue = dynamic_cast<Value_CButtonCheckState&>(value);
        pValue.nCheckState = (dynamic_cast<CButton*>(const_cast<Window*>(src)))->GetCheck( );
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CButtonCheckState::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_CButtonCheckState::get( const Window* src, String& value ) const
{
    try 
    { 
        int  nCheckState = (dynamic_cast<CButton*>(const_cast<Window*>(src)))->GetCheck( );
        value = CPropertyHelp::intToString(nCheckState);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CButtonCheckState::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_CButtonCheckState::set(Window* tag, const String& value)
{   
    try 
    {  
        int nCheckState = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CButton*>(const_cast<Window*>(tag)))->SetCheck(  nCheckState );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CButtonCheckState::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_CButtonCheckState::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CButtonCheckState& pValue = dynamic_cast<const Value_CButtonCheckState&>(value);
        (dynamic_cast<CButton*>(const_cast<Window*>(tag)))->SetCheck( pValue.nCheckState );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CButtonCheckState::set 传入的参数不正确" );
        return false;
    }	
} 
//CButton check  状态    end

//TouchList Layout Algroithm 算法  begin 
bool Property_LayoutAlgorithm::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_LayoutAlgorithm& pValue = dynamic_cast<Value_LayoutAlgorithm&>(value);
		if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(src)) )
		{
			pValue.strAlgorithm = pList->GetLayoutAlgroithm();
			return true;
		}
		return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_LayoutAlgorithm::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_LayoutAlgorithm::get( const Window* src, String& value ) const
{
	if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(src)) )
	{
		value = pList->GetLayoutAlgroithm();
	}	
    return false;
}

bool Property_LayoutAlgorithm::set(Window* tag, const String& value)
{   
	if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
	{
		return pList->SetLayoutAlgroithm( value );
	}
	return false;
}

bool Property_LayoutAlgorithm::set( Window* tag, const IValue& value )
{
    try 
    {
		const Value_LayoutAlgorithm& pValue = dynamic_cast< const Value_LayoutAlgorithm&>(value);
		if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
		{
			return pList->SetLayoutAlgroithm( pValue.strAlgorithm );
		}     
		return false;	
	}
    catch( bad_cast )
    {
        LOGEVENT( "Property_LayoutAlgorithm::set 传入的参数不正确" );
        return false;
    }	
} 
//TouchList Layout Algroithm 算法    end


//TouchList Sort Algroithm 算法  begin 
bool Property_SortAlgorithm::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_SortAlgorithm& pValue = dynamic_cast<Value_SortAlgorithm&>(value);
		if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(src)) )
		{
			pValue.strAlgorithm = pList->GetSortAlgroithm();
			return true;
		} 
		return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_SortAlgorithm::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_SortAlgorithm::get( const Window* src, String& value ) const
{
	
	if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(src)) )
	{
		value = pList->GetSortAlgroithm();
		return true;
	}	
	
    return false;
}

bool Property_SortAlgorithm::set(Window* tag, const String& value)
{     
	if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
	{
		return pList->SetSortAlgroithm( value );
	}
	return false;
}

bool Property_SortAlgorithm::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_SortAlgorithm& pValue = dynamic_cast< const Value_SortAlgorithm&>(value);

		if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
		{
			return pList->SetSortAlgroithm( pValue.strAlgorithm );	
		}
		return false;
	}
    catch( bad_cast )
    {
        LOGEVENT( "Property_SortAlgorithm::set 传入的参数不正确" );
        return false;
    }	
} 
//TouchList Sort Algroithm 算法    end


//TransparentList Drag begin
bool Property_TransparentListDrag::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentListDrag& pValue = dynamic_cast<Value_TransparentListDrag&>(value);
        pValue.bCanDrag = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src)))->GetDragEnable( );
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TouchListDrag::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentListDrag::get( const Window* src, String& value ) const
{
    try 
    { 
        bool bCanDrag = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src)))->GetDragEnable( );
        value = CPropertyHelp::boolToString(bCanDrag);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TouchListDrag::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentListDrag::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bCanDrag = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetDragEnable( bCanDrag );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TouchListDrag::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentListDrag::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListDrag& pValue = dynamic_cast<const Value_TransparentListDrag&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetDragEnable( pValue.bCanDrag );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TouchListDrag::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList Drag end


//TransparentList ClickNoSel begin
bool Property_TransparentListClickNoSel::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentListClickNoSel& pValue = dynamic_cast<Value_TransparentListClickNoSel&>(value);
        pValue.bNoSel = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src)))->IsClickNoSel();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentListClickNoSel::get( const Window* src, String& value ) const
{
    try 
    { 
        bool bNoSel = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src)))->IsClickNoSel( );
        value = CPropertyHelp::boolToString(bNoSel);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickNoSel::get 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentListClickNoSel::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bNoSel = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetClickNoSel( bNoSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentListClickNoSel::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListClickNoSel& pValue = dynamic_cast<const Value_TransparentListClickNoSel&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetClickNoSel( pValue.bNoSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickNoSel::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList ClickNoSel end



//tranparentlist select item set/get begin 
bool Property_TransparentListSelItem::set(Window* tag, const String& value)
{   
    try 
    {  
        int nSel = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetSelItem( nSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListSelItem::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransparentListSelItem::get( const Window* src, String& value ) const
{
    
    return false;
}

bool Property_TransparentListSelItem::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListSelItem& pValue = dynamic_cast<const Value_TransparentListSelItem&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetSelItem( pValue.dwDataKey );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListSelItem::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_TransparentListSelItem::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentListSelItem& pValue = dynamic_cast<Value_TransparentListSelItem&>(value);
        pValue.pSelItem = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src)))->GetSelItem();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListSelItem::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparentlist select item set/get end




//tranparentlist offset set/get begin 
bool Property_TransparentListOffset::set(Window* tag, const String& value)
{
	try 
    {  
        int nOffset = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetYOffset( nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListOffset::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransparentListOffset::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListOffset::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListOffset& pValue = dynamic_cast<const Value_TransparentListOffset&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetYOffset( pValue.nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListOffset::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_TransparentListOffset::get( const Window* src, IValue& value ) const
{
    try 
    { 
        Value_TransparentListOffset& pValue = dynamic_cast<Value_TransparentListOffset&>(value);
		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(src))) )
		{
			pValue.nOffset = pWnd->GetYOffset();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListOffset::get 传入的参数不正确" );
        return false;
    }
    return false;
}
//tranparentlist offset set/get end 

//TransparentList ClickFocus begin
bool Property_TransparentListClickFocus::get( const Window* src, IValue& value ) const
{		
    return false;
}

bool Property_TransparentListClickFocus::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListClickFocus::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bFocus = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetClickFocus( bFocus );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickFocus::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentListClickFocus::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListClickFocus& pValue = dynamic_cast<const Value_TransparentListClickFocus&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetClickFocus( pValue.bFocus );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListClickFocus::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList ClickFocus end


//TransparentList bkgColor begin
bool Property_TransparentListBkgColor::get( const Window* src, IValue& value ) const
{		
    return false;
}

bool Property_TransparentListBkgColor::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListBkgColor::set(Window* tag, const String& value)
{   
    try 
    {  
		COLORREF col = CPropertyHelp::stringToColor(value);
        Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetBkgColor( color );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListBkgColor::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentListBkgColor::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentListBkgColor& pValue = dynamic_cast<const Value_TransparentListBkgColor&>(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetBkgColor( pValue.colorBkg );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListBkgColor::set 传入的参数不正确" );
        return false;
    }	
} 
//TransparentList bkgColor end


//tranparentlist Item same size set/get begin 
bool Property_TransparentListItemSizeSame::set(Window* tag, const String& value)
{
	try 
    {  
        bool bSameSize = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetItemSizeSame( bSameSize );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListItemSizeSame::set 传入的参数不正确" );
        return false;
    }
    return false;	
} 


bool Property_TransparentListItemSizeSame::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListItemSizeSame::set( Window* tag, const IValue& value )
{ 
    return false; 
} 

bool Property_TransparentListItemSizeSame::get( const Window* src, IValue& value ) const
{	  
    return false;
}
//tranparentlist Item same size set/get end


//tranparentlist MultiSel set/get begin 
bool Property_TransparentListMultiSel::set(Window* tag, const String& value)
{
	try 
    {  
        bool bMulti = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetMultiSel( bMulti );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListMultiSel::set 传入的参数不正确" );
        return false;
    }
    return false;	
} 


bool Property_TransparentListMultiSel::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListMultiSel::set( Window* tag, const IValue& value )
{ 
    return false; 
} 

bool Property_TransparentListMultiSel::get( const Window* src, IValue& value ) const
{	  
    return false;
}
//tranparentlist MultiSel set/get end

//tranparentlist Over set/get begin 
bool Property_TransparentListOver::set(Window* tag, const String& value)
{
	try 
    {  
        bool bOver = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag)))->SetListOver( bOver );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentListOver::set 传入的参数不正确" );
        return false;
    }
    return false;	
} 


bool Property_TransparentListOver::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentListOver::set( Window* tag, const IValue& value )
{ 
	try 
	{
		const Value_TransparentListOver& pValue = dynamic_cast<const Value_TransparentListOver&>(value);		
		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetListOver( pValue.bOver );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListOver::set 传入的参数不正确" );
		return false;
	}
} 

bool Property_TransparentListOver::get( const Window* src, IValue& value ) const
{	  
    return false;
}
//tranparentlist Over set/get end

// transparentbasewnd image begin
bool Property_TransparentBaseWndImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentBaseWndImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentBaseWndImage::set(Window* tag, const String& value)
{   
	try 
	{
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + value;
// 		CString str;
// 		tag->GetWindowText( str );
		if ( CTransparentBaseWnd* pWnd = (dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str() );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseWndImage::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentBaseWndImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentBaseWndImage& pValue = dynamic_cast<const Value_TransparentBaseWndImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;

		if ( CTransparentBaseWnd* pWnd = (dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseWndImage::set 传入的参数不正确" );
		return false;
	}
}

bool Property_TransparentBaseWndAutoHideStatus::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentBaseWndAutoHideStatus::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentBaseWndAutoHideStatus::set(Window* tag, const String& value)
{   
	try 
	{
		bool bAutoHide = CPropertyHelp::stringToBool( value );
		if ( CTransparentBaseWnd* pWnd = (dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetAutoHideStatus( bAutoHide );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseWndAutoHideStatus::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentBaseWndAutoHideStatus::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentBaseWndAutoHideStatus& pValue = dynamic_cast<const Value_TransparentBaseWndAutoHideStatus&>(value);		
		if ( CTransparentBaseWnd* pWnd = (dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetAutoHideStatus( pValue.bHide );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseWndAutoHideStatus::set 传入的参数不正确" );
		return false;
	}
}
//transparentbasewnd image  end


//tranparentlist Data set/get begin  
bool Property_TransparentListData::set(Window* tag, const String& value)
{   	
	return false;
}

bool Property_TransparentListData::set( Window* tag, const IValue& value )
{
	try   
	{
        IValue* pVal = const_cast<IValue*>(&value) ; 
		if ( NULL == pVal )
		{
			LOGEVENT( "Property_TransparentListData::set 传入的参数不正确" );
		    return false;
		}

		Value_ListBase *valBase = dynamic_cast<Value_ListBase*>(pVal);
		if ( NULL == valBase )
		{
			LOGEVENT( "Property_TransparentListData::set 传入的参数不正确" );
		    return false;
		}

		if ( CTransparentList* pTouchList = dynamic_cast<CTransparentList*>( const_cast<Window*>(tag)) )
        {  
            pTouchList->Clear(); 
			bool bRet = valBase->SetData( pTouchList->GetRoot() );
			if ( bRet == true )
			{ 
				pTouchList->LayoutItem();				
			}
			pTouchList->ResetSelItem(); 
			pTouchList->SendMessage( WM_REDRAW_UI, 0, (LPARAM)0 );
		}
		else if ( CTransparentHoriList* pList = dynamic_cast<CTransparentHoriList*>( const_cast<Window*>(tag) ) )
		{
            pList->Clear();
			bool bRet = valBase->SetData( pList->GetRoot() );
			if ( bRet )
			{ 
				pList->LayoutItem();				
			}
			pList->ResetSelItem(); 
			pList->SendMessage( WM_REDRAW_UI, 0, 0 );
		}
        else if ( CTransparentViewList* pViewList = dynamic_cast<CTransparentViewList*>( const_cast<Window*>(tag) ) )
        {
            pViewList->Clear();
            bool bRet = valBase->SetData( pViewList->GetRoot() );
            if ( bRet )
            { 
                pViewList->LayoutItem();				
            }
            pViewList->ResetSelItem(); 
            pViewList->SendMessage( WM_REDRAW_UI, 0, 0 );
		}
		
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListData::set 传入的参数不正确" );
		return false;
	}
}

bool Property_TransparentListData::get( const Window* src, String& value ) const
{
    return false;
}
 
bool Property_TransparentListData::get( const Window* src, IValue& value ) const
{	  
    return false;
}
//tranparentlist Data set/get end

// transparent list image begin
bool Property_TransparentListImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentListImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentListImage::set(Window* tag, const String& value)
{   
	try 
	{
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + value;
		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str() );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListImage::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentListImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentListImage& pValue = dynamic_cast<const Value_TransparentListImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		
		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListImage::set 传入的参数不正确" );
		return false;
	}
}
// transparent list image end

// transparent list single image begin
bool Property_TransparentListSingleImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentListSingleImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentListSingleImage::set(Window* tag, const String& value)
{   
	try 
	{
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + value;

		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str(), FALSE, emImgCompSingle );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListSingleImage::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentListSingleImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentListSingleImage& pValue = dynamic_cast<const Value_TransparentListSingleImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		
		if ( CTransparentList* pWnd = (dynamic_cast<CTransparentList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetImage( strFile.c_str(), FALSE, emImgCompSingle );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentListSingleImage::set 传入的参数不正确" );
		return false;
	}
}
// transparent list single image end

// transparent btn image begin
bool Property_TransparentBtnImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentBtnImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentBtnImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentBtn* pWnd = dynamic_cast<CTransparentBtn*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_TransparentBtnImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentBtnImage& pValue = dynamic_cast<const Value_TransparentBtnImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentBtn* pWnd = dynamic_cast<CTransparentBtn*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBtnImage::set 传入的参数不正确" );
		return false;
	}
}
//transparent btn image  end

// transparentBtn use time begin
bool Property_TransparentBtnUseTimer::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_TransparentBtnUseTimer::get( const Window* src, String& value ) const
{
    return false;
}
bool Property_TransparentBtnUseTimer::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bState = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentBtn*>(const_cast<Window*>(tag)))->SetUseTimer( bState );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentBtnUseTimer::set 传入的参数不正确" );
        return false;
    }	
    return false;    
}

bool Property_TransparentBtnUseTimer::set( Window* tag, const IValue& value )
{
    try 
	{
		const Value_TransparentBtnUseTimer& pValue = dynamic_cast<const Value_TransparentBtnUseTimer&>(value);
		(dynamic_cast<CTransparentBtn*>(const_cast<Window*>(tag)))->SetUseTimer( pValue.bUseTimer );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBtnUseTimer::set 传入的参数不正确" );
		return false;
	}
    return false;
}
//transparentBtn use timer  end

// transparent checkbtn image begin
bool Property_TransparentCheckBtnImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentCheckBtnImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentCheckBtnImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentCheckButton* pWnd = dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_TransparentCheckBtnImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentCheckBtnImage& pValue = dynamic_cast<const Value_TransparentCheckBtnImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentCheckButton* pWnd = dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentCheckBtnImage::set 传入的参数不正确" );
		return false;
	}
}
//transparent checkbtn image  end

// transparent checkbtn fontspan begin
bool Property_TransparentCheckBtnFontSpan::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentCheckBtnFontSpan::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentCheckBtnFontSpan::set(Window* tag, const String& value)
{   
	try 
    {  
        int nFontSpan = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetFontSpan( nFontSpan );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentCheckBtnFontSpan::set 传入的参数不正确" );
        return false;
    }	

    return false;
}

bool Property_TransparentCheckBtnFontSpan::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentCheckBtnFontSpan& pValue = dynamic_cast<const Value_TransparentCheckBtnFontSpan&>(value);
		(dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetFontSpan( pValue.nFontSpan );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentCheckBtnFontSpan::set 传入的参数不正确" );
		return false;
	}

	return false;
}
//transparent checkbtn fontspan  end

// transparent checkbtn fontcolor begin
bool Property_TransparentCheckBtnFontColor::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentCheckBtnFontColor::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentCheckBtnFontColor::set(Window* tag, const String& value)
{   
	try 
    {  
        COLORREF col = CPropertyHelp::stringToColor(value);
        Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
        (dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetTextColor( color );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentCheckBtnFontColor::set 传入的参数不正确" );
        return false;
    }	
	
    return false;
}

bool Property_TransparentCheckBtnFontColor::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentCheckBtnFontColor& pValue = dynamic_cast<const Value_TransparentCheckBtnFontColor&>(value);
		(dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetTextColor( pValue.color );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentCheckBtnFontColor::set 传入的参数不正确" );
		return false;
	}
	
	return false;
}
//transparent checkbtn fontcolor  end

// transparent checkbtn fontsize begin
bool Property_TransparentCheckBtnFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentCheckBtnFontSize::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentCheckBtnFontSize::set(Window* tag, const String& value)
{   
	try 
    {  
        int nFontSize = CPropertyHelp::stringToInt(value);

		// checkbox文字自适应
		CPropertyHelp::FontSizeAdp( nFontSize );

        (dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetFont( nFontSize );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentCheckBtnFontSize::set 传入的参数不正确" );
        return false;
    }	
	
    return false;
}

bool Property_TransparentCheckBtnFontSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentCheckBtnFontSize& pValue = dynamic_cast<const Value_TransparentCheckBtnFontSize&>(value);
		(dynamic_cast<CTransparentCheckButton*>(const_cast<Window*>(tag)))->SetFont( pValue.nFontSize );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentCheckBtnFontSize::set 传入的参数不正确" );
		return false;
	}
	
	return false;
}
//transparent checkbtn fontsize  end

// transparent switchbtn image begin
bool Property_TransparentSwitchBtnImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentSwitchBtnImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentSwitchBtnImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentSwitchButton* pWnd = dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_TransparentSwitchBtnImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentSwitchBtnImage& pValue = dynamic_cast<const Value_TransparentSwitchBtnImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentSwitchButton* pWnd = dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentSwitchBtnImage::set 传入的参数不正确" );
		return false;
	}
}
//transparent switchbtn image  end

// transparent switchbtn State begin
bool Property_SwitchState::get( const Window* src, IValue& value ) const
{	
	try 
	{ 
		Value_SwitchState& pValue = dynamic_cast<Value_SwitchState&>(value);
		pValue.bState = (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(src)))->GetSwitchState();

		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_SwitchState::get 传入的参数不正确" );
		return false;
	}
	return false;
}

bool Property_SwitchState::get( const Window* src, String& value ) const
{
	try 
    { 
        bool bState = (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(src)))->GetSwitchState();
        value = CPropertyHelp::boolToString(bState);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_SwitchState::get 传入的参数不正确" );
        return false;
    }	
	return false;
}
bool Property_SwitchState::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bState = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetSwitchState( bState );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_SwitchState::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_SwitchState::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_SwitchState& pValue = dynamic_cast<const Value_SwitchState&>(value);
		(dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetSwitchState( pValue.bState );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_SwitchState::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent switchbtn State  end

// transparent switchbtn BindWnd begin
bool Property_SwitchBtnBindWnd::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_SwitchBtnBindWnd::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_SwitchBtnBindWnd::set(Window* tag, const String& value)
{   	
	IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( value ) );
// 	IWndTree* pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( tag, CWindowManage::GetSingletonPtr()->GetRoot() ) );
// 	pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( value, pTree->GetParentItem() ) );
	if ( pTree == NULL )
	{
		return false;
	}
	if ( CWnd* pWnd = dynamic_cast<CWnd*>(pTree->GetItemData()->pWnd) )
	{	
		if ( CTransparentSwitchButton* pButton = dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)) )
		{
			pButton->SetBindWnd( pWnd->GetSafeHwnd() );
			return true;
		}
	}
	return false;	
}

bool Property_SwitchBtnBindWnd::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_SwitchBtnBindWnd& pValue = dynamic_cast<const Value_SwitchBtnBindWnd&>(value);
		IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( pValue.strWndName ) );
		//IWndTree* pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( tag, CWindowManage::GetSingletonPtr()->GetRoot() ) );
		//pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( pValue.strListName, pTree->GetParentItem() ) );
		if ( pTree == NULL )
		{
			return false;
		}
		if ( CWnd* pWnd = dynamic_cast<CWnd*>(pTree->GetItemData()->pWnd) )
		{	
			if ( CTransparentSwitchButton* pButton = dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)) )
			{
				pButton->SetBindWnd( pWnd->GetSafeHwnd() );
				return true;
			}
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_SwitchBtnBindWnd::set 传入的参数不正确" );
		return false;
	}
}
// transparent switchbtn BindWnd end


// transparent switchbtn ShowText begin
bool Property_SwitchBtnShowText::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_SwitchBtnShowText::get( const Window* src, String& value ) const
{	
    return false;
}
bool Property_SwitchBtnShowText::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bState = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetShowText( bState );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_SwitchBtnShowText::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_SwitchBtnShowText::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_SwitchBtnShowText& pValue = dynamic_cast<const Value_SwitchBtnShowText&>(value);
        (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetShowText( pValue.bShow );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_SwitchBtnShowText::set 传入的参数不正确" );
        return false;
    }
    return false;
}
//transparent switchbtn ShowText  end

// transparent switchbtn fontsize begin
bool Property_TransparentSwitchBtnFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentSwitchBtnFontSize::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentSwitchBtnFontSize::set(Window* tag, const String& value)
{   
	try 
    {  
        int nFontSize = CPropertyHelp::stringToInt(value);
		
		// switchbtn文字自适应
		CPropertyHelp::FontSizeAdp( nFontSize );
		
        (dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetFont( nFontSize );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentSwitchBtnFontSize::set 传入的参数不正确" );
        return false;
    }	
	
    return false;
}

bool Property_TransparentSwitchBtnFontSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentSwitchBtnFontSize& pValue = dynamic_cast<const Value_TransparentSwitchBtnFontSize&>(value);
		(dynamic_cast<CTransparentSwitchButton*>(const_cast<Window*>(tag)))->SetFont( pValue.nFontSize );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentSwitchBtnFontSize::set 传入的参数不正确" );
		return false;
	}
	
	return false;
}
//transparent switchbtn fontsize  end


// transparent edit image begin
bool Property_TransparentEditImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentEditImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentEdit* pWnd = dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_TransparentEditImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditImage& pValue = dynamic_cast<const Value_TransparentEditImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;

		if ( CTransparentEdit* pWnd = dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditImage::set 传入的参数不正确" );
		return false;
	}
}
//transparent edit image  end

// transparent edit FontSize begin
bool Property_TransparentEditFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditFontSize::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditFontSize::set( Window* tag, const String& value )
{   
	try 
    {  
		int nFont = CPropertyHelp::stringToInt(value);	
        //edit内字体自适应
        CPropertyHelp::FontSizeAdp( nFont );
        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
        CString strFontName;
        if ( !tFontInfo.strFontName.empty() )
        {
            strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
        }
        else
        {
            strFontName = "微软雅黑";
        }

        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetFont( nFont, strFontName );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditFontSize::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditFontSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditFontSize& pValue = dynamic_cast<const Value_TransparentEditFontSize&>(value);

        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
        CString strFontName;
        if ( !tFontInfo.strFontName.empty() )
        {
            strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
        }
        else
        {
            strFontName = "微软雅黑";
        }

		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetFont( pValue.size, strFontName );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditFontSize::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit FontSize end

// transparent edit FontColor begin			//2012.12.27  edit框中字体颜色设置,normal与focus颜色一致
bool Property_TransparentEditFontColor::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditFontColor::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentEditFontColor::set(Window* tag, const String& value)
{   
	try 
    {  
		COLORREF col = CPropertyHelp::stringToColor(value);
        Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTextColor( color, color );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditFontColor::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditFontColor::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditFontColor& pValue = dynamic_cast<const Value_TransparentEditFontColor&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTextColor( pValue.color, pValue.color );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditFontColor::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit FontColor end

// transparent edit LimitLength begin
bool Property_TransparentEditLimitLength::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditLimitLength::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditLimitLength::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetLimitLength( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditLimitLength::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditLimitLength::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditLimitLength& pValue = dynamic_cast<const Value_TransparentEditLimitLength&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetLimitLength( pValue.length );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditLimitLength::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit LimitLength end

// transparent edit BackLen begin
bool Property_TransparentEditFrontLen::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditFrontLen::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditFrontLen::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetEditFrontLen( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditFrontLen::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditFrontLen::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditFrontLen& pValue = dynamic_cast<const Value_TransparentEditFrontLen&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetEditFrontLen( pValue.frontlen );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditFrontLen::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit BackLen end


// transparent edit BackLen begin
bool Property_TransparentEditBackLen::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditBackLen::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditBackLen::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetEditBackLen( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditBackLen::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditBackLen::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditBackLen& pValue = dynamic_cast<const Value_TransparentEditBackLen&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetEditBackLen( pValue.backlen );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditBackLen::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit BackLen end

// transparent edit showicon begin
bool Property_TransparentEditShowIcon::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditShowIcon::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditShowIcon::set(Window* tag, const String& value)
{   
	try 
    {  
		bool bShow = CPropertyHelp::stringToBool(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetShowIcon( bShow );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditShowIcon::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditShowIcon::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditShowIcon& pValue = dynamic_cast<const Value_TransparentEditShowIcon&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetShowIcon( pValue.bShow );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditShowIcon::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit ShowIcon end

// transparent edit tipstr begin
bool Property_TransparentEditTipStr::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditTipStr::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditTipStr::set(Window* tag, const String& value)
{   
	try 
    {  		
		CString strTip;
		strTip.Format( "%s", value.c_str() );
		int nFontSize = _ttoi(strTip);
		CPropertyHelp::FontSizeAdp( nFontSize );
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTipStr( strTip );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditTipStr::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditTipStr::set( Window* tag, const IValue& value )
{
	try 
	{
		CString strTip;
		const Value_TransparentEditTipStr& pValue = dynamic_cast<const Value_TransparentEditTipStr&>(value);
		strTip.Format( "%s", pValue.strTip.c_str() );
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTipStr( strTip );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditTipStr::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit LimitLength end

// transparent edit Align begin
bool Property_TransparentEditAlign::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditAlign::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditAlign::set(Window* tag, const String& value)
{   
	try 
    {  
		StringAlignment align = CPropertyHelp::stringToAlignment(value);
		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTextAlign( align );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditAlign::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditAlign::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditAlign& pValue = dynamic_cast<const Value_TransparentEditAlign&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetTextAlign( pValue.emAlign );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditAlign::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit Align end

// transparent edit search begin
bool Property_TransparentEditSearch::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditSearch::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditSearch::set(Window* tag, const String& value)
{   
	try 
    {  
		bool bSearch = CPropertyHelp::stringToBool(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetSearchEdit( bSearch );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditSearch::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditSearch::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditSearch& pValue = dynamic_cast<const Value_TransparentEditSearch&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetSearchEdit( pValue.bSearch );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditSearch::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit search end

// transparent edit DeleteText begin
bool Property_TransparentEditDeleteText::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentEditDeleteText::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentEditDeleteText::set(Window* tag, const String& value)
{   
	try 
    {  
		bool bDelete = CPropertyHelp::stringToBool(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetIconDeleteText( bDelete );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditDeleteText::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentEditDeleteText::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentEditDeleteText& pValue = dynamic_cast<const Value_TransparentEditDeleteText&>(value);
		(dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetIconDeleteText( pValue.bDelete );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentEditDeleteText::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent edit DeleteText end

// transparent edit DeleteText begin
bool Property_TransparentEditDisableImg::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_TransparentEditDisableImg::get( const Window* src, String& value ) const
{	
    return false;
}
bool Property_TransparentEditDisableImg::set(Window* tag, const String& value)
{   
    try 
    {  
        bool bShow = CPropertyHelp::stringToBool(value);		
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetDisableImg( bShow );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditDisableImg::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentEditDisableImg::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentEditDisableImg& pValue = dynamic_cast<const Value_TransparentEditDisableImg&>(value);
        (dynamic_cast<CTransparentEdit*>(const_cast<Window*>(tag)))->SetDisableImg( pValue.bShowImg );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentEditDisableImg::set 传入的参数不正确" );
        return false;
    }
    return false;
}
//transparent edit DeleteText end


// transparentwnd MoveStatus begin
bool Property_TransparentBaseWndMoveStatus::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentBaseWndMoveStatus::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentBaseWndMoveStatus::set(Window* tag, const String& value)
{   
	if ( CTransparentBaseWnd* pWnd = dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetMoveStatus( CPropertyHelp::stringToBool( value ) );
		return true;
	}
	return false;
}

bool Property_TransparentBaseWndMoveStatus::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentBaseWndMoveStatus& pValue = dynamic_cast<const Value_TransparentBaseWndMoveStatus&>(value);

		if ( CTransparentBaseWnd* pWnd = dynamic_cast<CTransparentBaseWnd*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( pValue.bMove );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentBaseWndMoveStatus::set 传入的参数不正确" );
		return false;
	}
}

/*
// transparent ipaddrctrl image begin
bool Property_TransparentIPAddrCtrlImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentIPAddrCtrlImage::get( const Window* src, String& value ) const
{
	return false;
}


bool Property_TransparentIPAddrCtrlImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentIPAddrCtrl* pWnd = dynamic_cast<CTransparentIPAddrCtrl*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentIPAddrCtrlImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentIPAddrCtrlImage& pValue = dynamic_cast<const Value_TransparentIPAddrCtrlImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentIPAddrCtrl* pWnd = dynamic_cast<CTransparentIPAddrCtrl*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentIPAddrCtrlImage::set 传入的参数不正确" );
		return false;
	}
}
*/
// transparent static image begin
bool Property_TransparentStaticImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentStaticImage::get( const Window* src, String& value ) const
{
	return false;
}


bool Property_TransparentStaticImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentStatic* pWnd = dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentStaticImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentStaticImage& pValue = dynamic_cast<const Value_TransparentStaticImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentStatic* pWnd = dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentStaticImage::set 传入的参数不正确" );
		return false;
	}
}

// transparent static FontColor begin
bool Property_TransparentStaticFontColor::get( const Window* src, IValue& value ) const
{	
	try 
	{ 
		Value_TransparentStaticFontColor& pValue = dynamic_cast<Value_TransparentStaticFontColor&>(value);
		pValue.color = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(src)))->GetTextColor();
		
		return true;
	}
	catch( bad_cast )
	{		
		LOGEVENT( "Property_TransparentStaticFontColor::get 传入的参数不正确" );
		return false;
	}
	return false;
}

bool Property_TransparentStaticFontColor::get( const Window* src, String& value ) const
{
	try 
    { 
        Color color = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(src)))->GetTextColor();
		COLORREF col = RGB( color.GetR(), color.GetG(), color.GetB() );
        value = CPropertyHelp::colorToString(col);
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontColor::get 传入的参数不正确" );
        return false;
    }	
	return false;
}
bool Property_TransparentStaticFontColor::set(Window* tag, const String& value)
{   
	try 
    {  
		COLORREF col = CPropertyHelp::stringToColor(value);
        Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
        (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetTextColor( color );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontColor::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentStaticFontColor::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentStaticFontColor& pValue = dynamic_cast<const Value_TransparentStaticFontColor&>(value);
		(dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetTextColor( pValue.color );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentStaticFontColor::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent static FontColor end


// transparent static FontSize begin
bool Property_TransparentStaticFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentStaticFontSize::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentStaticFontSize::set(Window* tag, const String& value)
{   
	try 
    {  
		int nFont = CPropertyHelp::stringToInt(value);
                
        // 字体随分辨率等比变化 2012-2-9 by yjj
        CPropertyHelp::FontSizeAdp( nFont );

        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetStaticFontInfo();
        CString strFontName;
        if ( !tFontInfo.strFontName.empty() )
        {
            strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
        }
        else
        {
            strFontName = "微软雅黑";
        }           

        (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( nFont, strFontName );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontSize::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentStaticFontSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentStaticFontSize& pValue = dynamic_cast<const Value_TransparentStaticFontSize&>(value);

        TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetStaticFontInfo();
        CString strFontName;
        if ( !tFontInfo.strFontName.empty() )
        {
            strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
        }
        else
        {
            strFontName = "微软雅黑";
        } 

		(dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( pValue.size, strFontName );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentStaticFontSize::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent static FontSize end

// transparent static FontName begin
bool Property_TransparentStaticFontName::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentStaticFontName::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentStaticFontName::set(Window* tag, const String& value)
{   
	try 
    {  
		Font* pFont = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->GetFont();
		if ( pFont != NULL )
		{	
			int nFont = pFont->GetSize();
            FontStyle emStyle = (FontStyle)pFont->GetStyle();
			CString strName;
			strName.Format( "%s", value );
			(dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( nFont, strName, emStyle );
		}		
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontName::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentStaticFontName::set( Window* tag, const IValue& value )
{
	try 
	{
		Font* pFont = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->GetFont();
		if ( pFont != NULL )
		{	
			int nFont = pFont->GetSize();
            FontStyle emStyle = (FontStyle)pFont->GetStyle();
			const Value_TransparentStaticFontName& pValue = dynamic_cast<const Value_TransparentStaticFontName&>(value);
			CString strName;
			strName.Format( "%s", pValue.strFontName );
			(dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( nFont, strName, emStyle );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentStaticFontName::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent static FontName end


// transparent static FontStyle begin
bool Property_TransparentStaticFontStyle::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_TransparentStaticFontStyle::get( const Window* src, String& value ) const
{	
    return false;
}
bool Property_TransparentStaticFontStyle::set(Window* tag, const String& value)
{   
    try 
    {  
        Font* pFont = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->GetFont();
        if ( pFont != NULL )
        {	
            int nFont = pFont->GetSize();
           
            FontStyle emStyle = CPropertyHelp::stringToFontStyle(value);
            
            TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetStaticFontInfo();
            CString strFontName;
            if ( !tFontInfo.strFontName.empty() )
            {
                strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
            }
            else
            {
                strFontName = "微软雅黑";
            }      

            (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( nFont, strFontName, emStyle );
        }		
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontName::set 传入的参数不正确" );
        return false;
    }	
    return false;
}

bool Property_TransparentStaticFontStyle::set( Window* tag, const IValue& value )
{
    try 
    {
        Font* pFont = (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->GetFont();
        if ( pFont != NULL )
        {	
            int nFont = pFont->GetSize();
                      
            TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetStaticFontInfo();
            CString strFontName;
            if ( !tFontInfo.strFontName.empty() )
            {
                strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
            }
            else
            {
                strFontName = "微软雅黑";
            } 

            const Value_TransparentStaticFontStyle& pValue = dynamic_cast<const Value_TransparentStaticFontStyle&>(value);
            (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetFont( nFont, strFontName, pValue.emStyle );
        }
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticFontName::set 传入的参数不正确" );
        return false;
    }
    return false;
}
//transparent static FontName end


// transparent static Align begin
bool Property_TransparentStaticAlign::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentStaticAlign::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentStaticAlign::set(Window* tag, const String& value)
{   
	try 
    {  
		StringAlignment align = CPropertyHelp::stringToAlignment(value);
		
        (dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetTextAlign( align );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentStaticAlign::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentStaticAlign::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentStaticAlign& pValue = dynamic_cast<const Value_TransparentStaticAlign&>(value);
		(dynamic_cast<CTransparentStatic*>(const_cast<Window*>(tag)))->SetTextAlign( pValue.emAlign );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentStaticAlign::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//transparent static Align end


// staticEx tansparentbk begin
bool Property_StaticExBkTransparent::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_StaticExBkTransparent::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_StaticExBkTransparent::set(Window* tag, const String& value)
{   
	try 
    {  
		bool bTrans = CPropertyHelp::stringToBool(value);
		
        (dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetBkTransparent( bTrans );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_StaticExBkTransparent::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_StaticExBkTransparent::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_StaticExBkTransparent& pValue = dynamic_cast<const Value_StaticExBkTransparent&>(value);
		(dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetBkTransparent( pValue.bBKTransparent );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_StaticExBkTransparent::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//staticEx tansparentbk end


//   StaticExFontSize begin
bool Property_StaticExFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_StaticExFontSize::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_StaticExFontSize::set(Window* tag, const String& value)
{   
	try 
    {  
		int nSize = CPropertyHelp::stringToInt(value);
		
        (dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetFontSize( nSize );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_StaticExBkTransparent::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_StaticExFontSize::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_StaticExFontSize& pValue = dynamic_cast<const Value_StaticExFontSize&>(value);
		(dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetFontSize( pValue.nFontSize );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_StaticExBkTransparent::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//  StaticExFontSize end

// staticEx  txt color begin
bool Property_StaticExTextColor::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_StaticExTextColor::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_StaticExTextColor::set(Window* tag, const String& value)
{   
	try 
    {  
		COLORREF col = CPropertyHelp::stringToColor(value); 
		
        (dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetTextColor( col );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_StaticExBkTextColor::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_StaticExTextColor::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_StaticExTextColor& pValue = dynamic_cast<const Value_StaticExTextColor&>(value);
		(dynamic_cast<CStaticEx*>(const_cast<Window*>(tag)))->SetTextColor( pValue.clrfTextColor );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "StaticExBkTextColor::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//staticEx  txt color  end

// LetterIndex image begin
bool Property_LetterIndexImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_LetterIndexImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_LetterIndexImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CLetterIndex* pWnd = dynamic_cast<CLetterIndex*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_LetterIndexImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_LetterIndexImage& pValue = dynamic_cast<const Value_LetterIndexImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CLetterIndex* pWnd = dynamic_cast<CLetterIndex*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_LetterIndexImage::set 传入的参数不正确" );
		return false;
	}
}
// LetterIndex image end

// LetterIndex BindList begin
bool Property_BindList::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_BindList::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_BindList::set(Window* tag, const String& value)
{   	
//	IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( value ) );
	IWndTree* pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( tag, CWindowManage::GetSingletonPtr()->GetRoot() ) );
	pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( value, pTree->GetParentItem() ) );
	if ( pTree == NULL )
	{
		return false;
	}
	if ( CWnd* pList = dynamic_cast<CWnd*>(pTree->GetItemData()->pWnd) )
	{	
		if ( CLetterIndex* pWnd = dynamic_cast<CLetterIndex*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetBindList( pList );
			return true;
		}
	}
	return false;	
}

bool Property_BindList::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_BindList& pValue = dynamic_cast<const Value_BindList&>(value);
//		IWndTree* pTree = const_cast<IWndTree* >( CWindowManage::GetSingletonPtr()->GetWindowTree( pValue.strListName ) );
		IWndTree* pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( tag, CWindowManage::GetSingletonPtr()->GetRoot() ) );
		pTree = const_cast<IWndTree* >( CWndTreeHelp::GetWindow( pValue.strListName, pTree->GetParentItem() ) );
		if ( pTree == NULL )
		{
			return false;
		}
		if ( CWnd* pList = dynamic_cast<CWnd*>(pTree->GetItemData()->pWnd) )
		{	
			if ( CLetterIndex* pWnd = dynamic_cast<CLetterIndex*>(const_cast<Window*>(tag)) )
			{
				pWnd->SetBindList( pList );
				return true;
			}
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_LetterIndexBindList::set 传入的参数不正确" );
		return false;
	}
}
// LetterIndex BindList end

// transparent slider image begin
bool Property_TransparentSliderCtrlImage::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_TransparentSliderCtrlImage::get( const Window* src, String& value ) const
{
    return false;
}


bool Property_TransparentSliderCtrlImage::set(Window* tag, const String& value)
{   
    String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
    String strFile = strImageFolder + "//" + value;
    
    if ( CTransparentSliderCtrl* pWnd = dynamic_cast<CTransparentSliderCtrl*>(const_cast<Window*>(tag)) )
    {
        pWnd->SetImage( strFile.c_str() );
        return true;
    }
    return false;	
}

bool Property_TransparentSliderCtrlImage::set( Window* tag, const IValue& value )											  
{
    try
    {
        const Value_TransparentSliderCtrlImage& pValue = dynamic_cast<const Value_TransparentSliderCtrlImage&>(value);
        String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
        String strFile = strImageFolder + "//" + pValue.strImage;
        if ( CTransparentSliderCtrl* pWnd = dynamic_cast<CTransparentSliderCtrl*>(const_cast<Window*>(tag)) )
        {
            pWnd->SetImage( strFile.c_str() );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentSliderCtrlImage::set 传入的参数不正确" );
        return false;
    }
}


//CSliderCtrlRange begin
bool Property_CSliderCtrlRange::get( const Window* src, String& value ) const
{ 
    int nMax = 0;
    int nMin = 0;
	if ( CSliderCtrl* pWnd = (dynamic_cast<CSliderCtrl*>(const_cast<Window*>(src))) )
	{
		pWnd->GetRange( nMin, nMax );
		value = CPropertyHelp::RangeToString( nMin, nMax);
		return true;
	}
    
    return false;
}

bool Property_CSliderCtrlRange::get( const Window* src, IValue& value ) const
{
    try 
    {
        Value_CSliderCtrlRange& pValue = dynamic_cast<Value_CSliderCtrlRange&>(value);
         
        Window*pSrc = const_cast<Window*>(src); 
        
        if ( CSliderCtrl * pSlider = dynamic_cast< CSliderCtrl*>(pSrc) )
        {
            if (  pSlider != NULL )
            {
                pSlider->GetRange( pValue.nMin,pValue.nMax );
            }
        }
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlRange::get 传入的参数不正确" );
        return false;
    }
    
    return true;
}

bool Property_CSliderCtrlRange::set(Window* tag, const String& value)
{   
    int nMax = 0;
    int nMin = 0;
    CPropertyHelp::StringToRange( value,nMin,nMax );
    if ( CSliderCtrl * pSlider = dynamic_cast<CSliderCtrl*>(const_cast<Window*>(tag)) )
    {
        pSlider->SetRange( nMin, nMax);
        return true;
    }
    return false;
}

bool Property_CSliderCtrlRange::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CSliderCtrlRange&  Val  = dynamic_cast<const Value_CSliderCtrlRange&>(value);
        if ( CSliderCtrl * pSlider = dynamic_cast<CSliderCtrl*>(const_cast<Window*>(tag)) )
        {
            pSlider->SetRange( Val.nMin, Val.nMax);
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlRange::set 传入的参数不正确" );
        return false;
    }
} 
//CSliderCtrlRange end


//CSliderCtrlPos begin
bool Property_CSliderCtrlPos::get( const Window* src, String& value ) const
{ 
	if ( CSliderCtrl* pWnd = (dynamic_cast<CSliderCtrl*>(const_cast<Window*>(src))) )
	{
		int pos = pWnd->GetPos();
		value = CPropertyHelp::intToString(pos);
		return true;
	}   
    return false;
}

bool Property_CSliderCtrlPos::get( const Window* src, IValue& value ) const
{
    try 
    {
        Value_CSliderCtrlPos& pValue = dynamic_cast<Value_CSliderCtrlPos&>(value);
        
        Window*pSrc = const_cast<Window*>(src); 
        
        if ( CSliderCtrl * pSlider = dynamic_cast< CSliderCtrl*>(pSrc) )
        {
            if (  pSlider != NULL )
            {
               pValue.nPos = pSlider->GetPos( );
            }
        }
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlPos::get 传入的参数不正确" );
        return false;
    }
    
    return true;
}

bool Property_CSliderCtrlPos::set(Window* tag, const String& value)
{    
    int nPos =  CPropertyHelp::stringToInt( value );
    if ( CSliderCtrl * pSlider = dynamic_cast<CSliderCtrl*>(const_cast<Window*>(tag)) )
    {
        pSlider->SetPos( nPos );
        return true;
    }
    return false;
}

bool Property_CSliderCtrlPos::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CSliderCtrlPos& val = dynamic_cast<const Value_CSliderCtrlPos&>(value);
        if ( CSliderCtrl * pSlider = dynamic_cast<CSliderCtrl*>(const_cast<Window*>(tag)) )
        {
            pSlider->SetPos( val.nPos );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlPos::set 传入的参数不正确" );
        return false;
    }
} 
//CSliderCtrlPos end

//CSliderCtrlPos begin
bool Property_CTransparentListShowItemStatus::get( const Window* src, String& value ) const
{ 
	if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(src)))
	{
		bool bShow = pList->IsShowItemAlways();
		value = CPropertyHelp::boolToString( bShow );
		return false;
	}
    return false;
}

bool Property_CTransparentListShowItemStatus::get( const Window* src, IValue& value ) const
{
    try 
    {
        Value_CTransparentListShowItemStatus& pValue = dynamic_cast<Value_CTransparentListShowItemStatus&>(value);
        
        Window*pSrc = const_cast<Window*>(src); 
        
        if ( IList* pList = dynamic_cast<IList*>(const_cast<Window*>(pSrc)) )
        {
            pValue.bAlways = pList->IsShowItemAlways();
        }
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CTransparentListShowItemStatus::get 传入的参数不正确" );
        return false;
    }
    
    return true;
}

bool Property_CTransparentListShowItemStatus::set(Window* tag, const String& value)
{    
    bool bShow =  CPropertyHelp::stringToBool( value );
    if ( IList * pWnd = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
    {
        pWnd->ShowItemAlways( bShow );
        return true;
    }
    return false;
}

bool Property_CTransparentListShowItemStatus::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CTransparentListShowItemStatus& pValue = dynamic_cast<const Value_CTransparentListShowItemStatus&>(value);
     
		if ( IList * pWnd = dynamic_cast<IList*>(const_cast<Window*>(tag)) )
		{
			pWnd->ShowItemAlways( pValue.bAlways );
			return true;
		}
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CTransparentListShowItemStatus::set 传入的参数不正确" );
        return false;
    }
} 
//CSliderCtrlPos end

//IPEdit Data begin
bool Property_IpEditData::get( const Window* src, String& value ) const
{
	DWORD dwAddress = 0; 
	(dynamic_cast<CTransparentIpEdit*>(const_cast<Window*>(src)))->GetAddress( dwAddress );
	value = CPropertyHelp::DWORDToString( dwAddress );
	return true;
}

bool Property_IpEditData::get( const Window* src, IValue& value ) const
{
	try 
	{
		Value_IpEditData& pValue = dynamic_cast<Value_IpEditData&>(value);
		DWORD dwAddress = 0; 		
		if ( CTransparentIpEdit* pIPCtrl = dynamic_cast<CTransparentIpEdit*>( const_cast<Window*>(src)) )
		{
			pIPCtrl->GetAddress( pValue.dwIP );
		}
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IpEditData::get 传入的参数不正确" );
		return false;
	}
	
    return true;
}

bool Property_IpEditData::set(Window* tag, const String& value)
{   
	DWORD dwAddress = CPropertyHelp::StringToDWORD( value );
	if ( CTransparentIpEdit* pIPCtrl = dynamic_cast<CTransparentIpEdit*>(const_cast<Window*>(tag)) )
	{
		pIPCtrl->SetAddress( dwAddress );
		return true;
	}
	return false;
}

bool Property_IpEditData::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_IpEditData& pValue = dynamic_cast<const Value_IpEditData&>(value);
		if ( CTransparentIpEdit* pIPEdit = dynamic_cast<CTransparentIpEdit*>(const_cast<Window*>(tag)) )
		{
			pIPEdit->SetAddress( pValue.dwIP );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_IpEditData::set 传入的参数不正确" );
		return false;
	}
}
//IPEdit Data end

// TransparentSlideBlock image begin
bool Property_TransparentSlideBlockImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentSlideBlockImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentSlideBlockImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentSlideBlock* pWnd = dynamic_cast<CTransparentSlideBlock*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentSlideBlockImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentSlideBlockImage& pValue = dynamic_cast<const Value_TransparentSlideBlockImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentSlideBlock* pWnd = dynamic_cast<CTransparentSlideBlock*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentSlideBlockImage::set 传入的参数不正确" );
		return false;
	}
}
// TransparentSlideBlock image end


// TransparentCalendar image begin
bool Property_TransparentCalendarImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentCalendarImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentCalendarImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentCalendar* pWnd = dynamic_cast<CTransparentCalendar*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentCalendarImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentCalendarImage& pValue = dynamic_cast<const Value_TransparentCalendarImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentCalendar* pWnd = dynamic_cast<CTransparentCalendar*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentCalendarImage::set 传入的参数不正确" );
		return false;
	}
}
// TransparentCalendar image end


// transparent slider image begin
bool Property_CTransparentSliderWndStyle::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_CTransparentSliderWndStyle::get( const Window* src, String& value ) const
{
    return false;
}


bool Property_CTransparentSliderWndStyle::set(Window* tag, const String& value)
{   
    
    int nStyle =  CPropertyHelp::stringToInt( value );
    if ( CTransparentSliderWnd* pWnd = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
    {
        pWnd->SetStyle( (EmStyle)nStyle );
        return true;
    }
    return false;	
}

bool Property_CTransparentSliderWndStyle::set( Window* tag, const IValue& value )											  
{
    try
    {
        const Value_CTransparentSliderWndStyle& pValue = dynamic_cast<const Value_CTransparentSliderWndStyle&>(value);
     
        if ( CTransparentSliderWnd* pWnd = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
        {
            pWnd->SetStyle( (EmStyle)pValue.nStyle );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CTransparentSliderWndStyle::set 传入的参数不正确" );
        return false;
    }
}


// transparent slider image begin
bool Property_CTransparentSliderWndImage::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_CTransparentSliderWndImage::get( const Window* src, String& value ) const
{
    return false;
}


bool Property_CTransparentSliderWndImage::set(Window* tag, const String& value)
{   
    String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
    String strFile = strImageFolder + "//" + value;
    
    if ( CTransparentSliderWnd* pWnd = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
    {
        pWnd->SetImage( strFile.c_str() );
        return true;
    }
    return false;	
}

bool Property_CTransparentSliderWndImage::set( Window* tag, const IValue& value )											  
{
    try
    {
        const Value_TransparentSliderCtrlImage& pValue = dynamic_cast<const Value_TransparentSliderCtrlImage&>(value);
        String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
        String strFile = strImageFolder + "//" + pValue.strImage;
        if ( CTransparentSliderWnd* pWnd = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
        {
            pWnd->SetImage( strFile.c_str() );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentSliderCtrlImage::set 传入的参数不正确" );
        return false;
    }
}


//CSliderCtrlRange begin
bool Property_CTransparentSliderWndRange::get( const Window* src, String& value ) const
{ 
    int nMax = 0;
    int nMin = 0;
	if ( CTransparentSliderWnd* pWnd = (dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(src))) )
	{
		pWnd->GetRange( nMin, nMax );
		value = CPropertyHelp::RangeToString( nMin, nMax);
		return true;
	}
    
    return false;
}

bool Property_CTransparentSliderWndRange::get( const Window* src, IValue& value ) const
{
    try 
    {
        Value_CSliderCtrlRange& pValue = dynamic_cast<Value_CSliderCtrlRange&>(value);
         
        Window*pSrc = const_cast<Window*>(src); 
        
        if ( CTransparentSliderWnd * pSlider = dynamic_cast< CTransparentSliderWnd*>(pSrc) )
        {
            if (  pSlider != NULL )
            {
                pSlider->GetRange( pValue.nMin,pValue.nMax );
            }
        }
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlRange::get 传入的参数不正确" );
        return false;
    }
    
    return true;
}

bool Property_CTransparentSliderWndRange::set(Window* tag, const String& value)
{   
    int nMax = 0;
    int nMin = 0;
    CPropertyHelp::StringToRange( value,nMin,nMax );
    if ( CTransparentSliderWnd * pSlider = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
    {
        pSlider->SetRange( nMin, nMax);
        return true;
    }
    return false;
}

bool Property_CTransparentSliderWndRange::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CSliderCtrlRange&  Val  = dynamic_cast<const Value_CSliderCtrlRange&>(value);
        if ( CTransparentSliderWnd * pSlider = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
        {
            pSlider->SetRange( Val.nMin, Val.nMax);
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlRange::set 传入的参数不正确" );
        return false;
    }
} 
//CSliderCtrlRange end


//CSliderCtrlPos begin
bool Property_CTransparentSliderWndPos::get( const Window* src, String& value ) const
{ 
	if ( CTransparentSliderWnd* pWnd = (dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(src))) )
	{
		int pos = pWnd->GetPos();
		value = CPropertyHelp::intToString(pos);
		return true;
	}   
    return false;
}

bool Property_CTransparentSliderWndPos::get( const Window* src, IValue& value ) const
{
    try 
    {
        Value_CSliderCtrlPos& pValue = dynamic_cast<Value_CSliderCtrlPos&>(value);
        
        Window*pSrc = const_cast<Window*>(src); 
        
        if ( CTransparentSliderWnd * pSlider = dynamic_cast< CTransparentSliderWnd*>(pSrc) )
        {
            if (  pSlider != NULL )
            {
               pValue.nPos = pSlider->GetPos( );
               int i = 0;
            }
        }
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlPos::get 传入的参数不正确" );
        return false;
    }
    
    return true;
}

bool Property_CTransparentSliderWndPos::set(Window* tag, const String& value)
{    
    int nPos =  CPropertyHelp::stringToInt( value );
    if ( CTransparentSliderWnd * pSlider = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
    {
        pSlider->SetPos( nPos );
        return true;
    }
    return false;
}

bool Property_CTransparentSliderWndPos::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_CSliderCtrlPos& val = dynamic_cast<const Value_CSliderCtrlPos&>(value);
        if ( CTransparentSliderWnd * pSlider = dynamic_cast<CTransparentSliderWnd*>(const_cast<Window*>(tag)) )
        {
            pSlider->SetPos( val.nPos );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_CSliderCtrlPos::set 传入的参数不正确" );
        return false;
    }
} 
//CTransparentSliderWndlPos end


// transparent dragbtn image begin
bool Property_TransparentDragBtnImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentDragBtnImage::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_TransparentDragBtnImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;
}

bool Property_TransparentDragBtnImage::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentDragBtnImage& pValue = dynamic_cast<const Value_TransparentDragBtnImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentDragBtnImage::set 传入的参数不正确" );
		return false;
	}
}
//transparent dragbtn image  end

// transparentdragbtn online begin
bool Property_DragButtonOnline::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_DragButtonOnline::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_DragButtonOnline::set(Window* tag, const String& value)
{   
	bool bOnline = CPropertyHelp::stringToBool(value);
	
	if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetOnline( bOnline );
		return true;
	}
	return false;
}

bool Property_DragButtonOnline::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_DragButtonOnline& pValue = dynamic_cast<const Value_DragButtonOnline&>(value);
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetOnline( pValue.bOnline );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_DragButtonOnline::set 传入的参数不正确" );
		return false;
	}
}
//transparentdragbtn online  end

// transparentdragbtn selstate begin
bool Property_DragButtonSel::get( const Window* src, IValue& value ) const
{	
	try 
    { 
        Value_DragButtonSel& pValue = dynamic_cast<Value_DragButtonSel&>(value);
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(src)) )
		{
			pValue.bSel = pWnd->GetSelState();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_DragButtonSel::get 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_DragButtonSel::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_DragButtonSel::set(Window* tag, const String& value)
{   
	bool bSel = CPropertyHelp::stringToBool(value);
	
	if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetSelState( bSel );
		return true;
	}
	return false;
}

bool Property_DragButtonSel::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_DragButtonSel& pValue = dynamic_cast<const Value_DragButtonSel&>(value);
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetSelState( pValue.bSel );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_DragButtonSel::set 传入的参数不正确" );
		return false;
	}
}
//transparentdragbtn selstate  end

// transparentdragbtn data begin
bool Property_DragButtonData::get( const Window* src, IValue& value ) const
{	
	try 
    { 
        Value_DragButtonData& pValue = dynamic_cast<Value_DragButtonData&>(value);
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(src)) )
		{
			pValue.pData = pWnd->GetUserData();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_DragButtonData::get 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_DragButtonData::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_DragButtonData::set(Window* tag, const String& value)
{   
	return false;
}

bool Property_DragButtonData::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_DragButtonData& pValue = dynamic_cast<const Value_DragButtonData&>(value);
		if ( CTransparentDragButton* pWnd = dynamic_cast<CTransparentDragButton*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetUserData( pValue.pData );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_DragButtonSel::set 传入的参数不正确" );
		return false;
	}
}
//transparentdragbtn data end

// TransparentProgress image begin
bool Property_TransparentProgressImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentProgressImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentProgressImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentProgress* pWnd = dynamic_cast<CTransparentProgress*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentProgressImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentProgressImage& pValue = dynamic_cast<const Value_TransparentProgressImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentProgress* pWnd = dynamic_cast<CTransparentProgress*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentProgressImage::set 传入的参数不正确" );
		return false;
	}
}
// TransparentProgress image end


// TransparentProgress Pos begin
bool Property_ProgressPos::get( const Window* src, IValue& value ) const
{	
	try 
    { 
        Value_ProgressPos& pValue = dynamic_cast<Value_ProgressPos&>(value);
		if ( CTransparentProgress* pWnd = dynamic_cast<CTransparentProgress*>(const_cast<Window*>(src)) )
		{
			pValue.nPos = pWnd->GetPos();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ProgressPos::get 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_ProgressPos::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_ProgressPos::set(Window* tag, const String& value)
{   
	int nPos = CPropertyHelp::stringToInt(value);
	
	if ( CTransparentProgress* pWnd = dynamic_cast<CTransparentProgress*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetPos( nPos );
		return true;
	}
	return false;
}

bool Property_ProgressPos::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_ProgressPos& pValue = dynamic_cast<const Value_ProgressPos&>(value);
		if ( CTransparentProgress* pWnd = dynamic_cast<CTransparentProgress*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetPos( pValue.nPos );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_ProgressPos::set 传入的参数不正确" );
		return false;
	}
}
//TransparentProgress Pos end


// VirtualBattery image begin
bool Property_VirtualBatteryImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_VirtualBatteryImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_VirtualBatteryImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CVirtualBattery* pWnd = dynamic_cast<CVirtualBattery*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_VirtualBatteryImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_VirtualBatteryImage& pValue = dynamic_cast<const Value_VirtualBatteryImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CVirtualBattery* pWnd = dynamic_cast<CVirtualBattery*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_VirtualBatteryImage::set 传入的参数不正确" );
		return false;
	}
}
// VirtualBattery image end

// VirtualBattery BatteryLife begin
bool Property_BatteryLife::get( const Window* src, IValue& value ) const
{	
	try 
    { 
        Value_BatteryLife& pValue = dynamic_cast<Value_BatteryLife&>(value);
		if ( CVirtualBattery* pWnd = dynamic_cast<CVirtualBattery*>(const_cast<Window*>(src)) )
		{
			pValue.nLife = pWnd->GetBatteryLife();
		}        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_BatteryLife::get 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_BatteryLife::get( const Window* src, String& value ) const
{
	return false;
}
bool Property_BatteryLife::set(Window* tag, const String& value)
{   
	int nLife = CPropertyHelp::stringToInt(value);
	
	if ( CVirtualBattery* pWnd = dynamic_cast<CVirtualBattery*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetBatteryLife( nLife );
		return true;
	}
	return false;
}

bool Property_BatteryLife::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_BatteryLife& pValue = dynamic_cast<const Value_BatteryLife&>(value);
		if ( CVirtualBattery* pWnd = dynamic_cast<CVirtualBattery*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetBatteryLife( pValue.nLife );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_BatteryLife::set 传入的参数不正确" );
		return false;
	}
}
//VirtualBattery BatteryLife end


// TransparentComboBoxIPStyle begin
bool Property_TransparentComboBoxIPStyle::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxIPStyle::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxIPStyle::set(Window* tag, const String& value)
{   
	try 
	{
		bool bProValue = CPropertyHelp::stringToBool( value );
		if ( CTransparentComboBox* pWnd = (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetIpStyle( bProValue );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxIPStyle::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentComboBoxIPStyle::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxIPStyle& pValue = dynamic_cast<const Value_TransparentComboBoxIPStyle&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetIpStyle( pValue.bIsIPStyle );	
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxIPStyle::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxIPStyle end

// ComboBoxList  BK color begin
bool Property_TransparentComboBoxListBkColor::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxListBkColor::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentComboBoxListBkColor::set(Window* tag, const String& value)
{   
	try 
    {  
		COLORREF col = CPropertyHelp::stringToColor(value);
        Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetListBkgColor( color );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxListBkColor::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentComboBoxListBkColor::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentComboBoxListBkColor& pValue = dynamic_cast<const Value_TransparentComboBoxListBkColor&>(value);
		(dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetListBkgColor( pValue.clrfBkColor );
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxListBkColor::set 传入的参数不正确" );
		return false;
	}
	return false;
}
// ComboBoxList  BK color end


// TransparentComboBoxImage begin
bool Property_TransparentComboBoxImage::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxImage::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxImage::set(Window* tag, const String& value)
{   
	String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
	String strFile = strImageFolder + "//" + value;
	
	if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetImage( strFile.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentComboBoxImage::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxImage& pValue = dynamic_cast<const Value_TransparentComboBoxImage&>(value);
		String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
		String strFile = strImageFolder + "//" + pValue.strImage;
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetImage( strFile.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxImage::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxImage end

// TransparentComboBoxFontSize begin
bool Property_TransparentComboBoxFontSize::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxFontSize::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxFontSize::set(Window* tag, const String& value)
{   
	try 
    {  
		int nSize = CPropertyHelp::stringToInt(value);	
		TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
        CString strFontName;
        if ( !tFontInfo.strFontName.empty() )
        {
            strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
        }
        else
        {
            strFontName = "微软雅黑";
        }

        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetFont( nSize, strFontName );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxFontSize::set 传入的参数不正确" );
        return false;
    }	
	return false;	
}

bool Property_TransparentComboBoxFontSize::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxFontSize& pValue = dynamic_cast<const Value_TransparentComboBoxFontSize&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			TFontInfo tFontInfo = CSystem::GetSingletonPtr()->GetEditFontInfo();
			CString strFontName;
			if ( !tFontInfo.strFontName.empty() )
			{
				strFontName.Format( "%s", tFontInfo.strFontName.c_str() );
			}
			else
			{
				strFontName = "微软雅黑";
			}

			pWnd->SetFont( pValue.nFontSize, strFontName );
			
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxFontSize::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxFontSize end

// TransparentComboBoxEditEdgeHeight begin
bool Property_TransparentComboBoxEditEdgeHeight::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxEditEdgeHeight::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxEditEdgeHeight::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetEditEdgeHeight( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxEditEdgeHeighth::set 传入的参数不正确" );
        return false;
    }	
	return false;	
}

bool Property_TransparentComboBoxEditEdgeHeight::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxEditEdgeHeight& pValue = dynamic_cast<const Value_TransparentComboBoxEditEdgeHeight&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetEditEdgeHeight( pValue.nEditEdgeHeight );
			
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxEditEdgeHeight::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxEditEdgeHeight end

// TransparentComboBoxDropListHeight begin
bool Property_TransparentComboBoxDropListHeight::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxDropListHeight::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxDropListHeight::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetDropListHeight( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxDropListHeight::set 传入的参数不正确" );
        return false;
    }	
	return false;	
}

bool Property_TransparentComboBoxDropListHeight::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxDropListHeight& pValue = dynamic_cast<const Value_TransparentComboBoxDropListHeight&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetDropListHeight( pValue.nDropListHeight );
			
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxDropListHeight::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxDropListHeightt end

// TransparentComboBoxEditFirstOffset begin
bool Property_TransparentComboBoxEditFrontLen::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxEditFrontLen::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxEditFrontLen::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetEditFrontLen( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxEditFrontLen::set 传入的参数不正确" );
        return false;
    }	
	return false;	
}

bool Property_TransparentComboBoxEditFrontLen::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxEditFrontLen& pValue = dynamic_cast<const Value_TransparentComboBoxEditFrontLen&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetEditFrontLen( pValue.nComboEditFrontLen );
			
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxEditFirstOffset::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxEditFirstOffset end

// TransparentComboBoxEditBackLen begin
bool Property_TransparentComboBoxEditBackLen::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxEditBackLen::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxEditBackLen::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);		
        (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)))->SetEditBackLen( nLength );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxEditBackLen::set 传入的参数不正确" );
        return false;
    }	
	return false;	
}

bool Property_TransparentComboBoxEditBackLen::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxEditBackLen& pValue = dynamic_cast<const Value_TransparentComboBoxEditBackLen&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetEditBackLen( pValue.nComboEditBackLen );
			
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxEditBackLen::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxEditBackLen end

// TransparentComboBoxShowIcon begin
bool Property_TransparentComboBoxShowIcon::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxShowIcon::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxShowIcon::set(Window* tag, const String& value)
{   
	try 
	{
		bool bProValue = CPropertyHelp::stringToBool( value );
		if ( CTransparentComboBox* pWnd = (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetShowIcon( bProValue );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxShowIcon::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentComboBoxShowIcon::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxShowIcon& pValue = dynamic_cast<const Value_TransparentComboBoxShowIcon&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetShowIcon( pValue.bIsShowIcon );	
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxShowIcon::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxShowIcon end

// TransparentComboBoxReadOnly begin
bool Property_TransparentComboBoxReadOnly::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxReadOnly::get( const Window* src, String& value ) const
{
	return false;
}

bool Property_TransparentComboBoxReadOnly::set(Window* tag, const String& value)
{   
	try 
	{
		bool bProValue = CPropertyHelp::stringToBool( value );
		if ( CTransparentComboBox* pWnd = (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetReadOnly( bProValue );
		}
		return true;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxReadOnly::set 传入的参数不正确" );
		return false;
	}	
}

bool Property_TransparentComboBoxReadOnly::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxReadOnly& pValue = dynamic_cast<const Value_TransparentComboBoxReadOnly&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetIpStyle( pValue.bIsReadOnly );	
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxReadOnly::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxReadOnly end

// TransparentComboBoxText begin
bool Property_TransparentComboBoxText::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_TransparentComboBoxText& pValue = dynamic_cast<Value_TransparentComboBoxText&>(value);
        pValue.strComboText = (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(src)))->GetComboText( );
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxText::get 传入的参数不正确" );
        return false;
    }
	return false;
}

bool Property_TransparentComboBoxText::get( const Window* src, String& value ) const
{
    try 
    { 
        value = (dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(src)))->GetComboText();
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxText::get 传入的参数不正确" );
        return false;
    }
	return false;
}

bool Property_TransparentComboBoxText::set(Window* tag, const String& value)
{   
	if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
	{
		pWnd->SetComboText( value.c_str() );
		return true;
	}
	return false;	
}

bool Property_TransparentComboBoxText::set( Window* tag, const IValue& value )											  
{
	try
	{
		const Value_TransparentComboBoxText& pValue = dynamic_cast<const Value_TransparentComboBoxText&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			pWnd->SetComboText( pValue.strComboText.c_str() );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxText::set 传入的参数不正确" );
		return false;
	}
}
// TransparentComboBoxText end

// TransparentComboBoxText LimitLength begin
bool Property_TransparentComboBoxLimitLength::get( const Window* src, IValue& value ) const
{	
	return false;
}

bool Property_TransparentComboBoxLimitLength::get( const Window* src, String& value ) const
{	
	return false;
}
bool Property_TransparentComboBoxLimitLength::set(Window* tag, const String& value)
{   
	try 
    {  
		int nLength = CPropertyHelp::stringToInt(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			if( CTransparentEdit* pEdit = pWnd->GetEditPoint() )
			{
				pEdit->SetLimitLength( nLength );
			} 
			return true;
		}     
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentComboBoxLimitLength::set 传入的参数不正确" );
        return false;
    }	
	return false;
}

bool Property_TransparentComboBoxLimitLength::set( Window* tag, const IValue& value )
{
	try 
	{
		const Value_TransparentComboBoxLimitLength& pValue = dynamic_cast<const Value_TransparentComboBoxLimitLength&>(value);
		if ( CTransparentComboBox* pWnd = dynamic_cast<CTransparentComboBox*>(const_cast<Window*>(tag)) )
		{
			if( CTransparentEdit* pEdit = pWnd->GetEditPoint() )
			{
				pEdit->SetLimitLength( pValue.length );
			} 
			return true;
		}  
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentComboBoxLimitLength::set 传入的参数不正确" );
		return false;
	}
	return false;
}
//TransparentComboBoxText LimitLength end


//tranparenthorilist offset set/get begin 
bool Property_TransHoriListOffset::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransHoriListOffset::get( const Window* src, IValue& value ) const
{
    return false;
}

bool Property_TransHoriListOffset::set(Window* tag, const String& value)
{
    try 
    {  
        int nOffset = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetTotalOffset( nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransHoriListOffset::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransHoriListOffset::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransHoriListOffset& pValue = dynamic_cast<const Value_TransHoriListOffset&>(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetTotalOffset( pValue.nOffset );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransHoriListOffset::set 传入的参数不正确" );
        return false;
    }	
} 
//tranparenthorilist offset set/get end 


//tranparenthorilist SelItem set/get begin 
bool Property_TransHoriListSelItem::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransHoriListSelItem::get( const Window* src, IValue& value ) const
{
    try 
    { 
        Value_TransHoriListSelItem& pValue = dynamic_cast<Value_TransHoriListSelItem&>(value);
        pValue.pSelItem = (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(src)))->GetSelItem();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransHoriListSelItem::get 传入的参数不正确" );
        return false;
    }
    return false;
}

bool Property_TransHoriListSelItem::set(Window* tag, const String& value)
{
    try 
    {  
        int nSel = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentHoriList*>(tag))->SetSelItem( nSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransHoriListSelItem::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_TransHoriListSelItem::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransHoriListSelItem& pValue = dynamic_cast<const Value_TransHoriListSelItem&>(value);
        (dynamic_cast<CTransparentHoriList*>(const_cast<Window*>(tag)))->SetSelItem( pValue.dwDataKey );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransHoriListSelItem::set 传入的参数不正确" );
        return false;
    }	
} 
//tranparenthorilist SelItem set/get end 


// transparent viewlist image begin
bool Property_TransparentViewListImage::get( const Window* src, IValue& value ) const
{	
    return false;
}

bool Property_TransparentViewListImage::get( const Window* src, String& value ) const
{
    return false;
}
bool Property_TransparentViewListImage::set(Window* tag, const String& value)
{   
    try 
    {
        String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
        String strFile = strImageFolder + "//" + value;
        if ( CTransparentViewList* pWnd = (dynamic_cast<CTransparentViewList*>(tag)) )
        {
            pWnd->SetImage( strFile.c_str() );
        }
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentViewListImage::set 传入的参数不正确" );
        return false;
    }	
}

bool Property_TransparentViewListImage::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_TransparentViewListImage& pValue = dynamic_cast<const Value_TransparentViewListImage&>(value);
        String strImageFolder = CSystem::GetSingletonPtr()->GetImagePath();
        String strFile = strImageFolder + "//" + pValue.strImage;
        
        if ( CTransparentViewList* pWnd = (dynamic_cast<CTransparentViewList*>(tag)) )
        {
            pWnd->SetImage( strFile.c_str() );
            return true;
        }
        return false;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentViewListImage::set 传入的参数不正确" );
        return false;
    }
}
// transparent viewlist image end

//tranparentviewlist select item set/get begin 
bool Property_ViewListSelItem::set(Window* tag, const String& value)
{   
    try 
    {  
        int nSel = CPropertyHelp::stringToInt(value);
        (dynamic_cast<CTransparentViewList*>(tag))->SetSelItem( nSel );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ViewListSelItem::set 传入的参数不正确" );
        return false;
    }
    return false;	
}

bool Property_ViewListSelItem::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_ViewListSelItem::set( Window* tag, const IValue& value )
{
    try 
    {
        const Value_ViewListSelItem& pValue = dynamic_cast<const Value_ViewListSelItem&>(value);
        (dynamic_cast<CTransparentViewList*>(tag))->SetSelItem( pValue.dwDataKey );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ViewListSelItem::set 传入的参数不正确" );
        return false;
    }	
} 

bool Property_ViewListSelItem::get( const Window* src, IValue& value ) const
{	
    try 
    { 
        Value_ViewListSelItem& pValue = dynamic_cast<Value_ViewListSelItem&>(value);
        pValue.pSelItem = (dynamic_cast<CTransparentViewList*>(const_cast<Window*>(src)))->GetSelItem();
        
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ViewListSelItem::get 传入的参数不正确" );
        return false;
    }	
    return false;
}
//tranparentviewlist select item set/get end

//tranparentlist Over set/get begin 
bool Property_TransparentViewListOver::get( const Window* src, String& value ) const
{
    return false;
}

bool Property_TransparentViewListOver::get( const Window* src, IValue& value ) const
{	  
    return false;
}

bool Property_TransparentViewListOver::set(Window* tag, const String& value)
{
	try 
    {  
        bool bOver = CPropertyHelp::stringToBool(value);
        (dynamic_cast<CTransparentViewList*>(const_cast<Window*>(tag)))->SetListOver( bOver );
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_TransparentViewListOver::set 传入的参数不正确" );
        return false;
    }
    return false;	
} 

bool Property_TransparentViewListOver::set( Window* tag, const IValue& value )
{ 
	try 
	{
		const Value_TransparentViewListOver& pValue = dynamic_cast<const Value_TransparentViewListOver&>(value);		
		if ( CTransparentViewList* pWnd = (dynamic_cast<CTransparentViewList*>(const_cast<Window*>(tag))) )
		{
			pWnd->SetListOver( pValue.bOver );
			return true;
		}
		return false;
	}
	catch( bad_cast )
	{
		LOGEVENT( "Property_TransparentViewListOver::set 传入的参数不正确" );
		return false;
	}
} 
//tranparentlist Over set/get end

bool Property_ViewListVertSliderOffset::get( const Window* src, String& value ) const
{
    return true;
}

bool Property_ViewListVertSliderOffset::get( const Window* src, IValue& value ) const
{
    return true;
}

bool Property_ViewListVertSliderOffset::set(Window* tag, const String& value)
{
    POINT pt = CPropertyHelp::stringToPoint( value );

    if ( CTransparentViewList* pList = dynamic_cast<CTransparentViewList*>(tag) )
    {
        pList->SetVertSliderOffsetPos( CPoint( pt.x, pt.y ) );
    }

    return true;
}

bool Property_ViewListVertSliderOffset::set( Window* tag, const IValue& value )
{    
    try 
    {
        const Value_ViewListVertSliderOffset& pValue = dynamic_cast<const Value_ViewListVertSliderOffset&>(value);    
        if ( CTransparentViewList* pList = dynamic_cast<CTransparentViewList*>(tag) )
        {
            pList->SetVertSliderOffsetPos( CPoint( pValue.nX, pValue.nY ) );
        }
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ViewListVertSliderOffset::set 传入的参数不正确" );
        return false;
    }
    return false;
}

bool Property_ViewListHoriSliderOffset::get( const Window* src, String& value ) const
{
    return true;
}

bool Property_ViewListHoriSliderOffset::get( const Window* src, IValue& value ) const
{
    return true;
}

bool Property_ViewListHoriSliderOffset::set(Window* tag, const String& value)
{
    POINT pt = CPropertyHelp::stringToPoint( value );
    
    if ( CTransparentViewList* pList = dynamic_cast<CTransparentViewList*>(tag) )
    {
        pList->SetHoriSliderOffsetPos( CPoint( pt.x, pt.y ) );
    }
    
    return true;
}

bool Property_ViewListHoriSliderOffset::set( Window* tag, const IValue& value )
{    
    try 
    {
        const Value_ViewListHoriSliderOffset& pValue = dynamic_cast<const Value_ViewListHoriSliderOffset&>(value);    
        if ( CTransparentViewList* pList = dynamic_cast<CTransparentViewList*>(tag) )
        {
            pList->SetHoriSliderOffsetPos( CPoint( pValue.nX, pValue.nY ) );
        }
        return true;
    }
    catch( bad_cast )
    {
        LOGEVENT( "Property_ViewListHoriSliderOffset::set 传入的参数不正确" );
        return false;
    }
    return false;
}


} // namespace AutoUIFactory end
