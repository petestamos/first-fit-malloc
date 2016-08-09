///////////////////////////////////////////////////////////////////////////
////////////////////// PETER STAMOS - CS449 PROJECT 3 /////////////////////
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "mymalloc.h"

extern struct Node *first_node;

int *a; // Test 1
int *b; // Test 2
int *c; // Test 3
int *d; // Test 4
int *e; // Test 5

///////////////////////////////////////////////////////////////////////////

void allocation() {

  // Allocation of memory...
  a = my_firstfit_malloc(sizeof(int));
  b = my_firstfit_malloc(sizeof(int));
  c = my_firstfit_malloc(sizeof(int));
  d = my_firstfit_malloc(sizeof(int));
  e = my_firstfit_malloc(sizeof(int));

  // Set values for testing...
  *a = 1;
  *b = 2;
  *c = 3;
  *d = 4;
  *e = 5;
}

///////////////////////////////////////////////////////////////////////////

void free_a() {
  my_free(a);
}

void free_b() {
  my_free(b);
}

void free_c() {
  my_free(c);
}

void free_d() {
  my_free(d);
}

void free_e() {
  my_free(e);
}

///////////////////////////////////////////////////////////////////////////

void print() {

  int index = 1;

  struct Node *current_node = first_node;

  if (current_node == NULL) {
    printf("\nEMPTY LIST\n");
    printf("\n////////////////////////////////////////////////////////////\n");
  }

  else {

    while (current_node != NULL) {

      if (current_node->previous == NULL && current_node->next != NULL) {

        printf("\nNode: %i \n\nPrevious Node: NULL\n", index);

        printf("Current Node: %p\n", current_node);

        printf("Allocated: %i\n", current_node->using);

        printf("Node Size: %i\n", current_node->size);

        printf("Next Node: %p\n", current_node->next);

        printf("Data: %p\n", ((void *) current_node) + sizeof(struct Node));
     
	printf("\n////////////////////////////////////////////////////////////\n");
      }

      else if (current_node->previous == NULL && current_node->next == NULL) {

        printf("\nNode: %i \n\nPrevious Node: NULL\n", index);

        printf("Current Node: %p\n", current_node);

        printf("Allocated: %i\n", current_node->using);

        printf("Node Size: %i\n", current_node->size);

        printf("Next Node: NULL\n");

        printf("Data: %p\n", ((void *) current_node) + sizeof(struct Node));

	printf("\n////////////////////////////////////////////////////////////\n");
      }
 
      else if (current_node->previous != NULL && current_node->next == NULL) {

        printf("\nNode: %i \n\nPrevious Node: %p\n", index, current_node->previous);

        printf("Current Node: %p\n", current_node);

        printf("Allocated: %i\n", current_node->using);

        printf("Node Size: %i\n", current_node->size);

        printf("Next Node: NULL\n");

        printf("Data: %p\n", ((void *) current_node) + sizeof(struct Node));

	printf("\n////////////////////////////////////////////////////////////\n");
      }

      else {

        printf("\nNode: %i \n\nPrevious Node: %p\n", index, current_node->previous);

        printf("Current Node: %p\n", current_node);

        printf("Allocated: %i\n", current_node->using);

        printf("Node Size: %i\n", current_node->size);

        printf("Next Node: %p\n", current_node->next);

        printf("Data: %p\n", ((void *) current_node) + sizeof(struct Node));

	printf("\n////////////////////////////////////////////////////////////\n");
      }

      current_node = current_node->next;

      index++;
    }
  }
  printf("\nbrk: %p\n", sbrk(0));

  printf("\n////////////////////////////////////////////////////////////\n");
}

///////////////////////////////////////////////////////////////////////////

void free_first() {

	printf("\nFREE FIRST\n");

	print();

	free_a();

	print();

	printf("\nEND OF FREE FIRST\n");
}

///////////////////////////////////////////////////////////////////////////

void free_end() {

  allocation();

  printf("\nFREE END\n");

  print();

  free_e();

  print();

  free_d();

  print();

  free_c();

  print();

  free_b();

  print();

  free_a();

  print();

  printf("\nEND OF FREE END\n");
}

///////////////////////////////////////////////////////////////////////////

void free_middle() {

  allocation();

  printf("\nFREE MIDDLE\n");

  print();

  free_c();
  
  print();

  free_d();

  print();

  free_b();

  print();

  free_e();

  print();

  free_a();

  print();

  printf("\nEND OF FREE MIDDLE\n");
}

///////////////////////////////////////////////////////////////////////////

int main(void) {

  allocation();

  free_first();

  free_b();

  print();

  free_c();

  print();

  free_d();

  print();

  free_e();

  print();

  free_end();

  free_middle();

  return 0;
}

///////////////////////////////////////////////////////////////////////////
////////////////////// PETER STAMOS - CS449 PROJECT 3 /////////////////////
///////////////////////////////////////////////////////////////////////////
