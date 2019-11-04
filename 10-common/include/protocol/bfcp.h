//////////////////////////////////////////////////////////////////////////
///  COPYRIGHT NOTICE
///  Copyright (C) 2018, ODDMETA
///  All right reserved
///  
///  @file        bfcp.h
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       binary floor control protocol related to dual functions 
///  @details     Easy BFCP ...
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of bfcp                                          */
/************************************************************************/

/**
 * @defgroup    bfcp
 * @brief       bfcp interfaces describe here what it is all about.
 * @{
 */

#ifndef _BFCP_H
#define _BFCP_H
#include "bfcp_messages.h"

/**
* \brief            Initialize bfcp participant
* \param[in]        nTransport  :transport protocol,such as tcp/udp/tls
* \param[in]        dwConfId    :conference id
* \param[in]        wUserId     :the unique user id in a conference
* \param[in]        pCapset     :pointer to contact context
* \param[in]        ptNonstd    :non-std message
* \param[in]        ptAddress   :server address which participant connect to
* \param[in]        fpNotifier  :call back function
* \param[in]        ptBfcpTlsCfg  :the related certificates when use tls,default null
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_init_client(s32 nTransport, u32 dwConfId, u16 wUserId, void *pCapset, bfcp_nonstd *ptNonstd, TRequestAddress *ptAddress, CB_BFCPNOTIFY fpNotifier, TBfcpTlsCfg *ptBfcpTlsCfg =NULL);

/**
* \brief            Initialize bfcp server
* \param[in]        bAutoAnswer  :auto response participant's request
* \param[in]        wMaxConf     :the max conferences in a server
* \param[in]        wPortServer  :port which server transport bind
* \param[in]        ptNonstd     :non-std message
* \param[in]        ptBfcpTlsCfg :the related certificates when use tls
* \param[in]        fpNotifier   :call back function     
* \param[in]        bIsUseTcp    :whether use tcp or tls,default false,if true tcp socket will be created,if use tls the ptBfcpTlsCfg mustn't be null
* \param[in]        bIsIpv6      :whether use ipv6 from peer request,default TRUE
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_init_server(BOOL32 bAutoAnswer, u16 wMaxConf, u16 wPortServer, bfcp_nonstd *ptNonstd, TBfcpTlsCfg *ptBfcpTlsCfg, CB_BFCPNOTIFY fpNotifier,BOOL32 bIsUseTcp = FALSE,BOOL32 bIsIpv6 = TRUE);

/**
* \brief            destory bfcp participant
* \param[in]        pCap     :the destoryed participant's uid 
* \param[in]        bIsDestoryThread     :whether destory participant's thread,default false
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_destroy_client(void *pCap, BOOL32 bIsDestoryThread = FALSE);

/**
* \brief            destory bfcp server
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_destroy_server();

/**
* \brief            bfcp participant update server's port
* \param[in]        pCap     :the participant's uid 
* \param[in]        dwPort   :the remote port
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_client_update_remote_port(void *pCap, u32 dwPort);

/**
* \brief            bfcp participant send a request
* \param[in]        nPrimitive     :send message type\n
                    nPrimitive=1¡ú FloorRequest\n
					nPrimitive=2¡ú FloorRelease\n	
                    nPrimitive=11¡úHello\n
					nPrimitive=12¡úHelloAck\n	
					nPrimitive=16¡úFloorStatusAck
* \param[in]        ptAttribute    :a common header followed by a set of attributes
* \param[in]        ptNonstd       :non-std message in the request
* \param[in]        pCap           :the participant's uid 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_client_send_message(s32 nPrimitive, bfcp_attribute_info *ptAttribute, bfcp_nonstd *ptNonstd, void *pCap);

/**
* \brief            bfcp server send a request
* \param[in]        nRcvPrimitive     :recv message type\n
                    nRcvPrimitive=1¡ú FloorRequest\n
                    nRcvPrimitive=2¡ú FloorRelease\n	
                    nRcvPrimitive=11¡úHello\n
                    nRcvPrimitive=12¡úHelloAck\n	
                    nRcvPrimitive=16¡úFloorStatusAck
* \param[in]        nPrimitive        :send message type\n
                    nPrimitive=4¡ú FloorRequestStatus\n
                    nPrimitive=8¡ú FloorStatus\n
                    nPrimitive=11¡úHello\n
					nPrimitive=12¡úHelloAck\n
					nPrimitive=14¡ú FloorRequestStatusAck\n
					nPrimitive=16¡úFloorStatusAck
* \param[in]        ptEntity       :a client or a floor control server
* \param[in]        ptAttribute    :a common header followed by a set of attributes
* \param[in]        ptNonstd       :non-std message in the request
* \param[in]        ptAddress      :the participant's address  
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_send_message(s32 nRcvPrimitive, s32 nPrimitive, bfcp_entity *ptEntity, bfcp_attribute_info *ptAttribute, bfcp_nonstd *ptNonstd, TBfcpSock_Addr *ptAddress);

/**
* \brief            bfcp participant add a floor
* \param[in]        wFloorId     :the floor id
* \param[in]        pCap         :the participant's uid 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_client_add_floor(u16 wFloorId, void *pCap);

/**
* \brief            bfcp participant delete a floor
* \param[in]        wFloorId     :the floor id
* \param[in]        pCap         :the participant's uid 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_client_delete_floor(u16 wFloorId, void *pCap);

/**
* \brief            bfcp server add a conference
* \param[in]        dwConfId     :the conference id
* \param[in]        wMaxFlrsNum  :the max floor num in a conference
* \param[in]        wMaxNumFlrReq  :the max requests for each floors 
* \param[in]        nAutoPolicy  :default 0 
* \param[in]        dwChairWait  :default 0 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_add_conference(u32 dwConfId, u16 wMaxFlrsNum, u16 wMaxNumFlrReq, s32 nAutoPolicy, u32 dwChairWait);

/**
* \brief            bfcp server delete a conference
* \param[in]        dwConfId     :the conference id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_delete_conference(u32 dwConfId);

/**
* \brief            bfcp server add a floor
* \param[in]        dwConfId  :the conference id
* \param[in]        wFloorId  :the floor id
* \param[in]        wChairId  :default 0 
* \param[in]        nLimitGrantedFloor  :default 0 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_add_floor(u32 dwConfId, u16 wFloorId, u16 wChairId, s32 nLimitGrantedFloor);

/**
* \brief            bfcp server delete a floor
* \param[in]        dwConfId  :the conference id
* \param[in]        wFloorId  :the floor id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_delete_floor(u32 dwConfId, u16 wFloorId);

/**
* \brief            bfcp server add a user
* \param[in]        dwConfId  :the conference id
* \param[in]        wUserId  :the user id
* \param[in]        pchUri  :the user uri 
* \param[in]        pchDisplayName  :the user display name 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_add_user(u32 dwConfId, u16 wUserId, s8 *pchUri, s8 *pchDisplayName);

/**
* \brief            bfcp server delete a user
* \param[in]        dwConfId  :the conference id
* \param[in]        wUserId  :the user id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_delete_user(u32 dwConfId, u16 wUserId);

/**
* \brief            bfcp server add a chair
* \param[in]        dwConfId  :the conference id
* \param[in]        wFloorId  :the floor id
* \param[in]        wChairId  :the chair id 
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_add_chair(u32 dwConfId, u16 wFloorId, u16 wChairId);

/**
* \brief            bfcp server delete a chair
* \param[in]        dwConfId  :the conference id
* \param[in]        wFloorId  :the floor id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_delete_chair(u32 dwConfId, u16 wFloorId);

/**
* \brief            bfcp server add a client information
* \param[in]        pAppPoint  :the participant's uid 
* \param[in]        ptAddress  :the participant's address,include ipv4 and ipv6
* \param[in]        dwConfId   :the conference id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_add_client_information(void *pAppPoint, TBfcpSock_Addr *ptAddress, u32 dwConfId, u32 dwUserId = BFCP_INVALID_USERID);

/**
* \brief            bfcp server update a client information
* \param[in]        pAppPoint  :the participant's uid 
* \param[in]        ptAddress  :the participant's address,include ipv4 and ipv6
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_update_client_information(void *pAppPoint, TBfcpSock_Addr *ptAddress);

/**
* \brief            bfcp server delete a client information
* \param[in]        pAppPoint  :the participant's uid 
* \param[in]        dwConfId   :the conference id
* \return           BOOL32, TRUE/FALSE
*/
PROTO_API BOOL32 bfcp_server_delete_client_information(void *pAppPoint, u32 dwConfId, u32 dwUserId = BFCP_INVALID_USERID);

PROTO_API BOOL32 bfcp_server_change_max_conference_number(u16 wNumber);
PROTO_API BOOL32 bfcp_server_change_granted_floor_number(u32 dwConfId, u16 wFloorId, u16 wLimitGrantedFloor);
PROTO_API BOOL32 bfcp_server_change_user_req_floors_number(u16 wMaxNumFlrReq);
PROTO_API BOOL32 bfcp_chair_change_policy(u32 dwConfId, s32 nAutoPolicy, u32 dwChairWait);

/**
* \brief            reg bfcp api for osp
* \return           void.
*/
PROTO_API void RegBfcpFunLinux();

PROTO_API void SetBfcpLogCB(ALL_LOG_CALlBACK  fpBfcpLogCB);

/**
* \brief            Print or Debug Function
* \return           void.
*/
PROTO_EXTERN_API void bfcphelp();
PROTO_EXTERN_API void bfcplogto(u8 byFilter);
PROTO_EXTERN_API void bfcplog(s32 nLevel);
PROTO_EXTERN_API void bfcpver();
PROTO_EXTERN_API void bfcpshowclt();
PROTO_EXTERN_API void bfcpshowsrv();

/**
* @}
*/

#endif
