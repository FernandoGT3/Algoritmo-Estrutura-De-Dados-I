// Luiz Fernando -- Matricula: 159325
// Tarefa 004
/*Um programa que determina a ordem em que as crianças serão eliminadas
durante o jogo da batata quente. Ao som de uma música. As crianças passam
a batata de mão em mão ao redor do círculo em sentido horário, até que a 
música pare de tocar. Quando a música parar, a criança que estiver segurando 
a batata deve deixar o jogo, e as outras crianças reduzem o círculo. 
Esse processo continua até que só reste uma criança, que é declarada vencedora. 
Suponha que a musica sempre pare de tocar após a batata ter sido passada K vezes..*/

// ======================== LISTA POR ARRANJOS =====================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000
#define MAXCHAR 21
#define INICIO 0

// TAD Lista

typedef int TChave;

typedef struct
{
    TChave ID;
    char Nome[MAXCHAR];
} TItem;

typedef int TApontador;

typedef struct
{
    TItem Criancas[MAX];
    TApontador Primeiro, Ultimo;
} TLista;

//Procedimento para inicializar a lista
void Inicializa_TLista(TLista *pLista)
{
    pLista->Primeiro = INICIO; // porque poderia começar com 0 ou 1, então é mais facil usar um define e dependendo da ocasião mudo nele
    pLista->Ultimo = pLista->Primeiro;
}

//Função que retorna se a lista esta vazia ou não
int TLista_Eh_Vazia(TLista *pLista)
{
    return (pLista->Primeiro == pLista->Ultimo);
}

//Função que retona o tamanho da lista
int Tamanho_TLista(TLista *pLista)
{
    return (pLista->Ultimo - pLista->Primeiro);
}

//Função que insere um item na lista
int Insere_TLista(TLista *pLista, TApontador p, TItem x)
{
    TApontador aux;

    if ((pLista->Ultimo == MAX) || (p < pLista->Primeiro) || (p > pLista->Ultimo))
        return 0;

    for (aux = pLista->Ultimo - 1; aux >= p; aux--)
        pLista->Criancas[aux + 1] = pLista->Criancas[aux];

    pLista->Criancas[p] = x;
    pLista->Ultimo++;

    return 1;
}

//Função que retira um item da lista
int TLista_Retira(TLista *pLista, TApontador p, TItem *pX)
{
    TApontador aux;

    if (TLista_Eh_Vazia(pLista) || (p < pLista->Primeiro) || (p >= pLista->Ultimo))
        return 0;

    *pX = pLista->Criancas[p];

    for (aux = p + 1; aux < pLista->Ultimo; aux++)
        pLista->Criancas[aux - 1] = pLista->Criancas[aux];

    pLista->Ultimo--;

    return 1;
} 

// TAD Lista.

int main()
{
    int n, k, i;

    TLista Lista_Criancas;
    TItem Info_Criancas, Eliminado;

    scanf("%d %d", &n, &k);

    Inicializa_TLista(&Lista_Criancas); //inicializando a lista

    for(i = 0; i < n; i++) //laço para ler as informações das n crianças
    {
        scanf("%s", Info_Criancas.Nome);

        Info_Criancas.ID = i;

        Insere_TLista(&Lista_Criancas, i, Info_Criancas); //inserindo as crianças na lista
    }

    i = k; //variavel que indica onde a batata irá para
    while(Tamanho_TLista(&Lista_Criancas) != 1 )
    {
        if(TLista_Retira(&Lista_Criancas, i, &Eliminado) != 0) //elimiando a criança
            printf("%s\n", Eliminado.Nome);
            
        i = (i + k) % Tamanho_TLista(&Lista_Criancas); //como é uma rotação( do ultimo vai para o primeiro) soma i com k e pega o resto da divisão com o tamanho da lista
    }
    
    if(TLista_Retira(&Lista_Criancas, 0, &Eliminado) != 0) //imprimindo o vencedor, a ultima criança
        printf("%s", Eliminado.Nome);
    
    return 0;
}