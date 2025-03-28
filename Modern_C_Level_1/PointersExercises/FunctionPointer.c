#include <stdio.h>
#include <stdlib.h>

/*
ADVANCED LEVEL 1:
Write a function that takes two integers and returns their sum.
Declare a function pointer and use it to call the function dynamically.
*/

// Function Prototype.
int sum(int number0, int number1);

int main()
{
    // Declare a function pointer.
    int (*pSum) (int, int);
    pSum = sum;

    // Call the function dynamically with the pointer.
    
    printf("%d\n", pSum(43, 34));

    return EXIT_SUCCESS;
}

// Function that returns the sum of two integers.
int sum(int number0, int number1)
{
    return number0 + number1;
}
