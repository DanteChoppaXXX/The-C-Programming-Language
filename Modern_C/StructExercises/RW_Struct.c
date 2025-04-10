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

// File pointer.
FILE* dataFile;

// Function Prototypes.
void writeData(Student student);
void readData(Student* student);
void displayStudentData(Student student);

int main(){

    /* Save an array of struct Student to a binary file. */

    // Create a student array of type (struct Student).
    Student student = {
        .name = "John Jones",
        .age = 23,
        .rollNumber = 443,
        .mark = 90.5
    };

    // Write the student array to the file.
    writeData(student);

    // Read the file and display the stored student details.
    readData(&student);

    return EXIT_SUCCESS;
}

void writeData(Student student)
{
    dataFile = fopen("./studentdata.bin", "wb");
    if (dataFile == NULL)
    {
        printf("Failed to open file!\n");
        exit(1);
    }
    else{
        printf("File Successfully Opened!\n");
    }

    if(fwrite(&student, sizeof(student), 1, dataFile) <= 0)
    {
        printf("Failed to write to file!\n");
        exit(1);
    }

    fclose(dataFile);
    printf("Student data written to file successfully!\n");

};

void readData(Student* student)
{
    dataFile = fopen("./studentdata.bin", "rb");
    if (dataFile == NULL)
    {
        printf("Failed to open file!\n");
        exit(1);
    }
    else{
        printf("File Successfully Opened!\n");
    }
    if(fread(student, sizeof(student), 1, dataFile) <= 0)
    {
        printf("Failed to read from file!\n");
        exit(1);
    }
    displayStudentData(*student);
    
    fclose(dataFile);
    printf("\nStudent data read from file successfully!\n");
};

// Function to display the student Data.
void displayStudentData(Student student){
    
    printf("\nSTUDENT DATA:\n");
    printf("================\n");
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Mark: %.1f\n", student.mark);
}
