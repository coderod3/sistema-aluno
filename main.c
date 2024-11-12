#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaMatriculas.h"

void menu() {
    printf("\n\n===== MENU =====\n");
    printf("1. Inserir aluno\n");
    printf("2. Remover aluno\n");
    printf("3. Exibir lista\n");
    printf("4. Ordenar lista (Selection Sort)\n");
    printf("5. Buscar aluno (Pesquisa Binaria)\n");
    printf("6. Sair\n");
    printf("================\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Lista *lista1 = (Lista*)malloc(sizeof(Lista));
    lista1->head = NULL;
    lista1->tail = NULL;
    lista1->size = 0;

    Aluno aluno1 = {3, "paulo3"};
    Aluno aluno2 = {5, "paulo5"};
    Aluno aluno3 = {4, "paulo4"};
    Aluno aluno4 = {2, "paulo2"};
    Aluno aluno5 = {1, "paulo1"};


    Disciplina disc1 = {1, "Geografia"};
    Disciplina disc2 = {2, "Matematica"};
    Disciplina disc3 = {2, "Historia"};
    Disciplina disc4 = {2, "Filosofia"};
    //Disciplina disc2 = {2, "Matematica"};


    Grade grade; // Grade fixa apenas neste exemplo
    grade.disciplinas[0] = disc1;
    grade.disciplinas[1] = disc2;
    grade.disciplinas[2] = disc3;
    grade.disciplinas[3] = disc4;

    grade.num_disciplinas = 4;

    //matriculando 5 alunos na mesma grade
    Matricula matricula1 = {&aluno1, &grade};
    Matricula matricula2 = {&aluno2, &grade};
    Matricula matricula3 = {&aluno3, &grade};
    Matricula matricula4 = {&aluno4, &grade};
    Matricula matricula5 = {&aluno5, &grade};

    Matricula *matriculas[5] = {&matricula1, &matricula2, &matricula3, &matricula4, &matricula5};
    printf("\nTamanho: %d\n", lista1->size);
    for (int i = 0; i < 5; i++) {
        Node *novo_node = (Node*)malloc(sizeof(Node));
        novo_node->prev = NULL;
        novo_node->registro = matriculas[i];
        novo_node->next = NULL;
        inserir(lista1, novo_node);
    }

    printf("\nTamanho: %d\n\nLista Atual:", lista1->size);
    display(lista1);
    printf("\n\nAplicando Selection Sort:");
    selectionSort(lista1);
    display(lista1);
    printf("\n\nBuscando com Binary Search:\n");
    int codBusca = 1;
    Node *resultado = buscaBinaria(lista1, codBusca);
    printf("Cod Busca %d: %s", codBusca, resultado->registro->aluno->nome);

    //------------------fim preenchimento automatico e testes-----------------------//

    //--------------------------------Menu-----------------------------------//
    int opcao, RA;
    char nome[50];
    Aluno *novo_aluno;

    do{
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:  // Inserir aluno
                novo_aluno = (Aluno*)malloc(sizeof(Aluno));
                Grade *grade1 = (Grade*)malloc(sizeof(Grade));
                grade1->num_disciplinas = 0;
                printf("Digite o RA do aluno: ");
                scanf("%d", &novo_aluno->RA);

                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
                strcpy(novo_aluno->nome, nome);

                // preencher grade
                for(int i = 0; i < 8; i++) {
                    Disciplina disciplina;
                    char nome_disciplina[10];

                    printf("Digite a etapa da grade: ");
                    scanf("%d", &disciplina.etapa);
                    printf("Digite o nome da disciplina: ");
                    scanf("%s", nome_disciplina);
                    strcpy(disciplina.disciplina, nome_disciplina);

                    grade1->disciplinas[grade1->num_disciplinas] = disciplina;
                    grade1->num_disciplinas++;

                    int op;
                    printf("Deseja adicionar mais disciplinas?[sim: 1][nao: 0]");
                    scanf("%d", &op);
                    if (op == 0) {
                        break;
                    }
                    if (op != 1) {
                        printf("invalido.");
                    }
                }

                // alocando matricula
                Matricula *nova_matricula = (Matricula*)malloc(sizeof(Matricula));
                nova_matricula->aluno = novo_aluno;
                nova_matricula->grade = grade1;
                // alocando node
                Node *novo_node = (Node*)malloc(sizeof(Node));
                novo_node->prev = NULL;
                novo_node->registro = nova_matricula;
                novo_node->next = NULL;
                // inserindo node aluno
                inserir(lista1, novo_node);
                printf("Aluno inserido com sucesso.\n");
                break;

            case 2:  // Remover aluno
                printf("Digite o RA do aluno que deseja remover: ");
                scanf("%d", &RA);
                remover(lista1, RA);
                break;

            case 3:  // Exibir lista
                printf("\nLista de Alunos:\n");
                display(lista1);
                break;

            case 4:  // Ordenar lista
                selectionSort(lista1);
                printf("\nLista ordenada.\n");
                break;

            case 5:  // Buscar aluno (Pesquisa Binaria)
                printf("Digite o RA do aluno que deseja buscar: ");
                scanf("%d", &RA);

                // Garantir que a lista está ordenada antes de usar busca binária
                Node *resultado =  buscaBinaria(lista1, RA);
                if (resultado != NULL) {
                    printf("Aluno encontrado: %s (RA: %d)\n", resultado->registro->aluno->nome, resultado->registro->aluno->RA);
                } else {
                    printf("Aluno com RA %d nao encontrado.\n", RA);
                }
                break;

            case 6:  // Sair
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    free(lista1);
    return 0;
}