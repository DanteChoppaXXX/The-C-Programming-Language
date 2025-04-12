/* LIMBOCHAT CLIENT: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <signal.h>

#define SERVER_PORT 4190
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

// Global Variables.
int client_socket;

// Function Prototype.
void cleanup();
void handle_sigint(int sig);

int main()
{
    /* Clean Exit On Ctrl+C (optional) */
    
    // Register the signal handler.
    signal(SIGINT, handle_sigint);

    // Initialize client socket.
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
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
    
    /* Basic send/recv Loop With Client */

    while (1)
    {
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
        char mBuffer[BUFFER_SIZE];
        int length;

        printf("[Client]: ");
        fgets(mBuffer, BUFFER_SIZE, stdin);
        length = strlen(mBuffer);
        mBuffer[length - 1] = '\0';

        if (send(client_socket, mBuffer, strlen(mBuffer), 0) < 0)
        {
            perror("[x] Failed To Send Message [FAILED] ");
        }
        else
        {
            printf("[SUCCESS]\n");
        }
        
    }

    return EXIT_SUCCESS;
}

void cleanup()
{
    // Close the sockets.
    printf("\n[+] Closing The Socket... [SUCCESS]\n");
    close(client_socket);

    // Disconnection Message.
    printf("[+] Disconnected From The Server [SUCCESS]\n");
}

void handle_sigint(int sig)
{
    // Run Clean Up.
    cleanup();

    // Exit Gracefully.
    exit(0);
}
