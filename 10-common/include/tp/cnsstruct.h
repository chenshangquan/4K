#ifndef _h_cnstruct_h__
#define _h_cnstruct_h__
#include "tpsys.h"
#include <time.h>

#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "osp.h"
#include "cnconst.h"
#include "cnstype.h"

typedef struct tagTTPMCUSelViewReq
{
	TTPTerLabel tTerLabel;
	EmTpCtrlMode emTpCtrlMode;
	u8           byPos;
	
	tagTTPMCUSelViewReq()
	{
		memset(this, 0, sizeof(struct tagTTPMCUSelViewReq));
	}
}TTPMCUSelViewReq;

typedef struct tagTTPShowLogo
{
	s8        achLogoName[TP_MAX_ALIAS_LEN + 1];
	BOOL      bIsShowLogo;
    EmTpColor emColor;
    EmTpSize  emSize;
	EmTpLogoStyle emStyle;
	BOOL      bInit;//标识T300第一次启动
}TTPShowLogo;

typedef struct tagTTPLogo
{
	u8          byIndex;
    TTPShowLogo tLogoInfo;
	tagTTPLogo()
	{
		Clear();
	}
	void Clear()
	{
		byIndex = 0;
		memset(&tLogoInfo, 0, sizeof(TTPShowLogo));
	}
}TTPLogo;

typedef struct tagTTPLogoInfo
{
    TTPShowLogo tFirsLogoInfo;
	TTPShowLogo tSecondLogoInfo;
	TTPShowLogo tThirdLogoInfo;
}TTPLogoInfo;

typedef struct tagTTPShowBanner
{
	s8        achBannerName[TP_MAX_ALIAS_LEN + 1];
    BOOL      bIsShowBanner;
	EmTpColor emColor;
    EmTpSize  emSize;
	EmTpStyle emStyle;
	emTpTransparency emTransparency;
}TTPShowBanner;

typedef struct tagTTPBanner
{
	u8            byIndex;
    TTPShowBanner tBannerInfo;
	tagTTPBanner()
	{
		Clear();
	}
	void Clear()
	{
		byIndex = 0;
		memset(&tBannerInfo, 0, sizeof(TTPShowBanner));
	}
}TTPBanner;

typedef struct tagTTPBannerInfo
{
    TTPShowBanner tFirstBannerInfo;
	TTPShowBanner tSeconfBannerInfo;
	TTPShowBanner tThirdBannerInfo;
}TTPBannerInfo;

//add by wangqichang
//视频源名称
typedef struct tagTTPVideoSourceName
{
	EmTPMtVideoPort m_emPortType;
	s8 m_achSourceName[TP_MAX_ALIAS_LEN+1];
	public:
		tagTTPVideoSourceName()
		{
			memset(this, 0 , sizeof( tagTTPVideoSourceName ));
		}
}TTPVideoSourceName;

//维护工具上主视频设置
typedef struct tagTTPVideoInfoTool
{
	EmTPMtVideoPort        m_aemBigVideoSource[emEndMPCodec - 1];//大图像视频源
	EmTPMtVideoPort        m_aemMinVideoSource[emEndMPCodec - 1];//小图像视频源
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid + 1];//视频源名称(6个+ 全景摄像机1)
	EmVidEncResizeMode     m_emVidEncResizeMode;//主视频图像比例调整策略
	BOOL                   m_bIsH323PipMerge;//H323会议画面合成
	EmVidMergeStyle        m_emVideoMergeStyle;//画面合成风格
	public:
		tagTTPVideoInfoTool(){memset(this,0,sizeof(struct tagTTPVideoInfoTool));}
}TTPVideoInfoTool;

//中控电视机配置信息
typedef struct tagTCentreTVCfg
{
	EmSerialType           emSerialType;  //电视机连接串口类型
	EmTvPowerMode          emTvPowerMode; //电视机开关状态 
	EmTVAudVisMode         emAudVisMode; //电视机视听模式
	EmTVDisplayMode        emDisMode;    //电视机显示模式
	EmTVInputSelect        emInpSelect;  //电视输入选择
	EmTvSrcPowerMode	   emTvSrcPowerMode;//电视机断电前开关状态
	EmTVModle			   emTvModle;  //电视机型号   add for B4 ---2015/2/4
    
	public:
		tagTCentreTVCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreTVCfg) );
		}
		
}TCentreTVCfg;

