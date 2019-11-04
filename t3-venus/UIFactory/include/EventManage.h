// EventManage.h: interface for the CEventManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_)
#define AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
* 类	名：CEventManage
* 功    能：全局默认事件的一个管理类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CEventManage : public Singleton< CEventManage >
{
public:
	CEventManage();
	virtual ~CEventManage();

};

#endif // !defined(AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_)
