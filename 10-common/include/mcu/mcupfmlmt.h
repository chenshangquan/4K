/*****************************************************************************
   模块名      : mcu
   文件名      : mcupfmlmt.h
   相关文件    : 
   文件实现功能: MCU 业务及MCS 使用，用于MCU能力限制通用的实现
   作者        : 张宝卿 顾振华 
   版本        : V4.0  Copyright(C) 2001-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
   使用说明：
        MCS包含本头文件前，请预定义宏 MCS_PFMLMT.请包含且只包含头本文件一次
         
   修改记录:
   日  期      版本        修改人      修改内容
   2007/01/29  4.0         顾振华      创建本文件
   2008/08/06  4.5         顾振华      H.264 HD 修改
******************************************************************************/

#ifndef __MCUPFMLMT_H_
#define __MCUPFMLMT_H_

#include "mcustruct.h"
#include "mcuerrcode.h"

TMcu8kbPfmFilter CMcuPfmLmt::m_tFilter;

// 内部接口
// 码率大于 x
#define IS_BITRATE_GR(tConf, br)  ( tConf.GetBitRate() > (br)  )
// 码率大于等于 x
#define IS_BITRATE_GE(tConf, br)  ( tConf.GetBitRate() >= (br) )
// 码率小于 x
#define IS_BITRATE_LO(tConf, br)  ( tConf.GetBitRate() < (br)  )
// 码率小于等于 x
#define IS_BITRATE_LE(tConf, br)  ( tConf.GetBitRate() <= (br) )

// 是否H264会议，如果双格式会议，一定要把H.264配置成主格式
inline BOOL32 IsConfH264(const TConfInfo &tConfInfo)
{
    return ( MEDIA_TYPE_H264 == tConfInfo.GetMainVideoMediaType() );
}

// 是否G729会议
inline BOOL32 IsConfG729(const TConfInfo &tConfInfo)
{
    return ( MEDIA_TYPE_G729 == tConfInfo.GetMainAudioMediaType() );
}

// 会议是否正在语音激励
inline BOOL32 IsConfVacing(const TConfInfo &tConfInfo)
{
    return ( tConfInfo.m_tStatus.IsVACing() );
}

// 会议是否正在混音(包括定制、智能、VAC所有情况)
inline BOOL32 IsConfMixing(const TConfInfo &tConfInfo)
{
    return ( tConfInfo.m_tStatus.IsMixing() || tConfInfo.m_tStatus.IsVACing() );
}

// 会议是否正在混音(包括定制和智能)
inline BOOL32 IsConfMixingNoVac(const TConfInfo &tConfInfo)
{
    return ( tConfInfo.m_tStatus.IsMixing() );
}

// 会议是否正在任何类型的适配
inline BOOL32 IsConfBasing(const TConfInfo &tConfInfo)
{
    return tConfInfo.m_tStatus.IsConfAdapting();
}

// 会议是否在画面合成
inline BOOL32 IsConfVmping(const TConfInfo &tConfInfo)
{
    return ( CONF_VMPMODE_NONE != tConfInfo.m_tStatus.GetVMPMode() );
}


BOOL32 g_bPrintPfmMsg = false;
void pfmlog(s8 * fmt, ... )
{
    s8  achBuf[255];
    va_list argptr;	
    if( g_bPrintPfmMsg )
    {
        s32 nPrefix = sprintf( achBuf, "[PFMLimit]:" );
        va_start( argptr, fmt );    
        vsprintf( achBuf + nPrefix, fmt, argptr );   
        OspPrintf(TRUE, FALSE, achBuf); 
        va_end(argptr); 
    }    
}

/*=============================================================================
    函 数 名： GetMaxVmpStyle
    功    能： 判断当前VMP最多支持的画面合成路数
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo         [in]  会议基本信息
               u8 byMtNum                   [in]  会议终端数量
               u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
               u16 &wError                  [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/29  4.0			顾振华                  创建
=============================================================================*/
u8 CMcuPfmLmt::GetMaxOprVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError )
{
	// xliang [2/25/2009] 目前该接口只在8000b情况下，mcs会调
    wError = 0;
    u8 byVmpStyle = VMP_STYLE_NONE;

#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return VMP_STYLE_TWENTY/*VMP_STYLE_SIXTEEN*/;   // 依据当前的其他业务判断逻辑
#else
    if (!m_tFilter.IsEnable())
    {
        // guzh [2/12/2007] FIXME 依据当前的其他业务判断逻辑，会出现错误
        return VMP_STYLE_TWENTY/*VMP_STYLE_SIXTEEN*/;   
    }
        
    BOOL32 bConfVideoH264  = IsConfH264(tConfInfo);     //会议视频格式H264
    BOOL32 bConfAudioG729  = IsConfG729(tConfInfo);     //会议音频格式G729

    // VMP和VAC互斥。已经在VAC则不支持Vmp
    if ( IsConfVacing(tConfInfo) )
    {
        wError = ERR_MCU_VACNOVMP;
        return VMP_STYLE_NONE;
    }

    // 没有其他模式的混音，依据当前的其他业务判断逻辑
    if ( !IsConfMixing(tConfInfo) )
    {
        // 264-Auto支持1、2、3、4、9、16，其余格式只支持1、2、3、4
		if( !bConfVideoH264 && IS_BITRATE_GR(tConfInfo, 2048) )
		{
			pfmlog( "[GetMaxOprVmpStyle] MP4 conf's BR should not be over 2048 !\n" );
			wError = ERR_MCU_VMPNOSUPPORT;
			return VMP_STYLE_NONE;
		}
		else if ( bConfVideoH264 && IS_BITRATE_GR(tConfInfo, 4096) )
		{
			pfmlog( "[GetMaxOprVmpStyle] H264 conf's BR should not be over 4096 !\n" );
			wError = ERR_MCU_VMPNOSUPPORT;
			return VMP_STYLE_NONE;
		}
        else 
		{
            // [zw] [09/08/2008] 如果不是VMP_STYLE_NONE就不直接return，留给后面return。这样后面就可以做业务扩展的后续处理了。
            byVmpStyle = ( bConfVideoH264 ? ( !tConfInfo.IsVmpAutoAdapt() ? VMP_STYLE_NONE : VMP_STYLE_SIXTEEN) : VMP_STYLE_FOUR );
		}
    }

    // 在混音       
    if ( bConfVideoH264 )
    {
        if ( !tConfInfo.IsVmpAutoAdapt() )
        {
            wError = ERR_MCU_VMPNOSUPPORT;
            return VMP_STYLE_NONE;
        }

		// 4M以上
		if ( IS_BITRATE_GR(tConfInfo, 4096) )
        {
            wError = ERR_MCU_VMPNOSUPPORT;
            pfmlog( "[GetMaxOprVmpStyle] H264 conf's BR should not be over 4096 !\n" );
            return  VMP_STYLE_NONE;
        }
        
        // H264-G729
        if ( bConfAudioG729 )
        {
            if ( byMixingMtNum > m_tFilter.byMaxNumMixMultiG729 ) 
            {
                wError = ERR_MCU_VMPNOSUPPORTONMIX;
                pfmlog("[GetMaxOprVmpStyle] Mix mem is over.%d, support no VMP in H264-G729!\n", m_tFilter.byMaxNumMixMultiG729 );
                return VMP_STYLE_NONE;
            }
            else 
            {
                // 768k 到 4M
                if ( IS_BITRATE_GR(tConfInfo, 768) )
                {
				    wError = ERR_MCU_VMPNOSUPPORTONMIX;
                    pfmlog( "[GetMaxOprVmpStyle] Mix member is Not zero, support no VMP in H264-G729 at Br. %d!\n", 768 );
                    return VMP_STYLE_NONE;
                }
                // 768K 以下
                else
                {
                    byVmpStyle = VMP_STYLE_NINE;
                }
            }
        }
        // H264-MP3
        else
        {
            if ( byMixingMtNum > m_tFilter.byMaxNumMixMultiMp3 ) 
            {
                wError = ERR_MCU_VMPNOSUPPORTONMIX;
                pfmlog( "[GetMaxOprVmpStyle] Mix mem is over.%d, support no VMP in H264-MP3!\n", m_tFilter.byMaxNumMixMultiMp3 );
                return VMP_STYLE_NONE;
            }
            else
            {
                // 1M 到 4M
                if ( IS_BITRATE_GR(tConfInfo, 1024) )
                {
                    byVmpStyle = VMP_STYLE_FOUR;
                }
                // 1M 以下
                else
                {
                    byVmpStyle = VMP_STYLE_NINE;
                }
            }
        }
    }
    else // MPEG4
    {
		if ( IS_BITRATE_GR(tConfInfo, 2048) )
        {
            wError = ERR_MCU_VMPNOSUPPORT;
            pfmlog( "[GetMaxOprVmpStyle] MPEG4 conf's BR should not be over 2048 !\n" );
            return  VMP_STYLE_NONE;
        }

        // MPEG4-G729
        if ( bConfAudioG729 )
        {
            if ( byMixingMtNum > m_tFilter.byMaxNumMixMultiG729 ) 
            {
                wError = ERR_MCU_VMPNOSUPPORTONMIX;
                pfmlog( "[GetMaxOprVmpStyle] Mix mem is over.%d, support no VMP in MP4-G729!\n", m_tFilter.byMaxNumMixMultiG729 );
                return VMP_STYLE_NONE;
            }
            else
            {
				// 768k 到 2M
                if ( IS_BITRATE_GR(tConfInfo, 768) )
                {
				    wError = ERR_MCU_VMPNOSUPPORTONMIX;
                    pfmlog( "[GetMaxOprVmpStyle] Mix member is Not zero, support no VMP in H264-G729 at Br. %d!\n", 768 );
                    return VMP_STYLE_NONE;
                }
                // 768K 以下
                else
                {
                    byVmpStyle = VMP_STYLE_FOUR;
                }
            }
        }
        // MPEG4-MP3
        else
        {
            if ( byMixingMtNum > m_tFilter.byMaxNumMixMultiMp3 ) 
            {
                wError = ERR_MCU_VMPNOSUPPORTONMIX;
                pfmlog("[GetMaxOprVmpStyle] Mix mem is over.%d, support no VMP in MP4-MP3!\n", m_tFilter.byMaxNumMixMultiMp3 );
                return VMP_STYLE_NONE;
            }
            else
            {
                byVmpStyle = VMP_STYLE_FOUR;
            }
        }
    }

    // [zw] [09/08/2008] 业务拓展后续处理：8000B高清会议最高支持四画面
#ifdef _MINIMCU_
    if ( IsConfFormatOverCif(tConfInfo) )
    {
        if ( (VMP_STYLE_DYNAMIC  != byVmpStyle)       
          && (VMP_STYLE_SPECFOUR != byVmpStyle) 
          && (VMP_STYLE_NONE     != byVmpStyle) 
          && (VMP_STYLE_ONE      != byVmpStyle) 
          && (VMP_STYLE_VTWO     != byVmpStyle) 
          && (VMP_STYLE_HTWO     != byVmpStyle)
          && (VMP_STYLE_THREE    != byVmpStyle)
          && (VMP_STYLE_FOUR     != byVmpStyle) )
        {
            byVmpStyle = VMP_STYLE_FOUR;
        }
    }
#endif

    return byVmpStyle;

#endif
}

