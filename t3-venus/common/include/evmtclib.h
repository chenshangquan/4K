/*=============================================================================
模   块   名: 终端控制台业务功能库
文   件   名: evmtclib.h
相 关  文 件: 无
文件实现功能: mtclib 消息定义
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/05/31  4.0     王昊        创建
=============================================================================*/

#ifndef _EVMTCLIB_20070531_H_
#define _EVMTCLIB_20070531_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
//  a. 向界面发送的消息
///////////////////////////////////////////////////////////////////////////////
//1. 连接
    //连接成功，消息体：u32(终端IP地址，主机序)
    OSPEVENT( MTCLIB_DISP_CONNECT_ACK,                  MTCLIB_MSG_BGN );
    //连接失败，消息体：u32(终端IP地址，主机序)
    OSPEVENT( MTCLIB_DISP_CONNECT_NACK,                 MTCLIB_MSG_BGN + 1 );


//2. VOD消息
    //登录成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_LOGIN_ACK,                MTCLIB_MSG_BGN + 10 );
    //登录失败：消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_LOGIN_NACK,               MTCLIB_MSG_BGN + 11 );

    //退出成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_LOGOUT_ACK,               MTCLIB_MSG_BGN + 12 );
    //退出失败,消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_LOGOUT_NACK,              MTCLIB_MSG_BGN + 13 );

    //获取文件列表成功，消息体：TVODFile[]
    OSPEVENT( MTCLIB_DISP_VOD_GETFILELIST_ACK,          MTCLIB_MSG_BGN + 14 );
    //获取文件列表失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_GETFILELIST_NACK,         MTCLIB_MSG_BGN + 15 );

    //获取文件信息成功，消息体：TVODFile
    OSPEVENT( MTCLIB_DISP_VOD_GETFILEINFO_ACK,          MTCLIB_MSG_BGN + 16 );
    //获取文件信息失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_GETFILEINFO_NACK,         MTCLIB_MSG_BGN + 17 );

    //播放文件成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_PLAYFILE_ACK,             MTCLIB_MSG_BGN + 18 );
    //播放文件失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_PLAYFILE_NACK,            MTCLIB_MSG_BGN + 19 );

    //暂停播放成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_PAUSEFILE_ACK,            MTCLIB_MSG_BGN + 20 );
    //暂停播放失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_PAUSEFILE_NACK,           MTCLIB_MSG_BGN + 21 );

    //恢复播放成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_RESUMEFILE_ACK,           MTCLIB_MSG_BGN + 22 );
    //暂停播放失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_RESUMEFILE_NACK,          MTCLIB_MSG_BGN + 23 );

    //停止播放成功，消息体：EmVODState(注：将ev_VODStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_VOD_STOPFILE_ACK,             MTCLIB_MSG_BGN + 24 );
    //停止播放失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_VOD_STOPFILE_NACK,            MTCLIB_MSG_BGN + 25 );

    //VOD状态通知，消息体：EmVODState(注：如果已发送ACK，则不再发送该消息)
    OSPEVENT( MTCLIB_DISP_VOD_STATE_NOTIF,              MTCLIB_MSG_BGN + 26 );
    //播放进度通知，消息体：u32(总时长，主机序) + u32(已播放时长，主机序)
    OSPEVENT( MTCLIB_DISP_VOD_PROGRESS_NOTIF,           MTCLIB_MSG_BGN + 27 );


