#include "StdAfx.h"
#include "CommonListUI.h"

//文件列表
const TCHAR* const PRO_BTN_CHECK = _T("btnCheck");
const TCHAR* const PRO_CT_WALL = _T("ctWall");
const TCHAR* const PRO_LB_FILENAME = _T("lbFileName");
const TCHAR* const PRO_LB_FILEPATH = _T("lbFilePath");

//会议列表
const TCHAR* const PRO_LB_CONFID = _T("lbConfID");
const TCHAR* const PRO_LB_CONFNAME = _T("lbConfName");
const TCHAR* const PRO_PROG_CONFPROG = _T("progConfProg");

//地址簿列表
//const TCHAR* const PRO_LB_ADDRID = _T("lbAddrIDD");
const TCHAR* const PRO_LB_ADDRNAME = _T("lbAddrName");
const TCHAR* const PRO_LB_ADDRNUM = _T("lbAddrNum");
const TCHAR* const PRO_LB_CHECK = _T("lbCheck");
static bool OnLogoButtonEvent(void* pEvent) 
{
	if( ((TEventUI*)pEvent)->Type == UIEVENT_BUTTONDOWN ) 
	{
		CControlUI* pButton = ((TEventUI*)pEvent)->pSender;
		if( pButton != NULL ) 
		{
// 			CListContainerElementUI* pListElement = (CListContainerElementUI*)(pButton->GetTag());
// 			if( pListElement != NULL ) pListElement->DoEvent(*(TEventUI*)pEvent);

			CButtonUI* log_button = static_cast<CButtonUI*>(pButton);
			if (log_button != NULL)
			{
				std::wstring strImg = log_button->GetFocusedImage();
				if ( strImg ==  log_button->GetPushedImage() )
				{
					log_button->SetFocusedImage( log_button->GetNormalImage() );
				}
				else
				{
					log_button->SetFocusedImage( log_button->GetPushedImage() );
				}
			}
		}
	}

	return true;
}

Node* CCommonListUI::DrawItemEx( const Data_FileList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;

	Data_FileList* pItemData = const_cast<Data_FileList*>(pData);
	if ( NULL == pItemData )	return NULL;

	CListContainerElementUI* pItemList = this->CreateElement();				//创建ListContainerElement
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedHeight(m_nListItemHeight);
	pItemList->SetItemName(this->GetName()/*.GetData()*/);						//设置ListElement name为列表name  注册消息即能匹配事件响应

	Node* pItemNode = new Node;
	if ( NULL == pItemNode )	return NULL;

	
	int nItemCount = pParent->GetChildNum();
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);


	//列表ITEM控件数据设置
	this->SetButtonNode( pItemList, PRO_BTN_CHECK, &OnLogoButtonEvent );


	tString strText;

	pItemNode->GetData().bFolder = pItemData->m_tData.bFolder;					//列表如有下级 则设置foder haschild为true 否则为false
	pItemNode->GetData().bHasChild = pItemData->m_tData.bFolder;
	if ( pItemData->m_tData.bFolder )
	{
		this->SetContainerVisible( pItemList, PRO_CT_WALL );
		strText += L"<x 8>";
		strText += m_strLevelCollapseImg;										//文件夹图片显示
		strText += L"<x 12>";

		strText += L"<x 2>";													//向右缩进2px
		strText += pItemData->m_tData.strFileName;
		this->SetLabelNode( pItemList, PRO_LB_FILENAME, strText, true );

		strText = L"<x 70>";													//可以用html动态控制字体 颜色等 _stprintf_s( szBuf, MAX_PATH - 1, _T("<x 20><c #2CF922>%s</c>"), pItemData->m_tData.strConfName.c_str() );
		strText += pItemData->m_tData.strPath.c_str();
		this->SetLabelNode( pItemList, PRO_LB_FILEPATH, strText, true );
	}
	else
	{
		strText += L"<x 2>";													//向右缩进2px
		strText += pItemData->m_tData.strFileName;
		this->SetLabelNode( pItemList, PRO_LB_FILENAME, strText, true );


		strText = L"<x 20>";													//可以用html动态控制字体 颜色等 _stprintf_s( szBuf, MAX_PATH - 1, _T("<x 20><c #2CF922>%s</c>"), pItemData->m_tData.strConfName.c_str() );
		strText += pItemData->m_tData.strPath.c_str();
		this->SetLabelNode( pItemList, PRO_LB_FILEPATH, strText, true );
	}



	this->AddAtEnd( pItemList, pParent );
	pParent->AddChild(pItemNode);

	return pItemNode;
}

