#ifndef _UMM_H_
#define _UMM_H_
#include "ummessagestruct.h"
//#include "mtutilscharset.h"
//#include "mtmacro.h"
#include "protocolcommonpublic.h"

#define VER_UM (const char *)"kdvum.40.06.02.131008"

#define AID_UMSERVER                    236
#define MAX_MSG_BUFF_SIZE               (64*1024)

// 定义统一移到头文件来 [pengguofeng 5/7/2013]
#if defined( WIN32 )    /* WIN32 */
#define PATH_DATA			( LPCSTR )"data"	///< 信息文件路径
#elif defined( VXWORKS_SIMU )
#define PATH_DATA			( LPCSTR )"data"	///< 信息文件路径
#elif defined(_LINUX_)
#define PATH_DATA			( LPCSTR )"/usr/conf"	///< 信息文件路径
#else                   /* vxWorks */
#define PATH_DATA			( LPCSTR )"/data"	///< 信息文件路径
#endif

/// 编码方式 [pengguofeng 4/22/2013]
#define ENCODE_GBK						0
#define ENCODE_UTF8						1


#define USERINFOFILENAME				( LPCSTR )"login.usr"  ///<  文件名
#define UM_FILEHEAD						(const s8*)"kdvum"       ///<  文件头
#define UM_VER							(u32)20130422              ///<  版本号
#define MAX_FILEHEAD_LEN				32
#ifndef KDVTYPE_LEGACY_H
#define USERINFO_MEMBERNUM				(u8)10			///<  CUserFullInfo的成员个数 [pengguofeng 4/24/2013]
#else
#define USERINFO_MEMBERNUM				(u8)8
#endif
//////////////////////////////////////////////////////////////////////////

/// 枚举定义
///<  使用说明:
///<  emType[u8] + emBufLen[u32] + emBuf[s8* ]
///<  允许使用的范围为1~254 [pengguofeng 5/6/2013]
enum emType
{
	emUmStart = (u8)0,	//禁止使用的值
	emUserInfo,
	//以下留待扩展，最大限到254
	emEnd
};

class PROTO_API CUsrManage
{
public:

	CUsrManage(); ///< 默认构造
	/**
	* \brief            构造函数 
	* \param[in]        acFilePath： 保存目录，仍沿用以前的宏  不需要修改               
    * \param[in]        achFileName: 保存的文件名，仍沿用以前的宏 不需要修改            
    * \param[in]        byEncoding:  视当前MCU/MT平台所使用的编码方式 自己设定          
    * \param[in]        bIsMcu    :  仅MCU平台需要设成TRUE,其他(如MT)使用默认的FALSE即可
	*/
	CUsrManage( u8* pbyFilePath, u8* pbyFileName = NULL, u8 byEncoding = ENCODE_GBK, BOOL32 bIsMcu = FALSE); ///< 带存储用户信息文件路径
	~CUsrManage();
private:
	u32 m_dwError; ///< 消息错误码
	CUserFullInfo m_acUsrAllMembers[MAX_USERNUM]; ///< 用户列表
	u8  m_byUsrNum; ///< 用户个数
	char  m_achCurrentPath[256];///< 存储用户信息文件路径
	char  m_achFileName[MAX_UMFILENAME_LEN];   ///< 老版本存储保存用户信息的文件名
	char  m_achCurFile[MAX_UMFILENAME_LEN];    ///< 当前存储用户信息的新文件名
    s8 m_achMsgBuff[MAX_MSG_BUFF_SIZE];
    BOOL32 m_bSingle;
	u8	m_byPlatEncoding;                      ///< 平台编码方式:使用上面宏定义 [pengguofeng 4/22/2013]
	u8	m_byFileEncoding;						///< 文件编码方式：只在开始的时候读过一回
	u8  m_byEmTypeNum;							///< emtype数量
	u8  m_byIsMcu;								///<  mcu平台会用discription的特殊字段 [pengguofeng 7/15/2013]
	u32 m_dwMaxGuid;                           ///< 记录当前最大的guid；guid的规则是一直递增，获取一个新guid的时候，对m_dwMaxGuid+1，然后与所有用户的guid比较没有相同的则成功，否则再加一再比较

public:
	CUserFullInfo m_usrCurLogin; ///< 当前登录的用户
	//init and quit 
private:
	void	Reset(); ///< 清空所有用户,包括管理员
protected:
	BOOL32 WriteAllUserBackToFile();///< 所有用户信息写入文件
	// lang [pengguofeng 4/22/2013]
	void SetPlatEncoding( const u8 &byEncoding = ENCODE_GBK); ///< 设置平台编码方式
	u8   GetPlatEncoding(void);
	void SetFileEncoding(const u8 &byEncoding = ENCODE_GBK);
	u8   GetFileEncoding(void);
	void SetEmTypeNum(const u8 &byEmTypeNum);
	u8   GetEmTypeNum();
	void WriteUserInfo(FILE *fp);   ///< 将用户信息写入文件，自用接口
	void ReadUserInfo(FILE *fp);    ///< 从文件中解析用户信息，自用接口
	u32  GetBufLen();
	u32  GetHeadLen();
	void TransEncoding(); ///<  转码 [pengguofeng 4/22/2013],如果不带参数，则需要保存至成员中