//3. 矩阵消息
    //获取所有矩阵方案成功，消息体：u8(方案数) + TAVInnerMatrixScheme[]
    OSPEVENT( MTCLIB_DISP_MATRIX_GETALLINNERSCHEME_ACK, MTCLIB_MSG_BGN + 35 );
    //获取所有矩阵方案失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_GETALLINNERSCHEME_NACK,MTCLIB_MSG_BGN + 36 );

    //获取指定矩阵方案成功，消息体：TAVInnerMatrixScheme
    OSPEVENT( MTCLIB_DISP_MATRIX_GETINNERSCHEME_ACK,    MTCLIB_MSG_BGN + 37 );
    //获取指定矩阵方案失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_GETINNERSCHEME_NACK,   MTCLIB_MSG_BGN + 38 );

    //保存矩阵方案成功，消息体：TAVInnerMatrixScheme
    OSPEVENT( MTCLIB_DISP_MATRIX_SAVEINNERSCHEME_ACK,   MTCLIB_MSG_BGN + 39 );
    //保存矩阵方案失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_SAVEINNERSCHEME_NACK,  MTCLIB_MSG_BGN + 40 );
    //矩阵方案变更通知，消息体：TAVInnerMatrixScheme
    OSPEVENT( MTCLIB_DISP_MATRIX_INNERSCHEME_NOTIF,     MTCLIB_MSG_BGN + 41 );

    //设置当前矩阵方案成功，消息体：u8(方案索引)
    OSPEVENT( MTCLIB_DISP_MATRIX_SETCURSCHEME_ACK,      MTCLIB_MSG_BGN + 42 );
    //设置当前矩阵方案失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_SETCURSCHEME_NACK,     MTCLIB_MSG_BGN + 43 );
    //当前矩阵方案变更通知，消息体：u8(方案索引)
    //(注：ev_InnerMatrixSetCurSchemeInd和ev_InnerMatrixCurSchemeInd两条消息的处理)
    OSPEVENT( MTCLIB_DISP_MATRIX_CURSCHEME_NOTIF,       MTCLIB_MSG_BGN + 44 );

    //获取当前矩阵方案成功，消息体：u8(方案索引)
    OSPEVENT( MTCLIB_DISP_MATRIX_GETCURSCHEME_ACK,      MTCLIB_MSG_BGN + 45 );
    //获取当前矩阵方案失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_GETCURSCHEME_NACK,     MTCLIB_MSG_BGN + 46 );

    //当前视频源端口通知，消息体：EmVideoType + EmMtVideoPort
    OSPEVENT( MTCLIB_DISP_MATRIX_CURVIDEOSOURCE_NOTIF,  MTCLIB_MSG_BGN + 50 );
    //当前当前视频源(近端/远端)通知，消息体：EmSite
    OSPEVENT( MTCLIB_DISP_MATRIX_CURVIDEOSITE_NOTIF,    MTCLIB_MSG_BGN + 51 );
    //视频源名称通知(包括内置和外接)，消息体：TVideoSourceInfo
    OSPEVENT( MTCLIB_DISP_MATRIX_CURVIDEOSOURCENAME_NOTIF,  MTCLIB_MSG_BGN + 52 );

    //获取外接矩阵信息成功，消息体：TExternalMatrixInfo
    OSPEVENT( MTCLIB_DISP_MATRIX_GETOUTERINFO_ACK,      MTCLIB_MSG_BGN + 60 );
    //获取外接矩阵信息失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_GETOUTERINFO_NACK,     MTCLIB_MSG_BGN + 61 );
    //外接矩阵信息通知，消息体：TExternalMatrixInfo
    OSPEVENT( MTCLIB_DISP_MATRIX_OUTERINFO_NOTIF,       MTCLIB_MSG_BGN + 62 );

    //设置外接矩阵视频源成功，消息体：TVideoSourceInfo
    OSPEVENT( MTCLIB_DISP_MATRIX_SETOUTERVIDEOSOURCE_ACK,   MTCLIB_MSG_BGN + 63 );
    //设置外接矩阵视频源失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_SETOUTERVIDEOSOURCE_NACK,  MTCLIB_MSG_BGN + 64 );

    //获取外接矩阵视频源成功，消息体：TVideoSourceInfo[]
    OSPEVENT( MTCLIB_DISP_MATRIX_GETOUTERVIDEOSOURCE_ACK,   MTCLIB_MSG_BGN + 65 );
    //获取外接矩阵视频源失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MATRIX_GETOUTERVIDEOSOURCE_NACK,  MTCLIB_MSG_BGN + 66 );
    //所有视频源信息通知，消息体：TVideoSourceInfo[]
    OSPEVENT( MTCLIB_DISP_MATRIX_ALLVIDEOSOURCEINFO_NOTIF,  MTCLIB_MSG_BGN + 67 );


