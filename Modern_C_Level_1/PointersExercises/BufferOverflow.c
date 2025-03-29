#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ADVANCED LEVEL 3:
Simulate a basic buffer overflow by writing beyond an allocated memory block.
Try passing code to the overflowed buffer for execution. ⚠ ⚠ ⚠
Discuss why this is dangerous and how it can be exploited in cybersecurity.
*/

// Structure to store Person data.
typedef struct
{
    char name[25];
    int age;

}Person;

int main()
{
    // Create an object of type(struct Person).
    Person* person = malloc(sizeof(Person));

    // Prompt the user for their Data.
    printf("Enter your name: \n");
    fgets(person->name, 25, stdin);
    person->name[strlen(person->name) - 1] = '\0';
    fflush(stdin); // Clear the input buffer to prevent buffer issues.
    
    printf("Enter your age: \n");
    scanf("%d", &person->age);

    // strcpy(person->name, "Dante Choppa");
    // person->age = 25;

    printf("\nPERSON DATA:\n");
    printf("============\n");
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);

    free(person);

    return EXIT_SUCCESS;
}
