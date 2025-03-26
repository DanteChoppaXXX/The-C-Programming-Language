#include <stdio.h>
#include <stdlib.h>

/*
BASIC LEVEL 3:
Write a function that swaps two integers using pointers.
Why can’t you swap them without pointers?
Answer: Without pointers the function can't and doesn't modify the content of the actual variable but rather a copy of it (Passing by value).
*/

// Function Prototype.
void swapIntegers(int* number0, int* number1);
void quiz(void);

int main()
{
    int number0 = 50;
    int number1 = 100;

    // Display the integers before swapping.
    printf("\nBEFORE SWAPPING:\n");
    printf("===============\n");
    printf("Number 0: %d\nNumber 1: %d\n", number0, number1);

    // Call the swap function with pointers to the integers as the arguments.
    swapIntegers(&number0, &number1);

    // Display the integers after swapping.
    printf("\nAFTER SWAPPING:\n");
    printf("===============\n");
    printf("Number 0: %d\nNumber 1: %d\n", number0, number1);

    quiz();
    
    return EXIT_SUCCESS;
}

void swapIntegers(int* number0, int* number1)
{
    int temp = *number0;
    *number0 = *number1;
    *number1 = temp;
}

void quiz()
{
    printf("\nQuestion:\n=========\n");
    printf("Why can’t you swap them without pointers?\n");
    printf("\nAnswer:\n=======\nWithout pointers the function can't and doesn't modify the content of the actual variable but rather a copy of it (i.e Passing By Value).\n");
}