#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *processoA(){
	printf("A\n");
}

void *processoB(){
	printf("B\n");
}

void *processoC(){
	printf("C\n");
}

void *processoD(){
	printf("D\n");
}

void *processoE(){
	printf("E\n");
}

void *processoF(){
	printf("F\n");
}

void *processoG(){
	printf("G\n");
}

void *processoH(){
	printf("H\n");
}


void main(){
	pthread_t idA, idB, idC, idD, idE, idF, idG, idH;

	// executa A, B e C e aguarda finalizar
	pthread_create(&idA,NULL,processoA,NULL);
	pthread_create(&idB,NULL,processoB,NULL);
	pthread_create(&idC,NULL,processoC,NULL);
	pthread_join(idA,NULL);
	pthread_join(idB,NULL);
	pthread_join(idC,NULL);

	// executa D e E e aguarda finalizar
	pthread_create(&idD,NULL,processoD,NULL);
	pthread_create(&idE,NULL,processoE,NULL);
	pthread_join(idD,NULL);
	pthread_join(idE,NULL);

	// executa F e aguarda finalizar
	pthread_create(&idF,NULL, processoF,NULL);
	pthread_join(idF,NULL);

	// executa G e H e aguarda finalizar
	pthread_create(&idG,NULL,processoG,NULL);
	pthread_create(&idH,NULL,processoH,NULL);
	pthread_join(idG,NULL);
	pthread_join(idH,NULL);
}

