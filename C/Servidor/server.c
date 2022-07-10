#include <unistd.h>

/* sockets */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h>
#include <string.h>

// fonction pour comparer deux strings : renvoie 0 si les valeurs sont égales
// et -1 sinon

/* server parameters */
#define SERV_PORT 10080                 /* port */
#define SERV_HOST_ADDR "192.168.100.36" /* IP, only IPV4 support  */
#define BUF_SIZE 1024                   /* Buffer rx, tx max size  */
#define BACKLOG 5                       /* Max. client pending connections  */

int compare_strings(char a[], char b[])
{
    int c = 0;
    while (a[c] == b[c])
    {
        if (a[c] == '\0' || b[c] == '\0')
            break;
        c++;
    }
    if (a[c] == '\0' && b[c] == '\0')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int main()
{
    // déclaration des variables : Serveur et deux Clients
    int sockfd, client1, client2;
    struct sockaddr_in server_addr;
    struct sockaddr_storage serverStorage;
    socklen_t len;
    char buffer[BUF_SIZE];

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully created..\n");
    }
    /* assign IP, SERV_PORT, IPV4 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);

    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    /* Bind socket */
    ;
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully binded \n");
    }

    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(server_addr.sin_port));
    }

    // lier le serveur et les deux clients
    len = sizeof serverStorage;

    /* Accept the data from incoming sockets in a iterative way */
    client1 = accept(sockfd, (struct sockaddr *)&serverStorage, &len);
    client2 = accept(sockfd, (struct sockaddr *)&serverStorage, &len);

    int cmdEXIT = 0;

    if (client1 < 0 || client2 < 0)
    {
        fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {

        while (cmdEXIT == 0)
        {
            /* receive message from client1 */
            // recv(client1, buffer, BUF_SIZE, 0);
            read(client1, buffer, sizeof(buffer));
            /* send it back to client2 */
            printf("%s\nSend to client2\n", buffer);
            // send(client2, buffer, BUF_SIZE, 0);
            write(client2, buffer, strlen(buffer));

            /* Exit the loop if the client1 types exit */
            if (compare_strings(buffer, "exit") == 0)
            {
                cmdEXIT = 1;
            }
            else
            {
                /* otherwise empty the buffer */
                memset(&buffer[0], 0, sizeof(buffer));
                /* receive message from client2 */
                //recv(client2, buffer, BUF_SIZE, 0);
                read(client2, buffer, sizeof(buffer));
                /* send it back to client1 */
                printf("%s\nSend to client1\n", buffer);
                //send(client1, buffer, BUF_SIZE, 0);
                write(client1, buffer, strlen(buffer));
                /* if client2 sent "exit" */
                if (compare_strings(buffer, "exit") == 0)
                {
                    cmdEXIT = 1;
                }
            }
        }
    }
    return 0;
}