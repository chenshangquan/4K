/*=============================================================================
模   块   名: 网管公用模块库
文   件   名: logmanage.cpp
相 关  文 件: logmanage.h
文件实现功能: 日志管理类
作        者: 刘瑞飞
版        本: V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
说        明: 需要MFC支持
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2005/04/07  3.6     刘瑞飞      创建
2005/12/08  4.0     王昊        分离出单独文件
=============================================================================*/

#include "stdafx.h"
#include "nmscommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//
//      日志管理类
//


/*=============================================================================
函 数 名:CLogManage
功    能:构造函数
参    数:CLogItem *pcLog                    [in]    日志记录的信息
         LPCTSTR lptrFilePath               [in]    日志文件的全路径，包括最后的文件名
         u32 dwBufferSize                   [in]    读取日志文件时候的缓冲区的大小
         u32 dwLogMaxNum                    [in]    文件里面最大的日志数目
         u32 dwMallocStep                   [in]    动态增长的步长
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
CLogManage::CLogManage(CLogItem *pcLog, LPCTSTR lptrFilePath,
                       u32 dwBufferSize /* = MAX_LOG_BUF_SIZE */,
		               u32 dwLogMaxNum /* = MAX_LOG_NUM */,
                       u32 dwMallocStep /* = DEFAULT_LOG_STEP */)
        : m_dwLogMaxSize(dwLogMaxNum), m_dwCount(0),
          m_dwMallocStep(dwMallocStep), m_dwMallocNum(0), m_dwNewAddCount(0),
          m_dwUsedCount(0), m_dwSn(0), m_dwBufferSize(dwBufferSize),
          m_nSummaryLen(0), m_nDetailLen(0), m_nLogLen(0), m_pchBuffer(NULL),
          m_pchSummaryData(NULL), m_pchData(NULL)
{
    ASSERT(pcLog != NULL);
    ASSERT(lptrFilePath != NULL);
    ASSERT(dwBufferSize > 0);
    ASSERT(dwLogMaxNum >  0);
    ASSERT(dwMallocStep > 0);

    if (pcLog == NULL)
    {
	    return;
    }

    m_pchBuffer = new s8 [dwBufferSize];
    ZeroMemory(m_pchBuffer, dwBufferSize);

    SetLogFilePath( lptrFilePath );
    GetSummaryLen( pcLog );
    GetDetailLen( pcLog );
    GetLogLen();

    m_csPathName = GetLogFilePath();

    m_pchData = new s8 [m_nLogLen * WRITE_NUM];
    ZeroMemory(m_pchData, m_nLogLen * WRITE_NUM);

    ReadLog();
}

