#include "allocator.h"

struct dlist *free_list; 
struct dlist *allocated_list;
int policy_num; 


int allocator_init(size_t size, int policy){ 
  policy_num = policy;
  free_list = dlist_create();
 
  allocated_list = dlist_create();
  void *ptr; 
  ptr = malloc(size);
  if(NULL == ptr){
    perror("malloc failed");
    return -1;
    
  }
   dlist_add_back(free_list,ptr,size);
  
  return 0;

} 

void *allocate(size_t size){
  void *node;
  int i =0;
  if(0 == policy_num){ //first fit 
    node = first_fit(size);   

    
  }
  if(1 == policy_num){ // best fit 
    node = best_fit(size); 
    
    
  }
  if(2 == policy_num){ // worst fit 
    node = worst_fit(size);
  }  
 
  
  dlist_add_back(allocated_list, node, size);

 return node;
}

void *first_fit(int size){    
  int i = 0;
  void *node;
  void *search_node;
  search_node = dlist_iter_begin(free_list); 
  
  while(i < free_list->counter){
    if(free_list->iter->mem_size > size){  
 
      free_list->iter->mem_size -= size; 
      
      free_list->iter->data += size; 
    
      node = search_node;
      
      
    } 
    i++;
    search_node = dlist_iter_next(free_list); 
  
  }  
  
  
  return node; //returns the correct pointer

} 

void *best_fit(int size){ 
  int i =0;
  void *search_node; 
  void *best_node;
  void *change_node; 
  void *return_node;
  int best_size = 9999;
  search_node = dlist_iter_begin(free_list);
  while(i < free_list->counter){
    if(free_list->iter->mem_size >= size){
      if(best_size > free_list->iter->mem_size){
        best_size = free_list->iter->mem_size; 
       
        best_node = search_node; 
       
      }

  }
    i++;
    search_node = dlist_iter_next(free_list);
  }   
  i=0;
 
  change_node = dlist_iter_begin(free_list); 

  while(i < free_list->counter){

    if(change_node  == best_node){
  
      free_list->iter->data += size; 
      free_list->iter->mem_size -= size;
     
      return_node = free_list->iter->data;
    }
    i++;
    change_node = dlist_iter_next(free_list);
      
  }
    
   
  

  return return_node;

  }



void *worst_fit(int size){
  int i =0;
  void *node; 
  void *worst_node;
  void *change_node; 
  void *return_node;
  int worst_size = 0;
  node = dlist_iter_begin(free_list);
  while(i < free_list->counter){ 
    if(free_list->iter->mem_size >= size){
      if(worst_size < free_list->iter->mem_size){
        worst_size = free_list->iter->mem_size; 
        worst_node = node;
      }
  }
    i++;
    node = dlist_iter_next(free_list);
  } 
  i=0;
  change_node = dlist_iter_begin(free_list); 

  while(i < free_list->counter){

    if(change_node  == worst_node){
  
      free_list->iter->data += size; 
      free_list->iter->mem_size -= size;
 
      return_node = free_list->iter->data;
    }
    i++;
    change_node = dlist_iter_next(free_list);
      
  }
  return worst_node;
} 

int deallocate(void *ptr){   

  int i =0;
  void * node;
  int ret_val = -1;
  int size;
  node = dlist_iter_begin(allocated_list); 
  
  while(i < allocated_list->counter){
  
    if(allocated_list->iter->data == ptr){ 
  
      ret_val = 0;

      break;
    }
    node = dlist_iter_next(allocated_list);
    i++;
  }
  if(0 == ret_val){
    size = allocated_list->iter->mem_size;
    dlist_add_back(free_list, ptr, size); 
    dlist_find_remove(allocated_list, ptr);

  } 
 
  return ret_val;

  

  
} 

void print_vals_allocated(){
  void *node;
   node = dlist_iter_begin(allocated_list); 
   int i=0;
  while(i< allocated_list->counter){ 
    printf("node %d has size of %d \n",i,allocated_list->iter->mem_size);
    node = dlist_iter_next(allocated_list);
    i++;
  }  
}


void print_vals_free(){
  void *node;
   node = dlist_iter_begin(free_list); 
   int i=0;
    while(i < free_list->counter){ 
    printf("node %d has size of %d \n",i,free_list->iter->mem_size);
    node = dlist_iter_next(free_list);
    i++;
  }   
    
} 
double average_frag(){
  double sum =0; 
  double num_nodes = (double) free_list->counter;  
  double ret_val =0;
  void * node = dlist_iter_begin(free_list); 
  int i=0;
  while( i< num_nodes){
    sum += free_list->iter->mem_size;
    node = dlist_iter_next(free_list);
    i++;
  } 
  ret_val = sum / num_nodes; 
  return ret_val;
  
}







