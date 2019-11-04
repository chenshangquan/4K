///  All right reserved
///  
///  @file        sipconfnonstdmsg.h
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       sipconfnonstdmsg
///  @details     sipconfnonstdmsg interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of sipconfnonstdmsg                                        */
/************************************************************************/

/**
 * @defgroup    sipconfnonstdmsg
 * @brief       sipconfnonstdmsg interfaces describe here what it is all about.
 * @{
 */
#ifndef _SIPCONFNONSTDMSG_H
#define _SIPCONFNONSTDMSG_H

/// 会议控制消息
enum EmSipConfCtrlMsgType
{
	h_conf_invalidInterface		= 0, ///< invalid Interface
	h_conf_nonstandard			= 1, ///< sip会控xml消息透传
	h_chan_flowControl	        = 2, ///< flow Control
	h_chan_fastupdate           = 3  ///< fast update
};

/// 信道控制消息
enum EmSipChanCtrlMsgType 
{
	h_chan_invalidInterface = 0,    ///< invalid Interface
	h_chan_videofastupdate,         ///< video fast update
	h_chan_flowControlCmd,          ///< flow Control Cmd
	h_chan_flowControlInd,          ///< flow Control Ind
	h_chan_fastupdatewithoutid,     ///< fast update without id
};

/// FECC控制消息
enum EmFeccCtrlMsgType
{
	h_fecc_bind = 0,               ///< fecc bind
	h_fecc_send_msg,               ///< fecc send msg
	h_fecc_open_chan,              ///< fecc open channel
	h_fecc_set_streamid,           ///< fecc set stream id
	h_fecc_close_chan,             ///< fecc close channel
	h_fecc_keep_alive,             ///< fecc keep alive
};

/**
* @}
*/
#endif 


