///  All right reserved
///  
///  @file        kdvsipadapter2.h
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       kdvsipadapter2
///  @details     kdvsipadapter2 interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of kdvsipadapter2                                         */
/************************************************************************/

/**
 * @defgroup    kdvsipadapter2  
 * @brief       kdvsipadapter2   interfaces describe here what it is all about.
 * @{
 */
#ifndef __SIPADAPTER_H__
#define __SIPADAPTER_H__

#include "kdvtype.h"
#include "sipcallstdstruct.h"
#include "sipconfnonstdmsg.h"

/// sip adapter
class PROTO_API CSipAdapter
{
public:	
	/**
	* \brief            sipadapter init
	* \param[in]        ptCfg      :sipadapter config
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_app_init(TSipAdapterCfg *ptCfg);

	/**
	* \brief            sipadapter destory
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_app_destroy();

	/**
	* \brief            sipadapter get call count 
	* \return           u16
	*/
	static u16 sipadpt_get_call_count();

	/**
	* \brief            sipadapter set app callback 
	* \param[in]        ptEvent      :sipadapter call back
	*/
	static void sipadpt_set_app_callback(TSipAdapterCB *ptEvent);

	/**
	* \brief            sipadapter get callid from reg 
	* \param[in]        hsReg          :lower reg handle
	* \param[in]        pchCallid      :call id
	* \param[in]        nLen           :call id length
	*/
	static void sipadpt_regc_get_callid(s32 hsReg, s8 *pchCallid, s32 &nLen);

	/**
	* \brief            sipadapter set call handle 
	* \param[in]        haCall          :upper call handle
	* \param[in]        hsCall          :lower call handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_set_call_app_handle(s32 haCall, s32 hsCall);

	/**
	* \brief            sipadapter create new call 
	* \param[in]        haCall          :upper call handle
	* \param[in]        hsCall          :lower call handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_create_new_call(s32 haCall, s32 &hsCall);

	/**
	* \brief            sip adapter get tls situation from info
	* \param[in]        hCall                     :lower call handle
	* \param[in]        pbTls                     :is tls
	* \param[in]        pdwPeerCertificatStatus   :peer certificat status
	* \param[in]        pnCipher                  :cipher
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_get_tlssituation_frominfo(IN s32 hsCall, OUT BOOL32 *pbTls,  OUT u32 *pdwPeerCertificatStatus,  OUT s32 *pnCipher);

	/**
	* \brief            sipadapter create new reg 
	* \param[in]        haCall          :upper reg handle
	* \param[in]        hsCall          :lower reg handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_create_new_reg(s32 haReg, s32 &hsReg);

	/**
	* \brief            sipadapter send call ctrl msg 
	* \param[in]        hsCall          :lower call handle
	* \param[in]        wMsgType        :h_call_make,h_call_answer,h_call_ack,h_call_bye,h_call_reinvite,h_call_200OK,h_call_roundtripdelay
	* \param[in]        pbyBuf          :h_call_make - TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)，可以不包含CSipCapSet对象\n
	                                     h_call_answer - TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)\n
	                                     h_call_ack - TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)，可以不包含CSipCapSet对象\n
	                                     h_call_bye - u8，sizeof(u8)\n
	                                     h_call_reinvite - CSipCapSet+u8，sizeof(CSipCapSet)+sizeof(u8)\n
	                                     h_call_200OK - CSipCapSet+u8，sizeof(CSipCapSet)+sizeof(u8)\n
	                                     h_call_roundtripdelay - NULL，0
	* \param[in]        dwLen           :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_call_ctrl_msg(s32 hsCall, u16 wMsgType, const u8 *pbyBuf, u32 dwLen);

	/**
	* \brief            sipadapter send conf ctrl msg 
	* \param[in]        hsCall          :lower call handle
	* \param[in]        wMsgType        :h_sip_info,h_sip_options
	* \param[in]        pbyBuf          :TSipNonStdData+buffer,sizeof(TSipNonStdData)+sizeof(buffer)（dialog无关）,buffer,sizeof(buffer)（dialog相关）
	* \param[in]        dwLen           :buffer length
	* \param[in]        ptHandle        :若与dialog无关,则hsCall为-1;否则,ptHandle为NULL
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_conf_ctrl_reqmsg(s32 hsCall, u16 wMsgType, const u8 *pbyBuf, u32 dwLen, TSipUacHandle *ptHandle);

	/**
	* \brief            sipadapter response conf ctrl msg 
	* \param[in]        tHandle         :tHandle为非空句柄（收到请求时回调）
	* \param[in]        nStatusCode     :应答码
	* \param[in]        pbyBuf          :null
	* \param[in]        dwLen           :0
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_conf_ctrl_rspmsg(TSipUasHandle tHandle, s32 nStatusCode, const u8 *pbyBuf, u32 dwLen);

	/**
	* \brief            sipadapter send reg ctrl msg 
	* \param[in]        hsReg           :lower reg handle
	* \param[in]        wMsgType        :h_sip_registration,h_sip_unregistration,h_sip_getreginfo,h_sip_reg_nonstandard_req
	* \param[in]        pbyBuf          :h_sip_registration-TRegisterInfo+注册别名个数(s32)+buffer长度(s32)+buffer,sizeof(TRegisterInfo)+2*sizeof(s32)+sizeof(buffer)\n
	                                     h_sip_unregistration-NULL，0\n
	                                     h_sip_getreginfo,h_sip_reg_nonstandard_reg-非标包头个数(u8)+非标包头个数*TSipHead+TSIPRegNSM+buffer,sizeof(u8)+非标包头个数*sizeof(TSipHead)+sizeof(TSIPRegNSM)+sizeof(buffer)
	* \param[in]        dwLen           :buffer length
	* \param[in]        ptHandle        :若与dialog无关，则hsCall为-1;否则,ptHandle为NULL
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_reg_ctrl_reqmsg(s32 hsReg, u16 wMsgType, const u8 *pbyBuf, u16 wLen);

	/**
	* \brief            sipadapter response reg ctrl msg 
	* \param[in]        tHandle         :tHandle为非空句柄（收到请求时回调）
	* \param[in]        nStatusCode     :应答码
	* \param[in]        pbyBuf          :null
	* \param[in]        dwLen           :0
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_reg_ctrl_rspmsg(TSipUasHandle tHandle, s32 nStatusCode, const u8 *pbyBuf, u32 dwLen);


	/**
	* \brief            sipadater set nat ip address
	* \param[in]        tNatIp       :nat ip,for ipv4 or ipv6
	*/
	static void sipadpt_set_nat_ip(PFC_IPADDR tNatIp);

