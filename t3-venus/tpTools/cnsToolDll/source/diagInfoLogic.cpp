// diagInfoLogic.cpp: implementation of the CDiagInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "diagInfoLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagInfoLogic::CDiagInfoLogic()
: m_strLostPacket("StcLostPacket")
, m_strUpstream("StcUpstream")
, m_strDownstream("StcDownstream")
, m_strComboboxInPort("ComboboxInPort")
, m_strComboboxOutPort("ComboboxOutPort")
, m_strInAdPort1("StcInAdPort1")
, m_strInAdPort2("StcInAdPort2")
, m_strInAdPort3("StcInAdPort3")
, m_bIsRecording(FALSE)
{

}

CDiagInfoLogic::~CDiagInfoLogic()
{

}

void CDiagInfoLogic::RegMsg()
{
	CDiagInfoLogic *pThis =  GetSingletonPtr(); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_UpDownstream_NTY, CDiagInfoLogic::OnUpDownstreamNty, pThis, CDiagInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_LostPacket_Rsp, CDiagInfoLogic::OnLostPacketRsp, pThis, CDiagInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AudPort_NTY, CDiagInfoLogic::OnUpdateAudioNty, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDiagInfoLogic::OnVgaInfoNotify, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNS_VGAINFO_NOTIFY, CDiagInfoLogic::OnVgaOutInfoNotify, pThis, CDiagInfoLogic ); 	
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_CONF_NTY, CDiagInfoLogic::OnConfStateNty, pThis, CDiagInfoLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftAudPort_NTY, CDiagInfoLogic::OnDefaultAudioNty, pThis, CDiagInfoLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_StartRecorder_Nty, CDiagInfoLogic::OnRecordMes, pThis, CDiagInfoLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_VideoSource_NTY, CDiagInfoLogic::OnUpdateMainAudioNty, pThis, CDiagInfoLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DefAudio_NTY, CDiagInfoLogic::OnUpdateMainAudioNty, pThis, CDiagInfoLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_VideoSource_NTY, CDiagInfoLogic::OnUpdateMainAudioInfo, pThis, CDiagInfoLogic );
}

void CDiagInfoLogic::UnRegMsg()
{
	
}

void CDiagInfoLogic::RegCBFun()
{
	CDiagInfoLogic *pThis =  GetSingletonPtr();	
    REG_GOBAL_MEMBER_FUNC( "CDiagInfoLogic::InitWnd", CDiagInfoLogic::InitWnd, pThis, CDiagInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "CDiagInfoLogic::OnBtnDiagTest", CDiagInfoLogic::OnBtnDiagTest, pThis, CDiagInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "CDiagInfoLogic::OnBtnStatistic", CDiagInfoLogic::OnBtnStatistic, pThis, CDiagInfoLogic );
}

void CDiagInfoLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CDiagInfoLogic::InitWnd" );	
}

bool CDiagInfoLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
	UIFACTORYMGR_PTR->LoadScheme( "SchExportPacket", m_pWndTree);
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagStatistic, false );	
	return true;
}

void CDiagInfoLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		m_bIsRecording = FALSE;
        m_tDualSrcInfo.Clear();
		memset( &m_tVgaMixInfo, 0, sizeof(m_tVgaMixInfo) );
		UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme( "SchExportPacket", m_pWndTree);
	}
}