Node* CCommonListUI::DrawItemEx( const Data_ConfList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;
	
	Data_ConfList* pItemData = const_cast<Data_ConfList*>(pData);			//得到ITEM结点数据
	if ( NULL == pItemData )	return NULL;

	CListContainerElementUI* pItemList =  this->CreateElement();
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedWidth(50);		//未生效？
	pItemList->SetFixedHeight(m_nListItemHeight);
	pItemList->SetItemName(this->GetName()/*.GetData()*/);						//设置ListElement name为列表name  注册消息即能匹配事件响应

	Node* pItemNode = new Node;												//创建ITEM结点
	if ( NULL == pItemNode )	return NULL;


	int nItemCount = pParent->GetChildNum();								//设置结点数据
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);									//设置点击ITEM数据

	//列表ITEM控件数据设置
	this->SetButtonNode( pItemList, PRO_BTN_CHECK, &OnLogoButtonEvent );


	tString strText;
	strText = L"<x 2>";														//向右缩进2px
	strText += pItemData->m_tData.strConfID;
	this->SetLabelNode( pItemList, PRO_LB_CONFID, strText, true );


	strText = L"<x 0>";														//可以用html动态控制字体 颜色等 _stprintf_s( szBuf, MAX_PATH - 1, _T("<x 20><c #2CF922>%s</c>"), pItemData->m_tData.strConfName.c_str() );
	strText += pItemData->m_tData.strConfName.c_str();
	this->SetLabelNode( pItemList, PRO_LB_CONFNAME, strText, true );

	this->SetProgressNode( pItemList, PRO_PROG_CONFPROG, pData->m_tData.nProgress, true );

	this->AddAtEnd( pItemList, pParent );
	pParent->AddChild(pItemNode);

	return pItemNode;
}

Node* CCommonListUI::DrawItemEx( const Data_AddrList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;

	Data_AddrList* pItemData = const_cast<Data_AddrList*>(pData);
	if ( NULL == pItemData )	return NULL;

	CListContainerElementUI* pItemList = this->CreateElement();				//创建ListContainerElement
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedHeight(m_nListItemHeight);							//生效的
	pItemList->SetItemName(this->GetName()/*.GetData()*/);					//设置ListElement name为列表name  注册消息即能匹配事件响应

	Node* pItemNode = new Node;
	if ( NULL == pItemNode )	return NULL;

	int nItemCount = pParent->GetChildNum();
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);

	tString strText;

	strText = L"<x 18>";													//向右缩进10px
	strText += pItemData->m_tData.strAddrName;
	this->SetLabelNode( pItemList, PRO_LB_ADDRNAME, strText, true );

	strText = L"<x 18>";													//可以用html动态控制字体 颜色等 _stprintf_s( szBuf, MAX_PATH - 1, _T("<x 20><c #2CF922>%s</c>"), pItemData->m_tData.strConfName.c_str() );
	strText += pItemData->m_tData.strAddrNum;
	this->SetLabelNode( pItemList, PRO_LB_ADDRNUM, strText, true );

	this->SetClickLabelNode(pItemList, PRO_LB_CHECK, nItemCount, false, this->GetName(), pItemNode);

	if ( -1 == m_nVirtualItemPos )
	{
		this->AddAtEnd( pItemList, pParent );
	}
	else
	{
		this->AddAt( pItemList, pParent );
	}
	pParent->AddChild(pItemNode);

	return pItemNode;
}

