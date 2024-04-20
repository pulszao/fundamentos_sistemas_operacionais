#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void T6(){  
    printf("T6\n");
}

void T1(){  
    printf("T1\n");
}

void T2(){  
    printf("T2\n");
}

void T3(){  
    printf("T3\n");
}

void T4(){  
    printf("T4\n");
}

void T5(){  
    printf("T5\n");
}

void main(){
	pid_t pid1, pid2;
	T1();
	pid1 = fork();
	if (pid1 > 0){
		pid2 = fork();
		if (pid2 > 0 ) {
			T2();
            wait(NULL);
			wait(NULL);
			T5();
			T6();	
		}
		else T3();
	}
	else T4();
}
