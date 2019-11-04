#ifndef __IMTCCAM_H__
#define __IMTCCAM_H__

#include "dispevent.h"
#include "vector"

using namespace std;

class IMtcCam : public CDispEvent
{
public:
    /*函数名： GetCamSource
    功    能： 得到当前的视频源(远端，本地)
    参    数： 
    返 回 值： virtual u16& 
    说    明： */
	virtual u16 GetCamSource() = 0;

    /*函数名： GetVSource
    功    能： 获取当前的视频源（c1 -- c6 , vga ,s）
    参    数： 
    返 回 值： virtual EmMtVideoPort& 
    说    明： */
	virtual EmMtVideoPort& GetVSource() = 0;
    /*函数名： GetVSource
    功    能： 获取当前辅视频源
    参    数： 
    返 回 值： virtual EmMtVideoPort& 
    说    明： */
	virtual EmMtVideoPort& GetVSecSource() = 0;

	/*功能	控制摄像头云台向上、向下、向左、向右运动
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 CameraTurnUp() = 0;
	virtual u16 CameraTurnUpStop() = 0;
	virtual u16 CameraTurnDown() = 0;
	virtual u16 CameraTurnDownStop() = 0;
	virtual u16 CameraTurnLeft() = 0;
	virtual u16 CameraTurnLeftStop() = 0;
	virtual u16 CameraTurnRight() = 0;
	virtual u16 CameraTurnRightStop() = 0;
	/*功能	自动调整摄像头的焦距
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/	
	virtual u16 CameraAdjustFocusAuto() = 0;
	/*功能	手动调近或调远摄像头的焦距
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 CameraAdjustFocus2Near() = 0;
	virtual u16 CameraAdjustFocus2NearStop() = 0;
	virtual u16 CameraAdjustFocus2Far() = 0;
	virtual u16 CameraAdjustFocus2FarStop() = 0;
	/*功能	增加（或减小）摄像头的亮度
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/	
	virtual u16 CameraIncLum() = 0;
	virtual u16 CameraIncLumStop() = 0;
	virtual u16 CameraDecLum() = 0;
	virtual u16 CameraDecLumStop() = 0;
	/*功能	放大或缩小摄像头的视野
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	无*/	
	virtual u16 CameraZoomIn() = 0;
	virtual u16 CameraZoomInStop() = 0;
	virtual u16 CameraZoomOut() = 0;
	virtual u16 CameraZoomOutStop() = 0;
	/*功能	加载（或保存）摄像头的状态
	参数	dwPos	保存位置索引，有效范围(0~3)
	返回值	成功返回0;失败返回非0错误码
	说明	无*/	
	virtual u16 CameraLoadStatus(u8 byPos) = 0;
	virtual u16 CameraSaveStatus(u8 byPos) = 0;
	/*功能	选择视频源
	参数	EmMtVideoPort emPort
	返回值	成功返回0;失败返回非0错误码
	说明	无*/	
	virtual u16 SelectCamera( EmMtVideoPort emPort , EmVideoType emType = emPriomVideo) = 0;
	/*功能	本地远端摄像头切换
	参数	bLocal 是否切换到本地摄像头
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 SwitchSourceCam(EmSite emSite) = 0;
	
	virtual const vector<TVideoSourceInfo>& GetVSourceInfo() = 0;

	virtual u16 UpdateVSourceInfo( const TVideoSourceInfo& tVSourceInfo ) = 0;

	virtual u16 SetAutoDualSrc() = 0;
	virtual BYTE& GetAutoDualSrc() = 0;
}; // IMtcCam

#endif