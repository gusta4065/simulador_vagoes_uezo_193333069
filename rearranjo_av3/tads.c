#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "tads.h"
#define MAX 9999;

int Isempty_stack(Rail *rail_)
{                           //testa estacionamento vazio
    return (rail_ == NULL); //<- se verdadeiro retorna 1 caso falso retorna 0
}

Wagon *New_element()
{
    Wagon *new = (Wagon *)malloc(sizeof(Wagon)); //<- alocando um novo elemento, nesse caso um vagao
    if (new == NULL)
    {
        exit(1);
    }
    new->next = NULL; //<- incializando o proximo elemento como nulo, assim eu evito cair em lixo de memoria sem querer
    new->key = -1;    //<- apenas uma flag pra eu identificar se foi devidamente incializada
    return new;
}

void Create_rail(Rail **rail_, int K, int max)
{                                                 // recebe endeçero de trilho
    Rail *new = (Rail *)malloc(K * sizeof(Rail)); //<- malloca K trilhos
    for (int i = 0; i < K; i++)
    {
        if (Isempty_stack(&new[i]))
        {
            exit(1);
        }
        new[i].max = max;           //<- seta max de vagões
        new[i].total = 0;           //<-incia total como zero
        new[i].top = NULL;          //<-inicializa topo
        new[i].botton = new[i].top; //<-inicializa fundo
    }
    *rail_ = new; //conteudo de rail_ recebe new;
}

Rail *Copy_rail(Rail *rail_, int K)
{
    Rail *auxStack = NULL;
    Rail *CRail = NULL;
    Create_rail(&CRail, K, rail_->max);
    for (int i = 0; i < K; i++)
    {                              // percorre toda as pilha
        Wagon *aux = rail_[i].top; // aux recebe topo de pilha
        if (aux != NULL)
        {

            Create_rail(&auxStack, K, rail_->max); // cria um novo trilho
            while (aux != NULL)                    //a pilha i aloca uma copia na auxStack em forma de pilha
            {
                Push_stack(auxStack, aux->key); //aloca na auxStack
                aux = aux->next;                // proximo elemento
            }
            aux = auxStack->top; // spot aux recebe auxStack
            while (aux != NULL)  // percorre por toda a pilha
            {
                //se tudo der certo o carro vai ser devidamente copiado aqui
                Push_stack(&CRail[i], aux->key); //aloca o carro na pilha clone
                aux = aux->next;
            }
            Free_stack(auxStack); // libera pilha
        }
    }
    return CRail;
}

void Print_stack(Rail *rail_)
{ // imprime a pilha
    if (!Isempty_stack(rail_)) // se diferente de nulo
    {
        Wagon *aux = rail_->top; // auxliar recebe topo de pilha
        while (aux != NULL)
        {
            printf(" %d ", aux->key); //imprime prilha
            aux = aux->next;          //<- vai para proximo elemento
        }
    }
}

Rail* Inverted_stack(Rail* rail_){
    Rail* auxStack = NULL;
    Create_rail(&auxStack,1,rail_->max);// cria uma pilha auxiliar
    Wagon* auxW = rail_->top;// auxR recebe topo de pilha
    while (auxW != NULL)// se diferente de nulo
    {
        if(!Push_stack(auxStack,auxW->key))// aloca na pilha auxliar
        {
            return NULL;// se não for possivel alocar  retorna nulo
        }
        auxW = auxW->next;//proximo elemento
    }
    return auxStack;
}

