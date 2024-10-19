#include <stdio.h>
#include "List/list.h"


static void 
test(List *list) {
  clear_list(list);
  print_list(list);
  for (int32 i = 0; i < 20000000; i++) {
    list->append(list, i);
  }
  puts("[OK]");
  clear_list(list);
  puts("[CLEAR]");
}


int main(void) {
  List numbers = new_list(); 
  numbers.append(&numbers, 10);
  numbers.append(&numbers, 20);
  numbers.append(&numbers, 30);

  print_list(&numbers);
  numbers.remove(&numbers, 1);	
  print_list(&numbers);
  numbers.insert(&numbers, 0, 22);
  print_list(&numbers);
  printf("Item: %d\n", numbers.get(&numbers, 1));
  test(&numbers);
  
  return 0;
}
