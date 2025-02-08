/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file sinscan.c
 * @author sinclairsecurity
 * 
 * @brief Main program
 ***********/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "ips.h"
#include "conn.h"
#include "utils.h"

#define N_ADDRS 100

void handle_showip(int argc, char *argv[]);
void handle_scan(const char *target, uint16_t port);
void handle_scan_domain(const char *target, uint16_t port);

int main(int argc, char *argv[]) 
{
    if (argc < 3) {
        usage();
        return 1;
    }

    const char *showip_opt = "showip";
    const char *scan_opt = "scan";

    if (strcmp(argv[1], showip_opt) == 0) {
        handle_showip(argc, argv);
    } else if (strcmp(argv[1], scan_opt) == 0) {
        if (argc == 4) {
            uint16_t port;
            if (validate_int_arg(argv[3], &port) == 0) {
                handle_scan(argv[2], port);
            } else {
                usage();
                return 1;
            }
        } else if (argc > 4) {
            usage();
            return 1;
        } else {
            handle_scan(argv[2], 0);
        }
    } else {
        usage();
        return 1;
    }
    
    return 0;
}

void handle_showip(int argc, char *argv[])
{
    for (int i = 2; i < argc; i++) {
        show(argv[i]);
        printf("\n");
    }
}

void handle_scan(const char *target, uint16_t port)
{
    if (is_valid_ip(target)) {
        scan(target, port);
    } else {
        handle_scan_domain(target, port);
    }
}

void handle_scan_domain(const char *target, uint16_t port)
{
    char *addrs[N_ADDRS] = {0};
    find(target, addrs);

    for (size_t i = 0; i < N_ADDRS && addrs[i] != NULL; i++) {
        scan(addrs[i], port);
    }
}