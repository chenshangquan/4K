/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        kdv323adapter.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Provide the API function and the callback function prototype for the upper application 
*   @details     
*/

#ifndef _H323ADAPTER_H
#define _H323ADAPTER_H

#include "pfc.h"
/**#define RV_H323_TRANSPORT_ADDRESS RV_H323_TRANSPORT_ADDRESS_ANY*/

#include "h323stack4_2/cm.h"
#include <time.h>
#include <math.h>

#ifdef _LINUX_
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#endif///!_LINUX_

///////////////////////////////// KDV H323 协议版本号 ///////////////////////////////
/// 用于 TH323CONFIG.SetVersionId
#define KDVH323_VERID      (u8*)"8"
#define LEN_KDVH323_VERID  strlen((s8*)KDVH323_VERID)
///////////////////////////////////////////////////////////////////////////////////

#include "h323callstdstruct.h" 
#include "h323confstdstruct.h"
#include "h323confnonstdstruct.h"
#include "h323callstdmsg.h"
#include "h323confstdmsg.h"
#include "h323confnonstdmsg.h"
#include "kdvdatanet.h"


///////////////////////////////// Outgoing Interface ////////////////////////////////

/**
	* \brief            Restore the alias structure
	* \param[in]        pbyAliasBuf		:Src alias buf
	* \param[in]        wAliasNum       :Alias Num
	* \param[in]        dwAliasBufLen   :Alias buf length
	* \param[out]       atAlias         :Alias
	* \param[in]        wMaxAliasNum    :Max Alias Num
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/
PROTO_API BOOL32 NSM_DecodeAlias(IN u8 *pbyAliasBuf, IN u16 wAliasNum, IN u32 dwAliasBufLen, OUT TALIASADDR* atAlias, IN u16 wMaxAliasNum);
///***********************mmcu define**************************


/**
	* \brief            Init MMcu Stack
	* \param[in]        wListenPort		:Listen Port
	* \param[in]        wWatchPortFrom  :Beginning of watch port
	* \param[in]        wWatchPortTo    :End of watch port
	* \param[in]        bSockInit       :Pfc sock init flag
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/
PROTO_API BOOL32 MMcuStackInit(u16 wListenPort,u16 wWatchPortFrom = 0,u16 wWatchPortTo = 0,BOOL32 bSockInit = FALSE);

/**
	* \brief            Clean MMcu Stack
	* \param[in]        bSockClean       :Clean MMcu source
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/
PROTO_API BOOL32 MMcuStackClean(BOOL32 bSockClean = FALSE);


/** New notification of conference cascading */
#define 	H_CASCADE_NEW_CALL_NTF   (s32)CASCADE_MSGTYPE_ENDING  

/** Disconnection notification of conference cascading */
#define     H_CASCADE_DROP_CALL_NTF  (s32)(H_CASCADE_NEW_CALL_NTF+1)

/** Setting the print level interface command for cascade */
PROTO_EXTERN_API void mmcusetlog(u8 level);
/** help command for cascade */
PROTO_EXTERN_API void mmcuhelp();


///////////////////////////////// Outgoing Interface ////////////////////////////////