/*=============================================================================
    函 数 名： GetMaxDynVmpStyle
    功    能： 获取当前能支持的动态合成风格。不支持MCS访问。
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo         [in]  会议基本信息
               u8 byMtNum                   [in]  会议终端数量
               u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
               u16 &wError                  [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/31  4.0			顾振华                  创建
=============================================================================*/    
u8 CMcuPfmLmt::GetMaxDynVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError )
{
#if (!defined(_MINIMCU_)) 
    return VMP_STYLE_SIXTEEN;
#else

    u8 byExpVmpStyleByMt;   // 根据MT数量期望的理想风格
    u8 byResultStyle = VMP_STYLE_NONE;
    BOOL32 bConfH264 = IsConfH264(tConfInfo);

    if (bConfH264 && !tConfInfo.IsVmpAutoAdapt())
    {
        wError = ERR_MCU_VMPNOSUPPORT;
        return VMP_STYLE_NONE;
    }

    if (byMtNum <= 2)
    {
        byExpVmpStyleByMt = VMP_STYLE_VTWO;
    }
    else if (byMtNum <= 3)
    {
        byExpVmpStyleByMt = VMP_STYLE_THREE;
    }
    else if (byMtNum <= 4)
    {
        byExpVmpStyleByMt = VMP_STYLE_FOUR;
    }
    else if (byMtNum <= 9)
    {
        byExpVmpStyleByMt = (bConfH264 ? VMP_STYLE_NINE : VMP_STYLE_FOUR);        
    }
    else
    {
        byExpVmpStyleByMt = (bConfH264 ? VMP_STYLE_SIXTEEN : VMP_STYLE_FOUR);        
    }
    
    if (!m_tFilter.IsEnable())
    {
        byResultStyle = byExpVmpStyleByMt;
    }
    else
    {
        // 当前剩余能力的风格
        u8 byCurCapStyle = GetMaxOprVmpStyle(tConfInfo, byMtNum, byMixingMtNum, wError);
        switch ( byCurCapStyle )
        {
        case VMP_STYLE_NONE:
            byResultStyle = VMP_STYLE_NONE;
            break;
        case VMP_STYLE_FOUR:
            switch (byExpVmpStyleByMt)
            {
            case VMP_STYLE_NINE:
            case VMP_STYLE_SIXTEEN:
                byResultStyle = VMP_STYLE_FOUR;
                break;
            default:
                byResultStyle = byExpVmpStyleByMt;
            }
            break;
        case VMP_STYLE_NINE:
            switch (byExpVmpStyleByMt)
            {
            case VMP_STYLE_SIXTEEN:
                byResultStyle = VMP_STYLE_NINE;
                break;
            default:
                byResultStyle = byExpVmpStyleByMt;
            }
			break;
        case VMP_STYLE_SIXTEEN:
        default:
            byResultStyle = byExpVmpStyleByMt;
            break;
        }
    }
    return byResultStyle;
#endif
}

