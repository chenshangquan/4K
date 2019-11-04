// listAssist.cpp: implementation of the CListAssist class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "listAssist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// 
// CListAssist::CListAssist()
// {
// 	 m_strValTypeFuncMenu = "";//功能列表
// }
// 
// CListAssist::~CListAssist()
// {
// 
// }
bool Value_ItemMenu::SetData( IItemList* pList )
{ 	
	if ( pList == NULL || m_pMenuList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm(  m_strAlgroithm ); 
	pBaseItem->SetMoveStatus( m_bDrag );
	
	//	sort( m_pMenuList->begin(), m_pMenuList->end(), CompareListData ); //排序
	
	Args_BuildItem args;
	args.pList = pList;
	args.bDrag = m_bDrag;
	args.strClickItemFunc = "";// m_strClickItemFunc;
	args.pVctSubItem =  NULL;// m_pVctSubItem;
	args.strImageItem = m_strImgItemType;
	args.strTxtItem = m_strTxtItemType;  
	
	s32 count =  m_pMenuList->size(); 
	for ( int j = 0; j < count; j++ )
	{ 
        args.strImageItem = m_pMenuList->at(j).szItemType;

		Data_ItemMenu UserData( *( &m_pMenuList->at(j) ) );  
		UserData.SetDataKey( j );
	   
		args.nKey = j;
		args.strTxt =m_pMenuList->at(j).szName;
		args.pUserData = &UserData;
		
		BuildItem( args );
	}
	return true;
}//end SetData()
		
   

bool Value_ItemTPad::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strTPadIpList ); 
	pBaseItem->SetMoveStatus( false );
	
	s32 count =  m_ptTPadList->m_byTPadNum; 
	for ( int j = 0; j < count; j++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextTpadIPItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{
			in_addr tAddr;
			tAddr.S_un.S_addr = m_ptTPadList->m_adwTPadIP[j];
			String strDualIp;
			strDualIp = inet_ntoa(tAddr);
			pTextItem->SetText( strDualIp );
		}
		
		IItemList *pNew = pList->AddItem( j, pItem, emGroup );  //添加 一个条目  
		delete pItem;
		pItem = 0;
	}
	return true;
}


bool Value_ItemNetMng::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecNMServerCfgLst->size(); 
	int nRow = 0;
	int nColSize = 5;
	
	for ( vector<TTPNMServerCfg>::iterator it = m_pVecNMServerCfgLst->begin(); it != m_pVecNMServerCfgLst->end(); it++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemNetMng" );
		
		TTPNMServerCfg tTPNMServerCfg;
		tTPNMServerCfg = *it;
		//tTPNMServerCfg.dwNMServerIP = ntohl(tTPNMServerCfg.dwNMServerIP);
		
		Data_NetMng dataNetMng(tTPNMServerCfg);
		dataNetMng.SetDataKey( nRow );
		
		pItem->SetFunc("CCfgNetMngLogic::OnClickNetMngLst");
		pItem->SetUserData( &dataNetMng );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		delete pItem;
		pItem = 0;
		
		
		for ( int i = 0; i < nColSize; i++ )
		{
			IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemNetMng" );
			
			if ( NULL == pSubItem )
			{			
				return false;
			}
			
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
			{
				
				String strItem;
				switch(i)
				{
				case 0:
					{
						in_addr tAddr;
						tAddr.S_un.S_addr = it->dwNMServerIP;
						strItem = inet_ntoa(tAddr);
						break;
					}
				case 1:
					{
						strItem = tTPNMServerCfg.achNMReadCommunity;
						break;
					}
				case 2:
					{
						strItem = tTPNMServerCfg.achNMWriteCommunity;
						break;
					}
				case 3:
					{
						char chTemp[10] = {0};
						_itot( tTPNMServerCfg.wNMGetSetPort, chTemp, 10 );
						strItem = chTemp;
						break;
					}
				case 4:
					{
						char chTemp[10] = {0};
						_itot( tTPNMServerCfg.WNMTrapPort, chTemp, 10 );
						strItem = chTemp;
						break;
					}
				default:
					break;
				}
				
				pTextItem->SetText( strItem );
				pNew->AddItem( i, pTextItem, emGroup );  //添加 一个条目
			}
			
			delete pSubItem;
			pSubItem = 0;
		}
		nRow++;
	}
	return true;
}

