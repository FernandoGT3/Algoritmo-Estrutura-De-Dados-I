// Luiz Fernando -- Matricula: 159325
// Tarefa 005
/* Um programa que dada uma lista de pacotes e uma lista de dependência entre os pacotes
determina o número de dependentes, o número de dependências e a lista de dependências de
cada pacote. Implementa o TAD Grafo usando matrizes de adjacência. */

#include <stdlib.h>
#include <stdio.h>

#define MVERTICES 100
#define MAX 10000
#define INICIO 0

// TAD Lista

typedef int TVertice;

typedef int TApontador;

typedef int TAresta;

typedef struct
{
    TVertice Vertices[MAX];
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
int Insere_TLista(TLista *pLista, TApontador p, TVertice x)
{
    TApontador aux;

    if ((pLista->Ultimo == MAX) || (p < pLista->Primeiro) || (p > pLista->Ultimo))
        return 0;

    for (aux = pLista->Ultimo - 1; aux >= p; aux--)
        pLista->Vertices[aux + 1] = pLista->Vertices[aux];

    pLista->Vertices[p] = x;
    pLista->Ultimo++;

    return 1;
}

//Função que retira um item da lista
int TLista_Retira(TLista *pLista, TApontador p, TAresta *pA)
{
    TApontador aux;

    if (TLista_Eh_Vazia(pLista) || (p < pLista->Primeiro) || (p >= pLista->Ultimo))
        return 0;

    *pA = pLista->Vertices[p];

    for (aux = p + 1; aux < pLista->Ultimo; aux++)
        pLista->Vertices[aux - 1] = pLista->Vertices[aux];

    pLista->Ultimo--;

    return 1;
} 

// TAD Lista.

// TAD Grafo Matriz de Adjacência

typedef int TVertice;

typedef int TAresta;

typedef struct
{
    int IncideAresta;
    TAresta Aresta;
} TAdjacencia;

typedef struct
{
    TAdjacencia Adj[MVERTICES][MVERTICES];
    int NVertices;
    int NArestas;
} TGrafo;

//Iniciando as variaveis do grafo
int Inicializa_TGrafo(TGrafo *pGrafo, int NumVertices)
{
    TVertice x, y; 

    if (NumVertices > MVERTICES)
        return 0;

    pGrafo->NVertices = NumVertices;
    pGrafo->NArestas = 0;
    for (x = 0; x < pGrafo->NVertices; x++)
        for (y = 0; y < pGrafo->NVertices; y++)
            pGrafo->Adj[x][y].IncideAresta = 0;

    return 1;
}

//Retorna se existe a aresta (x, y) no grafo
int ExisteAresta_TGrafo(TGrafo *pGrafo, TVertice x, TVertice y)
{
    return pGrafo->Adj[x][y].IncideAresta;
}

//Retorna o numero de vertices do grafo
int NVertices_TGrafo(TGrafo *pGrafo)
{
    return (pGrafo->NVertices);
}

//Retorna o numero de arestas do grafo
int NArestas_TGrafo(TGrafo *pGrafo)
{
    return (pGrafo->NArestas);
}

//Insere a aresta incidente aos vertices x e y no grafo
int InsereAresta_TGrafo(TGrafo *pGrafo, TVertice x, TVertice y, TAresta ValorAresta)
{

    pGrafo->Adj[x][y].IncideAresta = 1;
    pGrafo->Adj[x][y].Aresta = ValorAresta;

    pGrafo->NArestas++;
    return 1;
}

//Retira a aresta incidente aos vertices x e y no grafo
int RetiraAresta_TGrafo(TGrafo *pGrafo, TVertice x, TVertice y, TAresta *pValorAresta)
{
    if (ExisteAresta_TGrafo(pGrafo, x, y))
    {
        *pValorAresta = pGrafo->Adj[x][y].Aresta;
        pGrafo->Adj[x][y].IncideAresta = 0;

        pGrafo->NArestas--;
        return 1;
    }
    else
        return 0;
}

//Retorna a lista de adjacentes do vertice x no grafo 
TLista *ListaAdjacentes_TGrafo(TGrafo *pGrafo, TVertice x)
{
    TLista *pLista;
    TVertice y;

    pLista = (TLista *)malloc(sizeof(TLista));

    Inicializa_TLista(pLista);

    for (y = 0; y < pGrafo->NVertices + 1; y++)
        if (ExisteAresta_TGrafo(pGrafo, x, y))
            Insere_TLista(pLista, Tamanho_TLista(pLista), y);

    return pLista;
}
// TAD Grafo Matriz de Adjacência.

int main()
{
    int n, i, j;
    int *Dependentes;

    TAresta d;
    TVertice u, v;
    TGrafo Grafos_Pacotes;
    TLista *Dependencias;    

    scanf("%d %d", &n, &d); //lendo número de pacotes do SO(variavel n) e o número de relações de dependência entre pacotes(variável d)

    Inicializa_TGrafo(&Grafos_Pacotes, n); //inicializando o grafo

    Dependentes = malloc((n + 1) * sizeof(int));
    
    for(i = 0; i < n; i++)
        Dependentes[i] = 0; //inicializando o vetor

    for (i = 1; i < d + 1; i++)
    {
        scanf("%d %d", &u, &v);
        //printf("%d %d\n", u,v);
        Dependentes[v] = Dependentes[v] + 1; //armazenando quantas vezes um pacote é uma dependência de um outro pacote
        if ((u <= n && v <= n) && (u >= 1 && v >= 1)) //condição para que as dependencias não sejam 0 e nem maior que n
            InsereAresta_TGrafo(&Grafos_Pacotes, u, v, d); //inserindo as aresta de dependências no grafo
    }
    
    for (i = 1; i <= n; i++)
    {
        Dependencias = (TLista *)malloc(sizeof(TLista));
        Dependencias = ListaAdjacentes_TGrafo(&Grafos_Pacotes, i);
        printf("%d ", i); //imprimindo o número do pacote
        
        printf("%d ", Dependentes[i]); //imprimindo quantas vezes este pacote é uma dependência de um outro pacote(dependentes)

        printf("%d ", Tamanho_TLista(Dependencias)); //imprimindo o tamanho da lista, que seria o número de dependências
        
        if(Tamanho_TLista(Dependencias) > 0){;
            while(Tamanho_TLista(Dependencias) != 0) 
            {
                if(TLista_Retira(Dependencias, 0, &d) != 0) //imprimindo a lista de dependências
                printf("%d ", d);
            }
             printf("\n");
        }
        else
        {
            printf("\n");
        }
        free(Dependencias);
    }

    free(Dependentes);

    return 0;
}