/*=============================================================================
函 数 名： IsVmpOprSupported
功    能： 判断当前的VMP操作能否接受
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo         [in]  会议基本信息
               TVMPParam &tNewVmpParam      [in]  新的VMP操作将达到的Param
               u8 byMtNum                   [in]  会议终端数量
               u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
               u16 &wError                  [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/25  4.0			张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsVmpOprSupported( const TConfInfo &tConfInfo, u8 byNewStyle, u8 byMtNum, u8 byMixingMtNum, u16 &wError )
{
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return TRUE;
#else
    if (!m_tFilter.IsEnable())
        return TRUE;

    u8 byCapVmpStyle = GetMaxOprVmpStyle( tConfInfo, byMixingMtNum, byMixingMtNum, wError );

    // 其他
    BOOL32 bSupportVMPOpr = TRUE;

    // 支持的能力
    switch( byCapVmpStyle )
    {
    case VMP_STYLE_FOUR:

        switch( byNewStyle )
        {
        case VMP_STYLE_DYNAMIC:
        case VMP_STYLE_ONE:
        case VMP_STYLE_VTWO:
        case VMP_STYLE_THREE:
        case VMP_STYLE_FOUR:
            break;
        default:
			wError = ERR_MCU_VMPNOSUPPORTONMIX;
            bSupportVMPOpr = FALSE;
            return FALSE;
        }
        break;

    case VMP_STYLE_NINE:

        switch( byNewStyle )
        {
        case VMP_STYLE_DYNAMIC:
        case VMP_STYLE_ONE:
        case VMP_STYLE_VTWO:
        case VMP_STYLE_THREE:
        case VMP_STYLE_FOUR:
        case VMP_STYLE_NINE:
            break;
        default:
			wError = ERR_MCU_VMPNOSUPPORTONMIX;
            bSupportVMPOpr = FALSE;
            break;
        }
        break;

    case VMP_STYLE_SIXTEEN:
        switch(byNewStyle)
        {
        case VMP_STYLE_DYNAMIC:
        case VMP_STYLE_ONE:
        case VMP_STYLE_VTWO:
        case VMP_STYLE_THREE:
        case VMP_STYLE_FOUR:
        case VMP_STYLE_NINE:
        case VMP_STYLE_SIXTEEN:
            break;
        default:
			wError = ERR_MCU_VMPNOSUPPORTONMIX;
            bSupportVMPOpr = FALSE;
            break;
        }
		break;

    default:
        bSupportVMPOpr = FALSE;
        break;
    }

    if ( !bSupportVMPOpr )
    {
        pfmlog( "[IsVmpOprSupported] Result: failed due to style.%d needed while style.%d support only !\n",
                byNewStyle, byCapVmpStyle );
        return FALSE;
    }

    return TRUE;
#endif // 8000B / MCS
}


/*=============================================================================
    函 数 名： GetMaxOprMixNum
    功    能： 判断当前最多能设置的混音(包括定制和智能)终端数
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo     [in]  会议信息
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/29  4.0			顾振华                  创建
=============================================================================*/
u8 CMcuPfmLmt::GetMaxOprMixNum( const TConfInfo &tConfInfo, u16 &wError )
{
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return MAXNUM_MIXER_CHNNL;
#else
    
    if (!m_tFilter.IsEnable())
        return MAXNUM_MIXER_CHNNL;

	//会议视频格式H264
	BOOL32 bVideoTypeH264 = IsConfH264(tConfInfo);
    //会议音频格式G729
    BOOL32 bAudioTypeG729 = IsConfG729(tConfInfo);
	//会议码率超4M, zgc, 2007-11-02
	BOOL32 bConfBrLE4M	= IS_BITRATE_LE(tConfInfo, 4096);	
    //会议码率超2M
    BOOL32 bConfBrLE2M    = IS_BITRATE_LE(tConfInfo, 2048);  
    //会议码率超768K
    BOOL32 bConfBrLE768K  = IS_BITRATE_LE(tConfInfo, 768);
	//会议码率超1024K
    BOOL32 bConfBrLE1024K  = IS_BITRATE_LE(tConfInfo, 1024);
	//会议码率超1536K
    BOOL32 bConfBrLE1536K  = IS_BITRATE_LE(tConfInfo, 1536);

	TConfStatus tConfStatus = tConfInfo.m_tStatus;
	u8 byVmpStyle = tConfStatus.GetVmpStyle();

	u8 byMediaTypeComb = 0;
	byMediaTypeComb |= bAudioTypeG729 ? 0x01 : 0x00 ;
	byMediaTypeComb |= bVideoTypeH264 ? 0x02 : 0x00 ;
    
    //当前可以支持到的MIX成员总量
    u8 byMaxNum = 0;
    
    // 在适配
    if ( IsConfBasing(tConfInfo) )
    {
        wError = ERR_MCU_MIXNOSUPPORTONBAS;
        if ( bConfBrLE2M )
        {
            byMaxNum = ( bAudioTypeG729 ?  m_tFilter.byMaxNumMixMultiG729 : m_tFilter.byMaxNumMixMultiMp3 );
        }
        else
        {            
            byMaxNum = 0;
        }
    }
    else if ( IsConfVmping(tConfInfo) ) // 在画面合成
    {
        wError = ERR_MCU_MIXNOSUPPORTONVMP;
		if ( bConfBrLE4M )
		{
			switch( byMediaTypeComb )
			{
			case 0x02://H264-MP3
				if( bConfBrLE1024K )
				{
					switch(byVmpStyle) {
					case VMP_STYLE_ONE:
					case VMP_STYLE_VTWO:
					case VMP_STYLE_HTWO:
					case VMP_STYLE_THREE:
					case VMP_STYLE_FOUR:
					case VMP_STYLE_NINE:
						byMaxNum =  m_tFilter.byMaxNumMixMultiMp3;
						break;
					default:
						byMaxNum = 0;
						break;
					}
				}
				else
				{
					switch(byVmpStyle) {
					case VMP_STYLE_ONE:
					case VMP_STYLE_VTWO:
					case VMP_STYLE_HTWO:
					case VMP_STYLE_THREE:
					case VMP_STYLE_FOUR:
						byMaxNum =  bConfBrLE1536K ? m_tFilter.byMaxNumMixMultiMp3 : m_tFilter.byMaxNumMixMultiMp3/*4,临时放到8*/;
						break;
					default:
						byMaxNum = 0;
						break;
					}
				}
				break;
			case 0x03://H264-G729
				if( bConfBrLE768K )
				{
					switch(byVmpStyle) {
						case VMP_STYLE_ONE:
						case VMP_STYLE_VTWO:
						case VMP_STYLE_HTWO:
						case VMP_STYLE_THREE:
						case VMP_STYLE_FOUR:
						case VMP_STYLE_NINE:
							byMaxNum = m_tFilter.byMaxNumMixMultiG729;
							break;
						default:
							byMaxNum = 0;
							break;
					}				
				}
				else
				{
					byMaxNum = 0;
				}
				break;
			default:
				if ( bConfBrLE2M )
				{
					switch( byMediaTypeComb )
					{
					case 0x00://MPEG4-MP3
						switch(byVmpStyle) {
						case VMP_STYLE_ONE:
						case VMP_STYLE_VTWO:
						case VMP_STYLE_HTWO:
						case VMP_STYLE_THREE:
						case VMP_STYLE_FOUR:
							byMaxNum =  bConfBrLE1024K ? m_tFilter.byMaxNumMixMultiMp3 : m_tFilter.byMaxNumMixMultiMp3/*4,临时放到8*/;
							break;
						default:
							byMaxNum = 0;
							break;
						}				
						break;
					case 0x01://MPEG4-G729
						switch(byVmpStyle) {
						case VMP_STYLE_ONE:
						case VMP_STYLE_VTWO:
						case VMP_STYLE_HTWO:
						case VMP_STYLE_THREE:
						case VMP_STYLE_FOUR:
							byMaxNum =  bConfBrLE768K ? m_tFilter.byMaxNumMixMultiG729 : 0;
							break;
						default:
							byMaxNum = 0;
							break;
						}	
						break;
					default:
						byMaxNum = 0;
						break;
					}
				}
				else
				{
					byMaxNum = 0;
				}
				break;
			}
		}
		else
		{
			byMaxNum = 0;
		}

//		if( bConfBrLE2M )
//		{
//			switch( byMediaTypeComb ) {
//			case 0x00://MPEG4-MP3
//				switch(byVmpStyle) {
//				case VMP_STYLE_ONE:
//				case VMP_STYLE_VTWO:
//				case VMP_STYLE_HTWO:
//				case VMP_STYLE_THREE:
//				case VMP_STYLE_FOUR:
//					byMaxNum =  bConfBrLE1024K ? m_tFilter.byMaxNumMixMultiMp3 : m_tFilter.byMaxNumMixMultiMp3/*4,临时放到8*/;
//					break;
//				default:
//					byMaxNum = 0;
//					break;
//				}				
//				break;
//			case 0x01://MPEG4-G729
//				switch(byVmpStyle) {
//				case VMP_STYLE_ONE:
//				case VMP_STYLE_VTWO:
//				case VMP_STYLE_HTWO:
//				case VMP_STYLE_THREE:
//				case VMP_STYLE_FOUR:
//					byMaxNum =  bConfBrLE768K ? m_tFilter.byMaxNumMixMultiG729 : 0;
//					break;
//				default:
//					byMaxNum = 0;
//					break;
//				}	
//				break;
//			case 0x02://H264-MP3
//				if( bConfBrLE1024K )
//				{
//					switch(byVmpStyle) {
//					case VMP_STYLE_ONE:
//					case VMP_STYLE_VTWO:
//					case VMP_STYLE_HTWO:
//					case VMP_STYLE_THREE:
//					case VMP_STYLE_FOUR:
//					case VMP_STYLE_NINE:
//						byMaxNum =  m_tFilter.byMaxNumMixMultiMp3;
//						break;
//					default:
//						byMaxNum = 0;
//						break;
//					}
//				}
//				else
//				{
//					switch(byVmpStyle) {
//					case VMP_STYLE_ONE:
//					case VMP_STYLE_VTWO:
//					case VMP_STYLE_HTWO:
//					case VMP_STYLE_THREE:
//					case VMP_STYLE_FOUR:
//						byMaxNum =  bConfBrLE1536K ? m_tFilter.byMaxNumMixMultiMp3 : m_tFilter.byMaxNumMixMultiMp3/*4,临时放到8*/;
//						break;
//					default:
//						byMaxNum = 0;
//						break;
//					}
//				}
//				break;
//			case 0x03://H264-G729
//				if( bConfBrLE768K )
//				{
//					switch(byVmpStyle) {
//						case VMP_STYLE_ONE:
//						case VMP_STYLE_VTWO:
//						case VMP_STYLE_HTWO:
//						case VMP_STYLE_THREE:
//						case VMP_STYLE_FOUR:
//						case VMP_STYLE_NINE:
//							byMaxNum = m_tFilter.byMaxNumMixMultiG729;
//							break;
//						default:
//							byMaxNum = 0;
//							break;
//					}				
//				}
//				else
//				{
//					byMaxNum = 0;
//				}
//				break;
//			default:
//				pfmlog("[GetMaxOprMixNum]MediaType is error!\n");
//				byMaxNum = 0;
//				break;
//			}
//		}
//		else
//		{
//			byMaxNum = 0;
//		}
    }
    else    // 单开
    {
        wError = ERR_MCU_MIXNOSUPPORT;
        byMaxNum = ( bAudioTypeG729 ? m_tFilter.byMaxNumMixSingleG729 : m_tFilter.byMaxNumMixSingleMp3);
    }
    return byMaxNum;
#endif
}

