#ifndef _h_cnseventcomm_h__
#define _h_cnseventcomm_h__

#include "tpeventcomm.h"

define_event_count( tpcnswithmt, 1500 );
define_event_count( tpcnswithcms, 110 ); 

define_event_begin( tpeventcommon, tpcnswithmt );
define_event_begin( tpcnswithmt, tpcnswithcms );

const u16 last_outer_event_value = begin_tpcnswithcms + event_count(tpcnswithcms);


//cns内部消息段划分
define_event_count( innercns, 100 );
define_event_begin( tpsys, innercns );
const u16 last_inner_event_value = begin_innercns +  event_count(innercns);


//cns消息定义
define_event_count( outercnsmp, 50 );
define_event_count( outercnssys, 55 );
define_event_count( outercnssipreg, 20 );
define_event_count( outercnssipcall, 50 );
define_event_count( outercnssipconf, 75 );
define_event_count( outercnssipdual, 45 );
define_event_count( outercnsinside, 60 );
define_event_count( outercnsprotocol, 60 );
define_event_count( outercnsh323conf, 50 );
define_event_count( outercnswithcnmp, 60 );
define_event_count( outercnsdevice, 70 );
define_event_count( outercnsmediatrans, 50 );
define_event_count( outercnsextend, 100 );
define_event_count( outercnscamera, 70);
//Add by tanxiaodnog 2012 -11-20.
define_event_count( outercnstool, 80 );
//End to add.
define_event_count( outercncode, 120 );
define_event_count( outercnds, 60 );
define_event_count( outercnscentre, 120);
define_event_count( outercnspancamera, 30 );
define_event_count( outercnshduextend, 100);
define_event_count( outercnremotemp, 100);

const u16 begin_outercnsmp = begin_tpcnswithmt;
define_event_begin( outercnsmp, outercnssys );
define_event_begin( outercnssys, outercnssipreg );
define_event_begin( outercnssipreg,outercnssipcall );
define_event_begin( outercnssipcall,outercnssipconf );
define_event_begin( outercnssipconf,outercnssipdual );
define_event_begin( outercnssipdual,outercnsinside );
define_event_begin( outercnsinside,outercnsprotocol );
define_event_begin( outercnsprotocol,outercnsh323conf );
define_event_begin( outercnsh323conf,outercnswithcnmp );
define_event_begin( outercnswithcnmp,outercnsdevice );
define_event_begin( outercnsdevice,outercnsmediatrans );
define_event_begin( outercnsmediatrans,outercnsextend );
define_event_begin( outercnsextend,outercnscamera );
//Add by tanxiaodong 2012-11-20.
define_event_begin( outercnscamera,outercnstool );
//End to add.
define_event_begin(outercnstool, outercncode);
define_event_begin(outercncode, outercnds);
define_event_begin(outercnds, outercnscentre);
define_event_begin(outercnscentre, outercnspancamera);
define_event_begin(outercnspancamera, outercnshduextend);
define_event_begin(outercnshduextend, outercnremotemp);










#endif // _h_cnseventcomm_h__
