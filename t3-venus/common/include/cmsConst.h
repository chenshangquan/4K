/*****************************************************************************
模块名      : CMS控制台
文件名      : cmsConst.h
相关文件    : 
文件实现功能: 声明常量和错误代码,供cms的UI部分和lib（umclib 和 cnclib）部分共同使用
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/23  1.0          俞锦锦      创建
******************************************************************************/
#pragma once

#ifndef _CMSCONST_20110423_H_
#define _CMSCONST_20110423_H_

#include "printctrl.h"  

//------------------------------常量部分------begin-------------------------------
#define ARRAY                          vector
#define INVALID_WORD           0xffff                                           //非法的u16 / unsinged short 类型的值
#define INVALID_DWORD          0xffffffffff                                     //非法的u32/ DWORD 类型的值
#define MSG_SUCESS             -1                                               //消息传递时使用


#define INSTANT_CONFTEMPLATE_ID   0                                             //用于开即时会议的 会议模板  
#define INSTANT_CONFTEMPLATE_NAME "的临时会议"                                  //用于开临时会议的 会议模板 
#define PTP_CONF                  "点对点会议"                                  //点对点会议

#define CONFTEMPLATE_MAX_COUNT    128                                            //会议模板的最多为128个
#define MAX_VOLUME                32                                           //最大音量


#define MAX_USER_COUNT           128                                         //最大用户个数
#define MAX_PAGE_COUNT           14                                          //一页显示的最大会场个数

#define MANAGER_USER              "admin"                                    //管理员用户名
#define MANAGER_PSWD              "kedacomTP"									 //管理员密码
#define TP_PASSWORD               "tpkedacom"                                //解锁超级密码

 
#define CONNETCT_SERVER_PORT   60001                                     //登录UMS服务器端口
#define CONNETCT_CNS_PORT      60002                                     //CNS服务器端口号 
#define CNS_SIP_LISTEN_PORT    60000
#define LOCAL_CNS                 1                                      //本地CNS Inst号

#define INVALID_ALIAS_FOR_SHOW        "; / ? : @ & = + $ ， % ^ ——#"               //提示给用户的非法字符，别名中不可以包含，否则会引起呼叫失败
#define INVALID_ALIAS_FOR_CODE        "  `~!@$^&%()+=#|{}:;'\\[]<>/?！……（）——【】‘；：”“'。，、？￥＄＆"  //编码中使用，为了便于提示，同时禁用掉中文输入法下的相同字符
#define RTP_LOCALVIDEO_PORT    10000 	                // 本地RTP端口

#define DEFAULT_CODEGE         CP936

//会议中MainMenu名
#define MENU_ENDCONF           "结束会议"       
#define MENU_CNSCTRL           "会场控制"
#define MENU_AUDMIX            "会议讨论"
#define MENU_PIP		       "画中画"
#define MENU_TVW               "电视墙"
#define MENU_CNSPOLL           "会场轮询"
#define MENU_MUTE              "麦克风开关"
#define MENU_QUITE             "扬声器开关"
#define MENU_CNSDUAL           "本方演示开关"
#define MENU_SPEAKER           "扬声器"
#define MENU_MIC               "麦克风"
#define MENU_DUALSRC           "演示源"
#define MENU_ADDRBOOK          "地址簿"


#define PrtMsg (CPrintCtrl::GetPrintCtrl()->PrintMsg)                        //打印消息接口
#define PrtMsgForce (CPrintCtrl::GetPrintCtrl()->ForcePrtMsg)
#define IS_PRINT_ENTER_MSG (CPrintCtrl::GetPrintCtrl()->IsPrintEnterMsg())   //是否要打印入口处消息
#define IS_PRINT_OUT_MSG (CPrintCtrl::GetPrintCtrl()->IsPrintOutMsg())       //是否打印出口处消息
#define MAPPING_HELPER (CPrintCtrl::GetPrintCtrl()->MappingHelper)           //注册打印的消息名
  


