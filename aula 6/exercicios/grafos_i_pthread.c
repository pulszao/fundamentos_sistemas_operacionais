#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *processoS1(){
	printf("S1\n");
}

void *processoS2(){
	printf("S2\n");
}

void *processoS3(){
	printf("S3\n");
}

void *processoS4(){
	printf("S4\n");
}

void *processoS5(){
	printf("S5\n");
}

void *processoS6(){
	printf("S6\n");
}


void main(){
	pthread_t idS1, idS2, idS3, idS4, idS5, idS6;

	// executa S1 e aguarda finalizar
	pthread_create(&idS1,NULL,processoS1,NULL);
	pthread_join(idS1,NULL);

	// executa S2, S3, S4 e aguarda finalizar
	pthread_create(&idS2,NULL,processoS2,NULL);
	pthread_create(&idS3,NULL,processoS3,NULL);
	pthread_create(&idS4,NULL,processoS3,NULL);
	pthread_join(idS2,NULL);
	pthread_join(idS3,NULL);
	pthread_join(idS4,NULL);

	// executa S5 e aguarda finalizar
	pthread_create(&idS5,NULL,processoS5,NULL);
	pthread_join(idS5,NULL);

	// executa S6 e aguarda finalizar
	pthread_create(&idS6,NULL,processoS6,NULL);
	pthread_join(idS6,NULL);
}

