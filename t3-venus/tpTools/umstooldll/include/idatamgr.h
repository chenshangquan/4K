// idatamgr.h: interface for the IDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDATAMGR_H__00CFFFB4_DB5F_45BC_8CC5_7DE1C7CC21AA__INCLUDED_)
#define AFX_IDATAMGR_H__00CFFFB4_DB5F_45BC_8CC5_7DE1C7CC21AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IDataMgr  
{
protected:
	IDataMgr();
	virtual ~IDataMgr();


public:
	virtual TplArray<CUserFullInfo> GetUserListData() = 0;

protected:
	TplArray<CUserFullInfo> m_tplUserList;


};

#endif // !defined(AFX_IDATAMGR_H__00CFFFB4_DB5F_45BC_8CC5_7DE1C7CC21AA__INCLUDED_)