bool Value_ItemLight::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strTPadIpList ); 
	pBaseItem->SetMoveStatus( false );
	
	int z = 1;			//通过j与z的差值，正确的得出各个灯光所对应的状态
	s32 count =  16; 
	for ( int j = 0; j < count; j++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextLightItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{
			String strState;
			if ( j%2 == 0 )
			{
				switch(j)
				{
				case 0:
					strState = "灯光一";
					break;
				case 2:
					strState = "灯光二";
					break;
				case 4:
					strState = "灯光三";
					break;
				case 6:
					strState = "灯光四";
					break;
				case 8:
					strState = "灯光五";
					break;
				case 10:
					strState = "灯光六";
					break;				
				case 12:
					strState = "灯光七";
					break;
				case 14:
					strState = "灯光八";
					break;
				default:
					break;
				}
			} 
			else
			{	
				if ( j == 3)
				{
					switch(m_ptSchCfg->emSchMidLight)
					{
					case emSchMidLightOn:
						strState = "开";
						break;
					case emSchMidLightOff:
						strState = "关";
						break;
					case emSchMidLightInvalid:
						strState = "关";
						break;
					default:
						break;
					}
				}
				else if ( j == 13)
				{
					switch(m_ptSchCfg->emSchScrLight)
					{
					case emSchScrLightOn:
						strState = "开";
						break;
					case emSchScrLightOff:
						strState = "关";
						break;
					case emSchScrLightInvalid:
						strState = "关";
						break;
					default:
						break;
					}
				}
				else if ( j != 3 && j != 13 )
				{
					switch(m_ptSchCfg->emSchLight)
					{
					case emSchLightOn:
						strState = "开";
						break;
					case emSchLightOff:
						strState = "关";
						break;
					case emSchLightInvalid:
						strState = "关";
						break;
					default:
						break;
					}
				}
				z++;
			}
			pTextItem->SetText( strState );
		}
		
		IItemList *pNew = pList->AddItem( j, pItem, emGroup );  //添加 一个条目  
		delete pItem;
		pItem = 0;
	}
	return true;
}

bool Value_ItemCOMMON::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strMultiColumn ); 
	pBaseItem->SetMoveStatus( false );

	TListRangeInfo tRangeInfo;
	tRangeInfo.nFirstLeft = 0;
	tRangeInfo.nFirstTop = 0;
	tRangeInfo.nMaxColumn = 2;
	tRangeInfo.nVertSpace = 16;

	Data_ListRangeInfo dataRangeInfo(tRangeInfo);
	pBaseItem->SetUserData( &dataRangeInfo );

	//以下是筛选出被选中的卡侬麦克风号，并且将卡侬麦克风10放在数组的最后一个
	u32 count = 0;			//表示的是某个卡侬麦克风的编号
	u32 bUse10 = 0;			//用来存放来自哪个组的卡侬麦克风10
	u32 bIsUse[10];			//用来存放具体是哪个卡侬麦克风被选中
	for ( int i=0; i<3; i++ )
	{
		for ( int j=0; j<4; j++ )
		{
			if (TRUE == m_ptAudioDiagInfo->m_atPrimAudioInputPort[i].m_abAudioPort[j])
			{
				for ( count; count<10; )			
 				{
					if ( 0 == i )
					{
						bIsUse[count] = j;
					}
					if ( 1 == i )
					{
						bIsUse[count] = j+3;
					}
					if ( 2 == i )
					{
						bIsUse[count] = j+6;
					}
					if ( 3 == j && 0 == i )
					{
						bUse10 = 110;
						count -= 1;
					}
					if ( 3 == j && 1 == i )
					{
						bUse10 = 210;
						count -= 1;
					}
					if ( 3 == j && 2 == i )
					{
						bUse10 = 310;
						count -= 1;
					}
					count++;
					break;
				}
			}
		}
	}
	if ( bUse10 != 0 )
	{
		bIsUse[count] = bUse10;
		count += 1;
	}

	//由于是多行两列，但每一列的数据是一起获取的，所以采用以下方式
	u32 b = 0;
	u32 CommonNum;			//卡侬麦克风的序号
	
	for ( int a = 0; a < 2*count; a++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextCOMMONItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{	
			if ( a == 2 )
			{
				b = 1;
			}
			if ( a == 2*b )
			{					
				CommonNum = bIsUse[b];
				if ( a != 0 )
				{
					b++;
				}				
			}
			if ( a%2 == 0 )
			{
				s8 chCOMMON[50] = {0};
				if ( 110 == CommonNum || 210 == CommonNum || 310 == CommonNum )
				{
					sprintf( chCOMMON, "卡侬麦克风10：" );
				}
				else
				{
					sprintf( chCOMMON, "卡侬麦克风%u：", CommonNum+1 );
				}			
				pTextItem->SetText( chCOMMON );
				pTextItem->SetFontColor(Color(15,79,81));
				pTextItem->SetAlignment(StringAlignmentNear);
			}					
			else
			{
				String strVoice = CommonToStr(CommonNum);
				if ( "未检测到信号" == strVoice )
				{
					pTextItem->SetFontColor(Color(224,34,34));
				}
				else
				{
					pTextItem->SetFontColor(Color(15,79,81));
				}
				pTextItem->SetText( strVoice );
				pTextItem->SetAlignment(StringAlignmentNear);
			}
		}
		IItemList *pNew = pList->AddItem( a, pItem, emGroup );  //添加 一个条目  
		delete pItem;
		pItem = 0;
	}
	return true;
}

