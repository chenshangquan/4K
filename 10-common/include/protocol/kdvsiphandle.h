#ifndef __KDVSIPHANDLE_H__
#define __KDVSIPHANDLE_H__

#include <protocolcommonpublic.h>

typedef void* TSdpHandle;
typedef void* TSipPxyReservedHandle;
typedef void* TSipUacHandle;
typedef void* TSipUasHandle;

typedef struct PROTO_API tagSipPxyHandle
{
	TSdpHandle m_hSdp;
	TSipPxyReservedHandle m_hReserved;

	void Clear()
	{
		m_hSdp = NULL;
		m_hReserved = NULL;
	}
	tagSipPxyHandle()
	{
		Clear();
	}

} TSipPxyHandle;

typedef TSdpHandle* LpTSdpHandle;
typedef TSipPxyReservedHandle* LpTSipPxyReservedHandle;
typedef TSipPxyHandle* LpTSipPxyHandle;
typedef TSipUacHandle* LpTSipUacHandle;
typedef TSipUasHandle* LpTSipUasHandle;

#endif