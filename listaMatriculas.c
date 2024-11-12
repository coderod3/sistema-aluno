//
// Created by rodri on 23/10/2024.
//
#include "listaMatriculas.h"
#include <stdio.h>
#include <stdlib.h>

Node* buscaLinear(const Lista *lista, const int RA) { // nao usado
    Node *node = lista->head;
    while (node != NULL && node->registro->aluno->RA != RA) {
        node = node->next;

        if (node != NULL) {
            //printf("\n%d : %d\n", node->registro->aluno->RA, RA);
        }
    }
    return node;
}

void display(Lista *lista) {
    Node *node = lista->head;
    printf("\nCod:  Aluno:    Telefone:      | Grade:");

    while (node != NULL) { // loop para cada aluno
        printf("\n%d      %s    %s |  ", node->registro->aluno->RA,
            node->registro->aluno->nome, node->registro->aluno->telefone);
        // loop de cada materia por aluno
        for (int i = 0; i < node->registro->grade->num_disciplinas; i++) {
            printf("%d %s  ", node->registro->grade->disciplinas[i].etapa, node->registro->grade->disciplinas[i].disciplina);
        }
        node = node->next;
    }
}

void inserir(Lista *lista, Node *novo_node) {
    if (lista->head != NULL) {
        lista->tail->next = novo_node;
        novo_node->prev = lista->tail;
        novo_node->next = NULL;
        lista->tail = novo_node;
        //printf("Inserido em tail.\n");
    } else {
        lista->head = novo_node;
        lista->tail = novo_node;
        //printf("\nInserido em head...\n");
    }
    printf("Inserido item em lista.\n");
    lista->size++;
}

void remover(Lista *lista, const int codigo) {
    Node *registro = buscaBinaria(lista, codigo);
    if (registro) {
        if (registro->prev) {
            registro->prev->next = registro->next;
        }
        if (registro->next) {
            registro->next->prev = registro->prev;
        }
        if (lista->head == registro) {
            lista->head = registro->next;
        }
        if (lista->tail == registro) {
            lista->tail = registro->prev;
        }

        printf("\nAluno %s removido.\n", registro->registro->aluno->nome);
        free(registro);
    }
    else {
        printf("Aluno nao encontrado.");
    }
    lista->size--;
}

Node* buscaBinaria(Lista *lista, int RA_desejado) {
    int inicio = 0, index_meio = 0;
    int fim = lista->size - 1;
    Node *node_meio;

    while (inicio <= fim) {
        index_meio = inicio + ((fim - inicio) / 2);
        node_meio = lista->head;

        // loop para verificar o valor do meio
        for (int i = 0; i < index_meio; i++) {
            if (node_meio->next != NULL) {
                node_meio = node_meio->next;
            }
        }

        int ra_meio = node_meio->registro->aluno->RA;
        if (ra_meio == RA_desejado) {
            return node_meio;  // Encontrou o RA
        }

        if (ra_meio > RA_desejado) {
            fim = index_meio - 1;
        }
        else {
            inicio = index_meio + 1;
        }
    }
    return NULL;
}

void selectionSort(Lista *lista) {
    Node *node_atual = lista->head;

    while (node_atual != NULL) {
        // declaracoes
        int menor_RA = node_atual->registro->aluno->RA;;
        Node *node_auxiliar = node_atual;
        Node *menor_node = node_atual;

        while(node_auxiliar != NULL) {  // econtrando o menor RA

            if(node_auxiliar->registro->aluno->RA < menor_RA) {
                menor_RA = node_auxiliar->registro->aluno->RA;
                menor_node = node_auxiliar;
            }
            node_auxiliar = node_auxiliar->next;
        }

        // troca de registros - colocando o menor na posicao do atual
        Matricula *matricula_temp = node_atual->registro;
        node_atual->registro = menor_node->registro;
        menor_node->registro = matricula_temp;

        node_atual = node_atual->next;
    }
}
