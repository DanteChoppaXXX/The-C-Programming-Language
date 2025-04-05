#include <stdio.h>
#include <stdlib.h>

/*
Basic Level: Array Indexing & Pointers
Task:
Write a program that:

Declares an integer array of size 5 and initializes it with values {10, 20, 30, 40, 50}.
Prints each element using both array indexing (arr[i]) and pointer notation (*(arr + i)).
Prints the address of each element using both &arr[i] and (arr + i).
Concepts Covered: Array indexing, pointer notation, array element addresses.
*/

int main()
{
    // Declare an integer array of size 5 and initialize it.
    int array[5] = {10, 20, 30, 40, 50};

    // Display the elements of the array.
    for (int i = 0; i < 5; i++)
    {
        printf("%d %d\n", array[i], *(array + i));
    }
    
    // Display the address of each elements
    for (int i = 0; i < 5; i++)
    {
        printf("%p %p\n", &array[i], (array + i));
    }
    
    return EXIT_SUCCESS;
}