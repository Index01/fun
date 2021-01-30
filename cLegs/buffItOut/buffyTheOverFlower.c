
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"buffyTheOverFlower.h"




void vulnFunc(const char *overBuff){ 
        // vulnFunc just takes a pointer to a buffer and blindly coppies it to some heap space
        // And it compiles! one of the many big problems. gcc -fstack-protector cannot help you here.

        int num_chars = 4;
        char *cpt1 = (char *) calloc(num_chars, sizeof(char));

        // ok we checked for a non-null pointer, everything is cool, right?
        if(cpt1){ 
                printf("%s\n", "Has pointy");
        }
        
        char *cpt2 = cpt1;
        cpt2 = cpt2 + num_chars/2;

        printf("%p\n", (void *) &cpt1);
        printf("%p\n", (void *) &cpt2);


        // here we just prep some dowstream memory. In this real world, where someone 
        // might use malloc, this would just be arbitrary memory. In this example 
        // we put some known value, which is the same buffer. 
        strcpy(cpt2, overBuff); 

        // Look mum! no size check.
        // the big problem. We have a valid pointer, we copy some buffer into the heap
        // but it overflows into our second chunk of memory, which in this case is contiguous.
        strcpy(cpt1, overBuff); 

        // over read!!!
        // This is where things go further off the rails when some subesquent function or
        // bit of code reads the memory after the undersized buffer we overwrote. In
        // this instance we know what the original value of these downstream registers,
        // in the wild they could be anywhere, accessed at an unknown time with unknown results.
        printf("%s", "Pointer1, known memory, post buffer copy: ");
        puts(cpt1);
        printf("%s", "Pointer2, arbitrary memory, post buffer copy: ");
        puts(cpt2);
        for(int i=0; i<24; i++){ 
                // just read some bits.
                printf("%p ", (void *) &cpt1 + i);
                printf("%s\n", cpt1 + i);
        }

        // because we think we are good citizens.
        free(cpt1);
}

void callingFunc(){
        // callingFunc knows to expect some input of a particular size, maybe from user or socket or whatevs.
        // It then uses some un-suspecting super sweet, totally vulnerable, function. 
        
        const char buff[32] = "foo";
        const char *pOBuff = buff;

        vulnFunc(pOBuff);
}

void main(){
        printf("%s\n", "[+] Welcome, Starfighter");
        // Coolcool, we are just doing something
        callingFunc();

}
