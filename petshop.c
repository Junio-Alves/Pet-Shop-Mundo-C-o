/*
    Implemente um código em C com estruturas de dados e uso dinâmico da memória que seja capaz de manter 
    o controle de entrada e saída de animais (gato ou cachorro), em um pet shop. 
    O código deve representar os animais através de uma struct com os seguintes membros: nome, tutor, serviço e status. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definição da estrutura do nó
// nome, tutor, serviço e status.
typedef struct No {
    char nome_animal[50];      // Nome do estudante
    char nome_tutor[50];  // Nome do tutor
    char servico[50]; // [0] banho, [1] tosa ou [2] ambos
    int status; // ”aguardando", “em andamento" ou "finalizado"
    struct No *proximo;  // Ponteiro para o próximo nó
} No;

typedef struct fila{
    struct No *inicio;
    struct No *fim;
}FILA;

No* inicio = NULL;

void limpa_terminal(){
    for (int i = 0; i < 10; i++) {
        printf("\n");
    }
}

bool isEmpty(FILA *fila){
    if(fila->inicio->proximo == NULL){
        return true;
    }
    return false;
}

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
void inserir_fila(char *nome_animal,char *nome_tutor,char *servico){
    No* novo_no = criar_no(); 
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->servico, servico);
}
//



//Função para liberar fila
void liberar_fila(FILA *fila) {
    No *atual = fila->inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo; // Armazena o próximo nó
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

int escolher_servico(char *servico){
    bool sair = false;
     while (sair != true) {
        limpa_terminal();
        int opcao;

        // Exibe o menu de opções
        printf("----------------------------------------------------------\n");
        printf("Escolha uma serviço:\n");
        printf("[0] - Banho\n");
        printf("[1] - Tosa\n");
        printf("[2] - Ambos\n");
        printf("[3] - Sair\n");
        printf("Opcao: ");
        printf("----------------------------------------------------------\n");
        scanf("%d", &opcao);
        getchar();

        // Processa a escolha do usuário
        switch (opcao) {
            case 0:
                servico = "banho";
                sair = true;
                return 0;
                break;
            case 1:
                servico = "tosa";
                sair = true;
                return 0;
                break;
            case 2:
                servico = "ambos";
                sair = true;
                return 0;
                break;
            case 3:
                sair = true;
                return 1;
                break;
            default:
                // Opção inválida
                printf("Opcao invalida\n");
        }
    }
}

void cadastrar_novo_animal(){
    limpa_terminal();
    char nome_animal[50];
    char nome_tutor[50];
    char servico[50];
    printf("Digite o nome do tutor: ");
    entrada_dados(nome_tutor,sizeof(nome_tutor));
    printf("Digite o nome do animal: ");
    entrada_dados(nome_animal,sizeof(nome_animal));
    //Verifica se o usuário decidiu sair
    if(escolher_servico(servico) != 1){
       inserir_fila(nome_animal,nome_tutor,servico);
    };
    return;
}



int main() {
    while (1) {
        limpa_terminal();
        int opcao;

        // Exibe o menu de opções
        printf("----------------------------------------------------------\n");
        printf("Escolha uma opcao:\n");
        printf("[1] - Cadastrar Novo Animal\n");
        printf("[2] - Ver Animais da lista de espera\n");
        printf("[3] - Remover Animal da lista de espera\n");
        printf("[4] - Modificar Animal da lista de espera\n");
        printf("[5] - Finalizar Animal\n");
        printf("[6] - Listar Animais em serviço\n"); //Ryan, liste as seguintes opções 0 - espera / 1 - finalizados / 2 - cancelados
        printf("[7] - Entregar pets\n");
        printf("[0] - Sair\n");
        printf("Opcao: ");
        printf("----------------------------------------------------------\n");
        scanf("%d", &opcao);
        getchar();

        // Processa a escolha do usuário
        switch (opcao) {
            case 1:
                cadastrar_novo_animal();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 7:
                break;
            case 0:
                // Sai do programa liberando a memória
                printf("Saindo....");
                return 0;
            default:
                // Opção inválida
                printf("Opcao invalida\n");
        }
    }
    return 0;
}