void Print_WRail(Rail *waitR, int k)
{
    Rail *aux = NULL;
    Create_rail(&aux,k,waitR->max);// cria um axiliar
    for (int i = 0; i < k; i++)
    {
            aux[i] = waitR[i]; //recebe waitR[i]
    }
    printf("\n\n\n");
    for (int i = 0; i < waitR->max; i++)// percore coluna
    {
        printf("|");
        for (int j = 0; j < k; j++)//percorre linha
        {
            if (aux[j].top != NULL)
            {
                if (aux[j].total < (aux[j].max - i))// se max -1 maior q total
                {
                    printf("\t|");//printa vazio
                }
                else
                {
                    printf("%d\t|", aux[j].top->key);//printa valor do elemento
                    aux[j].top = aux[j].top->next;// proximo elemento da pilha
                }
            }
            else
            {
                printf("\t|"); // se pilha vazia imprime espaço vazio
            }
        }
        printf("\n");
        // printf("----------------- %d", i);
        // Print_stack(&waitR[i]);
    }
    for (int i = 0; i < k; i++)
    {
        printf(" H%d\t", i);// printa os trilhos de aux
        //Free_stack(au)
    }
}


void Print_park(Rail* input, Rail* wait, int k ,Rail* OutRail, int cont){
    printf("\nmovimento %d\n",cont);
    printf("Entarada: \t\t\t\t Saida:\n");
    Print_stack(Inverted_stack(input));/* Imprime pilha de saida invertida */ printf("\t\t\t\t\t");/* espaçamanto */ Print_stack(OutRail); /* trilho de saida */
    printf("\nTrilhos de espera\n");
    Print_WRail(wait,k);/*imprime o trilho de saida*/
    printf("\n");
    system("Pause");
    system("cls");

}

int Push_stack(Rail *stack, int key)
{                           //insere na pilha
    if (stack->top != NULL) //se topo não vazio
    {
        if (stack->total >= stack->max) //se atingir ou estorar o limite de vagoes
        {
            printf("N%co, %c possivel estacionar mais vagoes nesse trilho \n", 227, 233);
            return 0; //false  se erro
        }
    }
    Wagon *new;
    new = New_element(); //<- aloca memoria para um novo elemento
    new->key = key;      // <- recbe a indentificaçao do vagao
    stack->total++;      //<- incrementa o total da elementos
    if (stack->top == NULL)
    {                        //<-caso essa pilha esteja vazia
        stack->botton = new; //<- o novo elemento se torna TAMBEM o elemento do fundo da pilha
    }
    new->next = stack->top; //<- o topo da pilha de torna o sucessor do nosso novo elemento
    stack->top = new;       //<- o novo elemento se torna o topo da pilha
    return 1;               // true se sucesso
}

int equal_key(Rail *stack, int key)
{
    Wagon *i = stack->top;
    while (i != NULL) // percorre pilha
    {
        if (i->key == key) //se encontrar algum valor igual
        {
            return 1; // retorna 1
        }
        i = i->next;
    }
    return 0;
}

void Pop_stack(Rail *stack)
{ // remove da pilha
    if (stack->botton == NULL)
    { // se fundo nulo
        printf("pilha j%c vazia", 225);
        return; //retona
    }
    Wagon *q;               // elemento auxiliar
    q = stack->top;         //elemento auxiliar recebe topo
    stack->total--;         // decrementa o total
    stack->top = q->next;   // o elemento seguinte ao topo de torna o topo da pilha1
    free(q);                // libera memoria
    if (stack->top == NULL) //se topo nulo
    {
        stack->botton = stack->top; // seta fundo como nulo
    }
}

void Free_stack(Rail *stack)
{                              // libera uma pilha inteira
    while (stack != NULL && stack->top != NULL ) // percorre por toda a pilha
    {
        Pop_stack(stack); //aloca o vagao na pilha clone
    }
    stack = NULL; // seta como pilha nula
}

void Free_park(Rail *RailC, Rail *WrailC, int Stack)
{ // liberar a memoria d0 estacionamento de trens
    int i;
    Free_stack(RailC);
    for (i = 0; i < Stack; i++)
    { // percorre toda as pilha
        Free_stack(&WrailC[i]);
    }
    RailC = NULL; // seta como pilha nula
}

