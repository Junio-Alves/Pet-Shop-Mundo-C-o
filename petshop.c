/*
    Membros:
        - Ryan de Oliveira
        - Francisco Junio Alves Barros
    GitHub:
        https://github.com/Junio-Alves/Pet-Shop-Mundo-C-o
    Descrição:
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
typedef struct No
{
    int id;               // ID
    char nome_animal[50]; // Nome do Animal
    char nome_tutor[50];  // Nome do tutor
    char tipo_animal[10]; // [0] gato, [1] cachorro
    char servico[50];     // [0] banho, [1] tosa ou [2] ambos
    char status[50];      // ”aguardando", “em andamento","finalizado" ou "cancelado"
    struct No *proximo;   // Ponteiro para o próximo nó
} No;

typedef struct Fila
{
    char nome[50];
    No *inicio;  // Ponteiro para o inicio da fila
    No *fim;     // Ponteiro para o final
    int tamanho; // Tamanho da fila
    int limite;  // Limite da fila
} Fila;

// PUBLICOS
int id_contador;

// LISTAS
Fila *fila_espera = NULL;
Fila *fila_andamento = NULL;
Fila *fila_finalizados = NULL;
Fila *historico = NULL;

Fila *criarFila(int limite);
// Para limpar o terminal, facilitando a leitura (falta ajustes)
void limpa_terminal();

// Verifica se a Fila está vazia
bool isEmpty(No *no);

// criar nó
No *criar_no();

No *remover_fila(Fila *fila, int id_servico);

// inserir na fila
void inserir_fila(Fila *fila, int id, char *nome_animal, char *nome_tutor, char *tipo_animal, char *servico, char *status);

void inserir_pilha(Fila *fila, int id, char *nome_animal, char *nome_tutor, char *servico, char *status);

// Imprime todos os animais na lista de espera
void listar_animais(int opcao);

void imprimir_dados(No *atual);

// Função para liberar fila
void liberar_fila(No *fila);

// Função para capturar dados do usuário
void entrada_dados(char *buffer, size_t tamanho);

int escolher_servico(char *servico);

void cadastrar_novo_animal();

void modificar_cadastro();

void iniciar_servico();

void finalizar_servico();

void cancelar_servico();

void entregar_animais();

void lista_menu();

void mover_de_fila(Fila *fila_origem, Fila *fila_destino, int id_servico, char *novo_status);

void aperte_uma_tecla();

int main()
{
    fila_espera = criarFila(0);
    fila_andamento = criarFila(3);
    fila_finalizados = criarFila(3);
    historico = criarFila(0);

    id_contador = 0;
    while (1)
    {
        limpa_terminal();
        int opcao;

        // Exibe o menu de opções
        printf("----------------------------------------------------------\n");
        printf("Escolha uma opcao:\n");
        printf("[1] - Cadastrar Novo Animal/Serviço\n");
        printf("[2] - Listar Animais\n");
        printf("[3] - Cancelar Serviço\n");
        printf("[4] - Modificar Animal da lista de espera\n");
        printf("[5] - Iniciar Serviço\n");
        printf("[6] - Finalizar Serviço\n");
        printf("[7] - Entregar animais\n");
        printf("[0] - Sair\n");
        printf("Opcao: ");
        printf("----------------------------------------------------------\n");
        scanf("%i", &opcao);
        getchar();

        // Processa a escolha do usuário
        switch (opcao)
        {
        case 1:
            cadastrar_novo_animal();
            break;
        case 2:
            lista_menu();
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

// Função para remover o primeiro nó da fila, e retornar o nó removido;
No *remover_fila(Fila *fila, int id_servico){
    No *atual = fila->inicio;
    No *anterior = NULL;
    while (atual != NULL){
        if(atual->id == id_servico){
            if(anterior == NULL){
                fila->inicio = atual->proximo;
            }else{
                anterior->proximo = atual->proximo;
            }
            return atual;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("ID de serviço não encontrado! [remover]\n");
}

void mover_de_fila(Fila *fila_origem, Fila *fila_destino, int id_servico, char *novo_status){
    // Verifica se a fila de origem está vazia
    // Filas com limite 0 não possuem limite.
    if(fila_destino->limite != 0 && fila_destino->tamanho == fila_destino->limite){
        printf("Limite da fila antigido\n");
        return;
    }
    No *atual = fila_origem->inicio;
    while (atual != NULL){
        if(atual->id == id_servico){
            No *animal = remover_fila(fila_origem, id_servico);
            if(animal == NULL){
                printf("Erro ao mover animal\n");
                return;
            }
            strcpy(animal->status, novo_status);
            inserir_fila(fila_destino, animal->id, animal->nome_animal, animal->nome_tutor, animal->tipo_animal, animal->servico, animal->status);
            free(animal);
            fila_origem->tamanho--;
            fila_destino->tamanho++;
            return;
        }
        atual = atual->proximo;
    }
    printf("ID de serviço não encontrado! [mover]\n");
}

Fila *criarFila(int limite){
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
    fila->limite = limite;
    return fila;
}

// Para limpar o terminal, facilitando a leitura (falta ajustes)
void limpa_terminal(){
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
    }
}

void lista_menu(){
    limpa_terminal();
    while (1){
        int resposta;
        printf("----------------------------------------------------------\n");
        printf("Qual lista deseja exibir?\n[1]-Lista de Espera\n[2]-Lista de Andamento\n[3]-Lista de Finalizados\n[4]-Historico\n[0]-Sair\n");
        printf("----------------------------------------------------------\n");
        scanf("%d", &resposta);
        getchar();
        if(resposta == 0) return;
        if(resposta < 1 || resposta > 4){
            printf("Valor invalido!Escolha entre 0 e 4.\n");
        }else{

            listar_animais(resposta);
            aperte_uma_tecla();
        }
    }
}

// Verifica se a Fila está vazia
bool isEmpty(No *no)
{
    if (no == NULL)
    {
        return true;
    }
    return false;
}

// Para pausar a execução até que o usuário pressione uma tecla
void aperte_uma_tecla(){
    printf("Pressione qualquer tecla para continuar....\n");
    getchar();
}

// criar nó
No *criar_no(){
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL)
    {
        printf("Erro na alocação do Nó!");
        return 0;
    }
    return novo_no;
}

// inserir na fila
void inserir_fila(Fila *fila, int id, char *nome_animal, char *nome_tutor, char *tipo_animal, char *servico, char *status)
{
    No *novo_no = criar_no();
    novo_no->id = id;
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->tipo_animal, tipo_animal);
    strcpy(novo_no->servico, servico);
    strcpy(novo_no->status, status);
    novo_no->proximo = NULL;
    if (isEmpty(fila->inicio))
    {
        fila->inicio = novo_no;
        fila->fim = novo_no;
        return;
    }
    fila->fim->proximo = novo_no;
    fila->fim = novo_no;
}

void inserir_pilha(Fila *fila, int id, char *nome_animal, char *nome_tutor, char *servico, char *status)
{
    No *novo_no = criar_no();
    novo_no->id = id;
    strcpy(novo_no->nome_animal, nome_animal);
    strcpy(novo_no->nome_tutor, nome_tutor);
    strcpy(novo_no->servico, servico);
    strcpy(novo_no->status, status);
    novo_no->proximo = fila->inicio;
    if (isEmpty(fila->inicio))
    {
        fila->inicio = novo_no;
        fila->fim = novo_no;
        return;
    }
    fila->inicio = novo_no;
}
// Imprime todos os animais na lista de espera
void listar_animais(int opcao)
{
    limpa_terminal();
    No *atual;
    switch (opcao)
    {
    // Fila de Espera
    case 1:
        atual = fila_espera->inicio;
        printf("Animais em espera: %i\n", fila_espera->tamanho);
        break;
    // Fila Andamento
    case 2:
        atual = fila_andamento->inicio;
        printf("Animais em andamento: %i\n", fila_andamento->tamanho);
        break;
    // Fila Finalizados
    case 3:
        atual = fila_finalizados->inicio;
        printf("Animais em finalizados: %i\n", fila_finalizados->tamanho);
        break;
    // Historico
    case 4:
        atual = historico->inicio;
        printf("Historico: %i\n", historico->tamanho);
        break;
    default:
        // Opção inválida
        printf("opcao invalida. voltando pro menu.\n");
        return;
    }
    if (isEmpty(atual))
    {
        printf("Fila Vazia\n");
        return;
    }
    while (atual != NULL)
    {
        imprimir_dados(atual);
        atual = atual->proximo;
    }
}

void imprimir_dados(No *atual)
{
    printf("\n-----------------------------------\n");
    printf("ID: %d\nNome Tutor: %s\nNome Animal: %s\nTipo de Animal: %s\nServiço: %s\nStatus: %s", atual->id, atual->nome_tutor, atual->nome_animal,atual->tipo_animal,  atual->servico, atual->status);
    printf("\n------------------------------------\n");
}
// Função para liberar fila
void liberar_fila(No *fila)
{
    No *atual = fila;
    while (atual != NULL)
    {
        No *proximo = atual->proximo; // Armazena o próximo nó
        free(atual);                  // Libera o nó atual
        atual = proximo;              // Avança para o próximo nó
    }
}
// Função para capturar dados do usuário
void entrada_dados(char *buffer, size_t tamanho)
{
    if (fgets(buffer, tamanho, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n' capturado
    }
}

int escolher_servico(char *servico)
{
    while (1)
    {
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
        switch (opcao)
        {
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

void cadastrar_novo_animal()
{
    limpa_terminal();
    char nome_animal[50];
    char nome_tutor[50];
    char tipo_animal[10];
    char servico[50];
    char status[50];
    do {
        printf("Digite o nome do tutor: ");
        entrada_dados(nome_tutor, sizeof(nome_tutor));
        if (strlen(nome_tutor) < 3) {
            printf("Nome do tutor ndever ter ao minimo 3 caracteres!\n");
        }
    } while (strlen(nome_tutor) < 3);

    do {
        printf("Digite o nome do animal: ");
        entrada_dados(nome_animal, sizeof(nome_animal));
        if (strlen(nome_animal) < 3) {
            printf("Nome do animal dever ter ao minimo 3 caracteres!\n");
        }
    }while (strlen(nome_animal) < 3);
    int opcao = 0;
    while(opcao>2 || opcao<1) {
        printf("Qual é o tipo de animal?\n[1]gato [2]cahorro\n");
        scanf("%i", &opcao);
        getchar();
        if(opcao>2 || opcao<1) {
            printf("opcao invalida\n");
        }
    }
    if(opcao == 1) {
        strcpy(tipo_animal, "gato");
    }else {
        strcpy(tipo_animal, "cachorro");
    }
    // Verifica se o usuário decidiu sair
    if (escolher_servico(servico) != 1)
    {
        strcpy(status, "aguardando");
        inserir_fila(fila_espera, id_contador, nome_animal, nome_tutor, tipo_animal, servico, status);
        id_contador++;
        fila_espera->tamanho++;
    }
}

void modificar_cadastro()
{
    printf("qual cadastro deseja moficar?\n");
    listar_animais(1);
    printf("selecione o id:\n");
    int resposta;
    scanf("%d", &resposta);
    getchar();
    No *atual = fila_espera->inicio;
    while (atual != NULL)
    {
        if (atual->id != resposta)
        {
            atual = atual->proximo;
        }
        else
        {
            char nome_animal[50];
            char nome_tutor[50];
            char tipo_animal[10];
            char servico[50];
            printf("Digite o nome do tutor: ");
            entrada_dados(nome_tutor, sizeof(nome_tutor));
            printf("Digite o nome do animal: ");
            entrada_dados(nome_animal, sizeof(nome_animal));
            int opcao = 0;
            while(opcao>2 || opcao<1) {
                printf("[1]gato [2]cahorro\n");
                scanf("%i", &opcao);
                getchar();
                if(opcao>2 || opcao<1) {
                    printf("opcao invalida\n");
                }
            }
            if(opcao == 1) {
                strcpy(tipo_animal, "gato");
            }else {
                strcpy(tipo_animal, "cachorro");
            }
            if (escolher_servico(servico) != 1)
            {
                strcpy(atual->nome_animal, nome_animal);
                strcpy(atual->nome_tutor, nome_tutor);
                strcpy(atual->servico, servico);
            }
            return;
        }
    }
    printf("id nao encotrado\n");
}

void iniciar_servico()
{
    if (isEmpty(fila_espera->inicio))
    {
        printf("Nenhum animal na fila de espera\n");
        aperte_uma_tecla();
        return;
    }
    if ((fila_andamento->tamanho == fila_andamento->limite))
    {
        printf("Limite de animais em atendimento atingido\n");
        aperte_uma_tecla();
        return;
    }
    limpa_terminal();
    printf("\n-----------------------------------\n");
    printf("O proximo animal a ser atendido é:");
    No *atual = fila_espera->inicio;
    imprimir_dados(atual);
    while (1)
    {
        printf("Deseja iniciar o serviço? [1] Sim [2] Não\n");
        int resposta;
        scanf("%d", &resposta);
        getchar();
        switch (resposta)
        {
        case 1:
            mover_de_fila(fila_espera, fila_andamento, atual->id, "em andamento");
            printf("Serviço iniciado com sucesso!\n");
            aperte_uma_tecla();
            return;
        case 2:
            return;
        default:
            printf("Opção inválida\n");
            break;
        }
    }
}

void finalizar_servico()
{
    if (isEmpty(fila_andamento->inicio))
    {
        printf("Nenhum animal em andamento\n");
        aperte_uma_tecla();
        return;
    }
    if (fila_finalizados->tamanho == fila_finalizados->limite)
    {
        printf("pilha de entrega ja esta cheia\n");
        aperte_uma_tecla();
        return;
    }
    limpa_terminal();
    int id;
    No *atual = fila_andamento->inicio;
    No *anterior = NULL;
    printf("\n-----------------------------------\n");
    printf("Qual serviço deseja Finalizar?: \n");
    listar_animais(2);
    scanf("%d", &id);
    getchar();
    while (atual != NULL){
        if(atual->id == id){
            while (1){
                printf("Deseja finalizar o serviço? [1] Sim [2] Não\n");
                int resposta;
                scanf("%d", &resposta);
                getchar();
                switch (resposta)
                {
                case 1:
                    No *animal = remover_fila(fila_andamento, atual->id);
                    strcpy(animal->status, "em andamento");
                    inserir_pilha(fila_finalizados, animal->id, animal->nome_animal, animal->nome_tutor, animal->servico, animal->status);
                    fila_andamento->tamanho--;
                    fila_finalizados->tamanho++;
                    printf("Serviço finalizado com sucesso!\n");
                    aperte_uma_tecla();
                    return;
                case 2:
                    return;
                default:
                    printf("Opção inválida\n");
                    break;
                }
            }
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("ID de serviço não encontrado!\n");
}

void cancelar_servico()
{
    if (isEmpty(fila_espera->inicio))
    {
        printf("Nenhum animal em espera\n");
        return;
    }
    int id;
    No *atual = fila_espera->inicio;
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("AVISO: O cancelamento dos serviços só pode ser feito antes do serviço está em andamento.\n");
    printf("Qual serviço deseja cancelar?: \n");
    listar_animais(1);
    scanf("%d", &id);
    getchar();
    while (atual != NULL){
        if (atual->id == id){
            if (strcmp(atual->status, "em andamento") == 0)
            {
                printf("O cancelamento dos serviços só pode ser feito antes do serviço está em andamento.");
                return;
            }
            mover_de_fila(fila_espera, historico, atual->id, "cancelado");
            imprimir_dados(atual);
            printf("Serviço cancelado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("ID de serviço não encontrado! [cancelar] \n");
}

void entregar_animais()
{
    if (fila_finalizados->tamanho < fila_finalizados->limite)
    {
        printf("ainda nao tem 3 animais a serem entregues\n");
        aperte_uma_tecla();
        return;
    }
    No *atual = fila_finalizados->inicio;
    for (int i = 0; i < fila_finalizados->tamanho; i++)
    {
        inserir_fila(historico, atual->id, atual->nome_animal, atual->nome_tutor, atual->tipo_animal, atual->servico, "entregue");
        atual = atual->proximo;
    }
    liberar_fila(fila_finalizados->inicio);
    fila_finalizados->inicio = NULL;
    fila_finalizados->tamanho = 0;
    printf("animais entregues com sucesso\n");
    aperte_uma_tecla();
}