/**
	* \brief            Exchange call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        lphaCall	: Application call handle
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyNewCallT)(HCALL hsCall, LPHAPPCALL lphaCall);

/**
	* \brief            Exchange call handle for H460
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        lphaCall	: Application call handle
	* \param[in]        pBuf		: Callback data buffer
	* \param[in]        nBufLen		: Data length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyNew460CallT)(HCALL hsCall, LPHAPPCALL lphaCall , const void* pBuf , u16 nBufLen );

/**
	* \brief            Exchange channel handle
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        hsChan		: Protocol channel call handle
	* \param[in]        lphaChan	: Application channel handle
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyNewChanT)(HAPPCALL haCall,HCALL hsCall,HCHAN hsChan,
										  LPHAPPCHAN lphaChan);
/**
	* \brief            Notification function of call control
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message buffer
	* \param[in]        nBufLen		: Message length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyCallCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,u16 msgType,
											  const void* pBuf,u16 nBufLen);

/**
	* \brief            Notification function of channel control
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        haChan		: Application channel handle
	* \param[in]        hsChan		: Protocol stack channel handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message buffer
	* \param[in]        nBufLen		: Message length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyChanCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
											  u16 msgType,const void* pBuf,u16 nBufLen);

/**
	* \brief            Notification function of conference control
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        haChan		: Application channel handle
	* \param[in]        hsChan		: Protocol stack channel handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message buffer
	* \param[in]        nBufLen		: Message length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyConfCtrlMsgT)(HAPPCALL haCall, HCALL hsCall,u16 msgType,const void* pBuf,
											  u16 nBufLen);
/**
	* \brief            Notification function of ras message
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        haRas		: Application ras handle
	* \param[in]        hsRas		: Protocol stack ras handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message buffer
	* \param[in]        nBufLen		: Message length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK* NotifyRasCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPRAS haRas, HRAS hsRas,u16 msgType,
											 const void* pBuf,u16 nBufLen);
/**
	* \brief            Notification function of fecc message
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsChan		: Protocol stack channel handle
	* \param[in]        feccStruct	: Fecc struct
	* \param[in]        terSrc		: Src terminal number parameter
	* \param[in]        terDst		: Dst terminal number parameter
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsgT)(HCALL hsCall, HCHAN hsChan, 
										  TFeccStruct feccStruct,
										  TTERLABEL terSrc, TTERLABEL terDst);

/**
	* \brief            Notification function of cascade message
	* \param[in]        haCall		: Application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        haCall		: Application channel handle
	* \param[in]        hsChan		: Protocol stack channel handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message buffer
	* \param[in]        nBufLen		: Message length
	* \retval           success		: cb_ok
	* \retval           failed		: cb_err
*/
typedef int (PROTO_CALLBACK *NotifyMMcuMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
                                          u16 msgType,const void* pBuf,u16 nBufLen);



/**Structure of Callback function pointer*/
typedef struct 
{
    NotifyNewCallT		fpNewCall;		//**< Call callback pointer
    NotifyNewChanT		fpNewChan;		//**< Channel callback pointer
    NotifyCallCtrlMsgT  fpCallCtrlMsg;	//**< Call control callback pointer
    NotifyChanCtrlMsgT  fpChanCtrlMsg;	//**< Channel control pointer
    NotifyConfCtrlMsgT	fpConfCtrlMsg;	//**< Call control pointer
    NotifyRasCtrlMsgT	fpRasCtrlMsg;	//**< Ras control pointer
    NotifyFeccMsgT      fpFeccMsg;		//**< Fecc callback pointer 
    NotifyMMcuMsgT      fpMMcuMsg;		//**< cascade callback pointer
	NotifyNew460CallT   fpNew460Call;	//**< H460 callback pointer
}H323EVENT,*LPH323EVENT;

///////////////////////////////// Incoming Interface ////////////////////////////////

/**
	* \brief            Init H323 stack
	* \param[in]        pchConfigFile	: Protocol stack configuration file name
	* \param[in]        ptKeyParams		: Key configuration parameters of protocol stack
	* \param[out]		empFail			: Cause of failure
	* \return           Application handle created for the initialized stack instance
	* - success: &g_hApp
	* - failed : NULL
	* \note				(1)Initialize the protocol stack based on these parameters when the configuration file initializes failure
	* \note				(2)Some parameters are read from the configuration file to the structure for later use when the configuration file is initialized
*/
PROTO_API void* kdvInitH323Adapter(IN s8* pchConfigFile, IN TH323CONFIG *ptKeyParams, INOUT emInitFailReason *empFail=NULL);

/**
	* \brief            Close H323 Stack
	* \return           NULL
*/
PROTO_API void kdvCloseH323Adapter();