String Value_ItemCOMMON::CommonToStr( int u )
{
	s8 chCOMMON[8] = {0};	
	String strNoSignal = "255";
	String strAudio = "";//音量	
	switch(u)
	{
	case 0:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 1:
			
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 2:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 3:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}	
		strAudio += chCOMMON;
		break;
	case 4:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 5:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 6:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 7:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 8:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 110:		//表明是来自第一组中的10
 			
 		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 210:		//表明是来自第二组中的10
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 310:		//表明是来自第三组中的10
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "未检测到信号";
			break;
		}	
		strAudio += chCOMMON;
		break;
	default:
		break;	
	}
	return strAudio;
}

bool Value_DisplaySrc::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nRow = 0;
	int nColSize = 3;
	
	for ( vector<TDisplaySrcData>::iterator iter = m_pVecListData->begin(); iter != m_pVecListData->end(); iter++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemVideoSource" );
		
		Data_DisplaySource dataDisplaySource( *iter );
		dataDisplaySource.SetDataKey( nRow );
		
		pItem->SetFunc("CCfgDemonStrationDlg::OnClickVideoSourceList");
		pItem->SetUserData( &dataDisplaySource );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		delete pItem;
		pItem = NULL;	
		
		for ( s32 nNum = 0; nNum < nColSize; nNum++ )
		{
			IBaseItem* pSubItem = CreatText(nNum);
			
			if ( NULL == pSubItem )
			{			
				return false;
			}
			
			CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem);
			if ( pTextItem !=NULL )
			{
				String strItem;
				switch(nNum)
				{
				case 0:
					{
						strItem = CommonToStr(iter->m_tDisplaySourceInfo.m_emVgaType);
						break;
					}
				case 1:
					{
						strItem = iter->m_tDisplaySourceInfo.m_achAlias;
						String strName = CommonToStr(iter->m_tDisplaySourceInfo.m_emVgaType);
						if ( strName == strItem )
						{
							strItem = "";
						}
						break;
					}
				case 2:
					{
						if ( iter->m_bDefault == true )
						{
							strItem = "默认";
						}
						else
						{
							strItem = "";
						}
						break;
					}
				default:
					break;
				}
				
				pTextItem->SetText( strItem );
				pNew->AddItem( nNum, pTextItem, emGroup );  //添加 一个条目
			}
			
			delete pSubItem;
			pSubItem = NULL;
		}
		nRow++;
	}
	return true;
}

String Value_DisplaySrc::CommonToStr( EmVgaType emVideoSourceType )
{
	String strAudioSource;
	switch( emVideoSourceType )
	{
	case emVgaTypeFullScreenCamera:
		strAudioSource = "全景摄像机"; 
		break;
	case emVgaType001:
		strAudioSource = "演示源 1"; 
		break;
	case emVgaType002:
		strAudioSource = "演示源 2"; 
		break;
	case emVgaType003:
		strAudioSource = "演示源 3"; 
		break;
	case emVgaTypeDocCamera:
		strAudioSource = "文档摄像机"; 
		break;
	default:
		strAudioSource = "";
		break;	
	}
	return strAudioSource;
}

