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
    char status[50]; // ”aguardando", “em andamento","finalizado" ou "cancelado"
    struct No *proximo;  // Ponteiro para o próximo nó
} No;

typedef struct Fila {
    char nome[50];
    No *inicio; // Ponteiro para o inicio da fila
    No *fim; // Ponteiro para o final
    int tamanho; // Tamanho da fila
    int limite; // Limite da fila
} Fila;

//PUBLICOS
int id_contador;

//LISTAS
Fila *fila_espera = NULL;
Fila *fila_andamento = NULL;
Fila *fila_finalizados = NULL;
Fila *historico = NULL;

Fila* criarFila(int limite);
//Para limpar o terminal, facilitando a leitura (falta ajustes)
void limpa_terminal();

//Verifica se a Fila está vazia
bool isEmpty(No* no);

//criar nó
No* criar_no();

No* remover_fila(Fila *fila);

//inserir na fila
void inserir_fila(Fila *fila,int id,char *nome_animal,char *nome_tutor,char *servico,char *status);

void inserir_pilha(Fila *fila,int id,char *nome_animal,char *nome_tutor,char *servico,char *status);

//Imprime todos os animais na lista de espera
void listar_animais(int opcao);

void imprimir_dados(No *atual);

//Função para liberar fila
void liberar_fila(No *fila);

// Função para capturar dados do usuário
void entrada_dados(char *buffer, size_t tamanho) ;

int escolher_servico(char *servico);

void cadastrar_novo_animal();

void modificar_cadastro();

void iniciar_servico();

void finalizar_servico();

void cancelar_servico();

void adcionar_no_historico(No *item, char *estado);

void entregar_animais();





