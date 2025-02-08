/************
 * sinscan - Scan IPs, sockets, and domains
 * 
 * @file conn.c
 * @author sinclairsecurity
 * 
 * @brief Connect to an IP address and socket
 ***********/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>


int8_t conn(const char *node, uint16_t port)
{
    struct addrinfo hints, *res;
    int8_t status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char port_str[6];
    snprintf(port_str, sizeof(port_str), "%d", port);

    if ((status = getaddrinfo(node, port_str, &hints, &res)) != 0) {
        fprintf(stderr, "\tError: %s\n", gai_strerror(status));
        freeaddrinfo(res);
        return -1;
    }

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    int8_t sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("\tError");
        close(sockfd);
        freeaddrinfo(res);
        return -1;
    }

    status = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if (status == -1) {
        perror("\tError");
        close(sockfd);
        freeaddrinfo(res);
        return -1;
    }

    status = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    if (status == -1) {
        perror("\tError");
        close(sockfd);
        freeaddrinfo(res);
        return -1;
    }

    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        if (errno == EINPROGRESS) {
            fprintf(stderr, "\tConnection timed out.\n");
        } else {
            perror("\tError");
        }
        close(sockfd);
        freeaddrinfo(res);
        return -1;
    } else {
        printf("\tConnected successfully!\n");
    }

    close(sockfd);
    freeaddrinfo(res);

    return 0;
}

void scan(const char *node, uint16_t port)
{
    uint16_t ports[3];
    uint8_t num_ports;

    if (port == 0) {
        uint16_t default_ports[] = {80, 443, 6443};
        memcpy(ports, default_ports, sizeof(default_ports));
        num_ports = 3;
    } else {
        ports[0] = port;
        num_ports = 1;
    }

    for (size_t i = 0; i < num_ports; i++) {
        printf("Trying %s:%d...\n", node, ports[i]);
        conn(node, ports[i]);
        printf("\n");
    }
}