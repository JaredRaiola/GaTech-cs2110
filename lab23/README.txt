===============================================================================
CS2110                               Lab 23                         Spring 2019
===============================================================================

Objective: Use qsort to sort arrays using function pointers.

This is a lab where you will use qsort to sort an array of elements in
different ways.

Passing functions into functions
--------------------------------
If you take a look at the man page for qsort, you will see that the fourth
parameter looks like this:

    int (*compar)(const void *, const void *)

The type of this parameter is a function pointer, which is the address of a
function. The signature of the function must have "int" as the return type,
and take (const void*, const void*) as parameters. The way you can pass in
the address of a function is to simply use that function's name as the
parameter. For example, here is the signature of another function called
atexit:

    int atexit(void (*function)(void));

The atexit function takes in a pointer to a function which will be
executed on normal termination of the program. The function must be a void
function with no parameters (as indicated by the void parameter list):

void bye(void) {
    printf("Goodbye!\n");
}

int main(void) {
    atexit(bye);
    // do stuff
    return 0;
}

Assignment
----------
In the provided sort.c file, edit it where necessary to sort the array
appropriately. Use qsort from stdlib.h to accomplish this.

To build the application and run it:

make
./sort

Important Hints! Read before starting!
-------------------------------------
Use the man pages to see how qsort is used!

Tests will be run using assert. This means that if you fail a test, the program
will be aborted.

Remember that you can't dereference void pointers! You need to cast them first.

The second way you should sort the elements is alphabetically. You don't have
to write low level string comparison code to accomplish this because there's
already a function in string.h (strcmp) that can compare strings. It is reccommended
that you use that function in your implementation of this lab.

The third way you should sort the elements is by length, with the requirement
that names of the same length are then sorted alphabetically. Try calling the
function you wrote in part 2 from your function for part 3!

Submission Instructions
-----------------------
Show your TA the output from sort when you're getting checked off!
