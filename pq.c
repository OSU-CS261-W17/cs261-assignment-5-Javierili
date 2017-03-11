/*
 * This file contains the implementation of a priority queue.
 *
 * You must complete the implementations of these functions:
 *   pq_insert()
 *   pq_first()
 *   pq_remove_first()
 */

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dynarray.h"
#include "pq.h"

// This is the initial capacity that will be allocated for the heap.
#define INITIAL_HEAP_CAPACITY 16

/*
 * This is the definition of the structure we will use to represent the
 * priority queue.  It contains only a dynamic array, which will be used to
 * store the heap underlying the priority queue.
 */
struct pq {
  struct dynarray* heap;
};


/*
 * This is an auxiliary structure that we'll use to represent a single element
 * in the priority queue.  It contains two fields:
 *
 *   priority - the priority value assigned to the item
 *   item - the pointer to the data item represented by this element
 *
 * Both of these will come directly from the corresponding values passed to
 * pq_insert().
 */
struct pq_elem {
  int priority;
  void* item;
};


/* ADDED FUNCTION: perlocateHeap 
 * struct dynArr: heap. Pointer to priority queue heap
 * int1: the size of the heap, max indx function should reach
 * int2: indx of currently examined node
 */ 
 void perlocateHeap(struct dynarray *, int, int);
/*
 * This function allocates and initializes a new priority queue.
 *
 * You should not modify this function.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  assert(pq);
  pq->heap = dynarray_create(INITIAL_HEAP_CAPACITY);
  return pq;
}


/*
 * This function frees the memory associated with a priority queue.
 *
 * You should not modify this function.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  while (!pq_isempty(pq)) {
    pq_remove_first(pq);
  }
  dynarray_free(pq->heap);
  free(pq);
}

/*
 * This function returns 1 if the given priority queue is empty or 0
 * otherwise.
 *
 * You should not mofidy this function.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return dynarray_size(pq->heap) == 0;
}


/*
 * This function inserts a new item with a specified priority into a priority
 * queue.
 *
 * You should complete the implementation of this function.  The first part
 * is done for, where a new element is created to be placed into the dynamic
 * array underlying the priority queue.
 * Rest written by ili!
 */
void pq_insert(struct pq* pq, void* item, int priority) {
  assert(pq);
  assert(pq->heap);
  /*
   * Allocate space for the new element to be placed into the priority queue
   * and initialize it with the provided values.
   */
  struct pq_elem* new_elem = malloc(sizeof(struct pq_elem));
  new_elem->item = item;
  new_elem->priority = priority;
  
  struct dynarray * heap = pq->heap;
  struct pq_elem * par = 0;
  int bol = 0; //for perlocating 
  int parent; 
  int last = dynarray_size(heap); //gives the last filled space 
  				//after next line of code

  /*
   * Figure out where in the heap array to insert the new element represented
   * by new_elem and insert it.
   */

  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the newly added element up in the heap array.  To
   * perform the percolation, you will have to compare the priority values of
   * the struct pq_elems in the heap array (i.e. by comparing the
   * elem->priority values).
   */
  
  //Functions assers heap pointer and size, -1 indicates 
  //insert at next open spot in array, resizes if necessary 
  //increments heap size, and adds new_elem to array.
   dynarray_insert(heap, -1, new_elem); // add new elem to heap
	

   //Perlocate up:
   while(bol<1){
	   //find the node's parent
   	//parent = (int) floor((last-1) / 2);
	parent = (last - 1) / 2;
	par = dynarray_get(heap,parent); //the parent's element
	if(priority < par->priority){
		dynarray_set(heap,last,par);
		dynarray_set(heap,parent,new_elem);
		last = parent;
	}
	else{
	//break out of loop 
	 bol = 1;
	}

   } //while

   //printing array to screen (debugging)
   struct pq_elem * tempor = dynarray_get(heap, 0);
printf("\n");
   for(int i= 0; i<dynarray_size(heap);i++){
   tempor = dynarray_get(heap, i);
   printf("%d: %d --",i,tempor->priority); 
   }
   printf("\n");
} //insert


/*
 * This function returns the first (highest-priority) item from a priority
 * queue without removing it.
 *
 * You should complete the implementation of this function.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);

  struct pq_elem* first_elem = NULL;
  first_elem = dynarray_get(pq->heap, 0);
 

  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */

  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */
  if (first_elem != NULL) {
    return first_elem->item;
  } else {
    return NULL;
  }
}


