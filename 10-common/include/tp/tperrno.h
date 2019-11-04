#ifndef _h_tperrno_h__
#define _h_tperrno_h__

#define TP_UMS_ChairIsUMS		10000				//主席是UMS
#define TP_UMS_ChairIsMT		10001				//主席是MT
#define TP_UMS_ChairIsMCU		10002				//主席是MCU
#define TP_UMS_SuperDropped		10003				//上级掉线
#define TP_UMS_ChairIsFailed    10009               //主席未上线 

#define TP_UMS_AdapterQuit		10004				//接入板掉线
#define TP_UMS_AllEpHungUp		10005				//所有会场挂断
#define TP_UMS_BasDisConnect	10006				//适配板掉线
#define TP_UMS_BasStartFail		10007				//适配开启失败
#define TP_UMS_MediaTransQuit	10008				//转发板掉线


#define TP_UMS_ChairIsB3CNS		10010				//主席是老版本CNS
#define TP_UMS_SpeakerVmpError  10011               //点名时VMP掉线，演讲时VMP掉线

#define TP_UMS_QuitAudMix       15000				//会议语音激励关闭：资源不足

//TvWall  to umc
#define Tp_UMS_TvWall_MTVmpFail 10050               // 资源不足，进入电视墙通道失败
#define TP_UMS_TvWall_InvalidMT 10051               // 无效终端，进入电视墙通道失败
#define TP_UMS_TvWall_BandError 10052               // 带宽不足，进入电视墙通道失败
#define TP_UMS_TvWall_VmpError  10053               // 合成器掉线，进入电视墙通道失败
#define TP_UMS_TvWall_VmpCapFail 10054              //为发言人时，终端不降分辨率进入通道，但画面无输出，给出提示信息：“合成能力不足”
#define TP_UMS_TvWall_AssignVmpFail 10055           // 添加画面合成器进入电视墙多画面通道, 提示"多画面通道不支持选看画面合成器"


//#define TP_UMS_Discard_Start    10100				
#define TP_UMS_Discard_AddEp    10101				//场景：统一开启讨论时，会场xx进入讨论失败 
#define TP_UMS_Discard_EpOnLine	10102				//场景：会场xx上线时，进入讨论失败：  
                                                    //注：上述两个消息m_dwReserve1填会场ID，m_dwReserve2填枚举值EmDiscussOprRes区分原因

#define TP_Discuss_StopByUms_NoVaildEp   10103   // 讨论内无有效成员，讨论结束
#define TP_Discuss_StopByUms_MixError    10104   // 混音板掉线，讨论结束
#define TP_Discuss_StopByUms_BasError    10105   // 适配板掉线，讨论结束
#define TP_Discuss_StopByUms_VmpError    10106   // 合成板掉线，讨论结束


// 
#define TP_UMS_VMP_Audience_ChanNoVid    10150      //合成器vip不足，且没有小码流和不支持降分辨率，普通会场xx进入合成器xx无图像 注：m_dwReserve1为会场ID，m_dwReserve2为合成器ID          
#define TP_UMS_VMP_Speaker_ChanNoVid     10151      //合成器vip不足，发言会场xx进入合成器xx无图像 注：m_dwReserve1为会场ID，m_dwReserve2为合成器ID          
#define TP_UMS_VMP_Dual_ChanNoVid        10152      //合成器vip不足，会场xx的双流进入合成器xx无图像 注：m_dwReserve1为会场ID，m_dwReserve2为合成器ID          
#define TP_UMS_VMP_GetVidFail            10153      //码流调度失败，会场xx进入合成器无图像 注：m_dwReserve1为会场ID，m_dwReserve2为合成器ID

#define TP_UMS_Poll_BasDisCnnt  10200               //适配掉线，轮询停止
#define TP_UMS_Poll_VmpDisCnnt  10201               //合成掉线，轮询停止
#define TP_UMS_Poll_EpNextBas	10202               //轮询跳过会场xx：适配资源不足   注：m_dwReserve1 为会场ID
#define TP_UMS_Poll_EpNextBW	10203               //轮询跳过会场xx：带宽资源不足   注：m_dwReserve1 为会场ID

#define TP_UMS_View_BasDisCnnt  10250               //CNC：适配不足，选看停止  UMC：适配掉线，会场XX选看停止  注：m_dwReserve1 为会场ID
#define TP_UMS_View_VmpDisCnnt  10251               //CNC：合成掉线，选看停止  UMC：合成掉线，会场XX选看停止  注：m_dwReserve1 为会场ID
#define TP_UMS_View_BWFull      10252               //CNC：带宽不足，选看停止  UMC：带宽不足，会场XX选看停止  注：m_dwReserve1 为会场ID
#define TP_UMS_View_NoVid       10253               //CNC：无视频源，选看停止  UMC：无视频源，会场XX选看停止  注：m_dwReserve1 为会场ID
#define TP_UMS_View_NoVmp       10254               //CNC：无法收看合成图像：画面合成资源不足  UMC：会场XX无法收看合成图像：画面合成资源不足  注：m_dwReserve1 为会场ID

#define TP_UMS_Dual_BasDisCnnt  10300               //适配掉线，双流停止
#define TP_UMS_Dual_MixDisCnnt  10301               //混音器掉线，双流停止
#define TP_UMS_Dual_BasFull     10302               //开启双流失败：适配资源不足

#define TP_ROLLCALLER_OFFLINE          10350              //点名者掉线，点名结束
#define Tp_ROLLCALL_MIX_ERROR          10351              //点名混音器错误
#define Tp_ROLLCALL_CREATE_CHAN_FAIL   10352              //上调码流或PUT音频错误
#define Tp_ROLLCALL_ALLTARGET_OFFLINE  10353              //未选择被点名人，开启点名失败
#define Tp_ROLLCALL_START_NO_TARGET    10354              //无被点名人在线，点名结束


#define TP_CONFAUDMIX_MIX_ERROR        10370              //会议混音，混音器错误
#define TP_CONFAUDMIX_STOP_NO_EP       10371              //会议混音，所有的会场掉线（定制混音模式）
 
#define TP_CONFAUDMIX_MIXCHAN_FULL     10372              //会议混音，混音通道满
#define TP_CONFAUDMIX_DELETE_SPEAKER   10373              //会议混音，混音时删除发言人

#define TP_UMS_FECC_NO_323MT			10380				// 会场远遥  非323终端
#define TP_UMS_FECC_CHANNEL_NOT_OPEN	10381               // 会场远遥  远遥通道未打开

#endif // _h_tperrno_h__
