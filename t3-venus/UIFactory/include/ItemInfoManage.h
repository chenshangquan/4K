// ItemInfoManage.h: interface for the CItemInfoManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMINFOMANAGE_H__4AF3C20D_B7F1_4C4B_AF92_8C1F29E2869D__INCLUDED_)
#define AFX_ITEMINFOMANAGE_H__4AF3C20D_B7F1_4C4B_AF92_8C1F29E2869D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CItemInfoManage  
{
public:
	CItemInfoManage();
	virtual ~CItemInfoManage();
protected:
	/*
	 * 条目信息的路径\n 
	 */
	String m_strItemInfo;
};

#endif // !defined(AFX_ITEMINFOMANAGE_H__4AF3C20D_B7F1_4C4B_AF92_8C1F29E2869D__INCLUDED_)
