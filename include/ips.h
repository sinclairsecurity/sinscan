/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file ips.h
 * @author sinclairsecurity
 * 
 * @brief Show IP addresses for a list of hosts
 ***********/
#ifndef __IPS_H__
#define __IPS_H__

/**
 * Function: find
 * @brief Finds IP addresses for a given domain
 * @param domain character pointer for domain
 * @param addresses storage for IP addresses
 * @return void
 */
void find(const char *domain, char *addresses[]);

/**
 * Function show
 * @brief Prints IP addresses for a given domain
 * @param domain character pointer for domain
 * @return void
 */
void show(const char *domain);

#endif /* __IPS_H__ */