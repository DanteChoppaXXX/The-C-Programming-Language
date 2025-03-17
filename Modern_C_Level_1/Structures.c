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

    /* TO DO */
    // Loop through the array and display the name preceded with an index.
    //int elementCount;
    
    return EXIT_SUCCESS;
}