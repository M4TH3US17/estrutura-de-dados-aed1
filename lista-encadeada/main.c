
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
    @param head inicio da lista
    @param data dados do novo nó da lista
    
    @return endereço do novo nó se head for nulo
    @return endereço do primeiro nó se head não for nulo
*/
struct Aluno* add_fim(struct Aluno* head, struct Aluno data) {
    printf("add_fim :: Iniciando processo de inserção no fim da lista...\n");
    struct Aluno* novo = (struct Aluno*) malloc(sizeof(struct Aluno));
    
    printf("add_fim :: Node de endereço \"%p\" criado com sucesso!\n", novo);
    *novo = data;
    novo->next = NULL;
    
    if(head->next == NULL) {
        printf("add_fim :: Elemento de endereço \"%p\" é o primeiro da lista.\n", novo);
        head->next = novo;
        printf("add_fim :: Elemento inserido no inicio com sucesso! (ele é o primeiro nó)\n\n");
        return novo;
    }
    
    printf("add_fim :: Iniciando busca do ultimo elemento da lista...\n");
    struct Aluno* ultimo = head;
    
    printf("add_fim :: Iniciando busca do ultimo elemento da lista...\n");
    while(ultimo->next != NULL) 
        ultimo = ultimo->next;
    
    ultimo->next = novo;
    printf("add_fim :: Elemento inserido no fim com sucesso!\n\n");
    
    return head->next;
}

int main() { 
    struct Aluno* head = (struct Aluno*) malloc((sizeof(struct Aluno)));
    head->next = NULL;
    
    add_fim(head, (struct Aluno) {
      .dadosPessoais.nome = "Matheus", 
      .dadosPessoais.idade = 22, 
      .notas = {0, 1.5, 0, 2}, 
      .next = NULL 
    });
    
    add_fim(head, (struct Aluno) {
      .dadosPessoais.nome = "Matheus", 
      .dadosPessoais.idade = 22, 
      .notas = {0, 1.5, 0, 2}, 
      .next = NULL 
    });
    
    free(head);
    
    return 0;
}
