
#ifndef _PA_CALL_EVENT_H_
#define _PA_CALL_EVENT_H_
#include "protocaladapter.h"
enum EmPACall
{
	emPACallBegin = OSP_USEREVENT_BASE + 100,
/***********************<< 建立呼叫  >>************************
 *[消息体]			 
 *  + TDialParam
 *
 *[消息方向]
 *    UI        => MtService
 *    MtService => 323/320/sip
 */
	ev_MakeCallCmd,  //TDialParam


/***********************<< 呼叫正在处理指示  >>************************
 *[消息体]			 
 *  无
 *
 *[消息方向]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallProccedingInd,

/***********************<< 建立进入  >>************************
 *[消息体]			 
 *  + TDialParam
 *
 *[消息方向]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallIncomingInd,//TDialParam



/***********************<< 呼叫建立成功  >>************************
 *[消息体]			 
 *  无消息体
 *
 *[消息方向]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallConnectedInd,



/***********************<< 接受呼叫指示  >>************************
 *[消息体]			 
 *  + BOOL  TRUE=接受呼叫  FALSE=拒绝呼叫  
 *
 *[消息方向]
 *
 *    MtService => 323/320/sip
 */
	ev_CallAcceptInd,//BOOL



/***********************<< 呼叫挂断指示  >>************************
 *[消息体]			 
 *  +u8  byReason	挂断原因
 *
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallDisconnectedInd,//EmCallDisconnectReason

 
/***********************<< 挂断呼叫  >>************************
 *[消息体]			 
 *  +u8  byReason	挂断原因
 *
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallHangupCmd,//u8

/***********************<< 能力集通知  >>************************
 *[消息体]			 
 *  
 *
 *[消息方向]
 *
 *    MtService <=> sip
 */
   ev_CallCapbility,
/***********************<< 存活超时指示  >>************************
 *[消息体]			 
 *  +u32
 *
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallKeepLiveTimeOutInd,//u32









 /***********************<< 开始双流命令  >>************************
 *[消息体]			 
 *  +EmMtVideoPort  
 *  +BOOL             TRUE=开始 FALSE =停止
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_DualVideoCmd,//EmMtVideoPort BOOL





/***********************<< 开始双流命令  >>************************
 *[消息体]			 
 *  +EmMtVideoPort  
 *  +BOOL             TRUE=开始 FALSE =停止
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_DualVideoInd,//EmMtVideoPort  BOOL

/***********************<< 通道状态改变 >>************************	
 *[消息体]		 
 * EmChanType 
 * BOOL       
 *[消息方向]
 *    UI => MtService
 */
	ev_ChannelStatusChanged,//EmChanType BOOL

/***********************<< 会议是否加密指示 >>************************	
 *[消息体]		 
 *  +BOOL  //是否加密
 *[消息方向]
 *    MtService => UI
 */
	ev_CallEncryptInd ,//BOOL 

/***********************<< 接收双流指示  >>************************
 *[消息体]
 *  +BOOL             TRUE=开始 FALSE =停止
 *[消息方向]
 *
 *    MtService <=> 323/320/sip
 */
	ev_RecvDualVideoInd,//BOOL
	ev_StopDualVideoCmd,
   
/***********************<< 组播模式地址指示  >>************************
 *[消息体]
 * +TIPTransAddr     音频接收地址
 * +TIPTransAddr     第一路视频接收地址
 * +TIPTransAddr     第二路视频接收地址
 *[消息方向]
 *
 *    MtService <= 323/320/sip
 */
	ev_MulticastModeAddrInd,//TIPTransAddr*3   )


	/***********************<< 会议建立超时消息   >>************************
	*[消息体]			 
	*  无
	*
	*[消息方向]
	*    MtH323Service 内部
	*  该消息在呼叫建立后设置定时，在超时的时间内未成功打开通道
	*/
	ev_InnerConfEstablishTimeOut,
	
	/***********************<< 会议建立超时消息   >>************************
	*[消息体]			 
	*  无
	*
	*[消息方向]
	*    MtH323Service 内部
	*  该消息表示已经打开音频接收信道可以进入对话模式
	*/
	ev_InnerConfStartInd,
	
	/***************<< 发送RoundTripDelay消息指示   >>***********************
	*[消息体]			 
	*  无
	*
	*[消息方向]
	*    MtH323Service 内部
	*  该消息表示已经打开音频接收信道可以进入对话模式
	*/
//	ev_InnerSendRoundTripDelayInd,
	
 
	ev_SipRegisterReq,
	ev_SipUnRegisterReq,
	ev_SipRegisterResultInd,
	ev_SipGetRegReq,
	
