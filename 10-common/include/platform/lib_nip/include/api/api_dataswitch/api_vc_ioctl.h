
#ifndef __VC_IOCTL_H
#define __VC_IOCTL_H

#define UCHAR	unsigned char

/*defines*/
//*命令类型
#define     NIP_GET_IF_INFO      0x01
#define     NIP_SET_IF           0x02
#define     NIP_GET_DFLT_ROUTE   0x03
#define     NIP_SET_DFLT_ROUTE   0x04
#define     NIP_DEL_DFLT_ROUTE   0x05
#define     NIP_GET_NEXTHOP      0x06
#define     NIP_DEL_INTF         0x07

/*structs*/
//接口基本状态
struct if_info
{
    ulong   ipaddr;
    ulong   ipmask;
    union
    {
        struct
        {
            UCHAR enaddr[6];
        }eth;
    } u;
};

#define  if_eth  u.eth.enaddr

//cmd=NIP_GET_IF_INFO,取得接口信息
struct vc_req_get_if
{
    //请求
    struct
    {
        char    iftype[16];
        char    ifunit;
    }req;

    //返回值
    struct
    {
    #define IF_STS_DOWN 0x01
    #define IF_STS_UP   0x02
        int     state;
        struct if_info iff;
    }ifinfo;
};

//cmd=NIP_SET_IF_INFO || NIP_DEL_INTF 设置接口信息
struct vc_req_set_if
{
    char    iftype[16];
    char    ifunit;

#define VC_SET_IF_IP_AND_MASK    0x01
#define VC_SET_IF_ETHMAC    0x02
    int     flags;
    struct  if_info iff;
};

//cmd=NIP_GET_DFLT_ROUTE设置/取得默认路由
struct vc_req_route
{
    ulong dflt_rt;
};

//cmd=NIP_GET_NEXTHOP 取得下一条
struct vc_req_nxthop
{
    ulong req_dst;
    ulong nxthop;
};

extern int vc_ioctl(int cmd, void* req, int flags);


#endif

