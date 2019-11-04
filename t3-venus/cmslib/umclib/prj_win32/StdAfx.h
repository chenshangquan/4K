// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CA20AA06_3C4A_4ADB_80AA_F3A5AD70863E__INCLUDED_)
#define AFX_STDAFX_H__CA20AA06_3C4A_4ADB_80AA_F3A5AD70863E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>

//#include "kdvtype.h"
//#include "osp.h"

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning (disable: 4503) 
//70-common
#include "evCmsLib.h"
#include "cmsconst.h"
#include "ospmsgrecver.h" 


 
//10-common
#include "tpsys.h" 
#include "tpstruct.h"
#include "ummessagestruct.h"
#include "eventoutumslogin.h"
#include "eventoutumstool.h"
#include "eventoutumsboard.h"
#include "eventoutumshdu2.h"
#include "eventoutumstool.h"
#include "eventoutumscfg.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumsrec.h"
#include "eventoutumscall.h"

//#include "cmsstruct.h"
#endif // !defined(AFX_STDAFX_H__CA20AA06_3C4A_4ADB_80AA_F3A5AD70863E__INCLUDED_)
