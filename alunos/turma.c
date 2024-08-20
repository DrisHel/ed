#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Arquivo de prototipos das funções e definicao das estruturas
typedef struct aluno{
    char nome[100];
    int idade;
    int matricula;
    struct aluno *proximo;
}Aluno;
typedef struct lse{
    Aluno *primeiro;
    int n_elementos;
    char turma [20];
}LSE;

//Funções para gerenciar a lista
LSE* criaListaLSE(char turma[]){
    """Aloca memoria para uma nova lista"""; 
    LSE *nova = (LSE*)malloc(sizeof(LSE));
    if (nova == NULL) {
        printf("Erro ao alocar memoria para a nova lista.\n");
        return NULL;
    }  
    nova->primeiro = NULL;
    nova->n_elementos = 0;
    strcpy(nova->turma,turma);
    return nova;
}

Aluno* cadastraAluno(char nome[],int idade, int matricula){
    """Aloca memoria para um novo Elemento (aluno)""";
    Aluno *novoAluno = (Aluno*)malloc(sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memoria para o novo aluno.\n");
        return NULL;
    }
    strcpy(novoAluno->nome,nome);
    novoAluno->idade = idade;
    novoAluno->matricula = matricula;
    novoAluno->proximo = NULL;
    return novoAluno;
}

Aluno* lerAluno(){
    Aluno *novoAluno = (Aluno*)malloc(sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memoria para o novo aluno.\n");
        return NULL;
    }
    printf("\n Informe o nome do novo aluno:");
    scanf("%s",novoAluno->nome);
    printf("\n Informe a idade do novo aluno:");
    scanf("%d",&novoAluno->idade);
    printf("\n Informe a matricula do novo aluno:");
    scanf("%d",&novoAluno->matricula);
    novoAluno->proximo = NULL;
    return novoAluno;    
}

void mostraAluno(Aluno *novo){
    """Mostre os dados de um  Aluno""";
    if(novo != NULL){
        printf("\n\t Nome:%s",novo->nome);
        printf("\t Idade:%d",novo->idade);
        printf("\t Matricula:%d",novo->matricula);
    }else{
        printf("\n Erro ao imprimir Aluno Valor = NULL\n");
    }
}

void mostraLista(LSE *ls){
    """Mostra Lista""";
    Aluno *aux = ls->primeiro;
    printf("\n\n Mostra a Lista de %s:",ls->turma);
    while(aux != NULL){
        mostraAluno(aux);
        aux = aux->proximo;
    }
    printf("\n Fim da Lista!!\n");
}

void insereNoInicio(LSE *ls, Aluno *novo){
    if(ls->primeiro == NULL)
        novo->proximo = NULL;
    else
        novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->n_elementos++;
    printf("\n Aluno %s inserido com sucesso!!!",novo->nome);
}

void insereNoFim(LSE *ls, Aluno *novo){
    """Insere um novo aluno no Fim da Lista!!!""";
    Aluno *aux = ls->primeiro;
    if(aux == NULL)
        insereNoInicio(ls,novo);
    else{
        while (aux->proximo != NULL){
            aux = aux->proximo;
        }
        novo->proximo = NULL;
        aux->proximo = novo;
        ls->n_elementos++;
    }
}

