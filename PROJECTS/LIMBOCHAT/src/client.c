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
char* hashedPassword;

// Client Credential Structure.
typedef struct
{
    int socket_fd;
    char username[32];
    char password[50];

} Client;


// Function Prototype.
void cleanup();
void handle_sigint(int sig);
void authenticate();

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
        perror("[x] Failed To Connect To The Server! [FAILED] ");
        return EXIT_FAILURE;
    }
    else
    {
        printf("[+] Connection Successful! [SUCCESS]\n");
    }

    authenticate();
        
    /* Basic send/recv Loop With Client */

    while (1)
    {
        // Communicate with the server.
        char buffer[BUFFER_SIZE];

        // Receive message from the server.
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Message From The Server! [FAILED] ");
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

void authenticate()
{
<<<<<<< HEAD
    // Authenticate with the server in order to chat with other users.
    char authMessage[50];
    char authChoice[10];
    char username[32];
    char password[50];
    ssize_t bytes_received;
    int authStatus = -1;

    while (authStatus < 0)
    {
        // Receive authentication message from the server.
        bytes_received = recv(client_socket, authMessage, strlen(authMessage),0);
        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Authentication Message From The Server! [FAILED] ");
        }
        else
        {
            // Null terminate the received data.
            authMessage[bytes_received] = '\0';
            printf("%s\n", authMessage);
        }

        fgets(authChoice, 10, stdin);
        authChoice[strlen(authChoice) - 1] = '\0';

        // Send response to the server.
        if (send(client_socket, authChoice, strlen(authChoice), 0) < 0)
        {
            perror("[x] Failed To Send Response To The Server! [FAILED] ");
        }

        // Receive username prompt from the server.
        bytes_received = recv(client_socket, authMessage, strlen(authMessage),0);

        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Username Prompt From The Server! [FAILED] ");
        }
        else
        {
            // Null terminate the received data.
            authMessage[bytes_received] = '\0';
            printf("%s\n", authMessage);
        }

        fgets(username, 32, stdin);
        username[strlen(username) - 1] = '\0';

        // Send username to the server.
        if (send(client_socket, username, strlen(username), 0) < 0)
        {
            perror("[x] Failed To Send Username To The Server! [FAILED] ");
        }

        // Receive password prompt from the server.
        bytes_received = recv(client_socket, authMessage, strlen(authMessage),0);

        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Password Prompt From The Server! [FAILED] ");
        }
        else
        {
            // Null terminate the received data.
            authMessage[bytes_received] = '\0';
            printf("%s\n", authMessage);
        }

        fgets(password, 50, stdin);
        password[strlen(password) - 1] = '\0';

        // Send password to the server.
        if (send(client_socket, password, strlen(password), 0) < 0)
        {
            perror("[x] Failed To Send Password To The Server! [FAILED] ");
        }

        // Receive authentication status from the server.
        authStatus = recv(client_socket, authMessage, strlen(authMessage),0);

        if (authStatus < 0)
        {
            perror("[x] Failed To Receive Password Prompt From The Server! [FAILED] ");
        }
        else
        {
            // Null terminate the received data.
            authMessage[authStatus] = '\0';
            printf("%s\n", authMessage);
        }

        }
    
    
=======
    // Each new client must pass through this before being allowed to chat.
    char authOptions[2][10] = {
        "/login",
        "/register"
    };
    char authChoice[10];
    char username[32];
    char password[50];

    int loginAttempt = 0;

    Client* client = malloc(sizeof(Client));

    while (loginAttempt < 3)
    {
        printf("LOGIN or REGISTER [enter /login or /register]: ");
        scanf("%s", authChoice);
        
        if (strcmp(authChoice, authOptions[0]) == 0)
        {
            // Do LOGIN process.
            printf("Enter username: ");
            scanf("%s", username);
            strncpy(client->username, username, sizeof(client->username));


            printf("Enter password: ");
            scanf("%s", password);
            strncpy(client->password, password, sizeof(client->password));

            if (send(client_socket, client, sizeof(Client), 0) < 0)
            {
                perror("[x] Failed To Send Message [FAILED] ");
            }
            else
            {
                printf("[+] Username And Password Sent Successfully [SUCCESS]\n");
            }

        }
        else if (strcmp(authChoice, authOptions[1]) == 0)
        {
            // Do REGISTRATION process.
            printf("Enter username: ");
            scanf("%s", username);
            strncpy(client->username, username, sizeof(client->username));

            printf("Enter password: ");
            scanf("%s", password);
            strncpy(client->password, password, sizeof(client->password));

            printf("[+] Registering ... [SUCCESS]\n");
            sleep(2);
            break;
        }
        else
        {
            printf("Invalid Choice! (enter %s or %s)\n", authOptions[0], authOptions[1]);
            loginAttempt++;
        }
    }

    if (loginAttempt == 3)
    {
        perror("\n[x] Too Many Authentication Attempt! [YOU'RE FIRED!!!] ");
        
    }

>>>>>>> ed0c236ee148cd71c6f368ce6cfd4879e02753f3
}