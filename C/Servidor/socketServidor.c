// Strings y errores
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Simbolos standard
#include <unistd.h>

// Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// Parametros del servidor
#define SERVER_PORT 8080
#define SERVER_HOST_ADDRESS "192.168.100.36"
#define BUFFER_SIZE 256
#define BACK_LOG 5

int main(int argc, char *argv[])
{
    printf("Hello, World!\n");
    printf("Socket Servidor\n");

    int socket_file_description, socket_connection_file_description; // Escucha y Conexion de descriptores
    unsigned int length;                                             // Tamano de la direccion del cliente

    struct sockaddr_in server, client;

    int len_recive, len_transmit = 0;

    char buffer_recive[BUFFER_SIZE];
    char buffer_transmit[BUFFER_SIZE];

    socket_file_description = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_file_description < 0)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }else{
        printf("[SERVER - ON]");
    }

    return 0;
}