int Smaller_key(Rail *input, Rail *wait, int NwRail)
{
    /**
     * @brief menor valor
     *      procorrerá os trilhos de espera(se não nulos) procurando o a menor chave
     *      com esse valor percorrrá o trilho de entrada comprarando um a um de forma a procurar a menor chave
     */
    int min = MAX;
    for (int i = 0; i < NwRail; i++) // percorre os trlhos de espera
    {
        if (wait[i].top != NULL)
        {
            if (min > wait[i].top->key)
            {                           // como o trilho de espera sempre terá o topo como menor numero, faz muito mais sentido comparar apenas o topo
                min = wait[i].top->key; // recebe sempre o menor valor
            }
        }
    }
    if (input != NULL) // se input nao for nulo
    {
        Wagon *aux = input->top;
        while (aux != NULL) //percorre toda pilha(trilho)
        {
            if (min > aux->key)
            {                   //se min maior q alguma chave
                min = aux->key; // min recebe chave
            }
            aux = aux->next; //proximo elemento
        }
    }

    return min;
}

int Isert_outRail(Rail *rail_, Rail *outR, int min)
{                           //insere no trilho de saida e retona 1 ou 0(caso não for possivel a inserçao)
    if (rail_->top != NULL) // se topo naão nulo
    {
        if (min == rail_->top->key) //<- copara a chave com o minimo da pista
        {
            Push_stack(outR, rail_->top->key); //<- se verdadeiro aloca o vagão no trilho de saida
            Pop_stack(rail_);                  //<- libera topo de pilha
            return 1;                          //<- retorna 1
        }
    }
    return 0; //<- retorna 0
}

int empty_Wrail(Rail *wait, int k)
{ // verifica se os trilhos de espera estão vazios
    int cont = 0;
    for (int i = 0; i < k; i++)
    {
        if (wait[i].top == NULL)
        {
            cont++; //incrementa 1
        }
    }
    if (cont == k)
    {
        return 1; // <- caso vazio retorna 1
    }
    else
    {
        return 0; // <- caso não vazio retorna 2
    }
}

int Alocate_Wrail(Rail *wait, Rail *Out_rail, Rail *CopyRail, int K, int cont) //aloca os trilhos de espera no trilho de saida
{
    int i = 0, min;
    while (i < K) // percorre todos os trilhos
    {
        min = Smaller_key(CopyRail, wait, K); // novo minimo
        if (!Isert_outRail(&wait[i], Out_rail, min))
        {        //caso não seja possivel alocar no trilho saida
            i++; // tenta o proximo trilho
        }
        else
        {
            cont++; //incrementa contador
            Print_park(CopyRail,wait,K,Out_rail,cont);
        }
    }
    return cont;
}

int Beter_position(Rail *wait, int k, int key)
{ // procura a melhor posição possivel entre os trilhos de saida
    int Bt = -1;
    if (empty_Wrail(wait, k))
    {
        return 0; //<- se todos os trilhos estiverem vazios retorna 0
    }
    for (int i = 0; i < k; i++)
    {
        if (wait[i].top != NULL)
        { // se diferente de nulo
            if (wait[i].top->key > key)
            {              //caso a chave do topo seja maior q key
                Bt = i;    //<- melhor posiçao se torna i;
                return Bt; //retona Bt pois ele é a melhor posição já foi encontrada
            }
            else
            {
                if (wait[(i + 1) % k].top == NULL) // se a poisão Bt for um trilho vazio
                {
                    Bt = (i + 1) % k;               //<- a posição seguinte se torna Bt
                    return Bt; //retona Bt pois ele é a melhor posição já foi encontrada
                }
            }
        }
    }
    return Bt; // retorna e melhor posiçao entre os trilhos de espera, caso não tenha sido encontrada retorna -1
}

