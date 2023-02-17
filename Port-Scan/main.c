#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int sock, port;
    struct sockaddr_in target;

    // Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    // Set parameters of server
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr("127.0.0.1");

    // All 65535 ports
    for (port = 1; port <= 65535; port++) {
        target.sin_port = htons(port);
        if (connect(sock, (struct sockaddr *)&target, sizeof(target)) == 0) {
            printf("Puerto %d abierto\n", port);
        }
    }

    close(sock);

    return 0;
}

//Based on TCP/IP III Douglas Comer