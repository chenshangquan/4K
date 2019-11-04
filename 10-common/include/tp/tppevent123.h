#ifndef TPP_EVENT_H
#define TPP_EVENT_H
#include "eventcomm.h"
#include "tpstruct.h"
#ifndef _MakeMtEventDescription_
enum EmTPPEVENT
{
#endif 

  _ev_segment( tppevent  )

  _event(  ev_tppreg_timer )
  _ev_end

  _event(  ev_tppregister_req )
  _body( TMtTPEpParam, 1)
  _ev_end

  _event(  ev_tppregister_rsp )
  _ev_end

  _event(  ev_tppSetADecParamCmd )
  _body( TMtADecParam, 1)
  _ev_end

  _event(  ev_tppSetAEncParamCmd )
  _body( TMtAEncParam, 1)
  _ev_end

  _event(  ev_tppSetVDecParamCmd )
  _body( TMtVDecParam, 1)
  _ev_end

  _event(  ev_tppSetVEncParamCmd )
  _body( TMtVEncParam, 1)
  _ev_end

  _event(  ev_tppCodecStartCmd )
  _body( EmCodecComponent, 1 )
  _ev_end

  _event(  ev_tppCodecStopCmd )
  _body( EmCodecComponent, 1 )
  _ev_end

#ifndef _MakeMtEventDescription_
   _ev_segment_end( tppevent )
};
#endif
#endif //TPP_EVENT_H