/**
	* \brief            Set stack config
	* \param[in]        ptStackConfig	: stack additional config
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSetStackAdditionalConfig(TAdditionalConfig* ptStackConfig);

/**
	* \brief            Registration application callback function
	* \param[in]        lpEvent	:Structure of Callback function pointer
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32  kdvSetAppCallBack(IN LPH323EVENT lpEvent);

/**
	* \brief            Check whether the protocol stack has received H.323 messages
	* \return           NULL
*/
PROTO_API void kdvCheckMessage();

/**
	* \brief            Create a new call
	* \param[in]        haCall			: Application stack call handle
	* \param[out]       lphsCall		: Protocol stack call handle
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvCreateNewCall(IN HAPPCALL haCall, OUT LPHCALL lphsCall, IN bool bSync = true);

/**
	* \brief            Create a new channel
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[in]		haChan			: Application channel handle
	* \param[out]		lphsChan		: Protocol stack channel handle
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvCreateNewChan(IN HCALL hsCall, IN HAPPCHAN haChan, 
                     OUT LPHCHAN lphsChan, IN bool bSync = true);

/**
	* \brief            Create a new channel
	* \param[in]        haRas			: Application ras handle
	* \param[out]		lphsRas			: Protocol stack handle
	* \param[in]		transaction		: Indicates the type of RAS transaction we're dealing with
	* \param[in]		destAddress		: Destination address
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvCreateRASStartTransaction(IN  HAPPRAS          haRas,
                                 OUT LPHRAS           lphsRas,
                                 IN  cmRASTransaction transaction,
                                 IN  PFC_IPADDR*        destAddress,
                                 IN  HCALL            hsCall,
                                 IN  bool             bSync = true);

/**
	* \brief            Send ras control message
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[out]		hsRas			: Protocol stack handle
	* \param[in]		msgType			: Ras message type
	* \param[in]		pBuf			: Message buffer
	* \param[in]        nBufLen			: Message length
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSendRasCtrlMsg(IN HCALL hsCall, IN HRAS hsRas, IN u16 msgType,
                      IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/**
	* \brief            Send call control message
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[in]		msgType			: Call message type
	* \param[in]		pBuf			: Message buffer
	* \param[in]        nBufLen			: Message length
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSendCallCtrlMsg(IN HCALL hsCall,IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/**
	* \brief            Send channel control message
	* \param[in]        hsChan			: Protocol stack channel handle
	* \param[in]		msgType			: Call message type
	* \param[in]		pBuf			: Message buffer
	* \param[in]        nBufLen			: Message length
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSendChanCtrlMsg(IN HCHAN hsChan, IN u16 msgType,
                       IN const void* pBuf,IN u16 nBufLen, IN bool bSync = true);

/**
	* \brief            Send conference control message
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[in]		msgType			: Call message type
	* \param[in]		pBuf			: Message buffer
	* \param[in]        nBufLen			: Message length
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSendConfCtrlMsg(IN HCALL hsCall, IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/**
	* \brief            Check the legitimacy of the call handle
	* \param[in]        hsCall			: Protocol stack call handle
	* \retval           success			: TRUE
	* \retval           failed			: FALSE
*/
PROTO_API BOOL32 kdvCheckValid(IN HCALL hsCall);

/**
	* \brief            Check the legitimacy of the channel handle
	* \param[in]        hsChan			: Protocol stack channel handle
	* \retval           success			: TRUE
	* \retval           failed			: FALSE
*/
PROTO_API BOOL32 kdvCheckValid(IN HCHAN hsChan);

