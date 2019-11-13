// touchlistdatproperty.cpp: implementation of the CTouchListDataProperty class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "touchlistdataproperty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const int CLayoutAlgorithm_BoardUpgrade::nXSpace = 0;
const int CLayoutAlgorithm_BoardUpgrade::nYSpace = 0;

bool Value_TouchListCommon::SetData( IItemList* pList )
{
	if ( pList == NULL ||  m_pTplArryUser == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	pBaseItem->SetMoveStatus(true);  
	
	Args_BuildItem arg;
	arg.pList = pList;
	arg.bDrag = FALSE;
	arg.strClickItemFunc = m_strClickItemFunc; 
	arg.pVctSubItem = m_pVctSubItem ;
	arg.strImageItem = "TempListItem";
	arg.strTxtItem = "TextItem";
	
	int count =  m_pTplArryUser->Size();
	vector<CUserFullInfo> vctList;
	for ( int i = 0; i < count; i++ )
	{
		vctList.push_back( m_pTplArryUser->GetAt(i) );
	}
	
	//sort( vctList.begin(), vctList.end(), CTransparentAddrList::UserItemCompare );
	
	for ( int k = 0; k< count; k++ )
	{
		CUserFullInfo user = vctList[k];
		Data_Common data(  user );
		
		String txt = user.GetName();  
		
		arg.strTxt = txt;
		arg.nKey = k; 
		arg.pUserData = &data;  
		BuildItem( arg );
	}
	
	return false;
}

bool Value_ViewListBoard::SetData( IItemList* pList )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strBoardView );
    pBaseItem->SetMoveStatus(true);

    for ( int i = 0; i < m_pVecBoardList->size(); i++ )
    {
        TTPBrdInfo tBoardInfo = m_pVecBoardList->at(i); 

		String strBrdType;

		EMBrdType emEqpType = tBoardInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType;
		switch( emEqpType )
		{
		case em_eapu_brd:
			{
				strBrdType = "APU2";
			}
			break;
		case em_mpc_brd:
			{
				strBrdType = "MPC2";
			}
			break;
		case em_mpu2ecard_brd:
			{
				strBrdType = "MPU2";				
			}
			break;
		case em_is22_brd:
			{
				strBrdType = "IS2.2";				
			}
			break;
		case em_cri2_brd:
			{
				strBrdType = "CRI2";				
			}
			break;
		default:   //em_unknow_brd
			{
				strBrdType = "UKW";				
			}
			break;
		}

		Data_BoardInfo boardInfo(tBoardInfo);
		boardInfo.SetDataKey( i );
    
		IBaseItem* pImageItem = NULL;
		if ( em_eapu_brd == tBoardInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType )
		{
			if ( tBoardInfo.m_abEqpReg[0] || tBoardInfo.m_abEqpReg[1] )   //在线 离线
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListNor" );
			}
			else
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListDis" );
			}
		}
		else if( em_unknow_brd != tBoardInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType )
		{
			if ( tBoardInfo.m_abEqpReg[0] )   //在线 离线
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListNor" );
			}
			else
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListDis" );
			}
		}
		else
		{
			pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListNull" );	
		}

		if ( pImageItem != NULL )
		{		     
			pImageItem->SetLayoutAlgorithm( IAlgorithm::strBoardItem  );    
			pImageItem->SetUserData( &boardInfo );
			pImageItem->SetFunc( m_strClickItemFunc );
		}
		
		IItemList *pNew = pList->AddItem( i, pImageItem, emGroup );

		SAFE_RELEASE(pImageItem);
    
		IBaseItem* pTextItemUp = CItemFactory::GetSingletonPtr()->CreateItem( "TextLstItem" );
		if ( pTextItemUp != NULL )
		{
			if ( CTextItem * pTextItemContent = dynamic_cast<CTextItem*>(pTextItemUp)  )
			{
				if ( NULL != pTextItemContent )
				{
					if( em_unknow_brd != tBoardInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType )
					{	
						strBrdType += "板";
						pTextItemContent->SetText( strBrdType ); 
					}
					else
					{
						pTextItemContent->SetText( "空" ); 
					}
					pNew->AddItem( 0, pTextItemContent, emGroup );
				}
			} 
			
			SAFE_RELEASE(pTextItemUp);
		}

		IBaseItem* pTextItemDown = CItemFactory::GetSingletonPtr()->CreateItem( "TextLstItem" );
		if ( pTextItemDown != NULL )
		{
			if ( CTextItem * pTextItemContent = dynamic_cast<CTextItem*>(pTextItemDown)  )
			{
				if( NULL != pTextItemContent )
				{
					String strExText;
					if ( i == 0 )
					{
						strExText = "[MC:0]";
					}
					else if ( i == 9 )
					{
						strExText = "[MC:1]";
					}
					else if ( i == 8 )
					{
						strExText = "[IS:7]";
					}
					else
					{
						if ( i < 8 )
						{
							s8 chPos[4];
							memset( chPos, 0, 4 );
							sprintf( chPos, "%d", i - 1 );
							strExText = "[EX:";
							strExText += chPos;
							strExText += "]";
						}
						else
						{
							s8 chPos[4];
							memset( chPos, 0, 4 );
							sprintf( chPos, "%d", i - 2 );
							strExText = "[EX:";
							strExText += chPos;
							strExText += "]";
						}

					}

					pTextItemContent->SetText( strExText ); 
					
					pNew->AddItem( 1, pTextItemContent, emGroup );
				}
			} 
			
			SAFE_RELEASE(pTextItemDown);
		}
    }

    return true;
}

