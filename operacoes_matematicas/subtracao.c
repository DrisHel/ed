#include <stdio.h> // incluir arquivos de cabeçalho, contém informações usadas pelo compilador, lidam com entrada e saídas printf e scanf
#include <stdlib.h>

// void é função sem retorno
void main(){ // função
   
    int num1, num2, subtrai;
    printf("Digite o primeiro numero: \n");
    scanf("%d", &num1);
    printf("Digite o segundo numero: \n");
    scanf("%d", &num2);


    subtrai = num1 - num2;

    printf(" A Subtracao eh: %d\n", subtrai);
}