#include <stdio.h>
#include <stdlib.h>


int main(){
    
    /* Count characters in input; 1st version*/

    // long nc;

    // nc = 0;
    // while (getchar() != EOF)
    // {
    //     ++nc;
    // }
    // printf("%ld\n", nc);

    /* Count characters in input; 2nd version*/

    double nc;
    
    for (nc = 0; getchar() != EOF; ++nc)
    {
        ;
    }
    printf("%.0f\n", nc);
    

    return EXIT_SUCCESS;
}