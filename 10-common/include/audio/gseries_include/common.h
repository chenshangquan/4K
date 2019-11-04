/*****************************************************************************
模   块   名: common
文   件   名: common.h
相 关  文 件: 
文件实现功能: G系列中通用的函数
版        本: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
修 改 记 录:
日       期      版本        修改人      修改内容
 2005/05/25      1.0         宋  兵      创    建

******************************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include "algorithmtype.h"



void Copy(
  s16 x[],      /* (i)   : input vector   */
  s16 y[],      /* (o)   : output vector  */
  s16 L         /* (i)   : vector length  */
);
l32 Dot_Product(      /* (o)   :Result of scalar product. */
       s16   x[],     /* (i)   :First vector.             */
       s16   y[],     /* (i)   :Second vector.            */
       s16   lg       /* (i)   :Number of point.          */
);
/*--------------------------------------------------------------------------*
 *       LTP constant parameters                                            *
 *--------------------------------------------------------------------------*/

#define UP_SAMP         3
#define L_INTER10       10
#define FIR_SIZE_SYN    (UP_SAMP*L_INTER10+1)

void Pred_lt_3(
  s16   exc[],       /* in/out: excitation buffer */
  s16   T0,          /* input : integer pitch lag */
  s16   frac,        /* input : fraction of lag   */
  s16   L_subfr      /* input : subframe size     */
);
void Cor_h_X(
     s16 h[],        /* (i) Q12 :Impulse response of filters      */
     s16 X[],        /* (i)     :Target vector                    */
     s16 D[],         /* (o)     :Correlations between h[] and D[] */
 	 s16 s16Len
                        /*          Normalized to 13 bits            */
);
#endif // endif GMATH_H