	ev_SipFastUpdate,
	ev_SipFlowCtrl,
	ev_ConfCtrl,
	ev_SendDual,
	ev_AnswerDual,
	ev_StopDual,
};
typedef s32 (PA_CALLBACK* CBSipCallConnected)( const s32 nAppId, const s32 nCallId, CPACapSet *ptPACapSet, TPADialParam *ptPADial );
typedef s32 (PA_CALLBACK* CBSipChannelConnected)( const s32 nAppId, const s32 nCallId, CPACapMap *pCapMap, const s32 nArraySize );
typedef s32 (PA_CALLBACK* CBSipChannelDisConnect)( const s32 nAppId, const s32 nCallId, const s32 nChannelId, EmPAChannelReason emChannelReason );
typedef s32 (PA_CALLBACK* CBSipCallIncoming)( const s32 nCallId, TPADialParam *ptPADialParam );
typedef s32 (PA_CALLBACK* CBSipCallDisconnect)( const s32 nAppId, const s32 nCallId, const EmPACallDisconnectReason EmReason );
typedef s32 (PA_CALLBACK* CBSipRegister)( const s32 nAppId, void *pRegHandle, EmRegResult emPARegResult );
typedef s32 (PA_CALLBACK* CBSipUnRegister)( const s32 nAppId, EmRegResult emPARegResult, const u8 *pBuf, const s32 nLen);
typedef s32 (PA_CALLBACK* CBSipChanCtrl)( const s32 nAppId, const s32 nCallId, const s32 nChannelId, const s32 nMsgType, const u8 *pBuf, const s32 nSize );
typedef s32 (PA_CALLBACK* CBSipConfCtrl)( const s32 nAppId, const s32 nCallId, const s32 nMsgType, const u8 *pBuf, const s32 nSize );
typedef s32 (PA_CALLBACK* CBSipDualIncoming)( const s32 nAppId, const s32 nCallId, TPACascadeInfo *ptPACas );
typedef s32 (PA_CALLBACK* CBSipDualConnected)( const s32 nAppId, const s32 nCallId, CPACapMap *pDualCapMap, const s32 nArraySize, TPACascadeInfo *ptPACas );

typedef s32 (PA_CALLBACK* CBSipDualDisconnect)( const s32 nAppId, const s32 nCallId, s32 *pChannelId, const s32 nChannelSize, const EmPAChannelReason EmReason );

typedef s32 (PA_CALLBACK* CBSipInitStackRes)(const EmPAInitSipStackRes emPAStackRes); //回调初始化协议栈结果
typedef s32 (PA_CALLBACK* CBSipGetRegInfoAck)(s32 nAppid, const u8 *pBuf, const s32 nLen);

typedef struct tagSipServiceEvent
{
	CBSipCallConnected cbSipCallConnected;
	CBSipCallIncoming  cbSipCallIncoming;
	CBSipCallDisconnect cbSipCallDisconnect;
	CBSipRegister		cbSipRegister;
	CBSipUnRegister     cbSipUnRegister;
	CBSipChanCtrl          cbSipChanCtrl;
	CBSipConfCtrl		cbSipConfCtrl;
	CBSipDualIncoming   cbSipDualIncoming;
	CBSipDualConnected  cbSipDualConnected;
	CBSipDualDisconnect cbSipDualDisconnect;
	CBSipChannelConnected cbSipChannelConnected;
	CBSipChannelDisConnect cbSipChannelDisConnect;
	CBSipInitStackRes   cbSipInitStackRes;
	CBGetRegInfoAck     cbGetRegInfoAck;
	tagSipServiceEvent()
	{
		memset(this, 0, sizeof(tagSipServiceEvent) );
	}
}TSipServiceEvent;
extern TSipServiceEvent g_tSipServiceEvent;
inline void SetSipServiceEvent( const TSipServiceEvent & tSipServiceEvent )
{
	g_tSipServiceEvent.cbSipCallConnected = tSipServiceEvent.cbSipCallConnected;
	g_tSipServiceEvent.cbSipCallIncoming = tSipServiceEvent.cbSipCallIncoming;
	g_tSipServiceEvent.cbSipCallDisconnect = tSipServiceEvent.cbSipCallDisconnect;
	g_tSipServiceEvent.cbSipRegister = tSipServiceEvent.cbSipRegister;
	g_tSipServiceEvent.cbSipUnRegister = tSipServiceEvent.cbSipUnRegister;
	g_tSipServiceEvent.cbSipChanCtrl = tSipServiceEvent.cbSipChanCtrl;
	g_tSipServiceEvent.cbSipDualIncoming = tSipServiceEvent.cbSipDualIncoming;
	g_tSipServiceEvent.cbSipDualConnected = tSipServiceEvent.cbSipDualConnected;
	g_tSipServiceEvent.cbSipDualDisconnect = tSipServiceEvent.cbSipDualDisconnect;
	g_tSipServiceEvent.cbSipChannelConnected = tSipServiceEvent.cbSipChannelConnected;
	g_tSipServiceEvent.cbSipChannelDisConnect = tSipServiceEvent.cbSipChannelDisConnect;
	g_tSipServiceEvent.cbSipConfCtrl = tSipServiceEvent.cbSipConfCtrl;
	g_tSipServiceEvent.cbSipInitStackRes = tSipServiceEvent.cbSipInitStackRes;
	g_tSipServiceEvent.cbGetRegInfoAck = tSipServiceEvent.cbGetRegInfoAck;
}
inline TSipServiceEvent *GetSipServiceEvent()
{
	return &g_tSipServiceEvent;
}
#endif