/*=============================================================================
函 数 名:~CLogManage
功    能:析构函数
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
CLogManage::~CLogManage()
{
    WriteLog();

    DEL_PTR_ARRAY(m_pchData);
    DEL_PTR_ARRAY(m_pchSummaryData);
    DEL_PTR_ARRAY(m_pchBuffer) ;
}

/*=============================================================================
函 数 名:AddLog
功    能:把新增加的日志写入内存，当内存中的日志达到一定的数目时候，写入日志文件里
参    数:CLogItem *pcLog                    [in]    增加的日志记录
         void *pcbData                      [in]    调用IsAdd时的输入参数
注    意:会调用CLogItem的IsAdd判断是否需要写入内存
返 回 值:日志记录的流水号
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
2005/05/23  3.6     王昊    写入m_pchSummaryData查位置应该用m_dwSn来定位
=============================================================================*/
u32 CLogManage::AddLog(CLogItem *pcLog, void *pcbData /* = NULL */)
{
	ASSERT(pcLog != NULL);

	if ( pcLog == NULL || ! pcLog->IsAdd( pcbData ) )
	{
		return 0;
	}

	LPCTSTR lpszSummary = pcLog->GetSummary();
	LPCTSTR lpszDetail = pcLog->GetDetail();

	//如果日志简单信息为空不记录
	if ( NULL == lpszSummary )
	{
		return 0;
	}

	m_dwCount++;
    m_dwUsedCount++;
	m_dwSn++;
	m_dwNewAddCount++;
	time( &m_tOccurTime );

	//把新增加的日志写道内存里面
	if ( m_dwCount > m_dwLogMaxSize )
	{
		s8 *pchStartPos = m_pchSummaryData + ((m_dwSn - 1) % 
			m_dwLogMaxSize) * (sizeof(u32) + sizeof(time_t) + m_nSummaryLen);
		ZeroMemory(pchStartPos, sizeof(u32) + sizeof(time_t) + m_nSummaryLen);
		memcpy( pchStartPos, &m_dwSn,sizeof (u32) );
		memcpy( pchStartPos + sizeof (u32), &m_tOccurTime, sizeof (time_t) );
		memcpy( pchStartPos + sizeof (u32) + sizeof (time_t), lpszSummary,
			    _tcslen( lpszSummary ) );
	}
	else
	{
		if ( m_dwMallocNum == 0 )
		{
			s8 *pchOldData = m_pchSummaryData;
			m_pchSummaryData = NULL;
			MallocBuffer();
			memcpy( m_pchSummaryData, pchOldData, (m_dwCount- 1) * 
				        (sizeof(time_t) + sizeof(u32) + m_nSummaryLen) );
			m_dwMallocNum = m_dwMallocStep;
			DEL_PTR_ARRAY (pchOldData);
		}
		m_dwMallocNum--;
        //  wanghao 2005/05/23  用m_dwSn来定位
		s8 *pchStartPos = m_pchSummaryData + (m_dwSn - 1)
			* (sizeof (time_t) + sizeof (u32) + m_nSummaryLen);
		memcpy( pchStartPos, &m_dwSn, sizeof (u32) );
		memcpy( pchStartPos + sizeof (u32), &m_tOccurTime, sizeof (time_t) );
		memcpy( pchStartPos + sizeof (u32) + sizeof (time_t),
			    lpszSummary, _tcslen(lpszSummary) );
		
	}

	//写详细的信息
	s8 *pStartPos = m_pchData + (m_dwNewAddCount-1) * m_nLogLen;
	//复制信息
	memcpy( pStartPos, &m_dwSn, sizeof (u32) );
	memcpy( pStartPos + sizeof (u32), &m_tOccurTime, sizeof (time_t) );
	memcpy( pStartPos + sizeof (u32) + sizeof (time_t), lpszSummary,
		    _tcslen(lpszSummary) );
	memcpy( pStartPos + sizeof (u32) + sizeof (time_t) + 
		            m_nSummaryLen, lpszDetail, _tcslen(lpszDetail) );

	//日志文件达到100就记录
	if (m_dwNewAddCount == WRITE_NUM)
	{
		WriteLog();
	}

	return m_dwSn;
}

/*=============================================================================
函 数 名:GetLog
功    能:得到一条日志记录,可以是详细,可以是简单,也可以是全部的信息
参    数:u32 dwSn                           [in]    要查找的日志记录的流水号
         CLogItem *pcLog                    [out]   日志记录
         u32 dwType                         [in]    TYPE_SUMMARY 得到简单信息
                                                    TYPE_DETAIL  得到详细信息
                                                    TYPE_ALL	 得到日志的全部信息
注    意:无
返 回 值:成功返回 TRUE，失败返回 FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
BOOL32 CLogManage::GetLog(u32 dwSn, CLogItem *pcLog,
                          u32 dwType /* = TYPE_SUMMARY */)
{
	ASSERT(dwSn >= 0);
	ASSERT(pcLog != NULL);

	if ( pcLog == NULL || dwSn <= 0 )
	{
		return FALSE;
	}

	BOOL32 bFlag = FALSE;
	switch ( dwType ) 
	{
	case TYPE_SUMMARY:
		bFlag = GetSummary( dwSn, pcLog );
		break;
	case TYPE_DETAIL:
		bFlag = GetDetail( dwSn, pcLog );
		break;
	case TYPE_ALL:
		bFlag = GetSummary( dwSn, pcLog );
		if ( !bFlag )
        {
            break;
        }
		bFlag = GetDetail( dwSn, pcLog );
		break;
	default:
		break;
	}

	return bFlag;
}

