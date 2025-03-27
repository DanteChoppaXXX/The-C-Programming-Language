#include <stdio.h>
#include <stdlib.h>

/*
INTERMEDIATE LEVEL 3:
Reverse an array in-place using pointers without using extra space.
*/

// Function Prototype.
void reverseArray(int* array, int size);


int main()
{
    int numbers[] = {25, 20, 15, 10, 5};

    int size = sizeof(numbers) / sizeof(numbers[0]);

    int* pNumbers; 
    pNumbers = numbers;

    // Display elements of the array before reversing.
    printf("\nBEFORE REVERSING:\n");
    printf("=================\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", pNumbers[i]);
    }
    
    
    // Display elements of the array after reversing.
    printf("\nAFTER REVERSING:\n");
    printf("================\n");
    
    reverseArray(pNumbers, size);

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", pNumbers[i]);
    }
    
    
    return EXIT_SUCCESS;
}

// Function to reverse array.
void reverseArray(int* array, int size)
{
    
}