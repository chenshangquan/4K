#ifndef NIP_BYTEORDER_H
/* nip byteorder hearder file ,liangyulin 20051103 11:00 */
#include <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define NIP_LITTLE_ENDIAN   8888
#elif __BYTE_ORDER == __BIG_ENDIAN
#define NIP_BIG_ENDIAN   8888
#else
#error "Fix <lib/nip_byteorder.h>"
#endif

#endif /* NIP_BYTEORDER_H */


#if 0
/*  Usage example */
#include <lib/nip_byteorder.h>
struct hdr 
{ 
       #if defined NIP_LITTLE_ENDIAN 
       u_int8_t ihl:4; 
       u_int8_t vn:4; 
       #elif NIP_BIG_ENDIAN 
       u_int8_t vn:4; 
       u_int8_t ihl:4; 
       #else 
       #error "Please fix <lib/nip_byteorder.h>" 
       #endif 
}
#endif
