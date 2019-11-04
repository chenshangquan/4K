#ifdef _PFC_SERIAL_H_

///////////////////////////////////////////////////////////////////
//	Linux 操作系统头文件
///////////////////////////////////////////////////////////////////
#if (defined(_LINUX_) || defined(_IOS_PLATFORM_))
#ifdef PWLIB_SUPPORT
#include <ptlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#ifdef _IOS_PLATFORM_
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/times.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <termios.h>
#include <signal.h>
#include "syslog.h"

#if defined(_ANDROID_)
#include <sys/epoll.h>
#include <fcntl.h>
#elif (!(defined(_EQUATOR_) || defined(_IOS_PLATFORM_)))
#include <mqueue.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#endif
#endif //_LINUX_

///////////////////////////////////////////////////////////////////
//	Vxworks 操作系统头文件
///////////////////////////////////////////////////////////////////
#ifdef _VXWORKS_

#include <vxworks.h>
#include <tasklib.h>
#include <msgqlib.h>
#include <syslib.h>
#include <string.h>
#include <memLib.h>
#include <stdlib.h>
#include <string.h>
#include <sockLib.h>
#include <inetLib.h>
#include <stdioLib.h>
#include <strLib.h>
#include <hostLib.h>
#include <ioLib.h>
#include <assert.h>
#include <netdb.h>
#include <errno.h>
#include <sys/stat.h>
#include <taskHookLib.h>
#include <logLib.h>
//串口支持
#include "brddrvlib.h"

#endif // _VXWORKS_

///////////////////////////////////////////////////////////////////
//	Win32 操作系统头文件
///////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning(disable:4127)
#pragma warning(disable:4996)

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#ifdef WINVER
#undef WINVER
#endif
#if (_MSC_VER >= 1400)
#define _WIN32_WINNT 0x0501 //support only winxp and above
#define WINVER 0x0501 //support only winxp and above
#else
#define _WIN32_WINNT 0x400
#define WINVER 0x0400
#endif

#include <malloc.h>
#include <time.h>

#ifdef _AFXDLL
#include <afx.h>
#include <afxwin.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <assert.h>
#pragma comment(lib,"Ws2_32.lib")

#endif  // _MSC_VER

#include "kdvtype.h"

///////////////////////////////////////////////////////////////////
//	操作系统无关宏定义
///////////////////////////////////////////////////////////////////
// for Microsoft c++
#ifdef _MSC_VER

//紧排列
#ifndef _EQUATOR_
#pragma pack(push)
#pragma pack(1)
#endif

#define API extern "C"          __declspec(dllexport)
#define PFC_API                 __declspec(dllexport)

// for gcc
#else

#define API extern "C"
#define PFC_API

#endif  // _MSC_VER

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#if defined(_LINUX_)        //LINUX
    #define PFCSERIALHANDLE         int
    #define INVALID_SERIALHANDLE    (-1)
#elif defined(_VXWORKS_)    //VXWORKS
    #define PFCSERIALHANDLE         int
    #define INVALID_SERIALHANDLE    ERROR
#else                       //WINDOWS
    #define PFCSERIALHANDLE         HANDLE
    #define INVALID_SERIALHANDLE  INVALID_HANDLE_VALUE
#endif  // _LINUX_

#ifdef _MSC_VER
    #define TPfcCommTimeouts      COMMTIMEOUTS
    #define TPfcDCB               DCB
    #define TPfcComStat           COMSTAT
#endif  // _MSC_VER

#ifndef _MSC_VER

//
// Provider capabilities flags.
//

#define PCF_DTRDSR        ((u32)0x0001)
#define PCF_RTSCTS        ((u32)0x0002)
#define PCF_RLSD          ((u32)0x0004)
#define PCF_PARITY_CHECK  ((u32)0x0008)
#define PCF_XONXOFF       ((u32)0x0010)
#define PCF_SETXCHAR      ((u32)0x0020)
#define PCF_TOTALTIMEOUTS ((u32)0x0040)
#define PCF_INTTIMEOUTS   ((u32)0x0080)
#define PCF_SPECIALCHARS  ((u32)0x0100)
#define PCF_16BITMODE     ((u32)0x0200)

//
// Comm provider settable parameters.
//

#define SP_PARITY         ((u32)0x0001)
#define SP_BAUD           ((u32)0x0002)
#define SP_DATABITS       ((u32)0x0004)
#define SP_STOPBITS       ((u32)0x0008)
#define SP_HANDSHAKING    ((u32)0x0010)
#define SP_PARITY_CHECK   ((u32)0x0020)
#define SP_RLSD           ((u32)0x0040)

