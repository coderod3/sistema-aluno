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

void remover(Lista *lista, const int codigo) {
    // Trocar para busca binária
    Node *registro = buscaBinaria(lista, codigo);
    if (registro != NULL) {
        if (registro->prev) registro->prev->next = registro->next;
        if (registro->next) registro->next->prev = registro->prev;
        if (lista->head == registro) lista->head = registro->next;
        if (lista->tail == registro) lista->tail = registro->prev;
        printf("\nAluno %d removido.\n", registro->registro->aluno->RA);
        free(registro);
    }
    lista->size--;
}

void inserir(Lista *lista1, Node *novo_node) {
    if (lista1->head != NULL) {
        lista1->tail->next = novo_node;
        novo_node->prev = lista1->tail;
        novo_node->next = NULL;
        lista1->tail = novo_node;
        //printf("Inserido em tail.\n");
    } else {
        lista1->head = novo_node;
        lista1->tail = novo_node;
        printf("\nInserindo em lista encadeada...\n");
    }
    lista1->size++;
}

void display(Lista *lista) {
    Node *node = lista->head;
    printf("\nAluno:   |    Grade:");

    while (node != NULL) {
        printf("\n---------|-----------------------------------------------  \n%s   |  ", node->registro->aluno->nome);

        for (int i = 0; i < node->registro->grade->num_disciplinas; i++) {
            printf("  %s", node->registro->grade->disciplinas[i].disciplina);
        }
        node = node->next;
    }
}

void selectionSort(Lista *lista) {
    Node *nodeAtual = lista->head;

    while(nodeAtual != NULL) { // loop para percorrer a lista um-a-um
        int RA = nodeAtual->registro->aluno->RA;
        Node *menorEncontrado = nodeAtual;
        Node *node_de_comparacao = nodeAtual->next;
        
        while (node_de_comparacao != NULL) { // loop para encontrar o mínimo
            if (node_de_comparacao->registro->aluno->RA < RA) {
                RA = node_de_comparacao->registro->aluno->RA;
                menorEncontrado = node_de_comparacao;
            }
            node_de_comparacao = node_de_comparacao->next;
        }

        // trocar de posição
        Matricula * temp = nodeAtual->registro;
        nodeAtual->registro = menorEncontrado->registro;
        menorEncontrado->registro = temp;

        nodeAtual = nodeAtual->next;
    }
}

Node* buscaBinaria(Lista *lista, int procurado) {
    int inicio = 0, index_meio = 0;
    int fim = lista->size - 1;

    Node *node = lista->head;

    while (inicio <= fim) {
        index_meio = inicio + ((fim - inicio) / 2);
        node = lista->head;

        for (int i = 0; i < index_meio; i++) {
            if (node->next != NULL) {
                node = node->next;
            }
        }

        int raAtual = node->registro->aluno->RA;
        if (raAtual == procurado) {
            return node;  // Achou o RA
        }

        if (raAtual > procurado) {
            fim = index_meio - 1;
        }
        else {
            inicio = index_meio + 1;
        }
    }

    return NULL;
}


