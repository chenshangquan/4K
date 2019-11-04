/*****************************************************************************
模块名      : VPSS_DRV_API
文件名      : vpss_api_def.h
相关文件    : 
文件实现功能: 公共头文件定义
作者        : 张方明
版本        : V1.0  Copyright(C) 2011-2019 KEDACOM, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
03/29/2011  1.0         张方明      创建
******************************************************************************/

#ifndef __VPSS_API_DEF_H
#define __VPSS_API_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

//#define VPS_API_DBG_EN

/* 宏定义 */
#ifdef VPS_API_DBG_EN
# define VPS_API_DBG(fmt, args...) \
    do { \
        printf("[VPS_API_DBG]: " fmt, ## args); \
    } while (0)
#else
# define VPS_API_DBG(fmt, args...)
#endif

#define VPS_API_PRT(fmt, args...) \
    do { \
        printf("[VPS_API]: " fmt, ## args); \
    } while (0)

#define VPS_API_ERR(fmt, args...) \
    do { \
        printf("[VPS_API_ERR]%d:%s->" fmt, __LINE__, __FUNCTION__, ## args); \
    } while (0)


#ifdef __cplusplus
}
#endif

#endif /* __VPSS_API_DEF_H */
