/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file ips.c
 * @author sinclairsecurity
 * 
 * @brief Find IP addresses for a list of hosts
 ***********/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "utils.h"

#define N_ADDRS 100

void find(const char *domain, char *addresses[])
{
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(domain, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "Error getting IP address info for %s: %s\n", domain, gai_strerror(status));
        return;
    }

    int addr_count = 0;
    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));

        addresses[addr_count] = sin_strdup(ipstr);
        addr_count++;
        if (addr_count >= N_ADDRS) {
            break; // prevent overflow
        }
    }

    freeaddrinfo(res);
}

void show(const char *domain)
{
    char *addrs[N_ADDRS] = {0};
    find(domain, addrs);

    printf("IP addresses for %s\n", domain);
    for (int i = 0; i < N_ADDRS && addrs[i] != NULL; i++) {
        printf("  %s\n", addrs[i]);
        free(addrs[i]);
    }
}