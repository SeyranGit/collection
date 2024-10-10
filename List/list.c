#include <malloc.h>
#include "list.h"


static Node *create_node(int32 item) {
	Node *node = malloc(sizeof(Node));
	node->item = item;
	node->next_node = 0;

	return node;
}


static void
imp_append(List *list, int32 item) {
  Node **node = &(list->root_node);
	while (*node) {
		node = &((*node)->next_node);
	}
	*node = create_node(item);
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
	return 0;
}


static void
imp_remove(List *list, int32 index) {
	return;
}


static void
imp_insert(List *list, int32 index) {
	return; 
}


List create_list(void) {
	List list;
	list.root_node = (void*)0;
	list.append = imp_append;
	list.remove = imp_remove;
	list.insert = imp_insert;
	list.get = imp_get;

	return list;
}