/**
	* \brief            Set application call handle to stack
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[in]        haCall			: Application call handle
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvCallSetHandle(IN HCALL hsCall, IN HAPPCALL haCall, IN bool bSync = true);

/**
	* \brief            Get application call handle
	* \param[in]        hsCall			: Protocol stack call handle
	* \param[out]       haCall			: Application call handle
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvCallGetHandle(IN HCALL hsCall, OUT HAPPCALL* haCall, IN bool bSync = true);

/**
	* \brief            Update local alias
	* \param[in]        alias			: alias array
	* \param[in]        size			: alias num
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvRasUpdateRegAliasList(IN cmAlias alias[], IN s32 size);

/**
	* \brief            Update local alias
	* \param[in]        hApp			: Protocol stack handle
	* \param[in]		tr				: GK address
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSetGKRASAddress(IN HAPP hApp, IN cmTransportAddress tr, bool bSync = true );

/**
	* \brief            Get call parameters
	* \param[in]        hsCall			: Protocol stack handle
	* \param[in]		cpt				: Call parameter type
	* \param[out]		pBuf			: parameter value
	* \param[out]		nBufLen			: parameter length
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvGetCallParam(IN HCALL hsCall, IN CallParamType cpt, 
                    OUT void* pBuf, OUT u16 nBufLen, IN bool bSync = true);

/**
	* \brief            Check whether is master call or not
	* \param[in]        hsCall			: Protocol stack handle
	* \retval           success			: TRUE
	* \retval           failed			: FALSE
*/
PROTO_API BOOL32 kdvIsMasterCall(IN HCALL hsCall);

/**
	* \brief            Returns the master/slave status of this call
	* \param[in]        hsCall			: Protocol stack handle
	* \retval           success			: TRUE
	* \retval           failed			: FALSE
*/
PROTO_API BOOL32 kdvIsMasterTerminal(IN HCALL hsCall);

#if ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_ANY)
/**
	* \brief            Get local IP form the call
	* \param[in]        hsCall			: Protocol stack handle
	* \return			Network sequence IPV6 address
*/
PROTO_API ipAddress kdvGetLocalCallIPAddress(IN HCALL hsCall);
#elif ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_OLD)
/**
	* \brief            Get local IP form the call
	* \param[in]        hsCall			: Protocol stack handle
	* \return			Network sequence IPV4 address
*/
PROTO_API u32 kdvGetLocalCallIPAddress(HCALL hsCall);
#endif

/**
	* \brief			Judging whether is the audio type
	* \param[in]        wPayLoadType	: Payload value
	* \retval           support			: not zero
	* \retval           not-support		: 0
*/
inline BOOL32 IsAudioType(IN u16 wPayLoadType)
{
	return PayloardIsAudioType(wPayLoadType); 
}

/**
	* \brief			Judging whether is the video type
	* \param[in]        wPayLoadType	: Payload value
	* \retval           support			: not zero
	* \retval           not-support		: 0
*/
inline BOOL32 IsVideoType(IN u16 wPayLoadType)
{
	return PayloardIsVideoType(wPayLoadType);
}

/**
	* \brief			Judging whether is the data type
	* \param[in]        wPayLoadType	: Payload value
	* \retval           support			: not zero
	* \retval           not-support		: 0
*/
inline BOOL32 IsDataType(IN u16 wPayLoadType)
{
	return PayloardIsDataType(wPayLoadType);
}

/** 输出有关协议栈的函数，并增加信号量保护 */
/**
	* \brief            Get call parameters
	* \param[in]        hsCall			: Protocol stack handle
	* \param[in]		param			: Call parameter
	* \param[in]		index			: The instance of the parameter specified in param
	* \note								  The index of a single-instance parameter is 0.
	* \note								  The index of a multiple-instance parameter is 1-based.
	* \param[in]		value			: parameter value pointer
	* \note								  If the parameter value is a simple integer, the input
	* \note								  value of this parameter is ignored.
	* \note								  If the parameter value is a structure, value represents
	* \note								  the maximum length of svalue in bytes.
	* \param[out]		value			: parameter value pointer
	* \note                               If the parameter value is a simple integer, value is the
	* \note								  pointer to the parameter value.
	* \note								  If the parameter value is a structure, value represents
	* \note								  the length of the parameter.
	* \param[out]		svalue			: parameter value pointer
	* \note								  If the parameter value is a structure, svalue
	* \note								 (structured value) represents the pointer to the parameter itself.
	* \param[in]		bSync			: Mutual exclusion
	* \retval           success			: 0
	* \retval           failed			: other
*/
PROTO_API s32 kdvCmCallGetParam(IN HCALL hsCall, IN cmCallParam param, IN s32 index,
                      INOUT s32* value, OUT s8* svalue, IN bool bSync = true);

