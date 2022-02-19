// Luiz Fernando -- Matricula: 159325
// Tarefa 005
/*Um programa que que imprime o texto que será visto na tela ao ligar o monitor
Quando você está digitando um texto longo com um teclado quebrado, internamente,
às vezes as teclas "home", "end", "delete", "seta para esquerda" e "seta para direita"
são automaticamente pressionadas. Porém você não está com o monitor ligado.
 
O caractere "[" (abre colchetes) significa que a tecla "home" é pressionada internamente,
posicionado o cursor no início da linha. O caractere "]" (fecha colchetes) significa que
a tecla "end" é pressionada internamente, posicionado o cursor no fim da linha. O caractere
"-" (sinal de menos) significa que a tecla "delete" é pressionada internamente, apagando,
caso possível, o caractere na posição anterior ao cursor. O caractere "<" (sinal de menor) si
gnifica que a tecla "seta para esquerda" é pressionada internamente, posicionando, caso possível,
o cursor na posição anterior. O caractere ">" (sinal de maior) significa que a tecla "seta para direita"
é pressionada internamente, posicionando, caso possível, o cursor na posição seguinte. */
 
// ======================== LISTAS DUPLAS =====================================
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX 50000
 
// TAD Listas Duplas
 
typedef int TChave;
// typedef char TLetra;
 
typedef struct
{
    TChave Chave;
    char Letra;
} TItem;
 
typedef struct SCelula *TApontador;
 
typedef struct SCelula
{
    TItem Caracter;
    TApontador Ant, Prox;
} TCelula;
 
typedef struct
{
    TApontador Ultimo;
    int Tamanho;
} TLista;
 
//Procedimento para inicializar a lista
void Inicializa_TLista(TLista *pLista)
{
    pLista->Ultimo = (TApontador)malloc(sizeof(TCelula));
 
    pLista->Ultimo->Prox = pLista->Ultimo;
    pLista->Ultimo->Ant = pLista->Ultimo;
    pLista->Tamanho = 0;
}
 
//Função que retorna se a lista esta vazia ou não
int TLista_Eh_Vazia(TLista *pLista)
{
    return (pLista->Ultimo->Prox == pLista->Ultimo);
}
 
//Função que retona o tamanho da lista
int Tamanho_TLista(TLista *pLista)
{
    return (pLista->Tamanho);
}
 
//Função que retorna um apontador, que aponta para a i-nésima posição na lista
/* É uma função que "percorre" a lista até encontrar a posição desejada, e retorna um apontador para mais tarde
retirarmos ou inserirmos items */
TApontador Retorna_TLista(TLista *pLista, int posicao)
{
    TApontador pApontador_Aux;
 
    pApontador_Aux = pLista->Ultimo->Prox;
    pApontador_Aux = pApontador_Aux->Prox;
 
    int i = 0;
    while ((pApontador_Aux != pLista->Ultimo->Prox) && (i != posicao))
    {
        pApontador_Aux = pApontador_Aux->Prox;
        i++;
    }
 
    return pApontador_Aux;
}
 
//Função que insere um item na lista na posição em que o pApontador_Aux se encontra.
int Insere_TLista(TLista *pLista, TApontador pApontador_Aux, TItem *x)
{
    TApontador pNovo;
 
    if (pApontador_Aux == NULL)
        return 0;
 
    pNovo = (TApontador)malloc(sizeof(TCelula));
 
    pNovo->Caracter.Chave = x->Chave;
    pNovo->Caracter.Letra = x->Letra;
 
    pNovo->Prox = pApontador_Aux;
    pNovo->Ant = pApontador_Aux->Ant;
 
    pApontador_Aux->Ant->Prox = pNovo;
 
    if (pApontador_Aux->Ant == pLista->Ultimo)
        pLista->Ultimo = pNovo;
 
    pApontador_Aux->Ant = pNovo;
    
    pLista->Tamanho++;
 
    return 1;
}
 
//Função que retira um item da lista da posição em que o pApontador_Aux se encontra.
int Retira_TLista(TLista *pLista, TApontador pApontador_Aux, TItem *pX)
{
    TApontador pAux;
 
    if (TLista_Eh_Vazia(pLista))
        return 0;
 
    pAux = pApontador_Aux;
    pApontador_Aux->Ant->Prox = pApontador_Aux->Prox;
    pApontador_Aux->Prox->Ant = pApontador_Aux->Ant;
 
    if (pAux == pLista->Ultimo)
        pLista->Ultimo = pApontador_Aux->Ant;
 
    *pX = pAux->Caracter;
 
    free(pAux);
 
    pLista->Tamanho--;
    return 1;
}
 
// TAD Listas Duplas.
 
int main()
{
    int i, k, tam;
    char texto[MAX];
 
    TLista *Lista_Caracteres; 
    TApontador aux; //variável que irá receber o apontador retornado da função "Retorna_TLista"
    TItem *Mostrador;
    TItem *Info_Caracteres, *Deletado;
 
    Lista_Caracteres = (TLista *)malloc(sizeof(TLista)); //alocando dinâmicamente o espaço de memória para a variável
 
    gets(texto); //lendo a entrada
 
    Inicializa_TLista(Lista_Caracteres); //inicializando a lista 
 
    tam = strlen(texto); // usando a função strlen para pegar o tamanho do texto e depois usar no laço de repetição
 
    aux = (TApontador)malloc(sizeof(TApontador)); //alocando dinâmicamente o espaço de memória para a variável
 
    k = 0; // variável que representa o cursor
    for (i = 0; i < tam; i++) 
    {
        switch (texto[i])
        {
        case '[':
 
            k = 0; //cursor voltando para o inicio da linha
 
            break;
        case ']':
 
            k = Tamanho_TLista(Lista_Caracteres); //cursor indo para o final da linha
 
            break;
        case '-':
 
            if (k > 0) //se for zero não tem o que ser deletado
            {
                Deletado = (TItem *)malloc(sizeof(TItem));
 
                k = k - 1;
                aux = Retorna_TLista(Lista_Caracteres, k);
                Retira_TLista(Lista_Caracteres, aux, Deletado); //eliminando o caracter anterior ao cursor
 
                free(Deletado);
            }
 
            break;
        case '<':
 
            if (k != 0)
                k--; //posicionando o cursor na posição anterior
 
            break;
        case '>':
 
            if (k < Tamanho_TLista(Lista_Caracteres))
                k++; //posicionando o cursor na proxima posição
 
            break;
 
        default:
            Info_Caracteres = (TItem *)malloc(sizeof(TItem));
 
            aux = Retorna_TLista(Lista_Caracteres, k);
            Info_Caracteres->Chave = i;
            Info_Caracteres->Letra = texto[i]; 
            Insere_TLista(Lista_Caracteres, aux, Info_Caracteres); //inserindo os caracteres nao especiais na lista
            k++;
 
            free(Info_Caracteres);
 
            break;
        }
    }
 
    free(aux);
 
    Mostrador = (TCelula *)malloc(sizeof(TApontador));
 
    while (TLista_Eh_Vazia(Lista_Caracteres) == 0) //laço para pegar letra por letra da lista montada e printar o texto final
    {
        Retira_TLista(Lista_Caracteres, Retorna_TLista(Lista_Caracteres, 0), Mostrador);
        printf("%c", Mostrador->Letra);
    }
 
    free(Mostrador);
 
    free(Lista_Caracteres);
 
    return 0;
}