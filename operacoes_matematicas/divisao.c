#include <stdio.h> 
#include <stdlib.h>

// void é função sem retorno
void main(){ 

    int num1, num2, divisao;
    printf("Digite o primeiro numero: \n");
    scanf("%d", &num1);
    printf("Digite o segundo numero: \n");
    scanf("%d", &num2);


    divisao = num1 / num2;

    printf(" A Divisao eh: %d\n", divisao);
}