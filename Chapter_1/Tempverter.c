#include <stdio.h>
#include <stdlib.h>
/* Print Fahrenheit-Celsius Table
    For fahr = 0, 20, ..., 300; floating-point version */

int main(){
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;  // Lower limit of temperature scale
    upper = 300;    // Upper limit of temperature scale
    step = 20;  // Step size
    
    int counter = 0;
    fahr = lower;

    printf("===========================\n");
    printf("Fahrenheit To Celsius Table\n");
    printf("===========================\n");
   
    while (fahr <= upper)
    {
        counter++;
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%4d. %3.0f %6.1f\n", counter, fahr, celsius);
        fahr = fahr + step;
    }

    counter = 0;
    celsius = upper;

    // Celsius To Fahrenheit Table In Reverse Order.
    printf("===========================\n");
    printf("Celsius To Fahrenheit Table\n");
    printf("===========================\n");
   
    while (celsius >= lower)
    {
        counter++;
        fahr = (celsius * 9 / 5) + 32;
        printf("%4d. %3.0f %6.1f\n", counter, celsius, fahr);
        celsius = celsius - step;
    }
    

    return EXIT_SUCCESS;
}