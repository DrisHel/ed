/*Iniciando jornada em C! */
#include <stdio.h> // incluir arquivos de cabeçalho, contém informações usadas pelo compilador, lidam com entrada e saídas printf e scanf
#include <stdlib.h>

// void é função sem retorno
void main(){ // função
    printf("Vou aprender essa merda nem que seja no laco!!! \n");//mostra mensagem na tela o n/ significa nova linha( sequencia de escape)



    int num1, num2, soma;
    printf("Digite o primeiro numero: \n");
    scanf("%d", &num1);
    printf("Digite o segundo numero: \n");
    scanf("%d", &num2);


    soma = num1 + num2;

    printf(" A Soma eh: %d\n", soma);
}