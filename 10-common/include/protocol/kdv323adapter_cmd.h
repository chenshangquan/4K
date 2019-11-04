#ifndef _H323ADAPTER42_CMD_H_
#define _H323ADAPTER42_CMD_H_

typedef void (* pfFun_Void)();
typedef void (* pfFun_U32_U32)(u32 dwparam, u32 dwparam1);
typedef void (* pfFun_U8)(u8 byParam);
typedef void (* pfFun_S32)(s32 nparam);
typedef void (* pfFun_U32)(u32 dwparam);
typedef void (* pfFun_S32_S8)(s32 nparam, s8* lpparam);
typedef void (* pfFun_S32_S32)(int nparam,int nparam1);
typedef void (* pfFun_S32_U32)(int nparam,u32 dwparam);

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

void* LoadNImport(const s8* pchDllName, const s8* pchFName, TpFn &pfn)
{
	s8 achDllName[256] = {0};
	sprintf(achDllName, "lib%s.so", pchDllName);
	void* hDll = dlopen(achDllName, RTLD_LAZY);
	if (hDll)
	{
		pfn = (TpFn)dlsym(hDll, szFName);
		if (pfn)
			return hDll;
		dlclose(hDll);
	}
	return NULL;
}
#endif

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




#endif //_H323ADAPTER42_CMD_H_
