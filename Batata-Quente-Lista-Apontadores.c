// Luiz Fernando -- Matricula: 159325
// Tarefa 004
/*Um programa que determina a ordem em que as crianças serão eliminadas
durante o jogo da batata quente. Ao som de uma música. As crianças passam
a batata de mão em mão ao redor do círculo em sentido horário, até que a
música pare de tocar. Quando a música parar, a criança que estiver segurando
a batata deve deixar o jogo, e as outras crianças reduzem o círculo.
Esse processo continua até que só reste uma criança, que é declarada vencedora.
Suponha que a musica sempre pare de tocar após a batata ter sido passada K vezes..*/

// ======================== LISTA POR APONTADORES =====================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 21

// TAD Lista Apontador

typedef int TChave;

typedef struct
{
    TChave ID;
    char Nome[MAXCHAR];
} TItem;

typedef struct SCelula *TApontador;

typedef struct SCelula
{
    TItem Criancas;
    TApontador Prox;
} TCelula;

typedef struct
{
    TApontador Primeiro, Ultimo;
    int Tamanho;
} TLista;

//Procedimento para inicializar a lista
void Inicializa_TLista(TLista *pLista_Criancas)
{
    pLista_Criancas->Primeiro = NULL;
    pLista_Criancas->Ultimo = pLista_Criancas->Primeiro;
    pLista_Criancas->Tamanho = 0;
}

//Função que retorna se a lista esta vazia ou não
int TLista_Eh_Vazia(TLista *pLista_Criancas)
{
    return (pLista_Criancas->Primeiro == NULL); // || pLista->Primeiro == pLista->Ultimo
}

//Função que retona o tamanho da lista
int Tamanho_TLista(TLista *pLista_Criancas)
{
    return (pLista_Criancas->Tamanho);
}

//Função que retorna um apontador, que aponta para a i-nésima posição na lista
/* É uma função que "percorre" a lista até encontrar a posição desejada, e retorna um apontador para mais tarde
retirarmos ou inserirmos items */
TApontador Retorna_TLista(TLista *pLista_Criancas, int posicao)
{
    TApontador pApontador_Aux;
    int i = 0;

    pApontador_Aux = pLista_Criancas->Primeiro;

    while ((pApontador_Aux != NULL) && (i != posicao))
    {
        pApontador_Aux = pApontador_Aux->Prox;
        i++;
    }

    return pApontador_Aux;
}

//Função que insere um item na lista na primeira posição
int Insere_Primeiro_TLista(TLista *pLista_Criancas, TItem x)
{
    TApontador pNovo;

    pNovo = (TApontador)malloc(sizeof(TCelula));

    pNovo->Criancas = x;
    pNovo->Prox = pLista_Criancas->Primeiro;

    if (TLista_Eh_Vazia(pLista_Criancas))
        pLista_Criancas->Ultimo = pNovo;

    pLista_Criancas->Primeiro = pNovo;
    pLista_Criancas->Tamanho++;

    return 1;
}

//Função que insere um item na lista na ultima posição
int Insere_Ultimo_TLista(TLista *pLista_Criancas, TItem x)
{
    TApontador pNovo;

    pNovo = (TApontador)malloc(sizeof(TCelula));

    pNovo->Criancas = x;
    pNovo->Prox = NULL;

    if (TLista_Eh_Vazia(pLista_Criancas))
        pLista_Criancas->Primeiro = pNovo;
    else
        pLista_Criancas->Ultimo->Prox = pNovo;

    pLista_Criancas->Ultimo = pNovo;
    pLista_Criancas->Tamanho++;

    return 1;
}

//Função que insere um item na lista na posição em que o pApontador_Aux se encontra.
int Insere_Meio_TLista(TLista *pLista_Criancas, TApontador pApontador_Aux, TItem x)
{
    TApontador pAnterior, pNovo;

    if (pApontador_Aux == pLista_Criancas->Primeiro)
        return Insere_Primeiro_TLista(pLista_Criancas, x);
    else if (pApontador_Aux == NULL)
        return Insere_Ultimo_TLista(pLista_Criancas, x);
    else
    {
        pAnterior = pLista_Criancas->Primeiro;
        while ((pAnterior != pLista_Criancas->Ultimo) && (pAnterior->Prox != pApontador_Aux))
            pAnterior = pAnterior->Prox;

        if (pAnterior == pLista_Criancas->Ultimo)
            return 0;

        pNovo = (TApontador)malloc(sizeof(TCelula));

        pNovo->Criancas = x;
        pNovo->Prox = pAnterior->Prox;
        pAnterior->Prox = pNovo;

        pLista_Criancas->Tamanho++;
        return 1;
    }
}

