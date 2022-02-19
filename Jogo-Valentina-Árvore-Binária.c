// Luiz Fernando -- Matricula: 159325
// Tarefa 008
/* A pequena Valentina gostava muito de brincar com árvores binárias. 
Seu jogo favorito era construir árvores binárias aleatórias com números 
inteiros nos nós. Para salvar suas árvores para uso futuro, ela escreveu 
duas sequências numéricas para cada árvore: o percurso prefixo e o percurso
infixo. Agora, anos depois, olhando para as sequências numéricas, ela notou 
que reconstruir as árvores era realmente possível, mas só porque ela não havia 
usado o mesmo número duas vezes na mesma árvore. Dada duas sequências numéricas
representando os percursos pré-ordem e em-ordem. UM programa que construe a árvore binária e, 
em seguida, imprime a sequência numérica referente ao seu percurso pós-ordem.*/
 
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1000
 
//TAD Árvore Binária
 
typedef int TChave;
 
typedef struct {
    TChave Chave;
} TItem;
 
typedef struct SNo *TArvBin;
 
typedef struct SNo {
    TItem Item;
    TArvBin Esquerda, Direita;
} TNo;
 
//Procedimento que inicializa o vetor
void Inicializa_Vetor(TChave v[MAX], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        v[i] = 0;
}
 
/*TNo* TArvBin_Inicia(TItem x)
{ 
    TArvBin Arv_Novo;
 
    Arv_Novo = (TArvBin) malloc(sizeof(TNo));
 
    Arv_Novo->Item = x;
    Arv_Novo->Esquerda = NULL;
    Arv_Novo->Direita = NULL;
    
    return Arv_Novo;
}
*/
 
//Inicia uma árvore binária vazia
TArvBin TArvBin_Inicia()
{
    return NULL;
}
 
//Retorna um apontador para um nó contendo o item x e as subárvores Esq e Dir
TArvBin TArvBin_CriaNo(TItem x, TArvBin Esq, TArvBin Dir) 
{
    TArvBin No;
    
    No = (TArvBin) malloc(sizeof(TNo));
    
    No->Item = x;
    No->Esquerda = Esq;
    No->Direita = Dir;
 
    return No;
}
 
//Retorna true se a árvore não possuir nenhum descendente; caso contrário, retorna false
int TArvBin_EhFolha(TNo *No)
{
    return ((No == NULL) || ((No->Esquerda == NULL) && (No->Direita == NULL)));
}
 
//Retorna a subárvore esquerda da raiz da árvore
TArvBin TArvBin_SubarvoreEsquerda(TNo *No) 
{
    return No->Esquerda;
}
 
//Retorna a subárvore direita da raiz da árvore
TArvBin TArvBin_SubarvoreDireita(TNo *No) 
{
    return No->Direita;
}
 
//Função que insere uma subárvore a esquerda
TNo* TArvBin_Insere_Esquerda (TNo *No, TItem x) 
{ 
    No->Esquerda = (TNo*) malloc(sizeof(TNo));
    No->Esquerda->Item = x;
 
    return No;
 
    /*TNo *Novo_No;
 
    Novo_No = (TNo*) malloc(sizeof(TNo));
 
    Novo_No->Item = x;
    No->Esquerda = Novo_No;*/
}
 
//Função que insere uma subárvore a direita
TNo* TArvBin_Insere_Direita (TNo *No, TItem x) 
{ 
    TNo *Novo_No;
 
    Novo_No = (TNo*) malloc(sizeof(TNo));
 
    Novo_No->Item = x;
    No->Direita = Novo_No;
 
    return No;
 
    //No->Direita = (TNo*) malloc(sizeof(TNo));
    //No->Direita->Item = x;
}
 
//Libera a memória ocupada pela árvore
void TArvBin_Libera(TNo *No) 
{
    if (No != NULL) 
    {
        TArvBin_Libera(No->Esquerda);
        TArvBin_Libera(No->Direita);
        
        free(No);
    }
}
 
//Percorre a árvore de maneira pos-ordem e printa os dados
void PosOrdem(TArvBin No)
{
    if (No != NULL) {
        PosOrdem(No->Esquerda);
        PosOrdem(No->Direita);
        printf("%d\n", No->Item.Chave);
    }
}
 
//Retorna a árvore binaria de busca contendo o item com chave x; caso não haja nenhum item
// com chave x na árvore, retorna uma árvore vazia
int Pesquisa(TItem *EmOrdem, int Esq, int Dir, TChave x)
{
    int Raiz;
 
    for (Raiz = Esq; Raiz <= Dir; Raiz++)
        if (EmOrdem[Raiz].Chave == x)
            return Raiz;
 
    return 0;
}
 
//Função que constroi uma árvore a partir de uma sequência em-ordem e outra pre-ordem 
TArvBin ConstroiRecursivo(TItem *PreOrdem, int *pNo, TItem *EmOrdem, int Esq, int Dir)
{
    TArvBin pEsquerda, pDireita;
    TItem Item;
 
    int Raiz;
 
    if (Esq <= Dir) {
        Item = PreOrdem[(*pNo)++];
        Raiz = Pesquisa(EmOrdem, Esq, Dir, Item.Chave);
        pEsquerda = ConstroiRecursivo(PreOrdem, pNo, EmOrdem, Esq, Raiz-1);
        pDireita = ConstroiRecursivo(PreOrdem, pNo, EmOrdem, Raiz+1, Dir);
 
        return TArvBin_CriaNo(Item, pEsquerda, pDireita);
    }
 
    return TArvBin_Inicia();
}
 
//Função que recebe uma sequência pre-ordem e outra em-ordem, e com isso constroi uma árvore
TArvBin Constroi(TItem *PreOrdem, TItem *EmOrdem, int n)
{
    int No;
    No = 0;
    
    return ConstroiRecursivo(PreOrdem, &No, EmOrdem, 0, n-1);
}
 
//TAD Árvore Binária.
 
int main ()
{
    int tamanho, i, j;
 
    TItem Pre_Ordem[MAX], Em_Ordem[MAX];
 
    TArvBin Arvore;
 
    scanf("%d", &tamanho);
 
    Inicializa_Vetor(Pre_Ordem, tamanho);
 
    Inicializa_Vetor(Em_Ordem, tamanho);
 
    for (i = 0; i < tamanho; i++)
        scanf("%d", &Pre_Ordem[i]);
 
    //for (int i = 0; i < tamanho; i++)
      //  printf("%d", Pre_Ordem[i]);
 
    //printf("\n");
 
    for (j = 0; j < tamanho; j++)
        scanf("%d", &Em_Ordem[j]);
 
    //for (int j = 0; j < tamanho; j++)
      // printf("%d", Em_Ordem[j]);
 
    Arvore = TArvBin_Inicia();
 
    Arvore = Constroi(&Pre_Ordem, &Em_Ordem, tamanho);
 
    PosOrdem(Arvore);
 
    TArvBin_Libera(Arvore);
    
    return 0;
}