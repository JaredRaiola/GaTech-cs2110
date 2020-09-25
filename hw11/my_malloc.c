/*
 * CS 2110 Spring 2019
 * Author: Jared Raiola
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

static void removeBlock(metadata_t *curr);
static void setCanary(metadata_t *curr);
static metadata_t* splitBlock(metadata_t *block, size_t size);
static void addBlock(metadata_t *curr);
static metadata_t* left(metadata_t *currBlock);
static metadata_t* right(metadata_t *currBlock);
static void mergeL(metadata_t *currBlock, metadata_t *left);
static void mergeR(metadata_t *currBlock, metadata_t *right);

/* Our freelist structure - our freelist is represented as a singly linked list
 * the size_list orders the free blocks by size in ascending order
 */

metadata_t *size_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;



//so basically what this is supp to do is
//look at the prev one to the curr and say "if that exists then
//set it's next to the next of curr." But the problem is that 
//you might have a list of size one, or you're passing in the first
//element in the list so it technically doesn't have a prev
//Possible fixes:
//		-pass in both curr and prev and check to see if they're the same,
//		 the way you implemented prev and curr, if they're the same you're
//		 at the first element in the size_list
// your remove isn't working
static void removeBlock(metadata_t *curr) {
	metadata_t* currNode = size_list;
	if (currNode == curr) {
		size_list = curr -> next;
	} else {
		while (currNode -> next != curr) {
			currNode = currNode -> next;
		}
		currNode -> next = curr -> next;
	}
	curr -> next = NULL;
}

static void addBlock(metadata_t *blockToAdd) {
	//some loop to re-add the block to the list.
	metadata_t* curr = size_list;
	metadata_t* prev = NULL;

	if (curr == NULL) { // means the list is empty
		size_list = blockToAdd;
	} else { // means that there's something in the list
		while (curr != NULL && curr -> size <= blockToAdd -> size) {
			prev = curr;
			curr = curr -> next;
		}
		if (curr == NULL) {
			prev -> next = blockToAdd;
		} else {
			if (prev != NULL) {
				prev -> next = blockToAdd;
			} else {
				size_list = blockToAdd;
			}
			blockToAdd -> next = curr;
		}
	}
}

static void setCanary(metadata_t *curr) {
	unsigned long can = ((uintptr_t) curr ^ CANARY_MAGIC_NUMBER) + 1890;
	uint8_t *end = ((uint8_t*) curr) + curr -> size - sizeof(unsigned long) + TOTAL_METADATA_SIZE;
	unsigned long *endC = (unsigned long*) end;
	curr -> canary = can;
	*endC = can;
}

static metadata_t* splitBlock(metadata_t *curr, size_t size) {
	removeBlock(curr);
	uint8_t* s = ((uint8_t*) curr) + curr -> size - size;
	metadata_t *new = (metadata_t*) s;
	curr -> size = curr -> size - size - TOTAL_METADATA_SIZE;
	new -> size = size;
	setCanary(new);
	addBlock(curr);
	new -> next = NULL;
	return new;
}


static metadata_t* left(metadata_t *currBlock) {
	metadata_t *curr = size_list;
	while (curr != NULL) {
		if ((uintptr_t) ((uint8_t*) curr + TOTAL_METADATA_SIZE + curr -> size) == (uintptr_t) currBlock) {
			return curr;
		}
		curr = curr -> next;
	}
	return NULL;
}



static metadata_t* right(metadata_t *currBlock) {
	metadata_t *curr = size_list;
	while (curr != NULL) {
		if ((uintptr_t) ((uint8_t*) currBlock + TOTAL_METADATA_SIZE + currBlock -> size) == (uintptr_t) curr) {
			return curr;
		}
		curr = curr -> next;
	}
	return NULL;
}

static void mergeL(metadata_t *currBlock, metadata_t *left) {
	removeBlock(left);
	left -> size += currBlock -> size + TOTAL_METADATA_SIZE;
	addBlock(left);
}

static void mergeR(metadata_t *currBlock, metadata_t *right) {
	removeBlock(right);
	currBlock -> size += right -> size + TOTAL_METADATA_SIZE;
	addBlock(currBlock);
}


