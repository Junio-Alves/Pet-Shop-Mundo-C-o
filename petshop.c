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
    int id; // ID
    char nome_animal[50];      // Nome do Animal
    char nome_tutor[50];  // Nome do tutor
    char servico[50]; // [0] banho, [1] tosa ou [2] ambos
    char status[50]; // ”aguardando", “em andamento" ou "finalizado"
    struct No *proximo;  // Ponteiro para o próximo nó
} No;

typedef struct Fila {
    No *inicio; // Ponteiro para o inicio da fila
    No *fim; // Ponteiro para o final
    int quamt;
} Fila;

//PUBLICOS
Fila fila;
int id_contador;

Fila Andamento;
Fila Finalizados;

void inicializar_fila();

//Para limpar o terminal, facilitando a leitura (falta ajustes)
void limpa_terminal();

//Verifica se a Fila está vazia
bool isEmpty(No* no);

//criar nó
No* criar_no();

//inserir na fila
void inserir_fila(int id,char *nome_animal,char *nome_tutor,char *servico);

//Imprime todos os animais na lista de espera
void listar_animais(int opcao);


//Função para liberar fila
void liberar_fila(No *fila);

// Função para capturar dados do usuário
void entrada_dados(char *buffer, size_t tamanho) ;

int escolher_servico(char *servico);

void cadastrar_novo_animal();

void modificar_cadastro();

void mover_de_lista();


int main() {
    inicializar_fila();
    id_contador = 0;
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
        printf("[5] - Iniciar Serviço\n");
        printf("[6] - Finalizar Serviço\n");
        printf("[7] - Listar Animais em serviço\n"); //Ryan, liste as seguintes opções 0 - espera / 1 - finalizados / 2 - cancelados
        printf("[8] - Entregar pets\n");
        printf("[0] - Sair\n");
        printf("Opcao: ");
        printf("----------------------------------------------------------\n");
        scanf("%i", &opcao);
        getchar();

        // Processa a escolha do usuário
        switch (opcao) {
            case 1:
                cadastrar_novo_animal();
                break;
            case 2:
                printf("%i",id_contador);
                listar_animais(1);
                break;
            case 3:
                break;
            case 4:
                modificar_cadastro();
                break;
            case 5:
                break;
            case 7:
                printf("qual lista deseja listar?\n1-lista de espera\n2-lista de andamento\n3-lista de finalizados");
                int resposta;
                scanf("%d",&resposta);
                getchar();
                listar_animais(resposta);
                break;
            case 8:
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
}
void inicializar_fila() {
    fila.inicio = NULL;
    fila.fim = NULL;
}


//Para limpar o terminal, facilitando a leitura (falta ajustes)
void limpa_terminal(){
    for (int i = 0; i < 10; i++) {
        printf("\n");
    }
}

//Verifica se a Fila está vazia
bool isEmpty(No* no){
    if(no == NULL){
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
void inserir_fila(int id,char *nome_animal,char *nome_tutor,char *servico){
    No* novo_no = criar_no();
    novo_no->id = id;
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->servico, servico);
    strcpy(novo_no->status, "aguardando");
    novo_no->proximo = NULL;
    if(isEmpty(fila.inicio)){
        fila.inicio = novo_no;
        fila.fim = novo_no;
        return;
    }
    fila.fim->proximo = novo_no;
    fila.fim = novo_no;
}

//Imprime todos os animais na lista de espera
void listar_animais(int opcao){
    No *atual;
    if(opcao == 1) {
        atual = fila.inicio;
    }else if(opcao == 2) {
        atual = Andamento.inicio;
    }else if(opcao == 3) {
        atual = Finalizados.inicio;
    }else {
        printf("opcao invalida. voltando pro menu.\n");
        return;
    }
    limpa_terminal();
    if(isEmpty(atual)){
         printf("Fila Vazia\n");
         return;
    }
    printf("Animais em espera: ");
    while (atual != NULL) {
        printf("\n-------------------------\n");
        printf("ID: %d\nNome Tutor: %s\nNome Animal: %s\nServiço: %s\nStatus: %s", atual->id,atual->nome_tutor, atual->nome_animal,atual->servico,atual->status);
        printf("\n-------------------------");
        atual = atual->proximo;
    }
}



//Função para liberar fila
void liberar_fila(No *fila) {
    No *atual = fila;
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
     while (1) {
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
                strcpy(servico, "Banho");
                return 0;
                break;
            case 1:
                strcpy(servico, "Tosa");
                return 0;
                break;
            case 2:
                strcpy(servico, "Ambos");
                return 0;
                break;
            case 3:
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
       inserir_fila(id_contador,nome_animal,nome_tutor,servico);
       id_contador++;
    };
    return;
}
void modificar_cadastro() {
    printf("qual cadastro deseja moficar?\n");
    listar_animais(1);
    printf("selecione o id:\n");
    int resposta;
    scanf("%d",&resposta);
    getchar();
    No *aux = fila.inicio;
    for (int i = 0; i < 3; i++){
        if(aux->id != resposta) {
            aux = aux->proximo;
        }else {
            char nome_animal[50];
            char nome_tutor[50];
            char servico[50];
            printf("Digite o nome do tutor: ");
            entrada_dados(nome_tutor,sizeof(nome_tutor));
            printf("Digite o nome do animal: ");
            entrada_dados(nome_animal,sizeof(nome_animal));
            if(escolher_servico(servico) != 1){
                strcpy(aux->nome_animal, nome_animal);
                strcpy(aux->nome_tutor, nome_tutor);
                strcpy(aux->servico,servico);
            }
            return;
        }
    }
    printf("id nao encotrado\n");
}
void mover_de_lista() {

}