/*=============================================================================
函 数 名:GetLog
功    能:得到一批日志记录的简单信息, 信息只能是简单信息
参    数:u32 dwSn                           [in]    要查找的日志记录的流水号
         CLogItem *pcLog                    [out]   日志记录
         u32 dwOffSet                       [in]    指针的偏移量，即派生类的大小 
         u32 dwNum						    [in]    要查找的日志的数目
         u32 &dwNum                         [in/out]    要查找的日志的数目/实际数目
注    意:如果查找的日志的流水号小于日志文件的最小的流水号,则从最小的流水号开始查起
返 回 值:查找到记录: 返回找到最后一条记录的下一条纪录的流水号;
         没有找到记录: 返回0;
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
u32 CLogManage::GetLog(u32 dwSn, CLogItem *pcLog, u32 dwOffset, u32 &dwNum) const
{
	if ( pcLog == NULL || dwSn > m_dwSn )
	{
        dwNum = 0;
		return 0;
	}

	if ( dwSn < GetMinSn() )
	{
		dwSn = GetMinSn();
	}

	for ( u32 dwCount = 0; dwCount < dwNum; dwSn ++ )
	{
		BOOL32 bFlag = FALSE;
		bFlag = GetSummary( dwSn,
                            (CLogItem*)((u8*)(pcLog) + dwOffset * dwCount) );
		if ( bFlag )
		{
			dwCount++;
		}

		if ( dwSn > m_dwSn )
		{
			break;
		}
	}

    dwNum = dwCount;
	return dwSn;
}

/*=============================================================================
函 数 名:DeleteLog
功    能:删除指定流水号的日志记录
参    数:u32 dwSn                           [in]    要删除的日志记录的流水号
注    意:无
返 回 值:成功返回TRUE, 失败返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
BOOL32 CLogManage::DeleteLog(u32 dwSn)
{
	ASSERT(dwSn > 0);
	if ( dwSn <= 0 || dwSn > m_dwSn )
	{
		return FALSE;
	}

	//删除内存里面的简单信息
	u32 dwSequence = (dwSn - 1) % m_dwLogMaxSize;
    s32 nLogLen = sizeof (u32) + sizeof (time_t) + m_nSummaryLen;
	s8 *pchStartPos = m_pchSummaryData + dwSequence * nLogLen;
	memcpy(&dwSequence, pchStartPos, sizeof(u32) );
	if ( dwSequence != dwSn )
	{
		return FALSE;
	}

    m_dwUsedCount--;

    //  清空记录
    ZeroMemory(pchStartPos, nLogLen);

	//删除在内存里但是还没有写入文件里面的日志全部信息
	dwSequence = 0;
	for ( u32 dwLoopNum = 0; dwLoopNum < WRITE_NUM; dwLoopNum ++ )
	{
		s8 *pchStartPosition = m_pchData + dwLoopNum * m_nLogLen;
		memcpy( &dwSequence, pchStartPosition, sizeof (u32) );
		if ( dwSequence == dwSn )	
		{
            ZeroMemory(pchStartPosition, m_nLogLen);
			return TRUE;
		}
	}

	//删除文件里面的日志记录
	CFile cFile;
	BOOL bOpen = cFile.Open( m_csPathName,
                             CFile::modeReadWrite| CFile::shareExclusive );
	if ( ! bOpen )
	{
		return FALSE;
	}

	u32 dwRead = cFile.Read( &dwSequence, sizeof (u32) );
	if (dwRead == 0)
	{
		cFile.Close();
		return FALSE;
	}

	dwSequence = 0;
	dwSequence = (dwSn - 1) % m_dwLogMaxSize;
	cFile.Seek( sizeof (u32) + dwSequence * m_nLogLen, CFile::current );
	cFile.Read( &dwSequence, sizeof (u32) );
	if ( dwSequence != dwSn )
	{
		cFile.Close();
		return FALSE;
	}

	s8 *pchBuffer = new s8 [m_nLogLen];
	ZeroMemory(pchBuffer, m_nLogLen);
	//删除日志的流水号
	LONG lSeek = -static_cast<LONG>(sizeof (u32));
	cFile.Seek( lSeek, CFile::current );
	cFile.Write( pchBuffer, m_nLogLen );
	cFile.Close();
	DEL_PTR_ARRAY(pchBuffer);

	return TRUE;
}

/*=============================================================================
函 数 名:ClearLog
功    能:清除日志记录
参    数:无
注    意:无
返 回 值:成功删除返回TRUE, 失败返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
BOOL32 CLogManage::ClearLog(void)
{
	CFile cFile;
	BOOL bOpen = cFile.Open( m_csPathName,
                             CFile::modeCreate | CFile::modeWrite |
		                        CFile::shareDenyNone);
	if ( ! bOpen )
	{
		return FALSE;
	}

	m_dwCount = 0;
	m_dwSn = 0;
	m_dwNewAddCount = 0;
    m_dwUsedCount = 0;
	cFile.Write( &m_dwCount, sizeof (u32) );
	cFile.Write( &m_dwSn, sizeof (u32) );
	cFile.Close();
	DEL_PTR_ARRAY(m_pchSummaryData);

	return TRUE;
}

/*=============================================================================
函 数 名:GetMinSn
功    能:得到日志的最小可用的流水号
参    数:无
注    意:无
返 回 值:最小可用的流水号
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
2005/05/23  3.6     王昊    流水号必须是最小的, 且存在的
=============================================================================*/
u32 CLogManage::GetMinSn(void) const
{
    u32 dwOffsetNum = 0;
    s32 nLen = sizeof (u32) + sizeof (time_t) + m_nSummaryLen;
    s8 *pEmptyBuf = new s8 [nLen];
    ZeroMemory(pEmptyBuf, nLen);
    while (memcmp(pEmptyBuf, m_pchSummaryData + dwOffsetNum * nLen, nLen) == 0)
    {
        dwOffsetNum++;
    }
    memcpy(&dwOffsetNum, m_pchSummaryData + dwOffsetNum * nLen, sizeof (u32));
    DEL_PTR_ARRAY( pEmptyBuf );
    return dwOffsetNum;
}

