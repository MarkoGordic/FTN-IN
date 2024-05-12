#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXK 100				// maksimalno karaktera u kljucu
#define MAXL 128*MAXK			// maksimalan broj razlicitih vrednosti hash funkcije

typedef struct {
	char key[MAXK];
	int data;
} ELEMENT;

typedef struct node {
	ELEMENT info;
	struct node *next;
} NODE;

int hash(char[]);
NODE* makeNode(ELEMENT);
void insertNode(NODE**, NODE*);
void deleteNode(NODE**, char[]);
int findNode(NODE*, char[]);

void insert(NODE**, ELEMENT);
ELEMENT delete(NODE*[], char[]);
int findKey(NODE**, char[]);
void printTable(NODE**);
void freeTable(NODE**);

int main() {
	NODE** table;						// tabela je niz listi, svi elementi sa istim hashom istu u istu listu
	
	table = calloc(MAXL, sizeof(NODE*));
	
	ELEMENT e1 = {"ab", 1}, e2 = {"aa", 2}, e3 = {"ba", 3}, 
			e4 = {"abc", 1}, e5 = {"b3a", 34}, e6 = {"cw3", 9}, e7 = {"1wer", 67};
	
	insert(table, e1);
	insert(table, e2);
	insert(table, e3);
	insert(table, e4);
	insert(table, e5);
	insert(table, e6);
	insert(table, e7);
	
	printTable(table);
	
	printf("\nkey: %s, value: %d\n", "ba", findKey(table, "ba"));
	printf("\nkey: %s, value: %d\n", "ax", findKey(table, "cw3"));

	freeTable(table);
	
	return 0;
}

int hash(char s[]) {
    unsigned int hash_value = 0;
    int c;
    while ((c = *s++)) { // Simple hash function
        hash_value = c + (hash_value << 6) + (hash_value << 16) - hash_value;
    }
    return hash_value % MAXL;
}

NODE* makeNode(ELEMENT e) {
	NODE* n = malloc(sizeof(NODE));
	
	n->info = e;
	n->next = NULL;

    return n;
}

// Dodajemo novi cvor kao glavu liste
void insertNode(NODE** pglava, NODE* node) {
    node->next = *pglava;
    *pglava = node;
}

// Funkcija se koristi za direktno uklanjanje cvora iz spregnute liste na osnovu zadatog
void deleteNode(NODE** pglava, char key[]) {
    NODE* trenutni = *pglava;
    NODE* prethodni = NULL;
    while (trenutni != NULL && strcmp(trenutni->info.key, key) != 0) {
        prethodni = trenutni;
        trenutni = trenutni->next;
    }

    if (trenutni == NULL) {
        return;
    }

    if (prethodni == NULL) {
        *pglava = trenutni->next;
    } else {
        prethodni->next = trenutni->next;
    }
    
    free(trenutni);
}

int findNode(NODE *head, char key[]) {
    while (head != NULL) {
        if (strcmp(head->info.key, key) == 0) {
            return head->info.data;  // Ukoliko smo pronasli cvor, vracamo vrednost
        }
        head = head->next;
    }
    return -1;  // Ukoliko nismo pronasli cvor, vracamo -1
}



// Vraca cvor za zadati kljuc
int findKey(NODE** table, char key[]) {
    int index = hash(key);
    return findNode(table[index], key);
}

// Funkcija viseg nivoa, koja se pozivan a celu HASH tabelu, ona pronalazi listu i pomocu deleteNode brise odgovarajuci cvor
ELEMENT delete(NODE* table[], char key[]) {
    int index = hash(key);
    NODE** phead = &table[index];

    NODE* trenutni = *phead;
    ELEMENT obrisaniElement = { "", -1 };  // Vrednost koju vraćamo ako ne pronađemo element za brisanje

    // Pretražujemo listu da pronađemo element pre brisanja
    while (trenutni != NULL && strcmp(trenutni->info.key, key) != 0) {
        trenutni = trenutni->next;
    }

    // Ako je element pronađen, sačuvamo njegove informacije
    if (trenutni != NULL) {
        obrisaniElement = trenutni->info;
    }

    deleteNode(phead, key);

    return obrisaniElement; 
}

void insert(NODE** table, ELEMENT e) {
    int index = hash(e.key);

    NODE* node = makeNode(e);
    insertNode(&table[index], node);
}


// ISPISI I BRISANJA CELIH STRUKTURA

void printList(NODE *node) {
    while (node != NULL) {
        printf("Kljuc: %s, Podatak: %d\n", node->info.key, node->info.data);
        node = node->next;
    }
}

void printTable(NODE** table) {
	int i=0;
	
	for (i=0; i<MAXL; i++) {
		if (table[i]) {
			printf("\nindex: %d\n", i);
			printList(table[i]);
		}
	}
}

void freeList(NODE *head) {
	NODE *tmp;
	while (head) {
		tmp = head;
		head = tmp->next;
		free(tmp);
	}
}

void freeTable(NODE** table) {
	int i=0;
	
	for (i=0; i<MAXL; i++) {
		freeList(table[i]);
		table[i] = NULL;
	}
}
