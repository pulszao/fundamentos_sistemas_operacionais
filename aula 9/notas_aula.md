# Troca de Página

Ocorre nas duas seguintes situações:
- Falta de página (page fault)
- Não existem frames livres na memória física (SO remove uma página para liberar espaço)

## Trashing
Processo com um numero elevado de page faults

# Algoritmos de Troca de Página

## Troca de Página FIFO
O sistema operacional mantém uma lista de todas as páginas correntes na memória:
- A página da cabeça da lista a mais velha
- A página do fim da lista é a mais recentemente

Em caso de Page-Fault:
- A página da cabeça da lista é removida
- A nova página acrescentada no fim da lista

![imagem](/aula%209/fifo.png)

## Troca Ótima de Página
As páginas são rotuladas com o número de instruções que serão executadas antes que a página seja referenciada
(Impossivel de ser implementado :/)

![imagem](/aula%209/great.png)

## Last Recently Used (LRU)
As páginas usadas recentemente serão novamente acessadas por ele no futuro
- Descarta a página que faz mais tempo que foi referenciada
- Processos respeitam o princípio de localidade de referência
- Processos concentram seus acessos em poucas áreas da memória

![imagem](/aula%209/lru.png)

## Algoritmo da Segunda Chance
É adicionada um bit de referência para cada pagina
Evita-se substituir páginas antigas muito acessadas

## Not Recently Used (NRU)
Considera também o bit de modificação:
- Preferência pela remoção de páginas pouco referenciadas e que não foram modificadas
- Redução no overhead de transferência de páginas
- Somente as páginas modificadas necessitam ser reescritas no disco

Divisão em classes:
- Classe 0 ( R = 0 e M = 0)
Não referenciada e não modificada
- Classe 1 ( R = 0 e M = 1)
Não referenciada e modificada
- Classe 2 ( R = 1 e M = 0)
Referenciada e não modificada
- Classe 3 ( R = 1 e M = 1)
Referenciada e não modificada

## Algoritmo do Envelhecimento
Algoritmo dos bits de referência adicionais
A cada amostragem os bits de referência são copiados para a tabela de históricos

![imagem](/aula%209/envelh.png)

## Algoritmo do Relógio
Melhoria do algoritmo da segunda chance
Armazena página em uma lista circular (relógio)

O ponteiro percorre a lista analisando os bits de
referência das página:
• Se o bit de referência for 0 a página é trocada
• Se o bit de fererência for 1 o bit é zerado

## Working Set
Working Set é o conjunto de páginas que estão sendo utilizadas por um processo
A ideia é substituir páginas que não se encontrem dentro do working set de um processo

## Working Set Clock
Algoritmo do Relógio + Working Set

Lista circular de páginas
Utiliza bit R e o tempo do último acesso a página

Quando há necessidade de substituir páginas, o ponteiro
percorre a fila buscando páginas candidatas:
- Ao encontrar uma página referenciada (R = 1) sua data de último acesso é atualizada com o valor corrente do tempo e o bit de referência é limpo (R=0)
- Ao encontrar uma página não referenciada (R= 0), se sua idade for menor que , a página está no conjunto τ de trabalho; caso contrário, ela é considerada fora do
conjunto de trabalho e pode ser substituída.
- Caso o ponteiro não encontre páginas com idade maior que , a página mais antiga é substituída. τ