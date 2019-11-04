// cncaddrbook.cpp: implementation of the CCncAddrbook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncaddrbook.h"
#include "cncmsgrecver.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncAddrbook::CCncAddrbook( CCnsSession &cSession )
			: CCncAddrbookIF(), m_cAddrBook(MAX_ADDRENTRY, MAX_ADDRGROUP)
{
	m_pSession = &cSession;

	
	// 启动地址簿app
    u16 wRet = InitializeAddrOsp();
    ASSERT(wRet == NO_ERROR);
	RegHandler(this);

	g_AddrBookApp.SetNotifyWindow( GetOspRecvWindow() );

	BuildEventsMap();

	m_bAddrLoading = FALSE;
}

CCncAddrbook::~CCncAddrbook()
{
	// 置OSP通知目的窗口为空
    g_AddrBookApp.SetNotifyWindow(NULL);
    g_AddrBookApp.SetNodeId(INVALID_NODE);
    g_AddrBookApp.ClearOspMsg();
}



//分发消息
void CCncAddrbook::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncAddrbook, cMsg);
}

inline void CCncAddrbook::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}

u16 CCncAddrbook::PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg,
							 CKdvDispEvent *pDispEvent,u16 *pwEventTab,
							 s32 nEventNum, u32 dwTimeOut)
{
    CAddrBookMsg msgNew = cMsg;
	
    CMessage *pMsg = GetCMsgPtr();
    pMsg->event = wEvent;
    pMsg->length = sizeof(CAddrBookMsg);
    pMsg->content = reinterpret_cast<u8*>(&msgNew);
    pMsg->dstid = MAKEIID(AID_ADDRBOOK, 1);
	return PostCommand(pDispEvent, pwEventTab, nEventNum, TYPE_CMESSAGE, dwTimeOut);
}

u16 CCncAddrbook::PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg)
{
	CAddrBookMsg msgNew = cMsg;
	
	CMessage *pMsg = GetCMsgPtr();
    pMsg->event = wEvent;
    pMsg->length = sizeof(CAddrBookMsg);
    pMsg->content = reinterpret_cast<u8*>(&msgNew);
    pMsg->dstid = MAKEIID(AID_ADDRBOOK, 1);
	return PostMsg();
}


inline CAddrBook& CCncAddrbook::GetAddrBook()
{
    return m_cAddrBook;
}


u16 CCncAddrbook::RegAddrBook()
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_REGISTER_ACK;
    awWaitEvent[1] = ADDRBOOK_REGISTER_NACK;
    CAddrBookMsg cAddrMsg;
    u16 wRet = PostCmdToAddr(ADDRBOOK_REGISTER_REQ, cAddrMsg, this, awWaitEvent, 2);

    PrtMsg( ADDRBOOK_REGISTER_REQ, emEventTypeCnsSend, "" );
    return wRet;
}

u16 CCncAddrbook::UnRegAddrBook()
{
    m_cAddrBook.ClearAddrBook();
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_SAVE_ACK;
    awWaitEvent[1] = ADDRBOOK_SAVE_NACK;
    CAddrBookMsg cAddrMsg;	
	u16 wRet =  PostCmdToAddr(ADDRBOOK_UNREG_CMD, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_UNREG_CMD, emEventTypeCnsSend, "" );
	PostEvent(UI_CNS_ADDRBOOK_CHANGED);
    return wRet;
}