//insere o novo aluno na turma na posicao "pos";
void insereNaPosicao(LSE *ls, Aluno *novo, int pos){
    Aluno *aux = ls->primeiro;
    if(pos == 0)
        insereNoInicio(ls,novo);
    else if(pos == ls->n_elementos)
        insereNoFim(ls,novo);
    else if(pos > ls->n_elementos)
        printf("\n\t Erro - Posição Inválida!!");
    else{
        for(int i = 0; i < pos-1; i++){
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        ls->n_elementos++;
    }
};


Aluno* removeNoInicio(LSE *ls){
    """Remove e retorna o primeiro aluno da lista""";
    Aluno *aux = ls->primeiro;
    if(aux == NULL)
        printf("\n\t Erro - Lista Vazia!!");
    else{
        ls->primeiro = aux->proximo;
        aux->proximo = NULL;
        ls->n_elementos--;
    }
    return aux;
}
//Remove um novo aluno no final da lista;
Aluno* removeNoFim(LSE *ls){
    Aluno *aux = ls->primeiro;
    Aluno *aux2 = NULL;
    if(aux == NULL)
        printf("\n\t Erro - Lista Vazia!!");
    else{
        while(aux->proximo != NULL){
            aux2 = aux;
            aux = aux->proximo;
        }
        if(aux2 == NULL)
            ls->primeiro = NULL;
        else
            aux2->proximo = NULL;
        ls->n_elementos--;
    }
    return aux;
};

//Remove o aluno na turma na posicao "pos";
Aluno* removeNaPosicao(LSE *ls, int pos){
    Aluno *aux = ls->primeiro;
    Aluno *aux2 = NULL;
    if(pos < 0 || pos >= ls->n_elementos)
        printf("\n\t Erro - Posição Inválida!!");
    else{
        for(int i = 0; i < pos; i++){
            aux2 = aux;
            aux = aux->proximo;
        }
        if(aux2 == NULL)
            ls->primeiro = aux->proximo;
        else
            aux2->proximo = aux->proximo;
        aux->proximo = NULL;
        ls->n_elementos--;
    }
    return aux;
};

//retorna a quantidade de elementos da Lista
int retornaQuantidade(LSE *ls){
    return ls->n_elementos;
};

//Mostra as informações do aluno que está na Posicao "pos"
void mostraPosicao(LSE *ls, int pos){
    Aluno *aux = ls->primeiro;
    if(pos < 0 || pos >= ls->n_elementos)
        printf("\n\t Erro - Posição Inválida!!");
    else{
        for(int i = 0; i < pos; i++){
            aux = aux->proximo;
        }
        mostraAluno(aux);
    }
};

//Apaga todos os alunos da Lista (free em cada aluno)
void apagaLista(LSE *ls){
    Aluno *aux = ls->primeiro;
    Aluno *aux2 = NULL;
    while(aux != NULL){
        aux2 = aux;
        aux = aux->proximo;
        free(aux2);
    }
    ls->primeiro = NULL;
    ls->n_elementos = 0;
    printf("\n\t Lista Apagada com Sucesso!!!");
};


void menuTesteLista(LSE *lse){
    int op = 0, posicao = 0;
    Aluno *aux = NULL;
    printf("\n Menu de operacoes sobre um LSE:\n");
    printf("\n\t 1 - Insere no Inicio:");
    printf("\n\t 2 - Insere no Fim:");
    printf("\n\t 3 - Insere na Posicao:");
    printf("\n\t 4 - Remove no Inicio:");
    printf("\n\t 5 - Remove no Fim:");
    printf("\n\t 6 - Remove na Posicao:");
    printf("\n\t 7 - Mostra Lista:");
    printf("\n\t 8 - Mostra Aluno na Posicao:");
    printf("\n\t 9 - Apaga Lista:");
    printf("\n\t 0 - Para Sair da Funcao Menu:");
    printf("\n\t Informe a opcao:");
    scanf("%d",&op);
    switch (op) {
        case 1:
            printf("\n\t Funcao Insere no Inicio!!");
            insereNoInicio(lse,lerAluno());
        break;
        case 2:
            printf("\n\t Funcao Insere no Fim!!");
            insereNoFim(lse,lerAluno());
        break;
        case 3:
            printf("\n\t Funcao Insere na Posicao!!");
            printf("\n\t\t Informe a posicao:");
            scanf("%d",&posicao);
            insereNaPosicao(lse,lerAluno(),posicao);
        break;
        case 4:
            printf("\n\t Funcao remove  no Inicio:");
            aux = removeNoInicio(lse);
            if(aux != NULL){
                mostraAluno(aux);
                free(aux);
            }
        break;
        case 5:
            printf("\n\t Funcao remove  no FIM:");
            aux = removeNoFim(lse);
            free(aux);
        break;
        case 6:
            printf("\n\t Funcao Remove na Posicao!!");
            printf("\n\t\t Informe a posicao:");
            scanf("%d",&posicao);
            removeNaPosicao(lse,posicao);
        break;
        case 7:
            printf("\n\n Mostra Lista %s!!!",lse->turma);
            mostraLista(lse);
        break;
        case 8:
            printf("\n\t Funcao Mostra um Aluno na Posicao - Pos!!");
            printf("\n\t\t Informe a posicao:");
            scanf("%d",&posicao);
            mostraPosicao(lse,posicao);
        break;
        case 9:
            printf("\n\t Funcao Apaga toda Lista!");
            apagaLista(lse);
        break;
        case 0:
            printf("\n\n *** Fim do Programa!!! ***\n");
            break;
        break;        
        default:
            printf("\n\n *** Opcao Invalida!!! ***\n");
    }
    if(op > 0 && op < 10)
        menuTesteLista(lse);
}


//trocar de turma de Portugues para Matematica o aluno com nome selecionado pelo usuário



void trocaTurmaPorMat(LSE *lmatematica, LSE *lportugues, int pos){
      Aluno* aluno = removeNaPosicao(lportugues, pos);
    if (aluno == NULL) {
        printf("Aluno nao encontrado na turma de Portugues.\n");
        return;
    }
    removeNaPosicao(lportugues, 0);
    insereNoInicio(lmatematica, aluno);
    printf("Aluno %s transferido para a turma de Matematica.\n", pos);

    };

 //trocar de turma de Matematica para Portugues o aluno com nome selecionado pelo usuário
void trocaTurmaMatPor(LSE *lmatematica, LSE *lportugues){
    printf("\n\t Trocar um aluno de turma de Matematica para turma de Portugues");
    printf("\n\t Informe a posicao do aluno:");
}

//Mostrar as turmas de Portugues para Matematica 
void mostrarTurmaPorMat(LSE *lmatematica, LSE *lportugues){
    printf("\n\t Mostrar as listas das turmas de Portugues e Matematica");
    mostraLista(lmatematica);
    mostraLista(lportugues);
}


void menuTrocaTurmas(LSE *lmatematica, LSE *lportugues){
    int op = 0, posicao = 0;
    Aluno *aux = NULL;
    printf("\n Menu de operacoes Troca Turmas:\n");
    printf("\n Escolha um Opcao:");
    printf("\n\t 1 - Trocar um aluno de Portugues para Matematica:");
    printf("\n\t 2 - Trocar um aluno de Matematica para Portugues:");
    printf("\n\t 3 - Mostrar as Turmas de Portugues e Matematica:");
    printf("\n\t 0 - Para Sair do Programa:");
    printf("\n\t Informe a opcao:");
    scanf("%d",&op);
    switch (op) {
            case 1:
                //trocar de turma de Portugues para Matematica o aluno com nome selecionado pelo usuário
                // printf("\n\t Trocar um aluno de turma de Portugues para turma de Matematica");
                // trocaTurmaPorMat(lmatematica,lportugues, "Nome do Aluno");
                printf("Informe a posicao do aluno a ser transferido de Portugues para Matematica: ");
                int pos;
                scanf("%d", pos);
                trocaTurmaPorMat(lmatematica, lportugues, pos);
            break;
            case 2:
                //trocar de turma de Matematica para Portugues o aluno com nome selecionado pelo usuário
                trocaTurmaMatPor(lmatematica,lportugues);
            break;
            case 3:
                //Mostrar as turmas de Portugues para Matematica 
                mostrarTurmaPorMat(lmatematica,lportugues);
            break;
            case 0:
            printf("\n\n *** Fim do Programa!!! ***\n");
        break;        
        default:
            printf("\n\n *** Opção Inválida!!! ***\n");
    }
    if(op > 0 && op < 4)
        menuTrocaTurmas(lmatematica,lportugues);
}






//Programa lista de alunos de matemática

int main(){

    system("clear");
    //cria a lista de alunos de matemática 
    LSE *listaMatematica = criaListaLSE("Matematica");

    //cria o elemento de LSE chamado pedro
    Aluno *pedro = cadastraAluno("Pedro",44,1123301);

    //insere no inicio um novo aluno na lista de matemática
    insereNoInicio(listaMatematica,pedro);

    Aluno *novo = cadastraAluno("Joao",24,1123321);
    insereNoInicio(listaMatematica,novo);
 
    mostraLista(listaMatematica);
    printf("\n");

    //Primeira parte da atividade funções de lista

    menuTesteLista(listaMatematica);

    //segunda parte da atividade - Troca de turmas

    LSE *listaPortugues = criaListaLSE("Portugues");
    Aluno *livia = cadastraAluno("Livia",24,1123322);
     insereNoInicio(listaPortugues,livia);
    Aluno *novo1 = cadastraAluno("Gustavo",26,1123323);
     insereNoInicio(listaPortugues,novo1);

    char nome[50];

    printf("\n\n Informe o nome do aluno a ser transferido de Portugues para Matematica: \n");
    scanf("%s", nome);

    trocaTurmaMatPor(listaMatematica, listaPortugues);
       
    mostraLista(listaPortugues);
    printf("\n");
    menuTrocaTurmas(listaMatematica, listaPortugues);

// Liberação de memória alocada para os alunos
    free(livia);
    free(novo1);


    free(listaMatematica);
    free(listaPortugues);

    return 0;
}