Node* CCommonListUI::DrawItem( const Data_DynamicList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;

	Data_DynamicList* pItemData = const_cast<Data_DynamicList*>(pData);		//得到ITEM结点数据
	if ( NULL == pItemData )	return NULL;


	//	CListContainerElementUI* pItemList =  NULL; //static_cast<CListContainerElementUI*>(m_pManager->FindControl(L"listTest"))/*this->CreateElement()*/;				//创建ListContainerElement

	CListContainerElementUI* pItemList = this->CreateElement(L"45");
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedWidth(50);		//未生效？
	pItemList->SetFixedHeight(m_nListItemHeight);
	pItemList->SetItemName(this->GetName()/*.GetData()*/);						//设置ListElement name为列表name  注册消息即能匹配事件响应


	//创建列表Item控件
// 	CHorizontalLayoutUI *new_h_lay = new CHorizontalLayoutUI;
// 	new_h_lay->ApplyAttributeList(_T("float=\"false\" ")\
// 		_T("childpadding=\"10\" inset=\"3,5,3,5\""));


	TItemNodeUI tItemNodeUI;
	tItemNodeUI.strPos = L"140,2,0,0";
	tItemNodeUI.strWidth = L"20";
	tItemNodeUI.strText = L"100%";
	CLabelUI* plbPrg = this->CreateLabel( tItemNodeUI );

	tItemNodeUI.Clear();
	tItemNodeUI.strPos = L"30,1,0,0";
	tItemNodeUI.strWidth = L"20";
	tItemNodeUI.strHeight = L"20";
	tItemNodeUI.strImgPath = L"btnCommon/btnFile/";
	CButtonUI* pBtnFir = this->CreateButton( tItemNodeUI );

	//CVerticalLayoutUI *new_v_lay = new CVerticalLayoutUI;
	//new_v_lay->ApplyAttributeList(_T("height=\"60\""));

	tItemNodeUI.Clear();
	tItemNodeUI.strPos = L"55,6,0,0";
	tItemNodeUI.strWidth = L"150";
	tItemNodeUI.strHeight = L"8";
	tItemNodeUI.nValue = pData->m_tData.nProgress;/*100;*/
	tItemNodeUI.strImgPath = L"progress_fore.png";
	CProgressUI* pProgress = this->CreateProgress( tItemNodeUI );

	tItemNodeUI.Clear();
	tItemNodeUI.strPos = L"210,1,0,0";
	tItemNodeUI.strWidth = L"210";
	tItemNodeUI.strHeight = L"20";
	tItemNodeUI.strText = L"下载中...";
	tItemNodeUI.strFontColor = L"#FF2CF922";
	CTextUI* pTextFir = this->CreateText( tItemNodeUI );

	tItemNodeUI.Clear();
	tItemNodeUI.strPos = L"280,1,0,0";
	tItemNodeUI.strText = pItemData->m_tData.strID;
	CTextUI* pTextSec = this->CreateText( tItemNodeUI );

	tItemNodeUI.Clear();
	tItemNodeUI.strPos = L"340,1,0,0";
	tItemNodeUI.strWidth = L"20";
	tItemNodeUI.strHeight = L"20";
	tItemNodeUI.strImgPath = L"btnCommon/btnCheck/";
	CButtonUI* pBtnSec = this->CreateButton( tItemNodeUI );
	//this->SetButtonNode( pItemList, PRO_BTN_CHECK, &OnLogoButtonEvent );

	//new_h_lay->Add(new_label);
	//new_h_lay->Add(new_btn_1);
	//new_h_lay->Add(new_v_lay);
	//pItemList->Add(new_h_lay);

	pItemList->Add(plbPrg);
	pItemList->Add(pBtnFir);
	pItemList->Add(pProgress);
	pItemList->Add(pTextFir);
	pItemList->Add(pTextSec);
	pItemList->Add(pBtnSec);



	Node* pItemNode = new Node;											//创建ITEM结点
	if ( NULL == pItemNode )	return NULL;


	int nItemCount = pParent->GetChildNum();							//设置结点数据
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);								//设置点击ITEM数据

	//列表ITEM控件数据设置
	//this->SetButtonNode( pItemList, PRO_BTN_CHECK, &OnLogoButtonEvent );


	this->AddAtEnd( pItemList, pParent );
	pParent->AddChild(pItemNode);

	return pItemNode;
}

Node* CCommonListUI::DrawItem( const Data_BoardList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;

	Data_BoardList* pItemData = const_cast<Data_BoardList*>(pData);		//得到ITEM结点数据
	if ( NULL == pItemData )	return NULL;

	CListContainerElementUI* pItemList = this->CreateElement( L"62", L"62" );
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedHeight(m_nListItemHeight);
	pItemList->SetItemName(this->GetName()/*.GetData()*/);					//设置ListElement name为列表name  注册消息即能匹配事件响应


	//创建列表Item控件
	TItemNodeUI tItemNodeUI;
	int nXPos = 0;
	tString strPos;
	TCHAR szBuf[10];
	for ( int nIndex = 0; nIndex < 9; nIndex++ )
	{
		memset( szBuf, 0, 10 );
		nXPos = 5 + 60*nIndex;
		::wsprintf( szBuf, _T("%d"), nXPos );
		strPos = szBuf;
		strPos += L",1,0,0";

		tItemNodeUI.Clear();
		tItemNodeUI.strPos = strPos;
		tItemNodeUI.strWidth = L"58";
		tItemNodeUI.strHeight = L"62";
		tItemNodeUI.strImgPath = L"listDemo/listboard/boardlisticonnor/";
		CButtonUI* pBtn = this->CreateButton( tItemNodeUI );


		memset( szBuf, 0, 10 );
		nXPos = 5 + 60*nIndex + 12;
		::wsprintf( szBuf, _T("%d"), nXPos );
		strPos = szBuf;
		strPos += L",34,0,0";

		tItemNodeUI.Clear();
		tItemNodeUI.strPos = strPos;
		tItemNodeUI.strWidth = L"40";
		tItemNodeUI.strHeight = L"62";
		tItemNodeUI.strText = L"MPC板";
		tItemNodeUI.nFont = 2;
		tItemNodeUI.strFontColor = L"#FFDD1111";
		CTextUI* pTextFir = this->CreateText( tItemNodeUI );

		pItemList->Add(pTextFir);
		pItemList->Add(pBtn);
	}



	Node* pItemNode = new Node;											//创建ITEM结点
	if ( NULL == pItemNode )	return NULL;


	int nItemCount = pParent->GetChildNum();							//设置结点数据
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);								//设置点击ITEM数据

	this->AddAtEnd( pItemList, pParent );
	pParent->AddChild(pItemNode);

	return pItemNode;
}

