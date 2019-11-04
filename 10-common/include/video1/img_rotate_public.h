/******************************************************************************
模块名      ：img_rotate_public
文件名      ：img_rotate_public.h
相关文件    ：
文件实现功能：定义图像旋转参数结构体
作者        ：赵波
版本        ：1.0
-------------------------------------------------------------------------------
修改记录:
日  期            版本            修改人        走读人      修改内容
2012/03/14        1.0             赵波                        创建
******************************************************************************/
#ifndef _IMG_ROTATE_PUBLIC_H_
#define _IMG_ROTATE_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define IMAGE_MIRROR -1

//图像旋转初始化参数
typedef struct
{
    l32 l32SrcWidth;    //输入图像的宽度
    l32 l32SrcHeight;   //输入图像的高度
       
    l32 l32DstWidth;    //目标图像底图的宽度(必须大于等于l32Width)
    l32 l32DstHeight;   //目标图像底图的高度(必须大于等于l32Height)

    l32 l32YUVType;     //输入图像的图像类型，为YUV420或者YUV422P

    l32 l32BgYColor;    //处理后非图像的填充颜色Y分量,目前TI版本不支持背景填充
    l32 l32BgUColor;    //处理后非图像的填充颜色U分量,目前TI版本不支持背景填充
    l32 l32BgVColor;    //处理后非图像的填充颜色V分量,目前TI版本不支持背景填充
    
    l32 l32Angel;       //图像旋转角度。镜像翻转为IMAGE_MIRROR。

    u32 u32Reserved;
}TImageRotateParam;


//图像旋转模块状态结构体
#define TImageRotateStatusParam TImageRotateParam

//图像旋转输入参数
typedef struct
{
    u8 *pu8SrcY;    //源图像Y分量地址
    u8 *pu8SrcU;    //源图像U分量地址(如果YUV地址连续。可以将pu8SrcU和pu8SrcV置为NULL)
    u8 *pu8SrcV;    //源图像V分量地址(如果YUV地址连续。可以将pu8SrcU和pu8SrcV置为NULL)

    l32 l32SrcYStride;  //源图像的Y步进值
    l32 l32SrcUVStride; //源图像的UV步进值(l32SrcYStride的一半，不需要填写)

    u32 u32Reserved;
}TImageRotateInput;

//图像旋转输出参数
typedef struct
{
    u8 *pu8DstY;    //目的图像的Y分量地址
    u8 *pu8DstU;    //目的图像的U分量地址(如果YUV地址连续。可以将pu8DstU和pu8DstV置为NULL)
    u8 *pu8DstV;    //目的图像的V分量地址(如果YUV地址连续。可以将pu8DstU和pu8DstV置为NULL)

    l32 l32DstYStride;  //目的图像的Y步进值(输出图像的stride须等于输出图像的宽度)
    l32 l32DstUVStride; //目的图像的UV步进值(l32DstYStride的一半，不需要填写)

    u32 u32Reserved;
}TImageRotateOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_ROTATE_PUBLIC_H_
