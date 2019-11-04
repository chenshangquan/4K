// dvdtrans.h: interface for the CDvdTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DVDTRANS_H__A2DE305B_618D_419A_887E_755D39AE70DB__INCLUDED_)
#define AFX_DVDTRANS_H__A2DE305B_618D_419A_887E_755D39AE70DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "string"
using namespace std;
#include "asflib.h"

#pragma warning(disable : 4251)

#ifndef MIN_WARN_SPACE
#define MIN_WARN_SPACE          200//小于200M给出提示
#define MIN_STOP_SPACE          50//小于50M直接停止
#endif


#ifdef DVDTRANS_EXPORTS
#define DVDTRANS_API __declspec(dllexport)
#else
#define DVDTRANS_API __declspec(dllimport)
#endif

#define MAX_LANGUAGE     256       //最长语言字符数


enum
{
		DVD_Error_NoError				= 0,   // 没有错误，正确返回
		DVD_Error_FileNotFound			= 1,   // 文件没有找到
		DVD_Error_InvalidDvdFile		= 2,	// 无效的DVD文件
		DVD_Error_Transing              = 3,    //正在转换中
		DVD_Error_OpenError             = 4,
		DVD_Error_UnknownError			= 5	// 无法确定的错误		
};
typedef u16 Error_Code;

typedef struct tagDvdInfo{
	u8		byVideoType;		//视频261,263...,
	u32		dwVideoBitrate;	    //平均码率
	u8      byAudioType;        //音频g711,mp3....
	u8      byRatio;            //mp3 0,1,2,3,4
	u8      bySelectedAudio;    //选择的音频序号
	u8      bySelectedSubPic;   //选择的字幕序号
	
}TDvdInfo;

typedef struct tagDvdAttr{
	u8     byNumberOfAudio;
	LCID   adwAudioLanguage[8];
	u8     byNumberOfSubPic;
	LCID   adwSubPicLanguage[32];
	public:
		tagDvdAttr()
		{
			memset(this,0,sizeof(tagDvdAttr));
		}

}TDvdAttr;

class CDvdReader;
class CAudioEncoder;
class CAsfTransEncoder;
typedef CAsfTransEncoder CVideoEncoder;

class DVDTRANS_API CDvdTrans  
{
public:
	u16 GetDvdAttr( OUT TDvdAttr & tDvdAttr);
//	u16 GetSubPicAttr(IN u16 wSubPicIndex,OUT const TSubPicAttr &tSubPicAttr);
//	u16 GetSubPicCount(u16 &wSubPicCount);
//	u16 GetAudioAttr( IN u16 wAudioIndex,OUT TAudioAttr *ptAudioAttr);
//	u16 GetAudioCount(OUT u16 &wAudioCount);
	u16 SetOutInfo(const TDvdInfo &tDvdInfo);
	BOOL32 SetOutStreamPath(const char *szOutPath);
	BOOL32 SetInStreamPath(const char *szInPath=NULL);
	BOOL32 SetNotifyMsg(HWND hWnd,u32 dwMsg);
	u16 EndTransform();
	u16 BeginTransform();

    s32 CheckSpace(LPCTSTR lptrDisk  = NULL ) const;

	CDvdTrans();
	virtual ~CDvdTrans();

private:
	BOOL ChangeFile(u32 dwLastFileStamp);
	void YV12_I420(u8 *pInputBuf, u32 dwWidth, u32 dwHeight);
	VOID DealData(u32 dwStatus, TStreamDataPayload *ptStreamPayload);
	void Close();
	void DvdTransProc();
	BOOL32 ConfigAsfFileProperty(u32 dwWidth,u32 dwHeight);
	CDvdReader            *m_pcDvdReader;
	CKdvASFFileWriter     *m_pcAsfWriter;
	CAudioEncoder         *m_pcAudioEncoder;
	CVideoEncoder         *m_pcVideoEncoder;

	TDvdInfo    m_tDvdInfo;

    string 	    m_strInputPath;				//转换码流输入文件的全路径
	string		    m_strOutputPath;			//转换码流输出文件的全路径
	HWND			m_hWnd;					//通知上层界面的句柄 
	u32				m_dwMsg;				//通知消息ID

//	HANDLE           m_hStopEvent;
	HANDLE           m_hDvdThread;

	BOOL32              m_bTransfering;         //是否正在忙
	volatile BOOL32     m_bStop;
	u8                  *m_pbyVideoBuf;
	u8                  *m_pbyZoomBuf;
	u8                  *m_pbyChangeBuf;
    u8              m_byAudioMode;      //设置的音频类型
	u32             m_dwOutWidth;
	u32             m_dwOutHeight;
	u32              m_dwFileDuration;           //ms
	u32              m_dwFileSize;             //文件大小
	u32              m_dwFileIndex;            //当前转换文件
//	BOOL32           m_bFirstTime;
//	u64              m_llAudioTimeOffSet;
//	u64              m_llVideoTimeOffSet;
    BOOL32          m_bOspSelfInit;

    u32             m_dwLastFileStamp;
	u8              *m_pbyRemainBuf;
	u32             m_dwRemainLen;
	u8              *m_pbyAudioBuf;

	
    HWND                m_hTimer;

    TStreamProperty     m_atStreamProp[2];

	friend  void DvdTransThread(void *lpParam);
	friend  void DataProcCB(u32 dwStatus, TStreamDataPayload *ptStreamPayload,
                            void *pContext);
    friend VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

};

#endif // !defined(AFX_DVDTRANS_H__A2DE305B_618D_419A_887E_755D39AE70DB__INCLUDED_)