//4. 配置消息
    //H.323配置通知，消息体：TH323Cfg
    OSPEVENT( MTCLIB_DISP_CONFIG_H323_NOTIF,            MTCLIB_MSG_BGN + 90 );
    //用户配置通知，消息体：TUserCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_USER_NOTIF,            MTCLIB_MSG_BGN + 91 );
    //OSD配置通知，消息体：TOsdCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_OSD_NOTIF,             MTCLIB_MSG_BGN + 92 );
    //以太网配置通知，消息体：u8(以太网索引  0 - eth0 ) + TEthnetInfo
    OSPEVENT( MTCLIB_DISP_CONFIG_ETHNET_NOTIF,          MTCLIB_MSG_BGN + 93 );
    //E1配置通知，消息体：TE1Config
    OSPEVENT( MTCLIB_DISP_CONFIG_E1_NOTIF,              MTCLIB_MSG_BGN + 94 );
    //串口信息配置通知，消息体：EmSerialType + TSerialCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_SERIAL_NOTIF,          MTCLIB_MSG_BGN + 95 );
    //路由配置通知，消息体：TRouteCfg[MT_MAX_ROUTE_NUM]
    OSPEVENT( MTCLIB_DISP_CONFIG_ROUTE_NOTIF,           MTCLIB_MSG_BGN + 100 );
    //PPPoE配置通知，消息体：TPPPOECfg
    OSPEVENT( MTCLIB_DISP_CONFIG_PPPOE_NOTIF,           MTCLIB_MSG_BGN + 101 );
    //网管配置通知，消息体：TSNMPCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_NETMANAGEMENT_NOTIF,   MTCLIB_MSG_BGN + 102 );
    //IPQoS配置通知，消息体：TIPQos
    OSPEVENT( MTCLIB_DISP_CONFIG_IPQOS_NOTIF,           MTCLIB_MSG_BGN + 103 );
    //防火墙配置通知，消息体：TEmbedFwNatProxy
    OSPEVENT( MTCLIB_DISP_CONFIG_EMBEDFIREWALL_NOTIF,   MTCLIB_MSG_BGN + 104 );
    //静态映射配置通知，消息体：TNATMapAddr
    OSPEVENT( MTCLIB_DISP_CONFIG_NATMAP_NOTIF,          MTCLIB_MSG_BGN + 105 );
    //重传配置通知，消息体：TLostPackResend
    OSPEVENT( MTCLIB_DISP_CONFIG_RETRANSFER_NOTIF,      MTCLIB_MSG_BGN + 110 );
    //流媒体配置通知，消息体：TStreamMedia
    OSPEVENT( MTCLIB_DISP_CONFIG_STREAM_NOTIF,          MTCLIB_MSG_BGN + 111 );
    //视频编码参数通知，消息体：EmVideoType + TVideoEncodeParameter
    OSPEVENT( MTCLIB_DISP_CONFIG_VIDEOPARAM_NOTIF,      MTCLIB_MSG_BGN + 112 );
    //PC双流配置通知，消息体：TVideoParam
    OSPEVENT( MTCLIB_DISP_CONFIG_PCVIDEOPARAM_NOTIF,    MTCLIB_MSG_BGN + 113 );
    //优选协议配置通知，消息体：TAVPriorStrategy
    OSPEVENT( MTCLIB_DISP_CONFIG_AVPRIOR_NOTIF,         MTCLIB_MSG_BGN + 114 );
    //摄像头配置通知，消息体：u8(射像头索引号 1-6) + TCameraCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_CAMERA_NOTIF,          MTCLIB_MSG_BGN + 115 );
    //视频制式配置通知，消息体：TVideoStandard
    OSPEVENT( MTCLIB_DISP_CONFIG_VIDEOSTANDARD_NOTIF,   MTCLIB_MSG_BGN + 116 );
    //图像参数配置通知，消息体：TImageAdjustParam
    OSPEVENT( MTCLIB_DISP_CONFIG_IMAGEADJUST_NOTIF,     MTCLIB_MSG_BGN + 117 );
    //横幅参数通知，消息体：TBannerInfo
    OSPEVENT( MTCLIB_DISP_CONFIG_BANNERINFO_NOTIF,      MTCLIB_MSG_BGN + 118 );
    //串口控制配置通知，消息体：EmSerialType + TIPTransAddr
    OSPEVENT( MTCLIB_DISP_CONFIG_SERIALCTRL_NOTIF,      MTCLIB_MSG_BGN + 119 );
    //监控切换业务配置通知，消息体：TMonitorService
    OSPEVENT( MTCLIB_DISP_CONFIG_MONITORSERVICE_NOTIF,  MTCLIB_MSG_BGN + 120 );
    //双流比率通知，消息体：TDualRation
    OSPEVENT( MTCLIB_DISP_CONFIG_DUALRATIO_NOTIF,       MTCLIB_MSG_BGN + 125 );
    //内置MC配置通知，消息体：TInnerMcCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_INNERMC_NOTIF,         MTCLIB_MSG_BGN + 126 );
    //6610E内置GK配置通知，消息体：TInnerGKCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_INNERGK_NOTIF,         MTCLIB_MSG_BGN + 127 );
    //遥控器快捷键配置通知，消息体：TRapidKey
    OSPEVENT( MTCLIB_DISP_CONFIG_SHORTCUTKEY_NOTIF,     MTCLIB_MSG_BGN + 128 );
    //PCMT视频源通知，消息体：TCapType
    OSPEVENT( MTCLIB_DISP_CONFIG_PCMTVIDEOSOURCE_NOTIF, MTCLIB_MSG_BGN + 129 );
    //8010C VGA输出参数通知，消息体：TVgaOutCfg
    OSPEVENT( MTCLIB_DISP_CONFIG_VGAOUT_NOTIF,          MTCLIB_MSG_BGN + 130 );
    //回声抵消配置通知，消息体：BOOL32(TRUE = 开启 FALSE = 关闭)
    OSPEVENT( MTCLIB_DISP_CONFIG_AEC_NOTIF,             MTCLIB_MSG_BGN + 135 );
    //自动增益配置通知，消息体：BOOL32(TRUE = 开启 FALSE = 关闭)
    OSPEVENT( MTCLIB_DISP_CONFIG_AGC_NOTIF,             MTCLIB_MSG_BGN + 136 );
    //自动噪音抑制配置通知，消息体：BOOL32(TRUE = 开启 FALSE = 关闭)
    OSPEVENT( MTCLIB_DISP_CONFIG_ANS_NOTIF,             MTCLIB_MSG_BGN + 137 );
    //主视频输出配置通知，消息体：BOOL32(TRUE表示输出在Video)
    OSPEVENT( MTCLIB_DISP_CONFIG_MAINVIDEOTOVIDEO_NOTIF,MTCLIB_MSG_BGN + 138 );
    //VGA显示是否是本地配置通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_CONFIG_VGASHOWLOCAL_NOTIF,    MTCLIB_MSG_BGN + 139 );
    //第二路视频是否输出到VGA配置通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_CONFIG_SECONDVIDEOTOVGA_NOTIF,MTCLIB_MSG_BGN + 140 );
    //是否发送静态图片配置通知，消息体：(BOOL32 TRUE = 开始发送 FALSE = 停止发送)
    OSPEVENT( MTCLIB_DISP_CONFIG_SENDSTATICPIC_NOTIF,   MTCLIB_MSG_BGN + 145 );
    //是否使用DHCP配置通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_CONFIG_USEDHCP_NOTIF,         MTCLIB_MSG_BGN + 146 );
    //呼叫码率配置通知，消息体：u32(主机序)
    OSPEVENT( MTCLIB_DISP_CONFIG_CALLRATE_NOTIF,        MTCLIB_MSG_BGN + 147 );
    //网关配置通知，消息体：u32(主机序)
    OSPEVENT( MTCLIB_DISP_CONFIG_GATEWAY_NOTIF,         MTCLIB_MSG_BGN + 148 );
    //DNS服务器IP地址通知，消息体：u32(主机序)
    OSPEVENT( MTCLIB_DISP_CONFIG_DNSSERVERIP_NOTIF,     MTCLIB_MSG_BGN + 149 );
    //MTU时间配置通知，消息体：u32(主机序)
    OSPEVENT( MTCLIB_DISP_CONFIG_MTU_NOTIF,             MTCLIB_MSG_BGN + 150 );
    //TCP、UDP起始端口配置通知，消息体：u16(TCP 起始端口号，主机序)
    //                                + u16(UDP 起始端口号，主机序)
    OSPEVENT( MTCLIB_DISP_CONFIG_TCPUDPSTARTPORT_NOTIF, MTCLIB_MSG_BGN + 151 );
    //语言类型通知，消息体：EmLanguage
    OSPEVENT( MTCLIB_DISP_CONFIG_LANGUAGE_NOTIF,        MTCLIB_MSG_BGN + 152 );
    //LDAP服务器配置通知，消息体：s8[MT_MAX_LDAPSERVER_NAME_LEN](域名)
    OSPEVENT( MTCLIB_DISP_CONFIG_LDAP_NOTIF,            MTCLIB_MSG_BGN + 153 );
    //麦克风增益控制配置通知，消息体：u8
    OSPEVENT( MTCLIB_DISP_CONFIG_MICADJUST_NOTIF,       MTCLIB_MSG_BGN + 154 );
    //编码音量配置通知，消息体：u8
    OSPEVENT( MTCLIB_DISP_CONFIG_ENCVOL_NOTIF,          MTCLIB_MSG_BGN + 155 );
    //解码音量配置通知，消息体：u8
    OSPEVENT( MTCLIB_DISP_CONFIG_DECVOL_NOTIF,          MTCLIB_MSG_BGN + 160 );
    //终端系统时间通知，消息体：TMtKdvTime
    OSPEVENT( MTCLIB_DISP_CONFIG_SYSTIME_NOTIF,         MTCLIB_MSG_BGN + 161 );


