#include <stdio.h>
#include <stdlib.h>

struct BirdStruct
{
    char const* jay;
    char const* magpie;
    char const* raven;
    char const* chough;
};

int main(){

    struct BirdStruct const aName = {
        .jay = "Joe",
        .magpie = "Frau",
        .raven = "Lissy",
        .chough = "Henry"
    };

    printf("List Of Birds Name:\n");
    printf("%s\n%s\n%s\n%s\n", aName.chough, aName.jay, aName.magpie, aName.raven);

    /* TO DO 
    Loop through the struct object and display the name preceded with an index.
     e.g. 1. Joe
          2. Frau
          3. Lissy
          4. Henry
    */

    // Create an array to store the names of the birds
    char const* birdNames[] = {aName.jay, aName.magpie, aName.raven, aName.chough};

    // Calculate the number of elements in the array
    int arrayElements = sizeof(birdNames) / sizeof(birdNames[0]);
    
    printf("\nList Of Birds Name:\n");
    
    // Now loop through the array and display the name preceded with an index
    for (int i = 0; i < arrayElements; i++)
    {
        printf("%d. %s\n", i + 1, birdNames[i]);
    }
    
    return EXIT_SUCCESS;
}