u16 CCncAddrbook::AddEntry(const CAddrEntry& entry)
{	
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_ENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_ENTRY_NACK;
	
    CAddrEntry entry2 = entry;
    TADDRENTRY tentry;
    ZeroMemory(&tentry, sizeof(TADDRENTRY));
    tentry.SetEntryIndex(entry2.GetEntryIndex());
    TADDRENTRYINFO info;
    ZeroMemory(&info, sizeof(TADDRENTRYINFO));
    entry2.GetEntryInfo(&info);
    tentry.SetEntryInfo(&info);
	
	BOOL32 bExist = m_cAddrBook.IsAddrEntryExist(info) == INVALID_INDEX ? FALSE : TRUE; 
	if (bExist)
	{
		return NO_ERROR;
	}	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tentry), sizeof(TADDRENTRY));
	
    u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_ENTRY_REQ, cAddrMsg);

	PrtMsg( ADDRBOOK_ADD_ENTRY_REQ, emEventTypeCnsSend, "添加地址条目 Name: %s, E164: %s", info.achEntryName, info.achMtNumber );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::ModifyEntry(const CAddrEntry& entry)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_MODIFYENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_MODIFYENTRY_NACK;
    
    CAddrEntry entry2 = entry;
    TADDRENTRY tentry;
    ZeroMemory(&tentry, sizeof(TADDRENTRY));
    tentry.SetEntryIndex(entry2.GetEntryIndex());
    TADDRENTRYINFO info;
    ZeroMemory(&info, sizeof(TADDRENTRYINFO));
    entry2.GetEntryInfo(&info);
    tentry.SetEntryInfo(&info);
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tentry), sizeof(TADDRENTRY));
   
	u16 wRet = PostCmdToAddr(ADDRBOOK_MODIFYENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_MODIFYENTRY_REQ, emEventTypeCnsSend, "修改地址条目 Name: %s, E164: %s", info.achEntryName, info.achMtNumber );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteEntry(u32 dwIndex)
{
    u16 awWaitEvent[2];
	awWaitEvent[0] = ADDRBOOK_DEL_ENTRY_ACK;
	awWaitEvent[1] = ADDRBOOK_DEL_ENTRY_NACK;
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex(dwIndex);
    
	u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_ENTRY_REQ, cAddrMsg);
	PrtMsg( ADDRBOOK_DEL_ENTRY_REQ, emEventTypeCnsSend, "删除地址条目: %d", dwIndex );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::DeleteMultiEntry( vector<u32> vctEntry )
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetEntryIndex( MULTI_ENTRY );

    int nSize = vctEntry.size();
    if ( nSize > MAX_DELENTRY_NUM )
    {
        return ERR_CNC_ARRAY_OVERBOUNDS;
    }

    u32 adwEntry[MAX_DELENTRY_NUM] = {0};
    for ( int i = 0; i < nSize; i++ )
    {
        adwEntry[i] = htonl( vctEntry.at(i) );
    }

    cAddrMsg.SetMsgBody( (u8*)adwEntry, sizeof(u32)*nSize );

	u16 wRet = PostCmdToAddr( ADDRBOOK_DEL_ENTRY_REQ, cAddrMsg );
	PrtMsg( ADDRBOOK_DEL_ENTRY_REQ, emEventTypeCnsSend, "删除地址条目 %d条", nSize );
	NotifyCns();
	return wRet;
}


u16 CCncAddrbook::AddGroup(const CAddrMultiSetEntry& group)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_MULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_MULSETENTRY_NACK;
    
    TADDRMULTISETENTRY tgroup;
    ZeroMemory(&tgroup, sizeof(TADDRMULTISETENTRY));
    tgroup.SetEntryIndex(group.GetGroupIndex());//条目索引
    TMULTISETENTRYINFO info;
    ZeroMemory(&info, sizeof(TMULTISETENTRYINFO));
    CAddrMultiSetEntry group2 = group;
    group2.GetGroupInfo(&info);
    tgroup.SetEntryInfo(&info);//会议组信息
    tgroup.SetListEntryNum(group2.GetEntryCount());
    tgroup.SetListEntryIndex(group2.GetEntryTable(), group2.GetEntryCount());//会议组列表
    
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tgroup), sizeof(TADDRMULTISETENTRY));

	u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_MULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_ADD_MULSETENTRY_REQ, emEventTypeCnsSend, "添加地址组: %s", info.achGroupName );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::ModifyGroup(const CAddrMultiSetEntry& group)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_MODIFYMULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_MODIFYMULSETENTRY_NACK;
    
    TADDRMULTISETENTRY tgroup;
    ZeroMemory(&tgroup, sizeof(TADDRMULTISETENTRY));
    tgroup.SetEntryIndex(group.GetGroupIndex());
    TMULTISETENTRYINFO info;
    ZeroMemory(&info, sizeof(TMULTISETENTRYINFO));
    CAddrMultiSetEntry group2 = group;
    group2.GetGroupInfo(&info);
    tgroup.SetEntryInfo(&info);
    tgroup.SetListEntryNum(group2.GetEntryCount());
    tgroup.SetListEntryIndex(group2.GetEntryTable(), group2.GetEntryCount());
    
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tgroup), sizeof(TADDRMULTISETENTRY));

	u16 wRet = PostCmdToAddr(ADDRBOOK_MODIFYMULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_REQ, emEventTypeCnsSend, "修改地址组: %s", info.achGroupName );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteGroup(u32 dwIndex)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_DEL_MULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_DEL_MULSETENTRY_NACK;
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex(dwIndex);
 
	u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_DEL_MULSETENTRY_REQ, emEventTypeCnsSend, "删除地址组: %d", dwIndex );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteMultiGroup( vector<u32> vctGroup )
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex( MULTI_ENTRY );

    int nSize = vctGroup.size();
    if ( nSize > MAX_ADDRGROUP )
    {
        return ERR_CNC_ARRAY_OVERBOUNDS;
    }
    
    u32 adwGroup[MAX_ADDRGROUP] = {0};
    for ( int i = 0; i < nSize; i++ )
    {
        adwGroup[i] = htonl( vctGroup.at(i) );
    }
    
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(u32)*nSize );

    u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg );

    PrtMsg( ADDRBOOK_DEL_MULSETENTRY_REQ, emEventTypeCnsSend, "删除地址组 %d个", nSize );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::AddEntryToGroup(const TADDRMULTISETENTRY& tGroupEntry)
{
    TADDRMULTISETENTRY tMultiEntry = tGroupEntry;
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_ENTRYTOMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_ENTRYTOMULSET_NACK;
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tMultiEntry), sizeof(TADDRMULTISETENTRY));
   
	u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_ENTRYTOMULSET_REQ, cAddrMsg);
	PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_REQ, emEventTypeCnsSend, "添加地址条目到组" );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::DelEntryFromGroup(const TADDRMULTISETENTRY& tGroupEntry)
{
    TADDRMULTISETENTRY tMultiEntry = tGroupEntry;
       
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tMultiEntry), sizeof(TADDRMULTISETENTRY));
    
    u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_ENTRYFRMULSET_REQ, cAddrMsg);
   	PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_REQ, emEventTypeCnsSend, "从组中删除地址条目" );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_MULSETTOMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_MULSETTOMULSET_NACK;
	
	u32 adwGroup[2];
	adwGroup[0] = htonl(dwGroupIndex);
	adwGroup[1] = htonl(dwUpGroupIndex);

    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(adwGroup) );
	
	u16 wRet = PostCmdToAddr( ADDRBOOK_ADD_MULSETTOMULSET_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_MULSETTOMULSET_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_REQ, emEventTypeCnsSend, "添加地址组关系: %d的上级为%d", dwGroupIndex, dwUpGroupIndex );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_DEL_MULSETFROMMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_DEL_MULSETFROMMULSET_NACK;
	
	u32 adwGroup[2];
	adwGroup[0] = htonl(dwGroupIndex);
	adwGroup[1] = htonl(dwUpGroupIndex);
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(adwGroup) );
	
	u16 wRet = PostCmdToAddr( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETFROMMULSET_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, emEventTypeCnsSend, "删除地址组关系: %d的上级为%d", dwGroupIndex, dwUpGroupIndex );
	NotifyCns();
	return wRet;
}


