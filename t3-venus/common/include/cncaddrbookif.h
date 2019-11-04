// cncaddrbookif.h: interface for the CCncAddrbookIF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCADDRBOOKIF_H__F143B4A9_10C5_4BE6_9966_DB271533149A__INCLUDED_)
#define AFX_CNCADDRBOOKIF_H__F143B4A9_10C5_4BE6_9966_DB271533149A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvdispevent.h"
#include "addrbook.h"
#include <vector>

class CCncAddrbookIF : public CKdvDispEvent  
{
public:

	/** 获取地址簿对象 
	 *  @return 地址簿对象
	 *  @remarks 
	 */
	virtual CAddrBook& GetAddrBook() = 0;

	/** 功能  增删改条目（或组） 
	 *  @param[in] entry 条目
	 *  @param[in] group 组
	 *  @param[in] dwIndex	条目（或组）的索引
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks ModifyGroup并不能修改其中包含的条目列表,要修改条目列表使用AddEntryToGroup和DelEntryFromGroup
	 */
 	virtual u16 AddEntry( const CAddrEntry& entry ) = 0;

 	virtual u16 ModifyEntry( const CAddrEntry& entry ) = 0;

 	virtual u16 DeleteEntry( u32 dwIndex ) = 0;

	virtual u16 AddGroup( const CAddrMultiSetEntry& group ) = 0;

	virtual u16 ModifyGroup( const CAddrMultiSetEntry& group ) = 0;

	virtual u16 DeleteGroup( u32 dwIndex ) = 0;

    virtual u16 DeleteMultiEntry( vector<u32> vctEntry ) = 0;

    virtual u16 DeleteMultiGroup( vector<u32> vctGroup ) = 0;

	/** 功能  修改条目组中的条目 
	 *  @param[in] tGroupEntry 其中包含条目组列表
	 *  @return 成功返回0,失败返回非0错误码
	 */
	virtual u16 AddEntryToGroup(const TADDRMULTISETENTRY& tGroupEntry) = 0;
	virtual u16 DelEntryFromGroup(const TADDRMULTISETENTRY& tGroupEntry) = 0;

	/** 功能  增加/删除条目组关系 
	 *  @param[in] dwGroupIndex 组索引
	 *  @param[in] dwGroupIndex 上级组索引
	 *  @return 成功返回0,失败返回非0错误码
	 */
	virtual u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex ) = 0;
	virtual u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex ) = 0;

	/*函数名： AddCallOutEntryCmd
    功    能：增加呼出记录   
    参    数： 
    返 回 值： virtual u16
    说    明： 此消息发送给终端处理，不发送到地址簿*/
	//virtual u16  AddCallOutEntryCmd(const TAddrEntry& tAddrEntry)=0;  

	virtual BOOL GetAddrLoadingState() = 0;
	virtual void SetAddrLoadingState(BOOL bAddrLoading) = 0;

};

#endif // !defined(AFX_CNCADDRBOOKIF_H__F143B4A9_10C5_4BE6_9966_DB271533149A__INCLUDED_)
