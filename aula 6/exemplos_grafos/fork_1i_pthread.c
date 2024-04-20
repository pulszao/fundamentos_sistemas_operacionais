#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // malloc
#include <pthread.h>

#define TAMANHO 6
/*--------------------------------------------------------------------*/
struct parametros{
	char letra;
};
typedef struct parametros PARAMETROS;

/*--------------------------------------------------------------------*/
void *processo(void *args){
	PARAMETROS *par = (PARAMETROS *)args;
	printf("Processo = %c\n", par->letra);
}
/*--------------------------------------------------------------------*/


void main(){
	// variáveis locais
	pthread_t idA, idB, idC, idD, idE, idF;
	PARAMETROS *par = NULL;

	// alocação de memória para os parâmetros
	par = (PARAMETROS *)malloc(TAMANHO * sizeof(PARAMETROS));

	// executa 1 e aguarda finalizar
	par[0].letra = '1';
	pthread_create(&idA,NULL,processo, (void *) &par[0]);
	pthread_join(idA,NULL);

	// executa B e C e aguarda finalizar
	par[1].letra = '2';
	par[2].letra = '3';
	par[3].letra = '4';
	pthread_create(&idB,NULL,processo,(void *) &par[1]);
	pthread_create(&idC,NULL,processo,(void *) &par[2]);
	pthread_create(&idD,NULL,processo,(void *) &par[3]);
	pthread_join(idB,NULL);
	pthread_join(idC,NULL);

	// executa D e E e aguarda finalizar
	par[4].letra = '5';
	pthread_create(&idE,NULL,processo,(void *) &par[4]);
	pthread_join(idD,NULL);
	pthread_join(idE,NULL);

	// executa F e aguarda finalizar
	par[5].letra = '6';
	pthread_create(&idF,NULL, processo,(void *) &par[5]);
	pthread_join(idF,NULL);
}









