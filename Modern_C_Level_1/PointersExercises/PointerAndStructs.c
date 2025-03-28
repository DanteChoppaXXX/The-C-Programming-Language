#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ADVANCED LEVEL 3:
Create a struct representing a Person (name, age).
Allocate memory dynamically for a Person and modify its attributes using a pointer.
*/

// Structure to store Person data.
typedef struct
{
    char name[10];
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
