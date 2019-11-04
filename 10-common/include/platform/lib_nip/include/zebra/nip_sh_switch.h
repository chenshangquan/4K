#ifndef __NIP_SH_SWITCH__
#define __NIP_SH_SWITCH__
#include "lib/vty.h"


extern unsigned char boot_to_shell;//0---not auto to shell, 1----auto to shell

int nip_switch_to_shell();

int nip_set_boot_to_shell(int opcode);

void config_shell_write(struct vty *);

void config_shell_erase(struct vty *);


#endif

