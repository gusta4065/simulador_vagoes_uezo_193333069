#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "tads.h"
int main()
{
  //setlocale(LC_ALL, "");

  int wagons=0, maxWt=0, wtRail=0, key=0, option=-1;
  Rail *input_rail = NULL;
  Rail *wait_rail = NULL;

  while (1)
  {
    system("cls");
    printf(" -----------LUIZ GUSTAVO LUCIO PEREIRA-----------\n");
    printf("|                                                |\n");
    printf("|                                                |\n");
    printf("| 1- Inser%c%co manual                             |\n",135,198);
    printf("| 2- Inser%c%co automatica                         |\n",135,198);
    printf("| 3- Sair do programa                            |\n");
    printf(" ------------------------------------------------\n");
    scanf("%d", &option);
    fflush(stdin);
    system("cls");

    switch (option)
    {
    case 1:
      do
      {
        printf("\nInsira a quantidade de vag%ces: \n",228);
        scanf("%d", &wagons);
        fflush(stdin); //<- lendo o numero de vagões da pista
      } while (wagons < 0);
      do
      {
        printf("\nNumero de trilhos auxiliares\n");
        scanf("%d", &wtRail);
        fflush(stdin); //<- lendo o numero de trilhos auxiliares        /* code */
      } while (wtRail < 0);
      do
      {
        printf("\nNumero max de vag%ces em trilhos auxiliares\n",228);
        scanf("%d", &maxWt);
        fflush(stdin); //<- lendo o numero de vagões auxiliares
      } while (maxWt < 0);
      Create_rail(&input_rail, 1, wagons);    //<- cria o trilho de entrada(onde serão inseridos os dados),como so tem 1 trilho envia valor k = 1
      Create_rail(&wait_rail, wtRail, maxWt); //<-criando os trilhos de espera

      for (int i = 0; i < wagons; i++) //<- loop de inserção
      {
        for (;;)
        {
          printf("\n insira o %d%c vag%co\n",i+1,248,198);
          scanf("%d", &key); fflush(stdin);//<- lendo a chave(numero) do vagão
          if (!equal_key(input_rail, key))
          {
            break;
          }
        }
        if (!Push_stack(input_rail, key)) //<- caso a inserçao na pilha não seja possivel
        {
          break; // para loop
        }
     }
        break;
      case 2:
        wagons = 9;
        wtRail = 3;
        maxWt = 3;
        Create_rail(&input_rail, 1, wagons);    //<- cria o trilho de entrada(onde serão inseridos os dados),como so tem 1 trilho envia valor k = 1
        Create_rail(&wait_rail, wtRail, maxWt); //<-criando os trilhos de espera
        Push_stack(input_rail, 5);
        Push_stack(input_rail, 8);
        Push_stack(input_rail, 1);
        Push_stack(input_rail, 7);
        Push_stack(input_rail, 4);
        Push_stack(input_rail, 2);
        Push_stack(input_rail, 9);
        Push_stack(input_rail, 6);
        Push_stack(input_rail, 3);
        break;
      case 3:
        Free_park(input_rail, wait_rail, wtRail);
        exit(1);
        break;
      default:
        break;

    }
   Reorganize(input_rail, wait_rail, wtRail);
   Free_park(input_rail, wait_rail, wtRail);
  }

    return 0;
  }
