// Luiz Fernando -- Matricula: 159325
// Tarefa 009
/* Programa que implementa as operações básicas do algoritmo de pesquisa em 
árvores binárias de busca, conforme as especificações abaixo. Usa um procedimento 
separado para as seguintes operações: (1) pesquisa, (2) inserção e (3) remoção. 
Na operação de remoção, dá a preferência para a promoção da menor chave da subárvore 
à direita, ou seja, o sucessor.
Todos os números exceto o último serão inseridos na árvore binária de busca. 
O último número será utilizado como chave a ser pesquisada na árvore. 
No caso de uma pesquisa sem sucesso, esse número também será inserido na árvore, caso contrário, 
ele deverá ser removido da árvore.*/
 
#include <stdio.h>
#include <stdlib.h>
 
//TAD Árvore Binária de Busca
 
typedef int TChave;
 
typedef struct {
    TChave Chave;
/* outros componentes */
} TItem;
 
typedef struct SNo *TArvBin;
 
typedef struct SNo {
    TItem Item;
    TArvBin Esquerda, Direita;
} TNo;
 
typedef TArvBin TABB;
 
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
 
//Insere o item x com chave X na árvore binária de busca e retorna true, caso ele não esteja
// na árvore; caso contrário, retorna false
int TABB_Insere(TABB *pNo, TItem x)
{
    if (*pNo == NULL) {
        *pNo = TArvBin_CriaNo(x, TArvBin_Inicia(), TArvBin_Inicia());
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave)
        return TABB_Insere(&(*pNo)->Esquerda, x);
    else if (x.Chave > (*pNo)->Item.Chave)
        return TABB_Insere(&(*pNo)->Direita, x);
    else
        return 0; // retorna 0 caso o item ja estiver na arvore
}
 
//Retorna a árvore binaria de busca contendo o item com chave x; caso não haja nenhum item
// com chave x na árvore, retorna uma árvore vazia
TABB TABB_Pesquisa(TABB No, TChave x)
{
    if (No == NULL)
        return NULL;
    else if (x < No->Item.Chave)
        return TABB_Pesquisa(No->Esquerda, x);
    else if (x > No->Item.Chave)
        return TABB_Pesquisa(No->Direita, x);
    else
        return No;
}
 
//Retira o item com chave X na árvore binária de busca e retorna true, caso ele esteja na
// árvore; caso contrário, retorna false
int TABB_Remove(TABB *p, TChave x)
{
    TABB q;
 
    if (*p == NULL)
        return 0; // retorna 0 caso o item nao esteja na arvore
    else if (x < (*p)->Item.Chave)
        return TABB_Remove(&(*p)->Esquerda, x);
    else if (x > (*p)->Item.Chave)
        return TABB_Remove(&(*p)->Direita, x);
    else {
        q = *p;
        if (q->Esquerda == NULL)
            *p = q->Direita;
        else if (q->Direita == NULL)
            *p = q->Esquerda;
        else // possui dois filhos
            TABB_Sucessor(&q, &q->Direita); // equivalente a Predecessor(&q, &q->Esq);
        free(q);
        return 1;
    }
}
 
void TABB_Sucessor(TABB *q, TABB *r)
{
    if ((*r)->Esquerda != NULL)
        TABB_Sucessor(q, &(*r)->Esquerda);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Direita;
    }
}
 
void Exibir_TArvore(TABB No)
{
    if(No != NULL)
    {
        printf("(");
        printf("C%d", No->Item.Chave);
        Exibir_TArvore(No->Esquerda);
        Exibir_TArvore(No->Direita);
        printf(")");
    }
    else{
        printf("(");
        printf(")");
    }
}
 
//TAD Árvore Binária de Busca.
 
int main()
{
    int num, i;
    
    TItem num_insere, num_remove;
 
    TABB Arvore_Binaria;
 
    //Arvore_Binaria = (TABB *)malloc(sizeof(TArvBin));
 
    Arvore_Binaria = TArvBin_Inicia();
 
    scanf("%d", &num);
 
    for(i = 0; i < num; i++)
    {
        scanf("%d", &num_insere);
 
        TABB_Insere(&Arvore_Binaria, num_insere);
        
        //printf("%d ", num_insere.Chave);
    }
    
    scanf("%d", &num_remove);
 
    if(TABB_Pesquisa(Arvore_Binaria, num_remove.Chave) == NULL)
        TABB_Insere(&Arvore_Binaria, num_remove);
    else
        TABB_Remove(&Arvore_Binaria, num_remove.Chave);
 
    Exibir_TArvore(Arvore_Binaria);
 
    return 0;
}