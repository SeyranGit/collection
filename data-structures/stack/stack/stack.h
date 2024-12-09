#ifndef STACK_H
#define STACK_H

#include "../../list/list/list.h"

#define SUCCESSFULLY (int8)0
#define OUT_OF_RANGE (int8)1


typedef struct stack {
  List inner_list;

  error_code (*push)(struct stack *stack, int32 item);
  int32 (*pop)(struct stack *stack);
  int32 (*peek)(struct stack *stack);
} Stack;


error_code clear_stack(Stack *stack);
Stack new_stack(void);

#endif
