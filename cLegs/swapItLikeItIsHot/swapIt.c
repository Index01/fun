
#include<stdio.h>
#include<stdlib.h>
#include<string.h>




void swapInts(int *ap, int *bp){
        /** quickly swap ints by pointers. **/
        
        printf("%s", "Pre-swap intA: ");
        printf("%d\n", *ap);
        printf("%s", "Pre-swap intB: ");
        printf("%d\n", *bp);


        
        int tmp = *ap;
        *ap = *bp;
        *bp = tmp;


        printf("%s", "Post-swap intA: ");
        printf("%d\n", *ap);
        printf("%s", "Post-swap intB: ");
        printf("%d\n", *bp);


}


void swapGeneric(void *ap, void *bp, int size){
        /** quickly swap unknown types by pointers. **/

        printf("%s", "Pre-swap voidA: ");
        printf("%d\n", *(int *)ap);
        printf("%s", "Pre-swap voidB: ");
        printf("%d\n", *(int *)bp);

        printf("%ld\n", sizeof(*(int *)ap));
        printf("%ld\n", sizeof(*(double *)bp));

        if(sizeof(ap) == sizeof(bp)){
                printf("%s\n", "Same size!");
        }

        void *tmp = malloc(size);
        memcpy(tmp, ap, size);
        memcpy(ap, bp, size);
        memcpy(bp, tmp, size);

        printf("%s", "Post-swap voidA: ");
        printf("%d\n", *(int *)ap);
        printf("%s", "Post-swap voidB: ");
        printf("%d\n", *(int *)bp);

        free(tmp);

}


void main(){
        printf("%s\n", "[+] Welcome, Starfighter");

        int A = 7;
        int B = 42;
        double C = 212;

        swapInts(&A, &B);

        swapGeneric(&A, &C, sizeof(int));

}
