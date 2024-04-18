#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------------------------------------------------------*/
double calculo_media(double n1, double n2, double n3, double trab){
	return (6 / ( (2/n1) + (2/n2) + (1/n3) + (1/trab) ));	
} 

/*---------------------------------------------------------------------*/
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

	printf("MEDIA: %.2f\n", calculo_media(n1, n2, n3, trab));
}

/*---------------------------------------------------------------------*/
