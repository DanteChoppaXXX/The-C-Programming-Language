#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Hello, World!\n");
    
    int c;
    
    printf("%d", EOF);
    
    c = getchar() != EOF;

    printf("%d", c);


    
    

    return EXIT_SUCCESS;
}