/* Anton Kozhin 830515 */
#ifndef FACEBOOK_H
#define FACEBOOK_H

void inserisci_utenti(struct graph *g);
void inserisci_utente(struct graph *g);
void cerca_utente(struct graph *g);
void inserisci_amicizia(struct graph *g);
void gruppi(struct graph *g, int year);
void clean(struct graph *g);

#endif