int main() {
    fila_espera = criarFila(0);
    fila_andamento = criarFila(3);
    fila_finalizados = criarFila(3);
    historico = criarFila(0);

    id_contador = 0;
    while (1) {
        limpa_terminal();
        int opcao;

        // Exibe o menu de opções
        printf("----------------------------------------------------------\n");
        printf("Escolha uma opcao:\n");
        printf("[1] - Cadastrar Novo Animal\n");
        printf("[2] - Listar Animais\n");
        printf("[3] - Cancelar Serviço\n");
        printf("[4] - Modificar Animal da lista de espera\n");
        printf("[5] - Iniciar Serviço\n");
        printf("[6] - Finalizar Serviço\n");
        printf("[7] - entregar animais\n"); //Ryan, liste as seguintes opções 0 - espera / 1 - finalizados / 2 - cancelados
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
                printf("qual lista deseja listar?\n1-lista de espera\n2-lista de andamento\n3-lista de finalizados\n4-historico\n");
                int resposta;
                scanf("%d",&resposta);
                getchar();
                listar_animais(resposta);
                break;
            case 3:
                cancelar_servico();
                break;
            case 4:
                modificar_cadastro();
                break;
            case 5:
                iniciar_servico();
                break;
            case 6:
                finalizar_servico();
                break;
            case 7:
                entregar_animais();
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


//Função para remover o primeiro nó da fila, e retornar o nó removido;
No* remover_fila(Fila *fila){
    No * atual = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    return atual;
}

Fila* criarFila(int limite) {
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    fila->limite = limite;
    return fila;
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
void inserir_fila(Fila *fila,int id,char *nome_animal,char *nome_tutor,char *servico,char *status){
    No* novo_no = criar_no();
    novo_no->id = id;
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->servico, servico);
    strcpy(novo_no->status, status);
    novo_no->proximo = NULL;
    if(isEmpty(fila->inicio)){
        fila->inicio = novo_no;
        fila->fim = novo_no;
        return;
    }
    fila->fim->proximo = novo_no;
    fila->fim = novo_no;
}
void inserir_pilha(Fila *fila,int id,char *nome_animal,char *nome_tutor,char *servico,char *status) {
    No* novo_no = criar_no();
    novo_no->id = id;
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->servico, servico);
    strcpy(novo_no->status, status);
    novo_no->proximo = fila->inicio;
    if(isEmpty(fila->inicio)){
        fila->inicio = novo_no;
        fila->fim = novo_no;
        return;
    }
    fila->inicio = novo_no;
}

//Imprime todos os animais na lista de espera
void listar_animais(int opcao){
    No *atual;
    switch (opcao) {
            //Fila de Espera
            case 1:
                atual = fila_espera->inicio;
                printf("Animais em espera: %i", fila_espera->tamanho);
                break;
            //Fila Andamento
            case 2:
                atual = fila_andamento->inicio;
                printf("Animais em andamento: %i", fila_andamento->tamanho);
                break;
            //Fila Finalizados
            case 3:
                atual = fila_finalizados->inicio;
                printf("Animais em finalizados: %i",fila_finalizados->tamanho);
                break;
            //Historico
            case 4:
                atual = historico->inicio;
                printf("Animais em finalizados: %i",historico->tamanho);
                break;
            default:
                // Opção inválida
                printf("opcao invalida. voltando pro menu.\n");
                return;
    }
    limpa_terminal();
    if(isEmpty(atual)){
         printf("Fila Vazia\n");
         return;
    }
    while (atual != NULL) {
        imprimir_dados(atual);
        atual = atual->proximo;
    }
}
void imprimir_dados(No *atual){
    printf("\n-----------------------------------\n");
    printf("ID: %d\nNome Tutor: %s\nNome Animal: %s\nServiço: %s\nStatus: %s", atual->id,atual->nome_tutor, atual->nome_animal,atual->servico,atual->status);
    printf("\n------------------------------------\n");
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
            case 1:
                strcpy(servico, "Tosa");
                return 0;
            case 2:
                strcpy(servico, "Ambos");
                return 0;
            case 3:
                return 1;
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
    char status[50];
    printf("Digite o nome do tutor: ");
    entrada_dados(nome_tutor,sizeof(nome_tutor));
    printf("Digite o nome do animal: ");
    entrada_dados(nome_animal,sizeof(nome_animal));
    //Verifica se o usuário decidiu sair
    if(escolher_servico(servico) != 1){
        strcpy(status,"aguardando");
        inserir_fila(fila_espera,id_contador,nome_animal,nome_tutor,servico,status);
        id_contador++;
        fila_espera->tamanho++;
    }
}
void modificar_cadastro() {
    printf("qual cadastro deseja moficar?\n");
    listar_animais(1);
    printf("selecione o id:\n");
    int resposta;
    scanf("%d",&resposta);
    getchar();
    No *aux = fila_andamento->inicio;
    for (int i = 0; i < fila_andamento->tamanho; i++){
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
void iniciar_servico(){
    if(isEmpty(fila_espera->inicio)){
        printf("Nenhum animal na fila de espera\n");
        return;
    }
    limpa_terminal();
    printf("\n-----------------------------------\n");
    printf("O proximo animal a ser atendido é:");
    No *atual = fila_espera->inicio;
    imprimir_dados(atual);
    while (1){
        printf("Deseja iniciar o serviço? [1] Sim [2] Não\n");
        int resposta;
        scanf("%d",&resposta);
        getchar();
        switch (resposta){
            case 1:
                if((fila_andamento->tamanho == fila_andamento->limite)){
                    printf("Limite de animais em atendimento atingido\n");
                    return;
                }
                No* animal = remover_fila(fila_espera);
                strcpy(animal->status, "em andamento");
                inserir_fila(fila_andamento,animal->id,animal->nome_animal,animal->nome_tutor,animal->servico,animal->status);
                free(animal);
                fila_espera->tamanho--;
                fila_andamento->tamanho++;
                printf("Serviço iniciado com sucesso!\n");
                return;
            case 2:
                return;
            default:
                printf("Opção inválida\n");
                break;
        }
    }

}
void finalizar_servico() {
    if(isEmpty(fila_andamento->inicio)){
        printf("Nenhum animal em andamento\n");
        return;
    }
    limpa_terminal();
    printf("\n-----------------------------------\n");
    printf("O proximo animal a ser finalizado é:");
    No *atual = fila_andamento->inicio;
    imprimir_dados(atual);
    while (1){
        printf("Deseja iniciar o serviço? [1] Sim [2] Não\n");
        int resposta;
        scanf("%d",&resposta);
        getchar();
        switch (resposta){
            case 1:
                if((fila_finalizados->tamanho == fila_finalizados->limite)){
                    printf("Limite de animais em atendimento atingido\n");
                    return;
                }
                No* animal = remover_fila(fila_andamento);
                strcpy(animal->status, "em andamento");
                inserir_pilha(fila_finalizados,animal->id,animal->nome_animal,animal->nome_tutor,animal->servico,animal->status);
                free(animal);

            fila_andamento->tamanho--;
                fila_finalizados->tamanho++;
                printf("Serviço iniciado com sucesso!\n");
                return;
            case 2:
                return;
            default:
                printf("Opção inválida\n");
            break;
        }
    }

}

void cancelar_servico(){
    if(isEmpty(fila_espera->inicio)){
        printf("Nenhum animal em espera\n");
        return;
    }
    int id;
    No *atual = fila_espera->inicio;
    No *anterior = NULL;
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("AVISO: O cancelamento dos serviços só pode ser feito antes do serviço está em andamento.\n");
    printf("Qual serviço deseja cancelar?: \n");
    listar_animais(1);
    scanf("%d", &id);
    getchar();
    while (atual != NULL){
       if(atual->id == id){
            if(strcmp(atual->status,"em andamento") == 0 ){
                printf("O cancelamento dos serviços só pode ser feito antes do serviço está em andamento.");
                return;
            }
            if(anterior == NULL){
                fila_espera->inicio = atual->proximo;
            }else{
                anterior->proximo = atual->proximo;
            }
            imprimir_dados(atual);
            inserir_fila(historico, atual->id, atual->nome_animal,atual->nome_tutor, atual->servico, "cancelado" );
            free(atual);
            printf("Serviço cancelado com sucesso!\n");
            fila_espera->tamanho--;
            return;
       }
       anterior = atual;
       atual = atual->proximo;
    }
    printf("ID de serviço não encontrado!\n");
}

void entregar_animais() {
    if(fila_finalizados->tamanho != fila_finalizados->limite) {
        printf("ainda nao tem 3 animais a serem entregues\n");
        return;
    }
    No *atual = fila_finalizados->inicio;
    for(int i = 0; i < fila_finalizados->tamanho; i++) {
        inserir_fila(historico, atual->id, atual->nome_animal,atual->nome_tutor, atual->servico, "entregue" );
        atual = atual->proximo;
    }
    liberar_fila(fila_finalizados->inicio);
    fila_finalizados->inicio = NULL;
    fila_finalizados->tamanho = 0;
}
