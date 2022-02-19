// Luiz Fernando -- Matricula: 159325
// Tarefa 005
/* Um programa que dada uma lista de pacotes e uma lista de dependência entre os pacotes
determina o número de dependentes, o número de dependências e a lista de dependências de
cada pacote. Implementa o TAD Grafo usando listas de adjacência. */
 
#include <stdlib.h>
#include <stdio.h>
 
#define MAXVERTICES 100
#define MAX 10000
#define INICIO 0
 
// TAD Lista
 
typedef int TVertice;
 
typedef int TAresta;
 
typedef struct
{
    TVertice Vertice;
    TAresta Aresta;
} TAdjacencia;
 
typedef int TApontador;
 
typedef struct
{
    TAdjacencia Adjacentes[MAX];
    TApontador Primeiro, Ultimo;
} TLista;
 
//Procedimento para inicializar a lista
void Inicializa_TLista(TLista *pLista)
{
    pLista->Primeiro = INICIO;
    pLista->Ultimo = pLista->Primeiro; // porque poderia começar com 0 ou 1, então é mais facil usar um define e dependendo da ocasião mudo nele
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
int Insere_TLista(TLista *pLista, TApontador p, TAdjacencia x)
{
    TApontador aux;
 
    if ((pLista->Ultimo == MAX) || (p < pLista->Primeiro) || (p > pLista->Ultimo))
        return 0;
 
    for (aux = pLista->Ultimo - 1; aux >= p; aux--)
        pLista->Adjacentes[aux + 1] = pLista->Adjacentes[aux];
 
    pLista->Adjacentes[p] = x;
 
    pLista->Ultimo++;
 
    return 1;
}
 
//Função que retira um item da lista
int TLista_Retira(TLista *pLista, TApontador p, TAdjacencia *pA)
{
    TApontador aux;
 
    if (TLista_Eh_Vazia(pLista) || (p < pLista->Primeiro) || (p >= pLista->Ultimo))
        return 0;
 
    *pA = pLista->Adjacentes[p];
 
    for (aux = p + 1; aux < pLista->Ultimo; aux++)
        pLista->Adjacentes[aux - 1] = pLista->Adjacentes[aux];
 
    pLista->Ultimo--;
 
    return 1;
}
 
// TAD Lista.
 
// TAD Grafo Lista de Adjacência
 
typedef struct
{
    TLista Adj[MAXVERTICES];
    int NVertices;
    int NArestas;
} TGrafo;
 
//Iniciando as variaveis do grafo
int Inicializa_TGrafo(TGrafo *pGrafo, int NumVertices)
{
    TVertice x;
 
    if (NumVertices > MAXVERTICES)
        return 0;
 
    pGrafo->NVertices = NumVertices;
    pGrafo->NArestas = 0;
 
    for (x = 0; x < pGrafo->NVertices; x++)
        Inicializa_TLista(&pGrafo->Adj[x]);
 
    return 1;
}
 
//Retorna se existe a aresta (x, y) no grafo
int ExisteAresta_TGrafo(TGrafo *pGrafo, TVertice x, TVertice y)
{
    TAdjacencia Adj;
    TLista *Lista_Adjacentes;
 
    int Existe = 0;
 
    Lista_Adjacentes = (TLista *)malloc(sizeof(TLista));
 
    Inicializa_TLista(Lista_Adjacentes);
 
    while (TLista_Retira(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]) - 1, &Adj))
    {
        Insere_TLista(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes), Adj);
        Existe = (Adj.Vertice == y);
 
        if (Existe)
            break;
    }
 
    while (TLista_Retira(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes) - 1, &Adj))
        Insere_TLista(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]), Adj);
 
    free(Lista_Adjacentes);
 
    return (Existe);
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
    TAdjacencia Adj;
 
    Adj.Vertice = y;
    Adj.Aresta = ValorAresta;
 
    if (Insere_TLista(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]), Adj))
    {
        pGrafo->NArestas++;
        return 1;
    }
    else
        return 0;
}
 
//Retira a aresta incidente aos vertices x e y no grafo
int RetiraAresta_TGrafo(TGrafo *pGrafo, TVertice x, TVertice y, TAresta *pValorAresta)
{
    TAdjacencia Adj;
    TLista *Lista_Adjacentes;
 
    int IncideAresta = 0;
 
    Lista_Adjacentes = (TLista *)malloc(sizeof(TLista));
 
    Inicializa_TLista(Lista_Adjacentes);
 
    while (!IncideAresta && TLista_Retira(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]) - 1, &Adj))
    {
        if (Adj.Vertice == y)
        {
            *pValorAresta = Adj.Aresta;
            pGrafo->NArestas--;
            IncideAresta = 1;
        }
        else
            Insere_TLista(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes), Adj);
    }
 
    while (TLista_Retira(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes) - 1, &Adj))
        Insere_TLista(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]), Adj);
 
    free(Lista_Adjacentes);
 
    return IncideAresta;
}
 
//Retorna a lista de adjacentes do vertice x no grafo 
TLista *ListaAdjacentes_TGrafo(TGrafo *pGrafo, TVertice x)
{
    TLista *pLista, *Lista_Adjacentes;
    TAdjacencia Adj;
 
    pLista = (TLista *)malloc(sizeof(TLista));
 
    Lista_Adjacentes = (TLista *)malloc(sizeof(TLista));
    
    Inicializa_TLista(pLista);
    Inicializa_TLista(Lista_Adjacentes);
 
    while (TLista_Retira(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]) - 1, &Adj))
        Insere_TLista(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes), Adj);
 
    while (TLista_Retira(Lista_Adjacentes, Tamanho_TLista(Lista_Adjacentes) - 1, &Adj))
    {
        Insere_TLista(&pGrafo->Adj[x], Tamanho_TLista(&pGrafo->Adj[x]), Adj);
        Insere_TLista(pLista, Tamanho_TLista(pLista), Adj);
    }
 
    free(Lista_Adjacentes);
 
    return pLista;
}
 
// TAD Grafo Lista de Adjacência.
 
int main()
{
    int n, i, d;
    int *Dependentes;
 
    TVertice u, v;
    TGrafo Grafos_Pacotes;
    TLista *Dependencias;
 
    scanf("%d %d", &n, &d);//lendo número de pacotes do SO(variavel n) e o número de relações de dependência entre pacotes(variável d)
 
    Inicializa_TGrafo(&Grafos_Pacotes, n); //inicializando o grafo
 
    Dependentes = malloc((n + 1) * sizeof(int));
 
    for (i = 0; i < n; i++)
        Dependentes[i] = 0; //inicializando o vetor
 
    for (i = 1; i < d + 1; i++)
    {
        scanf("%d %d", &u, &v);
        // printf("%d %d\n", u,v);
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
 
        if (Tamanho_TLista(Dependencias) > 0)
        {
            while (Tamanho_TLista(Dependencias) != 0)
            {
                if (TLista_Retira(Dependencias, 0, &d) != 0) //imprimindo a lista de dependências
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