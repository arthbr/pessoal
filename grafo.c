#include <stdio.h>
#include <stdlib.h>

#define MAXPESSOAS 8

typedef struct node {
	int qntd;
	struct pessoa* prox;
} node;

typedef struct pessoa {
	int id;
	char rel;
	struct pessoa* prox;
} pessoa;

node lista[MAXPESSOAS+1];

void imprimeTudo(node *lista);
void imprimePessoa(node *lista, int id);
void inserirAresta(node *lista, int a, int b); 

int main(int argc, char *argv[]) {
	int i, a, b;

	FILE *arquivo;
	arquivo = fopen(argv[1],"r");
	if (!arquivo) {
		printf("Erro ao abrir o arquivo %s.\n", argv[1]);
		return 0;
	}

	/* Inicialização da lista. */
	for (i = 1; i <= MAXPESSOAS; i++){
		lista[i].qntd = 0;
		lista[i].prox = NULL;
	}

	/* Leitura dos vértices (a,b) - passagem para a função inserirAresta. */
	while (fscanf(arquivo,"%d %d", &a, &b) > 1) {
		if (!feof(arquivo)) {
			inserirAresta(lista, a, b);
			inserirAresta(lista, b, a);
		}
	}

	imprimeTudo (lista);

	imprimePessoa(lista, 2);
	imprimePessoa(lista, 3);
	
	return 0;
}


void imprimeTudo(node *lista) {
	int i;
	pessoa *tmp;

	for (i = 1; i <= MAXPESSOAS; i++) {
		tmp = lista[i].prox;
		printf("%2d: (%d) ==> ", i, lista[i].qntd);
		while (tmp != NULL) {
			printf("%d  ", tmp->id);
			tmp = tmp->prox;
		}
	printf("\n");
	}
}

void imprimePessoa(node *lista, int id) {
	pessoa *tmp;

	tmp = lista[id].prox;
	printf("%2d: (%d) ==> ", id, lista[id].id);
	while (tmp != NULL) {
		printf("%d  ", tmp->id);
		tmp = tmp->prox;
	}
	printf("\n");
}

void inserirAresta (node *lista, int a, int b) {
	pessoa *novo, *tmp, *ant;

	/* Retorno de um ponteiro genérico */
	novo = (pessoa*) malloc((int)sizeof(pessoa));
	novo->id = b;
	novo->prox = NULL;

	lista[a].qntd++;
	
	/* Caso a lista estiver vazia - Insere	*/
	if (lista[a].prox == NULL) {
		lista[a].prox = novo;

	/* Insere ordenadamente */
	} else {
		tmp = lista[a].prox;
		
		while (tmp != NULL && tmp->id < b) {
			ant = tmp;
			tmp = tmp->prox;
		}
		novo->prox = tmp;
		ant->prox = novo;
	}
}
