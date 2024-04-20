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

void G(){
	printf("G\n");
}

void H(){
	printf("H\n");
}

void main(){
	pid_t pid1, pid2, pid3, pid4;
	pid1 = fork();
	if (pid1 > 0){
		pid2 = fork();
		if (pid2 > 0){
			B();
			wait(NULL); // aguarda A ou C terminar 
			wait(NULL); // aguarda A ou C terminar 
			pid3 = fork();
			if (pid3 > 0){
				D();
				wait(NULL); // aguarda E terminar
				F();
				pid4 = fork();
				if (pid4 > 0){
				     G();
				}
				else H();
			}
			else E();
		}
		else C();
	}
	else A();
}