/*=============================================================================
    函 数 名： IsMixOprSupported
    功    能： 判断当前的定制混音操作能否接受
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo         [in]  会议信息
               u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
               u8 byAddNum                  [in]  要添加进混音的终端数量
               u16 &wError                  [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/25  4.0			张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsMixOprSupported( const TConfInfo &tConfInfo, u8 byMixingNum, u8 byAddNum, u16 &wError )
{
    wError = 0;
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return TRUE;
#else

    if (!m_tFilter.IsEnable())
        return TRUE;

    if ( byAddNum == 0 )
    {
        return TRUE;
    }

	if( IsConfG729(tConfInfo) )
	{
		if( byMixingNum + byAddNum > m_tFilter.byMaxNumMixSingleG729 )
		{
			wError = ERR_MCU_MIXNOSUPPORT;
			return FALSE;
		}
	}
	else
	{
		if( byMixingNum + byAddNum > m_tFilter.byMaxNumMixSingleMp3 )
		{
			wError = ERR_MCU_MIXNOSUPPORT;
			return FALSE;
		}
	}

    u8 byMaxNum = GetMaxOprMixNum(tConfInfo, wError);
    if ( byMaxNum == 0 )
    {
        pfmlog( "[IsMixOprSupported] GetMaxOprMixNum return 0 !\n");
        return FALSE;
    }
    if ( byMaxNum < byMixingNum + byAddNum )
    {
        pfmlog( "[IsMixOprSupported] return failed due to max num.%d while CurNum.%d and AddNum.%d !\n",
                 byMaxNum, byMixingNum, byAddNum );
        return FALSE;
    }

    return TRUE;       
#endif
}

/*=============================================================================
    函 数 名： IsVacOprSupported
    功    能： 判断开启VAC是否能被接受
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo   [in]  会议信息
               u8        byMtNum      [in]  会议当前的所有在线终端数
               u8        byMixNum     [in]  正在混音(智能、定制)终端数
               u16 &wError            [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/30  4.0			顾振华                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsVacOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u16 &wError )
{
    wError = 0;
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return TRUE;
#else

    if (!m_tFilter.IsEnable())
        return TRUE;

    BOOL32 bConfVMP = IsConfVmping(tConfInfo);
    BOOL32 bConfBAS = IsConfBasing(tConfInfo);

    BOOL32 bConfAudioG729 = IsConfG729(tConfInfo);

    BOOL32 bAck = TRUE;
    u8 byRef = 0;
    // 纯VAC
    if ( !bConfBAS & !bConfVMP )
    {
        wError = ERR_MCU_VACNOSUPPORT;
        byRef = bConfAudioG729 ? m_tFilter.byMaxNumVacSingleG729 : m_tFilter.byMaxNumVacSingleMp3 ;
        bAck = (byMtNum <= byRef);
    }
    else if ( bConfVMP ) // VMP + VAC
    {        
        wError = ERR_MCU_VMPNOVAC;
        bAck = FALSE;
    }
    else if ( bConfBAS )    // VAC + BAS
    {        
        wError = ERR_MCU_VACNOSUPPORTONBAS;
        BOOL32 bConfBRLE2M = IS_BITRATE_LE(tConfInfo, 2048);
        if ( bConfBRLE2M )
        {
            byRef = bConfAudioG729 ? m_tFilter.byMaxNumVacMultiG729 : m_tFilter.byMaxNumVacMultiMp3;
            bAck = (byMtNum <= byRef);
        }
        else 
        {
            bAck = FALSE;
        }        
    }
    
    if (!bAck)
    {
        pfmlog("[IsVacOprSupported] Return Nack(%d) because mtnum.%d is over max.%d at BR.%d\n", wError , byMtNum, byRef, tConfInfo.GetBitRate());
    }
    
    return bAck;
#endif

}

/*=============================================================================
    函 数 名： IsBasOprSupported
    功    能： 判断开启BAS是否能被接受
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo   [in]  会议信息
               u8        byMixNum     [in]  正在混音(智能、定制)终端数
               u16 &wError            [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/30  4.0			顾振华                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsBasOprSupported( const TConfInfo &tConfInfo, u8 byMixNum, u16 &wError )
{
    wError = 0;
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return TRUE;
#else

    if (!m_tFilter.IsEnable())
        return TRUE;

    BOOL32 bConfVAC = IsConfVacing(tConfInfo);
    BOOL32 bConfMIX = IsConfMixingNoVac(tConfInfo);
    
    BOOL32 bConfAudioG729 = IsConfG729(tConfInfo);
    BOOL32 bConfBRLE2M = IS_BITRATE_LE(tConfInfo, 2048);
    
    BOOL32 bAck = TRUE;
    u8 byRef = 0;
    
    // 纯BAS
    if ( !bConfVAC & !bConfMIX )
    {
        return TRUE;
    }

    if ( bConfVAC ) // BAS + VAC
    {
        wError = ERR_MCU_BASNOSUPPORTONVAC;
        if ( bConfBRLE2M )
        {
            byRef = bConfAudioG729 ? m_tFilter.byMaxNumVacMultiG729 : m_tFilter.byMaxNumVacMultiMp3;
            bAck =  (byMixNum <= byRef);
        }
        else 
        {
            bAck = FALSE;
        }  
    }
    else if ( bConfMIX )    // BAS + MIX
    {                
        wError = ERR_MCU_BASNOSUPPORTONMIX;
        if ( bConfBRLE2M )
        {
            byRef = bConfAudioG729 ? m_tFilter.byMaxNumMixMultiG729 : m_tFilter.byMaxNumMixMultiMp3;
            bAck =  (byMixNum <= byRef);
        }
        else 
        {
            bAck = FALSE;
        }        
    }

    if (!bAck)
    {
        pfmlog("[IsBasOprSupported] Return Nack(%d) because byMixNum.%d is over max. %d at BR %d\n", wError , byMixNum, byRef, tConfInfo.GetBitRate());
    }

    return bAck;
#endif    
}

/*=============================================================================
    函 数 名： IsMtOprSupported
    功    能： 判断当前的增加终端是否能被接受
    算法实现： 
    全局变量： 
    参    数： TConfInfo &tConfInfo   [in]  会议信息
               u8        byMtNum      [in]  会议当前的所有在线终端数
               u8        byMixNum     [in]  正在混音(智能、定制)终端数
               u16 &wError            [out] 返回的错误码
    返 回 值： BOOL32
    ----------------------------------------------------------------------
    修改记录    ：
    日  期		版本		修改人		走读人    修改内容
    2007/01/26  4.0			张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsMtOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixNum, u16 &wError )
{
    wError = 0;
#if ( (!defined(_MINIMCU_)) && (!defined(MCS_PFMLMT)) )
    return TRUE;
#else

    if (!m_tFilter.IsEnable())
        return TRUE;

    // 当前会议属性的关键值 标识
    BOOL32 bConfVAC = IsConfVacing(tConfInfo);
    BOOL32 bConfVMP = IsConfVmping(tConfInfo);
    BOOL32 bConfMIX = IsConfMixingNoVac(tConfInfo);
    BOOL32 bConfBAS = IsConfBasing(tConfInfo);

    BOOL32 bConfAudioG729 = IsConfG729(tConfInfo);
    BOOL32 bConfVideoH264 = IsConfH264(tConfInfo);

    BOOL32 bConfBRLE768K   = IS_BITRATE_LE(tConfInfo, 768);
    BOOL32 bConfBRLE1M     = IS_BITRATE_LE(tConfInfo, 1024);
    BOOL32 bConfBRLE2M     = IS_BITRATE_LE(tConfInfo, 2048);

    // [1] nothing
    if ( !bConfVMP && !bConfMIX && !bConfBAS && !bConfVAC )
    {
        return TRUE;
    }
    
	// zgc, 2008-04-24, BUG10556, 开始讨论会议时会控多次弹出提示从会议讨论切换到定制混音的提示
	// 以下代码统一修改: (1)混音使用 byMixNum ，语音激励使用 byMtNum; (2)'>'用'>='替换

    // [2] Audio only
    if ( !bConfVMP && !bConfBAS ) 
    {
        if ( bConfMIX )
        {
            u8 byMax = bConfAudioG729 ? m_tFilter.byMaxNumMixSingleG729 : m_tFilter.byMaxNumMixSingleMp3;
            //终端数力已经超限
            if ( byMixNum >= byMax ) 
            {
                wError = ERR_MCU_MIXNOSUPPORT;
                pfmlog( "[IsMtOprSupported] cur mt Num.%d is over the load.%d MIX!\n",
                        byMtNum, byMax );
                return FALSE;
            }
        }
        else if ( bConfVAC ) 
        {
            u8 byMax = bConfAudioG729 ? m_tFilter.byMaxNumVacSingleG729 : m_tFilter.byMaxNumVacSingleMp3;
            //终端数力已经超限
            if ( byMtNum >= byMax ) 
            {
                wError = ERR_MCU_VACNOSUPPORT;
                pfmlog( "[IsMtOprSupported] cur mt Num.%d is over the load.%d VAC!\n",
                    byMtNum, byMax );
                return FALSE;
            }
        }
        return TRUE;
    }

    // [3] Video and Audio    
    // [3.1] VMP + Mix  
    BOOL32 bOverload = FALSE;
    if ( bConfVMP ) 
    {
        // VMP + VAC 不同时支持，不考虑
        if ( !bConfMIX )
        {
            return TRUE;
        }
        
        bOverload =  ( bConfAudioG729 ? (byMixNum /*>*/>= m_tFilter.byMaxNumMixMultiG729) : (byMixNum /*>*/>= m_tFilter.byMaxNumMixMultiMp3) );
        if ( bOverload ) 
        {
            wError = ERR_MCU_MIXNOSUPPORTONVMP;
            pfmlog( "[IsMtOprSupported] cur mt Num.%d is over the load.%d VMP+MIX!\n", byMtNum );
            return FALSE;
        }

        return TRUE;
    }

    if ( bConfBAS )
    {
        // 只有 BAS
        if ( !bConfMIX && !bConfVAC )
        {
            return TRUE;
        }

        // [3.2] BAS + MIX
        if (bConfMIX)
        {            
            if ( bConfBRLE2M )
            {
                bOverload =  ( bConfAudioG729 ? (byMixNum >= m_tFilter.byMaxNumMixMultiG729) : (byMixNum >= m_tFilter.byMaxNumMixMultiMp3) );
            }
            else 
            {
                bOverload = TRUE;
            }
            if ( bOverload ) 
            {
                wError = ERR_MCU_MIXNOSUPPORTONBAS;
                pfmlog( "[IsMtOprSupported] cur mt Num.%d is over the load.%d BAS+MIX!\n", byMtNum);
                return FALSE;
            }
            return TRUE;
        }
        // [3.3] BAS + VAC
        else
        {
            bOverload = FALSE;
            if ( bConfBRLE2M )
            {
                bOverload =  ( bConfAudioG729 ? (byMtNum >= m_tFilter.byMaxNumVacMultiG729) : (byMtNum >= m_tFilter.byMaxNumVacMultiMp3) );
            }
            else 
            {
                bOverload = TRUE;
            }
            if ( bOverload ) 
            {
                wError = ERR_MCU_VACNOSUPPORTONBAS;
                pfmlog( "[IsMtOprSupported] cur mt Num.%d is over the load.%d BAS+VAC!\n", byMtNum);
                return FALSE;
            }
            return TRUE;
        }
    }

    return TRUE;
