#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // malloc
#include <pthread.h>

#define TAMANHO 4

/*--------------------------------------------------------------------*/
struct parametros{
	double nota;
};
typedef struct parametros PARAMETROS;

/*--------------------------------------------------------------------*/
void *peso_2(void *args){
	PARAMETROS *par = (PARAMETROS *)args;
    par->nota = 2/(par->nota);
	printf("Processo = %f\n", par->nota);
}

/*--------------------------------------------------------------------*/
void *peso_1(void *args){
	PARAMETROS *par = (PARAMETROS *)args;
    par->nota = 1/(par->nota);
	printf("Processo = %f\n", par->nota);
}
/*--------------------------------------------------------------------*/


int main(int argc, char **argv){
	double n1, n2, n3, trab;

	if ( argc != 5 ){
		printf("%s <N1> <N2> <N3> <Trabalhos>\n", argv[0]);
		exit(0);
	}

	n1 = atof(argv[1]);
	n2 = atof(argv[2]);
	n3 = atof(argv[3]);
	trab = atof(argv[4]);

	// variáveis locais
	pthread_t idA, idB, idC, idD, idE, idF;
	PARAMETROS *par = NULL;

	// alocação de memória para os parâmetros
	par = (PARAMETROS *)malloc(TAMANHO * sizeof(PARAMETROS));

	// calcula 2/n1 e aguarda finalizar
	par[0].nota = n1;
	pthread_create(&idA,NULL,peso_2, (void *) &par[0]);
	pthread_join(idA,NULL);

	// calcula 2/n2 e 1/n3 e aguarda finalizar
	par[1].nota = n2;
	par[2].nota = n3;
	pthread_create(&idB,NULL,peso_2,(void *) &par[1]);
	pthread_create(&idC,NULL,peso_1,(void *) &par[2]);
	pthread_join(idB,NULL);
	pthread_join(idC,NULL);

	// calcula 1/trab e aguarda finalizar
	par[3].nota = trab;
	pthread_create(&idD,NULL,peso_1,(void *) &par[3]);
	pthread_join(idD,NULL);

    double nota = 0;
    for(int i=0; i<4; i++){
        nota += par[i].nota;
    }

    printf("MEDIA FINAL: %f\n", 6/nota);
}