/*=============================================================================
函 数 名:GetLogFilePath
功    能:得到日志文件的路径
参    数:无
注    意:路径是绝对路径, 包含文件名
返 回 值:日志文件的路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
CString& CLogManage::GetLogFilePath(void)
{
	CFile cFile( m_csPathName, CFile::modeCreate | CFile::modeNoTruncate );
	m_csPathName = cFile.GetFilePath();
	return m_csPathName;
}

/*=============================================================================
函 数 名:GetLogFileName
功    能:得到日志文件的文件名
参    数:无
注    意:无
返 回 值:文件名
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
CString CLogManage::GetLogFileName(void)
{
	CString csFileName = _T("");
	CFile cFile( LPCTSTR(m_csPathName),
                 CFile::modeCreate | CFile::modeNoTruncate);
	csFileName = cFile.GetFileName();
	return csFileName;
}

/*=============================================================================
函 数 名:ReadLog
功    能:把文件里面日志记录的简单信息读到内存里面
参    数:无
注    意:无
返 回 值:成功: TRUE; 失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
2005/05/23  3.6     王昊    处理空值情况
=============================================================================*/
BOOL32 CLogManage::ReadLog(void)
{
	CFile cFile;
	BOOL bOpen = cFile.Open( m_csPathName,
                             CFile::modeRead | CFile::shareDenyNone );
	if ( ! bOpen )
	{
		cFile.Open( m_csPathName,
                    CFile::modeCreate| CFile::modeWrite| CFile::shareDenyNone );
		cFile.Write( &m_dwCount,sizeof (u32) );
		cFile.Write( &m_dwSn,sizeof (u32) );
		cFile.Close();
		return FALSE;
	}

    UINT dwRead = cFile.Read( &m_dwCount, sizeof (u32) );
	cFile.Read( &m_dwSn, sizeof (u32) );
	if ( dwRead == 0 )
	{
		cFile.Close();
		return FALSE;
	}

	if ( m_dwCount == 0 )
	{
		cFile.Close();
		return FALSE;
	}

    u32 dwGetNum = static_cast<s32>(m_dwBufferSize / m_nLogLen);
    u32 dwRealNum = 0;
    u32 dwReadNum = 0;
    s32 nOffset = 0;
    MallocBuffer();

    s8 *pEmptyBuf = new s8 [sizeof (u32) + sizeof (time_t) + m_nSummaryLen];

    while (dwReadNum < m_dwCount)
    {
        s32 nNumThisTime = m_dwCount - dwRealNum;
        nNumThisTime = nNumThisTime > (s32)dwGetNum ? dwGetNum : nNumThisTime;
        dwReadNum += nNumThisTime;

        u32 dwRealLen = nNumThisTime * m_nLogLen;
        cFile.Read( m_pchBuffer, dwRealLen );

        //复制内容倒m_pchSummaryData
		u32 dwCopyLength = sizeof (u32) + sizeof (time_t) + m_nSummaryLen;
		for ( s32 nNum = 0; nNum < nNumThisTime; nNum ++ )
		{
            s8 *pBuf = m_pchBuffer + nNum * (dwCopyLength + m_nDetailLen);
            memcpy( m_pchSummaryData + nOffset, pBuf, dwCopyLength );
            nOffset += dwCopyLength;
            //  wanghao 2005/05/23  日志文件某项位置可能为空, 需要跳过
            if ( memcmp(m_pchBuffer, pEmptyBuf, dwCopyLength) != 0 )
            {
                dwRealNum++;
            }
		}
		ZeroMemory( m_pchBuffer, m_dwBufferSize );
    }

    m_dwUsedCount = dwRealNum;

	cFile.Close();
    DEL_PTR_ARRAY(pEmptyBuf);

	return TRUE;
}