bool Value_ViewListTvwBoard::SetData( IItemList* pList )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strBoardView );
    pBaseItem->SetMoveStatus(true);

    for ( int i = 0; i < m_pVecTvwBoardList->size(); i++ )
    {
        THduCfg tTvwBoardInfo = m_pVecTvwBoardList->at(i); 

		Data_TvwBoardInfo tvwboardInfo(tTvwBoardInfo);
		tvwboardInfo.SetDataKey( i );
    
		IBaseItem* pImageItem = NULL;
		if( 0 != tTvwBoardInfo.m_dwIP )
		{
			if ( tTvwBoardInfo.m_bBrdReg && tTvwBoardInfo.m_bServiceReg )   //在线 离线
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListNor" );
			}
			else
			{
				pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListDis" );
			}
		}
		else
		{
			pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardListNull" );	
		}

		if ( pImageItem != NULL )
		{		     
			pImageItem->SetLayoutAlgorithm( IAlgorithm::strBoardItem  );    
			pImageItem->SetUserData( &tvwboardInfo );
			pImageItem->SetFunc( m_strClickItemFunc );
		}
		
		IItemList *pNew = pList->AddItem( i, pImageItem, emGroup );

		SAFE_RELEASE(pImageItem);
    
		IBaseItem* pTextItemUp = CItemFactory::GetSingletonPtr()->CreateItem( "TextLstItem" );
		if ( pTextItemUp != NULL )
		{
			if ( CTextItem * pTextItemContent = dynamic_cast<CTextItem*>(pTextItemUp)  )
			{
				if ( NULL != pTextItemContent )
				{
					if( 0 != tTvwBoardInfo.m_dwIP )
					{	
						pTextItemContent->SetText( "HDU2板" ); 
					}
					else
					{
						pTextItemContent->SetText( "空" ); 
					}
					pNew->AddItem( 0, pTextItemContent, emGroup );
				}
			} 
			
			SAFE_RELEASE(pTextItemUp);
		}

		IBaseItem* pTextItemDown = CItemFactory::GetSingletonPtr()->CreateItem( "TextLstItem" );
		if ( pTextItemDown != NULL )
		{
			if ( CTextItem * pTextItemContent = dynamic_cast<CTextItem*>(pTextItemDown)  )
			{
				if( NULL != pTextItemContent )
				{
					String strExText;
					s8 chPos[4];
					memset( chPos, 0, 4 );
					sprintf( chPos, "%d", i );
					strExText = "[EX:";
					strExText += chPos;
					strExText += "]";


					pTextItemContent->SetText( strExText ); 
					
					pNew->AddItem( 1, pTextItemContent, emGroup );
				}
			} 
			
			SAFE_RELEASE(pTextItemDown);
		}
    }

    return true;
}

