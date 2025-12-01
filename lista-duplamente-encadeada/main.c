#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa {
    char nome[10];
    int idade;
    char genero;
    struct Pessoa* next;
    struct Pessoa* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} ListaDupla;

Node* criar_node(Node data) {
    Node* novo = (Node*) malloc(sizeof(Node));
    *novo = data;
    return novo;
}

void inserir_inicio(ListaDupla* lista, Node data) {
    Node* novo = criar_node(data);
    Node* first = lista->head;
    Node* last = lista->tail;

    if(first == NULL) {
        lista->head = novo;
        lista->tail = novo;
        return;
    }

    lista->head->prev = novo;
    novo->next = lista->head;
    lista->head = novo;
}

void inserir_fim(ListaDupla* lista, Node data) {
    Node* novo = criar_node(data);
    Node* first = lista->head;

    if(first == NULL) {
        inserir_inicio(lista, data);
        return;
    }

    lista->tail->next = novo;
    novo->prev = lista->tail;
    lista->tail = novo;
}

/*
 * @example imprimir(lista->tail, 0) imprime do fim pra frente;
 * @example imprimir(lista->head, 1) imprime da frente pra trás;
 */
void imprimir(Node* current, int startByHEAD) {
    int isInvalidStartBy = (startByHEAD != 1 && startByHEAD != 0);

    if (current == NULL) return;
    if(isInvalidStartBy) return;

    Node* prev = current->prev;
    Node* next = current->next;

    printf("\n%s", current->nome);
    (startByHEAD == 0) ? imprimir(prev, startByHEAD) : imprimir(next, startByHEAD);
}

int main() {
    ListaDupla* lista = (ListaDupla*) malloc(sizeof(ListaDupla));
    lista->head = NULL;
    lista->tail = NULL;

    inserir_fim(lista, (Node) { .nome= "Matheus", .idade= 22, .genero='M' });
    inserir_fim(lista, (Node) { .nome= "Melanie", .idade= 9, .genero='F' });
    inserir_fim(lista, (Node) { .nome= "Chloe", .idade= 9, .genero='F' });
    inserir_fim(lista, (Node) { .nome= "Maysa", .idade= 24, .genero='F' });
    inserir_inicio(lista, (Node) { .nome= "Tommy", .idade= 10, .genero='M' });
    imprimir(lista->head, 1);

    return 0;
}
