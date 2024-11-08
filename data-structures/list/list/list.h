#ifndef LIST_H
#define LIST_H


#ifndef __GNUC__
  #define NORETURN __attribute__((noreturn))
#else
  #define NORETURN
#endif


#define int32 int
#define int8 char
#define uint32 unsigned int
#define uint8 unsigned char

#define SUCCESSFULLY 0
#define OUT_OF_RANGE 1


typedef int8 error_code;


typedef struct node {
  int32 item;
  struct node *next_node;
} Node;


typedef struct cache {
  Node **last_node;
  // ...
} Cache;


typedef struct list {
  Node *root_node;
  Cache cache;
  uint32 len;

  int32 (*get)(struct list *list, uint32 index);
  error_code (*append)(struct list *list, int32 item);
  error_code (*remove)(struct list *list, uint32 index);
  error_code (*insert)(struct list *list, uint32 index, int32 item);
} List;


List new_list(void);
error_code clear_list(List *list);
void print_list(List *list);

#endif
