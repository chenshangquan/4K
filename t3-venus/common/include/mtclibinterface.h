/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: mtclibinterface.h
相 关  文 件: mtclibinterface.cpp
文件实现功能: mtclib消息发送接口(UI->MT)
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/05/28  4.0     王昊        创建
=============================================================================*/

#ifndef _MTCLIBINTERFACE_20070528_H_
#define _MTCLIBINTERFACE_20070528_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "addrbook.h"
#include "key.h"
#include "ummessagestruct.h"

class CMtclibInterface : public CInstance
{
public:
    CMtclibInterface();
    virtual ~CMtclibInterface();

//UI调用接口
public:
    ///////////////////////////////////////////////////////////////////////////////
    //  1. 连接接口
    ///////////////////////////////////////////////////////////////////////////////

    //连接终端
    EMMtclibErrorCode ConnectMtReq(u32 dwMtIP, u16 wMtListenPort,
                                   LPCSTR lpszUserName, LPCSTR lpszPwd,
                                   u32 &dwLocalIpAddr);

    //断开连接
    EMMtclibErrorCode DisconnectMtCmd(void);

    ///////////////////////////////////////////////////////////////////////////////
    //  2. VOD接口
    ///////////////////////////////////////////////////////////////////////////////

    //登录VOD服务器
    EMMtclibErrorCode VodLoginReq(u32 dwServerIP, u16 wPort, LPCSTR lpszUsername,
                                  LPCSTR lpszPassword);

    //退出VOD服务器
    EMMtclibErrorCode VodLogoutReq(void);

    //获取VOD指定目录下文件列表
    EMMtclibErrorCode VodGetFileListReq(LPCSTR lpszDirectory);

    //获取VOD指定文件信息
    EMMtclibErrorCode VodGetFileInfoReq(LPCSTR lpszFilename);

    //播放VOD文件
    EMMtclibErrorCode VodPlayFileReq(LPCSTR lpszFilename);

    //暂停播放VOD文件
    EMMtclibErrorCode VodPauseFileReq(void);

    //恢复播放VOD文件
    EMMtclibErrorCode VodResumeFileReq(void);

    //停止播放VOD文件
    EMMtclibErrorCode VodStopFileReq(void);

    //从指定位置播放VOD文件(主机序)
    EMMtclibErrorCode VodPlayFileAtPosCmd(u32 dwPos);

    ///////////////////////////////////////////////////////////////////////////////
    //  3. 矩阵接口
    ///////////////////////////////////////////////////////////////////////////////

    //获取所有内置矩阵方案
    EMMtclibErrorCode MatrixGetAllInnerSchemeReq(void);

    //获取指定内置矩阵方案
    EMMtclibErrorCode MatrixGetInnerSchemeReq(u8 byIndex);

    //保存内置矩阵方案
    EMMtclibErrorCode MatrixSaveInnerSchemeReq(const TAVInnerMatrixScheme &tScheme);

    //设置当前应用内置矩阵方案
    EMMtclibErrorCode MatrixSetCurApplyInnerSchemeReq(u8 byIndex);

    //获取当前应用内置矩阵方案
    EMMtclibErrorCode MatrixGetCurApplyInnerSchemeReq(void);

    //设置当前内置视频源
    EMMtclibErrorCode MatrixSetCurInnerVideoSourceCmd(EmMtVideoPort emPort);

    //选择当前视频源(近端/远端)
    EMMtclibErrorCode MatrixSetCurInnerSiteCmd(EmSite emSite);

    //当前视频源更名
    EMMtclibErrorCode MatrixEditCurInnerVideoSourceNameCmd(
                                                const TVideoSourceInfo &tInfo);

    //获取外置矩阵信息
    EMMtclibErrorCode MatrixGetOuterInfoReq(void);

    //设置外置矩阵视频源
    EMMtclibErrorCode MatrixSetOuterVideoSourceReq(const TVideoSourceInfo &tInfo);

    //获取外置矩阵视频源
    EMMtclibErrorCode MatrixGetOuterVideoSourceReq(void);

    ///////////////////////////////////////////////////////////////////////////////
    //  4. 配置接口
    ///////////////////////////////////////////////////////////////////////////////

    //设置H.323配置
    EMMtclibErrorCode CfgSetH323CfgCmd(const TH323Cfg &tCfg);