bool Value_ViewListTvwStyle::SetData( IItemList* pList )
{
    IBaseItem* pBaseItem = pList->GetItemData();
	m_tListRangeInfo.nFirstLeft = 0;
	m_tListRangeInfo.nFirstTop = 0;
	m_tListRangeInfo.nVertSpace = 4;
	m_tListRangeInfo.nHoriSpace = 2;
	Data_ListRangeInfo dataRangeInfo(m_tListRangeInfo);
	pBaseItem->SetUserData(&dataRangeInfo);

    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strMultiColumn );
    pBaseItem->SetMoveStatus(true);
	
	s32 nCount = m_pVecTvwStyleList->size();

    for ( s32 i = 0; i < nCount; i++ )
    {
        TTvwStyleInfo tTvwStyleInfo = m_pVecTvwStyleList->at(i); 

		tTvwStyleInfo.nKey = i;
		
		Data_TvwStyleInfo tvwStyleInfo(tTvwStyleInfo);
		tvwStyleInfo.SetDataKey( i );
		
		IBaseItem* pImageItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemTvwStyleList" );	
		
		if ( pImageItem != NULL )
		{		     
			pImageItem->SetLayoutAlgorithm( IAlgorithm::strHori  );    
			pImageItem->SetUserData( &tvwStyleInfo );
			pImageItem->SetFunc( m_strClickItemFunc );
		}
		
		IItemList *pNew = pList->AddItem( i, pImageItem, emGroup );
		
		SAFE_RELEASE(pImageItem);
		
		IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ExTextItem" );
		if ( pSubItem != NULL )
		{
			if ( CExTextItem* pTextItem = dynamic_cast<CExTextItem*>(pSubItem) )
			{
 				if ( HDU_MAX_CHANNEL_NUM == tTvwStyleInfo.tHduStyleUnit.m_byChanIndex )
 				{
					pTextItem->SetText( "" );
					pTextItem->SetSecondText( "" );
 				}
 				else
				{
					String strChanName = tTvwStyleInfo.tChanName.m_abyAlias;
					if( strChanName.empty())
					{
						continue;
					}


					pTextItem->SetText( strChanName );
					
					String strChanIndex;
					char chChanIndex[3];
					memset( chChanIndex, 0, 3 );
					itoa( tTvwStyleInfo.tHduStyleUnit.m_byChanIndex, chChanIndex, 10 );
					strChanIndex.append("[").append(chChanIndex).append("]");
					pTextItem->SetSecondText( strChanIndex );
				}

			}
			
			pNew->AddItem( 0, pSubItem, emGroup );
			delete pSubItem;
			pSubItem = NULL;
		}
    }
	
    return true;
}


bool Value_ItemMenu::SetData( IItemList* pList )
{ 	
	if ( pList == NULL || m_pMenuList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm(  m_strAlgroithm ); 
	pBaseItem->SetMoveStatus( m_bDrag );
	
	//sort( m_pMenuList->begin(), m_pMenuList->end(), CompareListData ); //排序

	Args_BuildItem args;
	args.pList = pList;
	args.bDrag = m_bDrag;
	args.strClickItemFunc = m_strClickItemFunc;
	args.pVctSubItem =  NULL;
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
		tTPNMServerCfg.dwNMServerIP = ntohl(tTPNMServerCfg.dwNMServerIP);
		
		Data_NetMng dataNetMng(tTPNMServerCfg);
		dataNetMng.SetDataKey( nRow );

		pItem->SetFunc("CNetMngCfgLogic::OnClickNetMngLst");
		pItem->SetUserData( &dataNetMng );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );

		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		SAFE_RELEASE(pItem);


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
						tAddr.S_un.S_addr = tTPNMServerCfg.dwNMServerIP;
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

			SAFE_RELEASE( pSubItem );
		}
		nRow++;
	}
	return true;
}