void CCncAddrbook::BuildEventsMap()
{	
	REG_PFUN(ADDRBOOK_REGISTER_ACK, CCncAddrbook::OnRegister);
	REG_PFUN(ADDRBOOK_REGISTER_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_UNREG_ACK, CCncAddrbook::OnAck);

	REG_PFUN(ADDRBOOK_GETENTRYNUM_ACK, CCncAddrbook::OnGetEntryNum);
	REG_PFUN(ADDRBOOK_GETENTRYNUM_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_GETENTRY_ACK, CCncAddrbook::OnGetEntry);
	REG_PFUN(ADDRBOOK_GETENTRY_NACK, CCncAddrbook::OnNack);

    REG_PFUN(ADDRBOOK_GETMULSETENTRYNUM_ACK, CCncAddrbook::OnGetMulsetEntryNum);
	REG_PFUN(ADDRBOOK_GETMULSETENTRYNUM_NACK, CCncAddrbook::OnNack);
    REG_PFUN(ADDRBOOK_GETMULSETENTRY_ACK, CCncAddrbook::OnGetMulsetEntry);
	REG_PFUN(ADDRBOOK_GETMULSETENTRY_NACK, CCncAddrbook::OnNack);

	REG_PFUN(ADDRBOOK_GETMULSETRELATIONNUM_ACK, CCncAddrbook::OnGetMulsetRelationNum);
	REG_PFUN(ADDRBOOK_GETMULSETRELATIONNUM_NACK, CCncAddrbook::OnNack);         
    REG_PFUN(ADDRBOOK_GETMULSETRELATION_ACK, CCncAddrbook::OnGetMulsetRelation);
	REG_PFUN(ADDRBOOK_GETMULSETRELATION_NACK, CCncAddrbook::OnNack);

	REG_PFUN(ADDRBOOK_REFRESHENTRY_NOTIF, CCncAddrbook::OnRefresh);
	REG_PFUN(ADDRBOOK_DELENTRY_NOTIF, CCncAddrbook::OnDelete);
	REG_PFUN(ADDRBOOK_REFRESHMULSETENTRY_NOTIF, CCncAddrbook::OnRefreshGroup);
    REG_PFUN(ADDRBOOK_DELMULSETENTRY_NOTIF, CCncAddrbook::OnDeleteGroup);
	REG_PFUN(ADDRBOOK_REFRESHMULSETRELATION_NOTIF, CCncAddrbook::OnRefreshRelation);

	REG_PFUN(ADDRBOOK_ADD_ENTRY_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_ADD_ENTRY_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_MODIFYENTRY_ACK, CCncAddrbook::OnAck);
    REG_PFUN(ADDRBOOK_MODIFYENTRY_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_DEL_ENTRY_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_DEL_ENTRY_NACK, CCncAddrbook::OnNack);

	REG_PFUN(ADDRBOOK_ADD_MULSETENTRY_ACK, CCncAddrbook::OnAck);
    REG_PFUN(ADDRBOOK_ADD_MULSETENTRY_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_MODIFYMULSETENTRY_ACK, CCncAddrbook::OnAck);
    REG_PFUN(ADDRBOOK_MODIFYMULSETENTRY_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_DEL_MULSETENTRY_ACK, CCncAddrbook::OnAck);
    REG_PFUN(ADDRBOOK_DEL_MULSETENTRY_NACK, CCncAddrbook::OnNack);

	REG_PFUN(ADDRBOOK_ADD_ENTRYTOMULSET_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_ADD_ENTRYTOMULSET_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_DEL_ENTRYFRMULSET_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_DEL_ENTRYFRMULSET_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_ADD_MULSETTOMULSET_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_ADD_MULSETTOMULSET_NACK, CCncAddrbook::OnNack);
	REG_PFUN(ADDRBOOK_DEL_MULSETFROMMULSET_ACK, CCncAddrbook::OnAck);
	REG_PFUN(ADDRBOOK_DEL_MULSETFROMMULSET_NACK, CCncAddrbook::OnNack);
}


