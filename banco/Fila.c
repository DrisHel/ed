#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{   //dados do cliente bancário
    char nome [20];
    int operacao;
    float valor;
    int id;
    struct cliente *proximo;    
}Cliente;


typedef struct fila{   //atributos de Fila
    Cliente *inicio; //inicio
    Cliente *fim;
    int qtd;
}Fila;



Fila * criaFila(){
    Fila *fl  = (Fila *)malloc(sizeof(Fila));
    fl->inicio = NULL; //inicialização da fila
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}   

Cliente* cadastraNovoCliente(char nome [] , int op, double vl, int id ){
    Cliente *novo = (Cliente *)malloc (sizeof(Cliente));
    strcpy(novo->nome,nome);
    novo->operacao = op;
    novo->valor = vl;
    novo->proximo = NULL;
    novo->id = id;
    return novo;
}

void enfileirar(Fila *fl, Cliente *cl){ 
    if(fl->inicio == NULL){ //Fila Vazia
        fl->inicio = cl;
    }else{          //Fila com elementos
        fl->fim->proximo = cl;     
    }
    cl->proximo = NULL;
    fl->fim = cl;
    fl->qtd++;
}

Cliente* desenfileirar(Fila *fl){  
    Cliente *aux = fl->inicio;
    if(aux == NULL)   //Fila vazia
        printf("\nErro - Fila Vazia\n");
    else{       //Lista com elementos
        fl->inicio = aux->proximo;
        fl->qtd--;
        aux->proximo = NULL;
        if(fl->inicio == NULL)
            fl->fim = NULL;
    }
    return aux;
}

void mostraCliente(Cliente cl){
    printf("\n Id:%d \n\t Nome: %s \n\t Operacao: %d \n\t Valor=%.2f \n",cl.id,cl.nome,cl.operacao,cl.valor);
}

void mostraFila(Fila *fl){
    printf("\nInício da Fila\n");
    Cliente *aux = fl->inicio;
    while(aux != NULL){
        mostraCliente(*aux);
        aux = aux->proximo;
    }
    printf("\nFim da Fila\n");
}

void apagaCliente(Cliente *cl){
    """Apaga um elemento da Fila""";
    printf("\n Apagado!");
    free(cl);
}

void apagaFila(Fila *fl){
    Cliente *aux = desenfileirar(fl);
    while(aux!= NULL){
        aux = desenfileirar(fl);
        apagaCliente(aux);
    }
    printf("\nFila Vazia - Qtd = %d\n",fl->qtd);
}



void menu(Fila *fl,int id){
    int op;
    Cliente *cl;
    char nome[20];
    float vl;
    do{
        printf("\n\nInforme uma Opção:");
        printf("\n -- 1 - para Insere:");
        printf("\n -- 2 - para Remove:");
        printf("\n -- 3 - MostraFila:");
        printf("\n -- 4 - Apaga Fila:");
        printf("\n -- 0 - para Sair do Programa:\n");
        printf("\nInforme sua Opçao:");
        scanf("%d",&op);
        fflush(stdin);
        
        switch(op){
            case 1:                
                printf("\n Função Insere na Fila. \n");
                printf("Informe o seu nome:\n");
                scanf("%s",nome);
                printf("Informe a operacao: (1)Caixa (2)Gerente\n");
                scanf("%d",&op);
                printf("Informe o Valor:\n");
                scanf("%f",&vl);
                enfileirar(fl,cadastraNovoCliente(nome,op,vl,id++));
                printf("\n Inserção Realizada com Sucesso");
             
            break;
            case 2:
                printf("\n Função Remove da Fila. \n");
                cl = desenfileirar(fl);
                if(cl!=NULL){
                    mostraCliente(*cl);
                    apagaCliente(cl);
                }
                printf("\n Remoção Realizada com Sucesso");
               
            break;
            case 3:                
                printf("Mostra Fila:");
                mostraFila(fl);
            break;
            case 4:
                printf("\n Apagar a Fila !! \n");
                apagaFila(fl);
            break;
            default:
                printf("\nOpção Inválida!!\n");
        }
       
    
    }while(op>0);
}

int main(){
    int id = 0;
    Fila *fl;

    fl = criaFila();

    menu(fl,id);
    
    return 1;
}