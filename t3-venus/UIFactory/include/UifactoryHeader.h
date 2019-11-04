#ifndef UIFACTORY_HEADER
#define UIFACTORY_HEADER

/*
添加一个新控件的流程
1、添加工厂，如果你的空间名为CXXX，请用宏DECLARE_WINDOW_FACTORY(CXXX)
2、添加了工厂，需要到CRegDefaultData里面的RegDefaultWindowFactory函数里面注册
	请使用宏REG_WINDOW_FACTORY(CXXX)
3、控件写好后，需要为其添加属性集，请使用宏 DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) 和 DECLARE_PROPERTYSET_END
	如果需要集成一些默认的属性，请将IPropertySet修改为CWndPropertySet
4、写好控件集过后，需要在CRegDefaultData里面的RegDefaultWindowPropertySet函数里面注册
	也请使用宏REG_PROPERTY_SET(CXXX)
5、如果控件有新添加的属性，请使用宏DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END 进行申明
	具体注意事项请参看宏
6、新属性如果需要替换老属性：比如CXXXImage需要替换WindowPos这个属性，直接在第3步的宏中间添加
	AddProperty( "WindowPos", "CXXXImage" );
7、添加新属性后，需要在CRegDefaultData里面的RegDefaultWindowProperty函数里面注册
	使用宏REG_PROPERTY(CXXXImage)
*/
#include "uifactorydef.h"
#include "System.h"
#include "windowfactory.h"
#include "WndMsgEventManage.h"
#include "IProperty.h"
#include "IPropertyAssist.h"
#include "PropertySet.h"
#include "templateClass.h"
#include "CallFuncManage.h"
#include "WindowManage.h"
#include "MfcDefaultArgs.h"
#include "MfcDefaultWndFactory.h"
#include "MfcDefaultWndProperty.h"
#include "MfcDefaultWndPropertySet.h"
#include "WndTreeHelp.h"
#include "SaveXmlHelp.h"
#include "UILayoutHelp.h"
#include "ItemFactory.h"
#include "UIExLibArgs.h"
#include "UIExLibPropertySet.h"
#include "SchemeHelp.h"
using namespace AutoUIFactory;
#endif