void CCncAddrbook::OnRegister(const CMessage &cMsg)
{
	PrtMsg( ADDRBOOK_REGISTER_ACK, emEventTypeCnsRecv, "注册地址簿成功" );
	
    m_cAddrBook.ClearAddrBook();    //清除原来的地址簿条目
	
	u16 awWaitEvent[2];	
	awWaitEvent[0] = ADDRBOOK_GETENTRYNUM_ACK;
    awWaitEvent[1] = ADDRBOOK_GETENTRYNUM_NACK;
    CAddrBookMsg cAddrMsg;
    BOOL32 bRet = PostCmdToAddr(ADDRBOOK_GETENTRYNUM_REQ, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_GETENTRYNUM_REQ, emEventTypeCnsSend, "开始加载地址簿条目" );
	return;
}


void CCncAddrbook::OnGetEntryNum(const CMessage &cMsg)
{
	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();

	PrtMsg( ADDRBOOK_GETENTRYNUM_ACK, emEventTypeCnsRecv, "地址簿条目: 共%u条", dwNum );
  
    LoadEntries( INVALID_INDEX, dwNum );
}


//加载地址簿条目
void CCncAddrbook::LoadEntries(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
    static u32 s_dwLoaded = 0;
    //当地址簿条目数更新时,dwIndex == INVALID_INDEX,此时付给s_dwCount的条数
    if(dwIndex == INVALID_INDEX)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    
    s32 dwLeft = s_dwCount - s_dwLoaded;
	
    if(dwLeft > 0)	// 一次只能收MAX_GETENTRY_NUM条
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETENTRY_ACK;
        awWaitEvent[1] = ADDRBOOK_GETENTRY_NACK;
		
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETENTRY_NUM ? dwLeft : MAX_GETENTRY_NUM);
        //PostCmdToAddr(ADDRBOOK_GETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);

		PostCmdToAddr( ADDRBOOK_GETENTRY_REQ, cAddrMsg );

		//PrtMsg( ADDRBOOK_GETENTRY_REQ, emEventTypeCnsSend, "地址簿加载: 请求自索引%d, 数目%d",
		//												dwIndex, dwLeft < MAX_GETENTRY_NUM? dwLeft : MAX_GETENTRY_NUM );

		//每加载1000条刷新一次界面
		if ( s_dwLoaded > 0 && ( s_dwLoaded % 1000 == 0 ) )
		{
			PrtMsg( "\n\t刷新地址簿 ： %d \n", s_dwLoaded );
			PostEvent(UI_CNS_ADDRBOOK_CHANGED);
		}
    }
    else
    {
        u16 awWaitEvent[2];
		awWaitEvent[0] = ADDRBOOK_GETMULSETENTRYNUM_ACK;
		awWaitEvent[1] = ADDRBOOK_GETMULSETENTRYNUM_NACK;

		CAddrBookMsg cAddrMsg;
		PostCmdToAddr(ADDRBOOK_GETMULSETENTRYNUM_REQ, cAddrMsg, this, awWaitEvent, 2);

		PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_REQ, emEventTypeCnsSend, "开始加载地址簿组" );
		//PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE,-1);
    }
}


//地址条目更新消息
void CCncAddrbook::OnGetEntry(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRENTRY *pEntry = (TADDRENTRY*)(cAddrMsg.GetMsgBody());
    //添加保存到本地
    for(u32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
		u32 Index = pEntry[nIndex].GetEntryIndex();
        m_cAddrBook.AddAddrEntry( pEntry[nIndex].GetEntryInfo(), pEntry[nIndex].GetEntryIndex() );

		//PrtMsg( ADDRBOOK_GETENTRY_ACK, emEventTypeCnsRecv, "地址簿加载: %s", pEntry[nIndex].GetEntryInfo().achEntryName );
    }

    LoadEntries(pEntry[cAddrMsg.GetEntryNum()-1].GetEntryIndex(), cAddrMsg.GetEntryNum());
}



void CCncAddrbook::OnGetMulsetEntryNum(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();

	PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_ACK, emEventTypeCnsRecv, "地址簿组: 共%u条", dwNum );

    LoadMulsetEntries( INVALID_INDEX, dwNum );
}