//中控窗帘信息
typedef struct tagTCentreCurInfo
{
	BOOL			bCurOpen;
	u8				byCurNum;
	TCentreCurName  tCenCurName[MAX_CURTAIN_NUM];
	public:
		tagTCentreCurInfo()
		{
			memset( this, 0, sizeof(struct tagTCentreCurInfo) );
		}

}TCentreCurInfo;

//全景摄像机预置位名
typedef struct tagTPanCamName
{
    s8  achPanCamName[MAX_PANCAMNAME_LEN];
	public:
		tagTPanCamName()
		{
			memset( this, 0, sizeof(struct tagTPanCamName) );
		}
		
}TPanCamName;
//每个摄像机一组预置位最大为16个
typedef struct tagTPanCamGroupName
{
    TPanCamName  tPanCamName[MAX_PRESET_NUM];
	public:
		tagTPanCamGroupName()
		{
			memset( this, 0, sizeof(struct tagTPanCamGroupName) );
		}
		
}TPanCamGroupName;

//全景摄像机信息
typedef struct tagTPanCamInfo
{
	BOOL			  bPanCamOpen;				//全景摄像机状态
	u8				  byPanCamNum;              //全景摄像机总数
	TPanCamGroupName  tPCamGroupName[MAX_PAN_NUM];       
	EmQCamProType     emQCamProType;            //全景摄像机类型
	public:
		tagTPanCamInfo()
		{
			memset( this, 0, sizeof(struct tagTPanCamInfo) );
		}
		
}TPanCamInfo;

//end add

//双流屏
typedef struct tagTDualScreenInfo
{
	BOOL			  bDualScreenOpen;	//双流屏状态
	public:
		tagTDualScreenInfo()
		{
			memset( this, 0, sizeof(struct tagTDualScreenInfo) );
		}
		
}TDualScreenInfo;


//双流适配设置
typedef struct tagTTPVAdapterInfo
{
	BOOL    bStartAdapter; //是否开启双流适配
	u32     dwProfile;    //Hp or BP
	u32     dwWidth; 	 //适配分辨率宽度
	u32     dwHeight;	 //适配分辨率高度
	u32     dwFramerate; //适配帧率
	u16     wBitRate;  //适配码率
	BOOL    bOnlySetNewApPara; //只调整适配参数
	public:
		tagTTPVAdapterInfo(){memset(this,0,sizeof(struct tagTTPVAdapterInfo));}
}TTPVAdapterInfo;

typedef struct tagTTPAutoTestLoopInfo //用于生产测试
{
	EmTpMediaType          emTpMediaType;
	EmTpVEncCodecType      emTpVEncCodecType; //设置视频编码器才需要设置
	EmTpCodecComponent     emCope;
	BOOL                   bLoop;//自环
	u8                     byPos;      
	public:
		tagTTPAutoTestLoopInfo(){memset(this,0,sizeof(struct tagTTPAutoTestLoopInfo));}
}TTPAutoTestLoopInfo;

typedef struct tagTTPInterFaceTestInfo //用于接口测试
{
	EmTpCodecComponent     emCope;
	BOOL                   bLoop;//自环
	u8                     byPos;      
	public:
		tagTTPInterFaceTestInfo(){memset(this,0,sizeof(struct tagTTPInterFaceTestInfo));}
}TTPInterFaceTestInfo;

typedef struct tagTTPCapMap 
{
	TTPMediaStream cMeadiaStream;
	s32 nChannelId;
	EmTpChannelHandle emChanHandle;
public:
    tagTTPCapMap(){ memset ( this, 0, sizeof( struct tagTTPCapMap) );}
	
}TTPCapMap;

typedef struct tagTTPCapPack 
{
	u16		  wTotalPackNum;
	u16		  wCurPackIndex;
	u16		  wValidCapNum;
	TTPCapMap atTPCapMap[4];
public:
    tagTTPCapPack(){ memset ( this, 0, sizeof( struct tagTTPCapPack) );}
	
}TTPCapPack;

