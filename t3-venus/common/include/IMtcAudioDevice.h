#ifndef __IMTCAUDIODEVICE_H__
#define __IMTCAUDIODEVICE_H__

#include "dispevent.h"

class IMtcAudioDevice : public CDispEvent
{
public:
	/*功能	查询是否静音
	参数	无
	返回值	TRUE	静音中
			FALSE	非静音
	说明	终端是否输出音频信号*/
	virtual BOOL IsLocalSpeakerMute() const = 0;
	/*功能	查询是否哑音
	参数	无
	返回值	TRUE	哑音中
			FALSE	非哑音
	说明	终端是否被接受音频信号的输入*/
	virtual BOOL IsLocalMicMute() const = 0;
	/*功能	查询终端输出（或输入）音量
	参数	无
	返回值	音量大小，介于0~25之间
	说明	无*/
	virtual u8 GetLocalSpeakerVolume() const = 0;
	virtual u8 GetLocalMicVolume() const = 0;
	/*功能	调节终端输出（或输入）音量
	参数	dwVolume	音量大小，介于0~25之间
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
    virtual u16 AdjustLocalSpeakerVolume(u8 byVolume) = 0;
    virtual u16 AdjustLocalMicVolume(u8 byVolume) = 0;
	/*功能	启用(或取消)静音
	参数	bMute	是否启用静音
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 MuteLocalSpeaker(BOOL bMute = TRUE) = 0;
	virtual u16 MuteLocalMic(BOOL bMute = TRUE) = 0;

	/*功能	转储
	参数	无
	返回值	无
	说明	无*/
	virtual void Dump() = 0;
}; // IMtcAudioDevice


#endif