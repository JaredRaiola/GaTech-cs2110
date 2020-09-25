/**
 * CS 2110 - Spring 2019 - Timed Lab #5
 *
 * @author Jared Raiola
 *
 * tl5.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl5.h"
#include "string.h"

///* You should NOT have any global variables. */

/** copy_list
  *
  * Create a new list and new pokemon nodes  
  *
  * If listToCopy is NULL return NULL. For any memory allocations
  * failures your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must destroy
  * the list 
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The struct list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
struct list *copy_list(struct list *listToCopy)
{
  if (listToCopy == NULL) {
    return NULL;
  }

  struct list *newList = malloc(sizeof(struct list));
  if (!newList) {
    return NULL;
  }
  if (listToCopy -> starter_pokemon == NULL) {
    newList -> starter_pokemon = listToCopy -> starter_pokemon;
    return newList;
  }

  newList -> starter_pokemon = malloc(sizeof(struct pokemon));
  if (!(newList -> starter_pokemon)) {
    free(newList);
    return NULL;
  }

  struct pokemon *temp = malloc(sizeof(listToCopy -> starter_pokemon));
  if (!temp) {
    free(newList -> starter_pokemon);
    free(newList);
    return NULL;
  }
  free(temp);

  struct pokemon *node = newList -> starter_pokemon;

  struct pokemon *curr = listToCopy -> starter_pokemon;

  while(curr != NULL) {
    node -> level = curr -> level;
    node -> type = malloc(strlen(curr -> type) + 1);
    if (node -> type == NULL) {
      destroy(newList);
      return NULL;
    }
    node -> evolve = malloc(sizeof(struct pokemon));
    if (node -> evolve == NULL) {
      destroy(newList);
      return NULL;
    }
    strcpy(node -> type, curr -> type);
    curr = curr -> evolve;
    node = node -> evolve;
  }
  

  return newList;
}

/** Destroy
  *
  * Destroys the entire struct list. This function removes every list node
  * and finally remove the list itself.
  *
  * HINT: remember every malloc needs a respective free
  * 
  * @param listToEmpty a pointer to the struct list
  */
void destroy(struct list *listToDestroy)
{
  if (listToDestroy != NULL) {
    struct pokemon *node = listToDestroy -> starter_pokemon;
    while (node != NULL) {
      struct pokemon *prev = node;
      node = node -> evolve;
      free(prev -> type);
      free(prev);
    }
  }
  free(listToDestroy);
}