typedef struct tagTTPVideoLoopTestInfo
{
	EmTpVideoLoopTest   emVideoLoopTest;
	BOOL                   bLoop;//自环
	u8                     byPos;      
	public:
		tagTTPVideoLoopTestInfo(){memset(this,0,sizeof(struct tagTTPVideoLoopTestInfo));}
}TTPVideoLoopTestInfo;

typedef struct tagTTpConfEpInfo
{
	u16 m_wConfID; 
	TTpCallAddr m_tCallAddr;
	
	u16 m_Index;
	BOOL32 m_bPermit;
	
	tagTTpConfEpInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tCallAddr.Clear();
		m_Index = TP_INVALID_INDEX;
		m_bPermit = FALSE;
	}
	
}TTpConfEpInfo;

// begin add for Hdu
typedef struct tagTTpHduUnitPlayInfo
{
	u16		m_wConfID;		//会议ID
	u16		m_wDstID;
	s8      m_achAlias[TP_MAX_EPID_LEN+1];
	u16		m_wScreenNum;	//屏号
	EmViewEpType		m_emType;
	EmCnsHduRunStatus	m_emStatus;

	tagTTpHduUnitPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_emType = EmEpType_Invalid;
		m_emStatus = emCnsHdu_Idle;
	}

	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_EPID_LEN);
		m_achAlias[TP_MAX_EPID_LEN] = '\0';
	}

}TTpHduUnitPlayInfo;


typedef struct tagTTpHduPlanUnit
{	
	u8  	m_byReged;	//在线状态
	u8      m_byValid;
	u16		m_wIndex;	//索引
	s8		m_achAlias[TP_MAX_EPID_LEN+1];	//HDU 配置名
	u8   	m_byVmp;
	u8		m_byVol;
	u8  	m_byMute;
	u8		m_byChanIndex;	//通道号 0 和 1

	TTpHduUnitPlayInfo	m_atPlayInfo[TP_MAX_VMP_SUBCHAN];

	tagTTpHduPlanUnit()
	{
		Clear();
	}

	void Clear()
	{
		m_byReged = 0;
		m_byValid = 0;
		m_wIndex = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_byVmp = 0;
		m_byVol = 0;
		m_byMute = 0;
		m_byChanIndex = 0;
		for (u16 wIndex = 0 ; wIndex < TP_MAX_VMP_SUBCHAN; wIndex++)
		{
			m_atPlayInfo[wIndex].Clear();
		}
	}
}TTpHduPlanUnit;

typedef struct tagTTpHduPlanPackData
{
	u8		m_byRow;
	u8		m_byCol;
	u16		m_wNum; // 总数

	u8      m_byFirst; // 是否是第一包
	u8		m_CurentNum;  // 当前包下面数组的有效数量
	TTpHduPlanUnit m_atUnits[TP_STYLE_DATA_PACK_NUM];  

	tagTTpHduPlanPackData()
	{
		Clear();
	}

	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;
		m_wNum = 0;
		m_byFirst = 0;
		m_CurentNum = 0;
		for (u16 wIndex = 0; wIndex < TP_STYLE_DATA_PACK_NUM; wIndex++)
		{
			m_atUnits[wIndex].Clear();
		}
	}

}TTpHduPlanPackData;

typedef struct tagTTpHduPlayReq
{
	EmViewEpType	m_emType;
	u16		m_wConfID;
	u16		m_wDstID;   // 如果是会场，就是会场id，如果是合成器，就是外设id
	s8      m_achAlias[TP_MAX_ALIAS_LEN + 1];  // 会场名称或者外设名称
	u16		m_wScreenNum;  // 

	// 通道信息
	u16		m_wIndex;		//索引
	u8		m_bySubIndex;	//子索引
	BOOL32	m_bVmp; //是否是合成通道

	tagTTpHduPlayReq()
	{
		m_emType = EmEpType_Invalid;
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = TP_MAX_VMP_SUBCHAN;
		m_bVmp = FALSE;
	}

	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	tagTTpHduPlayReq& operator = (const tagTTpHduPlayReq& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}

}TTpHduPlayReq;

