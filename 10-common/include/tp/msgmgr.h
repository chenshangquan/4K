#ifndef _h_msgtype_h__
#define _h_msgtype_h__
#include "kdvtype.h"
#include "xmlengine.h"


enum EmxSysDataType
{
	emxAtomTypeBegin =0,//原子类型数据
		emx_s32,
		emx_BOOL32,
		emx_BOOL,
		emx_u8,
		emx_s8,
		emx_u16,
		emx_u32,
		emx_u32_ip,
		emx_u8_blob,
		emx_time_t,
		emx_string,
	emxEnumTypeBegin = 20,//枚举类型数据

	emxStructTypeBegin = 400, //数据结构类型数据(mtstruct.h 业务层结构类型头文件的解析结果)

	emxDataTypeEnd = 1000 //类型定义结束
};

struct TXEVENTINFO
{
	u16   eventid;				//Event id值
	char* name;					//Event description
	TXDATANODE* tDataNode;		//所对应结构数组

	TXEVENTINFO()
	{
		eventid = 0;
		name = 0;
		tDataNode = 0;
	}
};


//MsgInfo : 消息信息
typedef struct tagTTpMsgInfo
{
	u32 m_dwOutMinEventValue;
	u32 m_dwOutMaxEventValue;

	u32 m_dwInnerMinEventValue;
	u32 m_dwInnerMaxEventValue;

	TXDATAINFO** m_ptMsgEnumDataInfo;
	TXDATAINFO** m_ptMsgStructDataInfo;

	tagTTpMsgInfo()
	{
		m_dwOutMinEventValue = 0;
		m_dwOutMaxEventValue = 0;
		m_dwInnerMinEventValue = 0;
		m_dwInnerMaxEventValue = 0;
		m_ptMsgEnumDataInfo = NULL;
		m_ptMsgStructDataInfo = NULL;
	}	
}TTpMsgInfo;


BOOL32 InitEventMgr(TTpMsgInfo& tInfo);
void ExitEventMgr();



#endif // _h_msgtype_h__
