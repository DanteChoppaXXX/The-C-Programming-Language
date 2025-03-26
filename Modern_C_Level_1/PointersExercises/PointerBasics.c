#include <stdio.h>
#include <stdlib.h>

/*
Declare an integer variable, assign it a value, and create a pointer that holds its address.
Print the variable’s value using both the variable and the pointer.
*/

int main()
{
    int number = 419;

    int* pNumber = &number;

    printf("Displaying The Variable's Value\n");
    printf("===============================\n");
    printf("With Variable: %d\n", number);
    printf("With Pointer: %d\n", *pNumber);

    printf("Variable's Memory Address: %p\n", pNumber);

    return EXIT_SUCCESS;
}