#include <stdio.h> 
#include <stdlib.h>
#include "allocator.h"

int main(int argc, char * argv[]){ 
        int algorithm = atoi(argv[1]);  
	unsigned int seed = atoi(argv[2]);
	int requests = atoi(argv[3]); 
	 
	int r =0;  
	void * ptr;  
	int random_num;
	srandom(seed);
	allocator_init(10240, algorithm);
	while( r<requests){ 
	  
	  random_num = (random() + 100) % 1000 ; 
	  
	  ptr = allocate(random_num);
	  deallocate(ptr); 
	  r++;
	} 
	printf("avg frag size is %f\n" , average_frag());

	

}
