#ifndef LIST_H
#define LIST_H

struct list_node{
  void *item;
  struct list_node *next;
};

struct list_node* list_append(struct list_node* list, void* item);

#endif