LRESULT CDiagInfoLogic::OnUpDownstreamNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	TTPUpDownSpeedInfo tUpDownSpeedInfo;
	LIBDATAMGRPTR->GetUpDownstreamRate( tUpDownSpeedInfo );
	//上行速率
	s8 chUp[8] = {0};
	String strUpstream;
	if ( 1024 < tUpDownSpeedInfo.m_wUpSpeed )
	{
		float fUpSpeed = 1.0*tUpDownSpeedInfo.m_wUpSpeed/1024;
		sprintf( chUp, "%.1f", fUpSpeed );
		strUpstream = chUp;
		strUpstream += "Mpbs";
	}
	else
	{
		sprintf( chUp, "%u", tUpDownSpeedInfo.m_wUpSpeed );
		strUpstream = chUp;
		strUpstream += "Kpbs";
	}
 	UIFACTORYMGR_PTR->SetCaption(m_strUpstream, strUpstream, m_pWndTree, true);
	//下行速率
	s8 chDown[8] = {0};
	String strDownstream;
	if ( 1024 < tUpDownSpeedInfo.m_wDownSpeed )
	{
		float fDownSpeed = 1.0*tUpDownSpeedInfo.m_wDownSpeed/1024;
		sprintf( chDown, "%.1f", fDownSpeed );
		strDownstream = chDown;
		strDownstream += "Mpbs";
	}
	else
	{
		sprintf( chDown, "%u", tUpDownSpeedInfo.m_wDownSpeed );
		strDownstream = chDown;
		strDownstream += "Kpbs";
	}
	UIFACTORYMGR_PTR->SetCaption(m_strDownstream, strDownstream, m_pWndTree, true);

	if ( m_bIsRecording == TRUE )
	{
		if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
		{
			return S_FALSE;
		}
		else
		{
			WriteToFile();
		}
	}

	return S_OK;
}

bool CDiagInfoLogic::OnBtnDiagTest( const IArgs & arg )
{
// 	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
// 	if ( bInConf )
// 	{		
// 		MSG_BOX_OK( "会议中，禁止使用" );	
// 		return true;
// 	}	
	//获取演示源输入接口的vga类型
	String strInPort;
	EmVgaType emDualInput;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxInPort, strInPort, m_pWndTree );
	if ( strInPort.empty() )
	{
		emDualInput = emVgaTypeInValid;
		//MSGBOX_OK("演示源输入接口未选择!");
		//UIFACTORYMGR_PTR->SetFocus( m_strComboboxInPort );
		//return false;
	}
	else
	{
		vector<TVgaInfo>::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
		while( it != m_tDualSrcInfo.vctVgaInfo.end() )
		{   
			if ( StrCmp( strInPort.c_str(), it->m_achAlias ) == 0 )
			{
				emDualInput = it->m_emVgaType;
			}		
			it++;
		}
	}

	//获取演示源输出接口的vga类型
	String strOutPort;
	EmDualOutputType emDualOutput;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxOutPort, strOutPort, m_pWndTree );
	if ( strOutPort.empty() )
	{
		emDualOutput = emDualOutputInvalid;
		//MSGBOX_OK("演示源输出接口未选择!");
		//UIFACTORYMGR_PTR->SetFocus( m_strComboboxOutPort );
		//return false;
	}
	else
	{
		if ( StrCmp( strOutPort.c_str(), m_tVgaMixInfo.m_achVgaOutputFstName ) == 0 )
		{	
			emDualOutput = emDualOutput001;
		}
		else
		{
			emDualOutput = emDualOutput002;
		}
	}
	TTPVgaMixInfo tVgaMixInfo;
	tVgaMixInfo.m_emCurrentType = emDualInput;
	tVgaMixInfo.m_emDualOutputType = emDualOutput;
	COMIFMGRPTR->SelAVMatrixCmd(tVgaMixInfo);

	CMsgDispatch::SendMessage( UI_CNSTOOL_RefInportTitle_Nty, NULL,NULL);
	UIFACTORYMGR_PTR->Domodal( g_strDiagTestFrame );

	return true;
}

bool CDiagInfoLogic::OnBtnStatistic( const IArgs & arg )
{
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_Statistic_Nty, (WPARAM)&m_bIsRecording,NULL);

	if ( m_bIsRecording == TRUE )
	{
		m_bIsRecording = FALSE;
		UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
	}
	
	UIFACTORYMGR_PTR->Domodal( g_strDiagStatistic );
	return true;
}

