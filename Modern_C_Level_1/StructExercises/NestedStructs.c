#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* THIS PROGRAM CAN BE ADVANCED BY IMPLEMENTING THE NECESSARY INPUT VALIDATIONS. */

// Define a struct Date(day, month, year).
typedef struct
{
    int day;
    int month;
    int year;

}Date;

// Create an Employee struct with fields: name, id, salary, and joiningDate (which is a struct Date).
typedef struct
{
    char name[50];
    int id;
    double salary;
    Date joiningDate;

}Employee;


int main()
{
    // Create an employee object of type (struct Employee).
    Employee employee;

    /* Take input and display an employee’s data. */

    // Prompt the employee for their data.
    printf("Enter your full name: \n");
    fgets(employee.name, 50, stdin);
    employee.name[strlen(employee.name) - 1] = '\0';
    fflush(stdin); // Clear the input buffer to prevent buffer issues.

    printf("Enter your ID number: \n");
    scanf("%d", &employee.id);

    printf("Enter your exact salary amount(e.g 50000.55): \n");
    scanf("%lf", &employee.salary);

    printf("Enter the date you joined the company(e.g dd-mm-yyyy): \n");
    scanf("%d %d %d", &employee.joiningDate.day, &employee.joiningDate.month, &employee.joiningDate.year);

    // Display the employee's data.
    printf("\nEMPLOYEE'S DATA:\n");
    printf("==================\n");

    printf("Name: %s\n",employee.name);
    printf("ID: %d\n",  employee.id);
    printf("Salary: $%.2lf\n", employee.salary);
    printf("Join Date: %d-%d-%d", employee.joiningDate.day, employee.joiningDate.month, employee.joiningDate.year);


    return EXIT_SUCCESS;
}