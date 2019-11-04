#ifndef _TPADDRMGR_H
#define _TPADDRMGR_H


#include "tpstruct.h"
#include "kdvtype.h"
#include "tptype.h"
#include "tplog.h"
#include <list>
#include <vector>





class CSipRegInfo
{
public:
	CSipRegInfo();
	
	virtual ~CSipRegInfo()
	{
		
	}
	void Clear();
	
	void RemoveAll( EmGetRegInfoType emType );
	void AddSipRegInfo( const TTPSipRegInfo &tSipRegInfo );
	void RemoveAllBak( EmGetRegInfoType emType );
	void AddSipRegInfoBak( const TTPSipRegInfo &tSipRegInfo );
	void Replace( EmGetRegInfoType emType );
	u16 GetPackTotalNum( EmGetRegInfoType emType );
	u16 GetPackTotalNumBak( EmGetRegInfoType emType );
	BOOL GetPack( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize );
	BOOL GetPackBak( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize );
	void OutputAll();
	
protected:
	
private:
	std::list<TTPSipRegInfo> m_tSipRegInfoList;     //保存包
	
	std::list<TTPSipRegInfo> m_tSipRegInfoList_Bak;     //保存备份包
};





//全局单件类,管理全局地址簿
class CTPAddrMgr
{
public:
	enum EmTPAddrMgrStatus
	{
		em_Idle,        
		em_Updating_CNS, //更新中
		em_Updating_UMS,
		em_Updating_ALL,
		em_EnableNty    //更新完成，通知
		
	};
	static CTPAddrMgr *GetInstance()
	{
		static CTPAddrMgr s_cInstance;
		return &s_cInstance;
	}

	virtual ~CTPAddrMgr()
	{

	}
	

	void AddOneUserNty( const TTPAddrNtyUser &tTPAddNtyUser );             //加入要通知的用户
	u16  GetUserNtyNum( );                                                 //获得所有用户总数
	BOOL GetUserNty( TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize );         //获得所有用户
	void AddOnePack( const TTPSipRegPackInfo &tPackInfo,
					 const TTPSipRegInfo &tSipRegInfo,
					 const EmGetRegInfoType &emType );                      //加入包,每次加入完成后需要CHECK状态，若为NTY则必须通知界面
	
	void ClearUserNty()														//清用户列表
	{
		m_tNtyUserList.clear();
	}

	EmTPAddrMgrStatus GetStatus()										   //是否可以请求全局信息
	{
		return m_emStatus;
	}

	void SetStatus( EmTPAddrMgrStatus emStatus )
	{
		m_emStatus = emStatus;
	}

	u16 GetPackTotalNum( EmGetRegInfoType emType )
	{
		return m_cSipRegInfo.GetPackTotalNum( emType );
	}

	BOOL GetPack( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize )
	{
		return m_cSipRegInfo.GetPack( emType, ptSipRegInfo, wSize );
	}
	void OutPutAll()
	{
		MsgPrintHintLog("EmStatus->%d\n",m_emStatus);
		m_cSipRegInfo.OutputAll();
	}

	BOOL IsEnableUpdateAndSetStatus( EmGetRegInfoType emType );

	BOOL IsEnableNtyAndSetStatus()
	{
		if( em_EnableNty == m_emStatus )
		{
			SetStatus( em_Idle );
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

protected:
	CTPAddrMgr()
	{
		Clear();
	}
	void Clear()
	{
		m_cSipRegInfo.Clear();
		m_tNtyUserList.clear();
		m_emStatus = em_Idle;
	}
	void StatusStrategy( EmGetRegInfoType emType );
private:
	CSipRegInfo m_cSipRegInfo;
	std::list<TTPAddrNtyUser> m_tNtyUserList;
	EmTPAddrMgrStatus m_emStatus;                        

};


//B2版本的全局地址薄管理UMS 使用
class CTPAddrMgrEx
{
public:
	CTPAddrMgrEx();
	~CTPAddrMgrEx();

public:
	static CTPAddrMgrEx& Instance();

public:
	//添加UMS 信息
	void		AddPack(const TRegPackInfoEx& tPackInfo, const TUmsRegPackEx& tRegInfo);
	//添加CNS 信息
	void		AddPack(const TRegPackInfoEx& tPackInfo, const TCnsRegPackEx& tRegInfo);
	//添加MT  信息
	void		AddPack(const TTPMtRegInfo& tMtInfo);
	//添加MCU 信息
	void		AddPack(const TTPMcuRegInfo& tMcuInfo);
	//添加用户
	void		AddUser(const TTPAddrNtyUser& tUser);
	void        AddUserForCns(const TTPAddrNtyUser& tUser);
	//删除用户
	void		DelUser(const TTPAddrNtyUser& tUser);

public:
	//获取CNS 数据包总量
	u16			GetCnsPackNum() const;
	//获取CNS 注册信息
	u16			GetCnsRegPack(TCnsRegPackEx* ptCnsInfo, u16 wSize);
	//获取UMS 数据包总量
	u16			GetUmsPackNum() const;
	//获取UMS 注册信息
	u16			GetUmsRegPack(TUmsRegPackEx* ptUmsInfo, u16 wSize);
	//获取MT 数据包总量
	u16			GetMtPackNum() const;
	//获取MT 注册信息
	u16			GetMtRegPack(TTPMtRegInfo* ptMtInfo, u16 wSize);
	//获取MCU 数据包总量
	u16			GetMcuPackNum() const;
	//获取MCU 注册信息
	u16			GetMcuRegPack(TTPMcuRegInfo* ptMcuInfo, u16 wSize);

public:
	//用户个数
	u16			GetUserNums() const;
	//获取用户
	u16			GetUserNty(TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize);
	//清理用户信息
	void		ClearUser();

public:
	//SIP 接收完成
	BOOL32		IsSipEnd() const;
	//GK  接收完成
	BOOL32		IsGkEnd() const;
	//清理SIP 信息
	void		ClearSipInfo();
	//清理GK 信息
	void		ClearGkInfo();

	//Add by tanxiaodong 213-08-07.
	//清理SIP中的CNS信息
	void       ClearCnsInfo();

	//清理SIP中的UMS信息
	void       ClearUmsInfo();
	//End to add.
	void       ClearGkInfoForCns();

private:
	BOOL32		m_bSipEnd;	//SIP 数据是否接收完
	BOOL32		m_bGkEnd;	//GK  数据是否接收完

	u16			m_wUseCount;	//用户信息使用次数 最多为2次，根据这个值来确定是否要清理当前的用户信息

	std::vector<TUmsRegPackEx>	m_umsInfo;	//ums注册信息
	std::vector<TCnsRegPackEx>	m_cnsInfo;	//cns注册信息
	std::vector<TTPMtRegInfo>	m_mtInfo;	//mt 注册信息
	std::vector<TTPMcuRegInfo>	m_mcuInfo;	//mcu注册信息

	std::vector<TTPAddrNtyUser>	m_userList;	//请求的用户列表
};



#endif