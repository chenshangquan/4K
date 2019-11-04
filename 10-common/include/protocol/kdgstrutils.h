/******************************************************************************
 *  Module name: kdgstrutils
 *    File name: kdgstrutils.h
 *      Related: 
 *     Function: utils of strings including:
 *                 convert encoding of text that of Chinese charactors.
 *       Author: xiezhigang
 *      Version: v1.0  Copyright(C) 2014 KDC, All rights reserved.
 * ----------------------------------------------------------------------------
 * Revisions:
 * Date        Version     Reviser     Description
 * 2014-07-31  v1.0        xiezhigang  created
 ******************************************************************************/
#ifndef KDGSTRUTILS_H
#define KDGSTRUTILS_H

#include "kdglib_common.h"

#include <stddef.h>
#include <string.h>

BEGIN_KDGLIBAPI

/*!
 * \brief   Converts a string from one encoding into another.
 * \param fromcode    from which encoding the string for converting.
 * \param tocode      into which encoding the string will be converted.
 * \param inbuf       the string content for converting.
 * \param inbytes     the size of content for input in bytes.
 * \param outbuf      which accept the conversion result.
 * \param outbufsize  the size of outbuffer in bytes.
 * \return  bytes written into out buffer.
 * \error   EACCES  Permission denied, or NULL outbuffer.
 * \error   EBADRQC Invalid request code, or request code is unsupported.
 * \error   E2BIG   There is no sufficient room at outbuffer.
 * \error   EILSEQ  An invalid multibyte sequence has been encountered in the
 *                  input.
 * \error   EINVAL  An incomplete multibyte sequence has been encountered in
 *                  the input.
 * \note    The underlying implementation is iconv(), or some other widely used
 *          functions.
 * \note    Although inbuf and outbuf are typed as char *, this does not mean
 *          that the objects they point can be interpreted as C strings or as
 *          arrays of characters: the interpretation of character byte
 *          sequences is handled internally by the conversion functions. In
 *          some encodings, a zero byte may be a valid part of a multibyte
 *          character. 
 * \note    The caller of iconv() must ensure that the pointers passed to the
 *          function are suitable for accessing characters in the appropriate
 *          character set. This includes ensuring correct alignment on plat‐
 *          forms that have tight restrictions on alignment.
 */
KDGLIBAPI
size_t KdgStrConvert (
        const char * fromcode, const char * tocode,
        const char * inbuf, size_t inbytes,
        char * outbuf, size_t outbufsize
        );

/*!
 * \brief   Gets error message for string encoding conversion.
 * \return  Error message if there is an error in string conversion, or an
 *          empty string.
 * \note    also, `errno' is set, and possibly values are:
 *              E2BIG, EILSEQ, EINVAL.
 * \note    The content of this message will be changed until next invoke of
 *          KdgStrConvert().
 */
KDGLIBAPI
const char * KdgStrConvertErrorMessage (void);

/*!
 * \brief   Canonical code name for BMP string.
 * \note    Mostly, it is UTF-16BE.
 */
#define KDG_CODE_BMP        "UTF-16BE"

/*!
 * \brief   Canonical code name for UNICODE string.
 * \note    It is dependent on machine's byte ordering.
 *          In little-endian machines, it is UTF-16LE;
 *          In big-endian machines, it is UTF-16BE.
 */
KDGLIBAPI
const char * KdgHostUnicodeName (void);

/*!
 * \brief   Canonical code name for GB/ASCII string.
 * \note    Mostly, it is GB18030.
 */
#define KDG_CODE_GB         "GB18030"

/*!
 *  \brief  Canonical code name for UTF-8 string.
 *  \note   Mostly, it is UTF-8.
 */
#define KDG_CODE_UTF8       "UTF-8"


