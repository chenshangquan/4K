#ifndef _QT_INTERFACE_IMPL_H_
#define _QT_INTERFACE_IMPL_H_

#include "qtstruct.h"

//初始化QTLIB 库,HDU APU2 初始化参数使用默认值
BOOL32	QtLibInit(QTIN const TQtInitParam& tQtParam);
//清理QTLIB库
void	QtLibQuit();


//设置加密信息 
//bEncryption	打开或者关闭加密功能
//emKeyFre		加密等级
void	QtSetEncryptionInfo(BOOL32 bEncryption, EmQtKeyFrequency emKeyFre, EmQtProtocol emProtocol);

//设置是否USB加密 
void	QtSetUsbEncrpty(BOOL32 bEncryptUsb, QTOUT u8 acKey[QT_KEY_LEN_16+1]);

//初始化一次呼叫
EmQtRetReason	QtInitCall(QTIN const TQtCallParam& tCallParam, EmQtProtocol QTIN emQtProtocol, QTOUT QTCALLHANDLE& hCallHandle);
//清理一次呼叫使用的资源
void			QtExitCall(QTIN QTCALLHANDLE hCallHandle);

u32 QtGetLocalQtID();

//获取信令秘钥
EmQtRetReason QtGetKeyForMsgEnc(QTIN QTCALLHANDLE hCallHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]);
BOOL32 QtGetKeyForMsgDec(QTIN QTCALLHANDLE hCallHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);

//获取码流秘钥
BOOL32 QtInitMediaKey(QTIN const TQtCallParam& tCallParam, EmQtProtocol QTIN emQtProtocol, QTOUT QTMediaKeyHandle& hMediaHandle);
BOOL32 QtGetKeyForMediaEnc(QTIN QTMediaKeyHandle hMediaHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]); 
BOOL32 QtGetKeyForMediaDec(QTIN QTMediaKeyHandle hMediaHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);
void   QtExitMediaKey(QTIN QTMediaKeyHandle hMediaHandle);

//BFCP 
//目前版本仅支持bfcp依赖于呼叫，因此该接口必须晚于QtInitCall接口之后调用
EmQtRetReason QtInitBfcp(QTIN const TQtCallParam& tCallParam, QTOUT QTBFCPHANDLE& hBfcpHandle);
void QtExitBfcp(QTIN QTBFCPHANDLE hBfcpHandle);
EmQtRetReason QtGetKeyForBfcpEnc(QTIN QTBFCPHANDLE hBfcpHandle, QTOUT QTKEYHANDLE& hKeyHandle, QTOUT u8 acKey[QT_KEY_LEN_16+1]);
BOOL32 QtGetKeyForBfcpDec(QTIN QTBFCPHANDLE hBfcpHandle, QTIN QTKEYHANDLE hKeyHandle,  QTOUT u8 acKey[QT_KEY_LEN_16+1]);


//设置码流秘钥，在收到平台推送的码流秘钥消息后调用该接口
BOOL32 QtSetMediaKey(QTIN QTMediaKeyHandle& hMediaHandle, QTIN u8 acKey[QT_MAX_MEDIA_KEY+1], QTIN u32 dwKeyLen, QTIN EmQtKeyFrequency emQtKeyFrequency, QTIN u32 wQtFlag = 0,QTIN u16 wConverIndex = -1);

//测试接口
void SetTest();

//UMS平台业务使用
void QtSetConfID(QTIN s8* byAlias, QTIN u16 wConfID);
void QtSetConfInfo(QTIN u16 wConfID, BOOL32 bDownConf, BOOL32 bReset );
void QtQueryConfEncryptionResult(u16 wConfID, void* ptInfo, BOOL32 bRes, EmQtKeyFrequency emKeyFre);
void SetMediaKeyFailCB(QTIN QtCBMediaKeyFail cpFun);

#endif

