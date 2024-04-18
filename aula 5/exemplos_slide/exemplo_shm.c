#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 30 // tamanho da memória compartilhada
#define KEY 1   // chave

void main()
{
    // variáveis locais
    pid_t pid; // fork
    key_t key = KEY; // chave
    int shmid; // id da memória compartilhada
    char *memory; // memória compartilhada
    int i;

    // cria área de memória compartilhada
    if ((shmid = shmget(key, SIZE, IPC_CREAT | 0600)) < 0)
        printf("Erro na criacao da memoria compartilhada");

    // associar área de memória compartilhada    
    if ((memory = shmat(shmid, 0, 0)) < 0)
        printf("Erro na alocacao");

    // cria um novo processo
    pid = fork();
    if (pid > 0)
    {
        // popula a área compartilhada com o alfabeto
        for (i = 0; i < 26; i++)
            memory[i] = 'a' + i;
        memory[i] = '\0';

        // espera o outro processo terminar
        wait(NULL);

        // libera memória
        shmdt(memory);
        shmctl(shmid, IPC_RMID, NULL);
    }
    else
    {
        // aguarda 10 segundos
        sleep(10);

        // escreve o conteúdo da memória compartilhada
        printf("FILHO: %s\n", memory);
    }
}