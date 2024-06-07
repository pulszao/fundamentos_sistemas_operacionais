# Trabalho de Implementação 2024-2

## Universidade de Caxias do Sul
**Área de Ciências Exatas e Engenharias**

**Disciplina:** Fundamentos de Sistemas Operacionais  
**Professor:** Daniel Luis Notari

## Descrição do Projeto
O projeto aborda a duplicação de uma ponte em um cenário fictício, onde congestionamentos severos ocorrem devido ao alto fluxo de veículos e às interrupções causadas pelas obras.

## Objetivo
Desenvolver um software que resolva o problema de controle de acesso aos recursos (pista da ponte) utilizando programação concorrente. O problema é modelado como um problema clássico de sistemas operacionais (produtor-consumidor) usando exclusão mútua e variáveis de condição. A implementação deve ser realizada com a biblioteca `pthreads` e também com a biblioteca `fork` utilizando memória compartilhada.

## Implementação
O software deve simular filas do tipo produtor-consumidor para cada uma das 10 pistas (cinco para cada lado da ponte). Diversos carros, representados como threads, devem ser criados para simular o congestionamento. As situações a serem simuladas incluem:

- **Ponte totalmente fechada:** Mostrando o acúmulo de carros até 10 km de cada lado.
- **Ponte com fluxo baixo:** Passagem de 30/60/90 veículos por minuto.

As variáveis de condição são utilizadas para:
- Controlar o número de carros em cada pista.
- Controlar o acesso ou bloqueio da ponte utilizando mutex e semáforos (leitores e escritores).

## Detalhes de Implementação
- **Linguagem:** C
- **Memória compartilhada:** Uso de variáveis globais é permitido.
