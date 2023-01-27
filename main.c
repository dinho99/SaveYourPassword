#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct user
{
    int ID;
    char address[20];
    char password[16];
} User;

typedef struct Nodo
{
    User user;
    struct Nodo* next;
} Nodo;

int leggiNumeroSelezionato() {
    int numero = 0;
    printf("Digita il numero della password\n");
    printf("alla quale desideri accedere: ");
    scanf("%d%*c", &numero);
    return numero;
}

 /*Verifica se esiste l'account cercato tramite id e se esiste ritorna il nodo, se non esiste il nodo è null*/
Nodo* esistePassword(Nodo* head, int n) {
    if(head == NULL) return 0;
    Nodo* nodo = head;
    int esiste = 0;
    while(nodo != NULL || esiste) {
        if(nodo->user.ID == n) {
            esiste = 1;
        }
        else{
            nodo = nodo->next;
        }
    }
    if(esiste) return nodo;
    return 0;
}

void visualizzaPassword(User* u) {
    printf("password: %s\n", u->password);
}

void stampaPassword(Nodo* head, int n) {
    Nodo* accountTrovato = esistePassword(head, n); //salvo in account trovato il nodo che cercava
    if(accountTrovato != NULL) { //esiste un id corrispondete
        visualizzaPassword(&accountTrovato->user);
    }
    else {
        printf("Non ho trovato un ID corrispondente!\n");
    }
}

/*Si occupa di chiedere numero id da stampare e lo stampa*/
void chiediCosaVuoleFareEEsegui(Nodo* head) {
    if(head == NULL)
        return;
    else {
        int numeroSelezionato = 0;
        numeroSelezionato = leggiNumeroSelezionato();
        stampaPassword(head, numeroSelezionato);
    }    
}

void visualizzaLista(User* u) {
    printf("%d) Address: %s", u->ID ,u->address);
	printf("\n\n");
}

/*Stampa la lista di tutti gli account salavti*/
void stampaListaAccountSalvati(Nodo* head) {
    /* lista vuota */
	if(head==NULL)
		printf("Sembra che la tua lista sia vuota :-(\n\n");
	/* lista non vuota */
	else {
		printf("Ecco la lista*********\n\n");
		while(head!=NULL) {
			visualizzaLista(&(head->user));
			head = head->next;
		}
	}
}

int leggiNumeroDaModificare() {
    int numero = 0;
    printf("Digita il numero della password\n");
    printf("che vorresti modificare: ");
    scanf("%d%*c", &numero);
    return numero;
}

void modificaPassword(Nodo* n) {
    if(n == NULL)
        printf("Nessun account da modificare!\n");
    else {
        int numeroDaModificare = 0; 
        numeroDaModificare = leggiNumeroDaModificare();
        Nodo* accountTrovato = esistePassword(n, numeroDaModificare);
        if(accountTrovato != NULL) {
            printf("Inserisci la nuova password che desideri dell'account %d) : ", accountTrovato->user.ID);
            fgets(accountTrovato->user.password, 16, stdin);
            accountTrovato->user.password[strlen(accountTrovato->user.password)-1] = '\0';
        }
        else
            printf("Non ho trovato un account con quell' ID\n");
    }
}

/* inserimento dati computer */
void inserisciDati(Nodo* head, User* u) {
	/* leggi address */
	printf("Dammi il nome dell'accuount (max 20 cifre): ");
	fgets(u->address, 20, stdin);
	u->address[strlen(u->address)-1] = '\0';
	
	/* leggi password */
    printf("Dammi la password: ");
    fgets(u->password, 16, stdin);
    u->password[strlen(u->password)-1] = '\0';

	
	/* crea ID */
	int newID = 0;
	Nodo* index = head;
	while(index->next != NULL) {
	    newID += 1;
	    index = index->next;
	}
	u->ID = newID ++;
}
	
/* inserimento in coda */
Nodo* inserisciAccount(Nodo* head) {
	Nodo* nuovo = malloc(sizeof(Nodo));
	inserisciDati(head, &(nuovo->user));
	nuovo->next = NULL;
	
	/* lista vuota */
	if(head==NULL)
		head=nuovo;
	/* lista non vuota */
	else{
		Nodo* corrente = head;
		while(corrente->next!=NULL)
			corrente = corrente->next;
		corrente->next=nuovo;
	}
	printf("Inserimento effettuato!\n\n");
	return head;
}

int main()
{
    Nodo* head = NULL;
    int scelta = 1;

    while (scelta != 0) {
        printf("Cosa desideri fare?\n");
        printf("Premi 1 per: visualizzare password\n");
        printf("Premi 2 per: modificare password\n");
        printf("Premi 3 per: eliminare password\n");
        printf("Premi 4 per: inserire password\n");
        printf("Premi 0 per far finire il programma\n");
        scanf("%d%*c", &scelta);

        if(scelta == 1) {
            stampaListaAccountSalvati(head);
            chiediCosaVuoleFareEEsegui(head);
        }
        if(scelta == 2) {
            modificaPassword(head);
        }
        if(scelta == 4) {
            head = inserisciAccount(head);
        }
    }

}