    //设置用户配置
    EMMtclibErrorCode CfgSetUserCfgCmd(const TUserCfg &tCfg);

    //设置终端显示配置
    EMMtclibErrorCode CfgSetOSDCfgCmd(const TOsdCfg &tCfg);

    //设置以太网配置
    EMMtclibErrorCode CfgSetEthnetCfgCmd(u8 byIndex, const TEthnetInfo &tCfg);

    //设置E1配置
    EMMtclibErrorCode CfgSetE1CfgCmd(const TE1Config &tCfg);

    //设置串口信息配置
    EMMtclibErrorCode CfgSetSerialCtrlCmd(EmSerialType emType,
                                          const TSerialCfg &tCfg);

    //添加路由
    EMMtclibErrorCode CfgAddRouteCmd(const TRouteCfg &tCfg);

    //删除路由
    EMMtclibErrorCode CfgDelRouteCmd(const TRouteCfg &tCfg);

    //设置PPPoE配置
    EMMtclibErrorCode CfgSetPPPoECfgCmd(const TPPPOECfg &tCfg);

    //设置网管配置
    EMMtclibErrorCode CfgSetNetManagementCfgCmd(const TSNMPCfg &tCfg);

    //设置IPQoS信息配置
    EMMtclibErrorCode CfgSetIPQoSCfgCmd(const TIPQoS &tCfg);

    //设置防火墙信息配置
    EMMtclibErrorCode CfgSetEmbedFirewallCfgCmd(const TEmbedFwNatProxy &tCfg);

    //设置静态映射
    EMMtclibErrorCode CfgSetNatMapCfgCmd(const TNATMapAddr &tCfg);

    //设置发送重传信息配置
    EMMtclibErrorCode CfgSetRetransCfgCmd(const TLostPackResend &tCfg);

    //设置流媒体信息配置
    EMMtclibErrorCode CfgSetStreamCfgCmd(const TStreamMedia &tCfg);

    //设置视频编码参数配置
    EMMtclibErrorCode CfgSetVideoParamCmd(EmVideoType emType,
                                          const TVideoParam &tCfg);

    //设置PC双流配置
    EMMtclibErrorCode CfgSetPCVideoParamCmd(const TVideoParam &tCfg);

    //设置优选协议信息配置
    EMMtclibErrorCode CfgSetAVPriorCfgCmd(const TAVPriorStrategy &tCfg);

    //设置摄像头信息配置
    EMMtclibErrorCode CfgSetCameraCfgCmd(u8 byIndex, const TCameraCfg &tCfg);

    //设置视频制式(输入/输出)
    EMMtclibErrorCode CfgSetVideoStandardCmd(const TVideoStandard &tStand);

    //设置图像参数
    EMMtclibErrorCode CfgSetImageAdjustCfgCmd(const TImageAdjustParam &tParam);

    //设置横幅设置
    EMMtclibErrorCode CfgSetBannerInfoCmd(const TBannerInfo &tInfo);

    //设置串口控制配置
    EMMtclibErrorCode CfgSetSerialCfgCmd(EmSerialType emType,
                                         const TIPTransAddr &tIPAddr);

    //设置监控切换业务配置
    EMMtclibErrorCode CfgSetMonitorServiceCfgCmd(const TMonitorService &tCfg);

    //设置双流比率
    EMMtclibErrorCode CfgSetDualRatioCfgCmd(const TDualRation &tRatio);

    //设置内置MC配置
    EMMtclibErrorCode CfgSetInnerMCCfgCmd(const TInnerMcCfg &tCfg);

    //设置6610E内置GK配置
    EMMtclibErrorCode CfgSetInnerGKCmd(const TInnerGKCfg &tCfg);

    //设置遥控器快捷键
    EMMtclibErrorCode CfgSetShortcutKeyCmd(const TRapidKey &tKey);

    //设置PCMT视频源信息
    EMMtclibErrorCode CfgSetPcmtVideoSourceCmd(const TCapType &tType);

    //设置8010C配置VGA输出参数
    EMMtclibErrorCode CfgSetVGAOutCfgCmd(const TVgaOutCfg &tCfg);

    //设置回声抵消
    EMMtclibErrorCode CfgSetAECCmd(BOOL32 bEnable);

    //设置自动增益
    EMMtclibErrorCode CfgSetAGCCmd(BOOL32 bEnable);

