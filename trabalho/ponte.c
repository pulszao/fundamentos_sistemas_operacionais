#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define TAMANHO 50
#define CARROS_POR_MINUTO 60 // 30-60-90 veículos por minuto
#define TRUE 1
#define FALSE 0

pthread_mutex_t mutex;
pthread_mutex_t mutex2;

/*--------------------------------------------------------------------*/
struct carro {
    int id;
    int prioridade;
    int atravessou_ponte;
    pthread_t thread;
};
typedef struct carro CARRO;

/*--------------------------------------------------------------------*/
void *ponte(void *args) {
    CARRO *carro = (CARRO *)args;
    // exclusao mutua
    pthread_mutex_lock(&mutex);
    printf("PONTE 1\tCarro = %i\t Prioridade = %i\t Thread = %lu\n", carro->id, carro->prioridade, pthread_self());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *ponte2(void *args) {
    CARRO *carro2 = (CARRO *)args;
    // exclusao mutua
    pthread_mutex_lock(&mutex2);
    printf("PONTE 2\tCarro2 = %i\t Prioridade = %i\t Thread = %lu\n", carro2->id, carro2->prioridade, pthread_self());
    usleep(60000000 / CARROS_POR_MINUTO); // delay para limitar velocidade de carros que passam na ponte
    pthread_mutex_unlock(&mutex2);
    return NULL;
}
/*--------------------------------------------------------------------*/

int main(void) {
    // inicia gerador de numeros aleatorios
    srand(time(NULL));
    
    CARRO *carros = NULL;
    CARRO *carros2 = NULL;

    // alocação de memória para os parâmetros
    carros = (CARRO *)malloc(TAMANHO * sizeof(CARRO));
    carros2 = (CARRO *)malloc(TAMANHO * sizeof(CARRO));

    // inicia os mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);

    // criando carros com suas prioridades
    for (int i = 0; i < TAMANHO; i++) {
        carros[i].id = i + 1;
        carros[i].prioridade = (rand() % 5) + 1;
        carros[i].atravessou_ponte = FALSE;

        carros2[i].id = i + 1;
        carros2[i].prioridade = (rand() % 5) + 1;
        carros2[i].atravessou_ponte = FALSE;
    }
    
    // Executa a funcao de acordo com a prioridade
    int sinaleira = 0;
    for (int prio = 1; prio <= 5; prio++) {
        for (int i = 0; i < TAMANHO; i++) {
            if (carros[i].prioridade == prio) {
                carros[i].atravessou_ponte = TRUE;
                pthread_create(&carros[i].thread, NULL, ponte, (void *)&carros[i]);
            }
            if (carros2[i].prioridade == prio) {
                carros2[i].atravessou_ponte = TRUE;
                pthread_create(&carros2[i].thread, NULL, ponte2, (void *)&carros2[i]);
            }

            sinaleira =  (rand() % 100) + 1;
            if (sinaleira == 7) {
                // faz o join para garantir que todos os pontes acabaram antes de parar
                for (int i = 0; i < TAMANHO; i++) {
                    if (carros[i].atravessou_ponte == TRUE) {
                        pthread_join(carros[i].thread, NULL);
                    }
                    if (carros2[i].atravessou_ponte == TRUE) {
                        pthread_join(carros2[i].thread, NULL);
                    }
                }

                printf("\nSinaleira Fechada!\nCarros Aguardando Sinaleira:\n");
                printf("PONTE 1\n");
                for (int i = 0; i < TAMANHO; i++) {
                    if (carros[i].atravessou_ponte == FALSE) {
                        printf("\t*(Carro = %i - Prior = %i)\n", carros[i].id, carros[i].prioridade);
                    }
                }
                printf("PONTE 2\n");
                for (int i = 0; i < TAMANHO; i++) {
                    if (carros2[i].atravessou_ponte == FALSE) {
                        printf("\t*(Carro = %i - Prior = %i)\n", carros2[i].id, carros2[i].prioridade);
                    }
                }
                sleep(10);
                printf("\nSinaleira Aberta!\n");
            }
        }
    }

    // faz o join final para verificar que todos os pontes acabaram
    for (int i = 0; i < TAMANHO; i++) {
        if (carros[i].atravessou_ponte == TRUE) {
            pthread_join(carros[i].thread, NULL);
        }
        if (carros2[i].atravessou_ponte == TRUE) {
            pthread_join(carros2[i].thread, NULL);
        }
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);
    free(carros);
    free(carros2);

    return 0;
}
