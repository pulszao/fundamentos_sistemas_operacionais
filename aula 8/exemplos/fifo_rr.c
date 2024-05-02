#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h> 

#define N 6416700417


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

	int pid, ret;
	double inicio, fim;
	unsigned long long int n = N;
	struct timespec ts;

	struct sched_param sp;

	printf("Executar como root!\n");

	sp.sched_priority = sched_get_priority_max(SCHED_FIFO); 

	pid = fork();
	pid = fork();

	if ( pid > 0 ){
		ret = sched_setscheduler(0, SCHED_FIFO, &sp);	
	}

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


