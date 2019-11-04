// tvwCtrl.h: interface for the CTvwCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_)
#define AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_

#include "tvwCtrlIF.h"
#include "umssession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTvwCtrl : public CTvwCtrlIF 
{  
	friend class CUmsSession;
private:
	CTvwCtrl( CUmsSession &cUmsSession );
	CTvwCtrl( const CTvwCtrl & ){};
	 
public:
     
     /**
    * 功能:	 请求播放
    * @param [int]  tTvwInfo：请求播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    u16 PlayHduReq( const TTPHduPlayReq & tTvwInfo ) ;

     /**
    * 功能:	 停止播放
    * @param [int]  tTvwInfo：请求停止播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    u16 StopHduReq( const TTPHduPlayReq & tTvwInfo );

    /**
    * 功能:	 停止所有电视墙播放
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    u16 StopAllHduReq();
    
    /** 功能   获得电视墙方案配置
	 *  @return THduPlanData 电视墙方案信息
	 */
	virtual const THduPlanData& GetTvwPlanData() const;
   
protected:
    /**
    * 功能:	  tvw 注册 和 注销 的更新 通知（包含添加、删除 ）
    * @param [out]  cMsg 消息
    * @return  无
    * @remarks   
    */
    //void  OnRefeshTvwNotify(const CMessage& cMsg);

    /**
    * 功能:	  操作hdu的回复
    * @param [out]  cMsg	消息
    * @return  无
    * @remarks   
    */
    void  OnOperateHduRsp(const CMessage& cMsg);
    
    /**
    * 功能:	  
    * @param [out]  cMsg	消息
    * @return  无
    * @remarks   
    */
    //void OnCodeStreamNotify(const CMessage& cMsg);

    /**
    * 功能: 电视墙方案通知
    * @return  无
    * @remarks   
    */
    void OnTvwPlanNotify(const CMessage& cMsg);
    /**
    * 功能: 电视墙注册状态通知
    * @return  无
    * @remarks   
    */
    void OnTvwRegStatusNotify(const CMessage& cMsg);

    /**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();
   
	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);

    void  OnLinkBreak(const CMessage& cMsg);
private:
	CUmsSession *m_pUmsSession;
    //TplArray<TCmsTvwInfo> m_tplTvwLst;

    THduPlanData  m_tHduPlanData;
};

#endif // !defined(AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_)
