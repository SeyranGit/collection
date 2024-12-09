#include "stack.h"


static error_code push_impl(Stack *stack, int32 item) {
  return (
    stack->inner_list.append(
      &(stack->inner_list), item
    )
  ); 
}


static int32 pop_impl(Stack *stack) {
  uint32 last_index = stack->inner_list.len - 1;
  int32 result = stack->inner_list.get(
    &(stack->inner_list), last_index
  );
  stack->inner_list.remove(&(stack->inner_list), last_index);
  return result;
}


static int32 peek_impl(Stack *stack) {
  return (
    stack->inner_list.get(
      &(stack->inner_list),
      stack->inner_list.len - 1
    )
  );
}


Stack new_stack(void) {
  Stack stack;
  stack.inner_list = new_list();
  stack.push = push_impl;
  stack.pop = pop_impl;
  stack.peek = peek_impl;
  return stack;
}


error_code clear_stack(Stack *stack) {
  clear_list(&(stack->inner_list));
  return SUCCESSFULLY;
}