//5. 快照消息
    //获取快照信息成功，消息体：TSnapInfo
    OSPEVENT( MTCLIB_DISP_SNAPSHOT_GETINFO_ACK,         MTCLIB_MSG_BGN + 300 );
    //获取快照信息失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_SNAPSHOT_GETINFO_NACK,        MTCLIB_MSG_BGN + 301 );
    //快照信息通知(处理ev_SnapshotInd和ev_SnapshotInfoInd)，消息体：TSnapInfo
    OSPEVENT( MTCLIB_DISP_SNAPSHOT_INFO_NOTIF,          MTCLIB_MSG_BGN + 302 );

    //快照信息清空通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_SNAPSHOT_CLEAR_NOTIF,         MTCLIB_MSG_BGN + 303 );


//6. FXO消息
    //呼叫成功，消息体：EmFxoState(注：将ev_FxoCallLinkStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_FXO_CALL_ACK,                 MTCLIB_MSG_BGN + 320 );
    //呼叫失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_FXO_CALL_NACK,                MTCLIB_MSG_BGN + 321 );

    //电话呼入通知，消息体：s8*(对方号码)
    OSPEVENT( MTCLIB_DISP_FXO_CALLINCOMING_NOTIF,       MTCLIB_MSG_BGN + 322 );
    //本地超时通知，消息体：无
    OSPEVENT( MTCLIB_DISP_FXO_LOCALTIMEDOUT_NOTIF,      MTCLIB_MSG_BGN + 323 );
    //对端超时通知，消息体：无
    OSPEVENT( MTCLIB_DISP_FXO_PEERTIMEDOUT_NOTIF,       MTCLIB_MSG_BGN + 324 );
    //呼叫状态通知，消息体：EmFxoState(注：如果已发送ACK，则不再发送该消息)
    OSPEVENT( MTCLIB_DISP_FXO_STATE_NOTIF,              MTCLIB_MSG_BGN + 325 );


