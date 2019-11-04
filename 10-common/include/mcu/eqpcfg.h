//
//外设配置
//
//
#ifndef _PERIPHERY_EQUIPMENT_CONFIG_H_
#define _PERIPHERY_EQUIPMENT_CONFIG_H_

#include "mcuconst.h"

#define MAXNUM_MAP    5

#define QOS_AUDIO   (s32)1  // 音频Qos
#define QOS_VIDEO   (s32)2  // 视频Qos
#define QOS_DATA    (s32)3  // 数据Qos


#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
#endif


struct TMAPParam
{
	u32  dwCoreSpd;     // Map内核速度
	u32  dwMemSpd;      // 内存速度
	u32  dwMemSize;     // 内存大小
	u8   byMapId;	    // Map编号
	u32   dwPort;	    // Map端口号
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设基本配置结构
struct TEqpCfg
{
	char  achAlias[ MAXLEN_ALIAS+1 ];
	u8    byEqpId;          //外设ID
	u8    byEqpType;        //外设类型

	u32   dwLocalIP;        //本机IP地址
	u32   dwConnectIP;      //连接MCUIP地址
	u16   wConnectPort;     //连接MCU 通信端口
	u16   wMcuId;           //MCU id 号
	u16   wRcvStartPort;    //接收起始端口号
	u16   wMAPCount;        //使用的MAP个数
	TMAPParam m_atMap[MAXNUM_MAP];	//map信息

    u32 dwConnectIpB;
    u16 wConnectPortB;
    u16 wRcvStartPortB;

    TEqpCfg(void) { memset(this, 0, sizeof(TEqpCfg)); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TAudioMixerCfg : public TEqpCfg
{
	u8    byMaxMixGroupCount;
	u8    byMaxChannelInGroup;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//等DVMP上来逐步废除该结构体// xliang [5/27/2009] 
struct TVmpCfg : public TEqpCfg
{
	u8   by_VmpStyle;
	u8   byDbVid;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPrsCfg:public TEqpCfg
{
    u16  m_wFirstTimeSpan;	    //第一个重传检测点(ms)
	u16  m_wSecondTimeSpan;     //第二个重传检测点(ms)
	u16  m_wThirdTimeSpan;      //第三个重传检测点(ms)
	u16  m_wRejectTimeSpan;     //过期丢弃的时间跨度(ms)
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//4.6 新加版本 jlb
struct THduModePort
{
public:
	THduModePort()
	{
		memset(this, 0x0, sizeof(THduModePort));
	}
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }
	
    u8   GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8   GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }

private:
    u8 byOutPortType;
    u8 byOutModeType;
    u8 byZoomRate;
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct THduCfg : public TEqpCfg
{
protected:
	BOOL  m_bAutoTest;
	u8   byReserved[4];
    THduModePort atHduModePort[MAXNUM_HDU_CHANNEL];
public:
	THduCfg(void)
	{
        memset(atHduModePort, 0x0, sizeof(atHduModePort));
	}
	void GetHduModePort( u8 byNum, THduModePort &tHduModePortType )
	{
        tHduModePortType.SetOutModeType(atHduModePort[byNum].GetOutModeType());
		tHduModePortType.SetOutPortType(atHduModePort[byNum].GetOutPortType());
		tHduModePortType.SetZoomRate(atHduModePort[byNum].GetZoomRate());
	}
	void SetHduModePort( u8 byNum, THduModePort &tHduModePortType )
	{
        atHduModePort[byNum].SetOutModeType(tHduModePortType.GetOutModeType());
		atHduModePort[byNum].SetOutPortType(tHduModePortType.GetOutPortType());
		atHduModePort[byNum].SetZoomRate(tHduModePortType.GetZoomRate());
	}
	u8   GetEqpId( void ){ return byEqpId; }
	u8   GetEqpType( void ){ return byEqpType; }
    u16   GetMcuId( void ){ return wMcuId; }
    
	BOOL GetAutoTest( void ){ return m_bAutoTest; }
	void SetAutoTest( BOOL bAutoTest ){ m_bAutoTest = bAutoTest; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMpuCfg : public TEqpCfg
{
protected:
	u8		m_byVmpStyle;
	u8		m_byDbVid;
	u8		m_byReserved1;
	u8		m_byReserved2;
	BOOL32  m_bAutoTest;
public:
	TMpuCfg(void)
	{
		m_bAutoTest = FALSE;
		m_byVmpStyle = 0;
		m_byDbVid	= 0;
	}

	BOOL IsAutoTest( void ){ return m_bAutoTest; }
	void SetAutoTest( BOOL bAutoTest ){ m_bAutoTest = bAutoTest; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


#ifdef WIN32
    #pragma pack( pop )
#endif

#endif // _PERIPHERY_EQUIPMENT_CONFIG_H_
