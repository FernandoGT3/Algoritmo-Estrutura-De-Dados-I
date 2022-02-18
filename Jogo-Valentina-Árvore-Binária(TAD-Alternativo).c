// Luiz Fernando -- Matricula: 159325
// Tarefa 008
/* */

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

//TAD Árvore Binária

typedef int TChave;

typedef struct SNo
{
    TChave Chave;
    struct SNo *esquerdo, *direito;
}TNo;

typedef TNo* TArvore;

void Inicializa_Vetor(TChave v[MAX], int tam)
{
    for (int i = 0; i < tam; i++)
        v[i] = 0;
}

TArvore Inicializa_TArvore() {
    return (NULL);
}

TArvore CriaNo_TArvore(TChave Valor) {

    TArvore NovoNo = (TArvore)malloc(sizeof(TNo));

    NovoNo->Chave = Valor;
    NovoNo->direito = NULL;
    NovoNo->esquerdo = NULL;

    return(NovoNo);
}

TArvore Insere_TArvore(TArvore Raiz, TArvore No)
{
    if(Raiz == NULL)
        return(No);

    if(No->Chave < Raiz->Chave)
        Raiz->esquerdo = Insere_TArvore(Raiz->esquerdo, No);
    else
        Raiz->direito = Insere_TArvore(Raiz->direito, No);

    return Raiz;
}

TArvore Busca_No(TArvore Raiz, TChave Valor, TArvore *Pai)
{
    TArvore Aux = Raiz;

    *Pai = NULL;

    while(Aux){
        if(Aux->Chave == Valor)
            return(Aux);
        
        *Pai = Aux;

        if(Valor < Aux->Chave)
            Aux = Aux->esquerdo;
        else    
            Aux = Aux->direito;
    }
    return (NULL);
}

TArvore Pesquisa(TChave Valor, TArvore Raiz)
{
    if(Raiz == NULL)
        return(NULL);

    if(Raiz->Chave == Valor)
        return(Raiz);

    if(Raiz->Chave > Valor)
        return Pesquisa(Valor, Raiz->esquerdo);
    return Pesquisa(Valor, Raiz->direito);
}

void PosOrdem(TArvore No)
{
    if (No != NULL) {
        PosOrdem(No->esquerdo);
        PosOrdem(No->direito);
        printf("%d\n", No->Chave);
    }
}

//TAD Árvore Binária.

int main ()
{
    int tamanho, i, j;

    TChave Pre_Ordem[MAX], Em_Ordem[MAX];
    TArvore Arv_Bin, No;

    scanf("%d", &tamanho);

    Inicializa_Vetor(Pre_Ordem, tamanho);

    Inicializa_Vetor(Em_Ordem, tamanho);

    for (i = 0; i < tamanho; i++)
        scanf("%d", &Pre_Ordem[i]);

    /*for (int i = 0; i < tamanho; i++)
        printf("%d", Pre_Ordem[i]);

    printf("\n");*/

    for (i = 0; i < tamanho; i++)
        scanf("%d", &Em_Ordem[i]);

    for(j = 0; i < tamanho; j++)
    {
        No = CriaNo_TArvore(Pre_Ordem[i]);
        Arv_Bin = Insere_TArvore(Arv_Bin, No);
    }

    PosOrdem(Arv_Bin);

    return 0;
}