LRESULT CDiagInfoLogic::OnLostPacketRsp( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	CString LostPacketInfo;
	LIBDATAMGRPTR->GetLostPacketInfo( LostPacketInfo );

	//s8 chLostPacket[8] ={0};
	//sprintf( chLostPacket, "%u", LostPacketInfo );
	String strLostInfo = LostPacketInfo;
	strLostInfo += "%";
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, strLostInfo, m_pWndTree, true);
	}
	else
	{
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

LRESULT CDiagInfoLogic::OnUpdateAudioNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	TTpAudioPortInfo* pAudioPortInfo = NULL;
	LIBDATAMGRPTR->GetAudioPortInfo( &pAudioPortInfo );
	TTpAudioPortInfo atAudioPortInfo[3];
	for ( int i = 0; i < 3; i++ )
    {
        TTpAudioPortInfo tAudioPortInfo = *( pAudioPortInfo + i );
        atAudioPortInfo[i] = tAudioPortInfo;
    }

	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, "", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, "", m_pWndTree );

	String strGroup1 = UpdateGroup1( atAudioPortInfo[0] );
	String strGroup2 = UpdateGroup2( atAudioPortInfo[1] );
	String strGroup3 = UpdateGroup3( atAudioPortInfo[2] );

	if ( !strGroup1.empty() )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup1, m_pWndTree );
		if ( !strGroup2.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup2, m_pWndTree );
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, strGroup3, m_pWndTree );
			} 
		} 
		else
		{
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup3, m_pWndTree );
			} 
		}
	}
	else
	{
		if ( !strGroup2.empty() )
		{
			UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup2, m_pWndTree );
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strGroup3, m_pWndTree );
			} 
		} 
		else
		{
			if ( !strGroup3.empty() )
			{
				UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strGroup3, m_pWndTree );
			} 
		}
	}
	
	return S_OK;
}
/*---------------------------------------------------------------------
* 函数名称：UpdateGroup1
* 功    能：更新音频设置界面的Group1
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo )
{	
	String strInAdPort1 = "";
	if (tAudioPortInfo.m_byGroupIndex == 0)
	{		
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort1 += "卡侬麦克风1";
					break;
				case 1:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "卡侬麦克风2";
					}
					else
					{
						strInAdPort1 += ",卡侬麦克风2";
					}
					break;
				case 2:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "卡侬麦克风3";
					} 
					else
					{
						strInAdPort1 += ",卡侬麦克风3";
					}	
					break;
				case 3:
					if ( strInAdPort1.empty() )
					{
						strInAdPort1 += "卡侬麦克风10";
					} 
					else
					{
						strInAdPort1 += ",卡侬麦克风10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, strInAdPort1, m_pWndTree );
	} 
	return strInAdPort1;
}
/*---------------------------------------------------------------------
* 函数名称：UpdateGroup2
* 功    能：更新音频设置界面的Group2
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo )
{
	String strInAdPort2 = "";
	if (tAudioPortInfo.m_byGroupIndex == 1)
	{	
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort2 += "卡侬麦克风4";
					break;
				case 1:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "卡侬麦克风5";
					}
					else
					{
						strInAdPort2 += ",卡侬麦克风5";
					}
					break;
				case 2:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "卡侬麦克风6";
					}
					else
					{
						strInAdPort2 += ",卡侬麦克风6";
					}
					break;
				case 3:
					if ( strInAdPort2.empty() )
					{
						strInAdPort2 += "卡侬麦克风10";
					}
					else
					{
						strInAdPort2 += ",卡侬麦克风10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, strInAdPort2, m_pWndTree );
	} 
	return strInAdPort2;
}
/*---------------------------------------------------------------------
* 函数名称：UpdateGroup3
* 功    能：更新音频设置界面的Group3
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
String CDiagInfoLogic::UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo )
{
	String strInAdPort3 = "";
	if (tAudioPortInfo.m_byGroupIndex == 2)
	{	
		for( int i = 0; i <4; i++ )
		{
			if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
			{
				switch( i )
				{
				case 0:
					strInAdPort3 += "卡侬麦克风7";
					break;
				case 1:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "卡侬麦克风8";
					}
					else
					{
						strInAdPort3 += ",卡侬麦克风8";
					}
					break;
				case 2:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "卡侬麦克风9";
					}
					else
					{
						strInAdPort3 += ",卡侬麦克风9";
					}
					break;
				case 3:
					if ( strInAdPort3.empty() )
					{
						strInAdPort3 += "卡侬麦克风10";
					}
					else
					{
						strInAdPort3 += ",卡侬麦克风10";
					}
					break;
				default:
					break;
				}
			}
		}
		//UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, strInAdPort3, m_pWndTree );
	} 
	return strInAdPort3;
}

LRESULT CDiagInfoLogic::OnVgaInfoNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetDualSrcInfo( m_tDualSrcInfo );

	std::vector<CString> vecMdlTypeData;
//	vecMdlTypeData.push_back("");	
	String strComInPort;
	if ( emVgaTypeInValid == m_tDualSrcInfo.emCurrentType )
	{
		m_tDualSrcInfo.emCurrentType = m_tDualSrcInfo.emDefaultType;
	}
	vector<TVgaInfo>::iterator it =  m_tDualSrcInfo.vctVgaInfo.begin() ;
	while( it != m_tDualSrcInfo.vctVgaInfo.end() )
	{   
		if ( m_tDualSrcInfo.emCurrentType == it->m_emVgaType)
		{
			strComInPort = it->m_achAlias;
		}
		vecMdlTypeData.push_back(it->m_achAlias);		
		it++;
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxInPort, vecMdlTypeData, m_pWndTree );  
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxInPort, strComInPort, m_pWndTree );
	return S_OK;
}

LRESULT CDiagInfoLogic::OnVgaOutInfoNotify( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	LIBDATAMGRPTR->GetVgaMixInfo(m_tVgaMixInfo);

	String strComOutPort;
	switch(m_tVgaMixInfo.m_emDualOutputType)
	{	
	case emDualOutput001:
		strComOutPort = m_tVgaMixInfo.m_achVgaOutputFstName;
		break;
	case emDualOutput002:
		strComOutPort = m_tVgaMixInfo.m_achVgaOutputSndName;
		break;
	default:
		strComOutPort = "";
		break;
	}

	std::vector<CString> vecMdlTypeData;
//	vecMdlTypeData.push_back("");
	vecMdlTypeData.push_back(m_tVgaMixInfo.m_achVgaOutputFstName);
	vecMdlTypeData.push_back(m_tVgaMixInfo.m_achVgaOutputSndName);
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxOutPort, vecMdlTypeData, m_pWndTree ); 
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxOutPort, strComOutPort, m_pWndTree );

	return S_OK;
}

LRESULT CDiagInfoLogic::OnConfStateNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bInConf = LIBDATAMGRPTR->IsInConf();
	if ( bInConf )
	{
		if ( UIFACTORYMGR_PTR->IsVisible( g_strDiagTestFrame ) )
		{
			//停止测试请求
			COMIFMGRPTR->StopAVMatrixReq();

			s32 nResult = 0;
			UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
		}
		UIFACTORYMGR_PTR->EnableWindow( "BtnDiagPort", false, m_pWndTree );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxInPort, m_pWndTree ); 
		((CTransparentComboBox*)pWnd)->SetEnableWindow(FALSE);
		CWnd* pWndShow = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxOutPort, m_pWndTree ); 
		((CTransparentComboBox*)pWndShow)->SetEnableWindow(FALSE);
	} 
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( "BtnDiagPort", true, m_pWndTree );
		CWnd* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxInPort, m_pWndTree ); 
		((CTransparentComboBox*)pWnd)->SetEnableWindow(TRUE);
		CWnd* pWndShow = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxOutPort, m_pWndTree ); 
		((CTransparentComboBox*)pWndShow)->SetEnableWindow(TRUE);
		//没有会议的时候,丢包率显示---  石文娟确认
		UIFACTORYMGR_PTR->SetCaption(m_strLostPacket, "---", m_pWndTree, true);
	}
	return S_OK;
}

HRESULT CDiagInfoLogic::OnDefaultAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( bSuccess )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort1, "卡侬麦克风1", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort2, "卡侬麦克风4", m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strInAdPort3, "卡侬麦克风7", m_pWndTree );
	}
	return S_OK;
}

HRESULT CDiagInfoLogic::OnUpdateMainAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		return S_FALSE;
	}
	TTPVideoInfoTool tMainAudioInfo;

	string strInport = "";
	LIBDATAMGRPTR->GetMainAudioInfo( &tMainAudioInfo );

	for ( s32 nIndex = 0 ; nIndex < (emEndMPCodec-1) ; nIndex ++ )
	{
		for( s32 nNum = 0; nNum <( emTPC7Vid+1 ) ; nNum ++ )
		{
			if ( tMainAudioInfo.m_aemBigVideoSource[nIndex] == tMainAudioInfo.m_atVideoSourceName[nNum].m_emPortType )
			{
				strInport+= tMainAudioInfo.m_atVideoSourceName[nNum].m_achSourceName;
				break;
			}
		}
		if ( nIndex != (emEndMPCodec-2 ))
		{
			strInport+= ",";
		}
	}
	UIFACTORYMGR_PTR->SetCaption("DiagInfoDlg/StcInPort",strInport,m_pWndTree);
	return S_OK;
}

HRESULT CDiagInfoLogic::OnRecordMes( WPARAM wparam, LPARAM lparam )
{
	memcpy(&m_cFile,(CFile *)wparam,sizeof(m_cFile));
	
	if ( m_cFile.m_hFile == (UINT)INVALID_HANDLE_VALUE )
	{
		return S_FALSE;
	}

	m_bIsRecording	= TRUE;
	UIFACTORYMGR_PTR->LoadScheme( "SchEndOfStatistics", m_pWndTree );
	return S_OK;
}

void CDiagInfoLogic::WriteToFile()
{
	String  strLostInfo;
	String	strUpSpeed;
	String	strDownSpeed;

	UIFACTORYMGR_PTR->GetCaption(m_strLostPacket, strLostInfo, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption(m_strUpstream, strUpSpeed, m_pWndTree);
	UIFACTORYMGR_PTR->GetCaption(m_strDownstream, strDownSpeed, m_pWndTree);

	if ( m_cFile.m_hFile != (UINT)INVALID_HANDLE_VALUE )
	{
		String strRecord;

		SYSTEMTIME st;
		GetLocalTime(&st);  
		CString time = "";
		time.Format("%4d/%.2d/%.2d %.2d:%.2d:%.2d\n",
			st.wYear, st.wMonth,  st.wDay,
			     st.wHour, st.wMinute, st.wSecond);

		strRecord	+=time;
		strRecord	+=" 丢包率："+ strLostInfo;
		strRecord	+=" 上传速率："+ strUpSpeed;
		strRecord	+=" 下载速率："+ strDownSpeed;
		strRecord	+="\r\n";
		m_cFile.Write( strRecord.c_str(), strRecord.size() );
	}
}
HRESULT CDiagInfoLogic::OnUpdateMainAudioInfo( WPARAM wparam, LPARAM lparam )
{
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_strDiagTestFrame );
	if ( bIsVisible )
	{
		CMsgDispatch::SendMessage( UI_CNSTOOL_RefInportTitle_Nty, NULL,NULL);
	}
	return S_OK;
}
