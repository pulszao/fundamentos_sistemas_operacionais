#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void A(){
	printf("A\n");
}

void B(){
	printf("B\n");
}

void C(){
	printf("C\n");
}

void D(){
	printf("D\n");
}

void E(){
	printf("E\n");
}

void F(){
	printf("F\n");
}


void main(){
	pid_t pid1,pid2;
	A();
	pid1 = fork();
	if (pid1>0){
		B();
		wait(NULL); // espera C executar
		pid2 = fork();
		if (pid2>0){
			D();
			wait(NULL); // espera E executar
			F();
		}
		else 	E();		
	}
	else	C();
}

