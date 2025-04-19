/* LIMBOCHAT CENTRAL SERVER: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <sys/types.h>
 #include <sys/time.h>
#include <signal.h>
#include <crypt.h>


#define SERVER_PORT 4190
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024


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
int authenticate(Client* client);

// Global Variables.
int client_sockets[MAX_CLIENTS], max_sd, sd, activity, bytes_read;
int client_socket;
int server_socket;
FILE* userCred;
char* hashedPassword;
Client* clients;


int main()
{
    /* Clean Exit On Ctrl+C (optional) */
    
    // Register the signal handler.
    signal(SIGINT, handle_sigint);

    char buffer[BUFFER_SIZE];

    // Set of socket descriptors.
    fd_set readfds;

    // Initialize all client_sockets[i] to 0.
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_sockets[i] = 0;
    }
    

    /* Initialize TCP Server: socket(), bind(), listen() */

    // Create the server socket. 
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check if the socket was created successfully.
    if (server_socket <= 0)
    {
        perror("[x] Failed To Create Socket! [FAILED] ");
        return EXIT_FAILURE;
    }
    
    printf("[+] Socket Created Successfully! [SUCCESS]\n");

    // Allow multiple connections.
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("[x] Failed setsockopt! [FAILED] ");
        return EXIT_FAILURE;
    }
    
    // Define the server address structure.
    struct sockaddr_in server_address;
    socklen_t server_address_len = sizeof(server_address);
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);

    // Bind the socket to the server address.
    if (bind(server_socket, (struct sockaddr*)&server_address, server_address_len) < 0)    
    {
        perror("[x] Failed To Bind The Socket! [FAILED] ");
        return EXIT_FAILURE;
    }

    printf("[+] Socket Bound To Port %d [SUCCESS]\n", SERVER_PORT);
    
    // Listen for incoming connections; Maximum of 3 pending connections.
    if (listen(server_socket, 3) < 0)
    {
        printf("[x] Failed To Listen On The Server Address %s:%d [FAILED]\n", inet_ntoa(server_address.sin_addr), ntohs(SERVER_PORT));
        return EXIT_FAILURE;
    }

    printf("[+] Listening On Port %d...\n", SERVER_PORT);
    
    /* Accept One Client Connection */

    clients = malloc(MAX_CLIENTS * sizeof(Client));

    while (1)
    {
        // Clear the socket set.
        FD_ZERO(&readfds);

        // Add the server socket to set.
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;

        // Add child sockets to set.
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            // If it's a valid socket descriptor add it to read list.
            if (sd > 0)
            {
                FD_SET(sd, &readfds);
            }

            // Highest file descriptor number.
            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }
        
        // Wait for an activity on one of the sockets.
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            perror("[x] Failed To Select Socket! [FAILED] "); 
        }
        
        // If something happened on the master socket, then it's an incoming connection.
        if (FD_ISSET(server_socket, &readfds))
        {
            if((client_socket = accept(server_socket, (struct sockaddr*)&server_address, &server_address_len)) < 0)
            {
                perror("[x] Failed To Accept Incoming Client Connection [FAILED] ");
                return EXIT_FAILURE;
            }

            // Inform user of socket number - used in send and receive commands.
            printf("[+] New Client Accepted On Socket FD %d, IP: %s, Port: %d [SUCCESS]\n", client_socket, inet_ntoa(server_address.sin_addr), ntohs(SERVER_PORT));

            
            // AUTHENTICATION REQUIRED!!!
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                clients[i].socket_fd = client_socket;

                // Allow only authenticated users to chat.
                if (clients[i].is_authenticated != 1)
                {
                    char message[] = "[!] Only Authenticated Users Can Chat! [NOTICE]\n";
                    if (send(clients[i].socket_fd, message, strlen(message), 0) < 0)
                    {
                        perror("[x] Failed To Send Notice Message [FAILED] ");
                    }
                    
                    // Authenticate Client.
                    authenticate(&clients[i]);
                }
                
                // Add the new client socket to the array of sockets.
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = clients[i].socket_fd;
                    printf("[+] Added To List Of Sockets At Index %d [SUCCESS]\n", i);
                    break;
                }
            }
            
        }
        
        // Else it's some IO operation on a socket.
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds))
            {
                // Check if it was for closing, and also read the incoming message.
                if ((bytes_read = read(sd, buffer, BUFFER_SIZE)) == 0)
                {
                    // Somebody disconnected, get his details and print.
                    getpeername(sd, (struct sockaddr *)&server_address, &server_address_len);
                    printf("%s disconnected, ip %s, port %d \n", clients[i].username, inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));

                    // Close the socket and mark as 0 in list for reuse.
                    close(sd);
                    client_sockets[i] = 0;
                } 
                else
                {
                    // Null terminate the data read.
                    buffer[bytes_read] = '\0';
                    printf("[%s]: %s\n", clients[i].username, buffer);

                    // Broadcast the message to all clients.
                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if (client_sockets[i] != 0 && client_sockets[i] != sd)
                        {
                            if(send(client_sockets[i], buffer, strlen(buffer), 0) < 0)
                            {
                                perror("[x] Failed To Broadcast Message [FAILED] ");
                            }
                            printf("[+] Broadcast Successful! [SUCCESS]\n");
                        }
                    }
                    
                }
                
            }
            
        }
        

    }

    free(clients);

    return EXIT_SUCCESS;
}

// Cleans up used resources.
void cleanup()
{
    // Close the sockets.
    printf("\n[+] Closing The Sockets... [SUCCESS]\n");
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        close(client_sockets[i]);
    }
    
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
int authenticate(Client* client)
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
        bytes_received = recv(client->socket_fd, authChoice, sizeof(authChoice), 0);
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
            bytes_received = recv(client->socket_fd, creds, sizeof(Credentials), 0);
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
                if (send(client->socket_fd, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Success Message To The Client! [FAILED] ");
                }

                sleep(2);
                strncpy(client->username, creds->username, strlen(creds->username));
                client->is_authenticated = 1;
                return client->is_authenticated;
            }
            else
            {
                loginAttempt++;
                strcpy(authStatus, "[x] Invalid Credentials! [FAILED]\n");
                if (send(client->socket_fd, authStatus, strlen(authStatus), 0) < 0)
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
            bytes_received = recv(client->socket_fd, creds, sizeof(Credentials), 0);
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
                if (send(client->socket_fd, authStatus, strlen(authStatus), 0) < 0)
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
            if (send(client->socket_fd, authStatus, strlen(authStatus), 0) < 0)
                {
                    perror("[x] Failed To Send Failure Message To The Client! [FAILED] ");
                }
            sleep(2);
            strncpy(client->username, creds->username, strlen(creds->username));
            client->is_authenticated = 1;
            return client->is_authenticated;
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
        client->is_authenticated = 0;
        return client->is_authenticated;
    }

    free(creds);

}