#endif 
}

/* MCU 8000A 性能限制代码，不受过滤器约束 */

/*=============================================================================
函 数 名： IsVmpStyleSupport
功    能： 判断某个画面合成（包括多画面电视墙）操作的目标风格是否能支持
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo   [in] 会议信息
		   u8 byConfIdx                 [in] 会议ConfIdx信息
		   TPeriEqpStatus *ptVmpStatus  [in] 外设状态数组
		   u16 wLen                     [in] 外设状态数组长度
		   u8 byTargetStyle             [in] 指定的目标风格
		   u8 &bySelVmpId               [out] 返回符合条件的Vmp或VmpTw
返 回 值： static BOOL32 是否能支持
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2007/7/13   4.0			周广程      顾振华      创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsVmpStyleSupport( const TConfInfo &tConfInfo, u8 byConfIdx, 
                                      TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								      u8 byTargetStyle, u8 &bySelVmpId )
{
    // FIXME: 
    // 遗留问题1：如果用户选择了一个要求很低的VMP风格，但是却会分配一个能力很高的VMP
    // 遗留问题2：Mcu侧区分了 IsMcuSupport, IsVmpSupport，但是MCS没有区分，
    //            所以Change时MCS会把一些其他Vmp支持的能力列出来而被MCU拒绝

	u8 byVmpCapChnnlNum = 0;
	if( !GetMaxCapVMP( tConfInfo, byConfIdx,
                       ptVmpStatus, wLen, 
                       byVmpCapChnnlNum, 
                       bySelVmpId,
					   byTargetStyle) )
	{
		pfmlog( "[IsVmpStyleSupport] The GetMaxCapVmp() return no vmp avaiable or suitable!\n" );
		return FALSE;
	}
/*
	u8 byLop = 0;
	u8 byVmpMaxChnnlNum = 0;
	u8 byEqpType = 0;		//取的是TPeriEqpStatus中的EqpType，status notif消息过来，
							//vmp,mpu-svmp,mpu-dvmp,evpu均填EQP_TYPE_VMP
	u8 byVmpSubtype = 0;	//VMP 子类型
	for ( byLop = 0; byLop < wLen; byLop++ )
	{
		if ( ptVmpStatus[byLop].GetEqpId() == bySelVmpId )
		{
			byVmpMaxChnnlNum = ptVmpStatus[byLop].m_tStatus.tVmp.m_byChlNum;
			byEqpType = ptVmpStatus[byLop].GetEqpType();
			byVmpSubtype = ptVmpStatus[byLop].m_tStatus.tVmp.m_bySubType;
			break;
		}
	}

	u8 abyStyleArray[32];
    u8 bySize = 32;
	GetSupportedVmpStyles( tConfInfo, byEqpType, byVmpSubtype, byVmpCapChnnlNum, byVmpMaxChnnlNum, 
                           abyStyleArray, bySize );
	for ( byLop = 0; byLop < bySize; byLop++ )
	{
		if ( abyStyleArray[byLop] == byTargetStyle )
		{
			return TRUE;
		}
	}
		
	return FALSE;
	*/
	return TRUE;
}

/*=============================================================================
函 数 名： GetSupportedVmpStyles
功    能： 返回指定会议能够支持的所有画面合成风格
算法实现： 
全局变量： 
参    数：   const TConfInfo &tConfInfo   [in] 会议信息
             u8 byConfIdx                 [in] 会议ConfIdx信息
             TPeriEqpStatus *ptVmpStatus  [in] 外设状态数组
             u16 wLen                     [in] 外设状态数组长度
             u8 *pabStyle                 [out] 返回的风格数组
             u8 &byStyleSize              [I/O] 传入数组的大小，同时返回实际大小。
                                                如果实际返回值大于传入值，则说明空间不够，同时上面的数组没有进行填充
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2007/7/13   4.0			周广程      顾振华      创建
=============================================================================*/
void CMcuPfmLmt::GetSupportedVmpStyles( const TConfInfo &tConfInfo, u8 byConfIdx, 
                                        TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								        u8 *pabyStyle, u8 &byArraySize )
{
	u8 byVmpCapChnnlNum = 0;
	u8 bySelVmpId = 0;
	if( !GetMaxCapVMP( tConfInfo, byConfIdx, 
                       ptVmpStatus, wLen, 
                       byVmpCapChnnlNum, 
                       bySelVmpId ) )
	{
        // 没有找到可用的Vmp/VmpTw，返回0
		pfmlog( "[GetSupportedVmpStyles] The GetMaxCapVmp() return no vmp avaiable!\n" );
        byArraySize = 0;
		return;
	}
    
	u8 byLop = 0;
	u8 byVmpMaxChnnlNum = 0;
	u8 byEqpType = 0;
	u8 byVmpSubType = 0;
	for ( byLop = 0; byLop < wLen; byLop++ )
	{
		if ( ptVmpStatus[byLop].GetEqpId() == bySelVmpId )
		{
			byVmpMaxChnnlNum = ptVmpStatus[byLop].m_tStatus.tVmp.m_byChlNum;
			byEqpType = ptVmpStatus[byLop].GetEqpType();
			byVmpSubType = ptVmpStatus[byLop].m_tStatus.tVmp.m_bySubType;
			break;
		}
	}

	GetSupportedVmpStyles( tConfInfo, byEqpType, byVmpSubType, byVmpCapChnnlNum, byVmpMaxChnnlNum, pabyStyle, byArraySize );
}

/*=============================================================================
函 数 名： GetMaxCapVMPByConfInfo
功    能： 根据会议格式会议码率获取当前会议vmp最大支持的通道个数
算法实现： 
全局变量： 
参    数： void
返 回 值： u8  通道数
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2006/3/31  4.0			许世林                  创建
=============================================================================*/
u8 CMcuPfmLmt::GetMaxCapVMPByConfInfo(const TConfInfo &tConfInfo)  
{
    u8 byCapChnnlNum = 0;   
    
    u16 wBitrate   = tConfInfo.GetBitRate();
    u8 byVidFormat = tConfInfo.GetMainVideoFormat();
	u8 byVidType   = tConfInfo.GetMainVideoMediaType();

    // 只要是VmpAutoAdapt,就支持20路，非VmpAutoAdapt分情况处理
    if ( tConfInfo.IsVmpAutoAdapt() )
    {   
	    byCapChnnlNum = MAXNUM_MPUSVMP_MEMBER/*16*/;
    }    
    else
    {
        if ( MEDIA_TYPE_H264 == byVidType )
        {
            // guzh [2008/08/06]
            if ( VIDEO_FORMAT_CIF == byVidFormat && wBitrate <= 4096)
            {
                byCapChnnlNum = 4;
            }
            else
            {
                byCapChnnlNum = 0;
            }
        }
        else if ( byVidType   == MEDIA_TYPE_H262 && // MPEG2,2CIF 区分码率
                  byVidFormat == VIDEO_FORMAT_2CIF )
        {
            if ( wBitrate <= 3072 ) // <=2048 && 2048-3072
            {
                byCapChnnlNum = 6;
            }
            else if ( wBitrate <= 8128 )    // 3072 -- 8128
            {
                byCapChnnlNum = 4;
            }
            else
            {
                byCapChnnlNum = 0;
            }                
        }
        // 否则按照分辨率处理
        else
        {
            switch ( byVidFormat )
            {
            case VIDEO_FORMAT_CIF:     //  CIF
                if ( wBitrate <= 1024 )
                {
                    byCapChnnlNum = 16;
                }
                else if ( wBitrate <= 1536 )
                {
                    byCapChnnlNum = 13;
                }
                else if ( wBitrate <= 2048 )
                {
                    byCapChnnlNum = 10;
                }
                else if ( wBitrate <= 3072 )
                {
                    byCapChnnlNum = 7;
                }
                else if ( wBitrate <= 4096 )
                {
                    byCapChnnlNum = 6;
                }
                else if ( wBitrate <= 8128 )
                {
                    byCapChnnlNum = 4;
                }
                else
                {
                    byCapChnnlNum = 0;
                }
                break;
            case VIDEO_FORMAT_4CIF:     //  4CIF
                if (wBitrate > 8128)
                {
                    byCapChnnlNum = 0;
                }
                else
                {
                    byCapChnnlNum = 4;
                }            
                break;
            default:                   //  其余按auto处理
                if ( wBitrate <= 1024 )
                {
                    byCapChnnlNum = 16;
                }
                else if ( wBitrate <= 1536 )
                {
                    byCapChnnlNum = 13;
                }
                else if ( wBitrate <= 2048 )
                {
                    byCapChnnlNum = 8;
                }
                else if ( wBitrate <= 3072 )
                {
                    byCapChnnlNum = 6;
                }
                else if ( wBitrate <= 8128 )
                {
                    byCapChnnlNum = 4;
                }
                else
                {
                    byCapChnnlNum = 0;
                }
                break;
            }
        }
    }
    
    pfmlog("[GetMaxCapVMPByConfInfo] CapChnnlNum=%d, IsAutoAdapt:%d, Video Type:%d, Format:%d, Bitrate:%d\n",
            byCapChnnlNum, tConfInfo.IsVmpAutoAdapt(), byVidType, byVidFormat, wBitrate);
    
    return byCapChnnlNum;
}

