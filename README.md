# Implementation of a singly linked list data structure in C

```
  _       _    ____    _____  
 | |     | |  | ___|  |_   _| 
 | |     | |  |___ \    | |   
 | |__   | |   ___) |   | |   
 |_|__|  |_|  |____/    |_|   
```

* Usage example
```c
#include <stdio.h>
#include "List/list.h"

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
  clear_list(&number);

  return 0;
}

```


* Output
```
[10, 20, 30]
[10, 30]
[10, 22, 30]
Item: 22
```