//
// Settable baud rates in the provider.
//
#ifdef _VXWORKS_
#define BAUD_110          (u32)110
#define BAUD_300          (u32)300
#define BAUD_1200         (u32)1200
#define BAUD_2400         (u32)2400
#define BAUD_4800         (u32)4800
#define BAUD_9600         (u32)9600
#define BAUD_19200        (u32)19200
#define BAUD_38400        (u32)38400
#endif

#if defined(_LINUX_) && !defined(_EQUATOR_)
#define BAUD_300          (u32)300
#define BAUD_1200         (u32)1200
#define BAUD_2400         (u32)2400
#define BAUD_4800         (u32)4800
#define BAUD_9600         (u32)9600
#define BAUD_19200        (u32)19200
#define BAUD_38400        (u32)38400
#define BAUD_57600        (u32)57600
#define BAUD_115200       (u32)115200
#endif

// Equator上只能设置波特率，其他的都不能设置
#ifdef _EQUATOR_
// 注意：最高速率为9600
#define BAUD_110          (u16)110
#define BAUD_300          (u16)300
#define BAUD_600          (u16)600
#define BAUD_1200         (u16)1200
#define BAUD_2400         (u16)2400
#define BAUD_4800         (u16)4800
#define BAUD_9600         (u16)9600
#endif

//
// Settable Data Bits
//
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define DATABITS_5        (u8)5
#define DATABITS_6        (u8)6
#define DATABITS_7        (u8)7
#define DATABITS_8        (u8)8
#else
#define DATABITS_5        ((u16)0x0001)
#define DATABITS_6        ((u16)0x0002)
#define DATABITS_7        ((u16)0x0004)
#define DATABITS_8        ((u16)0x0008)
#define DATABITS_16       ((u16)0x0010)
#define DATABITS_16X      ((u16)0x0020)
#endif

//
// Settable Stop and Parity bits.
//
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define STOPBITS_10       (u8)1
#define STOPBITS_20       (u8)2
#else
#define STOPBITS_10       ((u16)0x0001)
#define STOPBITS_15       ((u16)0x0002)
#define STOPBITS_20       ((u16)0x0004)
#endif

#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define PARITY_NONE       (u8)0
#define PARITY_ODD        (u8)1
#define PARITY_EVEN       (u8)2
#define PARITY_MARK       (u8)3
#define PARITY_SPACE      (u8)4
#else
#define PARITY_NONE       ((u16)0x0100)
#define PARITY_ODD        ((u16)0x0200)
#define PARITY_EVEN       ((u16)0x0400)
#define PARITY_MARK       ((u16)0x0800)
#define PARITY_SPACE      ((u16)0x1000)
#endif
//
// DTR Control Flow Values.
//
#define DTR_CONTROL_DISABLE     0x00
#define DTR_CONTROL_ENABLE      0x01
#define DTR_CONTROL_HANDSHAKE   0x02

//
// RTS Control Flow Values
//
#define RTS_CONTROL_DISABLE     0x00
#define RTS_CONTROL_ENABLE      0x01
#define RTS_CONTROL_HANDSHAKE   0x02
#define RTS_CONTROL_TOGGLE      0x03

#define NOPARITY                0
#define ODDPARITY               1
#define EVENPARITY              2
#define MARKPARITY              3
#define SPACEPARITY             4

#define ONESTOPBIT              0
#define ONE5STOPBITS            1
#define TWOSTOPBITS             2

//
// Escape Functions
//

#define SETXOFF                 1       // Simulate XOFF received
#define SETXON                  2       // Simulate XON received
#define SETRTS                  3       // Set RTS high
#define CLRRTS                  4       // Set RTS low
#define SETDTR                  5       // Set DTR high
#define CLRDTR                  6       // Set DTR low
#define RESETDEV                7       // Reset device if possible
#define SETBREAK                8       // Set the device break line.
#define CLRBREAK                9       // Clear the device break line.

//
// PURGE function flags.
//
#define PURGE_TXABORT           0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT           0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR           0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR           0x0008  // Kill the typeahead buffer if there.

#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
//串口数据结构
typedef struct {
    //串口句柄
    PFCSERIALHANDLE handle;
    //串口超时结构
    TPfcCommTimeouts tCommTimeouts;
} TTiCommData;
#endif

typedef struct
{
    u32 ReadIntervalTimeout;
    u32 ReadTotalTimeoutMultiplier;
    u32 ReadTotalTimeoutConstant;
    u32 WriteTotalTimeoutMultiplier;
    u32 WriteTotalTimeoutConstant;
} TPfcCommTimeouts;

