#ifndef __IMTCCONF_H__
#define __IMTCCONF_H__

#include "dispevent.h"
//#include "mcustruct.h"		// Mcu类型结构
#include "mtcmt.h"
#include "mtmisc.h"
#include <vector>
using std::vector;


typedef struct tagTerDumbStatus
{
public:
    TMtId   m_tMtId;
    BOOL32  m_bIsDumb;
}TerDumbStatus, *PTerDumbStatus;

typedef struct tagPollInfo
{
	s8 achSchemeName[ MT_MAX_NAME_LEN + 1 ];
	u32 dwIndex;
	TMtPollInfo tPollInfo;
	tagPollInfo() { memset(this, 0 , sizeof(tagPollInfo)); }
}TMtcPollInfo;


//定义混音模式
typedef enum EmMixMode
{
	emNoMix = 0,
		emWholeMix,
		emPartMix,
		emVacMix,
		emVacWholeMix,
		emVacPartMix,
};


class IMtcConf : public CDispEvent
{
public:
	/*功能	查询Mcu上当前正在召开的多点会议列表
	参数	terMcu	被查询的多点控制单元
	返回值	与会的会议列表
	说明	无*/
	virtual const TplArray<TConfBaseInfo>& GetConfs() const = 0;
	/*功能	是否正在等待创建（或加入）会议回应
	参数	无
	返回值	TRUE	正在等待创建（或加入）会议回应
		FALSE	没有正在等待创建（或加入）会议回应
	说明	非主席终端总是返回一个空的列表*/
	virtual BOOL32 IsWaitingCreateAck() const = 0;
	virtual BOOL32 IsWaitingJoinAck() const = 0;
	/*功能	是否正在多点会议中
	参数	pConfInfo	返回参数，若在多点会议中，返回参与的多点会议信息；可以传入NULL
	返回值	TRUE	在多点会议中
			FALSE	不在多点会议中
	说明	无*/
	virtual BOOL32 IsInConf(TMtConfInfo *pConfInfo = NULL) const = 0;
	/*功能	是否正在轮询
	参数	无
	返回值	TRUE	正在轮询中
			FALSE	不在轮询中
	说明	无*/
	virtual BOOL32 IsPolling() const = 0;
	/*功能	是否轮询暂停中
	参数	无
	返回值	TRUE	正被暂停
	说明	FALSE	没被暂停
	说明	无*/
	virtual BOOL32 IsPollingPaused() const = 0;
	/*功能	是否语言激励中
	参数	无
	返回值	TRUE	语言激励中
	说明	FALSE	没被语言激励
	说明	无*/
	virtual BOOL32 IsVAC() const = 0;
	/*功能	查询与会终端列表
	参数	无
	返回值	与会的终端列表
	说明	无*/
	virtual const vector<CMtcMt>& GetMts() const = 0;
	/*功能	查询终端是否发言终端
	参数	cMt	被查询的终端
	返回值	TRUE	是发言终端
			FALSE	非发言终端
	说明	无*/
	virtual BOOL32 IsSpeaker(const CMtcMt& cMt) const = 0;
	/*功能	查询终端是否主席终端
	参数	cMt	被查询的终端
	返回值	TRUE	是主席终端
			FALSE	非主席终端
	说明	无*/
	virtual BOOL32 IsChairman(const CMtcMt& cMt) const = 0;
    /*功能	查询终端是否插话
    参数	 
    返回值	TRUE	插话
    FALSE	非插话
    说明	无*/
    virtual BOOL32 IsChime() const = 0;
		/*功能	查询当前的会议信息
	参数	无
	返回值	当前的发言终端
	说明	无*/
	virtual const TMtConfInfo& GetConfInfo() const = 0;
		/*功能	查询指定McuIdMtId的终端
	参数	byMcuId	多点控制单元标识
			byMtId	终端标识
	返回值	如果查询到,返回终端指针,没有查询到返回NULL
	说明	无*/
	virtual const CMtcMt* ConfGetMt(u8 byMcuId, u8 byMtId) const = 0;
	/*功能	查询当前的发言终端
	参数	无
	返回值	当前的发言终端
	说明	无*/
	virtual const CMtcMt& GetSpeaker() const = 0;
	/*功能	查询当前的主席终端
	参数	无
	返回值	当前的主席终端
	说明	无*/
	virtual const CMtcMt& GetChairman() const = 0;
	/*功能	查询当前的视频源
	参数	无
	返回值	当前的视频源
	说明	无*/
	virtual const CMtcMt& GetVideoSource() const = 0;
	/*功能	查询当前mc选看终端
	参数	无
	返回值	
	说明	无*/
	virtual const CMtcMt& GetCurMCSelMT() const = 0;
	/*功能	查询当前申请发言的终端
	参数	无
	返回值	当前申请发言的终端列表
	说明	非主席终端总是返回一个空的列表*/
	virtual const vector<CMtcMt>& GetReqSpeakerMts() const = 0;
	/*功能	查询当前申请主席的终端
	参数	无
	返回值	当前申请主席的终端列表
	说明	非主席终端总是返回一个空的列表*/
	virtual const vector<CMtcMt>& GetReqChairmanMts() const = 0;
    /*功能	查询当前申请插话的终端
	参数	无
	返回值	当前申请插话的终端列表
	说明	非主席终端总是返回一个空的列表*/
	virtual const vector<CMtcMt>& GetReqChimeMts() const = 0;
	/*功能	更新会议列表
	参数	terMcu	用此MCU上的会议列表更新
	返回值	成功返回0;失败返回错误码
	说明	随后发送MTC_UI_CONFSLIST_UPDATED表明已更新*/
	virtual u16 UpdateConfsList(const TMtAddr &tMcu, u16 wBitRate) = 0;
	/*功能	申请加入会议
	参数	conf	试图加入的会议
	返回值	成功返回0;失败返回非0错误码
	说明	不在一个多点会议中才可以申请加入会议*/
	virtual u16 JoinConf(const TConfBaseInfo& tConfBaseInfo) = 0;
	/*功能	取消加入会议
	参数	u128ConfId	要加入的会议标识
	返回值	成功返回0;失败返回非0错误码
	说明	正在试图加入一个会议中才可以取消加入*/
	virtual u16 CancelJoinConf() = 0;
	/*功能	申请发言
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	若已是发言终端，则忽略*/
	virtual u16 ReqSpeak() = 0;
	/*功能	申请主席
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	若已是主席终端，则忽略*/
	virtual u16 ReqChairman() = 0;
    /*功能	申请插话
    参数	无
    返回值	成功返回0;失败返回非0错误码
    说明	若已是插话，则忽略*/
    virtual u16 ReqChime() = 0;
	/*功能	创建会议
	参数	dwMcuIp	Mcu IP 地址
			u16Bitrate 会议码率
			info	会议信息
			vMts	与会终端列表
	返回值	成功返回0;失败返回非0错误码
	说明	若已是发言终端，则没有*/
	virtual u16 CreateConf(const TMtAddr &tMcu, const TConfBaseInfo &info, 
							const vector<TMtAddr>& vMts ) = 0;
	virtual u16 CreateConf(const TMtAddr &tMcu, u16 wBitrate,
                        const TConfBaseInfo &info, const vector<TMtAddr>& vMts) = 0;
    // 进行主叫呼集呼叫
    virtual u16 CreateSiteCall(const TSitecallInformation &tSiteCallInfo) = 0;
	/*功能	与会终端主动退出会议
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	若已是发言终端，则没有*/
	virtual u16 QuitConf() = 0;
	/*功能	轮询终端
	参数	emType		轮训的类型 emMediaAV, emMediaVideo, emMediaAdieo
			byInterval	轮训的间隔(时间是分钟)
			vMts		轮训的终端列表
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 MtcConfStartPoll(EmMediaType emType, 
		u16 byInterval, const vector<CMtcMt>& vMts) = 0;
	/*功能	结束轮询
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 MtcConfEndPoll() = 0;
	/*功能	暂停轮询
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 PausePoll() = 0;
	/*功能	恢复轮询
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 ResumePoll() = 0;
	/*功能	查询轮询参数
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	异步请求*/
	virtual u16 ReqPollStatus() = 0;
	virtual EmMediaType GetPollType() = 0;
	virtual u16 GetPollInterval() = 0;
	virtual const vector<CMtcMt>& GetPollMts() = 0;
	/*功能	向与会终端发送短消息
	参数	cMt	期望接收消息的终端
			strMsg	消息内容，最大1024字节，包括结尾的'\0'
			byTimes	重复次数
	返回值	成功返回0;失败返回非0错误码
	说明	旧接口,建议使用下面的新接口*/
	virtual u16 SendShortMessage(const CMtcMt& cMt, const CString &strMsg,
		EmSMSType emType = emSMSSingleLine,	u8 byRollSpeed = 3,	u8 byTimes = 1) = 0;
	/*功能	向与会终端发送短消息
	参数	msgex	CRollMsg类型的消息
	返回值	成功返回0;失败返回非0错误码
	说明	新的发送短消息接口,支持滚动消息*/
	virtual u16 SendShortMessage(const CShortMsg &cSMS) = 0;
	/*功能	邀请终端
	参数	dwIP	被邀请终端IP(主机序)
		    terMt	被邀请终端
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 Invite(u32 dwIP) = 0;
    virtual u16 Invite(const TMtAddr &tMt) = 0;
	/*功能	驱逐终端
	参数	cMt	被驱逐终端
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 MtcConfDropMt(const CMtcMt& cMt) = 0;
	/*功能	指定发言终端（或主席终端、插话）
	参数	cMt	终端
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 SpecifySpeaker(const CMtcMt& cMt) = 0;
    virtual u16 SpecifyChairman(const CMtcMt& cMt) = 0;
    virtual u16 SpecifyChime(const CMtcMt& mt) = 0;
	/*功能	取消当前发言终端的发言权
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 RevokeSpeaker() = 0;
	/*功能	取消当前主席终端的主席权
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 RevokeChairman() = 0;
	/*功能	批准（或拒绝）入会、发言、成为主席、插话
	参数	cMt	终端
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 AcceptSpeak(const CMtcMt& cMt) = 0;
	virtual u16 RefuseSpeak(const CMtcMt& cMt) = 0;
	virtual u16 AcceptChairman(const CMtcMt& cMt) = 0;
	virtual u16 RefuseChairman(const CMtcMt& cMt) = 0;
    virtual u16 AcceptChime(const CMtcMt& mt) = 0;
    virtual u16 RefuseChime(const CMtcMt& mt) = 0;
	/*功能	远端静音
	参数	cMt	被静音的远端终端
	bSilent	是否静音
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/	
	virtual u16 Silence(const CMtcMt& cMt, BOOL bSilent = TRUE) = 0;
	/*功能	远端哑音
	参数	cMt	被哑音的远端终端
	bSilent	是否哑音
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/	
	virtual u16 Dumb(const CMtcMt& cMt, BOOL bDumb = TRUE) = 0;
	/*功能	结束会议
	参数	cMt	终端
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 EndConf() = 0;
	/*功能	广播/选看终端
	参数	cMt		被操作终端
			byMode	选看模式MT_AUDIO:仅音频 MT_VIDEO:仅视频 MT_AV:音频和视频
	返回值	成功返回0;失败返回非0错误码
	说明	需主席权限*/
	virtual u16 MtcConfViewMt(const CMtcMt& cMt, EmMediaType emType = emMediaVideo) = 0;
	virtual u16 StopViewMt() = 0;
	/*功能	更新异步命令超时时间
	参数	u32		新超时时间(毫秒)
	返回值	u32		旧超时时间(毫秒)
	说明	若新超时时间为0xffffffff,则不更新超时时间,仅返回超时时间*/
	virtual u32 SetAsyncWaitTime(u32 dwTime) = 0;
	/*功能	开始/结束讨论
	参数	u32Max	最大参加讨论终端数目
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StartDiscuss(u8 byMaxNum = 10) = 0;
	virtual u16 StopDiscuss() = 0;
	/*功能	输入会议密码
	参数	strPwd	会议密码，最大长度为MT_PWD_LEN
	返回值	成功返回0;失败返回非0错误码
	说明	在接收到MTC_UI_CONFPWD时调用此接口*/
	virtual u16 InputConfPwd(const CString &strPwd) = 0;
	/*功能	DTMF语音拨号
	参数	strPwd	DTMF数字，最大长度为MT_PWD_LEN
	返回值	成功返回0;失败返回非0错误码
	说明	用户调用此接口*/
	virtual u16 InputConfDTMF(const CString &strDTMF) = 0;
	/*功能	开始/停止监控终端
	参数	cMt		被监控终端
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StartMonMt(const CMtcMt &cMt) = 0;
	virtual u16 StopMonMt(const CMtcMt &cMt) = 0;
	/*功能	开始视频复合
	参数	tVmpParam		视频复合参数
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StartVMP(const TMtVMPParam &tVmpParam) = 0;
	virtual u16 StartVMP(const TMtVMPParam& tVmpParam, vector<TMtVmpItem> &vec) = 0;
	virtual u16 StopVMP() = 0;
	virtual u16 StopVMP(const TMtVMPParam& tVmpParam, vector<TMtVmpItem> &vec) = 0;
	/*功能	更新视频复合参数
	参数	tVmpParam		视频复合参数
	返回值	成功返回0;失败返回非0错误码*/
	virtual u16 UpdateVMP(const TMtVMPParam &tVmpParam) = 0;
	virtual u16 UpdateVMP(const TMtVMPParam &tVmpParam , vector<TMtVmpItem> &vec) = 0;
	/*功能	请求视频复合参数
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	在接收到通知消息MTC_UI_VMP后调用GetVMP获取视频复合参数*/
	virtual u16 ReqVMP() = 0;
//	virtual u16 ReqVMP(const TMtVMPParam &tVmpParam , vector<TMtVmpItem> &vec);
	/*功能	获取视频复合参数
	参数	无
	返回值	视频复合参数
	说明	在MTC_UI_VMP之后调用*/
	virtual const TMtVMPParam& GetVMP()const = 0;
	virtual const vector<TMtVmpItem> &GetVMPEX()const = 0;
	virtual BOOL IsInVMP() = 0;
	/*功能	开启/停止语音激励
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StartVAC() = 0;
	virtual u16 StopVAC() = 0;
		/*功能	视频监控辅助
	说明	由于cMt组定义的接口EV_CONF_STARTMONITOR_RSP不方便使用,补充一个内嵌类
			参见消息MTC_UI_MONMT*/
    
