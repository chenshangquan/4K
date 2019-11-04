/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        h323confstdstruct.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Conference messages struct for H323 protocol 
*   @details     
*/
#ifndef _H323CONFSTDSTRUCT_H
#define _H323CONFSTDSTRUCT_H

#include "kdv323common.h"


/**会议信息*/
typedef struct tagConfInfo
{
	u8          m_abyConfId[LEN_GUID];
	TAliasAddr  m_tConfAlias;
	
	tagConfInfo()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
	}

	
	void Clear()
	{
		memset( m_abyConfId, 0, sizeof(m_abyConfId) );
		m_tConfAlias.Clear();
	}

	/**设置会议ID*/
	void SetConfId( u8 *pbyConfId, u32 dwLen );

	/**获取会议ID*/
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	
	/**设置TAliasAddr*/
	void SetAliasAddr( TAliasAddr &tAliasAddr)
	{
		m_tConfAlias = tAliasAddr;
	}
	/**获取TAliasAddr*/
	TAliasAddr& GetAliasAddr()
	{
		return m_tConfAlias;
	}
}TCONFINFO,*PTCONFINFO;

/**会议列表*/
typedef struct tagConferences
{
	u8		   m_byNum;
	TCONFINFO  m_atConfInfo[MAX_CONF_NUM];
	
	tagConferences():m_byNum(0){}
	
	void Clear()
	{
		m_byNum = 0;
		memset( m_atConfInfo, 0, sizeof(m_atConfInfo) );
	}
	
	/**设置会议数目*/
	void SetConfNum( u8 num)
	{
		m_byNum = num;
	}
	/**获取会议数目*/
	u8 GetConfNum()
	{
		return m_byNum;
	}

	/**设置会议信息*/
	void SetConfInfo( TCONFINFO &tConfInfo, u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return ;		
		m_atConfInfo[byConfNo] = tConfInfo;
	}
	/**获取会议信息*/
	PTCONFINFO GetConfInfo( u8 byConfNo )
	{
		if ( byConfNo >= MAX_CONF_NUM ) 
			return  NULL;
		return &(m_atConfInfo[byConfNo]);
	}
}TCONFERENCES,*PTCONFERENCES;

/**////////////////////////////  消息中带的结构体  //////////////////////////*/


/**通讯模式参数*/
typedef struct tagCommunicationModeCommandInfo
{
	u8				m_bySessionID;
	u8				m_byAssociatedSessionID;
	TTERLABEL		m_tTerLabel;							/**<如果为<255,255>表示所有终端*/
	u8				m_byDataType;							/**<type_audio/type_video/type_data*/
	u16				m_wPayloadType;							/**<媒体体类型*/
	PFC_IPADDR		m_tRtp;									/**<rtp地址	*/	
	PFC_IPADDR		m_tRtcp;								/**<rtcp地址*/
	TTERLABEL		m_tDestination;							/**<目的终端,<0,0>表示无效*/
	u8				m_bySessionDescriptLen;
	s8				m_achSessionDescript[MAXSessionDescript+1];
					
	tagCommunicationModeCommandInfo()
	{
		Clear();
	}
	
	void Clear();

    /**设置SessionID*/
	void SetSessionID( u8 bySessionID)
	{
		m_bySessionID = bySessionID;
	}
    /**得到SessionID*/
	u8 GetSessionID()
	{
		return m_bySessionID;
	}

    /**设置AssociatedSessionID*/
	void SetAssociatedSessionID( u8 byAssociatedSessionID )
	{
		m_byAssociatedSessionID = byAssociatedSessionID;
	}

    /**得到AssociatedSessionID*/
	u8 GetAssociatedSessionID()
	{
		return m_byAssociatedSessionID;
	}

    /**设置TTERLABEL*/
	void SetTerLabel( TTERLABEL &tTerLabel)
	{
		m_tTerLabel = tTerLabel;
	}

    /**得到TTERLABEL*/
	TTERLABEL& GetTerLabel()
	{
		return m_tTerLabel;
	}

    /**设置数据类型*/
	void SetDataType( u8 byDataType)
	{
		m_byDataType = byDataType;
	}

    /**得到数据类型*/
	u8 GetDataType()
	{
		return m_byDataType;
	}

    /**设置媒体类型*/
	void SetPayloadType( u16 wPayloadType)
	{
		m_wPayloadType = wPayloadType;
	}

    /**得到媒体类型*/
	u16 GetPayloadType()
	{
		return m_wPayloadType;
	}

    /**设置RTP地址*/
	void SetRTPAddr( PFC_IPADDR &tRtp )
	{
		m_tRtp = tRtp;
	}

    /**得到RTP地址*/
	PFC_IPADDR& GetRTPAddr()
	{
		return m_tRtp;
	}

    /**设置RTCP地址*/
	void SetRTCPAddr( PFC_IPADDR &tRtcp )
	{
		m_tRtcp = tRtcp;
	}

    /**得到RTCP地址*/
	PFC_IPADDR& GetRTCPAddr()
	{
		return m_tRtcp;
	}

    /**设置目的端TTERLABEL*/
	void SetDestTerLabel( TTERLABEL &tTerLabel)
	{
		m_tDestination = tTerLabel;
	}

    /**得到目的端TTERLABEL*/
	TTERLABEL& GetDestTerLabel()
	{
		return m_tDestination;
	} 
	
    /**设置SessionDescript*/
	void SetSessionDescript( s8 *pSessionDescript, u8 byLen )
	{
		m_bySessionDescriptLen = Minimum( byLen, MAXSessionDescript );
		strncpy( m_achSessionDescript, pSessionDescript, m_bySessionDescriptLen );
		m_achSessionDescript[m_bySessionDescriptLen] = '\0';
	}

    /**得到SessionDescript*/
	s8* GetSessionDescript()
	{
		return m_achSessionDescript;
	}

    /**得到SessionDescript长度*/
	u16 GetSessionDescriptLen()
	{
		return m_bySessionDescriptLen;
	}
}TCOMMODEINFO,*PTCOMMODEINFO;