bool Value_ItemBoardUpgrade::SetData( IItemList* pList )
{
	if ( NULL == pList )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecUmsToolFileLst->size(); 
	int nItemRow = 0;
	int nColSize = 2;
	
	for ( std::vector<TUmsToolFile>::iterator it = m_pVecUmsToolFileLst->begin(); it != m_pVecUmsToolFileLst->end(); it++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemBoardUpgrade" );
		
		TUmsToolFile tUmsToolFile;
		tUmsToolFile = *it;
		
		Data_BoardUpgrade dataBoardUpgrade(tUmsToolFile);
		dataBoardUpgrade.SetDataKey( nItemRow );
		
		pItem->SetFunc("CImpCommonDlgLogic::OnBoardUpgradeLstClick");
		pItem->SetUserData( &dataBoardUpgrade );
		pItem->SetDragStatus(true);
		pItem->SetLayoutAlgorithm( IAlgorithm::strBoardUpgradItem );
		
		IItemList *pNew = pList->AddItem( nItemRow, pItem, emGroup );
		SAFE_RELEASE(pItem);
		
		for ( s32 nRow = 0; nRow < nColSize; nRow++ )
		{
			IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemBoardUpgrade" );
			if ( NULL == pSubItem )
			{			
				return false;
			}
			
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
			{
				String strItem;
				switch(nRow)
				{
				case 0:
					{
						strItem = tUmsToolFile.chFileName;		
					}
					break;
				case 1:
					{
						s64 nSize = tUmsToolFile.nFileSize;
						s8 chData[20];
						memset( chData, 0, 20 );
						if ( 1024 > nSize )
						{
							sprintf( chData, "%u", nSize );
							strItem = chData;
							strItem += "byte";
						}
						else if ( 1024 < nSize && nSize < 1024*1024 )
						{
							float fSize = 1.0 * nSize / 1024;
							sprintf( chData, "%.1f", fSize );
							strItem = chData;
							strItem += "Kb";
						}
						else if ( 1024*1024 < nSize )
						{
							float fSize = 1.0 * nSize / (1024*1024);
							sprintf( chData, "%.1f", fSize );
							strItem = chData;
							strItem += "M";
						}
					}
					break;
				default:
					{
					}
					break;
				}
				
				pTextItem->SetText( strItem );
				pNew->AddItem( nRow, pTextItem, emGroup );  //添加 一个条目
			}
			
			SAFE_RELEASE( pSubItem );
		}
		nItemRow++;
	}
	return true;
}

bool Value_ItemVTR::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecVcrCfgLst->size(); 
	int nRow = 0;
	int nColSize = 3;
	
	for ( vector<TVcrCfg>::iterator it = m_pVecVcrCfgLst->begin(); it != m_pVecVcrCfgLst->end(); it++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemVTR" );
		
		TVcrCfg tVcrCfg;
		tVcrCfg = *it;
		
		Data_VTR dataVTR(tVcrCfg);
		dataVTR.SetDataKey( nRow );
		
		pItem->SetFunc("CVTRCfgLogic::OnClickVTRLst");
		pItem->SetUserData( &dataVTR );
		pItem->SetLayoutAlgorithm( IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		SAFE_RELEASE(pItem);
		
		
		for ( int i = 0; i < nColSize; i++ )
		{
			IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemVTR" );
			
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
						strItem = tVcrCfg.m_achName;
						break;
					}
				case 1:
					{
						char chTemp[4] = {0};
						_itot( tVcrCfg.m_byEqpID, chTemp, 10 );
						strItem = chTemp;
						break;
					}
				case 2:
					{
						in_addr tAddr;
						tAddr.S_un.S_addr = tVcrCfg.m_dwIP;
						strItem = inet_ntoa(tAddr);
						break;
					}
				default:
					break;
				}
				
				pTextItem->SetText( strItem );
				pNew->AddItem( i, pTextItem, emGroup );  //添加 一个条目
			}
			
			SAFE_RELEASE( pSubItem );
		}
		nRow++;
	}
	return true;
}

bool CLayoutAlgorithm_BoardUpgrade::Transition( IArgs* pArgs )
{
	Args_ItemList* p = 0;
	if ( p = dynamic_cast<Args_ItemList*>(pArgs) )
	{
		IItemList* pList = p->m_pList;
		if ( pList == 0 )
		{
			return false;
		}
		int nItemCounts = pList->GetItemCount();
		IBaseItem* pItem = pList->GetItemData();
		if ( pItem == 0 )
		{
			return false;
		}
		int nParentHeight = pItem->GetItemHeight();	 
		CRect rcLast( 0, 0, 0, 0 );
		for ( int i = 0; i < nItemCounts; i++ )
		{
			IItemList* pSubList = pList->GetItemByIndex( i );
			if ( pSubList == 0 )
			{
				continue;
			}
			IBaseItem* pItem = pSubList->GetItemData();
			if ( pItem == 0 )
			{
				continue;
			}
			CRect rc = pItem->GetItemRect();
			int nWidht = pItem->GetItemWidth();
			
			rcLast.SetRect( rcLast.right + nXSpace + 20, nYSpace, rcLast.right + nXSpace + rc.Width(), nParentHeight - nYSpace );	
			pItem->SetItemRect( rcLast );
		}
	}
	return false;
}