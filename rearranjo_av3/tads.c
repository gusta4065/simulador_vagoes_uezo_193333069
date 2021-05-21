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

Wagon *new_element()
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

void create_rail(Rail **rail_, int K, int max)
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

Rail* copy_rail(Rail* rail_,int K){
    for (int i = 0; i < K; i++)
    {                             // percorre toda as pilha
        Wagon* aux = rail_[i].top; // aux recebe topo de pilha
        if (aux != NULL)
        {
            Rail* auxStack = NULL;
            create_rail(&auxStack, K, rail_->max);// cria um novo trilho
            while (aux != NULL) //a pilha i aloca uma copia na auxStack em forma de pilha
            {
                push_stack(auxStack, aux->key); //aloca na auxStack
                printf("\n pilha alocaçao no auxliar  teste\n");
                print_Stack(auxStack);
                aux = aux->next; // proximo elemento
            }
            aux = auxStack->top; // spot aux recebe auxStack
            while (aux != NULL) // percorre por toda a pilha
            {
                //se tudo der certo o carro vai ser devidamente copiado aqui
                push_stack(&rail_[i], aux->key); //aloca o carro na pilha clone
                aux = aux->next;
            }
            free_stack(auxStack); // libera pilha
        }
    }
}

void print_stack(Rail *rail_)
{ // imprime a pilha
    printf("\n");
    if (!Isempty_stack(rail_)) // se diferente de nulo
    {
        Wagon *aux = rail_->top; // auxliar recebe topo de pilha
        while (aux != NULL)
        {
            printf("\t%d ", aux->key); //imprime prilha
            aux = aux->next;           //<- vai para proximo elemento
        }
        printf("\n");
    }
}

int push_stack(Rail *stack, int key)
{                           //insere na pilha
    if (stack->top != NULL) //se topo não vazio
    {
        if (stack->total >= stack->max) //se atingir ou estorar o limite de vagoes
        {
            printf("Não, é possivel estacionar mais vagoes nesse trilho \n");
            return 0; //false  se erro
        }
    }
    Wagon *new;
    new = new_element(); //<- aloca memoria para um novo elemento
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

void pop_stack(Rail *stack)
{ // remove da pilha
    if (stack->botton == NULL)
    { // se fundo nulo
        printf("pilha já vazia");
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

void free_stack(Rail* stack){// libera uma pilha inteira
     while (stack->top != NULL) // percorre por toda a pilha
    {
        pop_stack(stack); //aloca o vagao na pilha clone
    }
    stack = NULL; // seta como pilha vazia
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
        if (wait->top != NULL)
        {
            if (min > wait[i].top->key)
            {   // como por regra de negocio o trilho de espera sempre terá o topo como menor numero, faz muito mais sentido comparar apenas o topo
                // pode economizar em ate O(N-1) sendo N o numero de vagoes na pilha

                min = wait[i].top->key; // recebe sempre o menor valor
            }
        }
    }
    Wagon* aux = input->top;
    while (aux != NULL)//percorre toda pilha(trilho)
    {
        if(min > aux->key){//se min maior q alguma chave
            min = aux->key; // min recebe chave
        }
    }
    return min;
}

void reorganize(Rail *input, Rail *wait)
{
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
    Rail* Out_rail = NULL;
    Rail* copyRail = NULL;

}