/**Pass Rsp Struct*/
typedef struct PROTO_API tagPassRsp
{
	TTERLABEL m_tTer;
	s32       m_nPassLen;
	u8        m_abyPassword[LEN_H243PWD+1]; 

	tagPassRsp()
	{
		Clear();
	}

	void Clear()
	{
		memset( &m_tTer, 0, sizeof(m_tTer) );
		m_nPassLen = 0;
		memset( m_abyPassword, 0, sizeof(m_abyPassword) );
	}

    void host2net(BOOL32 bhton);

	/**设置TTERLABEL*/
	void SetTerLabel( TTERLABEL &tTerLabel )
	{
		m_tTer = tTerLabel;
	}

	/**获取TTERLABEL*/
	TTERLABEL& GetTerlabel()
	{
		return m_tTer;
	}
	
	/**设置Password*/
	void SetPassword( u8 *pPassword, u16 wLen );

	/**获取Password*/
	u16 GetPassword( u8 *pbyPassword, u16 &wLen );

}TPassRsp;

/**终端信息参数*/
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;
	s8			m_achTerID[LEN_TERID + 1];

	tagTerminalInformation()
	{
		Clear();
	}

	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	/**设置终端编号*/
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo < 193 && byTerNo <193)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}

	/**获得终端编号*/
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}

	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}

	/**获得Mcu号*/
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}

	/**获得终端号*/
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}

	/**设置终端名字*/
	BOOL32 SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}

	/**获得终端名字*/
	s8* GetName()
	{
		return m_achTerID;
	}

	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
									  tTerInfo.m_tTerLabel.GetTerNo() );

		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}

	bool operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return false;
		}
		return true;
	}

	bool operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			 m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			 strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return true;
		}
		return false;
	}
}TTERINFO,*PTTERINFO;

/**H239 Information*/
typedef struct PROTO_API tagH239Info
{
    emH239InfoType  m_emH239InfoType;
    TTERLABEL       m_tTerLabel;
    s32             m_nChannelId;
    
    /**
	*  在emH239FlowControlReleaseResponse
    *  和emH239PresentationTokenResponse中使用
    *  TRUE表示同意，FALSE表示拒绝*/
    BOOL32            m_bIsResponseAck;   
    
    /**通道码率，单位：100bit/s，范围：1～19200
    *  在emH239FlowControlReleaseRequest
    *  和emH239FlowControlReleaseResponse消息中使用      
    */
    u32             m_dwBitRate;          
    
    /**
    *  MT取1～127之间的随机值;
    *  MCU可以设为0，但是有具体含义
    */
    u8              m_bySymmetryBreaking; 
    
    tagH239Info()
    {
        Clear();
    }

    void Clear();

    void host2net(BOOL32 bhton);

    BOOL32 SetH239InfoType(emH239InfoType nH239InfoType);
  
    emH239InfoType GetH239InfoType()
    {
        return m_emH239InfoType;
    }
    
    void SetTerLabel(TTERLABEL &tTerlabel)
    {
        m_tTerLabel = tTerlabel;
    }

    TTERLABEL &GetTerlabel()
    {
        return m_tTerLabel;
    }

    void SetSymmetryBreaking(u8 bySymmetryBreaking)
    {
        m_bySymmetryBreaking = bySymmetryBreaking;
    }
    u8 GetSymmetryBreaking()
    {
        return m_bySymmetryBreaking;
    }
    
    void SetResponseAck(BOOL32 bIsResponseAck)
    {
        m_bIsResponseAck = bIsResponseAck;
    }
    BOOL32 IsResponseAck()
    {
        return m_bIsResponseAck;
    }
    
    void SetChannelId(HCHAN hsChan)
    {
        m_nChannelId = cmGetLCNFromHchan(hsChan);
    }
    s32 GetChannelId()
    {
        return m_nChannelId;
    }
    void SetChannelId(s32 nChannelId)
    {
        m_nChannelId = nChannelId;
    }
    
}TH239INFO,*PTH239INFO;