    //设置自动噪音抑制
    EMMtclibErrorCode CfgSetANSCmd(BOOL32 bEnable);

    //设置主视频输出
    EMMtclibErrorCode CfgSetMainVideoOutCmd(BOOL32 bOutToVideo);

    //设置VGA显示是否是本地
    EMMtclibErrorCode CfgSetVGAShowLocalCmd(BOOL32 bLocal);

    //设置第二路视频是否输出到VGA
    EMMtclibErrorCode CfgSetSecondVideoToVGACmd(BOOL32 bVGA);

    //设置是否发送静态图片
    EMMtclibErrorCode CfgSetSendStaticPicCmd(BOOL32 bSend);

    //设置是否使用DHCP
    EMMtclibErrorCode CfgSetUseDHCPCmd(BOOL32 bUsed);

    //设置呼叫码率(主机序)
    EMMtclibErrorCode CfgSetCallRateCmd(u32 dwCallRate);

    //设置网关(主机序)
    EMMtclibErrorCode CfgSetGatewayCmd(u32 dwIP);

    //设置DNS服务器IP地址(主机序)
    EMMtclibErrorCode CfgSetDNSServerIPCmd(u32 dwDNSIP);

    //设置MTU时间(主机序)
    EMMtclibErrorCode CfgSetMTUCmd(u32 dwMTU);

    //设置TCP、UDP起始端口(主机序)
    EMMtclibErrorCode CfgSetTCPUDPStartPortCmd(u16 wTCPPort, u16 wUDPPort);

    //设置语言类型
    EMMtclibErrorCode CfgSetLanguageCmd(EmLanguage emLan);

    //设置LDAP服务器
    EMMtclibErrorCode CfgSetLDAPCmd(LPCSTR lpszLDAP);

    //设置麦克风增益控制
    EMMtclibErrorCode CfgSetMicAdjustCmd(u8 byMicAdjust);

    //设置编码音量
    EMMtclibErrorCode CfgSetEncVolCmd(u8 byVol);

    //设置解码音量
    EMMtclibErrorCode CfgSetDecVolCmd(u8 byVol);

    //设置终端系统时间
    EMMtclibErrorCode CfgSetSysTimeCmd(const TMtKdvTime &tTime);

    //获取所有配置信息(发送所有获取配置的CMD)
    EMMtclibErrorCode CfgGetAllCfgCmd(EmMtModel emModel);

    ///////////////////////////////////////////////////////////////////////////////
    //  5. 快照接口
    ///////////////////////////////////////////////////////////////////////////////

    //获取快照信息
    EMMtclibErrorCode SnapShotGetInfoReq(void);

    //终端快照
    EMMtclibErrorCode SnapShotCmd(void);

    //清空快照信息
    EMMtclibErrorCode SnapShotClearCmd(void);

    ///////////////////////////////////////////////////////////////////////////////
    //  6. FXO接口
    ///////////////////////////////////////////////////////////////////////////////

    //FXO呼叫
    EMMtclibErrorCode FXOCallReq(LPCSTR lpszPhoneNo, u16 wNoLen,
                                 LPCSTR lpszEntryName = NULL);

    //FXO挂断呼叫
    EMMtclibErrorCode FXOHangupCmd(void);

    //FXO拒绝接听
    EMMtclibErrorCode FXORejectCmd(void);

    //FXO接听
    EMMtclibErrorCode FXOAcceptCmd(void);

    ///////////////////////////////////////////////////////////////////////////////
    //  7. 地址簿接口
    ///////////////////////////////////////////////////////////////////////////////

    //注册地址簿
    EMMtclibErrorCode AddrRegisterReq(void);

    //注销地址簿
    EMMtclibErrorCode AddrUnregisterReq(void);

    //添加条目
    EMMtclibErrorCode AddrAddEntryReq(const CAddrEntry &cEntry);

    //修改条目
    EMMtclibErrorCode AddrEditEntryReq(const CAddrEntry &cEntry);

    //删除条目
    EMMtclibErrorCode AddrDelEntryReq(u32 dwIndex);

    //添加会议组
    EMMtclibErrorCode AddrAddGroupReq(const CAddrMultiSetEntry &cGroup);

    //修改会议组
    EMMtclibErrorCode AddrEditGroupReq(const CAddrMultiSetEntry &cGroup);

    //删除会议组
    EMMtclibErrorCode AddrDelGroupReq(u32 dwIndex);