/**
	* \brief            Create a RAS transaction.
	* \param[in]        hApp			: Application's handle for a stack instance
	* \param[in]		haRas			: Application's handle for the RAS transaction
	* \param[out]		lphsRas			: The stack's RAS transaction handle that was created.
	* \param[in]		transaction		: he transaction type we want to start
	* \param[in]		destAddress		: Address of the destination.
	* \note								  If set to NULL, then it's for the gatekeeper
	* \param[in]		hsCall			: Stack's call handle if the transaction is related to a call. NULL otherwise.
	* \param[in]		bSync			: Mutual exclusion
	* \return
	*- If an error occurs, the function returns a negative value.
	*- If no error occurs, the function returns a non-negative value.
*/
PROTO_API s32 kdvCmRASStartTransaction(IN  HAPP hApp, IN  HAPPRAS haRas, OUT LPHRAS lphsRas,
                             IN  cmRASTransaction transaction, IN cmRASTransport* destAddress,
                             IN  HCALL hsCall, IN  bool bSync = true);

/**
	* \brief            Set a parameter about the RAS transaction
	* \param[in]        hsRas			: Stack's handle for the RAS transaction
	* \param[in]		trStage			: The transaction stage the parameters
	* \param[in]		param			: Type of the RAS parameter
	* \param[in]		index			: The instance of the parameter
	* \note								  If the parameter has several instances, 
	* \note								  the index that identifies the specific instance (0-based).0 otherwise.
	* \param[in]		value			: value of parameter.
	* \note								  For a simple integer - the parameter's value.
	* \note								  For a structure - the length of the parameter.
	* \param[in]		svalue			: parameter value pointer
	* \note								  For a structure - svalue represents the parameter itself.
	* \param[in]		bSync			: Mutual exclusion
	* \return
	*- If an error occurs, the function returns a negative value.
	*- If no error occurs, the function returns a non-negative value.
*/
PROTO_API s32 kdvCmRASSetParam(IN HRAS hsRas, IN cmRASTrStage trStage, IN cmRASParam param,
                     IN s32 index, IN s32 value, IN char* svalue, IN bool bSync = true);

/**
	* \brief            Get a parameter about the RAS transaction
	* \param[in]        hsRas			: Stack's handle for the RAS transaction
	* \param[in]		trStage			: The transaction stage the parameters
	* \param[in]		param			: Type of the RAS parameter
	* \param[in]		index			: The instance of the parameter
	* \note								  If the parameter has several instances, 
	* \note								  the index that identifies the specific instance (0-based).0 otherwise.
	* \param[in]		value			: parameter value pointer
	* \note								  If the parameter value is a simple integer, the input
	* \note								  value of this parameter is ignored.
	* \note								  If the parameter value is a structure, value represents
	* \note								  the maximum length of svalue in bytes.
	* \param[out]		value			: parameter value pointer
	* \note                               If the parameter value is a simple integer, value is the
	* \note								  pointer to the parameter value.
	* \note								  If the parameter value is a structure, value represents
	* \note								  the length of the parameter.
	* \note                               can be set to NULL if we're only interested in its length.
	* \param[in]		svalue			: parameter value pointer
	* \note								  For a structure - svalue represents the parameter itself.
	* \param[in]		bSync			: Mutual exclusion
	* \return
	*- If an error occurs, the function returns a negative value.
	*- If no error occurs, the function returns a non-negative value.
*/
PROTO_API s32 kdvCmRASGetParam(IN HRAS hsRas, IN  cmRASTrStage trStage, IN  cmRASParam param,
                     IN s32 index, IN OUT s32* value, /* value or length */
                     IN s8* svalue, IN bool bSync = true);

/**
	* \brief            Send an outgoing RAS transaction
	* \param[in]        hsRas			: Stack's handle for the RAS transaction
	* \param[in]		bSync			: Mutual exclusion
	* \return
	*- If an error occurs, the function returns a negative value.
	*- If no error occurs, the function returns a non-negative value.
*/
PROTO_API s32 kdvCmRASRequest(IN  HRAS hsRas, IN  bool bSync = true);

