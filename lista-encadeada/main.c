
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    (nome[10] + idade)
    = {(10B + 2B) + 4B)} = Bytes/pessoa
    = 16B

    -> processadores 64-bit buscam 8Bytes por vez na memória;
    -> processadores 32-bit buscam 4Bytes por vez na memória;
*/
typedef struct Pessoa {
  char nome[10]; // 12B (o compilador corrige o 10B adicionando +2B overhead pra organizar o padding de memória)
  int idade; // o 4B daqui agora começa no Byte 12
} Pessoa;

struct Aluno { // (notas[4] + next + dados) = (16B + 8B + 16B) = Bytes/aluno = 40B/1
  Pessoa dadosPessoais;
  float notas[4];
  struct Aluno* next; // 8B de overhead
};

/*
    @note comparar este código com o esquema que está no README seção
*/
struct Aluno* add_fim(struct Aluno* head, struct Aluno data) {
    struct Aluno* enderecoMemoriaNovoNode = (struct Aluno*) malloc((sizeof(struct Aluno)));

    enderecoMemoriaNovoNode->next = NULL;
    enderecoMemoriaNovoNode->dadosPessoais.idade = data.dadosPessoais.idade;
    strcpy(enderecoMemoriaNovoNode->dadosPessoais.nome, data.dadosPessoais.nome);
    for(int index = 0; index < 3; index++)
        enderecoMemoriaNovoNode->notas[index] = data.notas[index];

    int ehPrimeiroNodeDaLista = (head->next == NULL);
    if(ehPrimeiroNodeDaLista) return enderecoMemoriaNovoNode;

    struct Aluno* ultimoNode = head;
    int ehUltimoNodeDaLista  = (ultimoNode->next != NULL);
    while(ehUltimoNodeDaLista)
        ultimoNode = ultimoNode->next;
    ultimoNode->next = enderecoMemoriaNovoNode;

    return head;
}

int main() {
    struct Aluno* head = (struct Aluno*) malloc((sizeof(struct Aluno)));
    head->next = NULL;

    struct Aluno* novo = add_fim(head, (struct Aluno) {
      .dadosPessoais.nome = "Matheus",
      .dadosPessoais.idade = 22,
      .notas = {0, 1.5, 0, 2},
      .next = NULL
    });

    head->next = novo;

    free(head);

    return 0;
}