//7. 地址簿消息
    //地址簿注册成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_REGISTER_ACK,        MTCLIB_MSG_BGN + 350 );
    //地址簿注册失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_REGISTER_NACK,       MTCLIB_MSG_BGN + 351 );

    //地址簿注销成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_UNREGISTER_ACK,      MTCLIB_MSG_BGN + 352 );
    //地址簿注销失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_UNREGISTER_NACK,     MTCLIB_MSG_BGN + 353 );

    //添加地址簿条目成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDENTRY_ACK,        MTCLIB_MSG_BGN + 354 );
    //添加地址簿条目失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDENTRY_NACK,       MTCLIB_MSG_BGN + 355 );
    //添加地址簿条目通知，消息体：TADDRENTRY(将ADDRBOOK_REFRESHENTRY_NOTIF处理拆分而来)
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDENTRY_NOTIF,      MTCLIB_MSG_BGN + 356 );

    //修改地址簿条目成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITENTRY_ACK,       MTCLIB_MSG_BGN + 357 );
    //修改地址簿条目失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITENTRY_NACK,      MTCLIB_MSG_BGN + 358 );
    //修改地址簿条目通知，消息体：TADDRENTRY(将ADDRBOOK_REFRESHENTRY_NOTIF处理拆分而来)
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITENTRY_NOTIF,     MTCLIB_MSG_BGN + 359 );

    //删除地址簿条目成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELENTRY_ACK,        MTCLIB_MSG_BGN + 360 );
    //删除地址簿条目失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELENTRY_NACK,       MTCLIB_MSG_BGN + 361 );
    //删除地址簿条目通知，消息体：无；GetEntryIndex包含删除的条目
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELENTRY_NOTIF,      MTCLIB_MSG_BGN + 362 );

    //添加会议组成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDGROUP_ACK,        MTCLIB_MSG_BGN + 363 );
    //添加会议组失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDGROUP_NACK,       MTCLIB_MSG_BGN + 364 );
    //添加会议组通知，消息体：TADDRMULTISETENTRY(将ADDRBOOK_REFRESHMULSETENTRY_NOTIF处理拆分而来)
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDGROUP_NOTIF,      MTCLIB_MSG_BGN + 365 );

    //修改会议组成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITGROUP_ACK,       MTCLIB_MSG_BGN + 366 );
    //修改会议组失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITGROUP_NACK,      MTCLIB_MSG_BGN + 367 );
    //修改会议组通知，消息体：TADDRMULTISETENTRY(将ADDRBOOK_REFRESHMULSETENTRY_NOTIF处理拆分而来)
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_EDITGROUP_NOTIF,     MTCLIB_MSG_BGN + 368 );

    //删除会议组成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELGROUP_ACK,        MTCLIB_MSG_BGN + 369 );
    //删除会议组失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELGROUP_NACK,       MTCLIB_MSG_BGN + 370 );
    //删除会议组通知，消息体：无；GetEntryIndex包含删除的会议组
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELGROUP_NOTIF,      MTCLIB_MSG_BGN + 371 );

    //向会议组添加条目成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDENTRYTOGROUP_ACK, MTCLIB_MSG_BGN + 372 );
    //向会议组添加条目失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_ADDENTRYTOGROUP_NACK,MTCLIB_MSG_BGN + 373 );

    //从会议组删除条目成功，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELENTRYFROMGROUP_ACK,   MTCLIB_MSG_BGN + 374 );
    //从会议组删除条目失败，消息体：无
    OSPEVENT( MTCLIB_DISP_ADDRBOOK_DELENTRYFROMGROUP_NACK,  MTCLIB_MSG_BGN + 375 );


//8. 监控消息
    //监控参数通知，消息体：u8[2](第一路视频和音频的真实载荷类型)
    //                    + u8[2](第一路视频和音频的动态载荷类型)
    //                    + TEncryptKey[2](第一路视频和音频的密钥)
    //                    + EmSite(本地or远端)
    OSPEVENT( MTCLIB_DISP_MONITOR_PARAM_NOTIF,          MTCLIB_MSG_BGN + 390 );


//9. 用户消息
    //获取用户列表成功，消息体：CUserFullInfo[16]
    OSPEVENT( MTCLIB_DISP_USER_GETLIST_ACK,             MTCLIB_MSG_BGN + 400 );
    //获取用户列表失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_USER_GETLIST_NACK,            MTCLIB_MSG_BGN + 401 );
    //用户信息变更通知，消息体：CUserFullInfo[16]
    OSPEVENT( MTCLIB_DISP_USER_LIST_NOTIF,              MTCLIB_MSG_BGN + 402 );

    //添加用户成功，消息体：无
    OSPEVENT( MTCLIB_DISP_USER_ADD_ACK,                 MTCLIB_MSG_BGN + 403 );
    //添加用户失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_USER_ADD_NACK,                MTCLIB_MSG_BGN + 404 );

    //修改用户成功，消息体：无
    OSPEVENT( MTCLIB_DISP_USER_EDIT_ACK,                MTCLIB_MSG_BGN + 405 );
    //修改用户失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_USER_EDIT_NACK,               MTCLIB_MSG_BGN + 406 );

    //删除用户成功，消息体：CUserFullInfo
    OSPEVENT( MTCLIB_DISP_USER_DEL_ACK,                 MTCLIB_MSG_BGN + 407 );
    //删除用户失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_USER_DEL_NACK,                MTCLIB_MSG_BGN + 408 );


//10. 点对点会议消息
    //呼叫成功，消息体：TLinkState(将ev_CallLinkStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_P2P_CALL_ACK,                 MTCLIB_MSG_BGN + 450 );
    //呼叫失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_P2P_CALL_NACK,                MTCLIB_MSG_BGN + 451 );

    //链路状态通知，消息体：TLinkState(注：如果已发送ACK，则不再发送该消息)
    OSPEVENT( MTCLIB_DISP_P2P_STATE_NOTIF,              MTCLIB_MSG_BGN + 452 );

    //呼叫到来通知，消息体：TDialParam
    OSPEVENT( MTCLIB_DISP_P2P_CALLINCOMING_NOTIF,       MTCLIB_MSG_BGN + 453 );