//------------------------------错误码部分------begin-------------------------------
/* 摘自errorid.h
终端控制台错误(27501 - 29500)
#define ERR_CMS_BGN		ERR_HDU_END + 1
#define ERR_CMS_END		ERR_CMS_BGN + 1999
*/
#include "errorid.h"	// 错误码范围段定义

//共用部分 
enum EmErrCommon
{
#define  ERR_COMMON_BEGIN  ERR_CMS_BGN

	
	errCms = ERR_COMMON_BEGIN,
#define  ERR_CMS  errCms 

//osp 初始化失败
	errOspInit,
#define  ERR_CMS_OSP_Init  errOspInit   

//命令超时
    errCmdTimeout,
#define  ERR_CMS_CMD_TIME_OUT errCmdTimeout 

	//未找到相应项
    errNotFind,
#define  ERR_CMS_NOT_FIND   errNotFind


	//参数非法
    errParamIllegal,
#define  ERR_CMS_PARAM   errParamIllegal

 
   errCommonEnd,
#define ERR_COMMON_END  errCommonEnd
};


 

//umcLib中的错误码
enum EmErrUmcLib
{
#define  ERR_UMC_LIB_BEGIN  ERR_COMMON_END+1  

	
//命令处理超时
   errUmcCmdTimeout= ERR_UMC_LIB_BEGIN, 
#define ERR_UMC_CMD_TIMEOUT errUmcCmdTimeout 

//umcLib 初始化 osp失败	
   errUmcOspInit,
#define	ERR_UMC_OSP_Init       
 
//创建APP 失败
  errCreateOspFail,
#define ERR_UMC_CREATE_OSP_FAIL errCreateOspFail
 

//已连接
   errActiveConnection,
#define	 ERR_UMC_ACTIVE_CONNECTION errActiveConnection 
   

//tcp连接失败
   errCreateTcpFail,
#define	ERR_UMC_CREATE_TCP_FAIL errCreateTcpFail    

   

//osp 等待发送命令 
   errWaitForSendCmd,
#define  ERR_UMC_WAIT_FOR_SEND_CMD    NO_ERROR   //errWaitForSendCmd 避免操作过快时 会报错            
 	 
//---------login--------- 
//登录ums失败
    errLoginFail,
#define ERR_UMC_LOGIN_FAIL   errLoginFail

    errLoginUmsUserErr,
#define  ERR_UMC_LOGIN_UMS_USER_ERR errLoginUmsUserErr 

   errLoginUmsPswdErr,
#define  ERR_UMC_LOGIN_UMS_PSWD_ERR errLoginUmsPswdErr    

   //达到用户登录上限
   errLoginUmsMaxLogin,
#define  ERR_UMC_LOGIN_UMS_MAX_LOGIN errLoginUmsMaxLogin          
 	
//达到用户登录上限
   errLoginUmsLogged,
#define  ERR_UMC_LOGIN_UMS_LOGED errLoginUmsLogged   


  //达到用户登录上限
   errLoginUmsSysIniting,
#define  ERR_UMC_LOGIN_UMS_SYSINITING errLoginUmsSysIniting   

   
//---------使用会议模板开会相关--------- 
//未知错误
   errCmsStartConf_UnknowErr,
#define  ERR_UMC_STARTCONF_CONFTEMP_UNKNOW_ERR  errCmsStartConf_UnknowErr

   //开启会议失败：会议模板不存在
   errCmsStartConf_ConftempUnexist,
#define  ERR_UMC_STARTCONF_CONFTEMP_UNEXIST  errCmsStartConf_ConftempUnexist
   
   //开启会议失败：会议已满
   errCmsStartConf_ConfFull,
#define  ERR_UMC_STARTCONF_CONF_FULL  errCmsStartConf_ConfFull
    
   
   //开启会议失败：会议已存在
   errCmsStartConf_ConfExist,
#define  ERR_UMC_STARTCONF_CONF_EXIST  errCmsStartConf_ConfExist
   
//---------呼叫相关---------    
   // 呼叫失败：对端不接收
   errCmsCallCnsHungup,
#define  ERR_UMC_CALLCNS_HUNGUP EmCnsCallReason_hungup
   
