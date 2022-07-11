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

/* server parameters */
#define SERV_PORT 10080                 /* port */
#define SERV_HOST_ADDR "192.168.100.36" /* IP, only IPV4 support  */
#define BUF_SIZE 1024                   /* Buffer rx, tx max size  */
#define BACKLOG 5

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
        return 0;
    else
        return -1;
}

int main()
{
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in server_addr;
    socklen_t len;
    int cmdEXIT = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);
    len = sizeof server_addr;

    connect(sockfd, (struct sockaddr *)&server_addr, len);

    printf("Client 1 : ");
    scanf(" %[^\n]s", buffer);
    send(sockfd, buffer, sizeof buffer - 1, 0);

    while (cmdEXIT == 0)
    {
        if (compare_strings(buffer, "exit") == -1)
        {
            /* empty the buffer */
            memset(&buffer[0], 0, sizeof(buffer));
            /*  the value of recv which is equal to 1 if recv does not have
                still received message
                otherwise, it is equal to the number of bits received   */
            int recive_value = recv(sockfd, buffer, sizeof buffer - 1, 0);
            /* if recv is not equal to 1 => a message has been received */
            if (recive_value != 1)
            {
                
                if (compare_strings(buffer, "exit") == -1)
                {
                    /* display the message from Client2 */
                    printf("Client 2 : ");
                    printf("%s\n", buffer);
                    /*  empty the buffer    */
                    memset(&buffer[0], 0, sizeof(buffer));
                }
                /* if Client2 sent "exit"  */
                else
                {
                    cmdEXIT = 1;
                }
            }
            /*  if rcv is equal to 1 => no message received */
            else
            {
                /* Client1 can enter his message */
                printf("Client 1 : ");
                scanf(" %[^\n]s", buffer);
                /* send it to Client2   */
                send(sockfd, buffer, sizeof buffer - 1, 0);
            }
        }
        // End loop
        else
        {
            cmdEXIT = 1;
        }
    }

    return 0;
}