IBaseItem *Value_DisplaySrc::CreatText( s32 nIndex )
{
	IBaseItem* pItem = NULL;

	switch( nIndex )
	{
	case 0:
		pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemVideoSourceName" );
		break;
	case 1:
		pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemVideoSource" );
		break;
	case 2:
		pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemStaus" );
		break;
	default:
		pItem = NULL;
		break;
	}
	return pItem;
}

bool Value_CurtainList::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecListData->size(); 
	int nRow = 0;
	int nColSize = 2;
	
	for ( vector<TCentreCurName>::iterator it = m_pVecListData->begin(); it != m_pVecListData->end(); it++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemOfSelect" );
		
		TCentreCurName tCurtainName;
		tCurtainName = *it;
		
		Data_CurName dataCurName(tCurtainName);
		dataCurName.SetDataKey( nRow );
		
		pItem->SetFunc("CCentCfgCurtainDlg::OnClickCurList");
		pItem->SetUserData( &dataCurName );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		delete pItem;
		pItem = 0;
		
		
		for ( int i = 0; i < nColSize; i++ )
		{
			IBaseItem *pSubItem = NULL;
			String strItem;

			if ( i == 0 )
			{
				char chTemp[10] = {0};
				_itot( nRow+1, chTemp, 10 );
				strItem = chTemp;

				pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemCurtainID" );
			}
			else if ( i == 1 )
			{
				strItem += tCurtainName.achCurName;

				pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemCurtainName" );
			}

			if ( pSubItem == NULL )
			{
				return false;
			}
			
			if ( NULL == pSubItem )
			{			
				return false;
			}
			
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
			{
				
				pTextItem->SetText( strItem );
				pNew->AddItem( i, pTextItem, emGroup );  //添加 一个条目
			}
			
			delete pSubItem;
			pSubItem = 0;
		}
		nRow++;
	}
	return true;
}

bool Value_ItemRouteCfg::SetData(IItemList* pList)
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecRouteCfgLst->size(); 
	int nRow = 0;
	int nColSize = 5;
	
	for ( vector<TRouteCfg>::iterator it = m_pVecRouteCfgLst->begin(); it != m_pVecRouteCfgLst->end(); it++ )
	{
		IBaseItem* pItem =  CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemRouteMng" );
		
		TRouteCfg tRouteCfg;
		tRouteCfg = *it;
		
		Data_RouteMng dataRouteMng(tRouteCfg);
		dataRouteMng.SetDataKey( nRow );
		
		pItem->SetFunc("CCfgAdvanceDlg::OnClickRouteMngLst");
		pItem->SetUserData( &dataRouteMng );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		delete pItem;
		pItem = 0;
			
		for ( int i = 0; i < nColSize; i++ )
		{
			IBaseItem* pSubItem = NULL;
			String strItem;
			switch(i)
			{
			case 0:
				{
					pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemRouteNoMng" );
					char chTemp[10] = {0};
					_itot( nRow+1, chTemp, 10 );
					strItem = chTemp;
					break;
				}
			case 1:
				{
					pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemRouteInfoMng" );
					in_addr tAddr;
					tAddr.S_un.S_addr = it->dwDstNet;
					strItem = inet_ntoa(tAddr);
					break;
				}
			case 2:
				{
					pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemRouteInfoMng" );
					in_addr tAddr;
					tAddr.S_un.S_addr = it->dwDstNetMask;
					strItem = inet_ntoa(tAddr);
					break;
				}
			case 3:
				{
					pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemRouteInfoMng" );
					in_addr tAddr;
					tAddr.S_un.S_addr = it->dwNextIP;
					strItem = inet_ntoa(tAddr);
					break;
				}
			case 4:
				{
					pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemRoutePriorMng" );
					char chTemp[10] = {0};
					_itot( (int)it->dwPri, chTemp, 10 );
					strItem = chTemp;
					break;
				}
			default:
				break;
			}
			
			if( NULL == pSubItem )
			{
				return false;
			}
			
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
			{
				pTextItem->SetText( strItem );
				pNew->AddItem( i, pTextItem, emGroup );  //添加 一个条目
			}
			
			delete pSubItem;
			pSubItem = 0;
		}
		nRow++;
	}

	return true;
}
