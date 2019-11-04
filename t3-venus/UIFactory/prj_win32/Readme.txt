======================================================================================
								UIFactory
/*
添加一个新控件的流程
1、添加工厂，如果你的控件名为CXXX，请用宏DECLARE_WINDOW_FACTORY(CXXX) 
	（不添加这个，会导致无法创建对应控件）

2、添加了工厂，需要到CRegDefaultData里面的RegDefaultWindowFactory函数里面注册	
	请使用宏REG_WINDOW_FACTORY(CXXX)
	（不添加这个，会导致无法创建对应控件）

3、控件写好后，需要为其添加属性集，请使用宏 DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) 和 DECLARE_PROPERTYSET_END
	如果需要集成一些默认的属性，请将IPropertySet修改为CWndPropertySet
	（不添加这个，会导致无法在xml里面配置的属性无法设置到对应的控件上）

4、写好控件集过后，需要在CRegDefaultData里面的RegDefaultWindowPropertySet函数里面注册
	也请使用宏REG_PROPERTY_SET(CXXX)
	（不添加这个，会导致无法在xml里面配置的属性无法设置到对应的控件上）

5、如果控件有新添加的属性，请使用宏DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END 进行申明
	具体注意事项请参看宏
	（不添加这个，会导致无法在xml里面的新属性设置不上去）

6、新属性如果需要替换老属性：比如CXXXImage需要替换WindowPos这个属性，直接在第3步的宏中间添加
	AddProperty( "WindowPos", "CXXXImage" );
	如果不需要替换，可在宏中间写
	AddProperty( "CXXXImage", "CXXXImage" );
	（不添加这个，会导致无法在xml里面的新属性设置不上去）

7、添加新属性后，需要在CRegDefaultData里面的RegDefaultWindowProperty函数里面注册
	使用宏REG_PROPERTY(CXXXImage)
	（不添加这个，会导致无法在xml里面的新属性设置不上去）
*/
======================================================================================