    //向会议组添加条目
    EMMtclibErrorCode AddrAddEntryToGroupReq(const TADDRMULTISETENTRY &tEntry);

    //从会议组删除条目
    EMMtclibErrorCode AddrDelEntryFromGroupReq(const TADDRMULTISETENTRY &tEntry);

    //上传地址簿文件结束
    EMMtclibErrorCode AddrUploadFileNotif(LPCSTR lpszFilename);

    //将新添加的地址条目默认添加到UserDef组里面
    EMMtclibErrorCode AddrAddEntryToUserDefReq(u32 dwIndex);

    ///////////////////////////////////////////////////////////////////////////////
    //  8. 摄像头控制接口
    ///////////////////////////////////////////////////////////////////////////////

    //摄像头方向控制
    EMMtclibErrorCode CameraMoveDirectionCmd(EmDirection emDirect, EmAction emAct);

    //摄像头自动调焦
    EMMtclibErrorCode CameraAutoFocusCmd(void);

    //摄像头手动调焦
    EMMtclibErrorCode CameraAdjustFocusCmd(BOOL32 bNear, EmAction emAct);

    //摄像头视野调节
    EMMtclibErrorCode CameraAdjustZoomCmd(BOOL32 bZoomOut, EmAction emAct);

    //摄像头亮度调节
    EMMtclibErrorCode CameraAdjustBrightnessCmd(BOOL32 bDec, EmAction emAct);

    //摄像头预置位
    EMMtclibErrorCode CameraPresetCmd(BOOL32 bLoad, u8 byPos);

    ///////////////////////////////////////////////////////////////////////////////
    //  9. 监控接口
    ///////////////////////////////////////////////////////////////////////////////

    //开始监控
    EMMtclibErrorCode MonitorStartCmd(EmSite emSite, const TIPTransAddr &tIpAddr);

    //停止监控
    EMMtclibErrorCode MonitorStopCmd(EmSite emSite);

    //请求关键帧
    EMMtclibErrorCode MonitorRequestKeyFrameCmd(EmSite emSite);

    ///////////////////////////////////////////////////////////////////////////////
    //  10. 模拟遥控器接口
    ///////////////////////////////////////////////////////////////////////////////

    //按下遥控器按钮
    EMMtclibErrorCode RemotePressDownCmd(u8 byKey, u8 byRemoteType = LBLACK_REMOTE);

    //放开遥控器按钮
    EMMtclibErrorCode RemoteReleaseUpCmd(u8 byKey, u8 byRemoteType = LBLACK_REMOTE);

    ///////////////////////////////////////////////////////////////////////////////
    //  11. 用户管理接口
    ///////////////////////////////////////////////////////////////////////////////

    //请求用户列表
    EMMtclibErrorCode UserGetListReq(void);

    //添加用户
    EMMtclibErrorCode UserAddReq(const CUserFullInfo &cUser);

    //修改用户
    EMMtclibErrorCode UserEditReq(const CUserFullInfo &cUser);

    //删除用户
    EMMtclibErrorCode UserDelReq(const CUserFullInfo &cUser);

    ///////////////////////////////////////////////////////////////////////////////
    //  12. 点对点会议接口
    ///////////////////////////////////////////////////////////////////////////////

    //呼叫终端
    EMMtclibErrorCode P2PCallReq(const TMtAddr &tMtAddr, u16 wCallRate = 768,
                                 LPCSTR lpszEntryName = NULL);

    //停止呼叫/结束点对点会议
    EMMtclibErrorCode P2PEndCallCmd(void);

    //接受点对点呼叫
    EMMtclibErrorCode P2PAcceptAck(BOOL32 bAccept);

    //发送短消息(点对点会议)
    EMMtclibErrorCode P2PSendMsgCmd(LPCSTR lpszMsg,
                                    EmSMSType emType = emSMSSingleLine,
                                    u8 byRollSpeed = 3, u8 byTimes = 1);

    ///////////////////////////////////////////////////////////////////////////////
    //  13. MCU多点会议接口
    ///////////////////////////////////////////////////////////////////////////////

    //创建会议
    EMMtclibErrorCode McuConfCreateReq(const TMtAddr &tMcu, u16 wCallRate,
                                       const TConfBaseInfo &tConfInfo,
                                       const vector<TMtAddr> &vctMtList);

