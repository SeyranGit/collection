#ifndef LIST_H
#define LIST_H

#define int32 __int32


typedef struct node {
	int32 item;
	struct node *next_node;
} Node;


typedef struct list {
	Node *root_node;
	void (*append)(struct list *list, int32 item);
	void (*remove)(struct list *list, int32 index);
	void (*insert)(struct list *list, int32 index);
	int32 (*get)(struct list *list, int32 index);
} List;


List create_list(void);

#endif
