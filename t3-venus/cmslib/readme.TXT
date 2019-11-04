lib编写注意事项

一：重要文件说明
70/common:
cmsConst.h:定义常量和错误码
evCmsLib.h：定义 cms和lib间的消息，已经cms界面中的wnd消息
dispevent.h：实现消息分发的模块

    
70/cmslib/common：
msgdriver.h：实现lib和服务器间osp的通信 
ospmsgrecver.h: 声明接收OSP消息所需的CInstance派生类



APP号定义在70/tp/tpsys.h中
umcLib中的APP号：  AID_CMS2UMS_APP      
cncLib中的APP号：  AID_CMS2CNS_APP   


二：类功能说明
1 XXXSessionCtrlIF：为Lib的总接口，通过该接口可以获取到各个功能接口类（XXXCtrlIF）
2 各个功能模块都有接口类（类中全部为纯虚函数，作为接口使用）
3 各个功能类都需要继承其对应的（抽象类）接口类 和 CDispMsg类（用于实现消息分发）
4 各个功能类在与服务器通信时，使用XXXSession中重写的postmsg接口（该接口调用了CMsgDriver的postMsg接口：为了便于控制是否满足与服务器通信的条件，因而，在session处重写postMsg接口，统一控制）
5 BuildEventsMap（）
需要处理服务器发来的消息的类，都应包含并实现该函数 ，
其实现部分如下例：
  //eg： REG_PFUN(ev_XXX, OnXXX);
REG_PFUN():在70/common/CDispEvent.h中实现，第一个参数为要处理的消息号，第二个参数为ex_XXX对应的处理函数
OnXXX在类中实现