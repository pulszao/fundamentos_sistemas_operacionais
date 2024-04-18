#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calcula_numerador(double n1, double n2, double n3, double trab) {
	return ((2/n1) + (2/n2) + (1/n3) + (1/trab));	
}

/*---------------------------------------------------------------------*/
double calculo_media(double numerador){
	return 6 / numerador;	
} 

/*---------------------------------------------------------------------*/
int main(int argc, char **argv){
	double n1, n2, n3, trab, numerador;
	int pid;

	if ( argc != 5 ){
		printf("%s <N1> <N2> <N3> <Trabalhos>\n", argv[0]);
		exit(0);
	}

	n1 = atof(argv[1]);
	n2 = atof(argv[2]);
	n3 = atof(argv[3]);
	trab = atof(argv[4]);

	pid = fork();

	if (pid > 0) {
		// PAI
		numerador = calcula_numerador(n1, n2, n3, trab);
		wait(NULL);
	} else {
		// FILHO
		printf("MEDIA: %.2f\n", calculo_media(numerador));
	}
}

/*---------------------------------------------------------------------*/
