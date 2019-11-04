#ifndef __IMTCCONNECTMT_H__
#define __IMTCCONNECTMT_H__

#include "ummessagestruct.h"// 身份验证业务
#include "mtstruct.h"   //终端控制业务
#include "IMtcCam.h"
#include "IMtcAudioDevice.h"
#include "IMtcConf.h"
#include "IMtcP2PConf.h"
#include "IMtcRemoteCtrl.h"
#include "IMtcCfgMt.h"
#include "IMtcMatrix.h"
#include "IMtcUser.h"
#include "IMtcMonitor.h"
#include "IMtcAddrbook.h"
#include "IMtcVOD.h"
#include "imtcfxo.h"

#include "IMtcRecoder.h"
struct TTransFileInfo
{
	BOOL m_bSuc;        //是否成功
	u16 m_wMaxPackNum;  //最大包数
	u16 m_wCurPackNum;  //当前包序号
};

struct TUpgradeResult
{
	BOOL m_bSuc;        //是否成功
	u16 m_wRes;			//错误码
};

struct TUpgradeSrvAddr
{
	BOOL m_IsDefault;
	s8	*m_abAddr;
};
struct TUpgradeFileList
{
	u32 m_dwFileNum;
	TVerInfo *m_ptVerInfo;
};
class IMtcConnectMt : public CDispEvent
{
public:
    /*功能	获取登录用户信息（用户名和IP地址）
	参数	无
	返回值	登录用户信息
	说明	无*/
	virtual CString GetUserInfo(void) const = 0;
    /*功能	查询是否初始话完成
	参数	无
	返回值	TRUE 	初始话完成
			FALSE	没有初始话完成
	说明	无*/
	virtual BOOL IsInitFinish() = 0;
	/*功能	查询是否已连接终端
	参数	无
	返回值	TRUE 	已连接终端
			FALSE	没有连接终端
	说明	无*/
	virtual BOOL IsMtcConnectedMt() = 0;
	/*功能	查询本地终端的首选IP
	参数	无
	返回值	u32 IP地址（本地序）
	说明	无*/
	virtual u32 GetLocalIP() const = 0;
	/*功能	查询终端的IP地址
	参数	无
	返回值	u32 IP地址（本地序）
	说明	无*/
	virtual u32 GetConnectedMtIP() const = 0;
    /*功能	查询是否监控终端
    参数	无
    返回值	TRUE 	含监控程序的终端
    FALSE	不含监控程序的终端
    说明	无*/
    virtual BOOL32 IsInnerMonitorMt() = 0;
	/*功能	查询连接的终端
	参数	无
	返回值	连接的终端
	说明	无*/
	virtual const CMtcMt& GetConnectedMt() = 0;
	/*功能	查询登录的用户
	参数	无
	返回值	登录用户
	说明	无*/
	virtual const CLoginRequest& GetConnectedUser() = 0;
    /*功能	查询登录的用户
	参数	无
	返回值	登录用户
	说明	无*/
	virtual const TTerStatus& GetMtStatus() = 0;
	/*功能	获取特定的控制接口
	参数	ppCtrl	控制接口
	返回值	成功返回0,失败返回非0错误码
	说明	在连接到终端时,可以获取这些接口,在断开连接后,所有这些接口立刻失效*/
	virtual u16 MtcGetCtrlInterface(IMtcMonitor **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcCam **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcMatrix **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcAudioDevice **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcRemoteCtrl **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcCfgMt **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcUser **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcAddrbook **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcP2PConf **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcConf **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcVOD **ppCtrl) = 0;
	virtual u16 MtcGetCtrlInterface(IMtcFxo **ppIMtcFxo)=0;
//	virtual u16 MtcGetCtrlInterface(IMtcRecoder **ppIMtcRecoder)=0;
	/*功能	配置TCP结点端口号
	参数	u16		TCP端口号
	返回值	u16		返回以前的端口号*/
	virtual u16 ConfigTcpPort(u16 wPort) = 0;
	/*功能	连接到终端
	参数	dwIP	被连接终端的IP地址，主机序
			strUser	用户名
			strPwd	密码
	返回值	成功返回0,失败返回非0错误码
	说明	若连接失败，发送MTC_UI_CMD_FAILED消息,其中WPARAMK中为MCS_UM_LOGIN_REQ
			LPARAM中为错误原因,错误原因代码见umconst.h中的定义*/
	virtual u16 MtcConnectMt(u32 dwIP, u32 dwPort,
		const CString& strUser,
		const CString& strPwd, BOOL32 bConnect = TRUE) = 0;
	/*功能	断开与终端的连接
	参数	无
	返回值	成功返回0,失败返回非0错误码
	说明	在没有连接到终端时调用此方法，不起任何作用*/	
	virtual u16 MtcDisconnectMt() = 0;
	/*功能	注册消息接收窗口
	参数	hWnd	接收消息的窗口
	返回值	成功返回0,失败返回非0错误码
	说明	若为hWnd传递NULL,则不发送消息*/
	virtual u16 MtcConnectMtUIRegisterRecvWnd(HWND hWnd) = 0;
	/*功能	获取接收消息的窗口
	参数	无
	返回值	接收消息的窗口
	说明	无*/
	virtual HWND MtcConnectMtGetUIRecvWnd() = 0;
	/*功能	向业务库发送消息
	参数	wEventId	消息标识号
			pbyBuf		消息内容缓冲区
            nLen        消息的长度
	返回值	成功返回0;失败返回非0错误码
	说明	直接向业务库发送信息,需注意字节序问题*/
	virtual u16 DirectPost(u16 wEventId, const u8* pbyBuf, s32 nLen) = 0;
	/*功能	获取GK状态
	参数	无
	返回值	TRUE	已注册GK
			FALSE	未注册GK*/
	virtual BOOL GetGKStatus() = 0;
	/*功能	获取板卡类型
	参数	无
	返回值	板卡类型,或0xff未知板卡类型
	说明	板卡类型定义在MtConstDef.h文件里*/
	virtual EmMtModel GetMtBoardType() = 0;  
	/*功能	通过OSP的telnet dump内部信息
	参数	无
	返回值	无
	说明	无*/
	virtual void Dump() = 0;
	/*功能	获取快照信息
	参数	无
	返回值	快照信息
	说明	收到MTC_UI_SNAPSHOT_UPDATED消息后用此方法更新快照信息*/
	virtual const TSnapInfo& GetSnapShotInfo()const = 0;
	/*功能	通知终端osd刷新快照信息
	参数	无
	返回值	是否成功
	说明	*/
	virtual u16 UpdateShotInfoList() = 0;
	/*功能	请求同步快照信息
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	请求成功后,会收到MTC_UI_SNAPSHOT_UPDATED通知*/
	virtual u16 ReqSnapShotInfo() = 0;
	/*功能	终端快照
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
	virtual u16 SnapShot() = 0;
	/*功能	清除快照
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	快照信息更新后,向界面发送MTC_UI_SNAPSHOT_UPDATED通知*/
	virtual u16 ClearSnapShot() = 0;
    /*功能	请求终端信息
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	请求成功后,会收到MTC_UI_MTSTATUS_UPDATED通知*/
	virtual u16 ReqMtStatus() = 0;
    /*功能	重启终端
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
	virtual u16 ResetMt() = 0;
	/*功能	休眠终端
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
    virtual u16 StartDormancyMt(u16 wDelay) = 0;
	/*功能	停止休眠终端
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
    virtual u16 StopDormancyMt() = 0;
	/*功能	申请升级终端，如果终端忙碌不容许升级，返回的消息为False
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
	virtual u16 UpdateSystemReq(const CString& strName) = 0;
	/*功能	上传文件结果通知，成功为True， 失败为False
	参数	无
	返回值	成功返回0;失败返回非0错误码
	说明	*/
	virtual u16 UpLoadFileNotify( BOOL32 bResult ) = 0;
	/*函数名： GetInitTestPort
    功    能： 获取集成测试端口号
    参    数： 
    返 回 值： virtual u16 
    说    明： */
	virtual u16 GetInitTestPort() = 0;
    /*函数名： GetDormancyDelay
    功    能： 获取待机等待时间
    参    数： 
    返 回 值： virtual u16 
    说    明： */
    virtual u16 GetDormancyDelay() =0;
    /*函数名： GetEventName
    功    能： 获取消息名字，便于调试
    参    数： u16 wEvent
    返 回 值： virtual CString 
    说    明： */
    virtual CString GetEventName(u16 wEvent) = 0;   
    /*函数名： TransferBigFile
    功    能： 传输文件接口
    参    数： u8 nType  文件类型 台标、滚动消息、字幕等 如MT_OSD_TITLE为字幕
               u8 *pbyBuf = NULL 文件指针LIB库里面不分配内存，由上层来创建内存，lib库来释放内存
               u32 dwBufSize  文件大小
               u32 dwTimeOut  发送请求消息等待时间
    返 回 值： void 
    说    明： */
    virtual u16 TransferBigFile(u8 nType, u8 *pbyBuf = NULL,
                                u32 dwBufSize = 0, u32 dwTimeOut = 10000) = 0;   
    /*函数名： IsTransfering
    功    能： 判断是否正在传输文件
    参    数： 
    返 回 值： BOOL32 
    说    明： 同一个时刻只能有一个文件在传输*/
    virtual BOOL32 IsTransferingFile() = 0;

