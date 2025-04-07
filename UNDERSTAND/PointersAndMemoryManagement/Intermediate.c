#include <stdio.h>
#include <stdlib.h>

/*
Intermediate Level: Dynamic Memory Allocation
Task:
Write a program that:

Asks the user for a number n.
Dynamically allocates memory for n integers using malloc().
Fills the allocated memory with numbers from 1 to n.
Prints the numbers stored in memory.
Frees the allocated memory.

Concepts Covered: malloc(), accessing dynamically allocated memory, free().
*/

int main()
{
    // Declare an integr variable.
    int number;
    // Prompt the user for a integer number.
    printf("Enter a number: \n");
    scanf("%d", &number);

    int* numbers = malloc(number * sizeof(int));
    if (numbers == NULL)
    {
        perror("Memory Allocation Failed!");
        return EXIT_FAILURE;
    }

    // Fill the allocated memory with numbers from 1 to user's number.
    for (int i = 0; i < number; i++)
    {
        numbers[i] = i + 1;
    }

    // Display the numbers stored in memory.

    // Using array indexing.
    for (int i = 0; i < number; i++)
    {
        printf("Number: %d\n", numbers[i]);
    }
    
    // Using pointer arithmetics.
    for (int i = 0; i < number; i++)
    {
        printf("Number %d\n", *numbers);
        numbers++;
    }

    // Return the pointer to the original/initial point before freeing (to prevent invalid pointer error).
    numbers = &numbers[0 - number];

    // Free the allocated memory after use.
    free(numbers);

    return EXIT_SUCCESS;
}