//加载地址组
void CCncAddrbook::LoadMulsetEntries(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
	static u32 s_dwLoaded = 0;

    if(dwIndex == INVALID_INDEX)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    u32 dwLeft = s_dwCount - s_dwLoaded;
    if(dwLeft > 0)	// 一次只能收MAX_GETGROUP_NUM条
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETMULSETENTRY_ACK;
        awWaitEvent[1] = ADDRBOOK_GETMULSETENTRY_NACK;
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETGROUP_NUM ? dwLeft : MAX_GETGROUP_NUM);

        PostCmdToAddr( ADDRBOOK_GETMULSETENTRY_REQ, cAddrMsg );

		PrtMsg( ADDRBOOK_GETMULSETENTRY_REQ, emEventTypeCnsSend, "地址簿组加载: 请求自索引%d, 数目%d",
														dwIndex, dwLeft < MAX_GETENTRY_NUM ? dwLeft : MAX_GETENTRY_NUM );
    }
	else
	{
		u16 awWaitEvent[2];
		awWaitEvent[0] = ADDRBOOK_GETMULSETRELATIONNUM_ACK;
		awWaitEvent[1] = ADDRBOOK_GETMULSETRELATIONNUM_NACK;
		
		CAddrBookMsg cAddrMsg;
		PostCmdToAddr(ADDRBOOK_GETMULSETRELATIONNUM_REQ, cAddrMsg, this, awWaitEvent, 2);
		
		PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_REQ, emEventTypeCnsSend, "开始加载地址簿组关系" );

		//PostEvent(UI_CNS_ADDRBOOK_CHANGED);
	}
}


void CCncAddrbook::OnGetMulsetEntry(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRMULTISETENTRY *pEntry = (TADDRMULTISETENTRY*)(cAddrMsg.GetMsgBody());
    for(u32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
        //添加会议组信息
        m_cAddrBook.AddAddrMultiSetEntry(pEntry[nIndex].GetEntryInfo(),
            pEntry[nIndex].GetEntryIndex());
        u32 dwNum = pEntry[nIndex].GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum + 1];
		memset( pdwEntries, 0 , sizeof(int) * (dwNum + 1) );
        pEntry[nIndex].GetListEntryIndex(pdwEntries, dwNum);
        //添加会议组中条目
        for(u32 nEntryIdx=0; nEntryIdx < dwNum; nEntryIdx++)
        {
            m_cAddrBook.AddAddrEntry(pEntry[nIndex].GetEntryIndex(), pdwEntries[nEntryIdx]);
        }
        delete []pdwEntries;

		//PrtMsg( ADDRBOOK_GETMULSETENTRY_ACK, emEventTypeCnsRecv, "地址簿组加载: %s", pEntry[nIndex].GetEntryInfo().achGroupName );
    }

    LoadMulsetEntries( pEntry[cAddrMsg.GetEntryNum()-1].GetEntryIndex(), cAddrMsg.GetEntryNum() );
}


//获取到组关系数量
void CCncAddrbook::OnGetMulsetRelationNum(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();
	
	PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_ACK, emEventTypeCnsRecv, "地址簿组关系: 共%u条", dwNum );
	
    LoadMulsetRelation( 0, dwNum );
}


//加载地址组关系
void CCncAddrbook::LoadMulsetRelation(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
	static u32 s_dwLoaded = 0;
	
    if(dwIndex == 0)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    u32 dwLeft = s_dwCount - s_dwLoaded;
    if(dwLeft > 0)	// 一次只能收MAX_GETGROUPRELATION_NUM条
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETMULSETRELATION_ACK;
        awWaitEvent[1] = ADDRBOOK_GETMULSETRELATION_NACK;
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETGROUPRELATION_NUM ? dwLeft : MAX_GETGROUPRELATION_NUM);
		
        PostCmdToAddr(ADDRBOOK_GETMULSETRELATION_REQ, cAddrMsg, this, awWaitEvent, 2);
    }
	else
	{		
		//加载完毕
		PrtMsg( "\n\t地址簿加载完毕\n" );
		PostEvent(UI_CNS_ADDRBOOK_CHANGED);
	}
}


//地址组关系更新
void CCncAddrbook::OnGetMulsetRelation(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TMultiLevel* pLevel = (TMultiLevel*)(cAddrMsg.GetMsgBody());

    //添加保存到本地
    for(u32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
		m_cAddrBook.AddGroupToGroup( pLevel[nIndex].GetGroupIndex(), pLevel[nIndex].GetUpGroupIndex() );
		
		//PrtMsg( ADDRBOOK_GETMULSETRELATION_ACK, emEventTypeCnsRecv, "地址簿组关系加载: %u的上级是%u", pLevel[nIndex].GetGroupIndex(), pLevel[nIndex].GetUpGroupIndex() );
    }
    LoadMulsetRelation( cAddrMsg.GetEntryIndex() + cAddrMsg.GetEntryNum(), cAddrMsg.GetEntryNum() );
}