   //呼叫失败：对端不可达
   errCmsCallCnsUnreachable,
#define  ERR_CMS_CALLCNS_UNREACHABLE errCmsCallCnsUnreachable
   
   
   //呼叫失败：对端无可用资源
   errCmsCallCnsResourcefull,
#define  ERR_UMC_CALLCNS_RESOURCE_FULL errCmsCallCnsResourcefull
   
   
   //呼叫失败：对端不存在
   errCmsCallCnsDstNotFound,
#define  ERR_UMC_CALLCNS_DST_NOT_FOUND errCmsCallCnsDstNotFound
   
   
   //呼叫失败：对端忙
   errCmsCallCnsBusy,
#define  ERR_UMC_CALLCNS_BUSY errCmsCallCnsBusy
   
   //呼叫失败：本地原因
   errCmsCallCnsLocal,
#define  ERR_UMC_CALLCNS_LOCAL errCmsCallCnsLocal
   
   //呼叫失败：会议不存在
   errCmsCallCnsNoConf,
#define  ERR_CMS_CALLCNS_NO_CONF errCmsCallCnsNoConf
   
   //呼叫失败：对端已在会议中
   errCmsCallCnsExist,
#define  ERR_UMC_CALLCNS_CNS_EXIST errCmsCallCnsExist

   //对端拒绝
   errCmsCallCnsRejected,
#define  ERR_UMC_CALLCNS_CNS_REJECTED errCmsCallCnsRejected

   //对端挂断
   errCmsCallCnsPeerHungup,
#define  ERR_UMC_CALLCNS_CNS_PEERHUNGUP errCmsCallCnsPeerHungup

   //本地掉线挂断
   errCmsCallCnsAbnormal,
#define  ERR_UMC_CALLCNS_CNS_ABNORMAL  errCmsCallCnsAbnormal
   
   //对端掉线挂断
   errCmsCallCnsPeerAbnormal,
#define  ERR_UMC_CALLCNS_CNS_PEERABNORMAL  errCmsCallCnsPeerAbnormal

   //会议结束
   errCmsCallCnsConfOver,
#define  ERR_UMC_CALLCNS_CNS_CONFOVER  errCmsCallCnsConfOver

   //接入模块(cncall)掉线
   errCmsCallCnsCallException,
#define  ERR_UMC_CALLCNS_CNS_CALLEXCEPTION  errCmsCallCnsCallException

   //会议已存在
   errCmsCallCnsConfExist,
#define  ERR_UMC_CALLCNS_CNS_CONFEXIST  errCmsCallCnsConfExist

   //未知原因
   errCmsCallCnsUnKnown,
#define  ERR_UMC_CALLCNS_CNS_UNKNOWN  errCmsCallCnsUnKnown
   
   //挂断会议错误
   errCmsHungupConfUnexist,
#define  ERR_UMC_HUNGUP_CONF_UNEXIST errCmsHungupConfUnexist

//---------地址簿相关--------- 
   //存在相同地址簿条目
   errUmcAddrEntryExist,
#define ERR_UMC_ADDR_ENTRY_EXIST errUmcAddrEntryExist

    errUmcLibEnd,
#define ERR_UMC_LIB_END errUmcLibEnd

};




//cncLib中的错误码
enum EmErrCncLib
{

#define ERR_CNC_LIB_BEGIN  ERR_UMC_LIB_END+1 

	// CNS控制台错误
	errCnc = ERR_CNC_LIB_BEGIN,
#define ERR_CNC                 errCnc

	//创建实例失败
	errCreatInstance,
#define ERR_CNC_CREATINSTANCE   errCreatInstance

	//接口无效
	errInterface,
#define ERR_CNC_INTERFACE       errInterface

	//已连接上
	errActiveConnect,
#define	ERR_CNC_ACTIVE_CONNECT  errActiveConnect

	//TCP连接失败
	errTcpConnect,
#define	ERR_CNC_TCPCONNECT      errTcpConnect
	
