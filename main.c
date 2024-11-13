#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaMatriculas.h"


//Gabriel Barbosa dos Santos - 841923
//David Camara - 841925
//Rodrigo de Araujo Amaro - 841935

void stringInput(char *str, int size) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = '\0';
}
int inteiroInput() {
    char input[10];

    while (1) {
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        int isNumber = 1;
        for (int i = 0; i < strlen(input); i++) {
            if (!isdigit(input[i])) {
                isNumber = 0;
                break;
            }
        }

        if (isNumber) {
            const int valor = atoi(input);
            return valor;
        }
        printf("Entrada invalida. Por favor, insira um numero inteiro.\n");
    }
}
Lista *preenchimentoAutomatico(Lista *lista1) { // para testes
    // Alocando estruturas dinamicamente:

    // Alocando alunos
    Aluno *aluno1 = (Aluno*)malloc(sizeof(Aluno));
    Aluno *aluno2 = (Aluno*)malloc(sizeof(Aluno));
    Aluno *aluno3 = (Aluno*)malloc(sizeof(Aluno));
    Aluno *aluno4 = (Aluno*)malloc(sizeof(Aluno));
    Aluno *aluno5 = (Aluno*)malloc(sizeof(Aluno));

    // Alocando disciplinas
    Disciplina *disc1 = (Disciplina*)malloc(sizeof(Disciplina));
    Disciplina *disc2 = (Disciplina*)malloc(sizeof(Disciplina));
    Disciplina *disc3 = (Disciplina*)malloc(sizeof(Disciplina));
    Disciplina *disc4 = (Disciplina*)malloc(sizeof(Disciplina));

    // Alocando a grade
    Grade *grade = (Grade*)malloc(sizeof(Grade));

    // Alocando matriculas
    Matricula *matricula1 = (Matricula*)malloc(sizeof(Matricula));
    Matricula *matricula2 = (Matricula*)malloc(sizeof(Matricula));
    Matricula *matricula3 = (Matricula*)malloc(sizeof(Matricula));
    Matricula *matricula4 = (Matricula*)malloc(sizeof(Matricula));
    Matricula *matricula5 = (Matricula*)malloc(sizeof(Matricula));


    // Preenchendo os valores dos alunos com RA, nome e telefone fixo
    aluno1->RA = 3;
    strcpy(aluno1->nome, "paulo3");
    strcpy(aluno1->telefone, "016 997357323");

    aluno2->RA = 5;
    strcpy(aluno2->nome, "paulo5");
    strcpy(aluno2->telefone, "016 996473829");

    aluno3->RA = 4;
    strcpy(aluno3->nome, "paulo4");
    strcpy(aluno3->telefone, "016 995837462");

    aluno4->RA = 2;
    strcpy(aluno4->nome, "paulo2");
    strcpy(aluno4->telefone, "016 998274561");

    aluno5->RA = 1;
    strcpy(aluno5->nome, "paulo1");
    strcpy(aluno5->telefone, "016 997463829");



    // Definindo valores das disciplinas
    disc1->etapa = 1;
    strcpy(disc1->disciplina, "Geografia");
    disc2->etapa = 2;
    strcpy(disc2->disciplina, "Matematica");
    disc3->etapa = 4;
    strcpy(disc3->disciplina, "Historia");
    disc4->etapa = 3;
    strcpy(disc4->disciplina, "Filosofia");

    // Inserindo disciplinas na grade
    grade->disciplinas[0] = *disc1;
    grade->disciplinas[1] = *disc2;
    grade->disciplinas[2] = *disc3;
    grade->disciplinas[3] = *disc4;
    grade->num_disciplinas = 4;

    // Matriculando os alunos na grade (matriculando alunos com a mesma grade para exemplo)
    matricula1->aluno = aluno1;
    matricula1->grade = grade;
    matricula2->aluno = aluno2;
    matricula2->grade = grade;
    matricula3->aluno = aluno3;
    matricula3->grade = grade;
    matricula4->aluno = aluno4;
    matricula4->grade = grade;
    matricula5->aluno = aluno5;
    matricula5->grade = grade;

    // Array de ponteiros de matrículas para adicionar a lista
    Matricula *matriculas[5] = {matricula1, matricula2, matricula3, matricula4, matricula5};

    printf("\nTamanho: %d\n\n", lista1->size);

    for (int i = 0; i < 5; i++) {
        Node *novo_node = (Node*)malloc(sizeof(Node));
        novo_node->prev = NULL;
        novo_node->registro = matriculas[i];
        novo_node->next = NULL;
        inserir(lista1, novo_node);
    }

    //---------------Testes:-----------------//
    printf("\nTamanho: %d\n\nLista Atual:", lista1->size);
    display(lista1); // lista desorganizada

    printf("\n\nAplicando Selection Sort:");
    selectionSort(lista1);
    display(lista1);

    printf("\n\nBuscando com Binary Search:\n");
    int codBusca = 3; // cod de exemplo
    Node *resultado = buscaBinaria(lista1, codBusca);
    printf("\nCod:  Aluno:    Telefone:      | Grade:");
    printf("\n%d      %s    %s |  ", resultado->registro->aluno->RA, resultado->registro->aluno->nome, resultado->registro->aluno->telefone);
    // loop de cada materia do aluno de exemplo
    for (int i = 0; i < resultado->registro->grade->num_disciplinas; i++) {
        printf("%d %s  ", resultado->registro->grade->disciplinas[i].etapa, resultado->registro->grade->disciplinas[i].disciplina);
    }

    return lista1;
}
void menu() {
    printf("\n\n===== MENU =====\n");
    printf("1. Inserir aluno\n");
    printf("2. Remover aluno\n");
    printf("3. Exibir lista\n");
    printf("4. Ordenar lista (Selection Sort)\n");
    printf("5. Consultar aluno (Pesquisa Binaria)\n");
    printf("0. Sair\n");
    printf("================\n");
    printf("Escolha uma opcao: ");
}