    //主叫呼集呼叫
    EMMtclibErrorCode McuConfSiteCallCreateReq(const TSitecallInformation &tCall);

    //结束会议
    EMMtclibErrorCode McuConfEndCmd(void);

    //输入会议密码应答
    EMMtclibErrorCode McuConfEnterPwdAck(LPCSTR lpszPwd);

    //呼叫MCU(并获取MCU会议列表)
    EMMtclibErrorCode McuConfCallMcuReq(const TMtAddr &tMcu, u16 wCallRate);

    //加入会议
    EMMtclibErrorCode McuConfJoinConfAck(const TConfBaseInfo &tConfInfo);

    //邀请终端
    EMMtclibErrorCode McuConfInviteMtCmd(const TMtAddr &tAddr);

    //请退终端
    EMMtclibErrorCode McuConfDropMtCmd(const TMtId &tMt);

    //申请主席
    EMMtclibErrorCode McuConfApplyChairmanCmd(void);

    //申请发言
    EMMtclibErrorCode McuConfApplySpeakerCmd(void);

    //申请混音
    EMMtclibErrorCode McuConfApplyMixingCmd(void);

    //接受主席申请
    EMMtclibErrorCode McuConfAcceptChairmanCmd(const TMtId &tMt, BOOL32 bAccept);

    //接受发言申请
    EMMtclibErrorCode McuConfAcceptSpeakerCmd(const TMtId &tMt, BOOL32 bAccept);

    //接受混音申请
    EMMtclibErrorCode McuConfAcceptMixingCmd(const TMtId &tMt, BOOL32 bAccept);

    //指定主席
    EMMtclibErrorCode McuConfSpecChairmanCmd(const TMtId &tMt);

    //指定发言
    EMMtclibErrorCode McuConfSpecSpeakerReq(const TMtId &tMt);

    //取消主席
    EMMtclibErrorCode McuConfCancelChairmanReq(void);

    //取消发言
    EMMtclibErrorCode McuConfCancelSpeakerCmd(void);

    //选看终端(仅视频)
    EMMtclibErrorCode McuConfViewMtOnlyVideoCmd(TMtId &tMt);

    //选看终端(带音频)
    EMMtclibErrorCode McuConfViewMtWithAudioReq(TMtId &tMt,
                                                EmMediaType emViewType);

    //停止选看
    EMMtclibErrorCode McuConfStopViewCmd(void);

    //退出会议
    EMMtclibErrorCode McuConfQuitConfCmd(void);

    //开始轮询
    EMMtclibErrorCode McuConfStartPollCmd(EmMediaType emPollType, u16 wInterval,
                                          vector<TMtId> &vctMtList);

    //暂停轮询
    EMMtclibErrorCode McuConfPausePollCmd(void);

    //恢复轮询
    EMMtclibErrorCode McuConfResumePollCmd(void);

    //停止轮询
    EMMtclibErrorCode McuConfStopPollCmd(void);

    //发送短消息
    EMMtclibErrorCode McuConfSendMsgCmd(const TMtId &tMt, LPCSTR lpszMsg,
                                        EmSMSType emType = emSMSSingleLine,
                                        u8 byRollSpeed = 3, u8 byTimes = 1);

    //终端静音
    EMMtclibErrorCode McuConfMuteMtCmd(const TMtId &tMt, BOOL32 bMute);

    //终端哑音
    EMMtclibErrorCode McuConfDumbMtCmd(const TMtId &tMt, BOOL32 bDumb);

    //开始全体混音
    EMMtclibErrorCode McuConfStartEntireMixingReq(u8 byDepth = 10);

    //停止全体混音
    EMMtclibErrorCode McuConfStopEntireMixingReq(void);

    //开始画面合成
    EMMtclibErrorCode McuConfStartCPReq(const TMtVMPParam &tParam);

    //修改画面合成参数
    EMMtclibErrorCode McuConfEditCPParamReq(const TMtVMPParam &tParam);

    //停止画面合成
    EMMtclibErrorCode McuConfStopCPReq(void);

    //开始语音激励
    EMMtclibErrorCode McuConfStartVACReq(void);

    //停止语音激励
    EMMtclibErrorCode McuConfStopVACReq(void);

    //会议延时
    EMMtclibErrorCode McuConfProlongReq(u16 wMinute);

    //请求终端状态
    EMMtclibErrorCode McuConfGetMtStatusReq(const TMtId &tMt);

