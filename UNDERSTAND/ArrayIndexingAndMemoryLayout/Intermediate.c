#include <stdio.h>
#include <stdlib.h>

/*
Intermediate Level: Understanding Row-Major Order in 2D Arrays
Task:
Write a program that:

Declares a 3x3 matrix (2D array) and initializes it with numbers 1 to 9.
Prints the matrix in row-major order using both array notation (arr[i][j]) and pointer arithmetic (*(*(arr + i) + j)).
Prints the memory addresses of all elements in the matrix to observe how they are stored in contiguous memory.
Concepts Covered: Memory layout of 2D arrays, pointer arithmetic, row-major order storage.
*/

int main()
{
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Display the matrix in row-major order using array notation.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Display the matrix in row-major order using pointer arithmetic.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    printf("\n");

    // Display the address of the elements in the matrix using array notation.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%p ", &matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Display the address of the elements in the matrix using pointer arthimetic.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%p ", *(matrix + i) + j);
        }
        printf("\n");
    }
    
    
    return EXIT_SUCCESS;
}