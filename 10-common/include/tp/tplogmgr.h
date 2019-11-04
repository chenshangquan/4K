#include "loguserdef.h"

#ifndef _h_tplogmgr_h__
#define _h_tplogmgr_h__


#define MAX_MSGMDL_NUM (MID_UMS_20 - MID_CNS_1 + 1)
#define MAX_MSGLEVEL_NUM 5 //m_achmsgLogLevel 此数组 引用时候都是从1开始的，因此定义数量比打印层级+1，0位置不使用

typedef struct tagTMsgPrintCtrl
{
#define MAX_MDL_NAME 24
	BOOL32	m_bShow;
	s8		m_achlName[MAX_MDL_NAME];
	tagTMsgPrintCtrl()
	{
		m_bShow = FALSE;
		m_achlName[0] = '\0';
	}
}TMsgPrintCtrl;

class CTpLog;
class CTpLogManager
{	
	enum{ MaxInst = 512 ,PoolSize =5120 };
	static CTpLog*    m_apcLog[MaxInst];
	static u16        m_wEndInst;
	static u16        m_wTitlePoolEndPos;
	static s8         m_abyTitlePool[PoolSize+32];
public:
	static TMsgPrintCtrl m_atmsgModelCtrl[MAX_MSGMDL_NUM];
	static s8			 m_achmsgLogLevel[MAX_MSGLEVEL_NUM][24];
	static u32			 m_dwLogLevel;
	static BOOL32		 m_bIsInitKdvLog;
public:
	CTpLogManager();
	~CTpLogManager();
	static BOOL32 Init();
	static BOOL32 Regist( CTpLog* pcLogInst );
	static void UnRegist( CTpLog* pcLogInst );
	static s8*  CopyTitle(const s8*const title );
	static void ShowAllInst();
    static void ShowAllTitle(); 
	static void ShowLastMsg(); 
	static void SaveLastMsg(s8* pszFile); 
};



#define IsCanPrint(mdl, level) ( ((mdl - MID_CNS_1 + 1) > 0) && ((mdl - MID_CNS_1) < MAX_MSGMDL_NUM) && CTpLogManager::m_atmsgModelCtrl[(mdl - MID_CNS_1)].m_bShow && (CTpLogManager::m_dwLogLevel >= level))

#endif // _h_tplogmgr_h__
