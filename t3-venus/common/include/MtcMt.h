#ifndef __MTCMT_H__
#define __MTCMT_H__

//#include "vccommon.h"		// 终端控制业务
#include "mtstruct.h"

class CMtcMt
{
public:
    CMtcMt(){ SetMt(0, 0, 0, _T(""), _T(""));}
    CMtcMt(u16 wMcuMtId){ SetMt(wMcuMtId); }
    CMtcMt(u32 dwMcuMtId){ SetMt(dwMcuMtId); }

	u8          m_byMtId;	// 终端ID
	u8          m_byMcuId;	// McuID
	u8          m_byType;	// 终端类型
	CString     m_strAlias;	// 终端别名
	CString     m_strE164Name;	// E164号码

    u16 GetMcuMtId16() const { return MAKEWORD(m_byMtId, m_byMcuId); }
    u32 GetMcuMtId32() const { return (u32)(MAKEWPARAM(GetMcuMtId16(), 0)); }

	void SetMt(u8 byMtId, u8 byMcuId, u8 byType,
		const CString& strAlias,
		const CString& strE164Name)
	{
		m_byMtId = byMtId;
		m_byMcuId = byMcuId;
		m_byType = byType;
		m_strAlias = strAlias;
		m_strE164Name = strE164Name;
	};
    /*函数名： SetMt
    功    能： 
    参    数： u16 wMcuMtId
    返 回 值： void 
    说    明： */
	void SetMt(u16 wMcuMtId)
	{
		// 有时需借用16比特数据类型传递McuId和MtId
		SetMt(LOBYTE(wMcuMtId), HIBYTE(wMcuMtId), 0, _T(""), _T(""));
	};
    /*函数名： SetMt
    功    能： 
    参    数： u32 dwMcuMtId
    返 回 值： void 
    说    明： */
	void SetMt(u32 dwMcuMtId)
	{
		// 有时需借用32比特数据类型传递McuId和MtId
		SetMt(LOWORD(dwMcuMtId));
	};
    /*函数名： SetMt
    功    能： 
    参    数： TMtId tMtId
    返 回 值： void 
    说    明： */
	inline void SetMt(const TMtId &tMtId)
	{
		m_byMcuId = tMtId.byMcuNo;
		m_byMtId = tMtId.byTerNo;
	}
    /*函数名： SetMt
    功    能： 
    参    数： TMtInfo tMtInfo
    返 回 值： void 
    说    明： */
    inline void SetMt(const TMtInfo &tMtInfo)
    {
		m_byMcuId = tMtInfo.tLabel.byMcuNo;
        m_byMtId = tMtInfo.tLabel.byTerNo;
        m_strAlias = tMtInfo.achAlias;
    }
	void Clear(){SetMt(0, 0, 0, _T(""), _T(""));}

    /*函数名： operator==
    功    能： 
    参    数： const CMtcMt &cMt
    返 回 值： BOOL 
    说    明： */
	BOOL operator==(const CMtcMt &cMt) const
	{
		return (m_byMcuId == cMt.m_byMcuId && m_byMtId == cMt.m_byMtId);
	}

    /*函数名： operator!=
    功    能： 
    参    数： const CMtcMt &cMt
    返 回 值： BOOL 
    说    明： */
	BOOL operator!=(const CMtcMt &cMt) const
	{
		return !((*this) == cMt);
	}
    /*函数名： operator=
    功    能： 
    参    数： const CMtcMt &cMt
    返 回 值： CMtcMt& 
    说    明： */
	CMtcMt& operator=(const CMtcMt &cMt)
	{
		SetMt(cMt.m_byMtId, cMt.m_byMcuId, cMt.m_byType,
			cMt.m_strAlias, cMt.m_strE164Name);
		return (*this);
	}
	
    /*函数名： operator=
    功    能： 
    参    数： const TMtInfo &tMtInfo
    返 回 值： CMtcMt& 
    说    明： */
	CMtcMt& operator=(const TMtInfo &tMtInfo)
	{
		SetMt(tMtInfo);
		return (*this);
	}

    /*函数名： Print
    功    能： 
    参    数： 
    返 回 值： void 
    说    明： */
	void Print() const
	{
		OspPrintf(TRUE, FALSE, "<McuId = %d, MtID = %d> MtAlias = %s\n", 
			m_byMcuId, m_byMtId, m_strAlias);
	}
	
}; // CMtcMt


//定义一些临时的变量
#define MT_ADDRENTRY_NUM		1600 //callin callout missed 5*userdef(每组192)
#define MT_ADDRMULTISET_NUM		16	
#define CTRL_POLL_MAXNUM		128

//定义可能用到的宏
#define ASSIGN_MTINFO_WITH_CMTCMT(tMt, cMtcMt)				\
	tMt.tLabel.byMcuNo = cMtcMt.m_byMcuId;					\
	tMt.tLabel.byTerNo = cMtcMt.m_byMtId;					\
	memset(tMt.achAlias, 0, sizeof(TMtInfo) );				\
	memcpy(tMt.achAlias, (LPCTSTR)cMtcMt.m_strAlias, min( MT_MAX_NAME_LEN, cMtcMt.m_strAlias.GetLength() ) );\
	tMt.achAlias[MT_MAX_NAME_LEN] = '\0';				


#endif


