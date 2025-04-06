#include <stdio.h>
#include <stdlib.h>

/*
Advanced Level: Simulating 2D Arrays Using Pointers
Task:
Write a program that:

Asks the user for two integers, rows and cols, to define a dynamic 2D array.
Allocates memory for the 2D array using an array of pointers (int**).
Fills the array with values such that arr[i][j] = i * j.
Prints the array using array indexing and pointer arithmetic.
Properly deallocates memory using free().
Concepts Covered: Dynamic 2D arrays, pointer-to-pointer (int**), manual memory management.
*/

int main()
{
    int rows, cols;
    
    // Prompt the user for number of rows and columns.
    printf("Enter the number of rows: \n");
    scanf("%d", &rows);
    
    printf("Enter the number of columns: \n");
    scanf("%d", &cols);

    // Allocate memory for the 2D array using an array of pointers (int**).
    int** pArray = malloc(rows * sizeof(int*));
    printf("\nArray Memory Address: %p\n", pArray);

    // Allocate memory for each row (i.e each pointer) in the array.
    for (int i = 0; i < rows; i++)
    {
        pArray[i] = malloc(cols * sizeof(int));
    }
    
    // Fill the array with values such that arr[i][j] = i * j.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            pArray[i][j] = i * j;
        }
        // printf("\n");
    }
    
    printf("\n");

    // Display the array using array indexing.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", pArray[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");

    // Display the array using pointer arithmetic.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", *(*(pArray + i) + j));
        }
        printf("\n");
    }

    printf("\n");

    // Display the address of the elements in the matrix using array notation.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%p ", &pArray[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Display the address of the elements in the matrix using pointer arthimetic.
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%p ", *(pArray + i) + j);
        }
        printf("\n");
    }
    
    printf("\n");
    
    // Free the allocated memory of each row in the array.
    for (int i = 0; i < rows; i++)
    {
        free(pArray[i]);
        printf("Memory Address: %p Successfully Freed!\n", pArray[i]);
    }
    
    // Free the allocated memory of the array.
    free(pArray);
    printf("\nMemory Address: %p Successfully Freed!\n", pArray);

    return EXIT_SUCCESS;
}