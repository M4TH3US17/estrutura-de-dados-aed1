
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
    
    *novo = data;
    novo->next = NULL;
    printf("add_fim :: Node de endereço \"%p\" (%s) criado com sucesso!\n", novo, novo->dadosPessoais.nome);
    
    if(head->next == NULL) {
        printf("add_fim :: Elemento de endereço \"%p\" é o primeiro da lista.\n", novo);
        head->next = novo;
        printf("add_fim :: Elemento inserido no inicio com sucesso! (ele é o primeiro nó)\n\n");
        return novo;
    }
    
    printf("add_fim :: Iniciando busca do ultimo elemento da lista...\n");
    struct Aluno* ultimo = head;
    
    while(ultimo->next != NULL) 
        ultimo = ultimo->next;
    
    ultimo->next = novo;
    printf("add_fim :: Elemento inserido no fim com sucesso!\n\n");
    
    return head->next;
}

struct Aluno* add_inicio(struct Aluno* head, struct Aluno data) {
    struct Aluno* novo = (struct Aluno*) malloc(sizeof(struct Aluno));
    *novo = data;
    
    printf("add_fim :: Node de endereço \"%p\" (%s) criado com sucesso!\n", novo, novo->dadosPessoais.nome);
    printf("add_fim :: Adicionando \"%p\" no inicio da lista...\n", novo);
    if(head->next == NULL) {
        novo->next = NULL;
        head->next = novo;
        printf("add_fim :: \"%p\" é o primeiro elemento da lista!\n\n", novo);
        return head;
    }
    
    struct Aluno* primeiro = head->next;
    novo->next = primeiro;
    head->next = novo;
    
    printf("add_fim :: \"%p\" adicionado ao inicio com sucesso!\n\n", novo);
    return head;
}

void get_all(struct Aluno* head) {
    printf("add_fim :: Iniciando processo de busca de todos os elementos...\n");
    struct Aluno* inicio = head;
    
    while(inicio->next != NULL) {
        inicio = inicio->next;
        printf("%s\n", inicio->dadosPessoais.nome);
    }
    
    free(inicio);
}

// struct Aluno* get_by_name(struct Aluno* head, char name[10]) {
//     printf("add_fim :: Iniciando processo de busca do aluno de nome \"%s\"...\n", name);
//     return NULL;
// }

// void remove_by_name(struct Aluno* head, char name[10]) {
//     printf("add_fim :: Iniciando processo de remoção do aluno de nome \"%s\"...\n", name);
    
//     if(head->next == NULL) {
//         printf("add_fim :: Lista vazia!\n", name);
//         // matar a execução aqui
//     }
    
//     struct Aluno* aluno = get_by_name(head, name);
// }

int main() { 
    struct Aluno* head = (struct Aluno*) malloc((sizeof(struct Aluno)));
    head->next = NULL;
    
    
    add_fim(head, (struct Aluno) {
      .dadosPessoais.nome = "Matheus", 
      .dadosPessoais.idade = 22, 
      .notas = {0, 1.5, 0, 2}, // Manda ele me dar um ponto, to na merd
      .next = NULL 
    });
    
    add_inicio(head, (struct Aluno) {
      .dadosPessoais.nome = "Edson",  
      .dadosPessoais.idade = 20, 
      .notas = {10, 10, 10, 10}, 
      .next = NULL 
    });
    
    add_fim(head, (struct Aluno) {
      .dadosPessoais.nome = "Jaide",  
      .dadosPessoais.idade = 20, 
      .notas = {10, 9, 9, 7}, 
      .next = NULL 
    });
    
    get_all(head);
    
    free(head);
    
    return 0;
}
