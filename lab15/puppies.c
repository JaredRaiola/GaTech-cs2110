#include "puppies.h"
/**
 * TODO: Create two functions:
 * 1) create_new_puppy that takes in a name and an age and returns a new Puppy
 * 2) make_friends that takes in two puppies and prints out "[puppy1's name] and [puppy2's name] are now friends!"
 * 
 **/
 Puppy create_new_puppy(char *name, int age) {
 	Puppy pupper;
 	pupper.age = age;
 	pupper.name = name;
 	return pupper;
 }

 void make_friends(Puppy p1, Puppy p2) {
 	printf("%s and %s are now friends\n", p1.name, p2.name);
 }