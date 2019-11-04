#ifndef _h_eventoutumsreg_h__
#define _h_eventoutumsreg_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumsreg
{
#endif

	_ev_segment( outerumsreg )

/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *CMS配置UMS的注册信息
 */
_event(  ev_umsreg_cmd )
_body(TTPSipRegistrarCfg,	1)
_ev_end


/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *UMS告知CMS配置信息
 */
_event(  ev_umsreg_notify )
_body(TTPSipRegistrarCfg,	1)
_ev_end


/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *UMS告知CMS注册成功结果
 */
_event(  ev_umsRegResult_notify )
_body(TUCSipRegResult,	1)
_ev_end


/***********************<<   >>********************	
 *[消息方向]	CMS	-->  UMS
 *设置GK注册信息
 */
_event(  ev_umsGKReg_cmd )
_body(TTPGKCfg,	1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *GK注册信息通知
 */
_event(  ev_umsGKReg_notify )
_body(TTPGKCfg,	1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CMS
 *UMS告知CMS注册失败结果
 */
_event(  ev_umsGKReg_ret )
_body(TUCSipRegResult,	1)
_ev_end

/***********************<< 获取全域内UMS和CNS的全部注册信息 >>********************** 
*[消息体]

*[消息方向]
*  cmc	  -> UMS
*/
_event( ev_umsGetRegInfo_Req )
_body( EmGetRegInfoType, 1 )
_ev_end

/***********************<< 获取全域内UMS和CNS的全部注册信息回复 >>********************** 
*[消息体]

*[消息方向]
*  UMS	  -> cmc
*/
_event( ev_umsGetRegInfo_Rsp )
_body( TTPSipRegPackInfo, 1 )
_body( EmGetRegInfoType, 1 )
_body( TTPSipRegInfo, 1 )
_ev_end

/***********************<< B2版本UMS注册信息 >>********************** 
*[消息体]

  *[消息方向]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_UmsRspEx )
	_body( TUmsRegPackEx, 1)
_ev_end

/***********************<< B2版本CNS注册信息 >>********************** 
*[消息体]

  *[消息方向]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_CnsRspEx )
	_body( TCnsRegPackEx, 1)
_ev_end

/***********************<< B2版本mt注册信息 >>********************** 
*[消息体]

  *[消息方向]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_MtRspEx )
	_body( TTPMtRegInfo, 1)
_ev_end

/***********************<< B2版本mcu注册信息 >>********************** 
*[消息体]

  *[消息方向]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_McuRspEx )
	_body( TTPMcuRegInfo, 1)
_ev_end

/***********************<< 维护工具Sip注册结果通知 >>********************** 
 *[消息方向]
 *  ums	  -> tool
 */
  _event( ev_ums_sipreg_state_nty )
  _body( BOOL32, 1 )  //Sip是否注册上
  _body( TTPSipRegistrarCfg, 1)
  _ev_end

 /***********************<< 维护工具GK注册结果通知 >>********************** 
 *[消息方向]
 *  ums	  -> tool
 */
  _event( ev_ums_gkreg_state_nty )
  _body( BOOL32, 1 )  //GK是否注册
  _body( TTPGKCfg, 1)
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumsreg)
};
#endif

#endif //_h_eventoutumsreg_h__

