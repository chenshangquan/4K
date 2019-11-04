#ifndef _h_mooneventcomm_h__
#define _h_mooneventcomm_h__

#include "tpeventcomm.h"

define_event_count( tpmoonwithmt, 1100 );
define_event_count( tpmoonwithcms, 110 ); 

define_event_begin( tpeventcommon, tpmoonwithmt );
define_event_begin( tpmoonwithmt, tpmoonwithcms );

const u16 last_outer_event_value = begin_tpmoonwithcms + event_count(tpmoonwithcms);


//moon内部消息段划分
define_event_count( innermoon, 100 );
define_event_begin( tpsys, innermoon );
const u16 last_inner_event_value = begin_innermoon +  event_count(innermoon);

define_event_count( outermoonsys, 100 );
define_event_count( outermooncamera, 100 );
define_event_count( outermoonextend, 150 );

const u16 begin_outermoonsys = begin_tpmoonwithmt;
define_event_begin( outermoonsys, outermooncamera );
define_event_begin( outermooncamera, outermoonextend );







#endif // _h_cnseventcomm_h__
