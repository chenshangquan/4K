// MsgDispatch.h: interface for the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
#define AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_

#pragma warning( disable : 4786 )	// 标识符名称超过255字节

#include <map>
#include <vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;


class CCallBackFunBase
{ 
public:
    //定义回调函数的格式
     virtual HRESULT operator() ( WPARAM wParam, LPARAM lParam ) = 0;
};

template<class T> class CMsgCallBackFun:public  CCallBackFunBase
{
public:
    //定义回调函数的格式
    typedef LRESULT (T::*MemberFunctionType)(  WPARAM wParam, LPARAM lParam  );
    
    // 构造的时候需要为函数赋值
    CMsgCallBackFun ( MemberFunctionType pFunc, T* pObject )
    {
         m_pObject = pObject;
         m_pFuc = pFunc ;
    }
    
    virtual HRESULT operator()( WPARAM wParam, LPARAM lParam )
    {
        return (m_pObject->*m_pFuc)( wParam, lParam);
    }
    
private:
    T* m_pObject;
    MemberFunctionType m_pFuc;	
};

 
typedef std::map< DWORD ,  vector< CCallBackFunBase * > > FuncMap;

class CMsgDispatch 
{
public:
	CMsgDispatch();
	virtual ~CMsgDispatch();
/**  注册全局函数
 *  @param[in] strName 函数所对应的名称 必须唯一
 *  @param[in] piFunc 函数指针，可以是静态函数，可以是成员函数等
 *  @return 是否成功
 */
	static bool RegFunc( DWORD dwMsgID, CCallBackFunBase* piFunc );

/**  反注册全局函数
 *  @param[in] dwMsgID 函数所对应的消息ID
 *  @return 是否成功
 */
    static bool UnRegFunc( DWORD dwMsgID , CCallBackFunBase* piFunc );
//	static bool UnRegFunc( DWORD dwMsgID);


   static bool SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam );

/**  执行函数
 *  @param[in] dwMsgID 函数所对应的消息ID
 *  @param[in]  
 *  @see IArgs
 *  @param[out] 
 *  @return 是否成功
 */
//	bool ExeFunc( DWORD dwMsgID, WPARAM wParam, LPARAM lParam );
protected:
	
    static FuncMap m_mapFuncs;
 
};

/*
* 注册全局函数、以类成员函数作为函数指针 \n
* dwMsgID 函数ID func 函数名 obj 类指针 objType 类类型
*/
#ifndef REG_MSG_HANDLER
#define REG_MSG_HANDLER( dwMsgID, func, obj, objType ) \
CMsgDispatch::RegFunc( dwMsgID, new CMsgCallBackFun<objType>( func, obj ) );
#endif 

 

/*
* 反注册全局函数 \n
* str 函数标示
*/
#ifndef UN_REG_MSG_HANDLER
#define UN_REG_MSG_HANDLER(  dwMsgID, func, obj, objType  ) CMsgDispatch::UnRegFunc( dwMsgID ,new CMsgCallBackFun<objType>( func, obj ) );
#endif


#endif