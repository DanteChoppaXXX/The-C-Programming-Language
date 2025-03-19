#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[25];
    int age;
    int rollNumber;
    float mark;

}Student;


int main(){

    Student students[5][4] = {
        {"John Jones", 21, 9, 89.5},
        {"Mary Jackson", 19, 6, 79.6},
        {"Hunter Banes", 23, 9, 85.7},
        {"Dante Choppa", 25, 419, 99.9},
        {"Kyle Xavi", 30, 5, 90.8},
    };

    printf("\nSTUDENT DETAILS:\n");
    printf("================\n");

    for (int i = 0; i < 5; i++)
    {
        printf("Student %d\n", i + 1);
        printf("Name: %s\n", students[i][0].name);
        printf("Age: %d\n", students[i][0].age);
        printf("Roll Number: %d\n", students[i][0].rollNumber);
        printf("Mark: %.1f\n", students[i][0].mark);
        printf("\n");
    }
    

    return EXIT_SUCCESS;
}