typedef struct tagTTpHduBaseInfo
{
	u16		m_wIndex;
	u8		m_bySubIndex;

	tagTTpHduBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_bySubIndex = 0;
	}

}TTpHduBaseInfo;

typedef struct tagTTpHduSetVolInfo
{
	TTpHduBaseInfo	m_tInfo;
	u8		m_byVol;
	BOOL32	m_bMute;

	tagTTpHduSetVolInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tInfo.Clear();
		m_byVol = 0;
		m_bMute = FALSE;
	}
}TTpHduSetVolInfo;

typedef struct tagTTpHduChanModeSetInfo
{
	u16 m_wIndex;  // 通道索引
	u8  m_byMode;  // 0 为一画面，1为4画面

	tagTTpHduChanModeSetInfo()
	{
		Clear();
	}

	BOOL32 IsValidMode()
	{
		return (0 == m_byMode || 1 == m_byMode);
	}

	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_byMode = 0;
	}

}TTpHduChanModeSetInfo;


// end add for hdu


//点名列表
typedef struct tagTTpRollCallList
{
	u16	m_wNum;
	u16	m_awList[TP_MAX_ROLLCALL_NUM];	      //点名列表,所有被点名者
	u16 m_wRollCaller;                       //点名者
	u16 m_wCallTarget;                       //当前被点名者

	tagTTpRollCallList()
	{
		Clear();
	}

	tagTTpRollCallList& operator=(const tagTTpRollCallList& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		for (u16 wIndex = 0; wIndex < tInfo.m_wNum; ++wIndex)
		{
			m_awList[wIndex] = tInfo.m_awList[wIndex];
		}
		m_wNum = tInfo.m_wNum;
        m_wRollCaller = tInfo.m_wRollCaller;
		m_wCallTarget = tInfo.m_wCallTarget;

		return *this;
	}

	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
		m_wNum = 0;
		m_wRollCaller = TP_INVALID_INDEX;
        m_wCallTarget = TP_INVALID_INDEX;
	}


	BOOL32 SetRollCaller(u16 wEpID)
	{
		if (!(TP_VALID_HANDLE(wEpID)))
		{
            return FALSE;
		}

		// 点名者与被点名者必须不同
		for (u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            if (m_awList[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		
        m_wRollCaller = wEpID;
		
        return TRUE;
	}
	
	u16 GetRollCaller()
	{
		return m_wRollCaller;
	}
	

	BOOL32 SetRollCallTarget(u16 wEpID)
	{
		if (!(TP_VALID_HANDLE(wEpID)))
		{
            return FALSE;
		}
		
        m_wCallTarget = wEpID;
		
        return TRUE;
	}

	u16 GetRollCallTarget()
	{
		return m_wCallTarget;
	}

	BOOL32 IsRollCallTargetInList(u16 wEpID)
	{
		if (!TP_VALID_HANDLE(wEpID))
		{
            return FALSE;
		}
		
		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return TRUE;
			}
		}
		
		return FALSE;
	}
	
	u16 GetTargetIndex(u16 wEpID)
	{
		if (!TP_VALID_HANDLE(wEpID))
		{
            return TP_INVALID_INDEX;
		}
		
		
        for(u16 wIndex = 0; wIndex < m_wNum; wIndex++)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return wIndex;
			}
		}
		
        return TP_INVALID_INDEX;
	}

	u16 AddRollCallTarget(u16 wEpID)
	{		
		u16 wIndex = 0;

		if (!TP_VALID_HANDLE(wEpID))
		{
            return TP_INVALID_INDEX;
		}

		// 不能有重复的被点名者
		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return TP_INVALID_INDEX;
			}
		}

		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_awList[wIndex] = wEpID;
				m_wNum++;
				return wIndex;
			}
		}

		return TP_INVALID_INDEX;
	}


	void DelRollCallTarget(u16 wEpId)
	{
		u16 wIndex = 0;
		u16 wDelIndex = TP_INVALID_INDEX;
		for (wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpId)
			{
				m_awList[wIndex] = TP_INVALID_INDEX;
				wDelIndex = wIndex;
				m_wNum--;
				break;
			}
		}

		if (TP_VALID_HANDLE(wDelIndex))
		{
			for (wIndex = wDelIndex+1; wIndex < TP_MAX_ROLLCALL_NUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awList[wIndex]))
				{
					m_awList[wIndex-1] = m_awList[wIndex];
					m_awList[wIndex] = TP_INVALID_INDEX;
					continue;
				}
				break;
			}
		}
		return;
	}

	u16 GetRollCallTargetNum() const
	{
		//被点名成员数，不包括点名者
		return m_wNum;
	}

}TTpRollCallList, *PTTpRollCallList;

