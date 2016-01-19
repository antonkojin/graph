#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "malloc_check.h"

struct list_node* list_append(struct list_node *list, void *item){
  struct list_node* new_node;
  if(item){
    new_node = (struct list_node*)malloc_check( sizeof(struct list_node) );
    if(!new_node){
      fprintf(stderr, "OUT OF MEMORY ERROR");
      exit(EXIT_FAILURE);
    }
    new_node->item = item;
    new_node->next = list;
  }else{
    new_node = list;
  }
  return new_node;
}

//TODO cancella
// struct list_node* list_merge(struct list_node* list1, struct list_node *list2){
//   struct list_node *node;
//   if(!list1){
//     list1 = list2;
//   }else{
//     node = list1;
//     while(node->next) node = node->next;
//     node->next = list2;
//   }
//   return list1;
// }
