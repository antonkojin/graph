#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct bst_node{
  struct vertex *vertex; // puntatore al dato
  struct bst_node *left, *right; // puntatori ai figli
};

struct bst_node *bst_node_create(struct vertex *v);
struct vertex *bst_search(struct bst_node *bst, int id);
struct bst_node *bst_insert(struct bst_node *root, struct vertex *v);
void bst_destroy(struct bst_node *root);

#endif
