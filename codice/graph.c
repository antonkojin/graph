#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "list.h"
#include "binary_search_tree.h"
#include "malloc_check.h"

struct graph* graph_new(){
  /*
    Crea e restituisce un grafo vuoto.
  */
  struct graph *g = (struct graph*)malloc_check( sizeof(struct graph) );
  g->nv = g->ne = 0;
  g->vertexes = NULL;
  g->bst = NULL;
  return g;
}

void graph_destroy(struct graph *g){
  /*
    Libera la memoria del grafo g. Chiama bst_destroy di binary_search_tree.c
  */
  //TODO
}

struct vertex* insert_vertex(struct graph* g, struct user* user){
  /*
    g: grafo in cui inserire l'utente.
    user: utente da inserire.
    Cerca utente, se non presente lo inserisce nel grafo e chiama bst_insert
    di binary_search_tree.c, se presente stampa errore.

  */
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
  }else printf("Inserimento fallito, l'identificativo è gia presente");
  // fprintf(stderr, "DEBUG: insert_vertex: end\n");
  return v;
}

void graph_insert_edge(struct graph *g, int id1, int id2, int value){
  /*
    Cerca gli utenti di id1 e id2, se trovati inserisci un arco tra i due di
    valore value, se non trovati stampa errore.
  */
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
  /*
    Trova e restituisce la lista delle componenti connesse sotto forma di
    liste di utenti. Considera solo gli archi di valore >= di year.
    Passare year = 0 per considerare tutti gli archi.
  */
  struct list_node* connected_components = NULL;
  struct vertex *v = g->vertexes;
  /* mark all users as not visited */
  while(v){
    v->visited = false;
    v = v->next;
  }
  /* search connected components */
  v = g->vertexes;
  while(v){  // for each v in V
    if( !v->visited ){
      connected_components = list_append( connected_components,
                                          depth_first_visit(NULL, v, year)
                                        );
    }
    v = v->next;
  }
  return connected_components;
}

struct list_node* depth_first_visit(struct list_node *users, struct vertex *v, int year){
  /*
    Visita in profondità il grafo a partire dal vertice v. Appende gli utenti
    connessi alla lista users, passare users = NULL nella chiamata iniziale.
    Restituisce la lista di utenti connessi.
  */
  struct edge *adj;
  /* visita il nodo iniziale */
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
  /*
    Stampa il grafo g su standard output nel formato
    user_id -> user_id_adjacent -> ... -> user_id_adjacent
  */
  struct vertex *v = g->vertexes;
  struct edge *edges;
  while(v){  // for each v in V
    printf("%d", v->user->id );
    edges = v->edge;
    while(edges){  // for each adjacent to v
      printf(" -> %d", edges->vertex->user->id);
      edges = edges->next;
    }
    printf("\n");
    v = v->next;
  }
}
