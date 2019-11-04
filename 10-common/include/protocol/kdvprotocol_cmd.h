#ifndef _PROTOCOL_CMD_H_
#define _PROTOCOL_CMD_H_

typedef void (* pfFun_Void)();
typedef void (* pfFun_U32_U32)(u32 dwparam, u32 dwparam1);
typedef void (* pfFun_U8)(u8 byParam);
typedef void (* pfFun_U16)(u16 wParam);
typedef void (* pfFun_S32)(s32 nparam);
typedef void (* pfFun_U32)(u32 dwparam);
typedef void (* pfFun_S32_S8)(s32 nparam, s8* lpparam);
typedef void (* pfFun_S32_S32)(int nparam,int nparam1);
typedef void (* pfFun_S32_U32)(int nparam,u32 dwparam);
typedef void (* pfFun_PS8)(s8* pchparam);

#ifdef WIN32
template <class TpFn>
HINSTANCE  LoadNImport(LPCSTR szDllName, LPCSTR szFName, TpFn &pfn)
{
	s8 achDllName[256] = {0};
	sprintf(achDllName, "%s.dll", szDllName);

	HINSTANCE hDll = LoadLibraryA(achDllName);
	if (hDll)
	{
		pfn = (TpFn)GetProcAddress(hDll, szFName);
		if (pfn)
			return hDll;
		FreeLibrary(hDll);
	}
	return NULL;
}
#else

#include <dlfcn.h>
#define HINSTANCE void*
template <class TpFn>
void* LoadNImport(const s8* pchDllName, const s8* pchFName, TpFn &pfn)
{
	s8 achDllName[256] = {0};
	sprintf(achDllName, "lib%s.so", pchDllName);
	void* hDll = dlopen(achDllName, RTLD_LAZY);
	if (hDll)
	{
		pfn = (TpFn)dlsym(hDll, pchFName);
		if (pfn)
			return hDll;
		dlclose(hDll);
	}
	return NULL;
}
#endif

/*************************************************************************************/
/*H323 Related Command Begin*/
/*************************************************************************************/
API void print323call()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdv323adapter", "print323call", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}


API void set323trace(u8 byLevel)
{
	pfFun_U8 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdv323adapter", "set323trace", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(byLevel);
}

API void kdv323help()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdv323adapter", "kdv323help", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void setstacklog(s32 nLevel, BOOL bFileLogOn)
{
	pfFun_S32_S32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdv323adapter", "setstacklog", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(nLevel, bFileLogOn);
}

/*************************************************************************************/
/*H323 Related Command End*/
/*************************************************************************************/


/*************************************************************************************/
/*SIP Related Command Begin*/
/*************************************************************************************/

API void sipmodulehelp()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipmodulehelp", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipmodulelogon(s32 nModule, s32 nLevel)
{
	pfFun_S32_S32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipmodulelogon", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(nModule, nLevel);
}

API void sipmodulelogoff()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipmodulelogoff", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void setsiplogcallid(u16 wCallId)
{
	pfFun_U16 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "setsiplogcallid", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(wCallId);
}

API void setsiplogalias(s8 *pAlias)
{
	pfFun_PS8 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "setsiplogcallid", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(pAlias);
}

API void sipshowcall()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipshowcall", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipshowcallid(u16 wCallId)
{
	pfFun_U16 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipshowcallid", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(wCallId);
}

API void sipshowreg()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipshowreg", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipmodulever()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipmodule2", "sipmodulever", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipadapterhelp()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "sipadapterhelp", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipadapterlogoff()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "sipadapterlogoff", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void sipadapterlogon(s32 nType)
{
	pfFun_S32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "sipadapterlogon", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(nType);
}

API void sipadapterver()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "sipadapterver", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void setsiptrace(u32 dwFlag = 0)
{
	pfFun_U32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "setsiptrace", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(dwFlag);
}

API void setstackloglevel(s32 nLevel = 0)
{
	pfFun_S32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "setstackloglevel", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(nLevel);
}

API void showsipstack()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("kdvsipadapter2", "showsipstack", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void bfcphelp()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcphelp", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void bfcplogon(s32 nLevel)
{
	pfFun_S32 pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcplogon", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun(nLevel);
}

API void bfcplogoff()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcplogoff", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void bfcpver()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcpver", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void bfcpcltshow()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcpcltshow", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}

API void bfcpsrvshow()
{
	pfFun_Void pfFun = NULL;
	HINSTANCE  hInstUser32 = LoadNImport("bfcp", "bfcpsrvshow", pfFun);
	if (!hInstUser32) 
	{
		return;
	}
	pfFun();
}
/*************************************************************************************/
/*SIP Related Command End*/
/*************************************************************************************/

#endif //_PROTOCOL_CMD_H_
