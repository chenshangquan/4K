#ifndef _h_tplog_h__
#define _h_tplog_h__


#include "osp.h"
#include "tplogmgr.h"
#include "tpmsg.h"
#include "loguserdef.h"

/*
#define MID_TP_START	(MID_MT_START + 50)
#define MID_CNC_START	MID_TP_START
#define MID_CNS_START	(MID_TP_START + 30)
#define MID_UMS_START	(MID_TP_START + 60)

///////////////////////////////////////
#define MID_CNS_1    (MID_CNS_START + 1)
#define MID_CNS_2    (MID_CNS_START + 2)
#define MID_CNS_3    (MID_CNS_START + 3)
#define MID_CNS_4    (MID_CNS_START + 4)
#define MID_CNS_5    (MID_CNS_START + 5)
#define MID_CNS_6    (MID_CNS_START + 6)
#define MID_CNS_7    (MID_CNS_START + 7)
#define MID_CNS_8    (MID_CNS_START + 8)
#define MID_CNS_9    (MID_CNS_START + 9)
#define MID_CNS_10   (MID_CNS_START + 10)
#define MID_CNS_11   (MID_CNS_START + 11)
#define MID_CNS_12   (MID_CNS_START + 12)
#define MID_CNS_13   (MID_CNS_START + 13)
#define MID_CNS_14   (MID_CNS_START + 14)
#define MID_CNS_15   (MID_CNS_START + 15)
#define MID_CNS_16   (MID_CNS_START + 16)
#define MID_CNS_17   (MID_CNS_START + 17)
#define MID_CNS_18   (MID_CNS_START + 18)
#define MID_CNS_19   (MID_CNS_START + 19)
#define MID_CNS_20   (MID_CNS_START + 20)
////////////////////////////////////////
#define MID_UMS_1    (MID_UMS_START + 1)
#define MID_UMS_2    (MID_UMS_START + 2)
#define MID_UMS_3    (MID_UMS_START + 3)
#define MID_UMS_4    (MID_UMS_START + 4)
#define MID_UMS_5    (MID_UMS_START + 5)
#define MID_UMS_6    (MID_UMS_START + 6)
#define MID_UMS_7    (MID_UMS_START + 7)
#define MID_UMS_8    (MID_UMS_START + 8)
#define MID_UMS_9    (MID_UMS_START + 9)
#define MID_UMS_10   (MID_UMS_START + 10)
#define MID_UMS_11   (MID_UMS_START + 11)
#define MID_UMS_12   (MID_UMS_START + 12)
#define MID_UMS_13   (MID_UMS_START + 13)
#define MID_UMS_14   (MID_UMS_START + 14)
#define MID_UMS_15   (MID_UMS_START + 15)
#define MID_UMS_16   (MID_UMS_START + 16)
#define MID_UMS_17   (MID_UMS_START + 17)
#define MID_UMS_18   (MID_UMS_START + 18)
#define MID_UMS_19   (MID_UMS_START + 19)
#define MID_UMS_20   (MID_UMS_START + 20)
*/

#ifdef WIN32
#ifndef vsnprintf
#define vsnprintf		_vsnprintf
#endif

#ifndef snprintf
#define snprintf		_snprintf
#endif

#ifndef strncasecmp
#define strncasecmp		_strnicmp
#endif
#endif


#define MAX_MSG_LEN_TMP 235

//mtlog.h begin.
typedef BOOL (*ExcPrintCB)( FILE* pFile );	//异常打印函数
typedef BOOL (*LogPrintCB)( s8* pszBuf, u8 byBufLen);	//日志版本记录函数

typedef struct tagMdlCBFun
{
	ExcPrintCB  pFunException;
	LogPrintCB	pFunLogPrint;
	
	tagMdlCBFun()
		:pFunException(NULL)
		,pFunLogPrint(NULL)
	{
	}
}TMdlCBFun, *PTMdlCBFun;

