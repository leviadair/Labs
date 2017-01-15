#ifndef _ALLOCATOR_H_ 
#define _ALLOCATOR_H_
#include "dlist.h" 
#include "dnode.h" 
#include <stdlib.h>
#include <stdio.h>

int allocator_init(size_t size, int policy); 
void *allocate(size_t size); 
int deallocate(void *ptr);  
void *first_fit(int size);
void *best_fit(int size);
void *worst_fit(int size);
void print_vals_allocated();
void print_vals_free();
double average_frag();
#endif /*ALLOCATOR_H_*/
