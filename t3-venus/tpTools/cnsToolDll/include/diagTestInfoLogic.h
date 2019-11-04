// diagTestInfoLogic.h: interface for the CDiagTestInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_)
#define AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagTestInfoLogic : public CLogicBase, public ISingleTon<CDiagTestInfoLogic>   
{
public:
	CDiagTestInfoLogic();
	virtual ~CDiagTestInfoLogic();
	
	//CLogicBase
public:	 	
	/** 功能:  注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候,会调用其中注册的函数
	*/
	virtual void RegCBFun();
	/** 功能:  反注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  与上面函数相反,注销注册的函数
	*/
	virtual void UnRegFunc();
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	/** 功能:  清理窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在窗口关闭的时候调用,清空窗口数据
	*/
    virtual void Clear();

protected:	
	/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** 功能: 反注册消息,与上面函数相反,注销注册的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
private:
	/** 功能:  收到诊断测试结果的消息响应(视频)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVideoDiagInfoInd( WPARAM wparam, LPARAM lparam);
	/** 功能:  收到诊断测试结果的消息响应(音频)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnAudioDiagInfoInd( WPARAM wparam, LPARAM lparam);
	/** 功能:  收到诊断测试结果的消息响应(domodal窗口)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnDomodalDiagTestWnd( WPARAM wparam, LPARAM lparam);
	/** 功能:  收到停止诊断测试的结果(结束domodal窗口)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnStopAVMatrixRsp( WPARAM wparam, LPARAM lparam);
	/** 功能:  下一页按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnNextPage( const IArgs & arg );
	/** 功能:  上一页按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnPrePage( const IArgs & arg );
	/** 功能:  关闭窗口按钮(右上角叉叉)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnCloseDiagTest( const IArgs & arg );
	/** 功能:  导出报告按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnExRePort( const IArgs & arg );
	/** 功能:  获取摄像机的分辨率及帧率信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String GetVideoInfo( TTPVideoPortInfo& tVideoPortInfo );
	/** 功能:  将收到的分辨率信息转化为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String ChangeResToString( EmTpVideoResolution& emVideoRes );
	/** 功能:  将收到的演示源输入接口信息转化为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String VgaInToString( EmVgaType& emDualInput );
	/** 功能:  将收到的演示源输出接口信息转化为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String VgaOutToString( EmDualOutputType& emDualOutput );
	/** 功能:  获取音频输出设备的音量信息
	*  @param[in] 
	*  @return 
	*  @remarks   				
	*/
	String GetAudioOutInfo( TTpAudioPortInfo& tAudioPortInfo );
	/** 功能:  获取音频输出接口的序号
	*  @param[in] 
	*  @return  存取音频接口的数目
	*  @remarks   
	*/
	u32 GetAudioNum();
	/** 功能:  将具体的音量值转化为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String CommonToStr( u32 u );
	/** 功能:  判断check框是否被选中
	*  @param[in] strWnd  控件名称
	*  @return 
	*  @remarks   
	*/
	s32 GetCheckState( String strWnd );
	/** 功能:  获取界面接口信息
	*  @param[in] strWnd  控件名称
	*  @return 
	*  @remarks   
	*/
	String GetAVPortInfo();

private:
	TTPAudioDiagInfo m_tAudioDiagInfo;

	String  m_strDiagInVideo;
	String	m_strDiagInAudio;

	String  m_strDiagOutVideo1;
	String  m_strDiagOutVideo2;
	String  m_strDiagOutVideo3;
	String  m_strDiagOutVideo4;
	
	String	m_strDiagOutAudio1;
	String	m_strDiagOutAudio2;
	String	m_strDiagOutAudio3;
	s32 m_bIsUse[10];							//用来存放具体是哪个卡农麦克风被选中
	const String m_strCamera1;					//摄像机1	
	const String m_strCamera2;					//摄像机2
	const String m_strCamera3;					//摄像机3
	const String m_StrShowCameraInfo;			//选择的演示源	
	const String m_strShowCamera;				//演示源具体信息	
	const String m_strDisPlay1;					//显示器1
	const String m_strCheckDisPlay1;			//检测显示器1是否有图像
	const String m_strDisPlay2;					//显示器2
	const String m_strCheckDisPlay2;			//检测显示器2是否有图像
	const String m_strDisPlay3;					//显示器3
	const String m_strCheckDisPlay3;			//检测显示器3是否有图像
	const String m_strVoiceBox1;				//主音箱1
	const String m_strCheckVoiceBox1;			//检测主音箱1是否有声音
	const String m_strVoiceBox2;				//主音箱2
	const String m_strCheckVoiceBox2;			//检测主音箱2是否有声音
	const String m_strVoiceBox3;				//主音箱3
	const String m_strCheckVoiceBox3;			//检测主音箱3是否有声音
	const String m_strShowScreenInfo;			//选择的演示屏
	const String m_strShowScreen;				//演示屏信息
	const String m_strCheckShowScreen;			//检测演示屏是否有图像

};

#endif // !defined(AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_)
