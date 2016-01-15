#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

struct graph{
  int nv, ne; // numero vertici e numero nodi
  struct list_node *vertexes; // lista di vertici
  struct bst_node *bst;
};

struct vertex{
  int visited; //TODO maybe a Bool type?
  struct user *user; // puntatore al dato
  struct edge *edge; // lista di adiacenza
};

struct edge{
  int value; // label arco
  struct vertex *vertex; // puntatore al nodo adiacente
  struct edge *next; // prossimo arco
};

struct graph* graph_new();
void graph_destroy();
struct vertex* insert_vertex(struct graph *g, struct user *user);
void graph_insert_edge(struct graph *g, int id1, int id2, int value);
struct list_node* depth_first_visit( struct vertex *v, int year);
struct list_node* connected_components(struct graph *g, int year);
void graph_print(struct graph *g);

#endif
