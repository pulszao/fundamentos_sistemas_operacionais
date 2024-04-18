#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void gera_vetor(int vet[N]){
	int i;
	srand(time(NULL));		
	for (i=0;i<N;i++){
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
	int vet[N];
	gera_vetor(vet);
	escreve_vetor(vet);
}
