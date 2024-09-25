#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIORITARIO 1
#define GERAL 0

#define SAQUE 1
#define DEPOSITO 2
#define EMPRESTIMO 3
#define APLICACAO 4

#define SALDO_INICIAL 1000.00

// Estrutura para armazenar as informações dos clientes
typedef struct Cliente {
    char nome[100];
    int operacao;
    float valor;
    int id;
    struct Cliente *proximo;
} Cliente;

// Estrutura para a fila
typedef struct Fila {
    Cliente *inicio;
    Cliente *fim;
} Fila;

// Função para inicializar uma fila
void inicializarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Função para verificar se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->inicio == NULL;
}

// Função para adicionar um cliente na fila
void enfileirar(Fila *fila, Cliente *cliente) {
    cliente->proximo = NULL;
    if (fila->fim != NULL) {
        fila->fim->proximo = cliente;
    } else {
        fila->inicio = cliente;
    }
    fila->fim = cliente;
}

// Função para remover um cliente da fila
Cliente* desenfileirar(Fila *fila) {
    if (filaVazia(fila)) return NULL;
    Cliente *cliente = fila->inicio;
    fila->inicio = cliente->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    return cliente;
}

// Função para criar um novo cliente
Cliente* criarCliente(char *nome, int operacao, float valor, int id) {
    Cliente *cliente = (Cliente*)malloc(sizeof(Cliente));
    strcpy(cliente->nome, nome);
    cliente->operacao = operacao;
    cliente->valor = valor;
    cliente->id = id;
    cliente->proximo = NULL;
    return cliente;
}

// Função para exibir um cliente
void exibirCliente(Cliente *cliente) {
    printf("ID: %d, Nome: %s, Operacao: %d, Valor: %.2f\n", cliente->id, cliente->nome, cliente->operacao, cliente->valor);
}

// Função para processar operação de saque
void processarSaque(float *saldo, float valor) {
    *saldo -= valor;
    if (*saldo < 0) {
        printf("Saldo - Negativo no caixa\n");
        *saldo += 1000.00;
    }
}

// Função para processar operação de depósito
void processarDeposito(float *saldo, float valor) {
    *saldo += valor;
}

// Função para processar operações e logar no sistema
void processarOperacao(Fila *filaCaixaGeral, Fila *filaCaixaPrioritario, Fila *filaGerenteGeral, Fila *filaGerentePrioritario, Fila *logCaixa, Fila *logGerente, float *saldoCaixa) {
    while (!filaVazia(filaCaixaGeral) || !filaVazia(filaCaixaPrioritario) || !filaVazia(filaGerenteGeral) || !filaVazia(filaGerentePrioritario)) {
        Cliente *cliente;

        // Processar fila prioritária do Caixa
        if (!filaVazia(filaCaixaPrioritario)) {
            cliente = desenfileirar(filaCaixaPrioritario);
            printf("Atendendo Cliente ID: %d no Caixa\n", cliente->id);
            if (cliente->operacao == SAQUE) {
                processarSaque(saldoCaixa, cliente->valor);
            } else if (cliente->operacao == DEPOSITO) {
                processarDeposito(saldoCaixa, cliente->valor);
            }
            enfileirar(logCaixa, cliente);
        }

        // Processar fila geral do Caixa
        if (!filaVazia(filaCaixaGeral)) {
            cliente = desenfileirar(filaCaixaGeral);
            printf("Atendendo Cliente ID: %d Nome: %s no Caixa\n", cliente->id, cliente->nome);
            if (cliente->operacao == SAQUE) {
                processarSaque(saldoCaixa, cliente->valor);
            } else if (cliente->operacao == DEPOSITO) {
                processarDeposito(saldoCaixa, cliente->valor);
            }
            enfileirar(logCaixa, cliente);
        }

        // Processar fila prioritária do Gerente
        if (!filaVazia(filaGerentePrioritario)) {
            cliente = desenfileirar(filaGerentePrioritario);
            printf("Atendendo Cliente ID: %d no Gerente\n", cliente->id);
            if (cliente->operacao == EMPRESTIMO || cliente->operacao == APLICACAO) {
                // Sem alteração de saldo para Gerente
            }
            enfileirar(logGerente, cliente);
        }

        // Processar fila geral do Gerente
        if (!filaVazia(filaGerenteGeral)) {
            cliente = desenfileirar(filaGerenteGeral);
            printf("Atendendo Cliente ID: %d no Gerente\n", cliente->id);
            if (cliente->operacao == EMPRESTIMO || cliente->operacao == APLICACAO) {
                // Sem alteração de saldo para Gerente
            }
            enfileirar(logGerente, cliente);
        }
    }
}

