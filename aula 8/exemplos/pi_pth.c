#include <math.h>
#include <stdio.h>
#include <pth.h>
#include <stdlib.h>


/*-----------------------------------------------------*/
struct args {
	int nthreads;
	double npontos;
	double cont;
	int seed;
};
typedef struct args ARGS;

/*-----------------------------------------------------*/
void * calcula_pi(void * args){

	ARGS *p = (ARGS *) args;
	int nthreads = p->nthreads;
	double npontos = p->npontos;
	int seed = p->seed;

	double i, cont = 0;
	double x, y, distancia;

	for ( i=0; i<npontos/nthreads; i++){
		x = rand_r(&seed)/(double)RAND_MAX;
		y = rand_r(&seed)/(double)RAND_MAX;
		distancia = sqrt(x*x + y*y);
		if ( distancia <= 1 ){
			cont++;
		}
	}

	p->cont  = cont;
}

/*-----------------------------------------------------*/
int main(int argc, char **argv){

	pth_t *id = NULL;
	int i, nthreads;
	ARGS *argumentos = NULL;
	double npontos;
	double cont;
	double pi;
	int seed;
	
	if ( argc != 3 ){
		printf("%s <num_pontos> <num_threads>\n", argv[0]);
		exit(0); 
	}

	pth_init();

	npontos = atof(argv[1]);
	nthreads = atoi(argv[2]);

	id = (pth_t *)malloc(nthreads * sizeof(pthread_t));
	argumentos = (ARGS *)malloc(nthreads * sizeof(ARGS));


	seed = time(NULL);

	for ( i=0; i<nthreads; i++ ){
		argumentos[i].nthreads = nthreads;
		argumentos[i].npontos = npontos;
		argumentos[i].cont = 0;		
		argumentos[i].seed = seed;
		id[i] = pth_spawn(PTH_ATTR_DEFAULT, calcula_pi, (void *)&argumentos[i]);
	}

	for ( i=0; i<nthreads; i++){
		pth_join(id[i], NULL); 
		cont += argumentos[i].cont;
	}
	
	pi = 4 * cont/npontos;

	printf("PI= %.15f\n", pi);
}
/*-----------------------------------------------------*/

