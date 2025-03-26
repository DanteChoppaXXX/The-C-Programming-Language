#include <stdio.h>
#include <stdlib.h>

/*
INTERMEDIATE LEVEL 2:
Declare an integer pointer and a pointer to that pointer.
Access and modify the value of the integer using the pointer-to-pointer.
*/

// Function Prototype.
void modifyPointerValue(int* ptr);

int main()
{
    int number0 = 418;
    int* pNumber0;
    pNumber0 = &number0;

    // Display the integers before modification.
    printf("\nBEFORE MODIFICATION:\n");
    printf("====================\n");
    printf("Number: %d\n", *pNumber0);
    
    modifyPointerValue(pNumber0);
    
    // Display the integers after modification.
    printf("\nAFTER MODIFICATION:\n");
    printf("===================\n");
    printf("Number: %d\n", *pNumber0);

    return EXIT_SUCCESS;
}

// Function to modify pointer value.
void modifyPointerValue(int* ptr)
{
    printf("\nEnter new number:\n");
    scanf("%d", ptr);

}