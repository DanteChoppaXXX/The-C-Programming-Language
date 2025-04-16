/* LIMBOCHAT CENTRAL SERVER: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <signal.h>
#include <crypt.h>


#define SERVER_PORT 4190
#define BUFFER_SIZE 1024

// Global Variables.
int client_socket;
int server_socket;
FILE* userCred;
char* hashedPassword;

// Client Credentials Structure.
typedef struct
{
    char username[32];
    char password[32];

} Credentials;

// Client Tracking Structure. 
typedef struct
{
    int socket_fd;
    char username[32];
    bool is_authenticated;

} Client;

// Function Prototype.
void cleanup();
void handle_sigint(int sig);
void authenticate();
char hashPassword(char* password);


int main()
{
    /* Clean Exit On Ctrl+C (optional) */
    
    // Register the signal handler.
    signal(SIGINT, handle_sigint);

    

    /* Initialize TCP Server: socket(), bind(), listen() */

    // Create a socket object. 
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
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
    
    // Initialize the client socket object with accept().
    client_socket = accept(server_socket, (struct sockaddr*)&server_address, &server_address_len);

    // Check if the client was accepted.
    if (client_socket < 0)
    {
        perror("[x] Failed To Accept Incoming Client Connection [FAILED] ");
        return EXIT_FAILURE;
    }

    printf("[+] New Client Accepted On Socket FD %d [SUCCESS]\n", client_socket);

    // Authenticate Client.
    authenticate();
    
    // Send a welcome message to the client.
    char message[] = "WELCOME TO LIMBO\n";
    
    if (send(client_socket, message, strlen(message), 0) < 0)
    {
        perror("[x] Failed To Send Message [FAILED] ");
    }
    else
    {
        printf("[+] Welcome Message Sent Successfully! [SUCCESS]\n\n");
    }
    
    /* Basic send/recv Loop With Client */
    
    while (1)
    {
        char buffer[BUFFER_SIZE];

        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Message From The Client! [FAILED] ");
            return EXIT_FAILURE;
        }
        else
        {
            buffer[bytes_received] = '\0';
            printf("[Client]: %s\n", buffer);
        }

        // Send message to client.
        char mBuffer[BUFFER_SIZE];
        int length;

        printf("[Server]: ");
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

// Cleans up used resources.
void cleanup()
{
    // Close the sockets.
    printf("\n[+] Closing The Sockets... [SUCCESS]\n");
    close(client_socket);
    close(server_socket);

    // Disconnection Message.
    printf("[+] Disconnected The Server [SUCCESS]\n");
}

// Handles clean exit on CTRL+C.
void handle_sigint(int sig)
{
    // Run Clean Up.
    cleanup();

    // Exit Gracefully.
    exit(0);
}

// Authenticates each incoming client.
void authenticate()
{
    // Each new client must pass through this before being allowed to chat.

    char authOptions[2][10] = {
        "/login",
        "/register"
    };
    char authChoice[10];
    char authStatus[50];
    
    ssize_t bytes_received;

    Credentials* creds = malloc(sizeof(Credentials));

    int loginAttempt = 0;

    while (loginAttempt < 3)
    {
        // Buffers for credential validation.
        char buffer[85];
        char compareBuffer[BUFFER_SIZE];

        // Receive the client authentication choice.
        bytes_received = recv(client_socket, authChoice, sizeof(authChoice), 0);
        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Authentication Choice From Client! [FAILED] ");
        }
        else
        {
            authChoice[strcspn(authChoice, "\n")] = '\0';
            printf("%s\n", authChoice);
        }
        
        // LOGIN PROCESS.
        if (strcmp(authChoice, authOptions[0]) == 0)
        {
            // Do LOGIN process.

            // Receive credentials from the client.
            bytes_received = recv(client_socket, creds, sizeof(Credentials), 0);
            if (bytes_received < 0)
            {
                perror("[x] Failed To Receive Credentials From The Client! [FAILED] ");
            }
            else
            {
                printf("%s:%s\n", creds->username, creds->password);
            }
            

            hashedPassword = crypt(creds->password, creds->username);
            if (hashedPassword != NULL)
            {
                snprintf(buffer, sizeof(buffer), "%s:%s\n", creds->username, hashedPassword);
            } 
            else
            {
                perror("[x] Error Hashing Password! [FAILED] ");
            }
            
            // Validate the credentials. (Check if username:hashedpassword exist in the users credential file.)
            userCred = fopen("./users.txt", "r");
            if (userCred == NULL)
            {
                perror("[x] Failed To Open File! [FAILED] ");
            }
            
            fread(compareBuffer, BUFFER_SIZE, 1, userCred);

            // Condition for valid credentials.
            if (strstr(compareBuffer, buffer) != NULL)
            {
                // Copy success message into the prompt buffer.
                strcpy(authStatus, "[+] Authentication Successful! [SUCCESS]\n");

                // Send the success message to the client.
                if (send(client_socket, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Success Message To The Client! [FAILED] ");
                }

                sleep(2);
                break;
            }
            else
            {
                loginAttempt++;
                strcpy(authStatus, "[x] Invalid Credentials! [FAILED]\n");
                if (send(client_socket, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Failure Message To The Client! [FAILED] ");
                }
                continue;
            }
        }
        
        // REGISTRATION PROCESS.
        else if (strcmp(authChoice, authOptions[1]) == 0)
        {
            // Do REGISTRATION Process.

            // Receive the client's response.
            bytes_received = recv(client_socket, creds, sizeof(Credentials), 0);
            if (bytes_received < 0)
            {
                perror("[x] Failed To Receive Credentials From The Client! [FAILED] ");
                
            }
            else
            {
                printf("%s:%s\n", creds->username, creds->password);
            }

            // Check if username already exist.
            userCred = fopen("./users.txt", "r");
            if (userCred == NULL)
            {
                perror("[x] Failed To Open File! [FAILED] ");
            }
            
            fread(compareBuffer, BUFFER_SIZE, 1, userCred);

            fclose(userCred);

            if (strstr(compareBuffer, creds->username) != NULL)
            {
                loginAttempt++;
                strcpy(authStatus, "[x] Username Already Exist! [FAILED]\n");
                if (send(client_socket, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Failure Message To The Client! [FAILED] ");
                }
                continue;
            }

            // Save username and password to file.
            userCred = fopen("./users.txt", "a");
            if (userCred == NULL)
            {
                perror("[x] Failed To Open File! [FAILED] ");
            }
            
            // Hash the password for more security.
            hashedPassword = crypt(creds->password, creds->username);
            if (hashedPassword != NULL)
            {
                fprintf(userCred, "%s:%s\n", creds->username, hashedPassword);
            } 
            else
            {
                perror("[x] Error Hashing Password! [FAILED] ");
            }

            fclose(userCred);

            // Copy success message into the prompt buffer.
            strcpy(authStatus, "[+] Registration Successful! [SUCCESS]\n");
            if (send(client_socket, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Failure Message To The Client! [FAILED] ");
                }
            sleep(2);
            break;
        }
        else
        {
            printf("[x] Invalid Choice! [FAILED]\n");           
            loginAttempt++;
        }
    }

    if (loginAttempt == 3)
    {
        perror("[x] Failed To Authenticate The Client! [FAILED] ");
        sleep(3);
    }

    free(creds);

}