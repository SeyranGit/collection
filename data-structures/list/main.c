#include <stdio.h>
#include <malloc.h>
#include "list/list.h"


#define dename(type, pointer) *(type*)pointer


static void print_list_int(List *list) {
  Node *node = list->root_node;
  printf("[");
  while (node) {
    printf("%d", dename(int, node->item));
    if (node->next_node) {
      printf(", ");
    }
    node = node->next_node;
  }
  printf("]\n");
  return;
}


static void *cagv(int num) {
  int *num_ptr = malloc(sizeof(num));
  *num_ptr = num;
  return num_ptr;
}


static void test0(List *list) {
  int a = 10;
  clear_list(list);
  print_list_int(list);
  for (int32 i = 0; i < 20000000; i++) {
    list->append(list, cagv(i));
  }
  puts("[OK]");
  clear_list(list);
  puts("[CLEAR]");
  for (int32 i = 0; i < 20; i++) {
    list->append(list, cagv(i));
  }
  list->insert(list, (uint32)0, &a);
  list->insert(list, list->len, &a);
  print_list_int(list);
  printf("Len: %u\n", list->len);
  clear_list(list);
}


static void test1() {
  List numbers = new_list();
  typedef struct {
    int a;
    int b;
  } Object;
  Object obj_0;
  Object obj_1;
  obj_0.a = 10;
  obj_0.b = 20;
  obj_1.a = 20;
  obj_1.b = 10;
  numbers.append(&numbers, &obj_0);
  numbers.append(&numbers, &obj_1);
  obj_0 = dename(Object, numbers.get(&numbers, 0));
  obj_1 = dename(Object, numbers.get(&numbers, 1));
  printf("0: %d, 1: %d\n", obj_0.a, obj_0.b);
  printf("0: %d, 1: %d\n", obj_1.a, obj_1.b);
}


int main(void) {
  List numbers = new_list(); 
  int a = 10;
  int b = 20;
  int c = 30;
  int d = 22;
  
  numbers.append(&numbers, &a);
  numbers.append(&numbers, &b);
  numbers.append(&numbers, &c);
  print_list_int(&numbers);
  numbers.remove(&numbers, 1);
  print_list_int(&numbers);
  numbers.insert(&numbers, 0, &d);
  print_list_int(&numbers);
  printf("Item: %d\n", dename(int, numbers.get(&numbers, 1)));
  test0(&numbers);
  test1();
  return 0;
}
