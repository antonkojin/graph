#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"
#include "graph.h"
#include "malloc_check.h"

struct vertex* bst_search(struct bst_node *bst, int id){
  int cmp;
  struct vertex *found = NULL;
  // fprintf(stderr, "DEBUG: bst_search: start\n");
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
  // fprintf(stderr, "DEBUG: bst_search: end\n");
  return found;
}

struct bst_node *bst_insert(struct bst_node *root, struct vertex *v){
  // fprintf(stderr, "DEBUG: bst_insert: start\n");
  if(!root){
    root = bst_node_create(v);
  }else if(v->user->id > root->vertex->user->id){
    if(root->right){
      bst_insert(root->right, v);
    }else{
      root->right = bst_node_create(v);
    }
  }else if(v->user->id < root->vertex->user->id){
    if(root->left){
      bst_insert(root->left, v);
    }else{
      root->left = bst_node_create(v);
    }
  }
  // fprintf(stderr, "DEBUG: bst_insert: end\n");
  return root;
}

struct bst_node *bst_node_create(struct vertex *v){
  struct bst_node *new_node;
  new_node = (struct bst_node*)malloc_check( sizeof(struct bst_node) );
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->vertex = v;
  return new_node;
}

void bst_destroy(struct bst_node *root){
  // fprintf(stderr, "DEGUB: bst_destroy: start\n");
  if(root){
    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
  }
  // fprintf(stderr, "DEGUB: bst_destroy: end\n");
}