typedef struct tagTTpConfRollCallInfo
{
	u16					m_wConfID;
	BOOL32				m_bStart;
	TTpRollCallList		m_atRollCallMemList;
	EmRollCallRspRet	m_emRet;  // 开启点名的结果
	
	tagTTpConfRollCallInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart  = FALSE;
		
		m_atRollCallMemList.Clear();
		m_emRet = em_RollCallOprRsp_End;
	}
	
}TTpConfRollCallInfo;


typedef struct tagTTpRollCallNextEpInfo
{
	u16 m_wConfID;
    u16 m_wRollCaller;
	u16 m_wCallTarget;
    EmRollCallRspRet m_emRet;
	
	tagTTpRollCallNextEpInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wRollCaller = TP_INVALID_INDEX;
		m_wCallTarget = TP_INVALID_INDEX;
		m_emRet = em_RollCallOprRsp_End;
	}
	
}TTpRollCallNextEpInfo;

// for umsaudmix
typedef struct tagTTpAudMixList
{
	u16						m_wNum;
	u16						m_awMixEp[TP_APU2_MAX_CHAN_NUM];
	
	tagTTpAudMixList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_awMixEp[wIndex] = TP_INVALID_INDEX;
		}
	}
	
	BOOL32 AddID(u16 wEpID)
	{		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awMixEp[wIndex]))
			{
				m_awMixEp[wIndex] = wEpID;
				m_wNum++;
				return TRUE;
			}
		}
		return FALSE;
	}
	
	void DelId(u16 wEpId)
	{
		u16 wIndex = 0;
		u16 wDelIndex = TP_INVALID_INDEX;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpId)
			{
				m_awMixEp[wIndex] = TP_INVALID_INDEX;
				wDelIndex = wIndex;
				m_wNum--;
				break;
			}
		}
		
		if (TP_VALID_HANDLE(wDelIndex))
		{
			for (wIndex = wDelIndex+1; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awMixEp[wIndex]))
				{
					m_awMixEp[wIndex-1] = m_awMixEp[wIndex];
					m_awMixEp[wIndex] = TP_INVALID_INDEX;
					continue;
				}
				break;
			}
		}
		return;
	}

	BOOL32 IsInList(u16 wEpId) const
	{
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; ++wIndex)
		{
			if (m_awMixEp[wIndex] == wEpId)
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	tagTTpAudMixList& operator = (const tagTTpAudMixList& tInfo)
	{
		if (this != &tInfo)
		{
			m_wNum = tInfo.m_wNum;
			for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
				m_awMixEp[wIndex] = tInfo.m_awMixEp[wIndex];
			}
		}
		return *this;
	}
	
	
}TTpAudMixList;

typedef struct tagTTpAudMixInfo
{
	u16					m_wConfId;
	TTpAudMixList		m_tMixList;
	EmAudMixMode		m_emMode;
	
	tagTTpAudMixInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tMixList.Clear();
		m_emMode = em_umsaudmixmode_idle;
	}
	
	tagTTpAudMixInfo& operator = (const tagTTpAudMixInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_wConfId = tInfo.m_wConfId;
			m_tMixList = tInfo.m_tMixList;
			m_emMode = tInfo.m_emMode;
		}
		return *this;
	}
	
}TTpAudMixInfo;

