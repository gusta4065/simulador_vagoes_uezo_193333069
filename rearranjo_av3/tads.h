#ifndef TADS_H_INCLUDED
#define TADS_H_INCLUDED

typedef struct wagon_
{
    //int index; //<- indcie do carro 
    int key; //<- identificaçação de ordem do carro 
    struct wagon_* next; //<- proximo carro 

}Wagon;

typedef struct rail_
{
    Wagon* top; //<- recebe o carro
    //Wagon* first;
    Wagon*  botton;// <- ultimo da pilha
    int max,total; //<- numero max de vagoes

}Rail;


int Isempty_stack(Rail* rail_);
void create_rail(Rail** rail_, int K, int max);
Rail* copy_rail(Rail* rail_, int K);
void print_stack(Rail* rail_);
int  push_stack(Rail* stack, int key);
void pop_stack(Rail* stack);
void free_stack(Rail* stack);
Wagon* new_element();
int Smaller_key(Rail* input, Rail* wait, int NwRail);
void reorganize(Rail* input, Rail* wait);


#endif // TADS_H_INCLUDED
