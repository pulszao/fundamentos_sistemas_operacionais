#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h> 

#define N 641670017


/*****************************************************************************/
double tempoCorrente(void){
     struct timeval tval;
     gettimeofday(&tval, NULL);
     return (tval.tv_sec + tval.tv_usec/1000000.0);
}

/*****************************************************************************/
int primo ( unsigned long long int n){
	
	unsigned long long int i;
	int cont;

	cont = 0;	

	for ( i = 1; i <= n; i++){ 
		if (  n % i == 0 ){
			cont ++;
		}
	}

	if ( cont == 2 ){ 
		return (1);
	}
	else{
		return(0);
	}
}

/*****************************************************************************/
int main (int argc, char **argv){

	int pid, inc;
	double inicio, fim;
	unsigned long long int n = N;

	printf("Executar como root!\n");

	pid = fork();
	pid = fork();
	pid = fork();

	if ( pid > 0 ){
		inc = -20;
	}	
	else{
		inc = 20;
	}

	nice(inc);

	inicio = tempoCorrente();
		
	if ( primo(n) ) {
		printf("O valor %lld e primo\n", n);
	}
	else{
		printf("O valor e %lld nao e primo\n", n);
	}
	fim = tempoCorrente();
		

	printf("Tempo = %f\n", fim - inicio);
}

/*****************************************************************************/


