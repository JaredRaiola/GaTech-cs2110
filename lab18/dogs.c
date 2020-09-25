#include <stdlib.h>
#include <stdio.h>
#include "dogs.h"


Dog *createDogArray(int numDogs) {
    // TODO: Create a dog array using malloc. You don't need to initialize the dogs to anything.
    //       Make sure to remember to handle if malloc fails by returning NULL in that case.
    Dog *size = malloc(numDogs * sizeof(Dog));
    return size;
}

void setDogAtIndex(Dog *dogArray, int index, char *name, int age) {
    // TODO: Set the name and age of the dog at the specified index in the array
    dogArray[index].name = name;
    dogArray[index].age = age;

}

void printDogs(Dog *dogArray, int numDogs) {
    for (int i = 0; i < numDogs; i++) {
        printf("%d. Dog's Name: %s, Dog's Age: %d\n", i, dogArray[i].name, dogArray[i].age);
    }
}

int main(int argc, char *argv[]) {
    //TODO: Create an array of 5 dogs using your createDogArray function. Check if it failed (returned NULL) and if so return 1
    Dog *dogArray;
    dogArray = createDogArray(5);
    for (int i = 0; i < 5; i++) {
        dogArray[i].name = "Doggo";
        dogArray[i].age = i;
    }
    if (dogArray == NULL) {
        return 1;
    }
    //TODO: Go through the array and set all the dog's names to Doggo and their age to the index



    printDogs(dogArray, 5);

    //TODO: Give the memory you borrowed from malloc back to it by using free!
    free(dogArray);
    // Ignore these
    UNUSED(argc);
    UNUSED(argv);

    return 0;
}
