/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file utils.h
 * @author sinclairsecurity
 * 
 * @brief Various utilities
 ***********/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdint.h>

/**
 * Function: sin_strdup
 * @brief Custom implementation of strdup
 * @param s character pointer t ostring
 * @return character pointer to duplicated string
 */
char *sin_strdup(const char *s);

/**
 * Function: validate_int_arg
 * @brief Ensures passed argument is an int
 * @param arg the argument passed to the program
 * @param store integer storage if successful
 * @return status (0 for success, -1 for failure)
 */
int8_t validate_int_arg(const char *arg, uint16_t *store);

/**
 * Function: is_valid_ip
 * @brief Validates if the argument is a valid IP address
 * @param s character pointer to stirng
 * @return status (0 for success, -1 for failure)
 */
int8_t is_valid_ip(const char *s);

/**
 * Function: usage
 * @brief Prints the usage of sinscan
 * @return void
 */
void usage();

#endif /* __UTILS_H__ */