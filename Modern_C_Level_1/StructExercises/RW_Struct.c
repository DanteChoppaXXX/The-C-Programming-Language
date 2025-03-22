#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student data
typedef struct
{
    char name[25];
    int age;
    int rollNumber;
    float mark;

}Student;

int main(){

    /* Save an array of struct Student to a binary file. */

    // Create a student array of type (struct Student).
    Student* student = malloc(sizeof(Student));

    // Open a file for writing in binary mode.
    FILE* dataFile;
    
    dataFile = fopen("./studentdata.bin", "wb");
    if (dataFile == NULL)
    {
        printf("Failed to open file!\n");
        return EXIT_FAILURE;
    }
    else{
        printf("File Successfully Opened!\n");
    }

    
    // Write


    /* Read the file and display the stored student details. */


    return EXIT_SUCCESS;
}