//11. MCU多点会议消息
    //创会成功，消息体：TLinkState(将ev_CallLinkStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_MCU_CREATECONF_ACK,           MTCLIB_MSG_BGN + 490 );
    //创会失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_CREATECONF_NACK,          MTCLIB_MSG_BGN + 491 );

    //链路状态，消息体：TLinkState(注：如果已发送ACK，则不再发送该消息)
    OSPEVENT( MTCLIB_DISP_MCU_STATE_NOTIF,              MTCLIB_MSG_BGN + 492 );

    //主叫呼集呼叫成功，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_MCU_SITECALLCREATE_ACK,       MTCLIB_MSG_BGN + 495 );
    //主叫呼集呼叫失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_SITECALLREATE_NACK,       MTCLIB_MSG_BGN + 496 );
    //主叫呼集呼叫通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_MCU_SITECALLCREATE_NOTIF,     MTCLIB_MSG_BGN + 497 );

    //呼叫MCU(并获取MCU会议列表)成功，消息体：TLinkState(将ev_CallLinkStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_MCU_CALLMCU_ACK,              MTCLIB_MSG_BGN + 500 );
    //呼叫MCU(并获取MCU会议列表)失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_CALLMCU_NACK,             MTCLIB_MSG_BGN + 501 );

    //请退终端失败通知，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_DROPMTFAIL_NOTIF,         MTCLIB_MSG_BGN + 505 );

    //指定发言人成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_SPECSPEAKER_ACK,          MTCLIB_MSG_BGN + 506 );
    //指定发言人失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_SPECSPEAKER_NACK,         MTCLIB_MSG_BGN + 507 );

    //取消主席成功，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_CANCELCHAIRMAN_ACK,       MTCLIB_MSG_BGN + 510 );
    //取消主席失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_CANCELCHAIRMAN_NACK,      MTCLIB_MSG_BGN + 511 );
    //取消主席通知，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_CANCELCHAIRMAN_NOTIF,     MTCLIB_MSG_BGN + 512 );

    //带音频选看成功，消息体：BOOL32(TRUE = 选看成功 FALSE = 选看失败)
    OSPEVENT( MTCLIB_DISP_MCU_VIEWMTWITHAUDIO_ACK,      MTCLIB_MSG_BGN + 515 );
    //带音频选看失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_VIEWMTWITHAUDIO_NACK,     MTCLIB_MSG_BGN + 516 );
    //带音频选看通知，消息体：BOOL32(TRUE = 选看成功 FALSE = 选看失败)
    OSPEVENT( MTCLIB_DISP_MCU_VIEWMTWITHAUTIO_NOTIF,    MTCLIB_MSG_BGN + 517 );

    //取消选看通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPVIEW_NOTIF,           MTCLIB_MSG_BGN + 518 );

    //开始全体混音成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTENTIREMIXING_ACK,    MTCLIB_MSG_BGN + 525 );
    //开始全体混音失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STARTENTIREMIXING_NACK,   MTCLIB_MSG_BGN + 526 );
    //开始全体混音通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTENTIREMIXING_NOTIF,  MTCLIB_MSG_BGN + 527 );

    //停止全体混音成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPENTIREMIXING_ACK,     MTCLIB_MSG_BGN + 528 );
    //停止全体混音失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STOPENTIREMIXING_NACK,    MTCLIB_MSG_BGN + 529 );
    //停止全体混音通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPENTIREMIXING_NOTIF,   MTCLIB_MSG_BGN + 530 );

    //开始画面合成成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTCP_ACK,              MTCLIB_MSG_BGN + 535 );
    //开始画面合成失败，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_STARTCP_NACK,             MTCLIB_MSG_BGN + 536 );
    //开始画面合成通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTCP_NOTIF,            MTCLIB_MSG_BGN + 537 );

    //修改画面合成参数成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_EDITCPPARAM_ACK,          MTCLIB_MSG_BGN + 538 );
    //修改画面合成参数失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_EDITCPPARAM_NACK,         MTCLIB_MSG_BGN + 539 );
    //修改画面合成参数通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_EDITCPPARAM_NOTIF,        MTCLIB_MSG_BGN + 540 );

    //停止画面合成成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPCP_ACK,               MTCLIB_MSG_BGN + 541 );
    //停止画面合成失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STOPCP_NACK,              MTCLIB_MSG_BGN + 542 );
    //停止画面合成通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPCP_NOTIF,             MTCLIB_MSG_BGN + 543 );

    //开始语音激励成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTVAC_ACK,             MTCLIB_MSG_BGN + 560 );
    //开始语音激励失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STARTVAC_NACK,            MTCLIB_MSG_BGN + 561 );
    //开始语音激励通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STARTVAC_NOTIF,           MTCLIB_MSG_BGN + 562 );

    //停止语音激励成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPVAC_ACK,              MTCLIB_MSG_BGN + 563 );
    //停止语音激励失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STOPVAC_NACK,             MTCLIB_MSG_BGN + 564 );
    //停止语音激励通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_STOPVAC_NOTIF,            MTCLIB_MSG_BGN + 565 );

    //会议延时成功，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_PROLONG_ACK,              MTCLIB_MSG_BGN + 575 );
    //会议延时失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_PROLONG_NACK,             MTCLIB_MSG_BGN + 576 );
    //会议延时通知，消息体：BOOL32(TRUE = 同意 FALSE = 拒绝)
    OSPEVENT( MTCLIB_DISP_MCU_PROLONG_NOTIF,            MTCLIB_MSG_BGN + 577 );

    //获取终端状态成功，消息体：TMtId + TTerStatus
    OSPEVENT( MTCLIB_DISP_MCU_GETMTSTATUS_ACK,          MTCLIB_MSG_BGN + 585 );
    //获取终端状态失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_GETMTSTATUS_NACK,         MTCLIB_MSG_BGN + 586 );
    //终端状态通知，消息体：TMtId + TTerStatus
    OSPEVENT( MTCLIB_DISP_MCU_MTSTATUS_NOTIF,           MTCLIB_MSG_BGN + 587 );

    //开始监控成功，消息体：TMtId + u32(目标终端IP地址，如果失败则为0，主机序)
    //                    + u16(音频端口，主机序) + u16(视频端口，主机序)
    //                    + u8(音频真实载荷值) + u8(视频真实载荷值)
    //                    + EmEncryptArithmetic(音频加密类型)
    //                    + EmEncryptArithmetic(视频加密类型)
    //                    + u32(音频动态载荷，主机序)
    //                    + TEncryptKey(音频加密信息)
    //                    + u32(视频动态载荷，主机序)
    //                   + TEncryptKey(视频加密信息)
    OSPEVENT( MTCLIB_DISP_MCU_STARTMONITOR_ACK,         MTCLIB_MSG_BGN + 590 );
    //开始监控失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MCU_STARTMONITOR_NACK,        MTCLIB_MSG_BGN + 591 );


    //终端密码验证请求，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_ENTERPWD_REQ,             MTCLIB_MSG_BGN + 650 );
    //终端加入会议请求，消息体：TConfListInfo
    OSPEVENT( MTCLIB_DISP_MCU_JOINCONF_REQ,             MTCLIB_MSG_BGN + 651 );
    //终端号通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_MTID_NOTIF,               MTCLIB_MSG_BGN + 652 );
    //终端主席申请通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_APPLYCHAIRMAN_NOTIF,      MTCLIB_MSG_BGN + 653 );
    //终端发言申请通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_APPLYSPEAKER_NOTIF,       MTCLIB_MSG_BGN + 654 );
    //终端混音申请通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_APPLYMIXING_NOTIF,        MTCLIB_MSG_BGN + 655 );
    //当前视频源终端，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_CURVIDEOSOURCE_NOTIF,     MTCLIB_MSG_BGN + 656 );
    //终端列表通知，消息体：TMtInfo[]
    OSPEVENT( MTCLIB_DISP_MCU_MTLIST_NOTIF,             MTCLIB_MSG_BGN + 657 );
    //主席终端通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_CHAIRMAN_NOTIF,           MTCLIB_MSG_BGN + 658 );
    //发言人通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MCU_SPEAKER_NOTIF,            MTCLIB_MSG_BGN + 659 );
    //短消息通知，消息体：s8[]
    OSPEVENT( MTCLIB_DISP_MCU_SHORTMSG_NOTIF,           MTCLIB_MSG_BGN + 660 );
    //会议轮询状态通知，消息体：TMtPollInfo
    OSPEVENT( MTCLIB_DISP_MCU_POLLSTATUS_NOTIF,         MTCLIB_MSG_BGN + 670 );
    //邀请终端失败通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_MCU_INVITEMTFAIL_NOTIF,       MTCLIB_MSG_BGN + 671 );
    //会议信息通知，消息体：TMtConfInfo
    OSPEVENT( MTCLIB_DISP_MCU_CONFINFO_NOTIF,           MTCLIB_MSG_BGN + 672 );
    //会议即将结束通知，消息体：u16(剩余时间，主机序)
    OSPEVENT( MTCLIB_DISP_MCU_LEFTTIME_NOTIF,           MTCLIB_MSG_BGN + 673 );
    //画面合成参数通知，消息体：TMtVMPParam
    OSPEVENT( MTCLIB_DISP_MCU_CPPARAM_NOTIF,            MTCLIB_MSG_BGN + 674 );
    //简单会议信息，消息体：TMtSimpConfInfo
    OSPEVENT( MTCLIB_DISP_MCU_SIMCONFINFO_NOTIF,        MTCLIB_MSG_BGN + 675 );
    //消息体同步通知，消息体：无
    OSPEVENT( MTCLIB_DISP_MCU_UISYNCHRONIZE_NOTIF,      MTCLIB_MSG_BGN + 676 );
    //会议加密通知，消息体：BOOL32
    OSPEVENT( MTCLIB_DISP_MCU_CONFENCRYPTED_NOTIF,      MTCLIB_MSG_BGN + 677 );