    /*函数名： IsUsedMC
    功    能： 是否启用MC
    参    数： 
    返 回 值： virtual BOOL32&
    说    明： */
    virtual BOOL32& IsUsedMC() = 0;

    /*函数名： GetMCMode
    功    能： MC工作模式
    参    数： 
    返 回 值： virtual EmMCMode&
    说    明： */
    virtual EmMCMode& GetMCMode() = 0;
	/*函数名： ReqMTSysTime
    功    能：请求查询终端系统时间
    参    数： 
    返 回 值： virtual u16
    说    明： */
	virtual u16   ReqMTSysTime()=0;    

	virtual u16 UploadLicenseFile(const CString& strFilePath) = 0;
	/*函数名： SendSrvAddrCfg
    功    能： 发送升级服务器的地址信息
    参    数： 
    返 回 值： virtual u16
    说    明： */
	virtual u16 SendSrvAddrCfg(BOOL bflag, s8 *pAddr, int length) = 0; 
	/*函数名： ConnectUpgradeSrv
    功    能： 连接升级服务器
    参    数： 
    返 回 值： virtual u16
    说    明： */
	virtual u16 ConnectUpgradeSrv() = 0;
	/*函数名： CancelUpgrade
    功    能： 取消升级
    参    数： 
    返 回 值： virtual u16
    说    明： */
	virtual u16 CancelUpgrade() = 0; 
	/*函数名： StartupUpgrade
    功    能： 开始升级
    参    数： 升级文件编号
    返 回 值： virtual u16
    说    明： */
	virtual u16 StartupUpgrade(u8 byFileNum) = 0;	  //开始升级

	/*函数名： ResumeUpgrade
    功    能： 断点重传
    参    数： 
    返 回 值： virtual u16
    说    明： */
    virtual u16 ResumeUpgrade() = 0;  
	
	virtual u16 DisconnectUpgradeSrv() = 0; //断开升级服务器
	virtual TVerInfo &GetVerInfo() = 0; //获取升级文件
	virtual TUpgradeFileList &GetVerList() = 0; //文件升级列表
	virtual TTransFileInfo &GetFileTransferInfo() = 0; //当前传送文件片信息
	virtual BOOL GetConnectResult() = 0;



	//Log 日志
	virtual u16 UpdateWriteLog(BOOL32 bWriteLog) = 0;
	virtual BOOL32 GetIsLog() = 0;
	
	//ExportLog 导出日志
	virtual u16 UpdateExportLog( u8 Param = 0) = 0;
	virtual u32 GetExportLog() = 0;
	//请求log导出到本地
	virtual u16 ReqDownloadLogToLocal(EmMtFile filetype) = 0;
	//完成导出到本地
	virtual u16 FinishDownloadLog() = 0;
}; // IMtcConnect

#endif