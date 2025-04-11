/* LIMBOCHAT CENTRAL SERVER: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>


#define SERVER_PORT 4190
#define BUFFER_SIZE 1024

int main()
{
    /* Initialize TCP Server: socket(), bind(), listen() */

    // Create a socket object. 
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check if the socket was created successfully.
    if (server_socket < 0)
    {
        perror("[x] Failed To Create Socket! [FAILED] ");
        return EXIT_FAILURE;
    }
    
    printf("[+] Socket Created Successfully! [SUCCESS]\n");

    // Define the server address structure.
    struct sockaddr_in server_address;
    socklen_t server_address_len = sizeof(server_address);
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);
    
    // printf("%d\n", server_socket);

    // Bind the socket to the server address.
    if (bind(server_socket, (struct sockaddr*)&server_address, server_address_len) < 0)    
    {
        perror("[x] Failed To Bind The Socket! [FAILED] ");
        return EXIT_FAILURE;
    }

    printf("[+] Socket Bound To Port %d [SUCCESS]\n", SERVER_PORT);
    
    // Listen for incoming connections.
    if (listen(server_socket, 3) < 0)
    {
        perror("[x] Failed To Listen On The Server Address [FAILED] ");
        return EXIT_FAILURE;
    }

    printf("[+] Listening On Port %d...\n", SERVER_PORT);
    
    /* Accept One Client Connection */
    
    // Declare a client socket object.
    int client_socket;
    client_socket = accept(server_socket, (struct sockaddr*)&server_address, &server_address_len);

    // Check if the client was accepted.
    if (client_socket < 0)
    {
        perror("[x] Failed To Accept Incoming Client Connection [FAILED] ");
        return EXIT_FAILURE;
    }

    printf("[+] New Client Accepted On Socket FD %d [SUCCESS]\n", client_socket);
    
    // Send a welcome message to the client.
    char message[] = "WELCOME TO LIMBO\n";
    
    if (send(client_socket, message, strlen(message), 0) < 0)
    {
        perror("[x] Failed To Send Message [x] ");
    }
    else
    {
        printf("[+] Welcome Message Sent Successfully! [SUCCESS]\n");
    }
    
    /* Basic send/recv Loop With Client */
    while (1)
    {
        
        
    }
    

    /* Clean Exit On Ctrl+C (optional) */
    /* code */

    return EXIT_SUCCESS;
}