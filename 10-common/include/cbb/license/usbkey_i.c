/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 04 13:25:01 2015
 */
/* Compiler settings for .\usbkey.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IOprKey = {0x2D9BC8BC,0x65D6,0x4877,{0x83,0xCF,0x07,0x3D,0x5B,0x2C,0xC1,0x3B}};


const IID LIBID_USBKEYLib = {0x133AE72F,0xB4B2,0x45FB,{0x9E,0x36,0xD9,0x67,0x16,0x07,0xE6,0x7C}};


const CLSID CLSID_OprKey = {0xE8F57E98,0xD4EE,0x497B,{0xB8,0x19,0x95,0x20,0x3A,0x48,0x25,0xA8}};


#ifdef __cplusplus
}
#endif

