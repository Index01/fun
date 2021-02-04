
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



void swapInts(int *ap, int *bp){
        /** quickly swap ints by pointers. **/
        
        int tmp = *ap;
        *ap = *bp;
        *bp = tmp;

}


void swapGeneric(void *ap, void *bp, int size){
        /** quickly swap unknown types by pointers. **/

        void *tmp = malloc(size);
        memcpy(tmp, ap, size);
        memcpy(ap, bp, size);
        memcpy(bp, tmp, size);

        free(tmp);
}


void main(){
        printf("%s\n\n", "[+] Welcome, Starfighter");

        int A = 7;
        int B = 42;
        double C = 212.34;
        double D = 415.67;

        swapInts(&A, &B);

        swapGeneric(&C, &D, sizeof(double));
        printf("%s\n", "Post swap results:");
        printf("%d\n", A);
        printf("%d\n", B);
        printf("%f\n", C);
        printf("%f\n", D);

}
