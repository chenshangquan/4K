#ifndef _ACL_PROC_H
#define _ACL_PROC_H

#define ACL_PROC_MOD_ACL 0
#define ACL_PROC_MOD_NAT 1

int acl_proc_table_register(int modname, char* tablename);
int acl_proc_table_unregister(int modname);
void acl_proc_table_empty(int modname);
int acl_proc_add_allrule(int modname, int verdict_type, char* chain, struct interface* ifp,
                        void* target_info, int rulenum);
int acl_proc_insert_rule(int modname, int verdict_type, int rulenum, int subnum);
int acl_proc_delete_rule(int modname, int verdict_type, int rulenum, int subnum);
int acl_proc_replace_rule(int modname, int verdict_type, int rulenum, int subnum);
int acl_proc_delete_allrule(int modname, char* chain, struct interface* ifp, int rulenum);
void acl_proc_set_policy(char* policy);

#endif

