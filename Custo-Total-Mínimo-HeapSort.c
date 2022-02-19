// Luiz Fernando -- Matricula: 159325
// Tarefa 010
/* Uum programa que soma um conjunto de números. Onde, a operação de adição requer um custo, 
que é igual a soma dos dois números sendo adicionados. Assim, para somar 1 e 10, você precisa 
de um custo igual a 11. Se você quiser somar 1, 2 e 3, há diversas possibilidades que você pode 
considerar. Dado um conjunto de números, a sua tarefa, portanto, é determinar como esses números 
podem ser somados de modo que o custo total seja mínimo.
Imprime uma linha contendo um número inteiro que indica o custo total mínimo para somar o conjunto de números.*/
 
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1000
 
typedef int* TVetor;
 
//Procedimento que inicializa o vetor
void Inicializa_Vetor(TVetor v, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
        v[i] = 0;
}
 
void CriaHeap(TVetor Vetor, int i, int final)
{
    int aux = Vetor[i]; //pegando o pai
 
    int filho = (i * 2) +1; //pegando o primeiro filho
 
    while(filho <= final) //se esta dentro do vetor ainda
    {
        if(filho < final){
            if(Vetor[filho] < Vetor[filho + 1]) //vendo qual dos filhos é o maior
                filho = filho + 1;
        }
 
        if(aux < Vetor[filho]){ //verificando se o filho é maior que o pai
            Vetor[i] = Vetor[filho]; // se sim, o filho se torna o pai
            i = filho;
            filho = (2 * i) +1; //calcula o teu filho
        }
        else{
            filho = final + 1;
        }
    }
    Vetor[i] = aux; // o antigo pai ocupa o lugar do ultimo filho analisado
}
 
void HeapSort(TVetor Vetor, int n)
{
    int i, aux;
 
    for(i = (n - 1)/2; i >= 0; i--){ //percorrendo do meio para a esquerda
        CriaHeap(Vetor, i, n-1); //criando o heap com os dados
    }
 
    for (i = n - 1; i >= 1; i--){
        aux = Vetor[0];
        Vetor[0] = Vetor[i];
        Vetor[i] = aux;  // pegando o maior elemento da heap e o colocando na sua devida posição, ordenando o vetor
        CriaHeap(Vetor, 0, i - 1); //reconstruindo o heap
    }
}
 
int SomaVetor(TVetor soma, int n)
{
    int total = 0;
    int i;
    for(i = 0; i < n; i++)
    {
        //printf("%d %d\n", soma[i], soma[i]);
        total = total + soma[i];
        //printf("%d \n", total);
    }
    return total;
}
 
int SomaTudo(TVetor Vetor, int n)
{
    int somaTudo, i;
    int j = 0;
 
    TVetor soma;
    
    somaTudo = Vetor[0] + Vetor[1]; //somando os dois primeiros elementos do vetor
 
    soma = (TVetor)malloc(n * sizeof(int));
 
    Inicializa_Vetor(soma, n); //inicializando o vetor
 
    soma[j] = somaTudo; //colocando a primeira soma em um vetor
    j++;
 
    for(i = 2; i < n; i++)
    {
        somaTudo = somaTudo + Vetor[i];
        //printf("%d %d\n", somaTudo , Vetor[i]);
        soma[j] = somaTudo; //adicionando as somas em um vetor
        j++;
    }
 
    somaTudo = SomaVetor(soma, j); //somando os valores do vetor soma
 
    free(soma);
 
    return somaTudo;
}
 
int main()
{
    int num, custo, i;
    TVetor sequencia;
 
    scanf("%d", &num);
 
    sequencia = (TVetor)malloc(num * sizeof(int));
 
    Inicializa_Vetor(sequencia, num); //inicializando o vetor
 
    if(num >= 2 && num <= 1000)
    {
        for(i = 0; i < num; i++)
            scanf("%d", &sequencia[i]);
 
        HeapSort(sequencia, num); //ordenando o vetor
 
        custo = SomaTudo(sequencia, num);
 
        printf("%d", custo);
    }
 
    free(sequencia);
 
    return 0;
}