    //加密同步结构  
    typedef struct tagEncryptMT
    {
	    s32			  m_nSynchFlag;			         //shall be the Dynamic PayloadType for H.323
	    u8			  m_abyH235Key[64]; //H.235 encoded value(1-65535)
        s32           m_nH235KeyLen;
        
        tagEncryptMT()
	    {
		    Reset();
	    }

        void Reset()
	    {
		    m_nSynchFlag  = 0;
		    m_nH235KeyLen = 0;
	    }

        void host2net(BOOL bhton)
        {
            if (bhton)
            {
                m_nSynchFlag  = htonl(m_nSynchFlag);
                m_nH235KeyLen = htonl(m_nH235KeyLen);
            }
            else
            {
                m_nSynchFlag  = ntohl(m_nSynchFlag);
                m_nH235KeyLen = ntohl(m_nH235KeyLen);
            }
        }

        //获取H235Key的长度
	    s32 GetH235KeyLen() 
	    {
		    return m_nH235KeyLen; 
	    }
        //获取H235Key
	    u8* GetH235Key()
	    {
		    return m_abyH235Key;
	    }
    }TEncrypt;

    
	class CAuxMonParam
	{
	public:
		u8	m_byMcuId;			// 多点控制单元标识
		u8	m_byMtId;			// 终端标识
		u32	m_dwIP;			    // IP地址, 主机序
		u16	m_wPortAudio;		// 音频端口号, 主机序
		u16	m_wPortVideo;		// 视频端口号, 主机序
		u8  m_byRealAudioPT;    // 音频真实载荷值
        u8  m_byRealVideoPT;    // 视频真实载荷值
        u8  m_byActiveAudioPT;  // 音频动态载荷值
        u8  m_byActiveVideoPT;  // 视频动态载荷值
        u8  m_byAudioEncType;   // 音频加密类型
        u8  m_byVideoEncType;   // 视频加密类型
        TEncryptKey m_tAudioEnc;// 音频秘钥
        TEncryptKey m_tVideoEnc;// 视频秘钥
	};
	/*功能	延长会议请求
	参数	wMin	延长多少分钟
	返回值	成功返回0;失败返回非0错误码
	说明	如果延长被认可,收到MTC_UI_CMD_SUCCESS消息,消息中wParam为EV_CONF_DELAY_REQ
			如果延长没有被认可,收到MTC_UI_CMD_FAILED消息,消息中wParam为EV_CONF_DELAY_REQ*/
	virtual u16 Delay(u16 wMin) = 0;
	/*功能	请求其它终端的状态
	参数	cMt	被查询状态的终端
	返回值	成功返回0;失败返回非0错误码
	说明	成功后收到MTC_UI_CONF_MTSTATUS消息	
			超没收到业务终端的状态反馈,错误ID为EV_CONF_MTSTATUS_REQ*/
	virtual u16 ReqStatus(const CMtcMt& cMt) = 0;
    /*函数名： StartForceBroadcast
    功    能： 开始/停止强制播放发言人的码流
    参    数： 
    返 回 值： virtual u16 成功返回0;失败返回非0错误码
    说    明： */
	virtual u16 StartForceBroadcast() = 0;
	virtual u16 StopForceBroadcast() = 0;
	
