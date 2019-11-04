#ifndef _h_eventoutumsmediatrans_h__
#define _h_eventoutumsmediatrans_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpoutermediatrans
{
#endif
	
	_ev_segment( tpumswithmediatrans )
		
/***********************<<  创建一个交换 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_ds_create )
	_body( u16,		1)	//Conf ID
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  删除一个交换 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_ds_remove )
	_body( u16,		1)	//Conf ID
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  添加关键帧检测  按照两个源检测>>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_iframe_bySrc )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameBySrc,	1)
   _ev_end

/***********************<<  添加关键帧检测  按照两个源检测>>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_iframe_bySrc_Ind )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameBySrc,	1)
  _ev_end

  /***********************<<  添加关键帧检测  两个监测点>>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_iframe_TwoRcvPort )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameTwoRcvPort,	1)
   _ev_end

   /***********************<<  添加关键帧检测  到目的的包必须经过源检测>>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_iframe_SndBySrc )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameSndBySrc,	1)
  _ev_end

  /***********************<<  添加关键帧检测  两个监测点>>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_iframe_TwoRcvPort_Ind )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameTwoRcvPort,	1)
   _ev_end

   /***********************<<  删除关键帧检测 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  ev_media_ds_del_iframe )
	_body( TTPTransAddr,	1)	//check port
   _ev_end


 /***********************<<  创建一个nb >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */
 _event(  ev_media_nb_create )
_body( TConfEpID,		1)
_body( TUmsRSParam,		1)
_body( TUmsNetBuf,		1)
_ev_end

   
/***********************<<  删除一个nb >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_nb_remove )
	_body( TConfEpID,		1)
	_body( TUmsNetBuf,		1)
   _ev_end

/***********************<<  删除会议的所有交换 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_clear_conf )
	_body( u16,		1)
   _ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpumswithmediatrans)
};
#endif


#endif // _h_eventoutumsmediatrans_h__
