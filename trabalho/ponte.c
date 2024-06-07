#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define TAMANHO 50
#define CARROS_POR_MINUTO 190 // 30-60-90 veículos por minuto
#define TRUE 1
#define FALSE 0

pthread_mutex_t mutex;

/*--------------------------------------------------------------------*/
struct carro {
    int id;
    int prioridade;
    int atravessou_ponte;
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
    
    CARRO *carros = NULL;

    // alocação de memória para os parâmetros
    carros = (CARRO *)malloc(TAMANHO * sizeof(CARRO));

    // inicia o mutex
    pthread_mutex_init(&mutex, NULL);

    // criando carros com suas prioridades
    for (int i = 0; i < TAMANHO; i++) {
        carros[i].id = i + 1;
        carros[i].prioridade = (rand() % 5) + 1;
        carros[i].atravessou_ponte = FALSE;
    }
    
    // Executa a funcao de acordo com a prioridade
    int sinaleira = 0;
    for (int prio = 1; prio <= 5; prio++) {
        for (int i = 0; i < TAMANHO; i++) {
            if (carros[i].prioridade == prio) {
                carros[i].atravessou_ponte = TRUE;
                pthread_create(&carros[i].thread, NULL, processo, (void *)&carros[i]);
            }

            sinaleira =  (rand() % 100) + 1;
            if (sinaleira == 7) {
                // faz o join para garatir que todos os processos acabaram antes de parar
                for (int i = 0; i < TAMANHO; i++) {
                    if (carros[i].atravessou_ponte == TRUE) {
                        pthread_join(carros[i].thread, NULL);
                    }
                }

                printf("\nSinaleira Fechada!\nCarros Aguardando Sinaleira:\n");
                for (int i = 0; i < TAMANHO; i++) {
                    if (carros[i].atravessou_ponte == FALSE) {
                        printf("\t*(Carro = %i - Prior = %i)\n", carros[i].id, carros[i].prioridade);
                    }
                }
                sleep(10);
                printf("\nSinaleira Aberta!\n");
            }
        }
    }

    // faz o join final para verifica que todos os processos acabaram
    for (int i = 0; i < TAMANHO; i++) {
        if (carros[i].atravessou_ponte == TRUE) {
            pthread_join(carros[i].thread, NULL);
        }
    }
    
    pthread_mutex_destroy(&mutex);
    free(carros);

    return 0;
}
