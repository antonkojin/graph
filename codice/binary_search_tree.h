#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct bst_node{
  struct vertex *vertex; // puntatore al dato
  struct bst_node *left, *right; // puntatori ai figli
};


struct vertex *bst_search(struct bst_node *bst, int id);
struct bst_node *bst_insert(struct bst_node *root, struct vertex *v);

#endif
