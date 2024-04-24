#include <pthread.h>
#define NESCRITORES 1
#define NLEITORES 3

pthread_mutex_t mutex;
pthread_mutex_t database;
int nleitores=0;

void *esc (void *args){
    int id = (int)args;
    while(1){
        pthread_mutex_lock(&database);
        printf("Escritor %i Acessando a base\n",id);
        sleep(rand()%10);
        printf("Escritor %i Saindo da base\n",id);
        pthread_mutex_unlock(&database);
        sleep(rand()%10);
    }
}

void *leit (void *args){
int id = (int) args;
    while(1){
        pthread_mutex_lock(&mutex);
        nleitores++;
        if (nleitores==1)
            pthread_mutex_lock(&database);

        pthread_mutex_unlock(&mutex);
        printf("Leitor %i Acessando a base\n",id);
        sleep(rand()%10);
        printf("Leitor %i Saindo da base\n",id);
        pthread_mutex_lock(&mutex);
        nleitores--;

        if (nleitores==0)
            pthread_mutex_unlock(&database);

        pthread_mutex_unlock(&mutex);
        sleep(rand()%10);
    }
}

int main() {
    int i;
    pthread_t leitores[NLEITORES], escritores[NLEITORES];

    srand(time(NULL));
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&database,NULL);

    for ( i =0 ;i < NESCRITORES; i++)
        pthread_create( &escritores[i], NULL, esc, (void *)i);
    for ( i =0 ;i < NLEITORES; i++)
        pthread_create(&leitores[i],NULL,leit,(void *)i);

    for ( i =0 ;i < NESCRITORES; i++)
        pthread_join(escritores[i],NULL);
    for ( i =0 ;i < NLEITORES; i++)
        pthread_join(leitores[i],NULL);
}