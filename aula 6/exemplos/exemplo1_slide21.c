#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *funcao(void *args)
{
    printf("Hello World\n");
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, funcao, NULL);
}