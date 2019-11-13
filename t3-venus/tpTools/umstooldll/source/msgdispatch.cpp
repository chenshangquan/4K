// MsgDispatch.cpp: implementation of the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgDispatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


FuncMap CMsgDispatch::m_mapFuncs  ;

CMsgDispatch::CMsgDispatch() 
{

}

CMsgDispatch::~CMsgDispatch()
{

}

bool CMsgDispatch::UnRegFunc( DWORD dwMsgID , CCallBackFunBase* piFunc )
{
    FuncMap::iterator itr =	m_mapFuncs.find( dwMsgID );
    if ( itr != m_mapFuncs.end() )
    {
        vector<CCallBackFunBase * > VcPfun = itr->second;
        vector<CCallBackFunBase * >::iterator itPfun = VcPfun.begin();
        while(  itPfun != VcPfun.end() )
        {
            if ( * itPfun == piFunc )
            {  
               // TRACE( "CFuncManage::RegFunc 该处理函数已经存在 dwMsgID = " + dwMsgID );
                VcPfun.erase(itPfun) ;
                return false;
            }
            itPfun ++;
          }
        
        return true;
    }
    //LOGEVENT( "CMsgDispatch::UnRegFunc 未找到对应函数 dwMsgID = " + dwMsgID );
    return false;
}

bool CMsgDispatch::RegFunc ( DWORD dwMsgID, CCallBackFunBase* piFunc )
{
      FuncMap::iterator itr =	m_mapFuncs.find( dwMsgID );
      if ( itr != m_mapFuncs.end() )
      {    
          vector<CCallBackFunBase * >::iterator itPfun = itr->second.begin();
          while(  itPfun != itr->second.end() )
          {
              if ( *itPfun == piFunc )
              {  
                //  TRACE( "CFuncManage::RegFunc 该处理函数已经存在 dwMsgID = %d" , dwMsgID );
                  return false;
              }
              itPfun ++;
          }
       
          itr->second.push_back( piFunc );
         
          //TRACE( "\n[CFuncManage::RegFunc] dwMsgID =%d , pFun=%d\n" , dwMsgID ,piFunc);
          return false;
      }
   
    vector<CCallBackFunBase * > VcPfun;
    VcPfun.push_back(piFunc );
    m_mapFuncs.insert( FuncMap::value_type( dwMsgID, VcPfun ) );
  //  TRACE( "\n[CFuncManage::RegFunc] dwMsgID = %d, pFun=%d\n" , dwMsgID ,piFunc);
    return true;
}

 
bool CMsgDispatch::SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam ) 
{
    bool re = false;
    FuncMap::iterator itr = m_mapFuncs.find( dwMessage );
    if ( itr != m_mapFuncs.end() )
    {   
        re = true;
        vector<CCallBackFunBase * >::iterator itPfun =  itr->second.begin();
         while(  itPfun != itr->second.end() )
         {   
			 //  TRACE("\n[CMsgDispatch::SendMessage] msgID=%d, pFun=%d\n",dwMessage,**itPfun);
			 
             (**itPfun)( wParam, lParam );
             itPfun ++; 
		 }
		 
    } 
    
    return re;
}




 