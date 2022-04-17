#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct livro{
    char nome[50];
    char autor[50];
    int paginas;
    float preco;

}livro1;

int main()
{
    setlocale(LC_ALL, "");
    printf("Cadastrando livro: \n");
    printf("\n Digite o nome do livro: \n");
    gets(livro1.nome); //pega os dados
    printf("\n Digite o nome do autor: \n");
    gets(livro1.autor);
    printf("\n Digite o numero de paginas do livro: \n");
    scanf("%d", &livro1.paginas);
    printf("\n entre com o preco do livro: \n");
    scanf("%f", &livro1.preco);   

    printf("\nO livro %s  possui %d paginas e custa R$ %4.2f e seu autor eh %s .\n", livro1.nome, livro1.paginas, livro1.preco, livro1.autor); 
    return 0;
}