/**/////////////////////////////// 参数结构 ////////////////////////////////*/
/**userInput结构，有冲突，使用企业的定义（union）*/
typedef struct PROTO_API tagUserInputInfo 
{
    emUserInputIndication m_emUserInputType;
	union
	{
		struct 
		{
           s8  m_chSignalType;     /**<FROM ("0123456789#*ABCD!")*/
           s32 m_nDuration;        /**<超时值，单位：milliseconds*/
		}usersignal;
        s8 m_achAlphaNumeric[5];
	}arguments;

	s32 m_nNonStandardDataLen;
	u8* m_pbyNonStandardData; 

    tagUserInputInfo()
    {
		m_pbyNonStandardData = NULL;
		m_nNonStandardDataLen = 0;
		m_emUserInputType = emUserInputSignal;
        arguments.usersignal.m_chSignalType = '\0';
        arguments.usersignal.m_nDuration = 300;
		
    }

	/**对指针赋值，不能保存， 小心！！！！！！！！*/
	BOOL32 SetNonStandData(u8 *pBuf, s32 nLen);

    /**获取指针，不能保存小心！！！！！！！！*/
	BOOL32 GetNonStandData(u8 **ppBuf, s32 *pnLen);
			
    void SetSignalType(s8 signalType)
    {
        arguments.usersignal.m_chSignalType = signalType;
    }

    s8 GetSignalType()
    {
        return arguments.usersignal.m_chSignalType;
    }

    void SetDuration(s32 duration)
    {
        arguments.usersignal.m_nDuration = duration;
    }

    u16 GetDuration()
    {
        return arguments.usersignal.m_nDuration;
    }
	void SetAlpaNumericString( s8* string, u16 wLen );

	u16  GetAlpaNumericStringLen()
	{
		return strlen(arguments.m_achAlphaNumeric);
	}

	s8*  GetAlpaNumericString()
	{
		return arguments.m_achAlphaNumeric;
	}
}TUserInputInfo,*PTUserInputInfo;

typedef struct tagMultiplexCapability
{
	emH264NALMode m_emH264NALMode;

	tagMultiplexCapability()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emH264NALMode = emNALNode;
	}
	
	void SetH264NALMode( emH264NALMode emNALMode)
	{
		m_emH264NALMode = emNALMode;
	}
	emH264NALMode& GetH264NALMode()
	{
		return m_emH264NALMode;
	}

}TMultiplexCapability,*PTMultiplexCapability;
/**///////////////////////////   消息中带的结构体 //////////////////////////*/

/**Facility参数*/
typedef struct tagFacilityUUIE
{
	u8			  m_byReason;					/**<FacilityReason*/
	TAliasAddr	  m_tAlternativeAddrAlias;
	TCONFERENCES  m_tConferences;

	u8			  m_abyCallId[LEN_GUID]; 
	BOOL32        m_bExistCallId;
	
	/**begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010*/

	TFacilityConfList_NSM  m_atConfList_NSM[MAX_CONF_NUM];

	/**end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010*/

	tagFacilityUUIE()
	{
		Clear();
	}

	void Clear();

	/**设置TAliasAddr*/
	void SetAliasAddr( TAliasAddr &tAliasAddr )
	{
		m_tAlternativeAddrAlias = tAliasAddr;
	}

	/**获取TAliasAddr*/
	TAliasAddr& GetAliasAddr()
	{
		return m_tAlternativeAddrAlias;
	}

	/**设置TCONFERENCES*/
	void SetConferences( TCONFERENCES &tConf )
	{
		m_tConferences = tConf;
	}

	/**获取TCONFERENCES*/
	TCONFERENCES& GetConferences()
	{
		return m_tConferences;
	}

	/**获取呼叫ID*/
	s32 GetCallId(u8* pbyCallId, s32 nLen);
	
	/**设置呼叫ID*/
	void SetCallId(const u8* pbyCallId,u8 byLen);

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_atConfList_NSM[MAX_CONF_NUM-1].SetContinueFlag( bIsContinue );
    }
    BOOL32 IsContinue( void )
    {
        return m_atConfList_NSM[MAX_CONF_NUM-1].IsContinue();
    }

}TFACILITYINFO,*PTFACILITYINFO;


// typedef struct 
// {
// 	TFeccStruct m_tFeccStruct;
// 	TTERLABEL   m_tSrcTer;
// 	TTERLABEL   m_tDstTer;
// }TH245Fecc;

#endif //_H323CONFSTDSTRUCT_H
