#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main() {
    // a=1; b=12; c=-13
    float a, b, c, delta, r1, r2;
    float *r;
    int chave=5, shmid, pid;

    printf("Digite os coeficientes:\n");
    scanf("%f %f %f", &a, &b, &c);

    delta = b*b - 4*a*c;

    if ( delta < 0){
        printf("Nao possui raizes reais\n");
    }
    else if ( delta == 0 ){
        printf("Raiz: %f\n", -b/(2*a));
    }
    else{
 
        shmid = shmget(chave, 2*sizeof(float), IPC_CREAT | 0600 );
                
        r = shmat(shmid, 0, 0);

        pid = fork();

        if ( pid > 0 ){                
            r[0] = ( -b - sqrt(delta)) / (2*a);
            wait(NULL);
            printf("Raizes: %f %f\n", r[0], r[1]);
            shmdt(r);
            shmctl(shmid, IPC_RMID, 0);
        }
        else{ 
            r[1] = ( -b + sqrt(delta)) / (2*a);
            shmdt(r);        
        }
    }

    return 0;
}
