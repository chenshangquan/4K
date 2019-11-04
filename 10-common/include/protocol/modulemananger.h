#ifndef MODULEMANANGER
#define MODULEMANANGER
/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        modulemananger.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       mananger module
*   @details     
*/

#include "pfc.h"
#include "kdvtype.h"
#include "protocolcommonpublic.h"

#define MODULE_MSG_HEADER_LEN 4
#define MAX_MODULE_MSG_LEN 65531
#define ev_module_msg_init PFC_OSP_USEREVENT_BASE + 1
#define ev_module_msg_exit PFC_OSP_USEREVENT_BASE + 2
#define ev_module_msg_timer PFC_OSP_USEREVENT_BASE + 3
#define MAX_TITLE_LEN  32

class CModuleMsg;
class PROTO_API CModuleObject : public CTiInstance
{
public:
	CModuleObject();
	virtual ~CModuleObject();
	
	friend class CModuleHandler;
	
protected:
	BOOL32    m_bInit;/**<初始化标志*/
private:
    void DaemonInstanceEntry( CTiMessage *const pcMsg, CTiApp* pcApp );							/**< daemon消息入口函数 */
	void InstanceEntry( CTiMessage *const ptMsg );											/**< 消息处理入口函数 */
protected:
	
	virtual void MessageProc( CModuleMsg *const ptMsg ) {};										/**< 消息入口函数，此函数需要重载 */
	virtual void DaemonMessageProc( CModuleMsg *const ptMsg,CTiApp* pcApp ){}					/**< daemon消息入口函数，此函数需要重载 */
	
	virtual BOOL32 DaemonObjectInit( MemId wParam, MemId lParam );								/**< daemon初始化函数，需要重载 */
	virtual void DaemonObjectExit( void );													/**< daemon退出函数，需要重载 */
	virtual BOOL32 PreDaemonMessageProc( CTiMessage *const ptMsg )	{ return FALSE; }		    /**< daemon消息预处理函数，需要重载 */
	
protected:
	virtual BOOL32 ObjectInit( MemId wParam, MemId lParam ) = 0;									/**< object初始化函数，需要重载 */
	virtual void ObjectExit( void );															/**< object退出函数，需要重载 */
	
	virtual BOOL32 PreMessageProc( CTiMessage *const ptMsg )	{ return FALSE; }			    /**< 消息预处理函数，需要重载 */
	
public:
	void SetLogTitle(const s8* title );															/**< 设置模块打印前缀(模块名) */

	void Error(const s8* szFormat, ...);
	void Hint(const s8* szFormat, ...);
	void LowHint(const s8* szFormat, ... );

	BOOL32 NotifySelf( CModuleMsg &cMsg );
    
private:
	void*     m_plog;
	BOOL32      m_bShowMsg;
};


class CModuleMsg;
class CModuleHandler
{
protected:
	CModuleObject* m_pcInstance;
public:

	CModuleHandler( CModuleObject* pcObject ){ m_pcInstance = pcObject; }
	~CModuleHandler();

	virtual BOOL32 Handler( CModuleMsg *const ptMsg ) = 0;
	
	virtual BOOL32 Create()	{ return TRUE; }
	virtual void Destroy(){};
	void Error( s8* szFormat, ... );
	void Hint( s8* szFormat, ... );
	void LowHint( s8* szFormat, ... );

protected:

	int SetTimer( u32 nTimer, long nMilliSeconds, u32 nPara=0)
	{
		if( m_pcInstance )
			return m_pcInstance->SetTimer( nTimer ,nMilliSeconds ,nPara );
		return 0;
	};
	
	int KillTimer( u32 nTimerNo )
	{
		if( m_pcInstance )
			return m_pcInstance->KillTimer( nTimerNo );
		return 0;
	};
	
	CModuleObject*   GetInstance(){ return m_pcInstance; }
};

/// module message definition
class CModuleMsg
{
protected:
	u16 m_wEvent;
	u16 m_wBodyLen;
	u32 m_dwSrcIId;
	u32 m_dwSrcNode;
	
