/*****************************************************************************
模   块   名: 基音分析模块
文   件   名: pitch.h
相 关  文 件: 
文件实现功能: 基音分析的头文件
版        本: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
修 改 记 录:
日       期      版本        修改人      修改内容
2005/05/23       1.0         宋  兵      创    建
******************************************************************************/
#ifndef PITCH_H
#define PITCH_H



s16 s16PitchOpen(s16 *ps16SpeechWeighted,s16 s16FrameLen,s16 s16PitchMax);
s16 s16PitchClose(s16 *ps16PitchFrac,s16 *ps16Excitation,s16 *ps16Target,
				  s16 *ps16Impulse, s16 s16SubFrameLen,s16 s16Pitch0Min, 
				  s16 s16Pitch0Max,s16 s16Subframe);

#endif