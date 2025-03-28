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
    int numbers[] = {9,8,7,6,5,4,3,2,1,0};

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
    // Create two pointers; one pointing to the start of the array and the other to the end.
    int* left = array;
    int* right = array + size - 1;

    /* Swap the elements at each end together while moving the pointers towards each other until they meet at the middle. */
    
    while (left < right)
    {
        // Swap the elements at each end.
        int * temp; 
        *temp = *left;
        *left = *right;
        *right = *temp;
        
        // Move the pointers towards each other.
        left ++;
        right--;
    }
    
}