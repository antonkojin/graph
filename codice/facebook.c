#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "facebook.h"
#include "graph.h"
#include "user.h"
#include "binary_search_tree.h"

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
  input n: numero utenti da inserire
  inserisce n utenti chiedendo nome, cognime, id di ciascuno
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
  input nome, cognime, id.
  se presente stampa "Inserimento fallito, l'identificativo è gia presente"
  altrimenti inseriscilo
  */
  int id;
  char *nome, *cognome, string_buffer[STRING_BUFFER_MAX] = {0};
  struct user *u;
  printf("nome: ");
  scanf(" %s", string_buffer);
  nome = (char*)calloc( strlen(string_buffer) + 1, sizeof(char) );
  if(!nome){ //TODO my_calloc & my_malloc
    fprintf(stderr, "OUT OF MEMORY ERROR");
    exit(EXIT_FAILURE);
  }
  strcpy(nome, string_buffer);
  printf("cognome: ");
  scanf(" %s", string_buffer);
  cognome = (char*)calloc( strlen(string_buffer) + 1, sizeof(char) );
  if(!cognome){
    fprintf(stderr, "OUT OF MEMORY ERROR");
    exit(EXIT_FAILURE);
  }
  strcpy(cognome, string_buffer);
  printf("id: ");
  scanf(" %d", &id);
  u = (struct user*)malloc(sizeof(struct user));
  if(!u){
    fprintf(stderr, "OUT OF MEMORY ERROR");
    exit(EXIT_FAILURE);
  }
  u->nome = nome;
  u->cognome = cognome;
  u->id = id;
  insert_vertex(g, u);
}

void cerca_utente(struct graph *g){
  /*
  input id
  se presente stampa nome, cognome, identificativo
  altriment stampa "Utente non trovato"
  */
  struct user *u;
  int id;
  printf("id: ");
  scanf("%d", &id);
  u = bst_search(g->bst, id)->user;
  if(u){
    //TODO magari stampare sempre una riga vuota prima di ogni output
    printf("%s %s %d\n", u->nome, u->cognome, u->id);
  }else{
    printf("Utente non trovato");
  }
}

void inserisci_amicizia(struct graph *g){
  /*
  input identificativi di due utenti e anno creazione amicizia
  se presenti inserisci amicizia tra i due
  altrimenti stampa "Utente X non presente" oppure "Utenti X, Y non presenti"
  */
  int id1, id2, anno;
  printf("id utente: ");
  scanf("%d", &id1);
  printf("id altro utente: ");
  scanf("%d", &id2);
  if(id1 == id2){
    printf("E' lo stesso utente");
    return;
  }
  scanf("%d", &anno);
  graph_insert_edge(g, id1, id2, anno);
}

void gruppi(struct graph *g, int year){
  /*
  stampa gruppi di utenti nel seguente formato
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