// Função para exibir logs
void exibirLogs(Fila *logCaixa, Fila *logGerente) {
    printf("\nLogs do Caixa:\n");
    Cliente *cliente;
    while (!filaVazia(logCaixa)) {
        cliente = desenfileirar(logCaixa);
        exibirCliente(cliente);
        free(cliente);
    }

    printf("\nLogs do Gerente:\n");
    while (!filaVazia(logGerente)) {
        cliente = desenfileirar(logGerente);
        exibirCliente(cliente);
        free(cliente);
    }
}

int main() {
    Fila filaCaixaGeral, filaCaixaPrioritario, filaGerenteGeral, filaGerentePrioritario;
    Fila logCaixa, logGerente;
    float saldoCaixa = SALDO_INICIAL;
    int opcao, operacao, idade;
    char nome[100];
    float valor;
    int id = 1;

    // Inicializar filas
    inicializarFila(&filaCaixaGeral);
    inicializarFila(&filaCaixaPrioritario);
    inicializarFila(&filaGerenteGeral);
    inicializarFila(&filaGerentePrioritario);
    inicializarFila(&logCaixa);
    inicializarFila(&logGerente);

    do {
        // Exibir menu
        printf("\nMenu:\n");
        printf("1. Adicionar Cliente\n");
        printf("2. Processar Operações\n");
        printf("3. Exibir Logs\n");
        printf("4. Sair\n");
        printf("5. Mostrar Painel\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // Adicionar cliente
                printf("Escolha o recurso (1 - Caixa, 2 - Gerente): ");
                int recurso;
                scanf("%d", &recurso);

                printf("Nome do Cliente: ");
                scanf(" %[^\n]", nome);  // Ler string com espaço

                printf("Operação (1 - Saque, 2 - Depósito, 3 - Empréstimo, 4 - Aplicação): ");
                scanf("%d", &operacao);

                printf("Valor (0 se não aplicável): ");
                scanf("%f", &valor);

                printf("Idade do Cliente (para prioridade): ");
                scanf("%d", &idade);

                Cliente *cliente = criarCliente(nome, operacao, valor, id++);

                if (recurso == 1) {  // Caixa
                    if (idade > 60) {
                        enfileirar(&filaCaixaPrioritario, cliente);
                    } else {
                        enfileirar(&filaCaixaGeral, cliente);
                    }
                } else if (recurso == 2) {  // Gerente
                    if (idade > 60) {
                        enfileirar(&filaGerentePrioritario, cliente);
                    } else {
                        enfileirar(&filaGerenteGeral, cliente);
                    }
                }
                break;

            case 2:
                // Processar operações
                processarOperacao(&filaCaixaGeral, &filaCaixaPrioritario, &filaGerenteGeral, &filaGerentePrioritario, &logCaixa, &logGerente, &saldoCaixa);
                break;

            case 3:
                // Exibir logs
                exibirLogs(&logCaixa, &logGerente);
                break;

            case 4:
                // Sair
                printf("Saindo do sistema.\n");
                break;

            case 5:
                // Exibir filas
                printf("\n***Fila Caixa Geral:***\n\n");
                Cliente *cliente1 = filaCaixaGeral.inicio;
                while (cliente != NULL) {
                    exibirCliente(cliente);
                    cliente = cliente->proximo;
                }

                printf("\n***Fila Caixa Prioritário:***\n\n");
                cliente = filaCaixaPrioritario.inicio;
                while (cliente != NULL) {
                    exibirCliente(cliente);
                    cliente = cliente->proximo;
                }

                printf("\n***Fila Gerente Geral:***\n\n");
                cliente = filaGerenteGeral.inicio;
                while (cliente != NULL) {
                    exibirCliente(cliente);
                    cliente = cliente->proximo;
                }

                printf("\n***Fila Gerente Prioritário:***\n\n");
                cliente = filaGerentePrioritario.inicio;
                while (cliente != NULL) {
                    exibirCliente(cliente);
                    cliente = cliente->proximo;
                }

                break;    

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}