typedef struct tagTTpAudMixModeCmdRes
{
	u16					m_wConfId;
	EmAudMixMode		m_emCmdMode;
	EmAudMixRes		    m_emRes;
	
	tagTTpAudMixModeCmdRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_emCmdMode = em_umsaudmixmode_idle;
		m_emRes = em_umsaudmixres_unkown;
	}
	
}TTpAudMixModeCmdRes;

typedef struct tagTTpAudMixListCmd
{
	u16					m_wConfId;
	TTpAudMixList		m_tList;
	EmAudMixListOpr  	m_emOpr;

	tagTTpAudMixListCmd()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		m_emOpr = em_umsaudmixlistopr_unkown;
	}
	
}TTpAudMixListCmd;

typedef struct tagTTpAudMixListCmdRes
{
	u16					m_wConfId;
	TTpAudMixList		m_tList;
	EmAudMixRes		    m_aemRes[TP_APU2_MAX_CHAN_NUM];
	
	tagTTpAudMixListCmdRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfId = TP_INVALID_INDEX;
		m_tList.Clear();
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_aemRes[wIndex] = em_umsaudmixres_unkown;
		}
	}
	
}TTpAudMixListCmdRes;

typedef struct tagTTpUpdataRollCallList
{
	u16					m_wConfID;            //会议ID
	BOOL32				m_bAdd;               //添加删除
	TTpRollCallList		m_atRollCallMemList;  //添加删除点名列表
	
	tagTTpUpdataRollCallList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;
		
		m_atRollCallMemList.Clear();
	}
	
}TTpUpdataRollCallList;



typedef struct tagTTpUpdataRollCallListRes
{
	u16					m_wConfID;            //会议ID
	BOOL32				m_bAdd;               //添加删除
	TTpRollCallList		m_atRollCallMemList;  //添加删除点名列表, update 时不处理列表中的m_wRollCaller，m_wCallTarget 
	EmRollCallRspRet    m_emRet[TP_MAX_ROLLCALL_NUM];   //每一个 新增、删除 EP 的结果
	
	tagTTpUpdataRollCallListRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bAdd    = FALSE;
		
		m_atRollCallMemList.Clear();
		
		for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            m_emRet[wIndex] = em_RollCallOprRsp_End;
		}
	}
	
}TTpUpdataRollCallListRes;



typedef struct tagTTpRollCallPresentStateEpInfo
{
    u16 m_wEpID;                  //会议ID
    u16 m_wEpState;               //状态  EmRollCallPresentState 强转

	tagTTpRollCallPresentStateEpInfo()
	{
        Clear();
	}

	void Clear()
	{
        m_wEpID = TP_INVALID_INDEX;
        m_wEpState = 0;
	}

	tagTTpRollCallPresentStateEpInfo& operator = (const tagTTpRollCallPresentStateEpInfo& tInfo)
	{
		if (this != &tInfo)
		{
			m_wEpID = tInfo.m_wEpID;
			m_wEpState = tInfo.m_wEpState;
		}
		
		return *this;
	}

}TTpRollCallPresentStateEpInfo;

typedef struct tagTTpRollCallPresentStateMsg
{
    u16 m_wConfID;

    u16 m_wValidNum;              //  状态数组中有效数
    TTpRollCallPresentStateEpInfo  m_atEpState[TP_MAX_ROLLCALL_NUM];  //被点名者状态

	tagTTpRollCallPresentStateMsg()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID      = TP_INVALID_INDEX;
		m_wValidNum    = 0;

		for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
		{
            m_atEpState[wIndex].Clear();
		}
	}

	tagTTpRollCallPresentStateMsg& operator = (const tagTTpRollCallPresentStateMsg& tInfo)
	{
		if (this != &tInfo)
		{
			m_wConfID = tInfo.m_wConfID;
			m_wValidNum = tInfo.m_wValidNum;

			for (u16 wIndex = 0; wIndex < m_wValidNum; wIndex++)
			{
                 m_atEpState[wIndex] = tInfo.m_atEpState[wIndex];
			}

		}

		return *this;
	}
	
}TTpRollCallPresentStateMsg;

#endif //_h_cnstruct_h__