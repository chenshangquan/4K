#ifndef API_FTP_H_
#define API_FTP_H_

#include "api/nip_api.h"
#include "lib/if.h"

#define NIP_FTP_SET_ENABLE NIP_FTP_BASE + 1
#define NIP_FTP_SET_DISABLE NIP_FTP_BASE + 2

extern int nip_api_ftp_enable(int enable);

#endif  /* API_FTP_H_ */