    /*函数名： ConfIsEncrypte
    功    能： 会议是否加密
    参    数： 
    返 回 值： virtual BOOL32 
    说    明： */
	virtual BOOL32 ConfIsEncrypte() = 0;

    // mc 相关操作
    // 点对点会议扩展
    virtual u16 P2PConfExtend(const TDialParam &tDialParam) = 0;
    //mc时界面替换画面复合终端
    virtual u16 McVMPReplaceMt(u8 byIndex, const TMtId &tMtId) = 0;
    // mc远遥终端
    virtual u16 McFeccTerm(const TMtId& tMtId) = 0;
    // 配置mc工作模式命令
    virtual u16 McModeCfg(BOOL bEnable, EmMCMode emMcMode) = 0;
    // 设置画面合成自动增加/或者固定
    virtual u16 McVMPCfg(BOOL bAuto) = 0;
    // 设置vmp的风格
    virtual u16 McSetVMPStyle(EmInnerVMPStyle emVMPStyle, const TMtId *tMtId) = 0;
	// MC终端选看
	virtual u16 MCConfViewMt(BOOL byIsView, const CMtcMt& cMt) = 0;
	virtual BOOL IsInSel() = 0;
    // mc终端轮询广播
    virtual u16 McPollStart(EmMediaType emType, u16 wInterval, const vector<CMtcMt>& vMts) = 0;
    virtual u16 McPollStop() = 0;


	
	//请求 主席选看终端的画面合成 
	virtual u16 ConfmtSelectVmpReq(BOOL view) = 0;
	virtual BOOL IsSelectedVmp() = 0;
	// mc主席轮询
    virtual u16 McChairmanPollStart(EmMediaType emType, u16 wInterval, const vector<CMtcMt>& vMts) = 0;
    virtual u16 McChairmanPollStop()  = 0;
	virtual EmAction GetMCChairmanPollState() = 0;
	virtual EmAction GetMCPollState() = 0;
    // mc接收呼叫
    virtual u16 McAccept(const TMtId &tMtId, BOOL32 bAccept) = 0;
    // MC是否激活
    virtual BOOL32 IsMcActive() const = 0;
    // 获取当前MC模式
    virtual EmMCMode GetMcMode() const = 0;
    // 判断MC在当前会议中是否可用
    virtual BOOL32 IsMcEnableInCurConf() const = 0;
    // 获取MC轮询时的信息
    virtual const TMtPollInfo& GetMcPollInfo() const = 0;
    // 获取MC画面合成风格
    virtual EmInnerVMPStyle GetMcVMPStyle() const = 0;
    // MC是否自动画面合成
    virtual BOOL32 IsMcAutoVMP() const = 0;
    // 获取MC画面合成成员
    virtual const TMtId* GetMcVMPMember() const = 0;
    // 获取MC哑音终端成员
    virtual const TerDumbStatus* GetMcDumbTer() const = 0;
    // 获取远遥终端
    virtual const TMtId& GetMcFeccTerm() const = 0;


	//设置所有轮询方案
	virtual u16 UpdateAllPollSchemes(vector<TMtcPollInfo> &vec) = 0;
	//获得所有轮询方案
	virtual const vector<TMtcPollInfo>& GetAllPollSchemes()const = 0;
	//设置当前轮询方案
	virtual u16 UpdateOnePollScheme(u8 Index , s8* achName , EmMediaType emType, u16 wInterval, const vector<CMtcMt>& vMts) = 0;
	//获得当前轮询方案
	virtual const TMtcPollInfo& GetOnePollScheme() = 0;


	//定制混音
	virtual BOOL IsInSelMtsMixAudio() = 0;
	virtual u16 StartSelMtsMixAudio(TMtMixParam &tMixParam) = 0;
	virtual u16 StopSelMtsMixAudio() = 0;
	virtual u16 AddSelMtsMixAudio(TMtMixParam &tMixParam) = 0;
	virtual u16 RemoveSelMtsMixAudio(TMtMixParam &tMixParam) = 0;
	virtual const TMtMixParam& GetMtsInSelMixAudio() const = 0;
	 
	virtual EmMixMode GetMixMode() = 0;
}; // IMtcConf

#endif