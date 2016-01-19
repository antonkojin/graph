#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "graph.h"
#include "list.h"
#include "binary_search_tree.h"
#include "malloc_check.h"

struct graph* graph_new(){
  struct graph *g = (struct graph*)malloc_check( sizeof(struct graph) );
  g->nv = g->ne = 0;
  g->vertexes = NULL;
  g->bst = NULL;
  return g;
}

void graph_destroy();

struct vertex* insert_vertex(struct graph* g, struct user* user){
  // fprintf(stderr, "DEBUG: insert_vertex: start\n");
  struct vertex* v = NULL;
  if( !bst_search(g->bst, user->id) ){
    v = (struct vertex*)malloc_check( sizeof(struct vertex) );
    v->user = user;
    g->nv++;
    v->edge = NULL;
    v->next = g->vertexes;
    g->vertexes = v;
    g->bst = bst_insert(g->bst, v);
  }else printf("Utente già presente");
  // fprintf(stderr, "DEBUG: insert_vertex: end\n");
  return v;
}

void graph_insert_edge(struct graph *g, int id1, int id2, int value){
  struct vertex *v1, *v2;
  v1 = bst_search(g->bst, id1);
  v2 = bst_search(g->bst, id2);
  if(!v1 && !v2) printf("Utenti %d e %d non trovati\n", id1, id2);
  else if(!v1) printf("Utente %d non trovato", id1);
  else if(!v2) printf("Utente %d non trovato", id2);
  else{
    struct edge *edge_v1 = (struct edge*)malloc_check( sizeof(struct edge) );
    struct edge *edge_v2 = (struct edge*)malloc_check( sizeof(struct edge) );
    edge_v1->vertex = v2;
    edge_v1->value = edge_v2->value = value;
    edge_v1->next = v1->edge;
    v1->edge = edge_v1;
    edge_v2->vertex = v1;
    edge_v2->next = v2->edge;
    v2->edge = edge_v2;
    g->ne++;
  }
}

struct list_node* connected_components(struct graph *g, int year){
  struct list_node* connected_components = NULL;
  struct vertex *v = g->vertexes;
  /* nuke visited flag for all users */
  while(v){
    v->visited = false;
    v = v->next;
  }
  /* search connected components */
  v = g->vertexes;
  while(v){
    if( !v->visited ){
      connected_components = list_append( connected_components, depth_first_visit(NULL, v, year) );
    }
    v = v->next;
  }
  return connected_components;
}

struct list_node* depth_first_visit(struct list_node *users, struct vertex *v, int year){
  struct edge *adj;
  users = list_append(users, v->user);
  v->visited = true;
  adj = v->edge;
  while(adj){ // for each adjacent vertex to v
    if( !(adj->vertex->visited) && adj->value >= year ){
      users = depth_first_visit(users, adj->vertex, year);
    }
    adj = adj->next;
  }
  return users;
}

void graph_print(struct graph *g){
  struct vertex *v = g->vertexes;
  struct edge *edges;
  while(v){
    printf("%d", v->user->id );
    edges = v->edge;
    while(edges){
      printf(" -> %d", edges->vertex->user->id);
      edges = edges->next;
    }
    printf("\n");
    v = v->next;
  }
}
