#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "tads.h"
int main()
{
    setlocale(LC_ALL, "Portuguese");setlocale(LC_ALL, "Portuguese");

    int wagons,maxWt,wtRail,key;
    Rail* input_rail = NULL;
    Rail* wait_rail = NULL;

    printf(" -----------LUIZ GUSTAVO LUCIO PEREIRA-----------\n");
    printf("\nInsira a quantidade de vagoes: \n");
    //scanf("%d",&wagons);fflush(stdin);//<- lendo o numero de vagões da pista
    wagons = 5;
    printf("\nnumero de vagoes auxiliares\n");
    //scanf("%d",&wtRail);fflush(stdin);//<- lendo o numero de trilhos auxiliares
    wtRail = 3;
    printf("\nnumero max de vagoes em trilhos auxiliares\n");
    maxWt = 3;
    //scanf("%d",&maxWt);fflush(stdin);//<- lendo o numero de vagões auxiliares

    create_rail(&input_rail,1,wagons);//<- cria o trilho de entrada(onde serão inseridos os dados),como so tem 1 trilho envia valor k = 1
    create_rail(&wait_rail,wtRail,maxWt);//<-criando os trilhos de espera

    for (int i = 0; i < wagons; i++)//<- loop de inserção
    {
       //scanf("%d", &key); fflush(stdin);//<- lendo a chave(numero) do vagão
       key = rand() % 10;
       if (!push_stack(input_rail, key))//<- caso a inserçao na pilha não seja possivel
       {
         break;// para loop
       }
    }
    print_stack(input_rail);

    for (int i = 0; i < 2; i++)//<- loop de inserção
    {
       //scanf("%d", &key); fflush(stdin);//<- lendo a chave(numero) do vagão
       pop_stack(input_rail);
    }
    printf("depois do pop\n");
    print_stack(input_rail);
    return 0;
}
