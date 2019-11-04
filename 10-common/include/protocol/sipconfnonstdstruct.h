///  All right reserved
///  
///  @file        sipconfnonstdstruct.h 
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       sipconfnonstdstruct
///  @details     sipconfnonstdstruct interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of sipconfnonstdstruct                                        */
/************************************************************************/

/**
 * @defgroup    sipconfnonstdstruct
 * @brief       sipconfnonstdstruct interfaces describe here what it is all about.
 * @{
 */
#ifndef _SIPCONFNONSTDSTRUCT_H
#define _SIPCONFNONSTDSTRUCT_H

#include "kdvsipcommon.h"
#include "sipcallstdstruct.h"
#include "sipconfnonstdmsg.h"

#define SIP_REG_NONSTANDARD "KDRegNSM" ///< sip reg nonstandard

/// sip flow ctrl struct
typedef struct tagSipFlowCtrl
{
	s32   m_nChannelId;      ///< channel  id
	u16   m_wBitRate;        ///< bitrate
	/**
    * \brief            tagSipFlowCtrl Constructor
    * \return           void.
    */
	tagSipFlowCtrl()
	{
		m_nChannelId = -1;
		m_wBitRate = 0;
	}
}TSipFlowCtrl,*PTSipFlowCtrl;

/**
* @}
*/
#endif 