Node* CCommonListUI::DrawItem( const Data_TvwStyleList* pData, Node* pParent )
{
	if ( NULL == pData || NULL == pParent ) return NULL;

	Data_TvwStyleList* pItemData = const_cast<Data_TvwStyleList*>(pData);		//得到ITEM结点数据
	if ( NULL == pItemData )	return NULL;

	CListContainerElementUI* pItemList = this->CreateElement( L"40", L"40" );
	if ( pItemList == NULL )	return NULL;
	pItemList->SetFixedHeight(m_nListItemHeight);
	pItemList->SetItemName(this->GetName()/*.GetData()*/);							//设置ListElement name为列表name  注册消息即能匹配事件响应


	//创建列表Item控件
	TItemNodeUI tItemNodeUI;
	int nXPos = 0;
	tString strPos;
	TCHAR szBuf[10];
	for ( int nIndex = 0; nIndex < 5; nIndex++ )
	{
		memset( szBuf, 0, 10 );
		nXPos = 5 + 72*nIndex;
		::wsprintf( szBuf, _T("%d"), nXPos );
		strPos = szBuf;
		strPos += L",1,0,0";

		tItemNodeUI.Clear();
		tItemNodeUI.strPos = strPos;
		tItemNodeUI.strWidth = L"72";
		tItemNodeUI.strHeight = L"40";
		tItemNodeUI.strImgPath = L"listDemo/listtvwstyle/btnTvwStyleLst/";
		CButtonUI* pBtn = this->CreateButton( tItemNodeUI );


		memset( szBuf, 0, 10 );
		nXPos = 5 + 72*nIndex + 22;
		::wsprintf( szBuf, _T("%d"), nXPos );
		strPos = szBuf;
		strPos += L",6,0,0";

		tItemNodeUI.Clear();
		tItemNodeUI.strPos = strPos;
		tItemNodeUI.strWidth = L"72";
		tItemNodeUI.strHeight = L"40";
		tItemNodeUI.strText = L"通道";
		tItemNodeUI.nFont = 2;
		tItemNodeUI.strFontColor = L"#FFDD1111";
		CTextUI* pTextFir = this->CreateText( tItemNodeUI );


		memset( szBuf, 0, 10 );
		nXPos = 5 + 72*nIndex + 24;
		::wsprintf( szBuf, _T("%d"), nXPos );
		strPos = szBuf;
		strPos += L",22,0,0";

		tItemNodeUI.Clear();
		tItemNodeUI.strPos = strPos;
		tItemNodeUI.strWidth = L"72";
		tItemNodeUI.strHeight = L"40";
		tItemNodeUI.strText = L"[1]";
		tItemNodeUI.nFont = 2;
		tItemNodeUI.strFontColor = L"#FF2211FF";
		CTextUI* pTextSec = this->CreateText( tItemNodeUI );

		pItemList->Add(pTextFir);
		pItemList->Add(pTextSec);
		pItemList->Add(pBtn);
	}



	Node* pItemNode = new Node;											//创建ITEM结点
	if ( NULL == pItemNode )	return NULL;


	int nItemCount = pParent->GetChildNum();							//设置结点数据
	pItemData->SetDataKey(nItemCount);
	pItemNode->SetUserData(pItemData);

	pItemNode->GetData().pListElement = pItemList;
	pItemList->SetTag((UINT_PTR)pItemNode);								//设置点击ITEM数据

	this->AddAtEnd( pItemList, pParent );
	pParent->AddChild(pItemNode);

	return pItemNode;
}