#include <stdio.h>
#include <stdlib.h>

/*
Advanced Level: Pointer Arithmetic & Memory Management
Task:
Write a function that:

Takes an array of integers (dynamically allocated) and its size as input.
Uses pointer arithmetic to find and return the sum of all elements in the array.
The function should not use array indexing ([]).
In main(), dynamically allocate an array, call the function, and print the sum.
Ensure proper memory deallocation (free()).

Concepts Covered: Pointer arithmetic, dynamic memory allocation, avoiding memory leaks.
*/

int sumOfArray(int* array, int size);

int main()
{
    int numOfSubjects;
    //int sumOfSubjectScores;

    // Get the number of subjects.
    printf("Enter the number of subjects: \n");
    scanf("%d", &numOfSubjects);
    
    // Dynamically allocated memory for the scores array.
    int* scores = malloc(numOfSubjects * sizeof(int));

    printf("Enter the scores one after the other: \n");
    for (int i = 0; i < numOfSubjects; i++)
    {
        scanf("%d", &scores[i]);
    }

    // Display the sum of the subject scores.
    printf("Sum Of Subject Scores: %d\n", sumOfArray(scores, numOfSubjects));

    // Free the allocated memory.
    free(scores);

    return EXIT_SUCCESS;
}

int sumOfArray(int* array, int size)
{
    int sum = 0;
    
    for (int i = 0; i < size; i++)
    {
        sum = sum + *array;
        array++;
    }
    
    return sum;
}