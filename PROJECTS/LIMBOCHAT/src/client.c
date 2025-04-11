/* LIMBOCHAT CLIENT: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>

#define SERVER_PORT 4190
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main()
{
    // Initialize client socket.
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check if the socket was created successfully.
    if (client_socket < 0)
    {
        perror("[x] Failed To Create Socket! [FAILED] ");
        return EXIT_FAILURE;
    }
    
    printf("[+] Socket Created Successfully! [SUCCESS]\n");

    // Define the server address structure.
    struct sockaddr_in server_address;
    socklen_t server_address_len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);
    
    if (connect(client_socket, (struct sockaddr*)&server_address, server_address_len) < 0)
    {
        perror("[x] Failed To Connect To Server! [FAILED] ");
        return EXIT_FAILURE;
    }
    else
    {
        printf("[+] Connection Successful! [SUCCESS]\n");
    }
    
    // Communicate with the server.
    char buffer[BUFFER_SIZE];

    // Receive message from the server.
    size_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
    {
        perror("[x] Failed To Receive Message From Server! [FAILED] ");
        return EXIT_FAILURE;
    }
    else
    {
        // Null terminate the received data.
        buffer[bytes_received] = '\0';
        printf("[Server]: %s\n", buffer);
    }
    
    // Send message to the server.
    char message[BUFFER_SIZE];
    int length;

    // fgets(message, BUFFER_SIZE, stdin);
    // length = strlen(message);
    // message[length - 1] = '\0';
    
    snprintf(message, );

    printf("WHO GOES!!!\n");
    printf("%s\n", message);
    printf("WHO GOES!!!\n");

    return EXIT_SUCCESS;
}