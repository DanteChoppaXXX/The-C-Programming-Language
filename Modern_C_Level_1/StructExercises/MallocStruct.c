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

// Function to display the student Data.
void displayStudentData(Student* student){
    
    printf("\nSTUDENT DATA:\n");
    printf("================\n");
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("Roll Number: %d\n", student->rollNumber);
    printf("Mark: %.1f\n", student->mark);
}

int main(){

    // Allocate memory dynamically for an array of struct Student using malloc().
    Student* student = malloc(sizeof(Student));

    // Prompt the user for their Data.
    printf("Enter your name: \n");
    fgets(student->name, 25, stdin);
    student->name[strlen(student->name) - 1] = '\0';

    printf("Enter your age: \n");
    scanf("%d", &student->age);

    printf("Enter your roll number: \n");
    scanf("%d", &student->rollNumber);
    
    printf("Enter your mark: \n");
    scanf("%f", &student->mark);

    // Call the data display function with the student object as the argument.
    displayStudentData(student);
    
    return EXIT_SUCCESS;
}