/*****************************************************************************
模块名      : GkcTestStruct
文件名      : GkcTestStruct.h
相关文件    : GkcTestStruct.cpp
              
文件实现功能: 定义便于GkConsole使用的数据结构
作者        : 陈洪斌
模块版本    : V4.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期(n/m/d)      文件版本        修改人      修改内容
2005/08/10         0.1            陈洪斌      创建
******************************************************************************/
#ifndef GKCSTRUDEFINE_H_2005_08_10
#define GKCSTRUDEFINE_H_2005_08_10


//为了上层方便使用,封装实体认证策略(方式)的操作
class CGkAuthMothod
{
public:
    CGkAuthMothod()
    {
        m_dwGkAuthMothod = 0;
    };
public:
    //设置认证策略的32位值
    void SetAuthMethod(u32 dwGkAuthMothod)
    {
        m_dwGkAuthMothod = dwGkAuthMothod;
    }

    //获取认证策略的32位值
    u32 GetAuthMethod() const
    {
        return m_dwGkAuthMothod;
    }

    //设置不需要认证
    void SetNotAuth()
    {
        m_dwGkAuthMothod = 0;
    };
    
    //是否需要认证
    bool IsNeedAuth() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthIPForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow
            || m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid
            || m_dwGkAuthMothod & emAuthMethod_AuthPassword
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    
    //设置ip认证允许生效
    void SetAuthIPAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPAllow;       
    };

    //设置ip认证禁止生效
    void SetAuthIPForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthIPAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthIPForbid;
    };
    
    //是否ip认证允许生效
    bool IsAuthIPAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //是否ip认证禁止生效
    bool IsAuthIPForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthIPForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //设置实体认证允许生效
    void SetAuthAliasAllow()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasForbid;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasAllow;       
    };

    //设置实体认证禁止生效
    void SetAuthAliasForbid()
    {
        m_dwGkAuthMothod &= ~emAuthMethod_AuthAliasAllow;
        m_dwGkAuthMothod |= emAuthMethod_AuthAliasForbid;
    };
    
    //是否实体认证允许生效
    bool IsAuthAliasAllow() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasAllow) 
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    //是否实体认证禁止生效
    bool IsAuthAliasForbid() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthAliasForbid) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //设置密码认证
    void SetAuthPassword()
    {
        m_dwGkAuthMothod |= emAuthMethod_AuthPassword;
    };
 
    //是否密码认证
    bool IsAuthPassword() const
    {
        if(m_dwGkAuthMothod & emAuthMethod_AuthPassword) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
private:
    u32 m_dwGkAuthMothod; //认证策略32位值
};





#endif //GKCSTRUDEFINE_H_2005_08_10