//Função que retira um item da lista da primeira posição
int RetiraPrimeiro_TLista(TLista *pLista_Criancas, TItem *pX)
{
    TApontador pAux;

    if (TLista_Eh_Vazia(pLista_Criancas))
        return 0;

    pAux = pLista_Criancas->Primeiro;
    pLista_Criancas->Primeiro = pAux->Prox;

    *pX = pAux->Criancas;

    free(pAux);
    pLista_Criancas->Tamanho--;

    return 1;
}

//Função que retira um item da lista da ultima posição
int RetiraUltimo_TLista(TLista *pLista_Criancas, TItem *pX)
{
    TApontador pAnterior, pAux;

    pAnterior = pLista_Criancas->Primeiro;

    if (pAnterior == pLista_Criancas->Ultimo)
        return RetiraPrimeiro_TLista(pLista_Criancas, pX);

    else
    {
        while (pAnterior->Prox != pLista_Criancas->Ultimo)
            pAnterior = pAnterior->Prox;

        pAux = pLista_Criancas->Ultimo;

        pAnterior->Prox = NULL;
        pLista_Criancas->Ultimo = pAnterior;

        *pX = pAux->Criancas;

        free(pAux);
        pLista_Criancas->Tamanho--;

        return 1;
    }
}

//Função que retira um item da lista da posição em que o pApontador_Aux se encontra.
int TLista_Retira(TLista *pLista_Criancas, TApontador pApontador_Aux, TItem *pX)
{
    TApontador pAnterior, pAux;

    if (pApontador_Aux == pLista_Criancas->Primeiro)
        return RetiraPrimeiro_TLista(pLista_Criancas, pX);
    else if (pApontador_Aux == pLista_Criancas->Ultimo)
        return RetiraUltimo_TLista(pLista_Criancas, pX);
    else
    {
        pAnterior = pLista_Criancas->Primeiro;
        while ((pAnterior != pLista_Criancas->Ultimo) && (pAnterior->Prox != pApontador_Aux))
            pAnterior = pAnterior->Prox;

        if (pAnterior == pLista_Criancas->Ultimo)
            return 0;

        pAux = pAnterior->Prox;
        pAnterior->Prox = pAux->Prox;

        *pX = pAux->Criancas;

        free(pAux);
        pLista_Criancas->Tamanho--;

        return 1;
    }
}

// TAD Lista Apontador.

int main()
{
    int n, k, i;

    TLista *Lista_Criancas;
    TItem *Eliminado;
    TItem Info_Criancas;
    TApontador aux;

    scanf("%d %d", &n, &k);

    Lista_Criancas = (TLista *)malloc(sizeof(TLista)); //alocando dinâmicamente o espaço de memória para a variável

    Inicializa_TLista(Lista_Criancas); //inicializando a lista

    aux = (TApontador)malloc(sizeof(TCelula)); //alocando dinâmicamente o espaço de memória para a variável

    for (i = 0; i < n; i++) //laço para ler as informações das n crianças
    {
        scanf("%s", Info_Criancas.Nome);

        Info_Criancas.ID = i;

        aux = Retorna_TLista(Lista_Criancas, i);
        Insere_Meio_TLista(Lista_Criancas, aux, Info_Criancas); //inserindo as crianças na lista
    }

    Eliminado = (TItem *)malloc(sizeof(TItem)); //alocando dinâmicamente o espaço de memória para a variável

    i = k; //variavel que indica onde a batata irá parar
    while (Tamanho_TLista(Lista_Criancas) != 1)
    {
        aux = Retorna_TLista(Lista_Criancas, i);
        if (TLista_Retira(Lista_Criancas, aux, Eliminado) != 0) //elimiando a criança
            printf("%s\n", Eliminado->Nome);

        i = (i + k) % Tamanho_TLista(Lista_Criancas); //como é uma rotação( do ultimo vai para o primeiro) soma i com k e pega o resto da divisão com o tamanho da lista
    }

    free(aux);

    if (RetiraPrimeiro_TLista(Lista_Criancas, Eliminado) != 0) //imprimindo o vencedor, a ultima criança
        printf("%s", Eliminado->Nome);

    free(Lista_Criancas);

    return 0;
}