enum EmModuleType
{
	emModuleMtVer = 0,
		emModuleMtUpgrade,
		emModuleMtService,//修改原因:(协议栈定义的枚举名称重复)
		emModuleConfig,
		emModuleDevice,
		emModuleMtMp,
		emModuleMcService,
		emModuleH323Service,
		emModuleUI,
		emModuleGUI,
		emModuleWin,
		emModuleAgent,
		emModuleSysapi,
		emModuleTpyeEnd,
};
extern const char* g_pszMdlName[];	//必须和EmLogModuleType对应


extern void mtRegisterVerionPrintFunc( void* pf, const char* pszModuleName ); // 模块版本打印函数注册接口
enum EmStateLogType
{
	emH323ChanShow = 0,
		emH323CallShow,
		emH323CapShow,
		emMtmpShow,
		emMedianetShow,
		emInnerMcShow,
		emStateLogTypeEnd,
};
//mtlog.h end.

enum ENLogLevel
{
	enLoglowDetail = LOG_LVL_DETAIL,
	enLogLowest = LOG_LVL_KEYSTATUS,
	enLogHint = LOG_LVL_WARNING,
	enLogError = LOG_LVL_ERROR,
};

class CTpLog
{
public:
	CTpLog();
	virtual ~CTpLog();

protected:
	s8*   m_pLogTitle;

	u16   m_wLogModuleId;
	u16	  m_wLastEventID;	//最后一条处理的消息
	BOOL  m_bInHandMsg;		//是否还在处理中,   消息入口置TRUE，出口置FALSE

protected:

	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );

	void SetLogTitle( s8* title );//设置日志打印标题

public:
	virtual u16  GetLogApp()				{ return 0; }	
	virtual u16  GetLogInst()				{ return 0; }
	s8*  GetTitle()							{ return m_pLogTitle; }	
	u16  GetLastEventID(void)	const		{ return m_wLastEventID; }	
	BOOL GetInHandMsg() const				{ return m_bInHandMsg; }
	void SetLogModule( u16 wModuleId){m_wLogModuleId = wModuleId;};
	void SetLastEventID(u16 dwEventID)		{ m_wLastEventID = dwEventID; }
	void SetInHandMsg(BOOL bInHandMsg )		{ m_bInHandMsg = bInHandMsg; }
};

void printcallid(u8* pCallID, u16 wCallSize, BOOL32 bPauseZero = TRUE);
void msgprint( char *szFormat, ... );
void msgprintnotime( char *szFormat, ... );

void setmdllogname(u32 dwMdl, s8* pszName);

//放开指定模块的打印， 0为所有
API void tplogon(u32 dwMdl);
API void tploglow(u32 dwMdl);
API void tplogdtl(u32 dwMdl);
API void tplogoff();





#define ObjHint(printParams) if(IsCanPrint(m_wLogModuleId, enLogHint)) Hint printParams;
#define ObjError(printParams) /*if(IsCanPrint(m_wLogModuleId, enLogError))*/ Error printParams;

void MsgPrintHintLog(s8* szFormat, ...);
void MsgPrintErrorLog(s8* szFormat, ...);

void tpLowDtl( u16 wMdl,s8* szFormat, ...);
void tpLowHint( u16 wMdl,s8* szFormat, ...);
void tpHint( u16 wMdl,s8* szFormat, ...);
void tpError(s8* szFormat, ...);

#define MdlLowDtl(mdl, printParams) if(IsCanPrint(mdl, enLoglowDetail)) MsgPrintErrorLog printParams;
#define MdlLowHint(mdl, printParams) if(IsCanPrint(mdl, enLogLowest)) MsgPrintErrorLog printParams;
#define MdlHint(mdl, printParams) if(IsCanPrint(mdl, enLogHint)) MsgPrintHintLog printParams;
#define MdlError(mdl, printParams) /*if(IsCanPrint(mdl, enLogError))*/ MsgPrintErrorLog printParams;

//异常时输出
#ifdef _LINUX_
int regist_exception(const s8 *pachModuleName ,const s8* LogName);
#endif

void regist_tp_commond();
//void mtPrintf( char *szFormat, ... );

BOOL32 initKdvLog(s8 * pchName, BOOL32 bPrintToCom = TRUE);
void SetPrintToCom(BOOL32 bPrint);

#endif//!_h_tplog_h__


