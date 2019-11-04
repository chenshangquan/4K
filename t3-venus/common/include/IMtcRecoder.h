#ifndef __IMTCRECODER_H__
#define __IMTCRECODER_H__

#include "dispevent.h"

#include "RPCtrl.h"
#include "CodecLib.h"
#include "channelinfo.h"
#include "vccommon.h"

class IMtcRecoder : public CDispEvent
{
public:
	//继续录像
	virtual DWORD ResumeRec() = 0;
	
	//暂停录像
	virtual DWORD PauseRec() = 0;
	
	//是否暂停录像
	virtual BOOL IsPause() = 0;
	
	//是否正在录像
	virtual BOOL IsRunning() = 0;
	//   设置录像频道信息
	virtual void SetRecChannelInfo(TChannelEncrypt  tChannelInfo) = 0;
    
	//初始化录像库
    ///virtual static BOOL InitRec(const DWORD dwRecCount) = 0;
	virtual BOOL InitRec(const DWORD dwRecCount) = 0;
	
	//设置文件保存路径
    virtual BOOL SetRecPath(const CString &strPath) = 0;
	
	//设置码流转发参数
    virtual BOOL SetTransferDecoder(CKdvDecoder *pcDecoder, DWORD dwDestIP, WORD wDestPort, u8 byActivePt=0) = 0;
	
	//开始录像
    virtual WORD StartRec() = 0;
    
	//停止录像
    virtual BOOL StopRec() = 0;
    
	//退出、释放录放像库
    ///virtual static  BOOL QuitRec() = 0;
	virtual BOOL QuitRec() = 0;
    
	// 是否已经初始化
    ///virtual static BOOL IsInited() = 0;    
	virtual BOOL IsInited() = 0;    
	
	//是否在录像过程中
    virtual BOOL IsRecording() = 0;    
}; // IMtcRecoder

#endif
