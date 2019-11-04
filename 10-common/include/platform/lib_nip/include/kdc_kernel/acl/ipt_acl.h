#ifndef _IPT_ACL_H
#define _IPT_ACL_H

struct ipt_acl
{
	int verdict;
	unsigned int rulenum;
	unsigned int subnum;
};

#endif
