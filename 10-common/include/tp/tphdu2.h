#ifndef _tphdu2_h__
#define _tphdu2_h__

//电视墙相关定义
#define HDU_MAX_LAYER			10	//HDU 层数
#define HDU_MAX_SLOT			7	//HDU 最大槽数
#define HDU_MAX_CHANNEL_NUM		2	//一个HDU2的最大通道数
#define HDU_MAX_NUM				HDU_MAX_LAYER*HDU_MAX_SLOT	//UMS的最大电视墙屏数

#define HDU_STYLE_MAX_ROW		8	//电视墙风格最大行
#define HDU_STYLE_MAX_COLUMN	56	//电视墙风格最大列
#define HDU_STYLE_MAX_NUM		56
#define HDU_MAX_VMP_SUBCHAN		4

#define HDU_MAX_UPDATE_FILE_NUM	16	//HDU升级支持的最大文件数
#endif