	u8  *m_pbyMsg;
	s32 m_nXMLIndex;
	
protected:
	enum EmMsgCodeIndex
	{
		CODEC_FLAG			= 0,	/**< 该字节 = 0, 表示未编码 */
		CODEC_HOMEPLACE		= 1,	/**< 表示编码数据 */
		CODEC_User			= 2,	/**< 表示xml编码 */
		CODEC_RESERVER3		= 3,	
		CODEC_BODY			= 4,	

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE			= 0,
		CODEC_XML_MARSHAL	= 2,/**< 兼容旧的终端xml，从2开始 */
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData			= 0 ,/**< 未经编解码的原始数据 */
		emCodeData         /**< 经编解码的数据 */
	};
	/**消息是否经过编码 */
	u8 IsMsgCoder()
	{
		return m_pbyMsg[0];
	}

#define INVALID_SIP_XML_INDEX -1

public:
	CModuleMsg()
	{
		m_pbyMsg		= new u8[ MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN ];
        if(NULL == m_pbyMsg)
        {
            PfcPrintf(TRUE, FALSE, "CModuleMsg Failed to allocate memory\n");
        }
		Clear();
	}
	CModuleMsg( const CTiMessage* ptMsg )
	{
        if (NULL == ptMsg)
            return;
		m_pbyMsg		= new u8[ MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN ];
		m_nXMLIndex		= INVALID_SIP_XML_INDEX;
		m_dwSrcIId		= ptMsg->srcid;
		m_dwSrcNode		= ptMsg->srcnode;
		m_wEvent		= ptMsg->event;
		m_wBodyLen		= ptMsg->length - MODULE_MSG_HEADER_LEN;
        if(NULL != m_pbyMsg)
        {
            memcpy(m_pbyMsg, ptMsg->content, ptMsg->length);
        }
	}

	~CModuleMsg()
	{
		if (m_pbyMsg)
		{
			delete[] m_pbyMsg;
			m_pbyMsg = NULL;
		}
	}

	void Clear()
	{
		//memset( this,0,sizeof(CModuleMsg) );
		m_wEvent		= 0;
		m_wBodyLen		= 0;
		m_dwSrcIId		= 0;
		m_dwSrcNode		= 0;
		if (m_pbyMsg)
			memset(m_pbyMsg, 0, MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN);
		m_nXMLIndex		= 0;
	}

	/**获得消息体指针*/
	u8*	GetBody(){ return m_pbyMsg+CODEC_BODY; }
	
	/**获得消息体长度*/
	u16	GetBodyLen() { return m_wBodyLen; }

	/**设置消息体长度*/
	void SetBodyLen(u16 wLen) { m_wBodyLen = wLen; }

	/**获得消息指针*/
	u8*	GetMsg(){ return m_pbyMsg; }
	
	/**获得消息长度*/
	u16	GetMsgLen() { return m_wBodyLen + MODULE_MSG_HEADER_LEN; }

	/**设置消息体内容*/
	BOOL32 SetBody(const void* buf ,u16 len )
	{ 
		if( (len > (u16)(MAX_MODULE_MSG_LEN)) || (NULL == m_pbyMsg))
			return FALSE;
		if( NULL == buf || 0 == len )
		{
			m_wBodyLen = 0;
			return TRUE;
		}
		memcpy(m_pbyMsg + CODEC_BODY,buf ,len );
		m_wBodyLen = len;
		return TRUE;
	}

	/**添加消息体内容*/
	BOOL32 CatBody( const void* buf ,u16 len )
	{
		if( (len + m_wBodyLen > (u16)(MAX_MODULE_MSG_LEN)) || (NULL == m_pbyMsg))
			return FALSE;

		memcpy( m_pbyMsg +CODEC_BODY +m_wBodyLen ,buf ,len );
		m_wBodyLen += len;
		return TRUE;
	}

	void SetEvent(u16 event ) { m_wEvent = event; }
	u16  GetEvent() { return m_wEvent; }

	u32 GetSrcIId(){ return m_dwSrcIId; }
	u32 GetSrcNode(){ return m_dwSrcNode; }

	/**获取消息的发起者*/
	u8   GetHomeplace()
	{
		return m_pbyMsg[CODEC_HOMEPLACE];
	}

	void SetHomeplace( u8 byNode )
	{
		m_pbyMsg[CODEC_HOMEPLACE] = byNode;
	}

	/// get/set user data
	u8   GetUserData()
	{
		return m_pbyMsg[CODEC_User];
	}

	void   SetUserData( u8 byData )
	{
		m_pbyMsg[CODEC_User] = byData;
	}

protected:
    void  DisplayMsgStream( u32 srcid , u32 dstid );
};

/// module inition params
typedef struct tagMdlInitParam
{
	s8				achTitle[MAX_TITLE_LEN+1];	/**< 模块title名字*/
	MemId			wParam;
	MemId			lParam;						/**< 用户自定义*/
	PFCSEMHANDLE	hSem;
	
	tagMdlInitParam()
	{
		memset(achTitle, 0, MAX_TITLE_LEN + 1);
		wParam		= 0;
		lParam		= 0;
		hSem		= NULL;
	}
}TMDLInitParam;

#endif
