#ifndef VTY_CHNODE_H
#define VTY_CHNODE_H

#include <lib/zebra.h>

struct vty_chnode
{
    int node;
    int (*func)(struct vty* vty, int node);
};

void vty_chnode_init();
int vty_change_node(struct vty* vty, int node);
int vty_chnode_reg(int node, int (*func)(struct vty* vty, int node));
int vty_chnode_unreg(int node);

#endif
