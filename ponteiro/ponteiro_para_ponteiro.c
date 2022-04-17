#include <stdio.h> 
#include <stdlib.h>


int main()
{
   

     int numero =5;
     int *ponteiro1;
     int **ponteiro2;
     ponteiro1 = &numero;
     ponteiro2 = &ponteiro1;

     printf("O endereco da variavel numero é: %p\n", &numero);
    printf("O endereco do ponteiro 1 é: %p\n", &ponteiro1);
    printf("O endereco do ponteiro 2 é: %p\n", &ponteiro2);
    printf("O endereco apontado por ponteiro 1 é: %p\n", ponteiro1);
    printf("O endereco apontado por ponteiro 2 é: %p\n", ponteiro2);
    printf("E o valor armazenado em numero é : %d\n", **ponteiro2);
    
}
