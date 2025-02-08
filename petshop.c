/*
    Implemente um código em C com estruturas de dados e uso dinâmico da memória que seja capaz de manter 
    o controle de entrada e saída de animais (gato ou cachorro), em um pet shop. 
    O código deve representar os animais através de uma struct com os seguintes membros: nome, tutor, serviço e status. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó
// nome, tutor, serviço e status.
typedef struct No {
    char nome[50];      // Nome do estudante
    char tutor[50];  // Nome do tutor
    int servico; // [0] banho, [1] tosa ou [2] ambos
    int status; // ”aguardando", “em andamento" ou "finalizado"
    struct No *next;  // Ponteiro para o próximo nó
} No;

typedef struct fila{
    struct No *inicio;
    struct No *fim;
}FILA;

No* inicio = NULL;

//criar nó
No* criar_no(){
    No* novo_no = (No*)malloc(sizeof(No));
    if(novo_no == NULL){
        printf("Erro na alocação do Nó!");
        return 0;
    }
    return novo_no;
}
//inserir na fila

//



//Função para liberar fila
void liberar_fila(FILA *fila) {
    No *atual = fila->inicio;
    while (atual != NULL) {
        No *proximo = atual->next; // Armazena o próximo nó
        free(atual);                 // Libera o nó atual
        atual = proximo;             // Avança para o próximo nó
    }
}

// Função para capturar dados do usuário
void entrada_dados(char *buffer, size_t tamanho) {
    if (fgets(buffer, tamanho, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n' capturado
    }
}

int main() {
    while (1) {
        int opcao;

        // Exibe o menu de opções
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar Novo Animal\n");
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