/*=============================================================================
	函 数 名： GetMaxCapVMP
	功    能： 计算当前MCU的可用VMP中最多支持的画面合成路数、风格以及相应的设备ID			   
	算法实现： 
	全局变量： 
	参    数： const TConfInfo &tConfInfo :
			   u8 byConfIdx :
			   TPeriEqpStatus *ptStatus : VMP状态数组
			   u16 wlen : VMP状态数组长度
			   u8 &byVmpCapStyle [OUT] : 最大的合成风格
			   u8 &byVmpCapChnnlNum [OUT] : 最大的合成通道数
			   u8 &bySelVmpId[OUT] : 所有空闲及本会议已使用的VMP中能力最强的VMP的设备ID
	返 回 值： BOOL32
		----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/6/20   4.0			周广程                  创建
	09/04/21    4.6         薛亮                  不同种类VMP选择策略重整
=============================================================================*/
BOOL32 CMcuPfmLmt::GetMaxCapVMP( const TConfInfo &tConfInfo, u8 byConfIdx, 
								 TPeriEqpStatus *ptStatus, u16 wLen, 
								 u8 &byVmpCapChnnlNum, u8 &bySelVmpId,
								 u8 byTargetStyle)
{
	byVmpCapChnnlNum = 0;
	bySelVmpId = 0;

	if( NULL == ptStatus )
	{
		pfmlog( "[GetMaxCapVMP] pointer is NULL !\n" );
		return FALSE;
	}
	if( 0 == wLen || wLen > MAXNUM_PERIEQP )
	{
		pfmlog( "[GetMaxCapVMP] vmp status array length is %d, error!\n", wLen );
		return FALSE;
	}
		
	// 按会议信息计算最大支持合成能力
    u8 byMaxChnlNumByConf = GetMaxCapVMPByConfInfo(tConfInfo);

	// 会议支持能力为0，返回FALSE, zgc, 2008-03-26
	if ( 0 == byMaxChnlNumByConf )
	{
		pfmlog( "[GetMaxCapVMP] Conf don't support vmpopr!\n" );
		return FALSE;
	}
    
    // 根据外设状态计算所有在线VMP中最接近会议需要的，
    // 最接近即：如果所有VMP都无法满足会议需求，则返回最大能力者
    // 否则返回刚满足需求者
	// xliang [12/8/2008] 分5种vmp	EVPU也分1+3和2+2模式
	const u8 byVmpTypeNum = 5;
	u8	abySelIdx[byVmpTypeNum][MAXNUM_PERIEQP] = {0};	//5种vmp对应的id
	u8	abySelNum[byVmpTypeNum] = {0};					//5种vmp分别对应的数目
	u16 byWholeSelNum = 0;					//vmp总数目
	u8  byVmpSubType = 0;					//vmp子类型
	s32 nUsedIdx = -1;						//表征当前会议已经在用某个Vmp ID，-1表没在用

	// zgc, 2008-04-23, BUG10524修改及代码重整
    // zw 20081014 兼容VMPTW
    BOOL32 byIsVMPNone = FALSE;
    if ( EQP_TYPE_VMP == ptStatus->GetEqpType() )
    {
        if ( CONF_VMPMODE_NONE == tConfInfo.m_tStatus.GetVMPMode() )
        {
            byIsVMPNone = TRUE;
        }
    }
    else // EQP_TYPE_VMPTW == (u8*)ptStatus
    {
        if ( CONF_VMPTWMODE_NONE == tConfInfo.m_tStatus.GetVmpTwMode() )
        {
            byIsVMPNone = TRUE;
        }
    }

	if ( byIsVMPNone )
	{
		for (u8 byLop = 0; byLop < wLen; byLop++ )
		{
			if ( ptStatus[byLop].IsNull() )
			{
				continue;
			}
			if ( !ISTRUE(ptStatus[byLop].m_byOnline) )
			{
				continue;
			}
			if ( ISTRUE(ptStatus[byLop].m_tStatus.tVmp.m_byUseState) )
			{
				// 已被使用的VMP不可能属于未开启VMP合成的会议
				continue;
			}
			// 记下可能被选中的VMP的序号
			// xliang [12/8/2008] vmp分类统计.
			/*			0	//老vmp
						1	//EVPU_SVMP
					    2	//EVPU_DVMP
						3	//MPU_SVMP
						4	//MPU_DVMP */
			byVmpSubType = ptStatus[byLop].m_tStatus.tVmp.m_bySubType;
			abySelIdx[byVmpSubType][ abySelNum[byVmpSubType] ] = byLop;
			abySelNum[byVmpSubType]++;
			byWholeSelNum ++;
		}
	}
	else
	{
		u16 awUnusedIdx[MAXNUM_PERIEQP] = {0};
		u16 wUnusedNum = 0;
    	for (u8 byLop = 0; byLop < wLen; byLop++ )
		{
			if ( ptStatus[byLop].IsNull() )
			{
				continue;
			}
			if ( !ISTRUE(ptStatus[byLop].m_byOnline) )
			{
				continue;
			}
			if ( ISTRUE(ptStatus[byLop].m_tStatus.tVmp.m_byUseState) && 
				byConfIdx != ptStatus[byLop].GetConfIdx() )
			{
				// 已使用的VMP非被本会议占用，不能用
				continue;
			}
			if ( !ISTRUE(ptStatus[byLop].m_tStatus.tVmp.m_byUseState) )
			{
				// xliang [12/8/2008] 
				byVmpSubType = ptStatus[byLop].m_tStatus.tVmp.m_bySubType;
				abySelIdx[byVmpSubType][abySelNum[byVmpSubType]] = byLop;
				abySelNum[byVmpSubType]++;
				byWholeSelNum++;
			}
			else
			{
				// 一个会议只能开一个VMP
				// 会议如果已经在开VMP，则只能判断该VMP的能力，目前不支持VMP之间的切换
				nUsedIdx = byLop;
				// xliang [12/8/2008] 
 				byWholeSelNum = 1;
				break;
			}
		}
	}

	// xliang [12/8/2008] 
	if (0 == byWholeSelNum )
	{
		pfmlog( "[GetMaxCapVMP] No vmp can be used!\n" );
		return FALSE;
	}

	if(nUsedIdx >= 0) //表明当前会议已经在用某个vmp了
	{
		byVmpCapChnnlNum = ptStatus[nUsedIdx].m_tStatus.tVmp.m_byChlNum;
		bySelVmpId = ptStatus[nUsedIdx].GetEqpId();
		return TRUE;
	}

	// xliang [12/8/2008] 根据5种vmp对应各自会议格式的优先级分段遍历
	u8 byConfMediaType = tConfInfo.GetMainVideoMediaType();
	u8 byConfVidFormat = tConfInfo.GetMainVideoFormat();
	u8 abyVmpTypePri[byVmpTypeNum];
	if( MEDIA_TYPE_H264 == byConfMediaType )
	{
		switch(byConfVidFormat)
		{
		case VIDEO_FORMAT_HD720:
		case VIDEO_FORMAT_HD1080:
			{
				//1080,720会议：先后尝试以下VMP：mpu_svmp > mpu_dvmp > evpu_svmp > evpu_dvmp > vmp
				u8 abyVmpPri[] = { MPU_SVMP, MPU_DVMP, EVPU_SVMP, EVPU_DVMP, VMP };
				memcpy(abyVmpTypePri,abyVmpPri,sizeof(abyVmpTypePri));
				break;
			}
		case VIDEO_FORMAT_4CIF:
			{
				//4CIF会议:  evpu_svmp > evpu_dvmp > mpu_svmp > mpu_dvmp >vmp
				u8 abyVmpPri[] = { EVPU_SVMP, EVPU_DVMP, MPU_SVMP, MPU_DVMP, VMP };
				memcpy(abyVmpTypePri,abyVmpPri,sizeof(abyVmpTypePri));
				break;
			}
		case VIDEO_FORMAT_CIF:
			{
				//CIF会议:  vmp > evpu_dvmp > evpu_svmp > mpu_dvmp > mpu_svmp 
				u8 abyVmpPri[] = { VMP, EVPU_DVMP, EVPU_SVMP, MPU_DVMP, MPU_SVMP };
				memcpy(abyVmpTypePri,abyVmpPri,sizeof(abyVmpTypePri));
				break;
			}
		default:
			{
				//目前按cif会议的优先级
				u8 abyVmpPri[] = { VMP, EVPU_DVMP, EVPU_SVMP, MPU_DVMP, MPU_SVMP };
				memcpy(abyVmpTypePri,abyVmpPri,sizeof(abyVmpTypePri));
				break;
			}
			
		}
	}
	else //MP4,h263， mp2,h261
	{
		u8 abyVmpPri[] = { VMP, EVPU_DVMP, EVPU_SVMP, MPU_DVMP, MPU_SVMP };
		memcpy(abyVmpTypePri, abyVmpPri, sizeof(abyVmpTypePri));
	}

	

	u8 byLoop = 0;
 	//print All Selectable VMPs info
	pfmlog("[GetMaxCapVMP] All Selectable VMPs info:\n==================================\n");
	for(byLoop =0; byLoop<byVmpTypeNum; byLoop++)
	{
		u8 bySelVmpType = abyVmpTypePri[byLoop];
		u8 bySelNum		= abySelNum[bySelVmpType];
		pfmlog("VMP type %u, Num is %u\n---------------\n",bySelVmpType,bySelNum);
		for(u8 byLop = 0; byLop < bySelNum; byLop++)
		{
			u8 byIdx =  abySelIdx[bySelVmpType][byLop];
			pfmlog( "Vmp Id.%u\n",ptStatus[byIdx].GetEqpId() );
		}
	}
	
	//分段遍历选取合适的vmp
	u8 abySelVmpIdx[MAXNUM_PERIEQP];
	for(byLoop =0; byLoop<byVmpTypeNum; byLoop++)
	{
		u8 bySelNum = abySelNum[abyVmpTypePri[byLoop]];
		if(bySelNum ==0)
		{
			continue;
		}

		//  [12/22/2009 pengjie] Modify 高清会议，不能使用VPU（VMP）来进行画面合成
		if( MEDIA_TYPE_H264 == byConfMediaType && (VIDEO_FORMAT_HD720 == byConfVidFormat || VIDEO_FORMAT_HD1080 == byConfVidFormat) )
		{
			if(abyVmpTypePri[byLoop] == VMP)
			{
				continue;
			}
		}
		// End
		
		//对于会议主格式是mp2,h261,只能用老的VMP
		if( (MEDIA_TYPE_H262 == byConfMediaType || MEDIA_TYPE_H261 == byConfMediaType)
			
			&& abyVmpTypePri[byLoop] != VMP)
		{
			continue;
		}

		//老vmp不能用于画面合成批量轮询
		if (tConfInfo.m_tStatus.m_tVMPParam.IsVMPBatchPoll() &&
			abyVmpTypePri[byLoop] == VMP)
		{
			continue;
		}
		
		memcpy(abySelVmpIdx,abySelIdx[abyVmpTypePri[byLoop]],sizeof(u8)*bySelNum);
	
		if(GetSelVmpCap(abySelVmpIdx, ptStatus, bySelNum,
			byMaxChnlNumByConf,byVmpCapChnnlNum, bySelVmpId))
		{
			// xliang [2/12/2009] 若选出的VMP 其能力小于用户所选的风格能力，则选出的VMP也是不合适的
			if (byTargetStyle > byVmpCapChnnlNum)  
			{
				bySelVmpId = 0; //表没有合适的VMP可用
			}
			else
			{
				break;
			}
		}
	}
	pfmlog("[GetMaxCapVMP] byVmpCapChnnlNum=%d, bySelVmpId=%d\n",\
		byVmpCapChnnlNum, bySelVmpId);

	if(bySelVmpId == 0)
	{
		return FALSE;
	}
	return TRUE;

}