void Reorganize(Rail *input, Rail *wait, int K)
{
    //setlocale(LC_ALL, "Portuguese");
    /**
     * @brief -essa funçao devera alocar o primeiro elemento do trilho LIFO(aka pilha)
     *         no melhor trilho possivel visando respeitar a ordem numérica das chaves
     *         de identificação de cada vagão
     *        -no trilho de entrada, aquele onde o usuario fez a inserção dos vagões
     *         o vagão do topo da pilha deverá
     *              - procurar a melhor posição de inserção que pode ser:
     *                  - o trilho de saida
     *                  - um dos k-trilhos.
     *                      - esses trilhos serão escolidos baseados na seguinte heuristica( repetir até trilho de entrada ser nulo)
     *                          - verifica se é possivel alocar no trilho de saida e *logo em seguida procura o menor numero*
     *                              - caso não seja possivel:
     *                                      - verifica se existe algum trilho vazio/nulo ou com uma chave de identificaçao maior q a dele(ovagão do topo)
     *                                          - caso exista em algum trilho de espera um vagão onde a sua chave do topo seja MAIOR que a do vagão do topo do trilho de entrada
     *                                              - aloca nesse trilho
     *                                          - caso não exita:
     *                                               alocar no primeiro vagão vago
     *                          - verifica se é possivel alocar algum dos vagoes dos trilhos de espera na saia da seguite forma (repete enquanto nos trilho de espera existir um menor valor
     */
    Rail *Out_rail = NULL;
    Rail *CopyRail = NULL;
    Create_rail(&Out_rail, 1, input->max); //cria um trilho de saida
    CopyRail = Copy_rail(input, 1);
    //Print_stack(CopyRail);
    int min = Smaller_key(CopyRail, wait, K);
    int cont = 0;                 //contador de movimentos
    while (CopyRail->top != NULL) //percore todo o trilho principal vagão por vagão
    {
        Wagon *aux = CopyRail->top;
        if (!Isert_outRail(CopyRail, Out_rail, min))
        {                                               //caso não tenha sido possivel alocar no trilho de saida
            int Bt = Beter_position(wait, K, aux->key); // busca a melhor posição entre os trilhos de espera
            if (Bt >= 0)
            {                                         // busca a melhor posição entre os trilhos de espera. caso o retorno seja -1 não foi possivel encontrar essa posiçao
                if (!Push_stack(&wait[Bt], aux->key)) // caso não seja possivel alocar no trilho de espera
                {
                    printf("\nopera%c%co inv%clida",135,198,160);
                    Free_park(CopyRail, wait, K); //libera menoria da copia dos trilhos auxiliarer
                    Free_stack(Out_rail);
                    return;
                }
                Pop_stack(CopyRail);
                cont++;
                Print_park(CopyRail,wait,K,Out_rail, cont);//imprimime estado atual
            }
            else
            {
                printf("\nopera%c%co inv%clida",135,198,160);
                Free_park(CopyRail, wait, K); //libera menoria da copia dos trilhos auxiliarer
                Free_stack(Out_rail);
                return;
            }                                                //libera topo de pilha
            cont = Alocate_Wrail(wait, Out_rail, CopyRail, K, cont); // faz alocação,se possivel, dos vagões dos trilhos de espera no trilho de saida
            //printf("Movimento %d", cont);
            min = Smaller_key(CopyRail, wait, K); // novo minimo
        }
        cont = Alocate_Wrail(wait, Out_rail, CopyRail, K, cont); // faz alocação,se possivel, dos vagões dos trilhos de espera no trilho de saida
        //cont++;
        //Print_park(CopyRail,wait,K,Out_rail,cont);
    }
    while (!empty_Wrail(wait, K)) // enquanto o trilho de saida não estiver vazio
    {
        cont = Alocate_Wrail(wait, Out_rail, CopyRail, K, cont); // aloca os trens do trilho espera, no trilho de saida
        //Print_park(CopyRail,wait,K,Out_rail,cont);
    }
    printf("Saida:\n");
    Print_stack(Out_rail);
    printf("\nnumero de movimentos %d\n", cont);
    Free_stack(Out_rail);
}
