// tpTools.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "tpTools.h"
#include "tpToolsDlg.h"

#pragma comment (lib, "cnstooldll.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTpToolsApp

BEGIN_MESSAGE_MAP(CTpToolsApp, CWinApp)
	//{{AFX_MSG_MAP(CTpToolsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTpToolsApp construction

CTpToolsApp::CTpToolsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTpToolsApp object

CTpToolsApp theApp;
 
EM_SERVERAPP_TYPE g_emServerType = em_UMSTOOL_APP;

/////////////////////////////////////////////////////////////////////////////
// CTpToolsApp initialization

BOOL CTpToolsApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTpToolsDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CTpToolsApp::PreTranslateMessage(MSG* pMsg) 
{ 
	switch( pMsg->message )
	{
	case WM_KEYDOWN:
		{  
			if ( pMsg->wParam == VK_ESCAPE )
			{
				return TRUE;
			}
			
			if ( pMsg->wParam == VK_RETURN && pMsg->hwnd )
			{    
				s8 chWindowName[256] = {0};												//增加COMBOBOXLIST可以接收回车键
				GetWindowText( pMsg->hwnd,chWindowName,sizeof( chWindowName ));

				s8 chClassName[256] = {0};
				GetClassName(  pMsg->hwnd,chClassName,sizeof(chClassName) ); 
				if (( strcmp(chClassName,"Edit") != 0 )&&( strcmp(chWindowName,"TransparentComboBoxList") == 0))
				{
					return CWinApp::PreTranslateMessage(pMsg);
				}

				if ( AfxGetMainWnd()->IsWindowVisible() )
				{
					CWinApp::PreTranslateMessage(pMsg);
				}
				else      //主界面指定编辑框可接收
				{
					s8 pName[256] = {0};
					GetClassName(  pMsg->hwnd,pName,sizeof(pName) );  
					if ( strcmp(pName,"Edit") == 0 || strcmp(pName,"RichEdit") == 0   )
					{  
						return CWinApp::PreTranslateMessage(pMsg); 
					}
				}
				
				return TRUE;
			}
		}
	default:
		{
		}
		break;
	}

	if ( em_UMSTOOL_APP == g_emServerType )
	{
		if ( UMSTOOLSPACE::IsInitUmsTool() )
		{
			if(UMSTOOLSPACE::DllPreTranslateMessage(pMsg))
				return TRUE;
		}
	}
	else if ( g_emServerType == em_CNSTOOL_APP )
	{
		if ( CNSTOOL::IsInitCnsTool() )
		{
			if( CNSTOOL::HandleCnsToolMsg(pMsg))
				return TRUE;
		} 
	 
	}
	/*else
	{
		if ( MOONTOOL::IsInitMoonTool() )
		{
			if ( MOONTOOL::HandleMoonToolMsg(pMsg) )
			{
				return TRUE;
			}
		}
	}*/

    return CWinApp::PreTranslateMessage(pMsg);
}