/*
 * This function removes the first (highest-priority) element from a priority
 * queue and returns its value.
 *
 * You should complete this function.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
  assert(dynarray_size(pq->heap) > 0);

  struct pq_elem* first_elem = NULL;
  struct dynarray * heap = pq->heap;
  //struct pq_elem * tester = NULL; //DEBUGGER-- REMOVE LATER

  /*
   * Determine what index in the heap array corresponds to the highest-priority
   * element (i.e. the one with the lowest priority value), and store the
   * value there in first_elem.
   */

  first_elem = dynarray_get(heap, 0);

  //DEBUGGING
  //printf("In remove_first  Priority is: %d\n",first_elem->priority);
  /*
   * Replace the highest-priority element with the appropriate one from within
   * the heap array.  Remove that replacement element from the array after
   * copying its value to the location of the old highest-priority element..
   */
  if(dynarray_size(heap)!=1){
  dynarray_set(heap,0,dynarray_get(heap,-1)); //replace idx 0 w/ last filled
  }
  dynarray_remove(heap,-1); //remove last node

 //DEBUGGING: 
  //tester = dynarray_get(heap,0);
  //printf("After last swap: Priority is: %d\n",tester->priority);
  /*
   * Restore the heap so that it has the property that every node's priority
   * value is less than the priority values of its children.  This can be
   * done by "percolating" the element that replaced the highest-priority
   * element down in the heap array.  To perform the percolation, you will
   * have to compare the priority values of the struct pq_elems in the heap
   * array (i.e. by comparing the elem->priority values).  It may be helpful
   * to write a helper function to accomplish this percolation down.
   */
  if(dynarray_size(heap)>1){
   perlocateHeap(heap, dynarray_size(heap)-1,0);
  }
  /*
   * Return the extracted item, if the element taken out of the priority
   * queue is not NULL.
   */

   /*printing array to screen (DEBUGGING)
   struct pq_elem * tempor = dynarray_get(heap, 0);
   printf("\n");
   for(int i= 0; i<dynarray_size(heap);i++){
   tempor = dynarray_get(heap, i);
   printf("%d: %d --",i,tempor->priority); 
   }
   printf("\n");

  printf("Check for removed node: priority was: %d\n",first_elem->priority);
*/


  if (first_elem != NULL) {
    void* item = first_elem->item;
    free(first_elem);
    return item;
  } else {
    return NULL;
  }
}


/* ADDED FUNCTION: perlocateHeap 
 * checks node at index indx for one two or no children
 * if has children, checks if any have higher priority than parent,
 * calls perlocateHeap for highest priority child, 
 * if not or is leaf, returns. 
 *
 * preconditions: 
 * heap has at least one node, indx and end are valid indexs of heap
 * 
 * heap: heap. Pointer to priority queue heap
 * end: the size of the heap, max indx function should reach
 * indx: index of currently examined node
 */
void perlocateHeap(struct dynarray * heap, int end, int indx){
  assert(heap);
  assert(indx < dynarray_size(heap));

  int left = indx * 2 + 1; //finding the indexes of indx's kids
  int right = indx * 2 + 2;
  struct pq_elem *test = dynarray_get(heap,indx);  
  int indxPrio= test->priority;
  struct pq_elem * temp = NULL;  //will hold left/right children
  struct pq_elem * temp0 = NULL;
  
  
  //DEBUGGING
  //printf("Woah we're perlcoating'\n"); 
  //indx has 2 kids:
  if(right<= end){

  	temp0 = dynarray_get(heap,right);
  	temp = dynarray_get(heap, left);
	
	//finding child w/ highest priority 
	if(temp0->priority < temp->priority){
	   temp = dynarray_get(heap,right);
	   left = right;
	}


  } //ifRight

  //indx has only 1 kid
  else if(left <= end){
  	temp = dynarray_get(heap,left);
  }

  //no kids
  else { return; }

  
  if(temp->priority < indxPrio){
	//swap, then recurse

	   dynarray_set(heap,left, test);
	   dynarray_set(heap, indx, temp);
	   perlocateHeap(heap,end,left);	
	}
  else { return; }
}
