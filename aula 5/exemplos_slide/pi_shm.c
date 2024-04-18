#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

/*---------------------------------------------------------------------*/
double calculo_pi(double ri, double nr, double np){
	double pi = 0;
	double x, base, altura;
	double i;

	base = 1.0 / nr; 

	for( i= ri ; i<=nr ;  i+=np ) { 
        x = base * (( double)i - 0.5); 
        altura = 4.0 / (1.0 + x*x); 
		pi += base * altura;
	}
	return pi;	
} 

/*---------------------------------------------------------------------*/
int main(int argc, char **argv){
	// ./pi_shm <valor1> <valor2>

	double nr;
	int i, id, pid, np;
	double *pi_parcial = NULL;
	double pi;
	int shmid;
	int chave = 5;

	if ( argc != 3 ){
		printf("%s <Numero de retangulos> <Numero de processos>\n", argv[0]);
		exit(0);
	}

	nr = atof(argv[1]);
    np = atoi(argv[2]);

	shmid = shmget(5, np * sizeof(double), IPC_CREAT | 0600);

	pi_parcial = shmat(shmid, 0, 0);

    id = 0;
    for(i=1; i<np; i++){
        pid = fork();
        if ( pid == 0 ){
            id = i;
            break;
        }
    }
    
	pi_parcial[id] = calculo_pi(id+1, nr, np);

    if ( id != 0 ){
        shmdt(pi_parcial);
	}
    else{
        for(i=1; i<np; i++){
            wait(NULL);
        }
        for(i=0; i<np; i++){
            pi += pi_parcial[i];    
        }
		printf("PI: %.15f\n", pi);	
    	shmdt(pi_parcial);
		shmctl(shmid, IPC_RMID, NULL);
    }
}

/*---------------------------------------------------------------------*/
