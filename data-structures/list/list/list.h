#ifndef LIST_H
#define LIST_H


#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
  #define NORETURN [[noreturn]]
#elif !defined(__GNUC__)
  #define NORETURN __attribute__((noreturn))
#else
  #define NORETURN
#endif


typedef char int8;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef int8 error_code;
typedef void *ItemType;


#define SUCCESSFULLY (int8)0
#define OUT_OF_RANGE (int8)1


typedef struct node {
  ItemType item;
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

  ItemType (*get)(struct list *list, uint32 index);
  error_code (*append)(struct list *list, ItemType item);
  error_code (*remove)(struct list *list, uint32 index);
  error_code (*insert)(struct list *list, uint32 index, ItemType item);
} List;


List new_list(void);
error_code clear_list(List *list);
void print_list(List *list);

#endif
