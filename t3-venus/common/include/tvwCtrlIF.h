// tvwCtrlIF.h: interface for the CTvwCtrlIF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVWCTRLIF_H__6765F8CF_B128_456F_8136_7FEE61CC6882__INCLUDED_)
#define AFX_TVWCTRLIF_H__6765F8CF_B128_456F_8136_7FEE61CC6882__INCLUDED_
#include "kdvdispevent.h"
#include "cmsstruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTvwCtrlIF : public  CKdvDispEvent  
{
public:
     /**
    * 功能:	 请求播放
    * @param [int]  tTvwInfo：请求播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    virtual u16 PlayHduReq( const TTPHduPlayReq & tTvwInfo ) = 0 ;


    /**
    * 功能:	 停止播放
    * @param [int]  tTvwInfo：请求停止播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    virtual u16 StopHduReq( const TTPHduPlayReq & tTvwInfo ) = 0 ;

    /**
    * 功能:	 停止所有电视墙播放
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
    virtual u16 StopAllHduReq() = 0;

    /**
    * 功能:	 获取电视墙配置数据
    * @return   THduPlanData 电视墙所有数据
    * @remarks  
    */
    virtual const THduPlanData& GetTvwPlanData() const = 0;

};

#endif // !defined(AFX_TVWCTRLIF_H__6765F8CF_B128_456F_8136_7FEE61CC6882__INCLUDED_)
