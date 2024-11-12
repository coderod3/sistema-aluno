//
// Created by rodri on 23/10/2024.
//

#ifndef LISTAMATRICULAS_H
#define LISTAMATRICULAS_H

typedef struct Aluno {
    int RA;
    char nome[50];
    char telefone[15];
} Aluno;

typedef struct Disciplina {
    int etapa;
    char disciplina[30];
}Disciplina;

typedef struct Grade {
    int num_disciplinas;
    Disciplina disciplinas[8];
} Grade;

typedef struct Matricula {
    Aluno *aluno;
    Grade *grade;
} Matricula;

typedef struct Node {
    struct Node *prev;
    Matricula *registro;
    struct Node *next;
} Node;

typedef struct Lista {
    Node *head;
    Node *tail;
    int size;
} Lista;

Node* buscaRegistro(const Lista *lista, const int RA);
void remover(Lista *lista, const int codigo);
void inserir(Lista *lista, Node *novo_node);
void display(Lista *lista);
void selectionSort(Lista *lista);
Node* buscaBinaria(Lista *lista, int RA);

#endif //LISTAMATRICULAS_H
