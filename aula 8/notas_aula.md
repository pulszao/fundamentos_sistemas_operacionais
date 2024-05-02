# Escalonamento

## Não-preemptivo
Depois que a CPU foi alocada a um processo, o processo mantém a CPU até liberá-la terminando ou passando para o estado de espera (I/O)
Ex: Windows 3.x

## Preemptivo
O processo em execução na CPU pode ser interrompido para a execução de outro processo
Evita que um processo monopolize a CPU
Ex: Windows XP, Linux

### FIFO (first in, first out) ou FCFS (first come, first served)
Não-preemptivo
 
Um processo somente libera o processador :
- quando realiza uma chamada de sistema,
- ou quando ocorre algum erro na execução.

#### Tempo medio de execução
![imagem](/aula%208/tempo_medio_fifo.png)


### SJF (shortest job first)
(Método teórico)
Não-preemptivo

Ordena as tarefas do menor para o maior


### Round-Robin
'Versão preemptiva do FIFO'

O intervalo de tempo é chamado `quantum`

Funcionamento do Round Robin:
- Quando o quantum acaba o processo é colocado no final da fila
- Se um processo bloqueou ou terminou antes do final do quantum a CPU é dada para outro processo

Problema:
- Como definir a fatia de tempo do quantum
- O chaveamento entre processos não é instantâneo

- Um quantum muito pequeno
    - causa sucessivas trocas de contexto,
    - baixando a eficiência do processador.

- Um quantum muito elevado
    - causa um tempo de resposta inaceitável
    - para usuários interativos.

`Um valor aceitável para o quantum é de aproximadamente 100 ms`

#### Tempo medio de execução
![imagem](/aula%208/tempo_medio_robin.png)


### Escalonamento por Prioridade
Processos com alta prioridade sempre entram na frente
Possibilidade que processos de baixa prioridade nunca executem (portergação indefinida)

- Ajuste de Prioridade
- Algoritmo de Envelhecimento


### Escalonamento: Linux
Requisitos
- Apresentar boa performance em programas interativos,
mesmo com carga elevada
- Distribuir de maneira justa o tempo da CPU
- Possuir suporte para tempo real

Cada processo possui uma prioridade, que é recalculada
dinamicamente
- O escalonador entrega a CPU para o processo que possui a
maior prioridade
- O escalonador é preemptivo

Para processos interativos (mesma prioridade):
- Round Robin
Para processos de tempo real (mesma prioridade):
- FCFS (o processo executa até terminar ou se bloquear) ou Round Robin

Possui 140 niveis de prioridade


### Escalonamento: Windows

