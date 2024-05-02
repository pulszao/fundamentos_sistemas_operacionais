#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <math.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>

#define N 6416700417

/*****************************************************************************/

void systemcall_rusage(char *str){

	printf("-----------------------------------------------\n");
	printf("----------------- %s ----------------------\n",str);
	printf("-----------------------------------------------\n");

	struct rusage buf;

	getrusage(RUSAGE_SELF, &buf);
    
	printf("Trocas voluntarias de contexto: %ld\n",  buf.ru_nvcsw);
	printf("Trocas involuntarias de contexto: %ld\n", buf.ru_nivcsw);
}

/*****************************************************************************/

int primo ( unsigned long long int n){
	
	unsigned long long int i;
	int cont = 0;	

	for ( i = 1; i <= n; i++){ // Testar para --> for ( i = 2; i <= sqrt(n); i++)  -->   if (cont == 0 ) 
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

void cpu_bound(){

	unsigned long long int n = N;

	systemcall_rusage("INICIO");	

	int res = primo ( n ) ;		

	systemcall_rusage("FINAL");	

	if ( res ) {
		printf("O valor %lld e primo\n", n);
	}
	else{
		printf("O valor e %lld nao e primo\n", n);
	}
}

/*****************************************************************************/

void io_bound(){

	int i, n;

	systemcall_rusage("INICIO");	

	for ( i=0;i<5; i++){
		sleep(1);
	}

	systemcall_rusage("FINAL");	
}

/*****************************************************************************/

int main (int argc, char **argv){
	

	#ifdef CPU_BOUND
		cpu_bound();
	#elif  IO_BOUND
		io_bound();
	#endif
}

/*****************************************************************************/