/*=============================================================================
函 数 名:GetSummary
功    能:得到指定流水号的日志记录的简单信息
参    数:u32 dwSn                           [in]    要查找的日志记录的流水号
         CLogItem *pcLog                    [out]   日志记录
注    意:无
返 回 值:成功: TRUE; 失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
BOOL32 CLogManage::GetSummary(u32 dwSn, CLogItem *pcLog) const
{
	if ( pcLog == NULL || dwSn > m_dwSn )
	{
		return FALSE;
	}

	u32 dwPos = (dwSn - 1) % m_dwLogMaxSize;
	u32 dwSquence = 0;
	memcpy( &dwSquence, (m_pchSummaryData + dwPos * 
		                    (sizeof (u32) + sizeof (time_t)+ m_nSummaryLen)),
            sizeof (u32) );
	if ( dwSquence != dwSn )
	{
		return FALSE;
	}

	s8 *pchBuffer = new s8[m_nSummaryLen]; 
	ZeroMemory(pchBuffer,m_nSummaryLen);
	time_t tOccurTime;
	memcpy( &tOccurTime, m_pchSummaryData + sizeof(u32) + m_nSummaryLen
                            + dwPos * (sizeof (s32) + sizeof (time_t)),
            sizeof (time_t) );
	memcpy( pchBuffer,
            m_pchSummaryData + sizeof (u32) + sizeof (time_t) + m_nSummaryLen
		                    + dwPos * (sizeof (s32) + sizeof (time_t)),
            m_nSummaryLen);
	pcLog->SetTimeDate( tOccurTime );
	pcLog->SetSquence( dwSquence );
	pcLog->SetSummary( pchBuffer );
	DEL_PTR_ARRAY (pchBuffer);

	return TRUE;
}

/*=============================================================================
函 数 名:GetDetail
功    能:得到指定流水号的日志记录的详细信息
参    数:u32 dwSn                           [in]    要查找的日志记录的流水号
         CLogItem *pcLog                    [out]   日志记录
注    意:无
返 回 值:成功: TRUE; 失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
BOOL32 CLogManage::GetDetail(u32 dwSn, CLogItem *pcLog)
{
	if ( pcLog == NULL )
	{
		return FALSE;
	}
	CFile cFile;
	u32 dwSquence1 = 0;

	//读取日志记录条数
	for ( u32 dwCount1 = 0; dwCount1 < WRITE_NUM; dwCount1 ++ )
	{
		s8 *pchStart = m_pchData + dwCount1 * m_nLogLen;
		memcpy( &dwSquence1, pchStart, sizeof (u32) );
		if ( dwSquence1 == dwSn )
		{
			s8 *pchBuffer1 = new s8 [m_nDetailLen];
			ZeroMemory(pchBuffer1, m_nDetailLen);
			memcpy( pchBuffer1,
                    pchStart + (sizeof(u32) + sizeof (time_t) + m_nSummaryLen),
                    m_nDetailLen );
			pcLog->SetDetail( pchBuffer1 );
			DEL_PTR_ARRAY (pchBuffer1);
			return TRUE;
		}
	}

	BOOL bOpen = cFile.Open( m_csPathName,
                             CFile::modeRead | CFile::shareDenyWrite );
	if ( ! bOpen )
	{
		return FALSE;
	}

	UINT dwRead = cFile.Read(&m_dwCount, sizeof(u32));
	if (dwRead == 0)
	{
		cFile.Close();
		return FALSE;
	}

	//第二个u32记录了文件中流水号的最大的数值
	cFile.Read( &m_dwSn, sizeof (u32) );
	if ( dwSn > m_dwSn )
	{	
		cFile.Close();
		return FALSE;
	}

	u32 dwSquence = (dwSn - 1) % m_dwLogMaxSize;
	cFile.Seek( (dwSquence) * m_nLogLen, CFile::current );
	cFile.Read( &dwSquence, sizeof (u32) );
	if ( dwSquence != dwSn )
	{
		cFile.Close();
		return FALSE;
	}

	s8 *pchBuffer = new s8 [m_nDetailLen];
	ZeroMemory(pchBuffer , m_nDetailLen);

	cFile.Seek( sizeof (time_t) + m_nSummaryLen, CFile::current );
	cFile.Read( pchBuffer, m_nDetailLen );
	pcLog->SetDetail( pchBuffer );

	DEL_PTR_ARRAY (pchBuffer);
	cFile.Close();

	return TRUE;
}

/*=============================================================================
函 数 名:MallocBuffer
功    能:动态分配内存
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
void CLogManage::MallocBuffer(void)
{
	DEL_PTR_ARRAY(m_pchSummaryData) ;

	u32 dwStep = sizeof (time_t) + sizeof (u32) + m_nSummaryLen;
	m_pchSummaryData = new s8 [(m_dwCount + m_dwMallocStep) * dwStep];

	ZeroMemory( m_pchSummaryData, (m_dwCount + m_dwMallocStep) * dwStep );
}

/*=============================================================================
函 数 名:WriteLog
功    能:把内存里面的日志记录写到日志文件里面去
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/04/07  3.6     刘瑞飞  创建
=============================================================================*/
void CLogManage::WriteLog()
{
	CFile cFile;
	BOOL bOpen = cFile.Open( m_csPathName,
                             CFile::modeCreate | CFile::modeNoTruncate
		                        | CFile::modeWrite | CFile::shareExclusive );
	if ( ! bOpen )
	{
		return;
	}

	//当日志文件数目超出10000条时用新的日志覆盖最旧的日志
	if ( m_dwCount > m_dwLogMaxSize )
	{	
		m_dwCount = m_dwLogMaxSize;
		cFile.Write( &m_dwCount, sizeof (u32) );
		cFile.Write( &m_dwSn, sizeof (u32) );
		u32 dwStartPos = 0;
		if ( (m_dwSn-m_dwNewAddCount) % m_dwLogMaxSize
                > m_dwSn % m_dwLogMaxSize )
		{
			dwStartPos = (m_dwSn - m_dwNewAddCount) % m_dwLogMaxSize;
			cFile.Seek(2 * sizeof(u32) + dwStartPos * m_nLogLen, CFile::begin);
			cFile.Write( m_pchData, (m_dwLogMaxSize - dwStartPos)*m_nLogLen );
			cFile.Seek( 2 * sizeof (u32), CFile::begin );
			cFile.Write( m_pchData + (m_dwLogMaxSize -dwStartPos) * m_nLogLen,
			             (m_dwNewAddCount - (m_dwLogMaxSize - dwStartPos))
                                * m_nLogLen );
		}
		else
		{
			dwStartPos = (m_dwSn-m_dwNewAddCount) % m_dwLogMaxSize;
			cFile.Seek(2 * sizeof(u32) + dwStartPos * m_nLogLen, CFile::begin);
			cFile.Write( m_pchData, m_dwNewAddCount * m_nLogLen );
		}
		cFile.Close();
	}
	else
	{
		cFile.Write( &m_dwCount, sizeof (u32) );
		cFile.Write( &m_dwSn, sizeof (u32) );
		cFile.SeekToEnd();
		cFile.Write(m_pchData, m_dwNewAddCount * m_nLogLen);
		cFile.Close();
	}

	//扫尾工作
	ZeroMemory(m_pchData, m_nDetailLen * WRITE_NUM);
	m_dwNewAddCount = 0;
}