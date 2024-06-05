#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define TAMANHO 50
#define CARROS_POR_MINUTO 30 // 30-60-90 veículos por minuto

pthread_mutex_t mutex;

/*--------------------------------------------------------------------*/
struct carro {
    int id;
    int prioridade;
    pthread_t thread;
};
typedef struct carro CARRO;

/*--------------------------------------------------------------------*/
void *processo(void *args) {
    CARRO *carro = (CARRO *)args;
    // exclusao mutua
    pthread_mutex_lock(&mutex);
    printf("Carro = %i\t Prioridade = %i\t Thread = %lu\n", carro->id, carro->prioridade, pthread_self());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
    pthread_mutex_unlock(&mutex);
    return NULL;
}
/*--------------------------------------------------------------------*/

int main(void) {
    // inicia gerador de numeros aleatorios
    srand(time(NULL));


	// variáveis locais
	pthread_t idA, idB, idC, idD, idE, idF;
    
	// variáveis locais
	pthread_t idA, idB, idC, idD, idE, idF;
    CARRO *carros = NULL;

    // alocação de memória para os parâmetros
    carros = (CARRO *)malloc(TAMANHO * sizeof(CARRO));

    // inicia o mutex
    pthread_mutex_init(&mutex, NULL);

    // criando carros com suas prioridades
    for (int i = 0; i < TAMANHO; i++) {
        carros[i].id = i + 1;
        carros[i].prioridade = (rand() % 5) + 1;
    }
    
    // Executa a funcao de acordo com a prioridade
    for (int prio = 1; prio <= 5; prio++) {
        for (int i = 0; i < TAMANHO; i++) {
            if (carros[i].prioridade == prio) {
                pthread_create(&carros[i].thread, NULL, processo, (void *)&carros[i]);
            }
        }
        // faz o join para verifica que todas as threads de um mesmo nivel finalizaram antes de passar para o proximo
        for (int i = 0; i < TAMANHO; i++) {
            if (carros[i].prioridade == prio) {
                pthread_join(carros[i].thread, NULL);
            }
        }
    }

    // destroi o mutex
    pthread_mutex_destroy(&mutex);

    // libera memoria
    free(carros);

    return 0;
}