//12. MC多点会议消息
    //会议扩展成功，消息体：TLinkState(将ev_mcCallLinkStateInd处理拆分而来)
    OSPEVENT( MTCLIB_DISP_MC_CONFEXTEND_ACK,            MTCLIB_MSG_BGN + 730 );
    //会议扩展失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MC_CONFEXTEND_NACK,           MTCLIB_MSG_BGN + 731 );

    //工作模式设置成功，消息体：BOOL32 + EmMCMode
    OSPEVENT( MTCLIB_DISP_MC_SETMODE_ACK,               MTCLIB_MSG_BGN + 735 );
    //工作模式设置失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MC_SETMODE_NACK,              MTCLIB_MSG_BGN + 736 );
    //工作模式通知，消息体：BOOL32 + EmMCMode
    OSPEVENT( MTCLIB_DISP_MC_MODE_NOTIF,                MTCLIB_MSG_BGN + 737 );

    //画面合成是否自动通知，消息体：BOOL32(TRUE = 自动 FALSE = 指定风格)
    OSPEVENT( MTCLIB_DISP_MC_AUTOCPSTYLE_NOTIF,         MTCLIB_MSG_BGN + 740 );

    //画面合成参数通知，消息体：EmInnerVMPStyle + TMtId[6]
    OSPEVENT( MTCLIB_DISP_MC_CPPARAM_NOTIF,             MTCLIB_MSG_BGN + 741 );

    //远遥终端成功，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MC_CONTROLREMOTEMT_ACK,       MTCLIB_MSG_BGN + 760 );
    //远遥终端失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_MC_CONTROLREMOTEMT_NACK,      MTCLIB_MSG_BGN + 761 );
    //远遥终端通知，消息体：TMtId
    OSPEVENT( MTCLID_DISP_MC_CONTROLREMOTEMT_NOTIF,     MTCLIB_MSG_BGN + 762 );

    //终端轮询状态通知，消息体：TMtPollInfo
    OSPEVENT( MTCLIB_DISP_MC_POLLSTATUS_NOTIF,          MTCLIB_MSG_BGN + 765 );

    //MC呼入请求通知，消息体：TMtId + TDialParam
    OSPEVENT( MTCLIB_DISP_MC_CALLINCOMING_NOTIF,        MTCLIB_MSG_BGN + 780 );
    //MC能力通知，消息体：BOOL32(是否允许扩展会议) + BOOL32(是否激活)
    OSPEVENT( MTCLIB_DISP_MC_CAPABILITY_NOTIF,          MTCLIB_MSG_BGN + 781 );
    //混音成员通知，消息体：TMtId[6]
    //注：现有设计混音与画面合成绑定，所以成员相同，但消息处理需要分别对待，便于扩展
    OSPEVENT( MTCLIB_DISP_MC_MIXPARAM_NOTIF,            MTCLIB_MSG_BGN + 782 );
    //MC链路状态通知，消息体：TLinkState(注：如果已发送ACK，则不再发送该消息)
    OSPEVENT( MTCLIB_DISP_MC_STATE_NOTIF,               MTCLIB_MSG_BGN + 783 );
    //终端哑音通知，消息体：TMtId + BOOL32
    OSPEVENT( MTCLIB_DISP_MC_DUMB_NOTIF,                MTCLIB_MSG_BGN + 784 );
    //发言人通知，消息体：TMtId
    OSPEVENT( MTCLIB_DISP_MC_SPEAKER_NOTIF,             MTCLIB_MSG_BGN + 785 );