    //强制广播
    EMMtclibErrorCode McuConfStartForceBroadcastCmd(void);

    //停止强制广播
    EMMtclibErrorCode McuConfStopForceBroadcastCmd(void);

    //开始监控
    EMMtclibErrorCode McuConfStartMonitorReq(const TMtId &tMt);

    //停止监控
    EMMtclibErrorCode McuConfStopMonitorCmd(const TMtId &tMt);

    ///////////////////////////////////////////////////////////////////////////////
    //  14. MC多点会议接口
    ///////////////////////////////////////////////////////////////////////////////

    //会议扩展
    EMMtclibErrorCode McConfExtendReq(const TDialParam &tParam);

    //接受MC呼叫
    EMMtclibErrorCode McConfAcceptCallAck(const TMtId &tMt, BOOL32 bAccept);

    //MC工作模式设置
    EMMtclibErrorCode McConfSetModeReq(BOOL32 bEnable, EmMCMode emMode);

    //MC替换画面合成终端
    EMMtclibErrorCode McConfCPReplaceMtCmd(u8 byIndex, const TMtId &tMt);

    //MC画面合成自动风格设定
    EMMtclibErrorCode McConfSetAutoCPStyleCmd(BOOL32 bAuto);

    //MC画面合成参数设定(非自动画面合成状态下)
    EMMtclibErrorCode McConfSetCPParamCmd(EmInnerVMPStyle emStyle,
                                          const TMtId atMt[MAX_MC_CP_MEMBER_NUM]);

    //MC远遥终端
    EMMtclibErrorCode McConfControlRemoteMtReq(const TMtId &tMt);

    //MC开始终端轮询
    EMMtclibErrorCode McConfStartPollCmd(EmMediaType emType, u16 wInterval,
                                         const vector<CMt>& vctMtList);

    //MC停止终端轮询
    EMMtclibErrorCode McConfStopPollCmd(void);

    ///////////////////////////////////////////////////////////////////////////////
    //  15. 终端自身操作接口
    ///////////////////////////////////////////////////////////////////////////////

    //获取终端状态
    EMMtclibErrorCode MtGetStatusReq(void);

    //终端复位
    EMMtclibErrorCode MtResetCmd(void);

    //开始休眠
    EMMtclibErrorCode MtStartDormancyCmd(void);

    //停止休眠
    EMMtclibErrorCode MtStopDormancyCmd(void);

    //大文件传输
    EMMtclibErrorCode MtTransferBigFileReq(EmMtFile emType, const u8 *pbyBuf,
                                           u32 dwSize, u16 wTimedOut = 6000);

    //终端业务文件升级
    EMMtclibErrorCode MtUpgradeServiceReq(LPCSTR lpszFilename);


//LIB内部调用接口
protected:
    //获取等待消息1
    inline u16 GetWaitEvent1(void) const { return m_wWaitEvent1; }

    //获取等待消息2
    inline u16 GetWaitEvent2(void) const { return m_wWaitEvent2; }

    //发送下一条消息
    EMMtclibErrorCode PostNextMsg(void);

    //取消当前可取消的消息
    void CancelSendMsg(void);

    //清空
    void SetNull(void);

    //锁定数据
    inline void Lock(void) { EnterCriticalSection( &m_cSect ); }

    //解锁数据
    inline void Unlock(void) { LeaveCriticalSection( &m_cSect ); }

    //LIB发送消息
    EMMtclibErrorCode PostMsg(const TSendCMessage &tMsg);

    //向终端发送消息
    EMMtclibErrorCode PostMsgToMt(const TSendCMessage &tMsg);

    //唤醒终端
    void WakeupMt(u16 wEventID);

protected:
    u8                              m_abySendBuf[MAX_MSG_LEN];
    u16                             m_wWaitEvent1;
    u16                             m_wWaitEvent2;
    u16                             m_wTimerEvent;
    u32                             m_dwLibNode;
    queue<TSendCMessage>            m_queueSendMsg;

    u32                             m_dwMtNode;
    u32                             m_dwMtIID;

    HANDLE                          m_hEvent;//退出等待事件

private:
    CRITICAL_SECTION                m_cSect;

    friend class CMessageProcWnd;
    friend class CMtclibSsnData;
};

#endif//_MTCLIBINTERFACE_20070528_H_