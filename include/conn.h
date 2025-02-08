/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file conn.h
 * @author sinclairsecurity
 * 
 * @brief Connect to an IP address and socket
 ***********/
#ifndef __CONN_H__
#define __CONN_H__

#include <stdint.h>

/**
 * Function: conn
 * @brief Connect to socket
 * @param node character pointer for IP address
 * @param port port to connect on
 * @return void
 */
int8_t conn(const char *node, uint16_t port);

/**
 * Function: scan
 * @brief Scan IP
 * @param node character pointer to IP
 * @param port port to connect on
 * @return void
 */
void scan(const char *node, uint16_t port);

#endif /* __CONN_H__ */