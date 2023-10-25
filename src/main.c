#include <stdio.h>
#include <cx16.h>

//Function declaration for the assembly routine
extern void helloasm();

int main() {
    int num, correct_inputs;

    /* Testing input and output */
    printf("Hello! Enter a number: ");

    //scanf returns how many inputs were correctly entered
    correct_inputs = scanf("%d", &num);

    if (correct_inputs == 1) {
        printf("You have entered: %d\n", num);
    } else {
        printf("\nThat doesn't look like a number to me\n");
    }

    /* Calling assembly routines from C */
    printf("Calling an assembly routine...\n");

    //Functions are prefixed with one underscore when compiled.
    //In the assembly, this routine will be called "_helloasm"
    helloasm();

    return 0;
}