typedef struct
{
    u32 DCBlength;           // sizeof(DCB)
    u32 BaudRate;            // current baud rate
    u32 fBinary: 1;          // binary mode, no EOF check
    u32 fParity: 1;          // enable parity checking
    u32 fOutxCtsFlow: 1;     // CTS output flow control
    u32 fOutxDsrFlow: 1;     // DSR output flow control
    u32 fDtrControl: 2;      // DTR flow control type
    u32 fDsrSensitivity: 1;  // DSR sensitivity
    u32 fTXContinueOnXoff: 1; // XOFF continues Tx
    u32 fOutX: 1;            // XON/XOFF out flow control
    u32 fInX: 1;             // XON/XOFF in flow control
    u32 fErrorChar: 1;       // enable error replacement
    u32 fNull: 1;            // enable null stripping
    u32 fRtsControl: 2;      // RTS flow control
    u32 fAbortOnError: 1;    // abort on error
    u32 fDummy2: 17;         // reserved
    u32 wReserved;           // not currently used
    u16 XonLim;              // transmit XON threshold
    u16 XoffLim;             // transmit XOFF threshold
    u8  ByteSize;            // number of bits/Byte, 4-8
    u8  Parity;              // 0-4=no,odd,even,mark,space
    u8  StopBits;            // 0,1,2 = 1, 1.5, 2
    char XonChar;            // Tx and Rx XON character
    char XoffChar;           // Tx and Rx XOFF character
    char ErrorChar;          // error replacement character
    char EofChar;            // end of input character
    char EvtChar;            // received event character
    u16  wReserved1;         // reserved; do not use
} TPfcDCB;

typedef struct
{
    u32 fCtsHold : 1;
    u32 fDsrHold : 1;
    u32 fRlsdHold : 1;
    u32 fXoffHold : 1;
    u32 fXoffSent : 1;
    u32 fEof : 1;
    u32 fTxim : 1;
    u32 fReserved : 25;
    u32 cbInQue;
    u32 cbOutQue;
} TPfcComStat;

#endif //#ifndef _MSC_VER

// 串口封装：以Windows串口操作函数为准，在VxWorks下提供相应函数
/*====================================================================
函数名：PfcSerialOpen
功能：打开指定的串口
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：成功返回打开串口的句柄，失败返回INVALID_SERIALHANDLE
====================================================================*/
API PFCSERIALHANDLE PfcSerialOpen(u8 port);

/*====================================================================
函数名：PfcSerialClose
功能：关闭指定的串口
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcSerialClose(PFCSERIALHANDLE hCom);

/*====================================================================
函数名：PfcSerialRead
功能：从指定的串口读数据
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcSerialRead(PFCSERIALHANDLE hCom, char *pchBuf, u32 dwu8sToRead, u32 *puu8sRead);

/*====================================================================
函数名：PfcSerialWrite
功能：向指定的串口写数据
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcSerialWrite(PFCSERIALHANDLE hCom, char *pchBuf, u32 dwu8sToWrite, u32 *puu8sWrite);

/*====================================================================
函数名：PfcSetCommTimeouts
功能：设置串口超时
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcSetCommTimeouts(PFCSERIALHANDLE hCom, TPfcCommTimeouts *ptCommTimeouts);

/*====================================================================
函数名：PfcGetCommState
功能：获得串口状态
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcGetCommState(PFCSERIALHANDLE hCom, TPfcDCB *ptDCB);

/*====================================================================
函数名：PfcSetCommState
功能：设置串口状态
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcSetCommState(PFCSERIALHANDLE hCom, TPfcDCB *ptDCB);

/*====================================================================
函数名：PfcEscapeCommFunction
功能：使用串口扩展功能
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcEscapeCommFunction(PFCSERIALHANDLE hCom, u32 dwFunc);

/*====================================================================
函数名：PfcPurgeComm
功能：丢弃所有未决数据，终止串口读写操作
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcPurgeComm(PFCSERIALHANDLE hCom, u32 dwFlags);

/*====================================================================
函数名：PfcClearCommError
功能：与Windows下ClearCommError相同
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcClearCommError(PFCSERIALHANDLE hCom, u32 *pdwErrors, TPfcComStat *ptStat);

/*====================================================================
函数名：PfcGetCommTimeouts
功能：取得打开串口的超时设置
算法实现：（可选项）
引用全局变量：
输入参数说明：

 返回值说明：
====================================================================*/
API BOOL32 PfcGetCommTimeouts(PFCSERIALHANDLE hCom, TPfcCommTimeouts *ptCommTimeouts);

#endif //_ENABLE_SOCK5_API_

