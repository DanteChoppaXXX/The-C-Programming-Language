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

    Student student;

    printf("Enter your name: \n");
    fgets(student.name, 25, stdin);
    student.name[strlen(student.name) - 1] = '\0';

    printf("Enter your age: \n");
    scanf("%d", &student.age);

    printf("Enter your roll number: \n");
    scanf("%d", &student.rollNumber);
    
    printf("Enter your mark: \n");
    scanf("%f", &student.mark);

    printf("\nSTUDENT DETAILS:\n");
    printf("================\n");
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Mark: %.1f\n", student.mark);



    return EXIT_SUCCESS;
}