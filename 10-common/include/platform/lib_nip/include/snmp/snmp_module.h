/* all function macro define for snmp modules */

/* ------------------- feixp add start ------------------------- */
#define MOD_SNMP_ZEBRA_0
/*first change for snmp at nip */

#define MOD_SNMP_ZEBRA_0_1 
/*-----------------------
*
 date:2005/10/08 17:32
 purpose: free ----XFREE by the struct netsnmp_data_list member free_func
*/

/*#define MOD_SNMP_ZEBRA_0_2*/
/*-----------------------------------
  date: 2005/10/11 10:41
  purpose:把snmp_log.c用nip 的zlog代替。

*/

/*#define MOD_SNMP_USING_FORK*/
/*-----------------------------------
  日期: 2006-7-10
  作者: Yuanyi Zhang
  描述: 使用Fork产生一个新进程来运行Agent Master,
       如果没有定义这个宏,则Agent Master将在线程中运行
*/
