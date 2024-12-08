# Implementation of the stack data structure in C

```text
 ____   _____    _      _____  _   __
| ___| |_   _|  / \    /  ___|| | / /
|___ \   | |   / _ \  |  |    | |/ / 
 ___) |  | |  / ___ \ |  |__  |    \ 
|____/   |_| /_/   \_\ \____| |_|\ _\
```

* Usage example
```c
#include <stdio.h>
#include "stack/stack.h"

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
  clear_stack(&stack);
  return 0;
}
```

* Output
```text
30
30
30
20
10
```

### Build
___
If you don't have LLVM installed, you need to install it from the following link: [LLVM](https://github.com/llvm/llvm-project/releases/tag/llvmorg-19.1.0). Once installed, you can clone the repositories and enter the following command in the terminal if you are using Windows:
```
build
```

*Note: you may have to add the path to "../LLVM/bin" to your environment variable*
