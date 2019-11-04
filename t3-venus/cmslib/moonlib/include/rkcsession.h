#pragma once
#include "stdafx.h"
#include "rkcSessionCtrlIF.h"
#include "rkcmsgdriver.h"

class CRkcSession : public CRkcSessionCtrlIF,
                    public CRkcMsgDriver
{
public:
    CRkcSession();
    ~CRkcSession();

    //获取接口 
    virtual u16 RkcGetInterface(CRkcSysCtrlIF **ppCtrl);
    virtual u16 RkcGetInterface(CCamConfigIF **ppCtrl);
    virtual u16 RkcGetInterface(CSysConfigIF **ppCtrl);

protected:
    // 初始化OSP 
    u16 InitializeOsp();

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    BOOL32 m_bInitOsp;

    // 各个功能类接口类
    CRkcSysCtrlIF  *m_pSysCtrlIf;
    CCamConfigIF  *m_pCamConfigIf;
    CSysConfigIF  *m_pSysConfigIf;

};

