#include <stdio.h>
#include <stdlib.h>

/*
ADVANCED LEVEL 2:
Implement your own strlen() function using pointers.
Implement a function to reverse a string using pointers.
*/

// Function Prototypes.
int stringLength(char* string);
void reverseString(char* string);

int main()
{
    // Create a variable that holds a string.
    char string[] = "Devil May Cry";

    // Create a pointer and assign the string to it.
    char* pString = string;

    // Display the string before reversing.
    printf("\nBEFORE REVERSING:\n");
    printf("=================\n");
    
    printf("%s\n", pString);
    
    // Call the reverseString() function passing the pointer as the argument.
    reverseString(pString);
    
    // Display the string after reversing.
    printf("\nAFTER REVERSING:\n");
    printf("================\n");

    printf("%s\n", pString);

    printf("%d\n", stringLength(pString));

    return EXIT_SUCCESS;
}

// Function that takes a pointer to a string and returns the number of characters in the string.
int stringLength(char* string)
{
    // Declare a counter variable to store the character count.
    int counter = 0;

    // Loop through the string and update the counter.
    while (*string != '\0')
    {
        // Update the counter.
        counter++;

        // Move the pointer forward.
        string++;
    }
    
    return counter;
}

// Function that takes a pointer to a string and reverses it.
void reverseString(char* string)
{
    // Get the length of the string with the stringLength() function.
    int length = stringLength(string);
    
    // Create two pointers, one pointing to the start of the string and the other to the end.
    char* left = string;
    char* right = string + length - 1;

    // Swap the elements at each end while moving the pointers towards each other.
    while (left < right)
    {
        // Swap the characters at each end.
        int temp = *left;
        *left = *right;
        *right = temp;

        // Move the pointers towards each other.
        left++;
        right--;
    }
    
}
