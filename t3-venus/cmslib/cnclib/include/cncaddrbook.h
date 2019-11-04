// cncaddrbook.h: interface for the CCncAddrbook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCADDRBOOK_H__75FD17B1_ACC3_4C6C_98A5_CDA7E342CF0F__INCLUDED_)
#define AFX_CNCADDRBOOK_H__75FD17B1_ACC3_4C6C_98A5_CDA7E342CF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"
#include "addrmsgdriver.h"

class CCncAddrbook : public CCncAddrbookIF, 
					 public CAddrMsgDriver  
{
public:
	CCncAddrbook(CCnsSession &cSession);
	virtual ~CCncAddrbook();

    virtual CAddrBook& GetAddrBook();
    virtual u16 AddEntry(const CAddrEntry& entry);
    virtual u16 ModifyEntry(const CAddrEntry& entry);
    virtual u16 DeleteEntry(u32 dwIndex);
    virtual u16 AddGroup(const CAddrMultiSetEntry& group);
    virtual u16 ModifyGroup(const CAddrMultiSetEntry& group);
    virtual u16 DeleteGroup(u32 dwIndex);
    virtual u16 AddEntryToGroup(const TADDRMULTISETENTRY& tGroupEntry);     
	virtual u16 DelEntryFromGroup(const TADDRMULTISETENTRY& tGroupEntry);
	virtual u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );
	virtual u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	virtual u16 DeleteMultiEntry( vector<u32> vctEntry );
	virtual u16 DeleteMultiGroup( vector<u32> vctGroup );

	virtual BOOL GetAddrLoadingState();
	virtual void SetAddrLoadingState(BOOL bAddrLoading);
	
    // 请求(或注销)地址簿服务
    u16 RegAddrBook();
    u16 UnRegAddrBook();

	u16 PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg, CKdvDispEvent *pDispEvent,
		u16 *pwEventTab, s32 nEventNum = 1, u32 dwTimeOut = 1500);
	u16 PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg);

	//断链响应
	void OnLinkBreak( u32 dwNodeId );
	//启动地址簿app
	u16 InitializeAddrOsp();

protected:
	virtual void DispEvent(const CMessage &cMsg);
	virtual void OnTimeOut(u16 wEvent);
	void BuildEventsMap();

	void OnRegister(const CMessage &cMsg);
	void OnGetEntryNum(const CMessage &cMsg);
	void OnGetEntry(const CMessage &cMsg);
	void OnGetMulsetEntryNum(const CMessage &cMsg);
	void OnGetMulsetEntry(const CMessage &cMsg);
	void OnGetMulsetRelationNum(const CMessage &cMsg);
	void OnGetMulsetRelation(const CMessage &cMsg);
	void OnRefresh(const CMessage &cMsg);
	void OnDelete(const CMessage& cMsg);
	void OnRefreshGroup(const CMessage& cMsg);
	void OnDeleteGroup(const CMessage& cMsg);
	void OnRefreshRelation(const CMessage& cMsg);
	void OnAck(const CMessage &cMsg);
	void OnNack(const CMessage &cMsg);

    void LoadEntries(u32 dwIndex, u32 dwNum);
    void LoadMulsetEntries(u32 dwIndex, u32 dwNum);
	void LoadMulsetRelation(u32 dwIndex, u32 dwNum);

	//通知cns重新计算待机时间  xhx
	void NotifyCns();    

private:
	CCnsSession    *m_pSession;
	CAddrBook       m_cAddrBook;   // 地址簿本地缓冲
	BOOL            m_bAddrLoading;    // 是否正在从全局地址簿中导入 by xhx
};

#endif // !defined(AFX_CNCADDRBOOK_H__75FD17B1_ACC3_4C6C_98A5_CDA7E342CF0F__INCLUDED_)
