// Luiz Fernando -- Matricula: 159325
// Tarefa 007
/* São Petersburgo foi fundada no dia 27 de maio de 1703 pelo czar Pedro, o Grande, 
e foi capital imperial da Rússia por um período curto logo após (de 1713 a 1728) e 
depois por quase dois séculos, de 1732 a 1918. Neste último período, o trono imperial 
russo acabou sendo ocupado por diversos imperadores, muitas vezes de linhas de dinastia 
diferentes. Na tradição imperial russa chama-se de Linhagem uma sequência de descendentes 
dentro de uma dinastia, ou seja, um elemento, seu filho, seu neto, e assim por diante. 
A determinação destas Linhagens são fundamentais quando se deseja determinar o sucessor 
do atual imperador, uma vez que o próximo imperador é o elemento vivo de uma Linhagem que 
esteja mais próxima do atual imperador. É claro que uma árvore genealógica pode ser dividida 
em Linhagens de várias formas diferentes. Dada uma lista dos membros da família imperial e 
uma lista das relações de filiação entre os membros, o programa determina a árvore genealógica 
da família imperial russa permitindo, assim, identificar todas as Linhagens possíveis para o 
trono imperial russo.*/

#include <stdio.h>
#include <stdlib.h>

#define INICIO 0
#define MAX 1000

// TAD Árvore N-Ária

typedef int TChave;

typedef struct SNo
{
    TChave Chave;
    struct SNo *primeiroFilho;
    struct SNo *proxIrmao;
}TNo;

typedef TNo* TArvore;

TArvore CriaNovo_No(TChave Valor)
{
    TArvore NovoNo = (TArvore)malloc(sizeof(TNo));

    NovoNo->Chave = Valor;
    NovoNo->primeiroFilho = NULL;
    NovoNo->proxIrmao = NULL;

    return NovoNo;
}

TArvore TArvore_Inicia(TChave Valor)
{
    return(CriaNovo_No(Valor)); 
}

TArvore BuscaChave( TChave Valor, TArvore Raiz)
{
    if(Raiz == NULL)
        return NULL;

    if(Raiz->Chave == Valor)
        return Raiz;
    
    TArvore p = Raiz->primeiroFilho;

    while (p)
    {
        TArvore resp =BuscaChave(Valor, p);
        if(resp)
            return (resp);
        p = p->proxIrmao;
    }

    return(NULL);
    
}

int TArvore_Insere(TArvore Raiz, TChave Nova_Chave, TChave Chave_Pai)
{
    TArvore Pai = BuscaChave(Chave_Pai, Raiz);

    if(!Pai)
        return 0;

    TArvore Filho = CriaNovo_No(Nova_Chave);

    TArvore p = Pai->primeiroFilho;

    if(!p)
        Pai->primeiroFilho = Filho;
    else
    {
        while(p->proxIrmao)
            p = p->proxIrmao;
        p->proxIrmao = Filho;
    }

    return 1;
}

void Exibir_Arvore(TArvore Raiz)
{
    printf("(%d", Raiz->Chave);

    TArvore p = Raiz->primeiroFilho;

    while(p){
        Exibir_Arvore(p);
        p = p->proxIrmao;
    }

    printf(")");

}

// TAD Árvore N-Ária.

int main()
{
  int num_membros , num_relações, i;
  TArvore Arvore_Genealogica;
  TChave Pai, Filho;

  scanf("%d %d", &num_membros, &num_relações);
  //printf("%d %d", num_membros, num_relações);

  Arvore_Genealogica = TArvore_Inicia(1);

  for(i = 0; i < num_relações; i++)
  {
    scanf("%d", &Pai);
    scanf("%d", &Filho);
    TArvore_Insere(Arvore_Genealogica, Filho, Pai);
    Filho = 0;
    Pai = 0;
  } 

  Exibir_Arvore(Arvore_Genealogica);
  
  return 0;
}
