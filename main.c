#include <stdio.h>
#include "List/list.h"


int main(void) {	
	List numbers = create_list(); 
	numbers.append(&numbers, 10);
	numbers.append(&numbers, 20);
	
	printf("Item: %d\n", numbers.get(&numbers, 0));
	return 0;
}

