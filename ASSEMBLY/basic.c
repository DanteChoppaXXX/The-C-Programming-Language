#include <stdio.h>
#include <stdlib.h>

// Function Prototype.
int add(int a, int b);

int main()
{
    int a = 5;
    int b = 6;

    printf("Result: %d\n", add(a, b));
   
    return EXIT_SUCCESS;
}

int add(int a, int b)
{
    return (a + b);
}