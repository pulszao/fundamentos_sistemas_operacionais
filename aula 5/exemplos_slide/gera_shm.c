#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

void gera_vetor(int ini, int inc, int vet[N]){
	int i;
	srand(time(NULL));		
	for (i=ini;i<N;i+=inc){
		vet[i] = rand()%100;
	}
}

void escreve_vetor(int vet[N]){
	int i;
	for (i=0;i<N;i++){
		printf("%d ", vet[i]); 	
	}
	printf("\n");
}

int main(){
	int *vet = NULL; // memoria compartilhada
	int shmid;       // id memoria
	int pid;         // fork

	shmid = shmget(5, N * sizeof(int), IPC_CREAT | 0600);

	vet = shmat(shmid, 0, 0);	
	
	pid = fork();

	if (pid > 0 ) {
		pid = fork();

		if (pid > 0) {
			wait(NULL);
			wait(NULL);
			escreve_vetor(vet);
			shmdt(vet);	
			shmctl(shmid, IPC_RMID, 0);
		}
		else{
			// preenche as posicoes pares do vetor
			gera_vetor(0, 2, vet);
			shmdt(vet);
		}
	} else {
		// preenche as posicoes impares do vetor
		gera_vetor(1, 2, vet);
		shmdt(vet);
	}
}
