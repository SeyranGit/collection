#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


#define LIST_CACHE(list) ((list)->cache.last_node)


NORETURN
static void exit_and_clear_list(List* list) {
  clear_list(list);
  exit(EXIT_FAILURE);
}


static Node *create_node(ItemType item) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }  
  node->item = item;
  node->next_node = NULL;
  return node;
}


static error_code append_impl(List *list, ItemType item) {
  if (!list->cache.last_node || list->len == 0) {
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


static error_code insert_impl(List *list, uint32 index, ItemType item) {
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
    } else {
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
  fprintf(stderr, "Exception: Index %u is out of range.\n", index);
  exit_and_clear_list(list);
}


static ItemType get_impl(List *list, uint32 index) {
  Node *node;
  if (index >= list->len) {
    fprintf(stderr, "Exception: Index %u is out of range.\n", index);
    exit_and_clear_list(list);
  }
  node = list->root_node;
  for (uint32 current_index = 0; 
       current_index < index; 
       current_index++) {
    node = node->next_node;
  }
  return node->item;
}


static error_code remove_impl(List *list, uint32 index) {
  uint32 current_index = (uint32)0;
  Node *node = list->root_node;
  Node *previous_node = NULL;
  while (node) {
    if (index == current_index) {
      if (previous_node) {
        previous_node->next_node = node->next_node;
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
    previous_node = node;
    node = node->next_node;
    current_index++;
  }
  fprintf(stderr, "Exception: Index %u is out of range.\n", index);
  exit_and_clear_list(list);
}


error_code clear_list(List *list) {
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


List new_list(void) {
  List list = {
    .root_node = NULL,
    .len = 0,
    .cache = {
      .last_node = NULL
    }
  };
  list.append = append_impl;
  list.remove = remove_impl;
  list.insert = insert_impl;
  list.get = get_impl;
  return list;
}
