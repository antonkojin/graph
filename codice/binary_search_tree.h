#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct bst_node{
  struct vertex *vertex;
  struct bst_node *left, *right;
};


struct vertex* bst_search(struct bst_node *bst, int id);
void bst_insert(struct bst_node **bst, struct vertex *v);

#endif
