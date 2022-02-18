//Luiz Fernando -- Matricula: 159325
//Tarefa 002
/*Um programa que simula a execução de uma calculadora pós-fixada que oferece 
as 4 (quatro) operações básicas, a saber: + (soma), - (subtração), * (multiplicação) 
e / (divisão). */
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
#define MAX 51
 
//TAD Pilha :
 
typedef int TApontador; //dando um apelido para o int (TApontador)
 
typedef float TValor; //dando um apelido para o double (TValor)
 
typedef struct {
    TValor Valor;
}TItem;
 
typedef struct {
    TItem Item[MAX];
    TApontador Topo;
}TPilha;
 
//Procedimentos e Funções
 
void Inicializa_TPilha(TPilha *pCalculadora_Pilha) //inicializando a pilha
{
    pCalculadora_Pilha->Topo = 0;
};
 
int TPilha_E_Vazia(TPilha *pCalculadora_Pilha) //verificando se a pilha é vazia
{
    if (pCalculadora_Pilha->Topo == 0)
        return 1;
    else
        return 0;
};
 
int Empilha_TPilha(TPilha *pCalculadora_Pilha, TItem x) //função que insere novo item na pilha
{
    if(pCalculadora_Pilha->Topo == MAX) //verificando se a pilha está cheia
        return 0;
 
    pCalculadora_Pilha->Topo++;
    pCalculadora_Pilha->Item[pCalculadora_Pilha->Topo] = x;
    return 1;
};
 
int Desempilha_TPilha(TPilha *pCalculadora_Pilha, TItem *pX) //função que tira um item da pilha
{
    if(TPilha_E_Vazia(pCalculadora_Pilha) == 1) //verificando se a pilha está vazia
        return 0;
 
    *pX = pCalculadora_Pilha->Item[pCalculadora_Pilha->Topo];
    pCalculadora_Pilha->Topo--;
    return 1;
};
 
int TPilha_Tamanho(TPilha *pCalculadora_Pilha) //função que retorna o tamanho da pilha
{
    return(pCalculadora_Pilha->Topo);
};
 
//TAD Pilha.
 
int main()
{
    TPilha Calculadora_Pilha;
    TItem OperandosUm, OperandosDois, ResultadoCalculo;
 
    char ExpressaoAritmetica[MAX];
    int i;
 
    scanf("%s", &ExpressaoAritmetica);
 
    Inicializa_TPilha(&Calculadora_Pilha);
 
    for(i = 0; i < strlen(ExpressaoAritmetica); i++) //percorrendo a expressão aritmética
    {
        switch (ExpressaoAritmetica[i])
        {
        case '+':
            {
                if(Desempilha_TPilha(&Calculadora_Pilha, &OperandosUm.Valor) != 0 &&
                    Desempilha_TPilha(&Calculadora_Pilha, &OperandosDois.Valor) != 0) //desempilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse vazia retornaria 0 e não faria nada
                {
                    ResultadoCalculo.Valor = OperandosDois.Valor + OperandosUm.Valor;
 
                    if(Empilha_TPilha(&Calculadora_Pilha, ResultadoCalculo) == 0) //empilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse cheia retornaria 0 e não faria nada, apenas apresentaria um erro na tela
                        return("Não foi possível inserir");
                }
            }
            break;
        case '-':
            {
                if(Desempilha_TPilha(&Calculadora_Pilha, &OperandosUm.Valor) != 0  &&
                    Desempilha_TPilha(&Calculadora_Pilha, &OperandosDois.Valor) != 0) //desempilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse vazia retornaria 0 e não faria nada
                {
                    ResultadoCalculo.Valor = OperandosDois.Valor - OperandosUm.Valor;
 
                    if(Empilha_TPilha(&Calculadora_Pilha, ResultadoCalculo) == 0) //empilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse cheia retornaria 0 e não faria nada, apenas apresentaria um erro na tela
                        return("Não foi possível inserir");
                }
            }
            break;
        case '*':
            {
                if(Desempilha_TPilha(&Calculadora_Pilha, &OperandosUm.Valor) != 0 &&
                    Desempilha_TPilha(&Calculadora_Pilha, &OperandosDois.Valor) != 0) //desempilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse vazia retornaria 0 e não faria nada
                {
                    ResultadoCalculo.Valor = OperandosDois.Valor * OperandosUm.Valor;
 
                    if(Empilha_TPilha(&Calculadora_Pilha, ResultadoCalculo) == 0) //empilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse cheia retornaria 0 e não faria nada, apenas apresentaria um erro na tela
                        return("Não foi possível inserir");
                }
            }
            break;
        case '/':
            {
                if(Desempilha_TPilha(&Calculadora_Pilha, &OperandosUm.Valor) != 0 &&
                    Desempilha_TPilha(&Calculadora_Pilha, &OperandosDois.Valor) != 0) //desempilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse vazia retornaria 0 e não faria nada
                {
                    ResultadoCalculo.Valor = OperandosDois.Valor / OperandosUm.Valor;
 
                    if(Empilha_TPilha(&Calculadora_Pilha, ResultadoCalculo) == 0) //empilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse cheia retornaria 0 e não faria nada, apenas apresentaria um erro na tela
                        return("Não foi possível inserir");
                }
            }
            break;
        
        default: //se não for nenhum caracter de operações (+(soma),- (subtração),*(multiplicação) e / (divisão)), será um operando, então irá ler os valores de cada um dos operandos da expressão aritmética
        scanf("%f", &ResultadoCalculo.Valor);
            if(Empilha_TPilha(&Calculadora_Pilha, ResultadoCalculo) == 0) //empilhando e verificando se deu tudo certo, por exemplo se a pilha estivesse cheia retornaria 0 e não faria nada, apenas apresentaria um erro na tela
                return("Não foi possível inserir");
            break;
        }
    }
 
    printf("%f", ResultadoCalculo.Valor);
 
    return 0;
}