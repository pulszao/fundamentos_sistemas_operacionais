#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define PROCESSOS 2

double calcula_numerador(double n1, double n2, double n3, double trab) {
	return ((2/n1) + (2/n2) + (1/n3) + (1/trab));	
}

/*---------------------------------------------------------------------*/
double calculo_media(double numerador){
	return 6 / numerador;	
} 

/*---------------------------------------------------------------------*/
int main(int argc, char **argv){
	double n1, n2, n3, trab, numerador = 0;
	double *numerador_parc = NULL;
	int pid, id;
	int shmid;

	if ( argc != 5 ){
		printf("%s <N1> <N2> <N3> <Trabalhos>\n", argv[0]);
		exit(0);
	}

	n1 = atof(argv[1]);
	n2 = atof(argv[2]);
	n3 = atof(argv[3]);
	trab = atof(argv[4]);

	shmid = shmget(5, PROCESSOS * sizeof(double), IPC_CREAT | 0600);

	pid = fork();
	numerador_parc = shmat(shmid, 0, 0);

	id = 0;
    for(int i=1; i<PROCESSOS; i++){
        pid = fork();
        if ( pid == 0 ){
            id = i;
            break;
        }
    }

	if (pid > 0) {
		// PAI
		numerador_parc[id] = calcula_numerador(n1, n2, n3, trab);
		wait(NULL);
	} else {
		// FILHO
        for(int i=1; i<PROCESSOS; i++){
            wait(NULL);
        }
        for(int i=0; i<PROCESSOS; i++){
            numerador += numerador_parc[i];    
        }
		printf("MEDIA: %.2f\n", calculo_media(numerador));
    	shmdt(numerador_parc);
		shmctl(shmid, IPC_RMID, NULL);
	}
}

/*---------------------------------------------------------------------*/
