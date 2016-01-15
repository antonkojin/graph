#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "graph.h"
#include "list.h"
#include "binary_search_tree.h"

struct graph* graph_new(){
  struct graph *g = (struct graph*)malloc( sizeof(struct graph) );
  g->nv = g->ne = 0;
  g->vertexes = NULL;
  g->bst = NULL;
  return g;
}

void graph_destroy();

struct vertex* insert_vertex(struct graph* g, struct user* user){
  struct vertex* v = NULL;
  if( !bst_search(g->bst, user->id) ){
    v = (struct vertex*)malloc( sizeof(struct vertex) );
    if(!v){
      fprintf(stderr, "OUT OF MEMORY ERROR");
      exit(EXIT_FAILURE);
    }
    v->user = user;
    g->nv++;
    v->edge = NULL;
    g->vertexes = list_append(g->vertexes, v);
    bst_insert(&g->bst, v);
  }else{
    //TODO print error
  }
  return v;
}

void graph_insert_edge(struct graph *g, int id1, int id2, int value){
  struct vertex *v1, *v2;
  v1 = bst_search(g->bst, id1);
  v2 = bst_search(g->bst, id2);
  if(v1 && v2){
    struct edge *edge_v1 = (struct edge*)malloc( sizeof(struct edge) );
    struct edge *edge_v2 = (struct edge*)malloc( sizeof(struct edge) );
    if(!edge_v1 || !edge_v2){
      fprintf(stderr, "OUT OF MEMORY ERROR");
      exit(EXIT_FAILURE);
    }
    edge_v1->vertex = v2;
    edge_v1->value = edge_v2->value = value;
    edge_v1->next = v1->edge;
    v1->edge = edge_v1;
    edge_v2->vertex = v1;
    edge_v2->next = v2->edge;
    v2->edge = edge_v2;
    g->ne++;
  }else{
    //TODO print error
  }
}

struct list_node* depth_first_visit( struct vertex *v, int year){
  struct list_node *users = NULL;
  struct edge *adj;
  users = list_append(users, v->user);
  v->visited = 1;
  adj = v->edge;
  while(adj){ // for each adjacent vertex to v
    if( !(adj->vertex->visited) && adj->value >= year ){
      users = list_merge(users, depth_first_visit(adj->vertex, year));
    }
    adj = adj->next;
  }
  return users;
}

struct list_node* connected_components(struct graph *g, int year){
  struct list_node* connected_components = NULL;
  struct list_node *list_vertex = g->vertexes;
  /* nuke visited flag for all users */
  while(list_vertex){
    ( (struct vertex*)(list_vertex->item) )->visited = 0;
    list_vertex = list_vertex->next;
  }
  /* search connected components */
  list_vertex = g->vertexes;
  while(list_vertex){
    if( !( ( (struct vertex*)(list_vertex->item) )->visited ) ){
      connected_components = list_append(connected_components, depth_first_visit((struct vertex*)(list_vertex->item), year));
    }
    list_vertex = list_vertex->next;
  }
  return connected_components;
}

void graph_print(struct graph *g){
  struct list_node *list_vertexes = g->vertexes;
  struct edge *edges;
  while(list_vertexes){
    printf("%d", ( (struct vertex*)(list_vertexes->item) )->user->id );
    edges = ( (struct vertex*)(list_vertexes->item) )->edge;
    while(edges){
      printf(" -> %d", edges->vertex->user->id);
      edges = edges->next;
    }
    printf("\n");
    list_vertexes = list_vertexes->next;
  }
}
