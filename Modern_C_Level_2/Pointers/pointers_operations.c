#include <stdio.h>
#include <stdlib.h>

// Double Swap Function Prototype.
//void double_swap(double* p0, double* p1);

void double_swap1(double* p0, double* p1, double* p2);

int main(){

    double p0 = 25.5;
    double p1 = 55.5;
    double p2 = 75.5;

    printf("p0 = %.1lf\np1 = %.1lf\np2 = %.1lf\n", p0, p1, p2);
    printf("After Content Swap:\n");
    //double_swap(&p0, &p1);  
    double_swap1(&p0, &p1, &p2);
    printf("p0 = %.1lf\np1 = %.1lf\np2 = %.1lf\n", p0, p1, p2);

    return EXIT_SUCCESS;
}

// void double_swap(double* p0, double* p1){
//     double temp = *p0;
//     *p0 = *p1;
//     *p1 = temp;

// }

/* EXERCISE */
// Write a function that receives pointers to three objects and that shifts the values of these objects cyclically.

void double_swap1(double* p0, double* p1, double* p2){
    double temp = *p0;
    *p0 = *p1;
    *p1 = *p2;
    *p2 = temp;

}