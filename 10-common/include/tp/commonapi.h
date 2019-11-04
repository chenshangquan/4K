#ifndef _h_commonapi_h__
#define _h_commonapi_h__


#include "tpstruct.h"

class CComInterface
{
private:
	static BOOL32 IsConfTempSameLvl(const TUmsConfBase& tConfBasse);
	static u16 CheckAndProcConfTempFormat( TUmsVidFormat atVidFormat[], u16 wNum );
public:
	
	static u16 GetNeedBasNum(TPIN const TUmsConfBase& tConfBasse);
	static u16 GetNeedAudBasNum(TPIN const TUmsConfBase& tConfBasse);
};



#endif //_h_commonapi_h__