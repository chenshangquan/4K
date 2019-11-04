/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        h323confstdmsg.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Conference messages for H323 protocol 
*   @details     
*/
#ifndef _H323CONFSTDMSG_H
#define _H323CONFSTDMSG_H

/**H245 Ctrl Msg Type*/
enum H245CtrlMsgType 
{
	/************************h.245 Standard**************************/
	h_ctrl_MultipointConference				= 7,      /**<开始多点会议指示  MC->ter, Master->slave,   [incoming]&[outgoing]: NULL*/
	h_ctrl_CancelMultipointConference		= 8,      /**<取消多点会议指示  MC->ter, Master->slave,   [outgoing]: NULL*/
		
	h_ctrl_communicationModeCommand			= 9,      /**<会议模式命令	    MC->ter,   [incoming]&[outgoing]: [TCOMMODEINFO[]],目前不使用*/
	//10	
	h_ctrl_enterH243Password				= 10,	  /**<MC询问会议密码    MC->ter,   [incoming]&[outgoing]: NULL*/
	h_ctrl_passwordResponse					= 11,	  /**<终端回答密码	    ter->MC,   [incoming]&[outgoing]: [TPassRsp]*/
	h_ctrl_terminalNumberAssign				= 12,     /**<分配终端编号	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_terminalListRequest				= 13,     /**<请求终端列表	    ter->MC,   [incoming]&[outgoing]: NULL*/
	h_ctrl_terminalListResponse				= 14,     /**<回答终端列表	    MC->ter,   [incoming]&[outgoing]: [TTERLABEL[]]*/
	h_ctrl_requestTerminalID				= 15,     /**<ter询问终端名	    ter->MC,   [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_mCTerminalIDResponse				= 16,     /**<MC回答终端名	    MC->ter,   [incoming]&[outgoing]: [TTERINFO]*/
	h_ctrl_enterH243TerminalID				= 17,	  /**<MC询问终端名	    MC->ter,   [incoming]&[outgoing]: NULL*/
	h_ctrl_terminalIDResponse				= 18,     /**<ter回答终端名	    ter->MC,   [incoming]&[outgoing]: [TTERINFO]*/
	h_ctrl_requestAllTerminalIDs			= 19,     /**<ter请求所有终端名 ter->MC,   [incoming]&[outgoing]: NULL*/
	h_ctrl_requestAllTerminalIDsResponse	= 20,     /**<回答所有终端名字	MC->ter,   [incoming]&[outgoing]: [TTERINFO[]]*/
	h_ctrl_terminalJoinedConference			= 21,     /**<终端加入会议		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_terminalLeftConference			= 22,     /**<终端退出会议		MC->ter,   [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_dropTerminal						= 23,     /**<强制终端退出		chair->MC, [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_terminalDropReject				= 24,     /**<强制终端退出失败	MC->chair, [incoming]&[outgoing]: NULL	*/
	h_ctrl_dropConference					= 25,     /**<结束会议 chair->MC,MC->ter,  [incoming]&[outgoing]: NULL*/
	//26
	h_ctrl_requestForFloor					= 26,     /**<申请发言			ter->MC,   [incoming]&[outgoing]: NULL*/
	h_ctrl_floorRequested					= 27,     /**<发言申请			MC->chair, [incoming]&[outgoing]: [TTERLABEL]*/
	h_ctrl_makeTerminalBroadcaster			= 28,     /**<广播终端			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]*/
	h_ctrl_makeTerminalBroadcasterResponse	= 29,	  /**<广播应答			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]*/
	h_ctrl_cancelMakeTerminalBroadcaster	= 30,	  /**<取消广播			chair->MC, [incoming]&[outgoing]: NULL*/
	h_ctrl_seenByAll						= 31,     /**<广播源指示		MC->ter,   [incoming]&[outgoing]: NULL*/
	h_ctrl_cancelSeenByAll					= 32,     /**<广播源被取消指示	MC->ter,   [incoming]&[outgoing]: NULL*/
	h_ctrl_seenByAtLeastOneOther			= 33,     /**<告知被其他终端选看  MC->ter, [incoming]&[outgoing]: NULL*/
	h_ctrl_cancelSeenByAtLeastOneOther		= 34,     /**<告知被其他终端停看  MC->ter, [incoming]&[outgoing]: NULL*/
	h_ctrl_sendThisSource					= 35,     /**<选看终端			chair->MC, [incoming]&[outgoing]: [TTERLABEL+u8:CtrlMode]*/
	h_ctrl_sendThisSourceResponse			= 36,     /**<选看应答			MC->chair, [incoming]&[outgoing]: [u8:CtrlResult]*/
	h_ctrl_cancelSendThisSource				= 37,     /**<取消选看			chair->MC, [incoming]&[outgoing]: NULL*/
	h_ctrl_terminalYouAreSeeing				= 38,     /**<正在观看的视频源	MC->ter,   [incoming]&[outgoing]: [TTERLABEL]*/
	//39
	h_ctrl_makeMeChair						= 39,     /**<申请主席			ter->MC,   [incoming]&[outgoing]: NULL*/
	h_ctrl_cancelMakeMeChair				= 40,     /**<释放主席			chair->MC, [incoming]&[outgoing]: NULL*/
	h_ctrl_makeMeChairResponse				= 41,     /**<主席申请/释放应答	MC->ter,   [incoming]&[outgoing]: [u8:CtrlResult]*/
	h_ctrl_withdrawChairToken				= 42,     /**<主席撤销指示		MC->ter,   [incoming]&[outgoing]: NULL*/
	h_ctrl_requestChairTokenOwner			= 43,     /**<询问当前主席		ter->MC,   [incoming]&[outgoing]: NULL*/
	h_ctrl_chairTokenOwnerResponse			= 44,     /**<回答当前主席		MC->ter,   [incoming]&[outgoing]: [TTERINFO]*/
	h_ctrl_mcLocationIndication				= 45,	  /**<含有MC的实体地址	MC->ter,   [incoming]&[outgoing]: [TNETADDR]*/
	h_ctrl_roundTripDelay					= 46,	  /**<检查对端是否Alive ter->MC,MC->ter, [incoming]&[outgoing]: [s32:nMaxDelay]*/
	//47   
	h_ctrl_H239Message						= 47,     /**<发送H239消息      ter->MC,MC->ter, [incoming]&[outgoing]: [TH239INFO]*/
	h_ctrl_userInput						= 48,     /**<发送UserInput消息            [incoming]&[outgoing]: [TUserInputInfo]*/
		
	h_ctrl_roundTripDelay_request			= 49,     /**<h_ctrl_roundTripDelay请求的附加消息(防火墙内部使用，用于区分请求和应答)*/
		
	h_ctrl_customFecc						= 50,	  /**<FECC消息（使用H245进行FECC消息的传递，主要用于pxy）*/
		
	h_ctrl_multiplexCapability				= 51,     /**<multiplexCapability消息,  [incoming]&[outgoing]: [TMultiplexCapability]*/
		
	h_ctrl_masterSlaveResponse				= 52,     /**<[outgoing]      主从决定response，buf=BOOL32 用于收到对方masterslaveresquest后，手动回复对方ack*/
	h_ctrl_OutgoingMultipointConference		= 53,	  /**<[outgoing]		转发h_ctrl_MultipointConference消息，不产生回报*/
		
		
	h_ctrl_standardend						= 100,
		
};

#endif //_H323CONFSTDMSG_H