/**
	* \brief            Close a RAS transaction
	* \param[in]        hsRas			: Stack's handle for the RAS transaction
	* \param[in]		bSync			: Mutual exclusion
	* \return
	*- If an error occurs, the function returns a negative value.
	*- If no error occurs, the function returns a non-negative value.
*/
PROTO_API s32 kdvCmRASClose(IN  HRAS hsRas, IN bool bSync = true);


/**
	* \brief            Set ras call address
	* \param[in]        hApp			: Application's handle for a stack instance
	* \param[in]		tr				: IP address struct
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvRASSetCallAddress(IN HAPP hApp, IN cmTransportAddress tr);

/**
	* \brief            Set register ras address
	* \param[in]        hApp			: Application's handle for a stack instance
	* \param[in]		tr				: IP address struct
	* \retval           success			: act_ok
	* \retval           failed			: act_err
*/
PROTO_API s32 kdvSetlocalRASAddress(IN HAPP hApp, IN cmTransportAddress tr);

/**
	* \brief            Get alias type for upper user
	* \param[in]        dwAliasType		: Alias type
	* \return           return alias string
*/
PROTO_API const s8* GetCmAliasType(AliasType dwAliasType);

/**
	* \brief            Get alias type for stack
	* \param[in]        dwAliasType		: Alias type
	* \return           return alias string
*/
PROTO_API const s8* GetCmAliasType(cmAliasType dwAliasType);

/**
	* \brief            Get payload type
	* \param[in]        wSubMsgType		: Payload type
	* \return           return Payload string
*/
PROTO_API const s8* GetCmPayloadString	(u16 wSubMsgType);

/**
	* \brief            Get conference message type
	* \param[in]        wSubMsgType		: conference message type
	* \return           return conference message string
*/
PROTO_API const s8* GetCmConfMsgString	(u16 wSubMsgType);

/**
	* \brief            Get channel message type
	* \param[in]        wSubMsgType		: channel message type
	* \return           return channel message string
*/
PROTO_API const s8* GetCmChanMsgString	(u16 wSubMsgType);

/**
	* \brief            Get call message type
	* \param[in]        wPayload		: call message type
	* \return           return call message string
*/
PROTO_API const s8* GetCmCallMsgString	(u16 wPayload);

/**
	* \brief            Get ras message type
	* \param[in]        wSubMsgType		: ras message type
	* \return           return ras message string
*/
PROTO_API const s8* GetCmRasMsgString	(u16 wSubMsgType);

/**
	* \brief            Update Gatekeeper ID
	* \param[in]        hApp		: Application's handle for a stack instance
	* \param[in]        tGKID		: Alias struct
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32 kdvUpdateGatekeeperID(IN HAPP hApp, IN cmAlias tGKID);


/**
	* \brief            Get des mode DHKey
	* \note				Unrealized
*/
PROTO_API BOOL32 GetDesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);

/**
	* \brief            Get aes mode DHKey
	* \note				Unrealized
*/
PROTO_API BOOL32 GetAesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);

/**
	* \brief            Send conference cascade control messages
	* \param[in]        hsChan		: Protocol stack channel handle
	* \param[in]        msgType		: message type
	* \param[in]        pBuf		: message content
	* \param[in]        nBufLen		: message length
	* \param[in]        bSync		: Mutual exclusion
	* \retval           success		: act_ok
	* \retval           failed		: act_err
	* \note				1.关于双向逻辑通道(单独协议通道)(I incoming, O outgoing )
	* \note				逻辑通道冲突时， master 终端拒绝incoming channel
	* \note				I 方，主动tcp connect时，ack消息不需带单独协议通道监听地址
	* \note				O 方，当ack带有单独协议通道监听地址，且I没有主动tcp connect时,发起tcp connect
	* \note				2.级联通道,h_chan_open,h_chan_openAck 只需填写payload, m_tRtp.ip.
*/
PROTO_API int kdvSendMMcuCtrlMsg(HCHAN hsChan,u16 msgType,const void* pBuf,u16 nBufLen,bool bSync = true);

