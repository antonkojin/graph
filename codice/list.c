#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "malloc_check.h"

struct list_node* list_append(struct list_node *list, void *item){
  /*
    Data una lista e un elemento da inserire nella lista,
    inserisce l'elemento in testa alla lista,
    restituisce il nuvo puntatore all lista.
  */
  struct list_node* new_node;
  if(item){
    new_node = (struct list_node*)malloc_check( sizeof(struct list_node) );
    new_node->item = item;
    new_node->next = list;
  }else{
    new_node = list;
  }
  return new_node;
}
