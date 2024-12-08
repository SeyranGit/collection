#include <stdio.h>
#include "stack/stack.h"


static void test(Stack *stack) {
  for (int32 i = 0; i <= 9000; i++) {
    stack->push(stack, i);
  }
  for (int32 i = 0; i <= 9000; i++) {
    printf("%d\n", stack->pop(stack));
  }
}


int main(void) {
  Stack stack = new_stack();  
  stack.push(&stack, (int32)10);
  stack.push(&stack, (int32)20);
  stack.push(&stack, (int32)30);
  
  printf("%d\n", stack.peek(&stack));
  printf("%d\n", stack.peek(&stack));
  printf("%d\n", stack.pop(&stack));
  printf("%d\n", stack.pop(&stack));
  printf("%d\n", stack.pop(&stack));

  test(&stack);  
  clear_stack(&stack);
  return 0;
}
