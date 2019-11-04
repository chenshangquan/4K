#ifndef KDVCRYPT_WRAPPER_H
#define KDVCRYPT_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

//https://gcc.gnu.org/wiki/Visibility
#if defined _WIN32 || defined __CYGWIN__
  #ifdef KDVCRYPT_DLL
    #ifdef __GNUC__
      #define KDVCRYPT_PUBLIC __attribute__ ((dllexport))
    #else
      #define KDVCRYPT_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define KDVCRYPT_PUBLIC __attribute__ ((dllimport))
    #else
      #define KDVCRYPT_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define KDVCRYPT_LOCAL  // not use in this library
#else
  #if __GNUC__ >= 4
    #define KDVCRYPT_PUBLIC __attribute__ ((visibility ("default")))
    #define KDVCRYPT_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define KDVCRYPT_PUBLIC
    #define KDVCRYPT_LOCAL // not use in this library
  #endif
#endif

#include <stdint.h>

#define KDVCRYPT_DIR_DECRYPT    0
#define KDVCRYPT_DIR_ENCRYPT    1

typedef enum {
    KDVCRYPT_STATUS_OK                 = 0,
    KDVCRYPT_STATUS_WRONG_PARAM        = 1,
    KDVCRYPT_STATUS_NOT_SUPPORT        = 2,
    KDVCRYPT_STATUS_UNKNOW_ERROR       = 3,
    KDVCRYPT_STATUS_CIPHER_ERROR       = 4,
    KDVCRYPT_STATUS_UPDATE_ERROR       = 5,
    KDVCRYPT_STATUS_FINAL_ERROR        = 6,
    KDVCRYPT_STATUS_NOT_INITED         = 7,
    KDVCRYPT_STATUS_NOT_PADDING        = 8
} kdvcrypt_status_t;


typedef enum {
    KDVCRYPT_ALGO_NULL        = 0,
    KDVCRYPT_ALGO_AES_CBC_128 = 1
} kdvcrytp_ctx_cfg_t;


typedef struct {
    uint32_t direction;       /* IN */
    uint8_t * key;            /* IN */
    uint32_t key_len;         /* IN */
    uint8_t * iv;             /* IN */ 
    uint32_t iv_len;          /* IN */
    uint8_t * in;             /* IN */
    int32_t in_len;           /* IN */
    uint8_t * out;            /* OUT */
    int32_t out_len;          /* IN/OUT */
} kdvcrypt_crypt_data_t;

typedef struct _kdvcrypt_ctx_t kdvcrypt_ctx_t;

KDVCRYPT_PUBLIC kdvcrypt_ctx_t *kdvcrypt_ctx_new(kdvcrytp_ctx_cfg_t cfg);

KDVCRYPT_PUBLIC void kdvcrypt_ctx_free(kdvcrypt_ctx_t *ctx);

KDVCRYPT_PUBLIC kdvcrypt_status_t kdvcrypt_ctx_crypt(kdvcrypt_ctx_t *ctx, kdvcrypt_crypt_data_t *data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //KDVCRYPT_WRAPPER_H
