#include <pth.h>
#include <stdio.h>
#include <unistd.h>

/*-----------------------------------------------------*/
#define T 10

/*-----------------------------------------------------*/
void * funcao(void * args){
	int tid = *(int *)args;
	printf("Alo mundo - Pth %d\n", tid);  
	sleep(5);
}

/*-----------------------------------------------------*/
int main(int argc, char **argv){

	pth_t tid[T];
	int i, id[T];

	pth_init();
	
	for ( i=0; i<T; i++ ){
		id[i] = i;
		tid[i] = pth_spawn(PTH_ATTR_DEFAULT, funcao, &id[i]);
	}

	for ( i=0; i<T; i++){
		pth_join(tid[i], NULL); 
	}
	printf("Terminando o programa\n");
}
/*-----------------------------------------------------*/