	//抓包拒绝抢登
	refuseCNCLOGIN,
#define	Refuse_CNC_LOGIN      refuseCNCLOGIN

	//TCP连接失败
	errCnsLoginFail,
#define	ERR_CNC_LOGIN_FAIL     errCnsLoginFail

	//osp 等待发送命令 
	errCncWaitSendCmd,
#define ERR_CNC_WAIT_FOR_SEND_CMD errCncWaitSendCmd 
	
    //数组越界
    errCncArrayOverbounds,
#define ERR_CNC_ARRAY_OVERBOUNDS  errCncArrayOverbounds

	errCncLibEnd,
#define ERR_CNC_LIB_END      errCncLibEnd
		
};


 

//cms UI中的错误码
enum EmErrCmsUI
{
 
 //登录相关
    //ums 登录失败
   errCmsUmsLogin =  ERR_CNC_LIB_END+1 ,
#define ERR_CMS_UI_UMS_LOGIN errCmsUmsLogin

   //cns登录失败
   errCmsCnsLogin  ,
#define ERR_CMS_UI_CNS_LOGIN errCmsCnsLogin
  
//用户名重复
  errCmsNameRepeat,
#define  ERR_CMS_UI_NAME_REPEAT errCmsNameRepeat
 
 
  //E164号重复
  errCmsE164Repeat ,
#define  ERR_CMS_UI_E164_REPEAT errCmsE164Repeat
   
  //未获取到本地cns信息
  errCmsGetLocalCnsInfo,
#define ERR_CMS_Get_LOCAL_CNS_INFO errCmsGetLocalCnsInfo



//----会议模板 相关------begin--

  //cnsID 为非法值,cns 不存在
  errCmsCnsIDInvalid,
#define ERR_CMS_CNSID_INVALID errCmsCnsIDInvalid

  //模板 不存在
  errCmsConfTempUnexist,
#define ERR_CMS_CONFTEMP_UNEXIST errCmsConfTempUnexist
  //模板 别名为空
  errCmsConfTempAlairsEmpty,
#define ERR_CMS_CONFTEMP_ALIARS_EMPTY errCmsConfTempAlairsEmpty

  //模板名重复
  errCmsConfTempAlairsRepeat,
#define ERR_CMS_CONFTEMP_ALIARS_REPEAT errCmsConfTempAlairsRepeat

  //模板名重复
  errCmsConfTempE164Repeat,
#define ERR_CMS_CONFTEMP_E164_REPEAT errCmsConfTempE164Repeat

  
  //cns 别名为空
  errCmsCnsAlairsEmpty,
#define ERR_CMS_CNS_ALIARS_EMPTY errCmsCnsAlairsEmpty

  //cns 个数已达到最大
  errCmsCnsMaxNum,
#define ERR_CMS_CNS_MAX_NUM errCmsCnsMaxNum

  //cns别名重复
  errCmsCnsAliarsRepeat,
#define ERR_CMS_CNS_ALIAS_EXIST errCmsCnsAliarsRepeat

  // 
  errCmsCnsUnknow,
#define ERR_CMS_CNS_UNKNOW errCmsCnsUnknow

  errCmsCnsUneixt,
#define ERR_CMS_CNS_UNEXIST errCmsCnsUneixt 


//模板的主席不是本地cns
  errCmsTemplateChairManNotLocalCns,
#define ERR_CMS_TEMPLATE_CHAIRMAN_NOT_LOCAL_CNS errCmsTemplateChairManNotLocalCns 
//----会议模板 相关------end




//----会议  相关------begin


//会议不存在
errCmsConfUneixt,
#define ERR_CMS_CONF_UNEXIST errCmsConfUneixt


//----会议  相关------end



//用户相关
//会议不存在
errCmsOperateUserFail,
#define ERR_CMS_OPERATE_USER_FAIL errCmsOperateUserFail
  
  errCmsUiEnd,		
#define ERR_CMS_UI_END   errCmsUiEnd
		
};  
 

 
#endif