//13. 终端自身操作消息
    //获取终端状态成功，消息体：TTerStatus
    OSPEVENT( MTCLIB_DISP_SELF_GETMTSTATUS_ACK,         MTCLIB_MSG_BGN + 820 );
    //获取终端状态失败，消息体：无；含错误码
    OSPEVENT( MTCLIB_DISP_SELF_GETMTSTATUS_NACK,        MTCLIB_MSG_BGN + 821 );
    //终端状态通知，消息体：TTerStatus
    OSPEVENT( MTCLIB_DISP_SELF_MTSTATUS_NOTIF,          MTCLIB_MSG_BGN + 822 );

    //待机状态通知，消息体：BOOL32(TURE = 待机 FALSE = 工作)
    OSPEVENT( MTCLIB_DISP_SELF_DORMANCYSTATE_NOTIF,     MTCLIB_MSG_BGN + 825 );

    //传输大文件成功，消息体：TFileTransfer
    OSPEVENT( MTCLIB_DISP_SELF_TRANSFERBIGFILE_ACK,     MTCLIB_MSG_BGN + 830 );
    //传输大文件失败，消息体：TFileTransfer
    OSPEVENT( MTCLIB_DISP_SELF_TRANSFERBIGFILE_NACK,    MTCLIB_MSG_BGN + 831 );
    //传输进度通知，消息体：u16(精确到小数点后一位)
    OSPEVENT( MTCLIB_DISP_SELF_TRANSFERPROGRESS_NOTIF,  MTCLIB_MSG_BGN + 832 );
    //传输完毕通知，消息体：TFileTransfer
    OSPEVENT( MTCLIB_DISP_SELF_TRANSFEREND_NOTIF,       MTCLIB_MSG_BGN + 833 );

    //业务文件升级成功，消息体：无
    OSPEVENT( MTCLIB_DISP_SELF_UPGRADESERVICE_ACK,      MTCLIB_MSG_BGN + 840 );
    //业务文件升级失败，消息体：无
    OSPEVENT( MTCLIB_DISP_SELF_UPGRADESERVICE_NACK,     MTCLIB_MSG_BGN + 841 );

    //GK注册状态通知，消息体：BOOL32(TRUE = 注册成功 FALSE = 注册失败)
    OSPEVENT( MTCLIB_DISP_SELF_GKREGISTERRESULT_NOTIF,  MTCLIB_MSG_BGN + 845 );
    //CODEC错误码通知，消息体：u16
    OSPEVENT( MTCLIB_DISP_SELF_CODECERRORCODE_NOTIF,    MTCLIB_MSG_BGN + 846 );


//14. 特殊消息
    //超时，含错误码
    OSPEVENT( MTCLIB_DISP_TIMEOUT,                      MTCLIB_MSG_BGN + 1000 );
    //断链，消息体：u32(终端IP地址，网络序)
    OSPEVENT( MTCLIB_DISP_DISCONNECTED,                 MTCLIB_MSG_BGN + 1001 );
    //消息处理
    OSPEVENT( MTCLIB_MESSAGEPROC,                       MTCLIB_MSG_BGN + 1002 );


///////////////////////////////////////////////////////////////////////////////
//  b. LIB内部消息
///////////////////////////////////////////////////////////////////////////////
//1. 定时消息
    OSPEVENT( TIMER_WAIT_REPLY,                 EV_MTC_BGN + 1 );


#endif//_EVMTCLIB_20070531_H_