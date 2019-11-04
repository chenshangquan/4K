#include "stdafx.h"

CDuiexlibInterface::CDuiexlibInterface()
{

}

CDuiexlibInterface::~CDuiexlibInterface()
{

}

bool CDuiexlibInterface::UpdateList( const tString& strWndName, std::vector<IData*>& vecData, CPaintManagerUI& pm )
{
	CCommonListUI* pList = static_cast<CCommonListUI*>( pm.FindControl( strWndName.c_str() ) );
	if ( NULL != pList )
	{
		if ( 0 == vecData.size() )
		{
			pList->SetManagerUI(&pm);
			pList->UpdateList(vecData);
			return true;
		}

		IData* pData = vecData[0];
		if ( L"Data_ProgressInfo" == pData->GetType() )
		{
			for( size_t nIndex = 0; nIndex < vecData.size(); nIndex++ )
			{
				pData = vecData[nIndex];
				if ( NULL == pData )
				{
					continue;
				}

				const Data_ProgressInfo* pItemData = dynamic_cast<const Data_ProgressInfo*>( pData );
				Data_ProgressInfo* pProgressData = const_cast<Data_ProgressInfo*>(pItemData);
				if ( NULL != pProgressData )
				{
					CListContainerElementUI* pElem = static_cast<CListContainerElementUI*>( pList->GetItemAt( pProgressData->m_tData.nIndex ) );
					if ( NULL != pElem )
					{
						CProgressUI* pPro = static_cast<CProgressUI*>( pm.FindSubControlByName( pElem, pList->GetProgressName().c_str() ) );
						if ( NULL !=  pPro )
						{
							pPro->SetValue( pProgressData->m_tData.nValue );
						}
					}
				}
			}
		}
		else
		{
			pList->SetManagerUI(&pm);
			pList->UpdateList(vecData);
		}
	}

	return true;
}

bool CDuiexlibInterface::UpdateList( const tString& strWndName, CStdDataArray<IData*>& vecData, CPaintManagerUI& pm )
{
	CCommonListUI* pList = static_cast<CCommonListUI*>( pm.FindControl( strWndName.c_str() ) );
	if ( NULL != pList )
	{
		if ( 0 == vecData.GetSize() )
		{
			pList->SetManagerUI(&pm);
			pList->UpdateList(vecData);
			return true;
		}

		IData* pData = vecData[0];
		if ( L"Data_ProgressInfo" == pData->GetType() )
		{
			for( size_t nIndex = 0; nIndex < vecData.GetSize(); nIndex++ )
			{
				pData = vecData[nIndex];
				if ( NULL == pData )
				{
					continue;
				}

				const Data_ProgressInfo* pItemData = dynamic_cast<const Data_ProgressInfo*>( pData );
				Data_ProgressInfo* pProgressData = const_cast<Data_ProgressInfo*>(pItemData);
				if ( NULL != pProgressData )
				{
					CListContainerElementUI* pElem = static_cast<CListContainerElementUI*>( pList->GetItemAt( pProgressData->m_tData.nIndex ) );
					if ( NULL != pElem )
					{
						CProgressUI* pPro = static_cast<CProgressUI*>( pm.FindSubControlByName( pElem, pList->GetProgressName().c_str() ) );
						if ( NULL !=  pPro )
						{
							pPro->SetValue( pProgressData->m_tData.nValue );
						}
					}
				}
			}
		}
		else
		{
			pList->SetManagerUI(&pm);
			pList->UpdateList(vecData);
		}
	}

	return true;
}

int CDuiexlibInterface::GetListIndex( const tString& strWndName, CControlUI* pElement, CPaintManagerUI& pm )
{
	CCommonListUI* pList = static_cast<CCommonListUI*>( pm.FindControl( strWndName.c_str() ) );
	if ( NULL != pList )
	{
		return pList->GetItemIndex(pElement);
	}

	return -1;
}

bool CDuiexlibInterface::ShowWindow( const tString& strWndName, bool bShow )
{

	return true;
}

CDUIDialog* CDuiexlibInterface::GetDUIDialogPtr(const tString& strDlgName)
{
	return (CDUIDialog *)(CDlgManager::GetSingletonPtr()->FindDlgByName(strDlgName.c_str()));
}

CPaintManagerUI& CDuiexlibInterface::GetPaintMngUI(const tString& strDlgName)
{
	return *(CPaintManagerUI *)(CDlgManager::GetSingletonPtr()->FindDlgByName(strDlgName.c_str())->GetPaintMng());
}

void CDuiexlibInterface::GetCheckStateByName(const tString& strListName, const CPaintManagerUI& pm, CStdDataList<bool>** mapCheckState)
{
	CCommonListUI* pList = static_cast<CCommonListUI*>( pm.FindControl(strListName.c_str()) );
	if ( NULL != pList )
	{
		pList->GetCheckStateMap(mapCheckState);
	}
}