#include <malloc.h>
#include <stdio.h>
#include "list.h"


#define LIST_CACHE(list_obj) list_obj->cache.last_node


static Node
*create_node(int32 item) {
  Node *node = malloc(sizeof(Node));
  node->item = item;
  node->next_node = NULL;
  return node;
}


static error_code
imp_append(List *list, int32 item) {
  if (!list->cache.last_node) {
    LIST_CACHE(list) = &(list->root_node);
    while (*(LIST_CACHE(list))) {
      LIST_CACHE(list) = &(
        (*(LIST_CACHE(list)))->next_node
      );
    }
    *(LIST_CACHE(list)) = create_node(item);
  } else {
    (*(LIST_CACHE(list)))->next_node = create_node(item);
    LIST_CACHE(list) = &(
      (*(LIST_CACHE(list)))->next_node
    );
  }
  list->len++;
  return SUCCESSFULLY;
}


static error_code
imp_insert(List *list, uint32 index, int32 item) {
  uint32 current_index = (uint32)1;
  Node *node = list->root_node;
  Node *temp_node = NULL;
  Node *new_node = NULL;
  if (!node) {
    return list->append(list, item);
  }
  else {
    if (index == 0) {
      new_node = create_node(item);
      list->root_node = new_node;
      list->len++;
      new_node->next_node = node;
      return SUCCESSFULLY;
    }
    else {
      while (node) {
        if (index == current_index) {
          new_node = create_node(item);
          temp_node = node->next_node;
          node->next_node = new_node;
          new_node->next_node = temp_node;
          list->len++;
          return SUCCESSFULLY;
        }
        node = node->next_node;
        current_index++;
      }
    }
  }
  printf("Exception: Index %u is out of range.\n", index);
  return OUT_OF_RANGE;
}


static int32
imp_get(List *list, uint32 index) {
  Node *node;
  if (index >= list->len) {
    printf("Exception: Index %u is out of range.\n", index);
    return 0;
  }
  node = list->root_node;
  for (uint32 current_index = 0; 
       current_index < index; 
       current_index++) {
    node = node->next_node;
  }
  return node->item;
}


static error_code
imp_remove(List *list, uint32 index) {
  uint32 current_index = (uint32)0;
  Node *node = list->root_node;
  Node *previus_node = NULL;
  while (node) {
    if (index == current_index) {
      if (previus_node) {
        previus_node->next_node = node->next_node;
      } else {
        if (node->next_node) {
          list->root_node = node->next_node;
        } else {
          list->root_node = NULL;
        }
      }
      list->len--;
      free(node);
      return SUCCESSFULLY;
    }
    previus_node = node;
    node = node->next_node;
    current_index++;
  }
  return OUT_OF_RANGE;
}


error_code
clear_list(List *list) {
  Node *current_node = list->root_node;
  Node *temp_node = NULL;
  while (current_node) {
    temp_node = current_node->next_node;
    free(current_node);
    current_node = temp_node;
  }
  list->len = 0;
  list->root_node = NULL;
  list->cache.last_node = NULL;
  return SUCCESSFULLY;
}


List
new_list(void) {
  List list;
  Cache cache;
  cache.last_node = NULL;
  list.root_node = NULL;
  list.cache = cache;
  list.len = 0;
  list.append = imp_append;
  list.remove = imp_remove;
  list.insert = imp_insert;
  list.get = imp_get;

  return list;
}


void 
print_list(List *list) {
  Node *node = list->root_node;
  printf("[");
  while (node) {
    if (node->next_node) {
      printf("%d, ", node->item);
    } else {
      printf("%d", node->item);
    }
    node = node->next_node;
  }
  printf("]\n");
}
