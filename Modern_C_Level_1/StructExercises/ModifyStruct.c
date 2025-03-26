#include <stdio.h>
#include <stdlib.h>

/* Write a function that takes a pointer to a struct Student and updates the marks. */

// Structure to store student data
typedef struct
{
    char name[25];
    int age;
    int rollNumber;
    float mark;

}Student;

// Function Prototypes.
void displayStudentData(Student student);
void updateMark(Student* student);

int main()
{
    // Create a student array of type (struct Student).
    Student student = {
        .name = "John Jones",
        .age = 23,
        .rollNumber = 443,
        .mark = 90.5
    };
    
    // Display the student details.
    displayStudentData(student);

    // Call the mark update function.
    updateMark(&student);

    // Display the Updated student details.
    displayStudentData(student);


    return EXIT_SUCCESS;
}

// Function to update student mark.
void updateMark(Student* student)
{
    student->mark = 99.9;
}

// Function to display the student Data.
void displayStudentData(Student student){
    
    printf("\nSTUDENT DATA:\n");
    printf("================\n");
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Mark: %.1f\n", student.mark);
}