int main(void) {
    Lista *lista1 = (Lista*)malloc(sizeof(Lista));
    lista1->head = NULL;
    lista1->tail = NULL;
    lista1->size = 0;

    lista1 = preenchimentoAutomatico(lista1);

    //----------------------------Menu-------------------------------//

    int opcao, RA;
    char nome[50];
    char telefone[15];
    Aluno *novo_aluno;

    do{
        menu();
        opcao = inteiroInput();
        switch (opcao) {
            case 1:  // Inserir aluno
                novo_aluno = (Aluno*)malloc(sizeof(Aluno));
                Grade *grade1 = (Grade*)malloc(sizeof(Grade));
                grade1->num_disciplinas = 0;
                printf("Digite o RA do aluno: ");
                novo_aluno->RA = inteiroInput();

                printf("Digite o nome do aluno: ");
                stringInput(nome, sizeof(nome));
                strcpy(novo_aluno->nome, nome);

                printf("Digite o telefone do aluno: ");
                stringInput(telefone, sizeof(telefone));
                strcpy(novo_aluno->telefone, telefone);

                // preencher grade
                for(int i = 0; i < 8; i++) {
                    Disciplina disciplina;
                    char nome_disciplina[10];

                    printf("Digite a etapa da grade: ");
                    disciplina.etapa = inteiroInput();
                    printf("Digite o nome da disciplina: ");
                    stringInput(nome_disciplina, sizeof(nome_disciplina));
                    strcpy(disciplina.disciplina, nome_disciplina);

                    grade1->disciplinas[grade1->num_disciplinas] = disciplina;
                    grade1->num_disciplinas++;

                    int op;
                    printf("Deseja adicionar mais disciplinas?[sim: 1][nao: 0]");
                    op = inteiroInput();
                    if (op == 0) {
                        break;
                    }
                    if (op != 1) {
                        printf("invalido.");
                    }
                }

                // instanciando matricula
                Matricula *nova_matricula = (Matricula*)malloc(sizeof(Matricula));
                nova_matricula->aluno = novo_aluno;
                nova_matricula->grade = grade1;
                // instanciando node
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
                RA = inteiroInput();
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
                RA = inteiroInput();
                //scanf("%d", &RA);

                Node *resultado =  buscaBinaria(lista1, RA);
                if (resultado != NULL) {
                    printf("\n-----------------------------------------------------\n");
                    printf("ALUNO:\n");
                    printf("  RA    : %d\n", resultado->registro->aluno->RA);
                    printf("  Nome  : %s\n", resultado->registro->aluno->nome);
                    printf("  Telefone  : %s\n", resultado->registro->aluno->telefone);
                    //printf("--------------------------------------------\n");
                    printf("DISCIPLINAS:\n");
                    for (int i = 0; i < resultado->registro->grade->num_disciplinas; i++) {
                        printf("  %d %s, ", resultado->registro->grade->disciplinas[i].etapa, resultado->registro->grade->disciplinas[i].disciplina);
                    }
                    printf("\n-----------------------------------------------------\n");
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
    } while (opcao != 0);
    free(lista1);
    return 0;
}