#include <stdio.h> 
#include <stdlib.h>
#include <locale.h>

int main(){ 

 int *ponteiro, valor, y;
 valor = 45;
 ponteiro = &valor;
 y = *ponteiro;


 printf("endereco da variavel comum valor : %p\n", &valor);
 printf("lendo o conteudo do ponteiro x: %p\n",ponteiro);
 printf("endereco da variavel ponteiro : %p\n", &ponteiro);
 printf("conteudo da variavel apontada por ponteiro %d\n", *ponteiro);
 printf("conteudo da variavael comum y: %d\n", y);
}