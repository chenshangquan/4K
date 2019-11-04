/*
  **
  ** dnss_cache.h - function prototypes for the cache handling routines
  **
  ** Part of the drpoxy package by Matthew Pratt. 
  **
  ** Copyright 1999 Matthew Pratt <mattpratt@yahoo.com>
  **
  ** This software is licensed under the terms of the GNU General 
  ** Public License (GPL). Please see the file COPYING for details.
  ** 
  **
*/
#ifndef _DNS_SER_CACHE
#define _DNS_SER_CACHE

/* We assume cache entries are in the follwing form:

<name> <ip> <time_created>

Where "time_created" in the time the entry was created (seconds since 1/1/1970)
*/

/*
 * Search the cache "filename" for the first entry with name in the first field
 * Copies the corresponding IP into the char array "ip".
 * RETURNS: 0 if matching entry not found else 1.
 */
int cache_lookup_name(char *name,  u_long m_ip[DNS_IP_NUM]);

/*
 * Search the cache "filename" for the first entry with ip in the second field.
 * Copies the corresponding Name into the char array "result".
 * RETURNS: 0 if matching entry not found else 1.
 */
int cache_lookup_ip(char *ip, char result[DNS_FILE_BUF_SIZE]);
/*
 * Appends the "name" and "ip" as well as the current time (seconds 
 * since 1/1/1970), to the cache file "filename".
 */
void cache_name_append(char *name, char *ip, u_long ttl,  
                                                    char *append_mode);
/*
 * Scans the cache file "filename" for entries whose time_created fields
 * is greater than the current time minus the time they were created, and
 * removes them from the cache.
 */
int cache_lookup_name_ip (char *name, char *ip);
void cache_purge(u_long time_to_del);
void cache_delete_name(char *m_name);
void cache_delete_name_ip(char *m_name, char *m_ip);
 int cache_statistic (void);
void cache_show(struct vty *vty);

void cache_write2Terminal(struct vty *vty);

#endif

/* EOF */
