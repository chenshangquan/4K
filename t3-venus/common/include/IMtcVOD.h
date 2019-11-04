#ifndef  __IMTCVOD_H_
#define	 __IMTCVOD_H_

#include "DispEvent.h"
#include "mtstruct.h"
#include "vector"

using namespace std;

class IMtcVOD : public CDispEvent
{
public:
	/*功能	获取文件列表请求
	参数	const CString& csDirName   请求的目录名称		
	返回值	成功返回0
	说明	*/
	virtual u16 ReqFileList(const CString& csDirName) = 0;
	/*功能	获取当前目录下面的所有的文件名
	参数	无			
	返回值	点播服务器的文件列表
	说明	*/
	virtual const vector<TVODFileNameInfo>& GetFilelist() const = 0;
	/*功能	请求某一文件信息
	参数	const CString& csFileName   请求的文件名称			
	返回值	成功返回0
	说明	*/
	virtual u16 ReqFileInfo(const CString& csFileName) = 0;
	/*功能	获取文件的文件信息
	参数	无			
	返回值	TVODFileInfo  VOD文件信息
	说明	*/
	virtual const TVODFileInfo& GetFileInfo() const = 0;
	/*功能	获取文件名称等信息
	参数	无			
	返回值	TVODFileNameInfo  VOD文件名称、大小信息
	说明	*/
    virtual const TVODFileNameInfo& GetFileNameInfo() const = 0;
	/*功能	获取文件的播放状态
	参数	无			
	返回值	EmAction  文件的播放状态
	说明	*/
	virtual EmAction GetPlayState() const = 0;
	/*功能	获取文件播放总时长
	参数	无			
	返回值	u32 文件的播放长度(秒)
	说明	*/
	virtual u32 GetDuration() = 0;
	/*功能	获取文件播放已经播放的长度
	参数	无			
	返回值	u32 文件已经播放的长度
	说明	*/
	virtual u32 GetPlayTime() = 0;
	/*功能	连接VOD服务器			
	参数	u32 dwLoginIP    服务器的IP地址(网络序)
			u16 wPort	     登陆的端口
			const CString &csUserName	用户名称
			const CString& csPwd		密码
	说明	*/
	virtual u16 LoginVODServer(u32 dwLoginIP, u16 wPort, const CString &csUserName,
		const CString& csPwd) = 0;
	/*功能	退出VOD服务器
	参数	无			
	返回值	成功返回0
	说明	*/
	virtual u16 LogoutVODServer() = 0;
	//文件播放请求
	virtual u16 PlayFile(const CString& csFileName) = 0;
	//文件停止播放请求
	virtual u16 StopPlayFile() = 0;
	//播放信息请求
	virtual u16 ReqPlayInfo() = 0;
	//播放跳转指示
	virtual u16 RandomPlay(u32 dwStartPoint) = 0;
	//播放暂停请求
	virtual u16 PausePlay() = 0;
	//播放恢复请求
	virtual u16 ResumePlay() = 0;
	//是否在VOD点播中
	virtual BOOL IsInVod() = 0;
	

};

#endif