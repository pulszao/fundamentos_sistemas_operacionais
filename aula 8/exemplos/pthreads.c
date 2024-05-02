#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*-----------------------------------------------------*/
#define T 10

/*-----------------------------------------------------*/
void * funcao(void * args){
	int tid = *(int *)args;
	printf("Alo mundo - Pthreads %d\n", tid);  
	sleep(5);
}

/*-----------------------------------------------------*/
int main(int argc, char **argv){

	pthread_t tid[T];
	int i, id[T];
	
	for ( i=0; i<T; i++ ){
		id[i] = i;
		pthread_create(&tid[i],NULL, funcao, &id[i]);
	}

	for ( i=0; i<T; i++){
		pthread_join(tid[i],NULL);
	}
	printf("Terminando o programa\n");
}
/*-----------------------------------------------------*/

