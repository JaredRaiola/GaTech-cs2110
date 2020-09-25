/**
 * sort.c
 * CS 2110 Function pointers lab
 * Name: YOUR NAME HERE
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define UNUSED(x) (void)(x)

int verify_age_sort(void);
int verify_name_sort(void);
int verify_length_sort(void);
void shuffle(void);

typedef struct {
    int age;
    const char *name;
} person;

#define NUMPEOPLE 18
person people[NUMPEOPLE] = {
    {32, "Farzam"      },
    {51, "Joshua"   },
    {22, "Lauren"   },
    {25, "Manley"  },
    {37, "Michael"   },
    {73, "Vivian"    },
    {26, "Ben"   },
    {40, "Bharat"      },
    {68, "Gibran"      },
    {19, "Henry"   },
    {13, "Jarrett"   },
    {98, "Jim"   },
    {48, "Maddie"  },
    {16, "Sam"   },
    {64, "Sean"    },
    {58, "Shannon"   },
    {34, "Daniel"      },
    {43, "Youna"      }
};


// TODO write any additional comparator functions here above main.
// We even gave you the beginning of one to start!
int compare_by_age(const void *data1, const void *data2) {
    return ((person*)(data1)) -> age - ((person*)(data2)) -> age;
}

int compare_alphabetically(const void *a, const void *b) {
    return strcmp((person*)(a) -> name, (person*)(b) -> name);
}

int compare_by_length(const void *a, const void *b) {
    if ((strlen((person*)(a) -> name) - strlen((person*)(b) -> name)) == 0) {
        compare_alphabetically(a, b);
    } else {
        return (strlen((person*)(a) -> name) - strlen((person*)(b) -> name);
    }
}

int main(void) {
    // Sets up some random stuff ;)
    srand(time(NULL));
    shuffle();

    // TODO Use qsort to sort people by age in ascending order
    qsort(people, sizeof(people) / sizeof(person*), sizeof(person*), compare_by_age);


    // Print people sorted by age
    printf("----------------[Age sort]----------------\n");
    for(int i = 0; i < NUMPEOPLE; ++i) {
        printf("\t%-10s %-2d\n", people[i].name, people[i].age);
    }
    assert(verify_age_sort());
    shuffle();

    // TODO Use qsort to sort people alphabetically by name
    qsort(people, sizeof(people) / sizeof(person*), sizeof(person*), compare_alphabetically);

    // Print people sorted by name
    printf("---------[Name alphabetical sort]---------\n");
    for(int i = 0; i < NUMPEOPLE; ++i) {
        printf("\t%-10s %-2d\n", people[i].name, people[i].age);
    }
    assert(verify_name_sort());
    shuffle();

    // TODO Use qsort to sort people by the length of their name, ascending
    // If two names are the same length, alphabetically sort the two
    qsort(people, sizeof(people) / sizeof(person*), sizeof(person*), compare_by_length);



    // Print people sorted by name length
    printf("-----------[Name length sort]-------------\n");
    for(int i = 0; i < NUMPEOPLE; ++i) {
        printf("\t%-10s %-2d\n", people[i].name, people[i].age);
    }
    assert(verify_length_sort());

    printf("Passed the tests!\n");
    return 0;
}

// Verification functions. Do not modify!

int verify_age_sort(void) {
    for(int i = 1; i < NUMPEOPLE; ++i) {
        if(people[i - 1].age > people[i].age) {
            return 0;
        }
    }
    return 1;
}

int verify_name_sort(void) {
    for(int i = 1; i < NUMPEOPLE; ++i) {
        if(strcmp(people[i - 1].name, people[i].name) > 0) {
            return 0;
        }
    }
    return 1;
}

int verify_length_sort(void) {
    for(int i = 1; i < NUMPEOPLE; ++i) {
        int diff = strlen(people[i - 1].name) - strlen(people[i].name);
        if(diff > 0) {
            return 0;
        } else if(!diff) {
            if(strcmp(people[i - 1].name, people[i].name) > 0) {
                return 0;
            }
        }
    }
    return 1;
}

void shuffle(void) {
    for(int i = NUMPEOPLE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        person temp;
        memcpy(&temp, people + i, sizeof(person));
        memcpy(people + i, people + j, sizeof(person));
        memcpy(people + j, &temp, sizeof(person));
    }
}
