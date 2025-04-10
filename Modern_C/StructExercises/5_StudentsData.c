#include <stdio.h>
#include <stdlib.h>

// Structure to store student data
typedef struct
{
    char name[25];
    int age;
    int rollNumber;
    float mark;

}Student;


int main(){

    // Create an array of struct Student to store students data.
    Student students[5] = {
        {"John Jones", 21, 9, 89.5},
        {"Mary Jackson", 19, 6, 79.6},
        {"Hunter Banes", 23, 9, 85.7},
        {"Dante Choppa", 25, 419, 99.9},
        {"Kyle Xavi", 30, 5, 90.8},
    };

    // 
    printf("\nSTUDENTS DATA:\n");
    printf("================\n");

    // Loop through the students array and display their data.
    for (int i = 0; i < 5; i++)
    {
        printf("Student %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Mark: %.1f\n", students[i].mark);
        printf("\n");
    }
    

    return EXIT_SUCCESS;
}