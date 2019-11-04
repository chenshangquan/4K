#ifndef  _ASF_TRANS_
#define  _ASF_TRANS_

#if _MSC_VER > 1000
#pragma once
#endif

#include "asflib.h"
#include "helpmacro.h"
#include "string"

using namespace std;
//////////////////////////////////////////////////////////////////////////
// ERROR_CODE
OSPEVENT( ASF_TRANS_NO_ERROR,			 0 );
OSPEVENT( ASF_TRANS_FILENAME_EMPTY,		 1 );		//输入/输出的码流文件为空
OSPEVENT( ASF_TRANS_FILE_OPEN_FAILED,	 2 );		//打开输入码流文件失败
OSPEVENT( ASF_TRANS_GET_STREAM_NUM_FAILED, 3 );		//获取流属性个数失败
OSPEVENT( ASF_TRANS_STREAM_NUM_ZERO,     4 );		//流属性个数为0
OSPEVENT( ASF_TRANS_GET_STREAM_PROPERTY_FAILED, 5 );//获取流属性失败
OSPEVENT( ASF_TRANS_IN_MEMORY_SHORT,		6 );  //传入的数组空间太小
OSPEVENT( ASF_TRANS_WRITE_FILE_OPEN_FAILED, 7 );	//写入码流文件打开失败
OSPEVENT( ASF_TRANS_SET_STREAM_PROPERTY_FAILED, 8 ); //写入流属性失败

//开始: WPARAM: 1; LPARAM: 0
//进度: WPARAM: 2; LPARAM: u32(进度百分数, 个位数字代表小数点后一位)
//结束: WPARAM: 3; LPARAM: 0(成功), -1(用户主动停止), -2(空间不足), 其他(Asflib库函数返回值)
//提示: WPARAM: 4; LPARAM: 0
#define WM_ASF_TRANS				    WM_USER + 0x4323

BEGIN_NAME_SPACE

class CAsfTransEncoder;
class CAsfTransDecoder;
typedef CAsfTransDecoder CDecoder;
typedef CAsfTransEncoder CEncoder;

extern UINT TransFunctionProc(LPVOID lpParam);
extern void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
//extern void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);

//定义上层感兴趣的数据
typedef struct tagStreamInfo
{
	u8		byType;				//流的类型,是音频还是视频流
	u8		byStreamNumber;		//流序号
	u8		byMediaType;		//媒体类型，视频261,263...,音频g711,mp3....
	u32		dwDuration;			//持续时间
	u32		dwAverageBitrate;	//平均码率
	s32		nWidth;				//图像编码的宽度
	s32		nHeight;			//图像编码的高度
public:
	tagStreamInfo()
	{
		memset(this, 0, sizeof(tagStreamInfo) );
	}
}TStreamInfo;

class CAsfTrans
{
public:
	typedef enum EmSuffix
	{
		emFirst = 0,
		emSecond,
		emMaxNum,
	}Suffix;

	enum EmStreamPropertyNum
	{
		emMaxStreamNum = 3
	};

	//在ASF文件的流序号相应的顺序1,2,3, 在数组中下标分别为0,1, 2
	enum EmStreamNum
	{
		emFirstAudio = 0,
		emFirstVideo = 1,
		emSecondVideo = 2
	};

#define MIN_WARN_SPACE          200//小于200M给出提示
#define MIN_STOP_SPACE          50//小于50M直接停止
    enum EmSpaceLeft
    {
        emSpaceOk       = 0,
        emSpaceWarning  = 1,
        emSpaceStop     = 2
    };

public:

	CAsfTrans();
	~CAsfTrans();

	/*函数名： SetInStreamPath
    功    能： 设置输入文件的全路径
    参    数： IN const char* szInPath
    返 回 值： void 
    说    明： */
	void SetInStreamPath( IN const char* szInPath ) ;
    /*函数名： GetInStreamPath
    功    能： 得到输入文件的全路径 
    参    数： 
    返 回 值： const char* 
    说    明： */
	const char* GetInStreamPath() const;

    /*函数名： SetOutStreamPath
    功    能： 设置输出文件的全路径
    参    数： IN const char* szOutPath
    返 回 值： void 
    说    明： */
	void SetOutStreamPath( IN const char* szOutPath );
    /*函数名： GetOutStreamPath
    功    能： 得到输出文件的全路径
    参    数： 
    返 回 值： const char* 
    说    明： */
	const char* GetOutStreamPath() const;