/*=============================================================================
函 数 名： GetSupportedVmpStyles
功    能： 
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo
		   u8 byEqpType
		   u8 bySubType
		   u8 byCapChnnlNum             
           u8 byVmpMaxChnnlNum
           u8 *pabyStyle                [out] 返回的风格数组
           u8 &byArraySize              [I/O] 传入数组的大小，同时返回实际大小。
                                              如果实际返回值大于传入值，则说明空间不够，同时上面的数组没有进行填充
返 回 值： void 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2007/7/13   4.0			周广程                  创建
2009/2/18	4.6			薛亮					增参数区分VMP种类；引入20风格
=============================================================================*/
void CMcuPfmLmt::GetSupportedVmpStyles( const TConfInfo &tConfInfo,
									    u8 byEqpType,
										u8 bySubType,
										u8 byCapChnnlNum,
										u8 byVmpMaxChnnlNum, 
                                        u8 *pabyStyle,
										u8 &byArraySize )
{
	if ( pabyStyle == NULL )
	{
		pfmlog( "[GetSupportedVmpStyles] style array point is NULL!\n");
        byArraySize = 0;
		return;
	}
    
    u8 abyStyles[MAXNUM_MCU_PERIEQP] = {VMP_STYLE_NONE};

    u8 byRetSize = 0;
    if ( byEqpType == EQP_TYPE_VMP )
    {
        abyStyles[byRetSize++] = VMP_STYLE_DYNAMIC;
    }

	// xliang [2/18/2009] VMP最大16风格，MPU和EVPU最大20风格
	BOOL32 bEqpChnlFull = FALSE;
	if (bySubType == VMP )
	{
		bEqpChnlFull = (byVmpMaxChnnlNum == MAXNUM_SDVMP_MEMBER);
	}
	else
	{
		bEqpChnlFull = (byVmpMaxChnnlNum == MAXNUM_MPUSVMP_MEMBER);
	}
    //BOOL32 bEqpChnlFull = (byVmpMaxChnnlNum == 16);
    byCapChnnlNum = min(byCapChnnlNum, byVmpMaxChnnlNum);
    
	switch( byCapChnnlNum )
	{
		case 1:
			if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE; 
			}
			break;
		case 2:
			if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
			break;
		case 3:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
			}
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
			break;
		case 4:
        case 5:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;	
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;            		
			break;        
		case 6:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;            
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
			break;
		case 7:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;            
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_SEVEN;
            }		
			break;
		case 8:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;  
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_SEVEN;
                abyStyles[byRetSize++] = VMP_STYLE_EIGHT;
            }	
			break;
		case 9:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_ONE;
            }
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;  
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
            if (bEqpChnlFull)
            {
                abyStyles[byRetSize++] = VMP_STYLE_SEVEN;
                abyStyles[byRetSize++] = VMP_STYLE_EIGHT;
            }
            abyStyles[byRetSize++] = VMP_STYLE_NINE;		
			break;
		case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if ( /*tConfInfo.GetMainVideoFormat() != MEDIA_TYPE_H264 ||*/ bEqpChnlFull )
			{
				abyStyles[byRetSize++] = VMP_STYLE_ONE;
			}
            abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;            
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;            
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
            abyStyles[byRetSize++] = VMP_STYLE_SEVEN;
            abyStyles[byRetSize++] = VMP_STYLE_EIGHT;
            abyStyles[byRetSize++] = VMP_STYLE_NINE;	
            abyStyles[byRetSize++] = VMP_STYLE_TEN;
            if (byCapChnnlNum >= 13)
            {
                abyStyles[byRetSize++] = VMP_STYLE_THIRTEEN;  
            }
            if (byCapChnnlNum >= 16)
            {
                abyStyles[byRetSize++] = VMP_STYLE_SIXTEEN;
            }
            break;
		case 20:
			abyStyles[byRetSize++] = VMP_STYLE_ONE;
			abyStyles[byRetSize++] = VMP_STYLE_HTWO;
            abyStyles[byRetSize++] = VMP_STYLE_VTWO;            
            abyStyles[byRetSize++] = VMP_STYLE_THREE;
            abyStyles[byRetSize++] = VMP_STYLE_SPECFOUR;
            abyStyles[byRetSize++] = VMP_STYLE_FOUR;            
            abyStyles[byRetSize++] = VMP_STYLE_SIX;
            abyStyles[byRetSize++] = VMP_STYLE_SEVEN;
            abyStyles[byRetSize++] = VMP_STYLE_EIGHT;
            abyStyles[byRetSize++] = VMP_STYLE_NINE;	
            abyStyles[byRetSize++] = VMP_STYLE_TEN;
			abyStyles[byRetSize++] = VMP_STYLE_THIRTEEN;
			abyStyles[byRetSize++] = VMP_STYLE_SIXTEEN;
			abyStyles[byRetSize++] = VMP_STYLE_TWENTY;
			break;
		default:
			break;
	}

    if (byArraySize >= byRetSize)
    {
        memcpy(pabyStyle, abyStyles, byRetSize);
    }
    byArraySize = byRetSize;
    return;

}

