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
void Create_rail(Rail** rail_, int K, int max);
Rail* Inverted_stack(Rail* rail_);
Rail* Copy_rail(Rail* rail_, int K);
void Print_stack(Rail* rail_);
void Print_WRail(Rail* waitR, int k);
void Print_park(Rail* input, Rail* wait, int k ,Rail* OutRail,int cont);
int  Push_stack(Rail* stack, int key);
int equal_key(Rail* stack, int key);
void Pop_stack(Rail* stack);
void Free_stack(Rail* stack);
void Free_park(Rail *RailC, Rail *WrailC, int Stack);
Wagon* New_element();
int Smaller_key(Rail* input, Rail* wait, int NwRail);
int Isert_outRail(Rail* rail_, Rail* outR, int min);
int empty_Wrail(Rail* wait, int k);
int Alocate_Wrail(Rail *wait, Rail *Out_rail,Rail* CopyRail, int K,int cont);
int Beter_position(Rail* wait, int k, int key);
void Reorganize(Rail* input, Rail* wait, int K);


#endif // TADS_H_INCLUDED
