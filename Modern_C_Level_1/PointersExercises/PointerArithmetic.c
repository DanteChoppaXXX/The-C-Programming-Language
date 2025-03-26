#include <stdio.h>
#include <stdlib.h>

/*
Declare an array and use pointer arithmetic to access its elements.
Print the elements by incrementing the pointer instead of using array indexing.
*/

int main()
{
    char* Days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    
    int size = sizeof(Days) / sizeof(Days[0]);  // Get the number of elements in the array.

    char** pDays = Days;

    printf("Days Of The Week:\n");
    printf("=================\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d: %s\n", i + 1, *pDays);
        pDays++;
    }
    

    return EXIT_SUCCESS;
}