void CCncAddrbook::OnRefresh(const CMessage& cMsg)
{	
	PrtMsg( ADDRBOOK_REFRESHENTRY_NOTIF, emEventTypeCnsRecv, "" );

    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRENTRY &entry = *(TADDRENTRY*)cAddrMsg.GetMsgBody();
	
    if(cAddrMsg.GetEntryOptType() == ADD_ENTRY)
    {
        m_cAddrBook.AddAddrEntry(entry.GetEntryInfo(), entry.GetEntryIndex());
		PostEvent( UI_CNS_ADDRBOOK_ADDENTRY, entry.GetEntryIndex(), (LPARAM)entry.GetEntryInfo().achEntryName );
    }
    else
    {
        m_cAddrBook.ModifyAddrEntry(entry.GetEntryIndex(), entry.GetEntryInfo());

		PostEvent( UI_CNS_ADDRBOOK_MODIFY, TRUE, entry.GetEntryIndex() );
    }
    PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}

void CCncAddrbook::OnDelete(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_DELENTRY_NOTIF, emEventTypeCnsRecv, "" );
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);

    u32 dwEntryIndex = cAddrMsg.GetEntryIndex();
    if( dwEntryIndex != MULTI_ENTRY )
    {
        m_cAddrBook.DelAddrEntry( dwEntryIndex );
    }
    else
    {
        int nDelSize = cAddrMsg.GetMsgBodyLen() / sizeof(u32);
        u32 adwDelEntry[MAX_DELENTRY_NUM] = {0};
        memcpy( adwDelEntry, (u32*)cAddrMsg.GetMsgBody(), cAddrMsg.GetMsgBodyLen() );
        for ( int i = 0; i < nDelSize; i++ )
        {
            m_cAddrBook.DelAddrEntry( ntohl(adwDelEntry[i]) );
        }
    }
    
    PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}


void CCncAddrbook::OnRefreshGroup(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_REFRESHMULSETENTRY_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRMULTISETENTRY &tGroupEntry = *(TADDRMULTISETENTRY*)cAddrMsg.GetMsgBody();
    if(cAddrMsg.GetEntryOptType() == ADD_ENTRY)
    {
        TADDRMULTISETENTRY addrtGroupEntry = tGroupEntry;
        m_cAddrBook.AddAddrMultiSetEntry( addrtGroupEntry.GetEntryInfo(), addrtGroupEntry.GetEntryIndex() );
        u32 dwNum = addrtGroupEntry.GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum];
        addrtGroupEntry.GetListEntryIndex( pdwEntries, dwNum );
        for(u32 nIndex = 0; nIndex < dwNum; nIndex++)
        {
            m_cAddrBook.AddAddrEntry(addrtGroupEntry.GetEntryIndex(), pdwEntries[nIndex]);
        }
        delete []pdwEntries;
		PostEvent( UI_CNS_ADDRBOOK_ADDGROUP, addrtGroupEntry.GetEntryIndex(), (LPARAM)addrtGroupEntry.GetEntryInfo().achGroupName );
    }
    else
    {
        TADDRMULTISETENTRY addrtGroupEntry = tGroupEntry;
        u32 dwNum = addrtGroupEntry.GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum];
        addrtGroupEntry.GetListEntryIndex(pdwEntries, dwNum);
        m_cAddrBook.ModifyAddrGroup(addrtGroupEntry.GetEntryIndex(), addrtGroupEntry.GetEntryInfo(),
            (u8)dwNum, pdwEntries);
        delete []pdwEntries;
		PostEvent( UI_CNS_ADDRBOOK_MODIFY, FALSE, addrtGroupEntry.GetEntryIndex() );
    }
    PostEvent( UI_CNS_ADDRBOOK_CHANGED, FALSE, tGroupEntry.GetEntryIndex() );
}

void CCncAddrbook::OnDeleteGroup(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_DELMULSETENTRY_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);

    u32 dwGroupIndex = cAddrMsg.GetEntryIndex();
    if( dwGroupIndex != MULTI_ENTRY )
    {
        m_cAddrBook.DelAddrMultiSetEntry( dwGroupIndex );
    }
    else
    {
        int nDelSize = cAddrMsg.GetMsgBodyLen() / sizeof(u32);
        u32 adwDelEntry[MAX_DELENTRY_NUM] = {0};
        memcpy( adwDelEntry, (u32*)cAddrMsg.GetMsgBody(), cAddrMsg.GetMsgBodyLen() );
        for ( int i = 0; i < nDelSize; i++ )
        {
            m_cAddrBook.DelAddrMultiSetEntry( ntohl(adwDelEntry[i]) );
        }
    }

    PostEvent( UI_CNS_ADDRBOOK_CHANGED, TRUE );
}

