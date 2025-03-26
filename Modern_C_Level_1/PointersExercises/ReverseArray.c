#include <stdio.h>
#include <stdlib.h>

/*
INTERMEDIATE LEVEL 3:
Reverse an array in-place using pointers without using extra space.
*/

// Function Prototype.
void reverseArray(int* array);


int main()
{
   int numbers[] = {1, 2, 3, 4, 5};

   int size = sizeof(numbers);


    // Display elements of the array before reversing.
    printf("\nBEFORE REVERSING:\n");
    printf("=================\n");
    
    
    reverseArray();
    
    // Display elements of the array after reversing.
    printf("\nAFTER REVERSING:\n");
    printf("================\n");
    
    return EXIT_SUCCESS;
}

// Function to reverse array.
void reverseArray(int* array)
{
    
}