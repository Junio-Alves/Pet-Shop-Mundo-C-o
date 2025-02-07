/*
    Implemente um código em C com estruturas de dados e uso dinâmico da memória que seja capaz de manter 
    o controle de entrada e saída de animais (gato ou cachorro), em um pet shop. 
    O código deve representar os animais através de uma struct com os seguintes membros: nome, tutor, serviço e status. 
*/
#include <stdio.h>

// Definição da estrutura do nó
// nome, tutor, serviço e status.
typedef struct Node {
    char nome[50];      // Nome do estudante
    char tutor[50];  // Nome do tutor
    int servico; // [0] banho, [1] tosa ou [2] ambos
    int status; // ”aguardando", “em andamento" ou "finalizado"
    struct Node *next;  // Ponteiro para o próximo nó
} Node;

//criar nó
//inserir na fila
//



int main() {
    while (1) {
        int opcao;

        // Exibe o menu de opções
        printf("Escolha uma opcao:\n");
        printf("1 - Opção\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        // Processa a escolha do usuário
        switch (opcao) {
            case 1:
                break;
            case 0:
                // Sai do programa liberando a memória
                return 0;
            default:
                // Opção inválida
                printf("Opcao invalida\n");
        }
    }
    return 0;
}