    /*函数名： SetNotifyHWND
    功    能： 设置通知消息的发送窗口句柄
    参    数： HWND hWnd
    返 回 值： void 
    说    明： */
	void SetNotifyHWND(HWND hWnd);
    /*函数名： RegisterMsg
    功    能： 注册通知的消息ID
    参    数： u32 dwMsgId		    [in]消息ID
    返 回 值： void 
    说    明： 开始: WPARAM: 1; LPARAM: 0
               进度: WPARAM: 2; LPARAM: u32(进度百分数, 个位数字代表小数点后一位)
               结束: WPARAM: 3; LPARAM: 0(成功), -1(用户主动停止), -2(空间不足), 其他(Asflib库函数返回值)
               提示: WPARAM: 4; LPARAM: 0 */
	void RegisterMsg(u32 dwMsgId);
    /*函数名： IsDual
    功    能： 是否包含两路码流
    参    数： 
    返 回 值： BOOL32 
    说    明： 双流的时候流的个数为3，一路音频，两路视频 */
	BOOL32 IsDual() const
	{
		return m_dwStreamNum >= 3 ? TRUE : FALSE; 
	}

    /*函数名： GetInStreamInfo
    功    能： 获取输入文件相应的流属性信息
    参    数： OUT TStreamInfo *ptStreamInfo  [in]输入数组的起始地址
               OUT u32 &dwNum				  [out]输入数组的大小/以及实际返回的大小	
    返 回 值： u16 
    说    明： */
	u16 GetInStreamInfo( OUT TStreamInfo *ptStreamInfo, OUT u32 &dwNum );
    /*函数名： SetOutStreamInfo
    功    能： 设置输出文件相应的流属性信息
    参    数： IN TStreamInfo *ptStreamInfo		[in]输入数组的起始地址
               IN u32 &dwNum					[in]输入的大小
    返 回 值： u16 
    说    明： */
	u16 SetOutStreamInfo( IN TStreamInfo *ptStreamInfo, IN u32 &dwNum );

    /*函数名： BeginTransform
    功    能： 开始视频格式,码流大小的转化
    参    数： 
    返 回 值： BOOL32 
    说    明： */
	BOOL32 BeginTransform(void);

    /*=============================================================================
    函 数 名:EndTransform
    功    能:用户主动停止转换
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/07/27  4.0     王昊    创建
    =============================================================================*/
    void EndTransform(void);

    /*=============================================================================
    函 数 名:CheckSpace
    功    能:检查剩余空间
    参    数:LPCTSTR lptrDisk           [in]    例如 C:\
    注    意:无
    返 回 值:EmSpaceLeft
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/08/12  4.0     王昊    创建
    =============================================================================*/
    EmSpaceLeft CheckSpace(LPCTSTR lptrDisk = NULL) const;

private:
	void Init();

	u16 GetInStreamProperty( OUT TStreamProperty * ptStreamPro, OUT u32 &dwNum );
	u16 SetOutStreamProperty( IN u32 dwNum );

    /*函数名： GetOutStreamInfo
    功    能： 获取输出的码流信息,因为无法直接从属性中直接得到码流格式
    参    数： OUT TStreamInfo* ptStreamInfo
               OUT u32 &dwNum
    返 回 值： u16 
    说    明： */
	u16 GetOutStreamInfo(OUT TStreamInfo* ptStreamInfo, OUT u32 &dwNum );

	//forbid copy constructor and assign operator
	CAsfTrans(const CAsfTrans& rhs){};
	CAsfTrans& operator=(const CAsfTrans& rhs){};

private:
	CDecoder*		m_apDecoder[emMaxNum];			//码流的解码器
	CEncoder*		m_apEncoder[emMaxNum];			//码流的编码器

	string		    m_strInputPath;				//转换码流输入文件的全路径
	string		    m_strOutputPath;				//转换码流输出文件的全路径
	BOOL32			m_bNeedReread;				//是否需要重新读取输入码流的属性	
	TStreamProperty	m_atInStreamProperty[emMaxStreamNum];	//码流文件中流属性
	TStreamProperty m_atOutStreamProperty[emMaxStreamNum];	//输出码流的流属性

	CKdvASFFileReader m_cReader;				//ASF 文件阅读器		
	CKdvASFFileWriter m_cWriter;				//ASF 文件写入器
	u32				  m_dwStreamNum;		//文件中的码流的个数,用来判断是否有双流存在
	HWND			  m_hWnd;					//通知上层界面的句柄 
	u32				  m_dwMsg;				//通知消息ID

	BOOL32			m_bOspInnerInit;			//记录Osp是否是内部初始化的
	BOOL32			m_bTransfering;				//是否正在忙
    HANDLE          m_hEvent;                   //等待事件量

    HWND            m_hTimerWnd;        //定时句柄

	friend UINT TransFunctionProc(LPVOID lpParam);
    friend void CALLBACK EXPORT TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);
};

END_NAME_SPACE

#endif