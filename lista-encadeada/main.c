#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa {
    char nome[10];
    int idade;
    struct Pessoa* next;
} Node;

// Funções Auxiliares
Node* criar_node(Node data) {
    Node* novo = (Node*) malloc(sizeof(Node));
    *novo = data;
    novo->next = NULL;
    return novo;
};

int ehPrimeiroNodeNull(Node* head) {
    return head->next == NULL;
}

// Funções de Busca
void imprimir(Node* node) {
    if(node == NULL) return;
    printf("%s\n", node->nome);
    return imprimir(node->next);
}

Node* buscar_ultimo(Node* node) {
    if(node == NULL) return NULL;
    if(node->next == NULL) return node;
    return buscar_ultimo(node->next);
}

// Funções de Adicionar
void inserir_inicio(Node* head, Node node) {
    Node *primeiro = head->next;
    
    if(ehPrimeiroNodeNull(head)) {
        head->next = criar_node(node);
        return;
    }
    
    Node* novo = criar_node(node);
    novo->next = primeiro;
    head->next = novo;
};

void inserir_fim(Node* head, Node node) {
    if(ehPrimeiroNodeNull(head)) {
        inserir_inicio(head, node);
        return;
    }
    Node* ultimo = buscar_ultimo(head);
    ultimo->next = criar_node(node);
};

// Funções de Remover
void remover_por_nome(Node* head, Node* before, char nome[]) {
    int ehPrimeiro = !strcmp("", before->nome);
    int ehUltimo = !strcmp("", head->nome);
    
    if(ehPrimeiroNodeNull(head) && ehUltimo) return;
    
    if(!strcmp(nome, head->nome)) {
        if(ehPrimeiro) {
            // head apontar pro segundo 
            // primeiro elemento não apontar p/ segundo (isolar ele)
            // excluir o primeiro elemento, que está isolado
            Node* lixo = head;
            Node* segundo = lixo->next; 
            head = segundo;
            
            lixo->next = NULL;
            free(lixo);
            
            printf("\nPrimeiro (HEAD): %s\n",head);
            printf("Lixo: %s\n",lixo);
            return;
        }
        printf("\n\n> Current: %s, Before: %s", head->nome, before);
        return;
    }
    Node* previous = head;
    return remover_por_nome(head->next, previous, nome);
}

int main() {
    Node* head = (Node*) malloc(sizeof(Node));
    head->next = NULL;
    
    inserir_fim(head, (Node) { .nome= "Tommy", .idade= 22, .next= NULL });
    inserir_fim(head, (Node) { .nome= "Matheus", .idade= 22, .next= NULL });
    inserir_fim(head, (Node) { .nome= "Melanie", .idade= 22, .next= NULL });
    inserir_fim(head, (Node) { .nome= "Maysa", .idade= 22, .next= NULL });
    
    imprimir(head);
    remover_por_nome(head, head, "Tommy");
    imprimir(head);
    
    return 0;
}