/** DNS state */
typedef enum
{
    DNS_SUCCESS = 0,	/**< success */
    DNS_TIMEOUT,		/**< time out */
    DNS_NOTFOUND,		/**< not found */
    DNS_FAILED,			/**< failed */
} dnsResult;

/**
	* \brief            Dns callback function
	* \param[in]        nUserID		: User ID
	* \param[in]        eResult		: result of dns
	* \param[in]        nIpNum		: num of IP
	* \param[in]        adwIP		: IP array
	* \note				Unrealized
*/
typedef s32 (*DnsCallBackT)(s32 nUserID, dnsResult eResult, s32 nIpNum, u32* adwIP);

PROTO_API int kdvDnsRequest(s8* pchName, u32 dwDnsServer, u32 dwUserID, 
                      DnsCallBackT ptDnsCallbackFunc, IN  BOOL32 bSync);


/**
	* \brief            Set ras IRR meaage infomation
	* \param[in]        hsRas		: Stack's handle for the RAS transaction
	* \param[in]        ptIRRInfo	: IRR message struct
	* \param[in]        bSync		: Mutual exclusion
	* \retval           success		: act_ok
	* \retval           failed		: act_err
	* \note             Set IRR information for applications that do not depend on HCALL.
*/
PROTO_API s32 kdvSetRasIRR(HRAS hsRas, TIRRINFO* ptIRRInfo, bool bSync);

/**
	* \brief            The transformation of the host sequence and the network order of the message body
	* \param[in]        msgType		: message type
	* \param[in]        pBuf		: message content
	* \param[in]        nBufLen		: message length
	* \param[in]        bhton		: transformation flag
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32 kdvH323Adapterhton(u16 msgType, void* pBuf, u16 nBufLen, BOOL32 bhton);

/**
	* \brief            Set H323 tos
	* \param[in]        nTOS		: Tos value
	* \param[in]        bSync		: Mutual exclusion
	* \return           return tos value
*/
PROTO_API s32 kdvSetH323TOS(IN s32 nTOS, IN bool bSync = true);

/**
	* \brief            Get H323 tos
	* \return           return tos value
*/
PROTO_API s32 kdvGetH323TOS();

//设置远遥TOS值, 函数体在kdvdatanet库中定义
// API s32 kdvSetDataTOS(s32 nTOS);
// API s32 kdvGetDataTOS();

/**
	* \brief            Get Peer Version ID
	* \param[in]        hsCall		: Protocol stack channel handle
	* \return           return version string
*/
PROTO_API s8* GetPeerVersionID(HCALL hsCall);

/**
	* \brief            Get Peer Product ID
	* \param[in]        hsCall		: Protocol stack channel handle
	* \return           return product string
*/
PROTO_API s8* GetPeerProductID(HCALL hsCall);

/**
	* \brief            If peer support correct byte order for G7221.c Siren14
	* \param[in]        hsCall		: Protocol stack channel handle
	* \retval           support		: TRUE
	* \retval           not-support	: FALSE
*/
PROTO_API BOOL32 IsPeerSupportNewG7221c(HCALL hsCall);  

/**
	* \brief            set H460 GW falg
	* \param[in]        bIsGw		: support or not
*/
PROTO_API void KdvSetIsH460GW(BOOL32 bIsGw);

/**
	* \brief            send tpkt pinhole
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        type		: Tpkt type
	* \param[in]        bSync		: Mutual exclusion
	* \retval           support		: TRUE
	* \retval           not-support	: FALSE
*/
PROTO_API int KdvSendTpktPinhole(HCALL hsCall, cmTpktChanHandleType type, BOOL32 bSync = TRUE);

/**
	* \brief            Set H460 config
	* \param[in]        bSupportH460				: Support or not
	* \param[in]        bMediaTraversalServer		: Set h460 MediaTraversalServer.It is global.
	* \param[in]        bSupportTransMultiMedia		: Set h460 SupportTransMultiMedia. It is global.
	* \return           None
*/
PROTO_API void KdvSetH460Config(BOOL32 bSupportH460, BOOL32 bMediaTraversalServer, BOOL32 bSupportTransMultiMedia);

