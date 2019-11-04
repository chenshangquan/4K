/*****************************************************************************
模   块   名: G.729自适应码本搜索及其增益模块
文   件   名: adaptive_codebook.h
相 关  文 件: 自适应码本搜索及其增益的五篇设计文档
文件实现功能: G.729自适应码本搜索及其增益的计算
版        本: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
修 改 记 录:
日       期      版本        修改人      修改内容
2005/06/13       1.0         宋  兵      创    建
******************************************************************************/
#ifndef ADAPTIVE_CODEBOOK_H
#define ADAPTIVE_CODEBOOK_H

s16 s16EncodePitch( s16 s16PitchInt, s16 s16PitchFrac, s16 *ps16PitchMinSearch,
				    s16 *ps16PitchMaxSearch, s16 s16SubframeFlag );
void DecodePitch( s16 *ps16PitchInt, s16 *ps16PitchFrac, 
				 s16 s16PitchIndex, s16 s16SubframeFlag );
s16 s16ParityPitch( s16 s16PitchIndex );
s16 s16CheckParityPitch( s16 s16PitchIndex, s16 s16PitchParity );
s16 s16GainPitch( s16 *ps16Target, s16 *ps16AdaptCodebkFiltered,
				  s16 *ps16CorrGain, s16 s16SubframLen);

#endif