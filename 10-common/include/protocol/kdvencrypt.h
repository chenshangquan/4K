/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        kdvencrypt.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Encrption Function
*   @details     
*/
#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_
#include "kdvtype.h"
//#include "osp.h"

#ifdef WIN32
#include <winsock2.h>
#endif

#define KDVENCRYPTVERSION		(const char*)"kdvencrypt 40.01.02 071203"

/**Lib info*/
void kdvencryptver(); 
void KdvGetEncryptVer(char** ppEncryptVer);

typedef long*  verylong;



/**************************大数运算*******************************************/

/**
	* \brief            将字串转换为大整数
	* \param[in]        pszText		:以十六进制数表示的字符串("user"->"75736572")  
	* \param[out]       pvlNum      :要输出的大整数
	* \param[in]        wWatchPortTo    :End of watch port
	* \param[in]        bSockInit       :Pfc sock init flag
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/

bool StrToNumber(char *pszText, verylong *pvlNum);

/**
	* \brief            将大整数转换为字串
	* \param[out]       pszText		:以十六进制数表示的字符串("user"->"75736572")  
	* \param[in]        pvlNum      :输入的大整数
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/
bool NumberToStr(char *pszText, verylong vlNum);

/**
	* \brief            大整数内存释放
	* \param[out]       pszText		:以十六进制数表示的字符串("user"->"75736572")  
	* \param[in]        pvlNum      :输入的大整数
	* \retval           success:TRUE
*/
bool KdvVerylongNumFree();

/**
	* \brief            释放kar_mem内存
	* \retval           success:TRUE
*/
bool KdvFreeKarMem();

/**
	* \brief            求模运算
	* \retval           success:TRUE
*/
bool KdvExpMod(verylong a,  verylong e,   verylong n, verylong *bb); 

bool KdvRandomPrime(long lBits, verylong *bb);

void vlFree(verylong *a);


inline void kdvstrrev(s8 *s)
{
    s8 *p = s;

    if (!s)
    {
        return;
    }

    while (*p)
    {
        ++p;
    }
    --p;

    while (p > s)
    {
        s8 c  =  *p;
        *p--  =  *s;
        *s++  =   c;
    }
}
/*****************************************************************************/

/**********************des****************************************************/
/** what Type*/
typedef enum QFDES_what {qfDES_encrypt, qfDES_decrypt} QFDES_what;

/** mode */
typedef enum QFDES_mode {qfDES_ecb, qfDES_cbc, qfDES_cfb, qfDES_ofb} QFDES_mode;

/**
	* \brief            Des 加密运算
	* \param[in]        key		  :秘钥
	* \param[in]        data      :加密数据
	* \param[in]        size	  :加密长度大小
	* \param[in]        what      :DES加密或是解密方式
	* \param[in]        mode      :加密或解密模式
	* \param[in]        initVec   :初始化向量
	* \retval           void
*/
void KdvDES(u8	*key, u8 *data,  u32 size,  
		  const QFDES_what what,
		  const QFDES_mode mode,
		  u8 *initVec);

bool IsWeakDesKey(u8 *key);
/****************************************************************************/

/**********************AES****************************************************/

/**  Generic Defines  */
#define     DIR_ENCRYPT           0 /**<  Are we encrpyting?  */
#define     DIR_DECRYPT           1 /**<  Are we decrpyting?  */
#define     MODE_ECB              1 /**<  Are we ciphering in ECB mode?   */
#define     MODE_CBC              2 /**<  Are we ciphering in CBC mode?   */
#define     MODE_CFB1             3 /**<  Are we ciphering in 1-bit CFB mode? */

/**  Algorithm-specific Defines  */
#define     MAX_KEY_SIZE         /*32*/64 /**<# of ASCII char's needed to represent a key */
#define     MAX_IV_SIZE          16 /**< # bytes needed to represent an IV  */

/**
	* \brief            Aes 加密运算
	* \param[in]        keyMaterial		  :秘钥
	* \param[in]        keyLen            :秘钥长度
	* \param[in]        mode			  :加密或解密模式
	* \param[in]        IV				  :AES加密或是解密方式
	* \param[in]        direction		  :加密长度大小
	* \param[in]        IV				  :初始化向量
	* \param[in]        mode			  :加密或加密模式
	* \param[in]        input			  :被加密或解密数据
	* \param[in]        inputLen		  :被加密或解密数据长度
	* \param[in]        outBuffer		  :加密或是解密输出buffer
	* \retval           void
*/
int KdvAES(s8 *keyMaterial, s32 keyLen, u8 mode,u8 direction,s8 *IV, 
           u8 *input, s32 inputLen, u8 *outBuffer);

#endif
