#include <stdio.h>
#include <stdlib.h>

/*
Basic Level: Pointer Basics
Task:
Write a program that declares an integer variable, assigns it a value, and then uses a pointer to:

Print the address of the variable.
Print the value of the variable using the pointer.
Modify the value of the variable using the pointer and print the updated value.

Concepts Covered: Pointer declaration, dereferencing, modifying values through pointers.
*/

int main()
{
    // Declare an integer variable an assign it a value.
    int number = 418;
    
    // Declare a pointer and assign the integer variable to it.
    int* pNumber = &number;

    // Display the address of the variable and the value using the pointer.
    printf("Variable Address: %p\n", pNumber);
    printf("Variable Value: %d\n", *pNumber);

    // Update the value of the variable using the pointer.
    *pNumber = 419;

    // Display the new value.
    printf("New Variable Value: %d\n", *pNumber);

    // Extra: Display the pointer address.
    printf("\nPointer Address: %p\n", &pNumber);
    
    return EXIT_SUCCESS;
}