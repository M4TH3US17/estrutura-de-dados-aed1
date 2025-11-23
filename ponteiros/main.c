#include <stdio.h>
#include <stdlib.h>

/*
    -> "B" = Byte, "b" = bit;
    -> Um endereço de memória tem:
       * 8bits (1Byte) p/ caractere (A, B, C, etc)
       * 32bits (4Bytes) p/ inteiro (..., -1, 0, 1, ...)
       * 32bits (4Bytes) p/ float
*/

int main() {

    printf("\n--------------------------------------------------");
    printf("\n           DECLARAÇÃO DO PONTEIRO              ");
    printf("\n--------------------------------------------------\n");
    printf("Endereço (Hexadecimal) |  Conteúdo");
    /*
       -> Vetor de 7 ponteiros do tipo caractere apontando p/ endereços sequenciais na Mem. RAM;
       -> Os bits dentro de cada um dos endereços são transcritos com base na tipagem (char, int, etc);
       -> A transcrição é sequencial (0xffeecb0 [0], 0xffeecb1 [1], ... , 0xffeecb6 [6]);
       -> Não há valor setado no vetor, então os valores são os bits "lixo" que já estavam dentro do endereço;
    */
    char* caracteres[7];
    printf("\n[0]: %p    |  %s", &caracteres[0], caracteres[0]);
    printf("\n[1]: %p    |  %s", &caracteres[1], caracteres[1]);
    printf("\n[2]: %p    |  %s", &caracteres[2], caracteres[2]);
    printf("\n[3]: %p    |  %s", &caracteres[3], caracteres[3]);
    printf("\n[4]: %p    |  %s", &caracteres[4], caracteres[4]);
    printf("\n[5]: %p    |  %s", &caracteres[5], caracteres[5]);
    printf("\n[6]: %p    |  %s", &caracteres[6], caracteres[6]);

    printf("\n\n> Nota-se que a cada nova compilação/execução os ponteiros apontam pra endereços \n  diferentes, isso acontece pq a memória RAM é dinâmica e a cada fim de execução o \n  processo/programa encerra, ou seja, a cada nova execução o programa reinicia apontando\n  aleatoriamente pra endereços aleatórios na memória;");

    printf("\n\n--------------------------------------------------");
    printf("\n                MALLOC/FREE                         ");
    printf("\n--------------------------------------------------\n");
    printf("Endereço (Hexadecimal) |  Conteúdo");
    /*
      -> ALOCANDO MEMÓRIA P/ CADA ENDEREÇO NOS PONTEIROS
      -> 7 x 8B (qtde de posições x bytes ponteiro) = 56B ou 448b alocados pro vetor;
      -> caracteres[index] é um PONTEIRO que contém um ENDEREÇO de memória;
    */
    for (int index = 0; index < 6; index++)
        caracteres[index] = (char*) malloc(2 * sizeof(char));

    for(int index = 0;index < 6; index++)
        printf("\n[%d]: %p    |  %s", index, &caracteres[index], caracteres[index]);

    for (int index = 0; index < 6; index++) free(caracteres[index]);

    /*printf("\n\n  APÓS A FUNÇÃO free()");
    for(int index = 0;index < 6; index++)
        printf("\n[%d]: %p    |  %s", index, &caracteres[index], caracteres[index]);*/

    printf("\n\n> A função \"malloc\" alocou os espaços nos endereços mantendo os bits \"lixo\" de outros \n  processos/programas do computador. Pra mudar esses bits, só atribuindo valor a cada \n  variável ponteiro;\n");
    printf("\n> Neste ultimo FOR (descomente-o) os endereços de cada ponteiro que passaram \n  pela free() foram liberados para outros programas/processos usar. Com isso, \n  pode ser que esses processos sobrescrevam ou reutilizem os bits/dados que deixamos lá;");

    printf("\n\n--------------------------------------------------");
    printf("\n      PONTEIRO COMO VALOR DE OUTRO PONTEIRO                         ");
    printf("\n--------------------------------------------------\n");
    char* ptr1;
    char* ptr2;
    char* ptrAux;

    ptr1 = malloc(10);
    ptr2 = malloc(10);

    // -> Valores iniciais dos ponteiros (cada um apontando p/ seu respectivo endereço);
    printf("Ponteiro 1 (ptr1): %p", ptr1);
    printf("\nPonteiro 2 (ptr2): %p", ptr2);
    //printf("\nPonteiro Auxiliar (ptrAux): %p", ptrAux);

    ptrAux = ptr1;
    ptr1 = ptr2;

    // -> Ponteiro 1 aponta p/ o mesmo endereço de Ponteiro 2;
    printf("\n\nPonteiro 1 (ptr1): %p", ptr1);
    printf("\nPonteiro 2 (ptr2): %p", ptr2);
    //printf("\nPonteiro Auxiliar (ptrAux): %p", ptrAux);

    printf("\n\n> Ponteiro 1 (ptr1) inicialmente guardava o endereço %p, mas foi-lhe atribuido\n  o Ponteiro 2 %p, então Ponteiro 1 e Ponteiro 2 agora apontam para o mesmo endereço\n  de memória (%p);", ptrAux, ptr2, ptr1);
    free(ptr1);
    free(ptrAux);
    //printf("Ponteiro 1: %p;\nPonteiro 2: %p;\nPonteiro Auxiliar: %p;", &ptr1, &ptr2);

    return 0;
}
