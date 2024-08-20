#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DISCOS 12
#define MAX_PILHA 4

typedef struct {
    int discos[MAX_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void empilhar(Pilha *p, int valor) {
    if (!pilhaCheia(p)) {
        p->discos[++(p->topo)] = valor;
    } else {
        printf("Pilha cheia!\n");
    }
}

int desempilhar(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->discos[(p->topo)--];
    } else {
        printf("Pilha vazia!\n");
        return -1; // Valor indicando erro
    }
}

int topo(Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->discos[p->topo];
    } else {
        printf("Pilha vazia!\n");
        return -1; // Valor indicando erro
    }
}

void exibirPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia\n");
        return;
    }
    for (int i = 0; i <= p->topo; i++) {
        printf("%d ", p->discos[i]);
    }
    printf("\n");
}

void inicializarDiscos(Pilha pilhas[], int numPilhas) {
    int discos[MAX_DISCOS];
    // Preenche o array de discos com cores aleatórias (1-4)
    for (int i = 0; i < MAX_DISCOS; i++) {
        discos[i] = (i % 4) + 1; // 1 a 4
    }
    // Embaralha os discos
    for (int i = MAX_DISCOS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = discos[i];
        discos[i] = discos[j];
        discos[j] = temp;
    }
    // Distribui os discos nas pilhas
    int index = 0;
    for (int i = 0; i < numPilhas; i++) {
        inicializarPilha(&pilhas[i]);
        for (int j = 0; j < MAX_PILHA && index < MAX_DISCOS; j++) {
            empilhar(&pilhas[i], discos[index++]);
        }
    }
}

void moverDisco(Pilha *origem, Pilha *destino) {
    if (!pilhaVazia(origem)) {
        int disco = desempilhar(origem);
        if (!pilhaCheia(destino)) {
            empilhar(destino, disco);
        } else {
            printf("Pilha destino cheia!\n");
        }
    } else {
        printf("Pilha origem vazia!\n");
    }
}

void jogar(int nivel) {
    Pilha pilhas[4];
    Pilha temp1, temp2;
    int origem, destino, opcao;
    clock_t inicio, fim;
    double tempoGasto;

    //auxiliares
    inicializarPilha(&temp1);
    inicializarPilha(&temp2);

    inicializarDiscos(pilhas, 4);

    printf("Estado inicial das pilhas:\n");//jogo tem 4 colunas para armazenar os pinos
    for (int i = 0; i < 4; i++) {
        printf("Pilha %d: ", i + 1);
        exibirPilha(&pilhas[i]);
    }

    inicio = clock();

    while (1) {
        printf("\nEscolha a operação (1-3) ou 0 para sair:\n");
        printf("1: Mover disco de uma pilha para outra\n");
        printf("2: Mover disco para o temporário e depois para uma pilha\n");
        printf("3: Mover disco de um temporário para uma pilha\n");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        if (opcao == 1) {
            printf("Escolha a pilha de origem (1-4): ");
            scanf("%d", &origem);
            origem--; // Ajusta para índice da pilha

            printf("Escolha a pilha de destino (1-4): ");
            scanf("%d", &destino);
            destino--; // Ajusta para índice da pilha

            if (origem < 0 || origem >= 4 || destino < 0 || destino >= 4 || origem == destino) {
                printf("Escolha inválida. Tente novamente.\n");
                continue;
            }

            moverDisco(&pilhas[origem], &pilhas[destino]);
        } else if (opcao == 2 && nivel != 3) {
            printf("Escolha a pilha de origem (1-4): ");
            scanf("%d", &origem);
            origem--; // Ajusta para índice da pilha

            printf("Escolha a pilha de destino (1-4) ou 0 para o temporário 1: ");
            scanf("%d", &destino);
            
            if (destino == 0) {
                if (!pilhaVazia(&pilhas[origem]) && pilhaVazia(&temp1)) {
                    int disco = desempilhar(&pilhas[origem]);
                    empilhar(&temp1, disco);
                } else {
                    printf("Temporário 1 ocupado ou pilha origem vazia.\n");
                    continue;
                }
            } else {
                destino--; // Ajusta para índice da pilha
                if (destino < 0 || destino >= 4 || origem == destino) {
                    printf("Escolha inválida. Tente novamente.\n");
                    continue;
                }
                if (!pilhaVazia(&temp1)) {
                    moverDisco(&temp1, &pilhas[destino]);
                } else {
                    printf("Temporário 1 vazio.\n");
                }
            }
        } else if (opcao == 3 && nivel != 3) {
            printf("Escolha a pilha de destino (1-4): ");
            scanf("%d", &destino);
            destino--; // Ajusta para índice da pilha

            if (destino < 0 || destino >= 4) {
                printf("Escolha inválida. Tente novamente.\n");
                continue;
            }

            if (!pilhaVazia(&temp1)) {
                moverDisco(&temp1, &pilhas[destino]);
            } else {
                printf("Temporário 1 vazio.\n");
            }
        } else {
            printf("Opção inválida ou nível não permite.\n");
            continue;
        }

        printf("\nEstado atual das pilhas:\n");
        for (int i = 0; i < 4; i++) {
            printf("Pilha %d: ", i + 1);
            exibirPilha(&pilhas[i]);
        }

        if (nivel != 3) {
            printf("Temporário 1: ");
            exibirPilha(&temp1);
            if (nivel == 1) {
                printf("Temporário 2: ");
                exibirPilha(&temp2);
            }
        }
    }

    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.2f segundos\n", tempoGasto);
}

int main() {
    int nivel;

    printf("Escolha o nível do jogo (1-Fácil, 2-Médio, 3-Difícil): ");
    scanf("%d", &nivel);

    if (nivel < 1 || nivel > 3) {
        printf("Nível inválido. Encerrando o jogo.\n");
        return 1;
    }

    jogar(nivel);

    return 0;
}
