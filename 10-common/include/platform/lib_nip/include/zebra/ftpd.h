#include "lib/zebra.h"
#include "g_module.h"
#include "lib/zlog.h"
#include "lib/vty.h"

#define FTPD_DEFAULT_TIMEOUT 600
#ifdef MOD_FTP_SERVER_VER_1
#else
#define FTPD_DIR "/ftproot"
#define FTPD_DIR_SUPER "/"
#define FTPD_CONFIG_FILE "/usr/etc/ftpd.conf"
#define ZMSG_FTPD_AUTH ZMSG_FTPD_BASE + 1
#endif

#define FTPD_ERROR(fmt, args...)  zlog_msg(NULL, ZLOG_ERROR, fmt, ##args)
#define FTPD_WARN(vty, fmt, args...)  vty_out(vty, fmt, ##args)
#define FTPD_WARN2(vty, fmt1, fmt2, args...)  vty_out2(vty, fmt1, fmt2, ##args)
#define FTPD_SHOW(vty, fmt, args...) vty_out(vty, fmt, ##args)
#define FTPD_DEBUG(fmt, args...) zlog_msg(NULL, ZLOG_DEBUG, fmt, ##args)

#ifdef MOD_FTP_SERVER_VER_1
#else
struct ftpd_msg
{
	char user[32];
	char pass[32];
	int retval;
};
#endif

void ftpd_init();

