/*=======================================================================
模块名      : TPad lib接口
文件名      : tpadsessionif.h
相关文件    : 
文件实现功能: tpadlib控制接口
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013.3.6    1.0         肖楚然        创建
=======================================================================*/
#if !defined _TPADSESSIONIF_H_
#define _TPADSESSIONIF_H_

#include "kdvdispevent.h"
#include "tpstruct.h"

class CTPadSessionIF : public CKdvDispEvent 
{
public:	
    /*功    能  初始化lib库环境
	参    数  dwAppID： 需要的appID
	返 回 值   
	说    明   使用其他接口之前必须调用该接口*/ 
	virtual void InitEnv( u32 dwAppID ) = 0;
	
	/** 功能  连接到CNS 
	 *  @param[in] dwIP	被连接CNS的IP地址
	 *  @param[in] dwPort  被连接CNS的端口
	 *  @param[in] strUser	用户名
	 *  @param[in] strPwd	密码
     *  @param[in] achVersion TPad版本号
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 
	 */
	virtual u16 ConnectCns(u32 dwIP, u32 dwPort,
		const CString& strUser, const CString& strPwd, 
        s8* achVersion, BOOL32 bConnect = TRUE) = 0;

	/** 功能  断开CNS连接 
	 *  @return 成功返回0,失败返回非0错误码
	 *  @remarks 在没有连接到CNS时调用此方法，不起任何作用
	 */
	virtual u16 DisconnectCns() = 0;

	/** 功能  查询是否已连接CNS 
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
	virtual BOOL IsConnectedCns() = 0;

	 /** 功能  获取本地ip
	 *  @param[in] 
	 *  @return  本地ip 
	 *  @remarks 
	 */
    virtual u32 GetLocalHostIP() = 0;

	/** 
	* 功能  开启/停止双流码流
	* @return  BOOL  TRUE:开启， FALSE:停止
	* @remarks 
	*/
    virtual u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVideoTransAddr , const TTPCnMediaTransPort  &tAudioTransAddr ) const = 0;

    virtual u16 StopDualCodeStream() const = 0;

    virtual u16 ReqKeyFrame( BOOL32 bForce ) const = 0;

	virtual TTPCnMediaTransPort GetVedioTransAddr() const = 0;
	
    virtual TTPCnMediaTransPort GetAudioTransAddr() const = 0;

	/** 功能  获取CNS会议状态
	*  @return TTPCnsConfStatus 会议状态
	*  @remarks 
	*/
	//virtual TTPCnsConfStatus& GetCnsConfStatus() const =0;
	virtual TTPCnsConfStatus GetCnsConfStatus() const = 0;


    /** 功能  判断是否可进行链接(cnc、中控均以连上Tpad)
	 *  @return  TRUE 已连接，FALSE	没连接
	 *  @remarks 
	 */
    virtual BOOL IsReadyLogin( vector<TNodeInfo>&vctNodeList ) = 0;

	
    /** 功能  获取登陆ip
	 *  @param[in] 
	 *  @return  登陆ip
	 *  @remarks 
	 */
	virtual u32 GetLoginIp() = 0;
        
	//文件共享
	virtual u16 FileDualCmd( BOOL bStart ) = 0;
	virtual u16 FileDualRcvAddrCmd( EmTPAddDualRcvResult emAddDualRcvRes, TTPCnMediaTransPort &tVideoTransAddr, u16 nVideoNode ) = 0;

	virtual TTPMtVideoEncodeParameter& GetFileDualEncParam() = 0;  

	virtual TEncryptKey& GetFileDualkey() = 0;

	virtual u8 GetFileDualPayload() = 0;

	virtual TTPCnMediaTransPort& GetFileDualTransPort() = 0;

    virtual void TPadHomeKeyNty() = 0;

	virtual void OpenCenterCtrl() = 0;

    virtual void WBConfStartNty( bool bIsSelfStart, bool bIsSuccess  ) = 0;
    
    //virtual void NewConfCallRsp( BOOL bIsJoinWBConf ) = 0;
    
    virtual void WBConfStateNty( bool bIsInWBConf ) = 0;
    
    virtual void SetDataServerInfoCmd( u32 dwIp ) = 0;
    
	virtual void T300UpdateInd( BOOL bIsUpT300 ) = 0;
};

#endif