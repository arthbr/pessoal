#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPESSOAS 200

typedef struct no {
	int qntd;
	char *nome;
} lista;

int **matriz;
lista list[MAXPESSOAS+1];

int inicializa();
int leArquivo();
void escreveArquivo(char nome1[], char nome2[]);
void atualizaLista (char nome1[], char nome2[]);
int pesquisaPessoa (char nome[]);
void inserePessoa(char nome[], int i);
void imprimeElemento(int x);
void imprimeMatriz();
void listaTodos();

int main(int argc, char *argv[]) {
	int indice;
	char opcao, nome1[25], nome2[25];

	if (inicializa() == 0) return 0;
	
	
	printf("----------------------------------\n");	
	printf ("Bem-vindo ao Grafo do IME!\n\n");
	
	while (1) {
		printf ("Escolha a opção desejada:\n");
		printf ("> Listar pessoas\t(0)\n");
		printf ("> Pesquisar alguém\t(1)\n");
		printf ("> Acrescentar relação\t(2)\n");
/*		printf ("3 - Acrescentar informações a uma aresta\n"); */
		printf("----------------------------------\n");
		scanf ("%c", &opcao);
		
		switch (opcao) {
			case 'l':
			case '0':
				printf ("Listar:\n");
				listaTodos();
				break;
			
			case 'p':
			case '1':
				printf ("Pesquisar: ");
				scanf ("%25s", nome1);
				indice = pesquisaPessoa(nome1);
				if (indice != -1) {
					imprimeElemento(indice);
				}
				else {
					printf("Elemento não encontrado!\n");
				}
				break;
			
			case 'a':
			case '2':
				printf ("Adicionar: ");
				scanf ("%25s %25s", nome1, nome2);
				atualizaLista(nome1, nome2);
				escreveArquivo(nome1, nome2);
				break;

			case '3':
				break;
			case 'q':
				return 0;
		
			default:
				break;
		}
	}

	return 0;
}

void listaTodos(){
	int i;
	
	for (i = 0; i < MAXPESSOAS; i++) {
		if (list[i].nome != NULL) {
			printf ("> %d:  %s\n", list[i].qntd, list[i].nome);
		}
		else {
			printf("------------------------\n");
			return;
		}
	}
}


int inicializa() {
	/* Inicialização da lista e da matriz. */
	int i, j;
	
	matriz = (int **) malloc(MAXPESSOAS * sizeof (int *));

	for (i = 0; i < MAXPESSOAS; i++){
		list[i].qntd = 0;
		list[i].nome = NULL;

		matriz[i] = (int *) malloc(MAXPESSOAS*sizeof(int));
		
		for (j = 0; j < MAXPESSOAS; j++) {
			matriz[i][j] = 0;
		}
	}
	
	return leArquivo();
}

void escreveArquivo(char nome1[], char nome2[]) {
	FILE *arquivo;
	char buffer[50];
	
	arquivo = fopen("entrada", "a");
	sprintf(buffer, "\n%s, %s", nome1, nome2);
	fputs(buffer, arquivo);
	
	fclose(arquivo);
}

int leArquivo(){
	FILE *arquivo;
	int i, j;
	char nome1[25], nome2[25], buffer[50];	
	
	
	arquivo = fopen("entrada","r");
	if (!arquivo) {
		printf("Erro ao abrir o arquivo de entrada.\n");
		return 0;
	}
	
	while (fgets(buffer, 50, arquivo)) {
		
		for (i = j = 0; i < strlen(buffer); i++) {
			switch (buffer[i]) {
				case ' ':
					break;
				case ',':
					nome2[j] = '\0';
					strcpy(nome1, nome2);
					j = 0;
					break;
				case '\n':
					nome2[j] = '\0';
					break;
				default:
					nome2[j++] = buffer[i];
					break;
			}
		}
		
		atualizaLista(nome1, nome2);
	}

	fclose(arquivo);
	return 1;
}

int pesquisaPessoa (char nome[]) {
	int i;
	
	for (i = 0; i < MAXPESSOAS; i++) {
		if (list[i].nome == NULL || strcmp(list[i].nome, nome) == 0) {
			return i;
		}
	}
	return -1;
}

void atualizaLista (char nome1[], char nome2[]) {
	int pos1, pos2;
	
	if (nome1 != NULL && nome2 != NULL) {

		pos1 = pesquisaPessoa(nome1);
		inserePessoa(nome1, pos1);
		
		pos2 = pesquisaPessoa(nome2);		
		inserePessoa(nome2, pos2);

		/* atualiza matriz */		
		matriz[pos1][pos2] = 1;
		matriz[pos2][pos1] = 1;
	}
}

void inserePessoa(char nome[], int i) {

		if (list[i].nome == NULL) {
			list[i].nome = malloc (strlen(nome) * sizeof (char));
			strcpy(list[i].nome, nome);
		}
		list[i].qntd++;
}

void imprimeElemento(int x) {
	int i;
	
	printf("%s (%d):\n", list[x].nome, list[x].qntd);
	
	for (i = 0; i < MAXPESSOAS; i++) {
		if (matriz[i][x] == 1) {
			printf ("\t> %s\n", list[i].nome);
		}
	}
	
	printf("----------------------\n");
}


void imprimeMatriz(){
	int i, j;
	
	for (i = 0; i < MAXPESSOAS; i++) {	
		printf ("%d --> %d / %s\n", i, list[i].qntd, list[i].nome);
	}
		
		
	for (i = 0; i < MAXPESSOAS; i++) {
		printf ("linha[%d]: ", i);
		for (j = 0; j < MAXPESSOAS; j++) {
			printf ("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}













