#pragma once
#include "kdvdispevent.h"
#include "rkcsysctrlif.h"
#include "camconfigif.h"
#include "sysconfigif.h"
#include "rkcstruct.h"

class CRkcSessionCtrlIF : public CKdvDispEvent 
{
public:
    //获取接口
    virtual u16 RkcGetInterface(CRkcSysCtrlIF **ppCtrl) = 0;
    virtual u16 RkcGetInterface(CCamConfigIF **ppCtrl) = 0;
    virtual u16 RkcGetInterface(CSysConfigIF **ppCtrl) = 0;
};
