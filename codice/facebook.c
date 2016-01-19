#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "facebook.h"
#include "binary_search_tree.h"
#include "list.h"
#include "malloc_check.h"

#define STRING_BUFFER_MAX 21
#define menu \
"1 - inserire un nuovo utente facebook\n"\
"2 - cercare un utente facebook\n"\
"3 - inserire una nuova relazione di amicizia\n"\
"4 - determinare i gruppi di amici\n"\
"5 - determinare i gruppi di amici nati dall'anno X\n"\
"6 - stampa grafo\n"\
"9 - esci\n"\
"inserisci il numero dell'operazione: "

int main(void){
  /*
    Processa l'inserimento iniziale di n utenti, n letto in input.
    Stampa il menù e esegue la funzione desiderata.
  */
  struct graph *users = graph_new();
  int op;
  inserisci_utenti(users);
  while(1){
    printf("%s", menu);
    scanf("%d", &op);
    switch (op) {
      case 1: inserisci_utente(users); break;
      case 2: cerca_utente(users); break;
      case 3: inserisci_amicizia(users); break;
      case 4: gruppi(users, 0); break;
      case 5: {int year; scanf("%d", &year); gruppi(users, year);} break;
      case 6: graph_print(users); break;
      case 9: clean(users); return 0;
    }
  }
}

void inserisci_utenti(struct graph *g){
  /*
  Legge in input n, numero utenti che si vuole inserire.
  Inserisce n utenti chiedendo nome, cognome, id di ciascuno
  */
  int n, i;
  printf("numero utenti: ");
  scanf("%d", &n);
  for(i=0; i<n; i++){
    inserisci_utente(g);
  }
}

void inserisci_utente(struct graph *g){
  /*
    Legge in input nome, cognime, id e chiama insert_vertex in graph.c.
  */
  int id;
  char *nome, *cognome, string_buffer[STRING_BUFFER_MAX] = {0};
  struct user *u;
  // fprintf(stderr, "DEBUG: inserisci_utente: start\n");
  printf("nome: ");
  scanf(" %s", string_buffer);
  nome = (char*)calloc_check( strlen(string_buffer) + 1, sizeof(char) );
  strcpy(nome, string_buffer);
  printf("cognome: ");
  scanf(" %s", string_buffer);
  cognome = (char*)calloc_check( strlen(string_buffer) + 1, sizeof(char) );
  strcpy(cognome, string_buffer);
  printf("id: ");
  scanf(" %d", &id);
  u = (struct user*)malloc_check(sizeof(struct user));
  u->nome = nome;
  u->cognome = cognome;
  u->id = id;
  insert_vertex(g, u);
  // fprintf(stderr, "DEBUG: inserisci_utente: end\n");
}

void cerca_utente(struct graph *g){
  /*
  Legge in input id, chiama bst_search di graph.c.
  Se trova utente stampa nome, cognome, identificativo
  altriment stampa "Utente non trovato"
  */
  struct user *u;
  int id;
  // fprintf(stderr, "DEBUG: cerca_utente: start\n");
  printf("id: ");
  scanf("%d", &id);
  u = bst_search(g->bst, id)->user;
  if(u){
    printf("%s %s %d\n", u->nome, u->cognome, u->id);
  }else{
    printf("Utente non trovato");
  }
  // fprintf(stderr, "DEBUG: cerca_utente: end\n");
}

void inserisci_amicizia(struct graph *g){
  /*
  Input identificativi di due utenti e anno creazione amicizia.
  chiama graph_insert_edge di graph.c
  */
  int id1, id2, anno;
  // fprintf(stderr, "DEBUG: inserisci_amicizia: start\n");
  printf("id utente: ");
  scanf("%d", &id1);
  printf("id altro utente: ");
  scanf("%d", &id2);
  if(id1 == id2){
    printf("E' lo stesso utente");
    return;
  }
  printf("anno: ");
  scanf("%d", &anno);
  graph_insert_edge(g, id1, id2, anno);
  // fprintf(stderr, "DEBUG: inserisci_amicizia: end\n");
}

void gruppi(struct graph *g, int year){
  /*
  Stampa i gruppi di amici nel seguente formato
  gruppo_i
  nome_k cognome_k id_k
  */
  struct list_node *lista_gruppi, *lista_utenti;
  struct user *amico;
  int i = 0;
  printf("Gruppi di amici\n");
  lista_gruppi = connected_components(g, year);
  while(lista_gruppi){
    lista_utenti = (struct list_node*)lista_gruppi->item;
    printf("gruppo %d\n", i);
    while(lista_utenti){
      amico = (struct user*)(lista_utenti->item);
      printf("%s\t%s\t%d\n", amico->nome, amico->cognome, amico->id);
      lista_utenti = lista_utenti->next;
    }
    i++;
    lista_gruppi = lista_gruppi->next;
  }
}

void clean(struct graph *g){

}