void CCncAddrbook::OnRefreshRelation(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_REFRESHMULSETRELATION_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
	//网络序转主机序
	u32 dwGroupIndex = *(u32*)cAddrMsg.GetMsgBody();
	dwGroupIndex = ntohl( dwGroupIndex );
	u32 dwUpGroupIndex = *(u32*)( cAddrMsg.GetMsgBody() + sizeof(u32) );
	dwUpGroupIndex = ntohl( dwUpGroupIndex );
	if ( cAddrMsg.GetEntryOptType() == ADD_ENTRY )
	{
		m_cAddrBook.AddGroupToGroup( dwGroupIndex, dwUpGroupIndex );
	}
	else
	{
		m_cAddrBook.DeleteGroupFromGroup( dwGroupIndex, dwUpGroupIndex );
	}
	PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}


void CCncAddrbook::OnAck(const CMessage& cMsg)
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetAddrBookMsg( cMsg.content, cMsg.length );
	u16 wCmd = 0;
	switch( cMsg.event ) 
	{
	case ADDRBOOK_REGISTER_ACK:			
		wCmd = ADDRBOOK_REGISTER_REQ;
		PrtMsg( ADDRBOOK_REGISTER_ACK, emEventTypeCnsRecv, "注册地址簿成功" );
		break;
	case ADDRBOOK_UNREG_ACK:
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_UNREG_ACK, emEventTypeCnsRecv, "注销地址簿成功" );
		break;
    case ADDRBOOK_SAVE_ACK:				
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_SAVE_ACK, emEventTypeCnsRecv, "地址簿保存成功" );
		break;
    case ADDRBOOK_ADD_ENTRY_ACK:			
		wCmd = ADDRBOOK_ADD_ENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRY_ACK, emEventTypeCnsRecv, "添加地址条目成功" );
		break;
    case ADDRBOOK_MODIFYENTRY_ACK:			
		wCmd = ADDRBOOK_MODIFYENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYENTRY_ACK, emEventTypeCnsRecv, "修改地址条目成功" );
		break;
    case ADDRBOOK_DEL_ENTRY_ACK:			
		wCmd = ADDRBOOK_DEL_ENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRY_ACK, emEventTypeCnsRecv, "删除地址条目成功" );
		break;
    case ADDRBOOK_ADD_MULSETENTRY_ACK:		
		wCmd = ADDRBOOK_ADD_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_MULSETENTRY_ACK, emEventTypeCnsRecv, "添加组成功" );
		break;
    case ADDRBOOK_MODIFYMULSETENTRY_ACK:	
		wCmd = ADDRBOOK_MODIFYMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_ACK, emEventTypeCnsRecv, "修改组成功" );
		break;
    case ADDRBOOK_DEL_MULSETENTRY_ACK:		
		wCmd = ADDRBOOK_DEL_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_MULSETENTRY_ACK, emEventTypeCnsRecv, "删除组成功" );
		break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_ACK:
		wCmd = ADDRBOOK_ADD_ENTRYTOMULSET_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_ACK, emEventTypeCnsRecv, "添加地址条目到组成功" );
		break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_ACK:	
		wCmd = ADDRBOOK_DEL_ENTRYFRMULSET_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_ACK, emEventTypeCnsRecv, "从组中删除地址条目成功" );
		break;
	case ADDRBOOK_ADD_MULSETTOMULSET_ACK:
		PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_ACK, emEventTypeCnsRecv, "添加组关系成功" );
		break;
	case ADDRBOOK_DEL_MULSETFROMMULSET_ACK:
		PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_ACK, emEventTypeCnsRecv, "删除组关系成功" );
		break;
    default:
		wCmd = 0;
		break;
	}
//	PostEvent( MTC_UI_CMD_SUCCESS, wCmd );
}

