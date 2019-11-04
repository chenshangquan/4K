// vcdconvert.h: interface for the CVcdConvert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VCDCONVERT_H__C28639EF_BB38_4CBE_8B09_899FF6EEC356__INCLUDED_)
#define AFX_VCDCONVERT_H__C28639EF_BB38_4CBE_8B09_899FF6EEC356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include "kdvtype.h"
#include "StdAfx.h"	// Added by ClassView

#ifdef VCDTRANS_EXPORTS
#define VCDTRANS_API __declspec(dllexport)
#else
#define VCDTRANS_API __declspec(dllimport)
#endif

typedef struct tagVideoInfo
{
	u8		byType;				//流的类型,是音频还是视频流
	u8		byStreamNumber;		//流序号
	u8		byMediaType;		//媒体类型，视频261,263...,音频g711,mp3....
	u32		dwDuration;			//持续时间
	u32		dwAverageBitrate;	//平均码率
	s32		nWidth;				//图像编码的宽度
	s32		nHeight;			//图像编码的高度
public:
	tagVideoInfo()
	{
		memset(this, 0, sizeof(tagVideoInfo));
	}
}TVideoInfo;
typedef enum enSpaceLeft
{
	emSpaceOk       = 0,
	emSpaceWarning  = 1,
	emSpaceStop     = 2
}enumSpaceLeft;

class CVCDTrans;

VCDTRANS_API int vcdtranver(void);

class VCDTRANS_API CVcdConvert  
{
public:
	enumSpaceLeft CheckSpace(LPCTSTR lptrDisk  = NULL ) const;
	VOID EndTransform();
	u16 GetInStreamInfo( TVideoInfo *ptStreamInfo, u32 &dwNum );
	const char* GetOutStreamPath();
    void GetInStreamPath(std::vector<std::string> &vctstrInputFile);
	u16 GetOutStreamInfo(const TVideoInfo *ptStreamInfo);
	VOID SetNotifyMsg(HWND hWnd,u32 dwMsg);
	VOID SetOutStreamPath(const char *szOutPath);
	VOID SetInStreamPath(const s8 (*lptrInputFile)[MAX_PATH + 1], s32 nFileNum);
	BOOL32 SetOutInfo(TVideoInfo *ptVideoInfo, u8 byAudioType,u8 byRatio=0);
	BOOL32 BeginTransform();
	CVcdConvert();
	virtual ~CVcdConvert();
private:
	CVCDTrans *m_pVcdTrans;
	BOOL32     m_bOspSelfInitd;

};

#endif // !defined(AFX_VCDCONVERT_H__C28639EF_BB38_4CBE_8B09_899FF6EEC356__INCLUDED_)
