#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"
#include "user.h"
#include "graph.h"
#include "malloc_check.h"

struct vertex* bst_search(struct bst_node *bst, int id){
  int cmp;
  struct vertex *found = NULL;
  fprintf(stderr, "DEBUG: bst_search: start\n");
  if(bst){
    cmp = bst->vertex->user->id - id;
    if(cmp == 0){
      found = bst->vertex;
    }else if(cmp > 0){
      found = bst_search(bst->left, id);
    }else{
      found = bst_search(bst->right, id);
    }
  }
  fprintf(stderr, "DEBUG: bst_search: end\n");
  return found;
}

struct bst_node *bst_insert(struct bst_node *root, struct vertex *v){
  //TODO maybe create_node function
  fprintf(stderr, "DEBUG: bst_insert: start\n");
  struct bst_node *new_node;
  if(!root){
    new_node = (struct bst_node*)malloc_check( sizeof(struct bst_node) );
    new_node->vertex = v;
    new_node->left = NULL;
    new_node->right = NULL;
    root = new_node;
  }else if(v->user->id > root->vertex->user->id){
    if(root->right){
      bst_insert(root->right, v);
    }else{
      new_node = (struct bst_node*)malloc_check( sizeof(struct bst_node) );
      new_node->vertex = v;
      new_node->left = NULL;
      new_node->right = NULL;
      root->right = new_node;
    }
  }else if(v->user->id < root->vertex->user->id){
    if(root->left){
      bst_insert(root->left, v);
    }else{
      new_node = (struct bst_node*)malloc_check( sizeof(struct bst_node) );
      new_node->vertex = v;
      new_node->left = NULL;
      new_node->right = NULL;
      root->left = new_node;
    }
  }
  fprintf(stderr, "DEBUG: bst_insert: end\n");
  return root;
}