void CCncAddrbook::OnNack(const CMessage& cMsg)
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetAddrBookMsg( cMsg.content, cMsg.length );
	u16 wCmd = 0;
	switch(cMsg.event)
    {
    case ADDRBOOK_REGISTER_NACK:			
		wCmd = ADDRBOOK_REGISTER_REQ;
		PrtMsg( ADDRBOOK_REGISTER_NACK, emEventTypeCnsRecv, "注册地址簿失败" );
		break;
	case ADDRBOOK_UNREG_NACK:
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_UNREG_NACK, emEventTypeCnsRecv, "注销地址簿失败" );
		break;
    case ADDRBOOK_SAVE_NACK:				
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_SAVE_NACK, emEventTypeCnsRecv, "地址簿保存失败" );
		break;
    case ADDRBOOK_ADD_ENTRY_NACK:			
		wCmd = ADDRBOOK_ADD_ENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRY_NACK, emEventTypeCnsRecv, "添加地址条目失败" );
		break;
    case ADDRBOOK_MODIFYENTRY_NACK:			
		wCmd = ADDRBOOK_MODIFYENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYENTRY_NACK, emEventTypeCnsRecv, "修改地址条目失败" );
		break;
    case ADDRBOOK_DEL_ENTRY_NACK:		
		wCmd = ADDRBOOK_DEL_ENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRY_NACK, emEventTypeCnsRecv, "删除地址条目失败" );
		break;
    case ADDRBOOK_ADD_MULSETENTRY_NACK:		
		wCmd = ADDRBOOK_ADD_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_MULSETENTRY_NACK, emEventTypeCnsRecv, "添加组失败" );
		break;
    case ADDRBOOK_MODIFYMULSETENTRY_NACK:	
		wCmd = ADDRBOOK_MODIFYMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_NACK, emEventTypeCnsRecv, "修改组失败" );
		break;
    case ADDRBOOK_DEL_MULSETENTRY_NACK:	
		wCmd = ADDRBOOK_DEL_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_MULSETENTRY_NACK, emEventTypeCnsRecv, "删除组失败" );
		break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_NACK:	
		wCmd = ADDRBOOK_ADD_ENTRYTOMULSET_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_NACK, emEventTypeCnsRecv, "添加地址条目到组失败" );
		break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_NACK:
		wCmd = ADDRBOOK_DEL_ENTRYFRMULSET_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_NACK, emEventTypeCnsRecv, "从组中删除地址条目失败" );
		break;
    case ADDRBOOK_GETENTRYNUM_NACK:			
		wCmd = ADDRBOOK_GETENTRYNUM_REQ;
		PrtMsg( ADDRBOOK_GETENTRYNUM_NACK, emEventTypeCnsRecv, "获取地址条目个数失败" );
		break;
    case ADDRBOOK_GETENTRY_NACK:		
		wCmd = ADDRBOOK_GETENTRY_REQ;
		PrtMsg( ADDRBOOK_GETENTRY_NACK, emEventTypeCnsRecv, "获取地址条目失败" );
		break;
    case ADDRBOOK_GETMULSETENTRYNUM_NACK:	
		wCmd = ADDRBOOK_GETMULSETENTRYNUM_REQ;
		PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_NACK, emEventTypeCnsRecv, "获取组个数失败" );
		break;
    case ADDRBOOK_GETMULSETENTRY_NACK:	
		wCmd = ADDRBOOK_GETMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_GETMULSETENTRY_NACK, emEventTypeCnsRecv, "获取组信息失败" );
		break;
	case ADDRBOOK_GETMULSETRELATIONNUM_NACK:
		wCmd = ADDRBOOK_GETMULSETRELATIONNUM_REQ;
		PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_NACK, emEventTypeCnsRecv, "获取组关系个数失败" );
		break;
	case ADDRBOOK_GETMULSETRELATION_NACK:
		wCmd = ADDRBOOK_GETMULSETRELATION_REQ;
		PrtMsg( ADDRBOOK_GETMULSETRELATION_NACK, emEventTypeCnsRecv, "获取组关系失败" );
		break;
	case ADDRBOOK_ADD_MULSETTOMULSET_NACK:
		PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_NACK, emEventTypeCnsRecv, "添加组关系失败" );
		break;
	case ADDRBOOK_DEL_MULSETFROMMULSET_NACK:
		PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_NACK, emEventTypeCnsRecv, "删除组关系失败" );
		break;
    default:
		wCmd = 0;
		break;
    }
    u32 dwError = ntohl(*(u32*)cAddrMsg.GetMsgBody());
	PostEvent( UI_CNS_ADDRBOOKOPT_FAILED, wCmd, dwError );
}


void CCncAddrbook::OnLinkBreak( u32 dwNodeId )
{
	ClearWaiting();	// OSP断链后,尚未执行完的命令中断执行 
	ClearAllCommand(); // 清空所有在队列中等待执行的命令
    g_AddrBookApp.ClearOspMsg();  
    
    //与cns断链，但与tpad未断链，不将NodeId置空
    if ( dwNodeId == g_AddrBookApp.GetNodeId() )
    {
        g_AddrBookApp.SetNodeId(INVALID_NODE);
    }

    m_cAddrBook.ClearAddrBook();
	m_bAddrLoading = FALSE;

    PrtMsg( "\n\t[CCncAddrbook::OnLinkBreak]清空地址簿信息\n" );
}


u16 CCncAddrbook::InitializeAddrOsp()
{
	char szOspApp[] = "CncAddrbook";
	u32 dwPrior = 180; //优先级调低
	int nRet = g_AddrBookApp.CreateApp(&szOspApp[0], AID_CNCADDRBOOK_APP,(u8)dwPrior, 300, 1024);
	ASSERT(nRet == 0);

	PrtMsg( "AID_CNCADDRBOOK_APP 启动成功\n" );
    
    return NO_ERROR;
}

void CCncAddrbook::NotifyCns()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_cncAddrBookNty ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);	

	if ( 0 == wRet )
	{
		PrtMsg( ev_cns_cncAddrBookNty, emEventTypeCnsSend , "通知cns重新计算待机时间\n" );
	} 
	else
	{
		PrtMsg( ev_cns_cncAddrBookNty, emEventTypeCnsSend , "通知cns重新计算待机时间失败！\n" );
	}
}

BOOL CCncAddrbook::GetAddrLoadingState()
{
	return m_bAddrLoading;
}

void CCncAddrbook::SetAddrLoadingState(BOOL bAddrLoading)
{
	m_bAddrLoading = bAddrLoading;
}