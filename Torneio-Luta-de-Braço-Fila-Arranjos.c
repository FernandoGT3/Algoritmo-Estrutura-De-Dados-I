// Luiz Fernando -- Matricula: 159325
// Tarefa 003
/* Um programa que determina quem vai ganhar o torneio de luta de braço.
 
Esse torneio conta com a participação de 2^N competidores, que são numerados de 1 a 2^N.
O primeiro concorrente (C1) irá competir com o segundo competidor (C2), o terceiro (C3)
vai competir com o quarto (C4), e assim por diante. O vencedor de C1 e C2 irá competir
com o vencedor de C3 e C4. O vencedor de C5 e C6 vai competir com o vencedor de C7 e C8,
e assim por diante. Cada participante tem uma força inicial Pi. Quando dois competidores
lutam, o mais forte é quem ganha a partida. Após cada luta, o vencedor tem a sua força
reduzida o equivalente à força de seu oponente. No entanto, antes de sua próxima luta,
ele tem tempo para recuperar sua força em K unidades. Porém, sua força não poderá exceder
a sua força inicial (Pi). Se dois competidores possuem uma força igual, então, o competidor
com menor índice vai ganhar. */
 
// ======================== FILA POR ARRANJOS =====================================
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define MAX 32769
 
// TAD Fila:
 
typedef int TChave;
 
typedef struct
{
    TChave ID;
    int Forca_Inicial;
    int Forca;
} TItem;
 
typedef int TApontador;
 
typedef struct
{
    TItem Lutador[MAX];
    TApontador Primeiro, Ultimo;
} TFila;
 
//Procedimento para inicializar a lista
void Inicia_TFila(TFila *pFilaLutadores)
{
    pFilaLutadores->Primeiro = 0;
    pFilaLutadores->Ultimo = 0;
}
 
//Função que retorna se a lista esta vazia ou não
int TFila_E_Vazia(TFila *pFilaLutadores)
{
    return (pFilaLutadores->Primeiro == pFilaLutadores->Ultimo);
}
 
//Função que retona o tamanho da lista
int Tamanho_TFila(TFila *pFilaLutadores)
{
    if (pFilaLutadores->Ultimo >= pFilaLutadores->Primeiro)
        return (pFilaLutadores->Ultimo - pFilaLutadores->Primeiro);
    else
        return (MAX + pFilaLutadores->Ultimo - pFilaLutadores->Primeiro);
}
 
//Função que enfileira o item na fila
int Enfileira_TFila(TFila *pFilaLutadores, TItem x)
{
    if (pFilaLutadores->Primeiro == (pFilaLutadores->Ultimo + 1) % MAX)
        return 0; /* quer dizer que a fila esta cheia */
 
    pFilaLutadores->Lutador[pFilaLutadores->Ultimo] = x;
    pFilaLutadores->Ultimo = (pFilaLutadores->Ultimo + 1) % MAX;
 
    return 1;
}
 
//Função que desenfileira o item da fila
int Desenfileira_TFila(TFila *pFilaLutadores, TItem *pX)
{
    if (TFila_E_Vazia(pFilaLutadores))
        return 0;
 
    *pX = pFilaLutadores->Lutador[pFilaLutadores->Primeiro];
    pFilaLutadores->Primeiro = (pFilaLutadores->Primeiro + 1) % MAX;
    return 1;
}
 
// TAD Fila.
 
int main()
{
    int n, k, i, Ncompetidores;
 
    TFila FilaLutadores;
    TItem Info_Lutadores, PrimeiroCompetidor, SegundoCompetidor;
 
    scanf("%d %d", &n, &k);
 
    Inicia_TFila(&FilaLutadores); //inicializando a fila
 
    Ncompetidores = pow(2, n);
 
    for (i = 1; i <= Ncompetidores; i++) //laço para ler as informações dos n competidores
    {
        Info_Lutadores.ID = i;
 
        scanf("%d", &Info_Lutadores.Forca_Inicial);
 
        Info_Lutadores.Forca = Info_Lutadores.Forca_Inicial;
 
        Enfileira_TFila(&FilaLutadores, Info_Lutadores);  //enfileirando os competidores
    }
 
    while (Tamanho_TFila(&FilaLutadores) != 1) //enquanto nao ficar um competidor restante eu vou retirando dois a dois
    {
        Desenfileira_TFila(&FilaLutadores, &PrimeiroCompetidor); //desenfileirando o primeiro competidor
        Desenfileira_TFila(&FilaLutadores, &SegundoCompetidor); //desenfileirando o segundo competidor
 
        if (PrimeiroCompetidor.Forca > SegundoCompetidor.Forca) //verificando quem é mais forte
        {
            PrimeiroCompetidor.Forca = (PrimeiroCompetidor.Forca - SegundoCompetidor.Forca) + k; //dando a nova força
 
            if (PrimeiroCompetidor.Forca > PrimeiroCompetidor.Forca_Inicial) //se a nova força for maior que a incial
                PrimeiroCompetidor.Forca = PrimeiroCompetidor.Forca_Inicial; // a força volta a ser a inicial
            Enfileira_TFila(&FilaLutadores, PrimeiroCompetidor);
        }
        else
        {
            if (PrimeiroCompetidor.Forca < SegundoCompetidor.Forca)
            {
                SegundoCompetidor.Forca = (SegundoCompetidor.Forca - PrimeiroCompetidor.Forca) + k;
 
                if (SegundoCompetidor.Forca > SegundoCompetidor.Forca_Inicial)
                    SegundoCompetidor.Forca = SegundoCompetidor.Forca_Inicial;
                Enfileira_TFila(&FilaLutadores, SegundoCompetidor);
            }
            else
            {
                if (PrimeiroCompetidor.Forca == SegundoCompetidor.Forca) // se a força for igual, vence o que possui o menor indice
                {
                    PrimeiroCompetidor.Forca = (PrimeiroCompetidor.Forca - SegundoCompetidor.Forca) + k;
 
                    if (PrimeiroCompetidor.Forca > PrimeiroCompetidor.Forca_Inicial)
                        PrimeiroCompetidor.Forca = PrimeiroCompetidor.Forca_Inicial;
                    Enfileira_TFila(&FilaLutadores, PrimeiroCompetidor);
                }
            }
        }
    }
 
    Desenfileira_TFila(&FilaLutadores, &Info_Lutadores); //desenfileirando o vencedor
 
    printf("%d", Info_Lutadores.ID);
 
    return 0;
}