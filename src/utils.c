/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file utils.c
 * @author sinclairsecurity
 * 
 * @brief Various utilities
 ***********/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <arpa/inet.h>

char *sin_strdup(const char *s)
{
    size_t len = strlen(s) + 1; // +1 for \0
    char *dup = malloc(len);
    if (dup) {
        memcpy(dup, s, len);
    }
    return dup;
}

int8_t validate_int_arg(const char *arg, uint16_t *store)
{
    char *endptr;
    errno = 0;
    long val = strtol(arg, &endptr, 10);

    if (errno != 0 || endptr == arg || *endptr != '\0' || val > 65535 || val < 0) {
        printf("Invalid integer input detected: %s. You will now be executed.\n", arg);
        *store = 0;
        return -1;
    }

    *store = (uint16_t)val;
    return 0;
}

int8_t is_valid_ip(const char *s)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, s, &(sa.sin_addr)) != 0;
}

void usage()
{
    printf("Usage: sinscan <command>\n");
    printf("\n");
    printf("Commands:\n");
    printf("- showip <domain1> <domain2>\n");
    printf("\n");
    printf("- scan <IP> <port>\n");
    printf("\tattempts TCP connection to the IP\n");
    printf("\tNOTE: If no port is passed, defaults to 80, 443, and 6443\n");
    printf("\n");
}