/* MALLOC
 * See PDF for documentation
 */
void *my_malloc(size_t size) {
	if (size + TOTAL_METADATA_SIZE > SBRK_SIZE) {
  	my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
  	return NULL;
  }

  if (size == 0) {
  	my_malloc_errno = NO_ERROR;
  	return NULL;
  }

  while (1) {
  	metadata_t *curr = size_list;
  	while (curr != NULL) {
  		if (curr -> size == size) {
  			removeBlock(curr);
  			setCanary(curr);
  			my_malloc_errno = NO_ERROR;
  			return curr + 1;
  		} else if (curr -> size - MIN_BLOCK_SIZE >= size) {
  			my_malloc_errno = NO_ERROR;
  			return splitBlock(curr, size) + 1;
  		}
  		curr = curr -> next;
  	}
  	//sbrk
  	metadata_t *new = (metadata_t*) my_sbrk(SBRK_SIZE);
  	if (new == NULL) {
  		my_malloc_errno = OUT_OF_MEMORY;
  		return NULL;
  	}

  	new -> size = SBRK_SIZE - TOTAL_METADATA_SIZE;
  	new -> next = NULL;

  	metadata_t *leftA = left(new);
  	metadata_t *rightA = right(new);

  	if (rightA != NULL) {
  		mergeR(new, rightA);
  	}
  	if (leftA != NULL) {
  		mergeL(new, leftA);
  		if (rightA != NULL) {
  			removeBlock(new);
  		}
  	}
  	if (leftA == NULL && rightA == NULL) {
  		addBlock(new);
  	}
  }
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
  if (ptr == NULL) {
  	return my_malloc(size);
  }
  metadata_t *node = (metadata_t*) ptr - 1;
  if (size == 0 && node != NULL) {
   	my_free(ptr);
   	return NULL;
  }
  unsigned long can = ((uintptr_t) node ^ CANARY_MAGIC_NUMBER) + 1890;
	if (node -> canary != can) {
		my_malloc_errno = CANARY_CORRUPTED;
		return NULL;
	}

	unsigned long *endC = (unsigned long*) ((uint8_t*) node + sizeof(metadata_t) + node -> size);
	if (*endC != can) {
		my_malloc_errno = CANARY_CORRUPTED;
		return NULL;
	}

	metadata_t *block = my_malloc(size);
	if (block == NULL) {
		return NULL;
	}
	memcpy(block, ptr, size);
	my_malloc_errno = NO_ERROR;
	my_free(ptr);
	return block;
}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
	metadata_t *p = my_malloc(nmemb *size);
	if (p == NULL) {
		return p;
	} else {
		memset(p, 0, nmemb * size);
	}
	return p;
}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    if (ptr != NULL) {
    	metadata_t *block = (metadata_t*) ptr - 1;
    	int holdInt = 0;
    	unsigned long can = ((uintptr_t) block ^ CANARY_MAGIC_NUMBER) + 1890;
    	uint8_t *end = ((uint8_t*) block) + block -> size - sizeof(unsigned long) + TOTAL_METADATA_SIZE;
			unsigned long *endC = (unsigned long*) end;
			if (block -> canary != can) {
				holdInt = 0;
			} else if (*endC != can) {
				holdInt = 0;
			} else {
				holdInt = 1;
			}
    	if (holdInt == 1) {
    		metadata_t *leftA = left(block);
	    	metadata_t *rightA = right(block);

	    	if (rightA != NULL) {
	    		mergeR(block, rightA);
	    	}
	    	if (leftA != NULL) {
	    		mergeL(block, leftA);
	    		if (rightA != NULL) {
	    			removeBlock(block);
	    		}
	    	}
	    	if (leftA == NULL && rightA == NULL) {
	    		addBlock(block);
	    	}
	    	my_malloc_errno = NO_ERROR;
    	} else {
    		my_malloc_errno = CANARY_CORRUPTED;
    	}
    } else {
    	my_malloc_errno = NO_ERROR;
    }
}
