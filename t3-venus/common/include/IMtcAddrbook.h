#ifndef __IMTCADDRBOOK_H__
#define __IMTCADDRBOOK_H__

#include "dispevent.h"
#include "Addrbook.h"		// 地址簿业务

class IMtcAddrbook : public CDispEvent
{
public:
	/*功能	返回地址簿对象
	参数	无
	返回值	地址簿对象
	说明	参见潘越峰的addrbook.h*/
	virtual CAddrBook& GetAddrBook() = 0;
	/*功能	增删改条目（或组）
	参数	entry	条目
			group	组
			dwIndex	条目（或组）的索引
	返回值	成功返回0;失败返回非0错误码
	说明	ModifyGroup并不能修改其中包含的条目列表,要修改条目列表使用
			AddEntryToGroup和DelEntryFromGroup*/
	virtual u16 AddEntry(const CAddrEntry& entry) = 0;
	virtual u16 ModifyEntry(const CAddrEntry& entry) = 0;
	virtual u16 DeleteEntry(u32 dwIndex) = 0;
	virtual u16 AddGroup(const CAddrMultiSetEntry& group) = 0;
	virtual u16 ModifyGroup(const CAddrMultiSetEntry& group) = 0;
	virtual u16 DeleteGroup(u32 dwIndex) = 0;
	/*功能	修改条目组中的条目
	参数	tGroupEntry	其中包含条目组列表
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 AddEntryToGroup(const TADDRMULTISETENTRY& tGroupEntry) = 0;
	virtual u16 DelEntryFromGroup(const TADDRMULTISETENTRY& tGroupEntry) = 0;

	/*功能	地址簿上传结束
	参数	const CString strFilePath   [in]     上传文件保存路径
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 UploadAddrbook(const CString &strFilePath) = 0;
	/*函数名： AddCallOutEntryCmd
    功    能：增加呼出记录   
    参    数： 
    返 回 值： virtual u16
    说    明： 此消息发送给终端处理，不发送到地址簿*/
	virtual u16   AddCallOutEntryCmd(const TAddrEntry& tAddrEntry)=0;    

}; // IMtcAddrbook

#endif