#ifndef _CN_MPREMOTEMGR_STRUCT_H
#define _CN_MPREMOTEMGR_STRUCT_H
#include "kdvdef.h"
#include "cnmpremotemgrsys.h"

// #ifdef WIN32
// #pragma  pack(push)
// #pragma  pack(1)
// #define PACKED 
// #else
// #define PACKED __attribute__((__packed__))	// 取消编译器的优化对齐
// #endif

typedef struct tagRegInfo 
{
public:
    tagRegInfo()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagRegInfo));
    }

public:
    u32 m_dwIP;
    u8  m_byScreenIndex;
   
}TRegInfo;

typedef struct tagTerminalRegInfo 
{
public:
    tagTerminalRegInfo()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagTerminalRegInfo));
    }

public:
    TRegInfo m_tRegInfo;
    u32 m_dwNode;
    BOOL m_bUsed;
    u32 m_dwId;

}TTerminalRegInfo;


typedef struct tagMpSnapshotinfo 
{
public:
    tagMpSnapshotinfo()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagMpSnapshotinfo));
    }

public:

     EmTpSnapShotType m_emTpSnapShotType;
     u8	m_byPanCamIndx;
     u8	m_byPresetIdx; 
    
}TMpSnapshotinfo;


typedef struct tagTMPVideoEncDecRes
{
    //EmTpVideoResolution enRes;//分辨率
    u32 dwWidth;
    u32 dwHeight;
    TTpCodecComponent tTpCodc;
    BOOL bvalid;//是否有效
public:
    tagTMPVideoEncDecRes()
    {
        memset( this ,0 ,sizeof( struct  tagTMPVideoEncDecRes ) );
        bvalid = FALSE;
    }
}TMPVideoEncDecRes;

typedef struct tagTMPVideoEncDecResPack
{
    TMPVideoEncDecRes  atVideoRes[TP_MAX_VIDEO_RES_NUM];
    u8 byNum;

public:
    tagTMPVideoEncDecResPack()
    {
        memset( this ,0 ,sizeof( struct  tagTMPVideoEncDecResPack ) );		 
    }
}TMPVideoEncDecResPack;

typedef struct tagTMPCodecPackStat
{
    TTPVideoFrameRatePack  tTPVideoFrameRatePack;//从编解码器获取实际帧率
    TMPVideoEncDecResPack  tMPVideoEncDecResPack;//从编解码器获取实际分辨率
    TTPVideoRecv           tTPVideoRecv;  //编码器有没有视频源输入
    TTPAudPower            tTPAudPower; //音频功率

public:
    tagTMPCodecPackStat()
    {
        memset( this ,0 ,sizeof( struct  tagTMPCodecPackStat ) );		 
    }
}TMPCodecPackStat;

//文件传输结构体
typedef struct tagTMPFileTransInfo
{
public:
    tagTMPFileTransInfo()
    {
        memset( this ,0 ,sizeof( struct  tagTMPCodecPackStat ) );		 
    }
public:
    s8  m_achDataFileName[MP_FTP_SERVER_TRANSFILE_LEN_MAX];
    u8  m_byDataFlag; //1:表示开始 2：表示结束 3：表示既有开始又有结束, 一次就传输完成
    u8  m_abyData[MP_DATA_TRANS_MAX_SIZE];    
    u16 m_wDataLen;
    
}TMPFileTransInfo;



// #ifdef WIN32
// #pragma  pack(pop)
// #endif


#endif // _CN_MPREMOTEMGR_STRUCT_H
