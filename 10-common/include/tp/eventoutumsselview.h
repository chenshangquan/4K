#ifndef _h_eventoutumsselview_h_
#define _h_eventoutumsselview_h_

//#include "tpeventcomm.h"
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumsselview
{
#endif

	_ev_segment( outerumsselview )
		
/***********************<<   >>********************	
 *[消息方向]	UMC	-->  UMS
 *  UMC 请求 选看
 */
_event(  ev_UMC_UMS_SelView_Req )
_body(TTPSelViewReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	CNC	-->  UMS
 *  CNC 请求 选看
 */
_event(  ev_CNC_UMS_SelView_Req )
_body(TUmsHandle, 1)
_body(TTPSelViewReq, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  UMS给umc的回应
 */
_event(  ev_UMS_UMC_SelView_Ind )
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  UMS给cnc的回应
 */
_event(  ev_UMS_CNC_SelView_Ind )
_body(TUmsHandle, 1)
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  下级 给 上级选看请求的回应
 */
_event(  ev_UMS_UMS_SelView_Ind )
_body(TUmsHandle, 1)
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  UMC
 *  通知UMC的选看状态
 */
_event(  ev_UMS_UMC_SelView_Ntfy )
_body(TTPSelViewNtfy, 1)
_ev_end

/***********************<<   >>********************	
 *[消息方向]	UMS	-->  CNC
 *  通知UMC的选看状态
 */
_event(  ev_UMS_CNC_SelView_Ntfy )
_body(TUmsHandle, 1)
_body(TTPSelViewNtfy, 1)
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumsselview)
};
#endif




#endif // _h_eventoutumsselview_h_
