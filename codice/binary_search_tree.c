#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"
#include "user.h"
#include "graph.h"

struct vertex* bst_search(struct bst_node *bst, int id){
  int cmp;
  struct vertex *found = NULL;
  if(bst){
    cmp = bst->vertex->user->id - id;
    if(cmp == 0){
      found = bst->vertex;
    }else if(cmp < 0){
      found = bst_search(bst->left, id);
    }else{
      found = bst_search(bst->right, id);
    }
  }
  return found;
}

void bst_insert(struct bst_node **bst_ptr, struct vertex *v){
  int cmp;
  struct bst_node *new_node;
  if(! *bst_ptr){
    new_node = (struct bst_node*)malloc( sizeof(struct bst_node) );
    if(!new_node){
      fprintf(stderr, "OUT OF MEMORY ERROR");
      exit(EXIT_FAILURE);
    }
    new_node->vertex = v;
    new_node->left = NULL;
    new_node->right = NULL;
    *bst_ptr = new_node;
  }else{
    cmp = (*bst_ptr)->vertex->user->id - v->user->id;
    if(cmp < 0){
      bst_insert(&(*bst_ptr)->left, v);
    }else if(cmp > 0){
      bst_insert(&(*bst_ptr)->right, v);
    }
  }
}