	/**
	* \brief            sipadpater send dtmf info
	* \param[in]        hCall             :lower call
	* \param[in]        pbyBuf            :dtmf info buffer
    * \param[in]        wLen              :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_send_dtmf_info(s32 hsCall, const u8 *pbyBuf, u16 wLen);

	/**
	* \brief            sipadapter tls Renegotiate after register successed
	* \param[in]        hsReg            :lower reg handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_register_ssl_sock_renegotiate(s32 hsReg);

	/**
	* \brief            sipadater send info without call
	* \param[in]        pbyBuf       :pbybuf from module TSipNonStdData+XML
	* \param[in]        wLen         :buffer length
	*/
	static BOOL32 sipadpt_send_info_without_call(const u8 *pbyBuf, u16 wLen);

	/**
	* \brief            sipadater get qtkey to ssl_do_handshake
	* \param[in]        phSession    :qtparam
	* \param[in]        args         :qtparam
	* \param[in]        result       :qtkey result
	*/
	static BOOL32 sipadpt_qt_get_qtkey_result(void *phSession, void* args, u32 result);

private:
	/**
	* \brief            sipadapter default congif
	*/
	static void sipadpt_default_config();
	
	/**
	* \brief            sipadapter set config
	* \param[in]        ptCfg            :sipadapter config
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32 sipadpt_set_config(TSipAdapterCfg *ptCfg);
	
};
/**
* \brief            sipadapter help
*/
PROTO_EXTERN_API void sipahelp();

/**
* \brief            sipadapter version
*/
PROTO_EXTERN_API void sipaver();

/**
* \brief            sipadapter log on
* \param[in]        nType            :log type
*/
PROTO_EXTERN_API void sipalog(s32 nType, s32 nLevel);

/**
* \brief            print packet on
* \param[in]        dwFlag            :0-off,1-on
*/
PROTO_EXTERN_API void sipsettrace(u32 dwFlag = 0);

/**
* \brief            sip stack log on
* \param[in]        nLevel            :log level
*/
PROTO_EXTERN_API void sipslog(s32 nLevel = 0);

/**
* \brief            show sip stack
*/
PROTO_EXTERN_API void showsconfig();

/**
* \brief            sip adapter log to
* \param[in]        byFilter            :telnet or cmd
*/
PROTO_EXTERN_API void sipalogto(u8 byFilter);
/**
* \brief            sip stack log to
* \param[in]        byFilter            :telnet or cmd
*/
PROTO_EXTERN_API void sipslogto(u8 byFilter);
/**
* \brief            sip stack log to
* \param[in]        nTimeout1            :T1
* \param[in]        nTimeout2            :T2
* \param[in]        nTimeout4            :T4
* \param[in]        nTimeoutTD           :TD
*/
PROTO_EXTERN_API void siptsxtimeout(s32 nTimeout1, s32 nTimeout2, s32 nTimeout4, s32 nTimeoutTD);
/**
* \brief            sip adapter show call
*/
PROTO_EXTERN_API void sipshowacall();
PROTO_EXTERN_API void sipshowtsx(BOOL32 bDetail);
/**
* \brief            sip adapter show tsx
*/
PROTO_EXTERN_API void sipshowtsx(BOOL32 bDetail);
/**
* @}
*/
#endif
