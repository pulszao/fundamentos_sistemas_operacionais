#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define TAMANHO 50

pthread_mutex_t mutex;

/*--------------------------------------------------------------------*/
struct carro {
	int id;
    int prioridade;
};
typedef struct carro CARRO;

/*--------------------------------------------------------------------*/
void *processo(void *args) {
	CARRO *carros = (CARRO *)args;
    // exclusao mutua
    pthread_mutex_lock(&mutex);
	printf("Processo = %i\n", carros->id);
    pthread_mutex_unlock(&mutex);
}
/*--------------------------------------------------------------------*/


int main(void) {
    // inicia gerador de numeros aleatorios
    srand(time(NULL));

	// variáveis locais
	pthread_t idA, idB, idC, idD, idE, idF;
	CARRO *carros = NULL;

	// alocação de memória para os parâmetros
	carros = (CARRO *)malloc(TAMANHO * sizeof(CARRO));

    // criando carros com suas prioridades
    for(int i=0; i<TAMANHO; i++) {
        carros[i].id = i + 1;
        carros[i].prioridade = (rand() % 5) + 1;
        // printf("CARRO: %i - PRIORIDADE: %i\n", carros[i].id, carros[i].prioridade);
    }

    // TODO: Algoritmo de verificacao de prioridades e execucao da funcao + 'kill' da thread

    // libera memoria
    free(carros);

    return 0;
}
