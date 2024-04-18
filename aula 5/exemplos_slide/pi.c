#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------------------------------------------------------*/
double calculo_pi(double nr){
	double pi = 0;
	double x, base, altura;
	double i;

	base = 1.0 / nr; 

	for( i=1 ; i<=nr ;  i++ ) { 
                x = base * (( double)i - 0.5); 
                altura = 4.0 / (1.0 + x*x); 
		pi += base * altura;
	}
	return pi;	
} 

/*---------------------------------------------------------------------*/
int main(int argc, char **argv){

	double nr;

	if ( argc != 2 ){
		printf("%s <Numero de retangulos>\n", argv[0]);
		exit(0);
	}

	nr = atof(argv[1]);

	printf("PI: %.15f\n", calculo_pi(nr));
}

/*---------------------------------------------------------------------*/