	void UmPrint(s8 *pszFmt, ...);
	/// operate
public:	
    void SetSingle(BOOL32 bSingle); ///< 是否单用户

    BOOL32 GetAllUserFromFile();	///< 从文件中读入所有用户信息

    s32 GetUserNum(){return m_byUsrNum;}
    /// 获取第nIndex用户信息， nIndex从0开始
    BOOL32 GetUserFullInfo(CUserFullInfo* pcUserInfo, s32 nIndex);


   /**
	* \brief            添加用户记录，保证添加的记录的唯一性和记录内容的合法性 
	* \param[in]        newusr：新加入的用户记录
	* \return           BOOL32, TRUE:添加的记录与记录数组中的记录内容无重复&&记录内容合法&&容量允许&&操作权限允许,且生成此用户的guid号码  or FALSE
	*/
	BOOL32 AddUser(CUserFullInfo* pcNewusr); 


   /**
	* \brief            删除一个用户记录
	* \param[in]        oldinfo：待删除的记录
	* \return           BOOL32, TRUE:记录存在&&操作权限允许&&用户名不为admin  or FALSE
	*/
	BOOL32 DelUser(CUserFullInfo* pcOldinfo);///< 删除一个用户


   /**
	* \brief            从内容和文件中删除所有的用户记录（admin用户不会被删除）
	* \return           BOOL32, TRUE:操作权限允许  or FALSE
	*/
	BOOL32 DelAllMembers();///< 删除所有用户


   /**
	* \brief            修改记录信息，记录名不可修改，需要修改记录名需要首先删除然后再创建 
	* \param[in]        newinfo ：修改的记录信息
	* \return           BOOL32, TRUE:记录存在&&不是用户名为admin的记录&&操作权限允许  or FALSE
	* \notice           增加了唯一性检查，名字和guid都对应才会操作
	*/
	BOOL32 ModifyInfo(CUserFullInfo* pcNewinfo);

	BOOL32 CheckLoginValid(CLoginRequest* pcCurusr);///< 检查当前登录用户信息


   /**
	* \brief            获取所有用户信息，向请求者发送所有用户信息列表，每个回应（response）消息 \
	* \                 最多有15条用户信息记录，超过部分采用多次回应的方法
	* \param[in]        pcMsg ：获取用户信息的请求消息
	* \return           BOOL32, TRUE  or FALSE
	*/
	BOOL32 GetAllUser(CTiMessage* pcMsg); ///< 得到所有用户信息


   /**
	* \brief            显示版本或是显示所有用户信息列表
	* \param[in]        cmdcode：命令模式
	*/
	void CmdLine(int nCmdcode); ///< 命令显示信息


   /**
	* \brief            设置地址簿的装载和存储的文件，当前地址簿的所有用户记录首先都被清除，然后再从 \
	* \                 acFilePath文件中读入新的用户数据，以后的用户记录操作都针对该文件
	* \param[in]        acFilePath：载入和存储用户记录的文件名
	*/
	void SetPath(char* pchFilePath); ///< 设置保存文件路径

	u16 GetLastError() ///< 当前操作的错误码
	{
		return (u16)m_dwError;
	}
	void TestDelAllUser(); ///< 集成测试删除所有用户

	/// 读文件的固定信息 [pengguofeng 5/9/2013]
	void ReadFile();  ///< 文件从成员变量里找
	BOOL32 IsMatchFileHead(FILE *fp, const s8 *pFileHead = NULL);
	void WriteFileHead(FILE *fp, const s8 *pFileHead = NULL);
	BOOL32 IsMatchSoftVer(FILE *fp, const u32 &dwVer = 0);
	void WriteSoftVer(FILE *fp, const u32 &dwVer = 0);
	void ReadFileAttr(FILE *fp);
	void WriteFileAttr(FILE *fp);
	void SkipUnknownType(FILE *fp);
#ifndef KDVTYPE_LEGACY_H
	u32 CreateNewUserGuid(); ///< 生成新的用户guid
	void UpdateMaxGuid();
#endif
	/// message
private:
	void OnLigIn(CTiMessage* pcMsg);
	void OnAddUser(CTiMessage* pcMsg);
	void OnDelUser(CTiMessage* pcMsg);
	void OnModifyInfo(CTiMessage* pcMsg);
	void OnGetAllMembers(CTiMessage* pcMsg);
	void DisplayMenu();
	void OnDelAllMembers(CTiMessage* pcMsg);
	
	/// interface
public:
	void ShowAll();///< 命令所有用户信息
	void ProcessMsg(CTiMessage* pcMsg);
	void TransferToOldFile(void); ///<  转换版本接口 [pengguofeng 4/24/2013]
}
#ifdef _VXWORKS_
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;

PROTO_API BOOL32 InitUserManage();

#endif
