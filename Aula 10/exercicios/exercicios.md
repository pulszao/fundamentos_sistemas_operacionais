O processador Intel 8086 é um processador de 16 bits, ou seja, sua unidade lógica e aritmética, os seus registradores internos e suas instruções foram concebidas para trabalhar com palavras de 16bits. Além disso, esse trabalha internamente com endereços lógicos de 16bits. Já o barramento de endereço do processador Intel 8086 é de 20 bits (memória física). A conversão dos endereços é realizada através de quatro registradores de 16 bits que indicam o início dos segmentos de dados, código, pilha e extra de um programa (DS, CS, SS e ES, respectivamente). A conversão de um endereço lógico de um determinado segmento do programa em endereço físico é feito da seguinte forma: o valor do registrador base do segmento é deslocado 4 bits para a esquerda e o endereço lógico é somado a esse valor deslocado. Por exemplo, supondo que o endereço lógico de uma variável de um programa é 4AB2h (010010101010010b) e o valor de DS seja 1123h, o endereço físico que essa variável corresponderá será:

11230      ou       00010001001000110000
+4AB2               +0100101010110010
15CE2               00010101110011100010

 

a) Qual o tamanho máximo de memória que esse processador pode endereçar?
2^20 = 1 Mb

b) Qual o último endereço de memória em hexadecimal?
1111 1111 1111 1111 1111 => 0xFFFFF

c) Qual o tamanho máximo de um segmento nessa arquitetura?
2^16 = 64 kb

d) Supondo que os registradores DS, CS, SS e ES contenham, respectivamente, AAAAh, BBBBh, CCCCh e DDDDh e o contador de programa (IP) contenha 1234h. Qual o endereço físico da próxima instrução a ser executada?

CS + IP = BBBB0
         + 1234
         -------
          BCDE4 