#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
	int id[T];
	
	for ( i=0; i<T; i++ ){
		id[i] = i;
		pthread_create(&tid[i],NULL, funcao, &id[i]);
	}

	for ( i=0; i<nthreads; i++){
		pthread_join(tid[i],NULL);
	}
}
/*-----------------------------------------------------*/

