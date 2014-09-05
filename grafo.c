#include <stdio.h>
#include <stdlib.h>

#define MAXPESSOAS 8

typedef struct pessoa{
	int id;
	struct pessoa* prox;
} pessoa;

pessoa lista[MAXPESSOAS+1];

void Imprimir(pessoa *lista);
void Inserir_Aresta(pessoa *lista, int a, int b); 

int main(int argc, char *argv[]){
  int i, a, b;
  
  FILE *arquivo;
  arquivo = fopen(argv[1],"r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo %s.\n", argv[1]);
    return 0;
  }
  
  // Inicialização da lista. 
  for (i = 1; i <= MAXPESSOAS; i++){
    lista[i].id = 0;
    lista[i].prox = NULL;
  }
        
  //leitura dos vertices (a,b) - passagem para a função Inserir_Aresta.
  fscanf(arquivo,"%d %d", &a, &b);
  while (!feof(arquivo)) {
    Inserir_Aresta(lista, a, b);
    Inserir_Aresta(lista, b, a);
    fscanf(arquivo,"%d %d", &a, &b);
  }

  Imprimir (lista);
}


void Imprimir(pessoa *lista){
  int i;
  pessoa *tmp;
  for (i = 1; i <= MAXPESSOAS; i++) {
    tmp = lista[i].prox;
    printf("%2d: (%d) ==> ", i, lista[i].id);
    while (tmp != NULL) {
      printf("%d  ", tmp->id);
      tmp = tmp->prox;
    }
    printf("\n");
  }
}

void Inserir_Aresta (pessoa *lista, int a, int b) {
  pessoa *aux;
  pessoa *tmp;
 
  aux = (pessoa*) malloc((int)sizeof(pessoa));    //retorno de um ponteiro genérico.
  aux->id = b;
  aux->prox = NULL;
  
  lista[a].id++;
  if (lista[a].prox == NULL) // Caso a lista estiver vazia - Insere.	
    lista[a].prox = aux;
  else	{
    tmp = lista[a].prox;
    if (tmp->id > b) { //insere como primeiro da lista
      aux->prox = tmp;
      lista[a].prox = aux;
    } 		          //insere os vértices ordenados
    else if (tmp->prox == NULL) { 
      aux->prox = tmp->prox;
      tmp->prox = aux;  
    }
    else {
      while ((tmp->prox != NULL) &&(tmp->prox->id < b))
	tmp = tmp->prox;
      aux->prox = tmp->prox;
      tmp->prox = aux;  
    }
  }
  
  free(aux);
  free(tmp);
}
