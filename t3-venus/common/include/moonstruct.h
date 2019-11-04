// moonstruct.h: interface for the moonstruct class.
//
//////////////////////////////////////////////////////////////////////
#include "tpstruct.h"
//#include "cmsconst.h"
#ifndef _h_moonstruct_h__
#define _h_moonstruct_h__

//µÇÂ½ÐÅÏ¢
typedef struct tagCamLoginInfo
{
	u32     dwIp;
	u16     nPort;
	tagCamLoginInfo()
	{
		dwIp = 0;
		nPort = 0;
	}
}TCamLoginInfo;

#endif 
