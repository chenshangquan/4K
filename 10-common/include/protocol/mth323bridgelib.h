#ifndef _MTH323BRIDGELIB_H_
#define _MTH323BRIDGELIB_H_

#include "kdvtype.h"

#include "pxyadapter.h"
//using namespace H323ADAPTER_FOR_V50PXY;

#include "firewallproxyconst.h"
#include "firewallproxyclientlib.h"



// #ifdef _MSC_VER
// #ifdef MTH323BRIDGE_EXPORTS
// #define PXY_API 				__declspec(dllexport)
// #else
// #define PXY_API
// #endif
// // for gcc
// #else
// #define PXY_API
// #endif	// _MSC_VER


/************************************************************************
 *   Defines & Enum
 ***********************************************************************/
#define MAX_CHAN_NUM 8
#define RETMTBRIDGEOK   0
#define RETMTBRIDGEFAIL -1
/************************************************************************
 *   Struct
 ***********************************************************************/
typedef struct tagStatus
{
    // Bridge Status.
    BOOL32 m_bBridgeRun;
    
    // Pxy Status.
    BOOL32 m_bPxyInited;
    u8   m_bPxyState;
    H323ADAPTER_FOR_V50PXY::H323EVENT m_tPxyEvent;  

    // Mt Status.
    BOOL32 m_bMtInited;
    u8   m_bMtState;
    H323ADAPTER_FOR_V50PXY::H323EVENT m_tMtEvent;

    u32   m_dwCallOpened;
    u32   m_dwChanOpened;

    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tMTDstLabel;
    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tMTSrcLabel;
    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tPxyDstLabel;
    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tPxySrcLabel;
}TH323BridgeStatus;

//用户使用的MsgSrc指明是终端还是Pxy
typedef enum tagEmMsgSrc
{
    emMsgFromMt = 1,
    emMsgFromPxy
}EmBridgeMsgSrc;

typedef struct tagFeccStr
{
    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tSrcLabel;
    H323ADAPTER_FOR_V50PXY::TTERLABEL m_tDstLabel;
    H323ADAPTER_FOR_V50PXY::TFeccStruct feccStruct;
}TBridgeFeccStruct;


PROTO_EXTERN_API void bridgehelp();
PROTO_EXTERN_API void bridgever();
PROTO_EXTERN_API void bridgestatus();
PROTO_EXTERN_API void bridgestatis();
/*H323Bridge Manager*/
PROTO_API void *InitMtH323Bridge(TClientCfgStruc & tCfg);
PROTO_API void  CloseMtH323Bridge();
PROTO_API BOOL32  BridgeLog(u8 byType, u8 byLevel);
PROTO_API TH323BridgeStatus BridgeStatus();
//TH323BridgeStatis BridgeStatis();


/*Interface*/
PROTO_API s32 MtH323BridgeSetCallBack(IN H323ADAPTER_FOR_V50PXY::LPH323EVENT lpEvent, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeCreateNewCall(IN HAPPCALL haCall, OUT LPHCALL lphsCall, EmBridgeMsgSrc emSrc);

PROTO_API s32 MtH323BridgeCreateNewChan(IN HCALL hsCall, IN HAPPCHAN haChan, 
                   OUT LPHCHAN lphsChan, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSendRasCtrlMsg(IN HCALL hsCall, IN HRAS hsRas, IN u16 msgType,
                   IN const void* pBuf, IN u16 nBufLen, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSendCallCtrlMsg(IN HCALL hsCall,IN u16 msgType,
                   IN const void* pBuf, IN u16 nBufLen, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSendChanCtrlMsg(IN HCHAN hsChan, IN u16 msgType,
                   IN const void* pBuf,IN u16 nBufLen, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSendConfCtrlMsg(IN HCALL hsCall, IN u16 msgType,
                   IN const void* pBuf, IN u16 nBufLen, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeFeccBind(IN HCHAN hsChan, IN H323ADAPTER_FOR_V50PXY::TTERLABEL localTer, 
                IN H323ADAPTER_FOR_V50PXY::TTERLABEL remoteTer, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSendFeccMsg(IN HCHAN hsChan, IN H323ADAPTER_FOR_V50PXY::TFeccStruct feccStruct, EmBridgeMsgSrc emSrc);
PROTO_API s32 MtH323BridgeSetGKRASAddress(IN HAPP hApp, IN cmTransportAddress tr);
PROTO_API s32 MtH323BridgeIsMasterCall(IN HCALL hsCall);
PROTO_API void MtH323BridgeReset();

PROTO_API s8* MtH323BridgeGetPeerVersionID(HCALL hsCall);
PROTO_API s8* MtH323BridgeGetPeerProductID(HCALL hsCall);

#endif


