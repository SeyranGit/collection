#include <malloc.h>
#include <stdio.h>
#include "list.h"


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
		list->cache.last_node = &(list->root_node);
		while (*(list->cache.last_node)) {
			list->cache.last_node = &(
				(*(list->cache.last_node))->next_node
			);
		}
		*(list->cache.last_node) = create_node(item);
	} else {
		(*(list->cache.last_node))->next_node = create_node(item);
		list->cache.last_node = &(
			(*(list->cache.last_node))->next_node
		);
	}
	list->len++;
	return SUCCESSFULLY;
}


static error_code
imp_insert(List *list, int32 index, int32 item) {
	int32 current_index = 0;
	Node *node = list->root_node;
	Node *temp_node = NULL;
	Node *new_node = NULL;
	while (node) {
		if (index == current_index) {
			new_node = create_node(item);
			temp_node = node->next_node;
			node->next_node = new_node;
			new_node->next_node = temp_node;
			return SUCCESSFULLY;
		}
		node = node->next_node;
		current_index++;
	}
	printf("Exception: Index %d is out of range.\n", index);
	return OUT_OF_RANGE; 
}


static int32
imp_get(List *list, int32 index) {
	int32 current_index = 0;
  Node *node = list->root_node;	
	while (node) {
		if (index == current_index) {
			return node->item;
		}
		node = node->next_node;
		current_index++;
	}
	printf("Exception: Index %d is out of range.\n", index);
	return 0;
}


static error_code
imp_remove(List *list, int32 index) {
	int32 current_index = 0;
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


error_code
clear_list(List *list) {
	Node *current_node = list->root_node;
	Node *temp_node = NULL;
	while (current_node) {
		temp_node = current_node->next_node;
		free(current_node);
		current_node = temp_node;
	}
	list->root_node = NULL;
	list->cache.last_node = NULL;
	return SUCCESSFULLY;
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
