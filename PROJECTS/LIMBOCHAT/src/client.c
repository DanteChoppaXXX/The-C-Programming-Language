/* LIMBOCHAT CLIENT: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <signal.h>
#include <pthread.h>

#define SERVER_PORT 4190
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

// Global Variables.
int client_socket;
char* hashedPassword;
pthread_t send_thread, recv_thread;

// Client Credentials Structure.
typedef struct
{
    char username[32];
    char password[32];

} Credentials;

// List of commands.
char commands[3][10] = {
    "/help",
    "/users",
    "/quit",
};


// Function Prototype.
void cleanup();
void handle_sigint(int sig);
void authenticate(char* username);
void* send_handler(void* arg);
void* recv_handler(void* arg);

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

    char username[32];
    authenticate(username);

    time_t raw_time;
    struct tm *timeinfo;

    time(&raw_time);
    timeinfo = localtime(&raw_time);

    int hour = timeinfo->tm_hour;
    int mins = timeinfo->tm_min;

    printf("[!] Logged In At %02d:%02d US-Eastern-Time [!]\n", hour, mins);


    // Create threads for sending and receiving messages.
    pthread_create(&recv_thread, NULL, recv_handler, (void *)&client_socket);
    sleep(3);
    pthread_create(&send_thread, NULL, send_handler, (void *)username);

    // Wait for threads to finish.
    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);
    

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

void authenticate(char* username)
{
    // Each new client must pass through this before being allowed to chat.
    char authOptions[2][10] = {
        "/login",
        "/register"
    };
    char authChoice[10];
    char authStatus[50];
    ssize_t bytes_received;

    int loginAttempt = 0;

    Credentials* creds = malloc(sizeof(Credentials));

    while (loginAttempt < 3)
    {
        printf("LOGIN or REGISTER [enter /login or /register]: ");
        scanf("%s", authChoice);

        if (send(client_socket, authChoice, sizeof(authChoice), 0) < 0)
        {
            perror("[x] Failed To Send Credentials To The Server! [FAILED] ");
            continue;
        }
        
        // Check for valid authentication choice.
        if (strstr(authOptions[0], authChoice) != NULL || strstr(authOptions[1], authChoice) != NULL)
        {
            // AUTHENTICATION PROCESS.

            printf("Enter username: ");
            scanf("%s", creds->username);


            printf("Enter password: ");
            scanf("%s", creds->password);
            fflush(NULL);

            if (send(client_socket, creds, sizeof(Credentials), 0) < 0)
            {
                perror("[x] Failed To Send Credentials To The Server! [FAILED] ");
            }
            else
            {
                printf("[+] Credentials Sent Successfully [SUCCESS]\n");
            }

            bytes_received = recv(client_socket, authStatus, sizeof(authStatus), 0);
            if (bytes_received <= 0)
            {
                perror("[x] Failed To Receive Authentication Status From The Server! [FAILED] ");
            }
            else
            {
                authStatus[strcspn(authStatus, "\n")] = '\0';
                printf("%s\n", authStatus);

                if (strstr(authStatus, "FAILED") != NULL)
                {
                    loginAttempt++;
                    continue;
                }
                else
                {
                    strncpy(username, creds->username, sizeof(creds->username));
                    //sleep(5);
                    break;
                }
                
            }
        }
        else
        {
            printf("[x] Invalid Choice! [FAILED]\n");           
            loginAttempt++;
            continue;
        }
        
    }
    if (loginAttempt == 3)
    {
        perror("\n[x] Too Many Authentication Attempt! [YOU'RE FIRED!!!] ");
        exit(1);
    }

    free(creds);
}


void* send_handler(void* arg)
{
    char* username = arg;

    time_t raw_time;
    struct tm *timeinfo;

    time(&raw_time);
    timeinfo = localtime(&raw_time);

    int hour = timeinfo->tm_hour;
    int mins = timeinfo->tm_min;
    
    /* Sending logic. */
    while (1)
    {
        // Send message to the server.
        char mBuffer[BUFFER_SIZE];
        char userBuffer[BUFFER_SIZE];
    
        printf("[%02d:%02d] [%s]: ",hour, mins, username);
        fgets(mBuffer, BUFFER_SIZE, stdin);
        mBuffer[strcspn(mBuffer, "\n")] = '\0';

        if (strcmp(mBuffer, "") == 0)
        {
            continue;
        }
        
        snprintf(userBuffer, BUFFER_SIZE, "[%02d:%02d][%s]: %s", hour, mins, username, mBuffer);
    
        if (send(client_socket, userBuffer, strlen(userBuffer), 0) < 0)
        {
            perror("[x] Failed To Send Message [FAILED] ");
        }
        
    }

    return NULL;
}

void* recv_handler(void* arg)
{
    /* Receiving logic. */
    while (1)
    {
        // Receive message from the server.
        char buffer[BUFFER_SIZE];
        
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0)
        {
            perror("[x] Failed To Receive Message From The Server! [FAILED] ");
        }
        else
        {
            // Null terminate the received data.
            buffer[bytes_received] = '\0';
            printf("%s\n", buffer);
        }

        
    }

    return NULL;
}


/* 
    *TO-DO
    0. Multi-Threading for sending and receiving. ✅
    1. Add list of commands.
    2. Add timestamps ([04:19][username]: <msg>).
    3. Add Join/Leave Notifications.
    4. Free the disconnected client socket.
    
*/

