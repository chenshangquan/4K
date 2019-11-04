#ifndef __IMTCP2PCONF_H__
#define __IMTCP2PCONF_H__

#include "dispevent.h"
#include "mtcmt.h"
//#include "mtctrllib.h"

class IMtcP2PConf : public CDispEvent
{
public:
	/*功能	是否正在点对点会议中
	参数	pMt	返回参数，若在点对点会议中，则在*pMt中填充与会的另一个终端
	返回值	TRUE	正在点对点会议中
			FALSE	不在点对点会议中
	说明	无*/
	virtual BOOL IsInP2PConf(CMtcMt *pMt) const = 0;
	/*功能	是否正在呼叫其它终端
	参数	pMt	返回参数，若正在呼叫其它终端，则在*pMt中填充被呼叫的终端
	返回值	TRUE	正在呼叫其它终端
			FALSE	没在呼叫其它终端
	说明	无*/
	virtual BOOL IsCalling(CMtcMt *pMt) const = 0;
	/*功能	呼叫其他终端
	参数	const TMtAddr& tMtAddr		终端的地址
			u16 wCallRate				呼叫的速率
	返回值	成功返回0
	说明	无*/
	virtual u16 MakeCall(const TMtAddr& tMtAddr, u16 wCallRate = 768) = 0;
	/*功能	从地址簿呼叫其他终端,并向终端添加呼出记录
	参数	const TMtAddr& tMtAddr		   [in]     终端的地址
			u16 wCallRate				   [in]     呼叫的速率
			const CString& strEntryName    [in]     从地址簿呼叫时的条目名称

	返回值	成功返回0
	说明	无*/
	virtual u16 MakeCall(const TMtAddr& tMtAddr,const CString& strEntryName,u16 wCallRate = 768) = 0;

	/*功能	回答呼叫
	参数	无
	返回值	成功返回0;失败返回错误码
	说明	*/
	virtual u16 Accept(BOOL32 bAccept) = 0;
	/*功能	取消呼叫
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	如果已在会议中,又有呼叫进入,使用Reject拒绝新呼叫*/
	virtual u16 CancelCalling() = 0;
	/*功能	结束点对点会议
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	若已扩展为多点会议，不能用此方法结束会议*/
	virtual u16 EndP2PConf() = 0;
	/*功能	是否主终端
	参数	无
	返回值	TRUE	主终端
			FALSE	从终端
	说明	主终端可以扩展点对点会议到多点会议*/
	virtual BOOL IsMasterMt() const = 0;
	/*功能	接受新呼叫而使会议扩展
	返回值	成功返回0;失败返回非0错误码
	说明	拥有会议扩展能力才会发生作用*/
	virtual u16 AcceptEx() = 0;
    /*功能	发送短消息
	返回值	成功返回0;失败返回非0错误码
	说明	*/
	virtual u16 SendShortMessage(const CString &strMsg, EmSMSType emType = emSMSSingleLine,
		 u8 byRollSpeed = 3, u8 byTimes=1) = 0;
    /*功能	点对点会议中获取对端终端类型
	返回值	EmMtModel
	说明	*/
	virtual EmMtModel& GetOtherMtModelInP2P() = 0;	
	/*功能	点对点会议中将序列号发送给对端终端
	返回值	void
	说明	*/
//	virtual void SendSerialNumber(const CString &strSerialNumber) = 0;

	/*功能	点对点会议中发送给对端数据会议请求
	返回值	void
	说明	*/
	virtual u16  SendPcmtDataConfReq() = 0;

	/*功能	点对点会议中发送给对端数据会议回应
	返回值	void
	说明	*/
	virtual u16  SendPcmtDataConfRsp(BOOL bAccept) = 0;
}; // IMtcP2PConf

#endif