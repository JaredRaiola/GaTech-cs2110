// TODO: Include the correct file so you can use the methods you wrote in the puppies file
#include "puppies.c"

int main() {
	Puppy puppy1 = create_new_puppy("Sparkie", 2);
	printf("Welcome our new puppy, %s, who is %d years old!\n", puppy1.name, puppy1.age);

	Puppy puppy2 = create_new_puppy("Bailey", 3);
    printf("Welcome our new puppy, %s, who is %d years old!\n", puppy2.name, puppy2.age);
	make_friends(puppy1, puppy2);		
}