/**
	* \brief            Set application call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        haCall		: Application call handle
	* \return           None
*/
PROTO_API void KdvSetCallApplicationHandle(HCALL hsCall, void* haCall);

/**
	* \brief            Set local encoding method to utf-8
	* \param[in]        bIsUtf8		: support or not
	* \return           None
*/
PROTO_EXTERN_API void kdvSetLocalIsUTF8(BOOL32 bIsUtf8);

/**
	* \brief            Debug H323 interface
	* \param[in]        bCap		: Cap reject or not
	* \param[in]        bMsd		: Msd reject or not
	* \param[in]        bChan		: Chan reject or not
	* \return           None
*/
PROTO_EXTERN_API void h323debug(BOOL32 bCap,BOOL32 bMsd,BOOL32 bChan);

/**
	* \brief            Set H323 Tos Value(DSCP)
	* \param[in]        nTos		: Tos Value
	* \return           None
*/
PROTO_EXTERN_API void h323asettos(s32 nTos);

/**
	* \brief            support non-standard stack
	* \param[in]        bIsKDV323		: support or not
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_EXTERN_API s32 kdvSetKDV323(IN BOOL32 bIsKDV323);

/**
	* \brief            View the state of the protocol stack
	* \retval           standard stack:; non-standard stack
*/
PROTO_EXTERN_API BOOL32 kdv323std();

/**
	* \brief            support non-standard stack
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        hsRas		: Protocol stack ras handle
	* \param[in]        msgType		: Message type
	* \param[in]        pBuf		: Message content
	* \param[in]        nBufLen		: Message length
	* \param[in]        ptDstNetAddr: Destination address
	* \param[in]        bSync		: Mutual exclusion
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32 kdvManualRASSendNSM(IN HCALL hsCall,IN HRAS hsRas,IN u16 msgType,
						IN const void* pBuf,IN u16 nBufLen,IN PFC_IPADDR * ptDstNetAddr,IN bool bSync = true);
///end add 
/**
	* \brief            Set H460 feature
	* \param[in]        bSupportH460				: Support or not
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32 kdvSetH460Feature(IN BOOL32 bSupportH460);

/**
	* \brief            Close call handle
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]        bSync		: Mutual exclusion
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32 kdvCloseCall( IN HCALL hsCall, IN bool bSync = true );

/**
	* \brief            Get local IP address
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[out]    tAddress	: IP address struct
	* \retval           success		: 1
	* \retval           failed		: 0
*/
PROTO_API u32 kdvGetLocalTCPAddress(HCALL hsCall, PFC_IPADDR *tAddress );

/**
	* \brief            Get local IP address
	* \param[in]        hsCall		: Protocol stack call handle
	* \param[in]		hsChan		: Protocol stack chan handle
	* \param[in]		tDstAddr	: Destination connection address
	* \retval           success		: act_ok
	* \retval           failed		: act_err
*/
PROTO_API s32	 kdvConnectMMCU(IN HCALL hsCall, IN HCHAN hsChan, IN  PFC_IPADDR tDstAddr);

/**
	* \brief            Get H225 version
	* \return           return H225 version
*/
PROTO_API u32	 kdvGetH225Ver(IN HCALL hsCall);

// [12/3/2008 zhangzhihua]add.手动删除远遥所占资源.
/**
	* \brief            Free fecc recv source
	* \param[in]		hsChan		: Protocol stack chan handle
	* \return           annexQOk if succeed, or <0 if fails
*/
PROTO_API s32 KdvH323FreeFeccRcvSession(IN HCHAN hsChan);

/**
	* \brief            Free fecc send source
	* \param[in]		hsChan		: Protocol stack chan handle
	* \return           annexQOk if succeed, or <0 if fails
*/
PROTO_API s32 KdvH323FreeFeccSendSession(IN HCHAN hsChan);

#endif 
///_H323ADAPTER_H