/*!
 * \brief Converts a text from encoding of GB18030 to encoding of Unicode.
 *        Please note that the `Unicode' here is canonical `UTF-16LE'.
 *
 * \param pszGb      a text in encoding of GB18030, or NULL.
 * \param pbyBuff    a buffer that accepts the converted text in Unicode.
 * \param nBuffLen   buffer length in bytes.
 * \return Length in bytes of converted text.
 *         If there is a null text, it returns a value == 0.
 *         If there is an error, it returns a value of (size_t)-1.
 */
KDGLIBAPI
size_t KdgConvertGbToUnicode (const char *pszGb,
        uint8_t *pbyBuff, size_t nBuffLen);

/*!
 * \brief Converts a text from encoding of Unicode to encoding of GB18030.
 *        Please note that the `Unicode' here is canonical `UTF-16LE'.
 *
 * \param pbyUni     a text in encoding of Unicode(UTF-16LE), or NULL.
 *                   be sure of terminate with no less two nil-chars.
 * \param pchBuff    a buffer that accepts the converted text in GB18030.
 * \param nBuffLen   buffer length in bytes.
 * \return Length in bytes of converted text.
 *         If there is a null text, it returns a value == 0.
 *         If there is an error, it returns a value of (size_t)-1.
 */
KDGLIBAPI
size_t KdgConvertUnicodeToGb (const uint8_t *pbyUni,
        char *pchBuff, size_t nBuffLen);

/*!
 * \brief   converts string of ascii into bmp.
 * \param pszGb     a text in encoding of GB, or NULL, nil terminated.
 * \param pbyBuff   outbuffer that accepts the converted text.
 * \param nBuffLen  byte size of outbuffer.
 * \return  bytes written to target buffer
 */
KDGLIBAPI
size_t KdgConvertGbToBmp (const char *pszGb,
        uint8_t *pbyBuff, size_t nBuffLen);

/*!
 * \brief   converts string of bmp into ascii.
 * \param pbyBmp    a text in encoding of BMP, double nil terminated.
 * \param pbyBuff   outbuffer that accepts the converted text.
 * \param nBuffLen  byte size of outbuffer.
 * \return  bytes written to target buffer.
 */
KDGLIBAPI
size_t KdgConvertBmpToGb (const uint8_t *pbyBmp,
        char * pchBuff, size_t nBuffLen);

/*!
 * \brief   converts string of utf-8 into ascii.
 * \param pszUtf8   a text in encoding of UTF-8, nil terminated.
 * \param pbyBuff   outbuffer that accepts the converted text.
 * \param nBuffLen  byte size of outbuffer.
 * \return  bytes written to target buffer.
 */
KDGLIBAPI
size_t KdgConvertUtf8ToGb (const char *pszUtf8,
        char *pchBuff, size_t nBuffLen);

/*!
 * \brief   converts string of ascii into utf-8.
 * \return  bytes written to target buffer
 */
KDGLIBAPI
size_t KdgConvertGbToUtf8 (const char *pszGb,
        char *pchBuff, size_t nBuffLen);

KDGLIBAPI
size_t KdgConvertUtf8ToUnicode (const char* pszUtf8,
        uint8_t *pbyBuff, size_t nBuffLen);

KDGLIBAPI
size_t KdgConvertUnicodeToUtf8 (const uint8_t* pbyUni,
        char *pchBuff, size_t nBuffLen);

/* case insensitive strncmp */
#ifdef _MSC_VER

#define strcasecmp  stricmp
#define strncasecmp strnicmp

#else // !_MSC_VER

#define stricmp     strcasecmp
#define strnicmp    strncasecmp

#endif // !_MSC_VER

#if 0
/* multi thread safe strtok version */
char * strtok_mts(char *s, const char *delim, char **lasts);

// ./10-common/include/protocol/h323stack4_2/strutils.h
// ./20-cbb/460/g0-pluto/h323stacklib/source/utils/strutils.h
// ./20-cbb/h323stacklib/source/utils/strutils.h
// ./20-cbb/radversion-4.2/Linux/10-common/include/protocol/h323stack4_2/strutils.h
#endif


END_KDGLIBAPI


#endif // KDGSTRUTILS_H
