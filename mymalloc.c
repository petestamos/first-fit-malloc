///////////////////////////////////////////////////////////////////////////
////////////////////// PETER STAMOS - CS449 PROJECT 3 /////////////////////
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mymalloc.h"

struct Node *first_node = NULL;

///////////////////////////////////////////////////////////////////////////

void *my_firstfit_malloc(int size) {

  void *location;
  struct Node *current_node; 
  int total = (int)sizeof(struct Node) + size;

  if (first_node == NULL) {

    first_node = sbrk(total);

    first_node->previous = NULL;
    first_node->next = NULL;
    first_node->using = 1;
    first_node->size = total;

    location = ((void *) first_node + sizeof(struct Node));

    return location;
  }

  current_node = first_node;

  while (current_node->next != NULL) {

    if (current_node->using) {
      current_node = current_node->next;
    }

    else if (((!current_node->using) && (current_node->size < total))) {
      current_node = current_node->next;
    }

    else {

      if ((current_node->size - total) > sizeof(struct Node)) {

        struct Node *node;

        node = (struct Node *)(((void *) current_node) + total);
        node->previous = current_node;
        node->next = current_node->next;
        node->size = current_node->size - total;
        node->using = 0;

        location = ((void *) current_node) + sizeof(struct Node);

        current_node->next = node;
        current_node->size = total;
        current_node->using = 1;

        return location;
      }

      else {

        current_node->using = 1;
        location = ((void *) current_node) + sizeof(struct Node);

        return location;
      }
    }
  }

  current_node->next = sbrk(total);

  current_node->next->previous = current_node;
  current_node->next->next = NULL;
  current_node->next->using = 1;
  current_node->next->size = total;

  location = ((void *) current_node->next) + sizeof(struct Node);

  return location;
}

///////////////////////////////////////////////////////////////////////////

void my_free(void *ptr) {

  struct Node *current_node;

  current_node = (struct Node *)(ptr - sizeof(struct Node));

  if (current_node->previous == NULL) {

    if (current_node->next == NULL) {

      int size = current_node->size;

      first_node = NULL;
      sbrk(-size);
    }

    else {

      if (!(current_node->next->using)) {

        current_node->using = 0;
        current_node->size += current_node->next->size;
        current_node->next = current_node->next->next;
      }

      else {
        current_node->using = 0;
      }
    }
  }

  else if ((current_node->previous != NULL) && (current_node->next == NULL)) {

    int size;

    if (!(current_node->previous->using)) {

      current_node->previous->size += current_node->size;
      current_node = current_node->previous;
    }

    size = current_node->size;

    if (current_node == first_node) {
      first_node = NULL;
    }

    else {
      current_node->previous->next = NULL;
    }

    sbrk(-size);
  }

  else {

    if (!(current_node->previous->using)) {

      current_node->previous->size += current_node->size;
      current_node->previous->next = current_node->next;
      current_node->next->previous = current_node->previous;

      current_node = current_node->previous;
    }

    if (!(current_node->next->using)) {

      current_node->size += current_node->next->size;
      current_node->next->next->previous = current_node;
      current_node->next = current_node->next->next;
    }

    current_node->using = 0;
  }
}

///////////////////////////////////////////////////////////////////////////
////////////////////// PETER STAMOS - CS449 PROJECT 3 /////////////////////
///////////////////////////////////////////////////////////////////////////
