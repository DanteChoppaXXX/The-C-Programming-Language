/* LIMBOSHELL: [-- Description of the Program --] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/errno.h>
#include <signal.h>

#define BUFFER_SIZE 1024


int main()
{
    printf("Limbo $hell...\n");
    // Create command input buffer.
    char command[BUFFER_SIZE];
    
    // Display a prompt.
    printf("[#]> ");
    fflush(stdout);

    // Start an infinite loop to keep the shell running.
    while ((atoi(fgets(command, BUFFER_SIZE, stdin))) != EOF)
    {
        

        
        
        // Read input.
        // fgets(command, BUFFER_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';

        printf("%s\n", command);

        printf("[#]> ");
        fflush(stdout);

        // Parse the command.
        /* code */

        // Execute the command.
        /* code */
        
        // Repeat.
    } 

    printf("Exiting...\n");
    
    return EXIT_SUCCESS;
}