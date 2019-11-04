#ifndef __IMTCREMOTECTRL_H__
#define __IMTCREMOTECTRL_H__

#include "dispevent.h"
#include "key.h"

class IMtcRemoteCtrl : public CDispEvent
{
public:
	/*功能	查询终端当前是否接收遥控器操作
	参数	无
	返回值	TRUE	终端当前允许遥控器操作
	FALSE	终端当前禁止遥控器操作
	说明	无*/
	virtual BOOL IsEnableRemoteCtrl() const = 0;
	/*功能	控制终端启用或禁用遥控器
	参数	bEnable	是否启用遥控器
	返回值	无
	说明	无*/
	virtual u16 EnableRemoteCtrl(BOOL bEnable = TRUE) = 0;
    /*功能	虚拟遥控器键控制总接口
    参数	无
    返回值	成功返回0;失败返回非0错误码
    说明	PressDown	按下
    ReleaseUp	弹起
    Click		点击(按下后再弹起)*/
    virtual u16 PressDown(u8 u8Key, u8 u8Type = SBLACK_REMOTE) = 0;	// 按下
    virtual u16 ReleaseUp(u8 u8Key, u8 u8Type = SBLACK_REMOTE) = 0;	// 弹起
    virtual u16 Click(u8 u8Key, u8 u8Type = SBLACK_REMOTE) = 0;		// 按下后弹起

}; // IRemoteCtrl

#endif