/*=============================================================================
函 数 名： IsConfFormatHD
功    能： 本会议是否为高清会议
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo   [in] 会议信息
返 回 值： BOOL32
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2007/12/19  4.0			张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsConfFormatHD(const TConfInfo &tConfInfo)
{
    BOOL32 bFormatHD = FALSE;
    u8 byVideoType = tConfInfo.GetMainVideoMediaType();
    if (MEDIA_TYPE_H264 != byVideoType)
    {
        return bFormatHD;
    }
    
    u8 byConfFormat = tConfInfo.GetMainVideoFormat();
    switch( byConfFormat )
    {
    case VIDEO_FORMAT_W4CIF:
    case VIDEO_FORMAT_HD720:
    case VIDEO_FORMAT_SXGA:
    case VIDEO_FORMAT_UXGA:
    case VIDEO_FORMAT_HD1080:
        bFormatHD = TRUE;
        break;
    default:
        break;
    }
    return bFormatHD;
}

/*=============================================================================
函 数 名： IsConfFormatOverCif
功    能： 本会议是否为D1或者高清会议，仅对H.264有效(仅判主视频)
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo   [in] 会议信息
返 回 值： BOOL32
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2008/03/11  4.5			顾振华                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsConfFormatOverCif( const TConfInfo &tConfInfo )
{
    u8 byVideoType = tConfInfo.GetMainVideoMediaType();
    if (MEDIA_TYPE_H264 != byVideoType)
    {
        return FALSE;
    }

    u8 byConfFormat = tConfInfo.GetMainVideoFormat();
    if ( byConfFormat == VIDEO_FORMAT_4CIF ||
         IsConfFormatHD(tConfInfo) )
    {
         return TRUE;
    }
    return FALSE;
}

/*=============================================================================
函 数 名： IsConfPermitVmp
功    能： 本会议是否允许画面合成
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo
返 回 值： BOOL32 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2008/4/2   4.0		周广程                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsConfPermitVmp( const TConfInfo &tConfInfo )
{
	BOOL32 bSupport = TRUE;
    /*
	if ( IsConfFormatHD(tConfInfo) )
	{
		bSupport = FALSE;
	}
    */
	return bSupport;
}

/*=============================================================================
 函 数 名： IsRollCallSupported
 功    能： 本会议是否支持会议点名
 算法实现： 
 全局变量： 
 参    数： const TConfInfo &tConfInfo   [in] 会议信息
 返 回 值： BOOL32
 ----------------------------------------------------------------------
 修改记录    ：
 日  期		 版本		修改人		走读人    修改内容
 2007/12/19  4.0		张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsRollCallSupported( const TConfInfo &tConfInfo )
{
    BOOL32 bSupported = TRUE;
    /*
    if ( IsConfFormatHD(tConfInfo) )
    {
        bSupported = FALSE;
    }
    */
    return bSupported;
}

/*=============================================================================
 函 数 名： IsMPWSupported
 功    能： 本会议是否支持多画面电视墙
 算法实现： 
 全局变量： 
 参    数： const TConfInfo &tConfInfo   [in] 会议信息
 返 回 值： BOOL32
 ----------------------------------------------------------------------
 修改记录    ：
 日  期		 版本		修改人		走读人    修改内容
 2007/12/19  4.0		张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsMPWSupported( const TConfInfo &tConfInfo )
{
    BOOL32 bSupported = FALSE;
    /*
    if ( IsConfPermitVmp(tConfInfo) )
    {
        bSupported = TRUE;
    }
    */
    return bSupported;
}

/*=============================================================================
函 数 名： IsVmpSupported
功    能： 
算法实现： 
全局变量： 
参    数： const TConfInfo &tConfInfo
返 回 值： BOOL32 
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
2008/4/2   4.0		周广程                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsVmpSupported( const TConfInfo &tConfInfo )
{
	BOOL32 bSupported = FALSE;
    if ( IsConfPermitVmp(tConfInfo) )
    {
        bSupported = TRUE;
    }
    return bSupported;
}

/*=============================================================================
 函 数 名： IsTVWallSupported
 功    能： 本会议是否支持电视墙
 算法实现： 
 全局变量： 
 参    数： const TConfInfo &tConfInfo   [in] 会议信息
 返 回 值： BOOL32
 ----------------------------------------------------------------------
 修改记录    ：
 日  期		 版本		修改人		走读人    修改内容
 2007/12/19  4.0		张宝卿                  创建
=============================================================================*/
BOOL32 CMcuPfmLmt::IsTVWallSupported( const TConfInfo &tConfInfo )
{
    BOOL32 bSupported = TRUE;
    if ( IsConfFormatOverCif(tConfInfo) )
    {
        bSupported = FALSE;
    }
    return bSupported;
}

/*=============================================================================
 函 数 名： IsMultiVidStreamSupported
 功    能： 本会议是否支持视频多速多格式。需要判断两路视频格式
 算法实现： 
 全局变量： 
 参    数： const TConfInfo &tConfInfo   [in] 会议信息
            u8 byMode = MODE_VIDEO       [in] 音频或视频,不支持MODE_BOTH
 返 回 值： BOOL32
 ----------------------------------------------------------------------
 修改记录    ：
 日  期		版本		修改人		走读人    修改内容
 2007/12/19  4.0		张宝卿                  创建
 2008/03/11  4.5        顾振华
=============================================================================*/
BOOL32 CMcuPfmLmt::IsMultiStreamSupported( const TConfInfo &tConfInfo, u8 byMode )
{
    BOOL32 bSupported = TRUE;
    
    /*
    if ( MODE_VIDEO != byMode && MODE_AUDIO != byMode )
    {
        OspPrintf( TRUE, FALSE, "[MultiStreamSup] unexpected mode.%d\n", byMode );
        return FALSE;
    }
    if ( byMode == MODE_VIDEO )
    {
        // 主格式视频
        if ( IsConfFormatOverCif(tConfInfo) )
        {
            return FALSE;
        }

        // 辅格式视频
        u8 byVideoType = tConfInfo.GetSecVideoMediaType();
        if (MEDIA_TYPE_H264 == byVideoType)
        {
            u8 byConfFormat = tConfInfo.GetSecVideoFormat();
            if ( byConfFormat != VIDEO_FORMAT_CIF )
            {
                return FALSE;
            }
        }          
    }
    */

    return bSupported;
}
/*=============================================================================
函 数 名： GetSelVmpCap
功    能： 获取最接近会议能力的vmp id及其能力
算法实现： 
全局变量： 
参    数： u8 abySelVmpIdx[]				[in] 
TPeriEqpStatus *ptStatus		[in] 
u8 bySelNum						[in]
u8 byMaxChnlNumByConf			[in]
u8 &byVmpCapChnnlNum			[out]
u8 &bySelVmpId					[out]
返 回 值： BOOL32
----------------------------------------------------------------------
修改记录    ：
日  期		版本		修改人		走读人    修改内容
12/9/2008				薛亮					
=============================================================================*/
BOOL32 CMcuPfmLmt::GetSelVmpCap(u8 abySelVmpIdx[], TPeriEqpStatus *ptStatus, u8 bySelNum, 
								u8 byMaxChnlNumByConf,u8 &byVmpCapChnnlNum, u8 &bySelVmpId)
{
	if( bySelNum == 0 )
	{
		return FALSE;
	}

	u8 byMaxEqpChnlNum = 0;
	u8 byMaxEqpChnlNumId = 0;
	u8 byMinNearConfChnlNum = MAXNUM_MPUSVMP_MEMBER +1; /*16+1;*/ // xliang [2/12/2009] 
	u8 byMinNearConfChnlNumId = 0;
	
	u8 bySelIdx = 0;
	u8 byCurEqpChnnlNum = 0;
	for(u8 byLoop = 0; byLoop < bySelNum; byLoop++)
	{
		bySelIdx = abySelVmpIdx[byLoop];
		byCurEqpChnnlNum = ptStatus[bySelIdx].m_tStatus.tVmp.m_byChlNum;
		
		if ( byCurEqpChnnlNum > byMaxEqpChnlNum )
		{
			// 通过遍历查找并记录所有设备中的能力最大值
			byMaxEqpChnlNum = byCurEqpChnnlNum;
			byMaxEqpChnlNumId = ptStatus[bySelIdx].GetEqpId();
		}
		if ( byCurEqpChnnlNum >= byMaxChnlNumByConf )
		{
			// 如果能力超过会议能力，记录满足中的最小值
			if ( byCurEqpChnnlNum < byMinNearConfChnlNum )
			{
				byMinNearConfChnlNum = byCurEqpChnnlNum;
				byMinNearConfChnlNumId = ptStatus[bySelIdx].GetEqpId();
			}
		}
	}

	if (byMinNearConfChnlNumId >= VMPID_MIN &&
		byMinNearConfChnlNumId <= VMPID_MAX)
	{
		byVmpCapChnnlNum = byMaxChnlNumByConf;
		bySelVmpId = byMinNearConfChnlNumId;
	}
	else if (byMaxEqpChnlNumId >= VMPID_MIN && 
		     byMaxEqpChnlNumId <= VMPID_MAX)
	{
		byVmpCapChnnlNum = byMaxEqpChnlNum;
		bySelVmpId = byMaxEqpChnlNumId;
	}
	else
	{
		pfmlog("[GetSelVmpCap] no find any vmp\n");
		return FALSE;
	}
// 	if (byMaxEqpChnlNum >= byMaxChnlNumByConf)
// 	{
// 		byVmpCapChnnlNum = byMaxChnlNumByConf;
// 		bySelVmpId = byMinNearConfChnlNumId;
// 	}
// 	else
// 	{
// 		byVmpCapChnnlNum = byMaxEqpChnlNum;
// 		bySelVmpId = byMaxEqpChnlNumId;
// 	}
	return TRUE;
}

#endif  //__MCUPFMLMT_H_



