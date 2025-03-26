#include <stdio.h>
#include <stdlib.h>

/*
Use malloc() to allocate memory for an integer dynamically.
Assign it a value, print it, and then free the memory.
*/

int main()
{
    int* number0 = malloc(sizeof(int));
    *number0 = 419;
    

    printf("Number: %d\n", *number0);

    free(number0);

    return EXIT_SUCCESS;
}