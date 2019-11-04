#ifndef _h_tptime_h__
#define _h_tptime_h__


#include "osp.h"
#include "kdvtype.h"

typedef s32 (*KdvTimerHandler)(u32 dwTimerId, void* param);


typedef enum
{
    TIME_FREE  = 0,
	TIME_ALLOC,
	TIME_RUNNING,
} TimerState;


typedef struct tagTpTimer
{
    void*           m_pParam;					//回调函数的参数
    u32             m_dwInterval;               //定时器的间隔毫秒数
	KdvTimerHandler m_pCallBack;				//回调函数
    u32             m_dwAbsTime;                //定时器的绝对触发时刻
    TimerState      m_eState;
	
    struct tagTpTimer* m_ptNext;				//用户链表的指针
	
	//05.9.5
	tagTpTimer()
	{
		m_pCallBack = NULL;
		m_pParam = NULL;
		m_ptNext = NULL;
	};
	~tagTpTimer()
	{
		m_pCallBack = NULL;
		m_pParam = NULL;
		m_ptNext = NULL;
	}
} TTpTimer;


class CTpTimerMgr
{
public:
    CTpTimerMgr();
    ~CTpTimerMgr();
    
public:
    BOOL32  Create(s32 nTotalNum);    
    s32  Close();    
	
    TTpTimer* AddTimer(u32 dwInterval, KdvTimerHandler pCallBack, void* context);
	
    BOOL32 DeleteTimer(TTpTimer* ptTimer);
	
    BOOL32 UpdateTimer(TTpTimer* ptTimer);
	
    s32 Check();	
	
    s32 GetStatis(u32* pdwNowTime, s32* pnTotal, s32* pnUsed);
	
    
	//private:
public:
    TTpTimer* m_ptUsedList; //使用列表
    
    TTpTimer* m_ptFreeListFirst;    //空闲头列表
	
    TTpTimer* m_ptFreeListLast;    //空闲尾指针
	
	
    TTpTimer* m_patTimer;  //开辟的定时器数组
    
    u32 m_dwNowTime;        //当前时间
	s32 m_nTimerCount;      //定时器总个数
    s32 m_nUsedCount;
	
private:
    BOOL32 DeleteFirst();
    TTpTimer* NewTimer();
    BOOL32 AddTimer(TTpTimer* ptTimer);
	
	
};


#endif // _h_tptime_h__
