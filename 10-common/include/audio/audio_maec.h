/*****************************************************************************
模块名      : audio_maec
文件名      : audio_maec.h
相关文件    : 
文件实现功能: 多声道AEC对外结构体声明和对外函数的声明
版本        : v100  Copyright(C) 2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日    期      版本        修改人      修改内容
03/22/2013    v100        陆志洋      创建
******************************************************************************/
#ifndef _AUDIO_MAEC_H_
#define _AUDIO_MAEC_H_

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#define TMAecStatusParam TMAecParam

//初始化参数结构体
typedef struct 
{	
    l32 l32CapSigFrameLen;          //近端播放信号帧长
    l32 l32PlaySigFrameLen;         //远端采集信号帧长
    l32 l32SampleRate;              //支持的采样率(32000)
    l32 l32RefChannelNum;           //回声抵消每通道参考信号路数(3)
    l32 l32CapChannelNum;           //支持回声抵消的通道数(3)
    l32 l32BitWidth;                //样本位宽模式(TEnumAudBitWidth)
    u32 u32Reserved;                //保留参数 
}TMAecParam;

//MAec播放端输入数据结构体
typedef struct
{
    s16 *aps16PlayBuf[3];          //指向播放端各通道输入缓冲区的指针数组
    u32 u32PlayBufSize;            //每个通道播放端输入缓冲区的字节数
    l32 l32CapBufSamples;          //采集缓冲区的样点数
    l32 l32PlayBufSamples;         //播放缓冲区的样点数
    u32 u32Reserved;               //保留参数
}TMAecPlayInput; 

//MAec采集端输入数据结构体
typedef struct
{
    s16 *ps16CapBuf;               //采集端输入缓冲区的指针
    u32 u32CapBufSize;             //采集端输入缓冲区的字节数
    s16 *ps16OutBuf;               //输出端缓冲区的指针
    u32 u32OutBufSize;             //输出端缓冲区的字节数
    l32 l32ChannelID;              //通道号(0, 1, 2)
    u32 u32Reserved;               //保留参数
}TMAecCapInput; 

/*====================================================================
函   数   名:  MAecOpen
功        能:  多声道AEC的初始化
引用全局变量:  无
输入参数说明:  ppvHandle             指向AEC句柄指针的指针[in]
			   ptMAecParam           指向初始化参数结构体的指针[in]
			   ptMAecMemParam        指向内存分配结构体的指针[in]
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码  
特 殊 说  明:  无
======================================================================*/
l32 MAecOpen(void **ppvHandle, TMAecParam *ptMAecParam, void *ptMAecMemParam);

/*====================================================================
函   数   名:  MAecReset
功        能:  多声道AEC修改编解码类型时重新设置的参数
引用全局变量:  无
输入参数说明:  pvHandle             指向AEC句柄的指针[in]
			   ptMAecParam          指向初始化参数结构体的指针[in]
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecReset(void *pvHandle, TMAecParam *ptMAecParam);

/*====================================================================
函   数   名:  MAecPlaySigSet  
功        能:  多声道AEC把远端信号放入远端信号的缓存中
引用全局变量:  无
输入参数说明:  pvHandle               指向AEC句柄的指针[in]
			   ptMAecPlayInput        指向播放端输入数据结构体指针[in]
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecPlaySigSet(void *pvHandle, TMAecPlayInput *ptMAecPlayInput);

/*====================================================================
函   数   名:  MAecPreProcess
功        能:  多声道AEC所有通道前处理
引用全局变量:  无
输入参数说明:  pvHandle                指向AEC句柄的指针[in]
返回值说明  :  成功: AUDIO_SUCCESS,    失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecPreProcess(void *pvHandle);

/*====================================================================
函   数   名:  MAecSubProcess
功        能:  多声道AEC每个子通道回声抵消
引用全局变量:  无
输入参数说明:  pvHandle               指向AEC句柄的指针[in]
			   ptMAecCapInput         指向采集端输入数据结构体指针[in]
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecSubProcess(void *pvHandle, TMAecCapInput *ptMAecCapInput);

/*====================================================================                        
函数名      : MAecGetStatus                                                                 
功能        : 多声道AEC得到状态信息                                                                        
算法实现    : 无                                                                              
引用全局变量: 无                                                                              
输入参数说明: pvHandle               指向AEC句柄的指针[in]
              ptMAecStatusParam      指向MAEC状态参数结构体指针[in/out]                                 
返回值说明  : 成功: AUDIO_SUCCESS, 失败: 返回错误码
特 殊 说  明:  无
====================================================================*/                        
l32 MAecGetStatus(void *pvHandle, TMAecStatusParam *ptMAecStatusParam);

/*====================================================================
函   数   名:  MAecGetVersion
功        能:  多声道AEC获取回声抵消的版本
引用全局变量:  无
输入参数说明:  *pvVer                指向输出版本号缓存的指针[in]
			   l32BufLen             输入的版本号字符串的长度[in]
			   pl32VerLen            实际的版本号字符串的长度[in/out]
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*====================================================================
函   数   名:  MAecClose
功        能:  多声道AEC关闭
引用全局变量:  无
输入参数说明:  pvHandle             指向AEC句柄的指针[in] 
返回值说明  :  成功: AUDIO_SUCCESS, 失败: 返回错误码 
特 殊 说  明:  无
======================================================================*/
l32 MAecClose(void *pvHandle);

#ifdef __cplusplus
}

#endif  /* __cplusplus */

#endif
