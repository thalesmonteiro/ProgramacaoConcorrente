#include <iostream>
#include <thread>
#include <vector>
using namespace std;

//Bibliotecas responsáveis pelos números aleatórios
#include <cstdlib>
#include <ctime>

#define NUM_THREADS 200 // Define numero de threads desejáveis para o cálculo das matrizes
#define TAMANHO_MATRIZ 200 //Qtde. de linhas e colunas p/ criação de uma matriz quadrada

static int randomico(){ // Retorna número aleatório entre 1 e 10
	return (rand() % 10) + 1;
}

int linha, coluna;

int matriz_A[TAMANHO_MATRIZ][TAMANHO_MATRIZ],
	matriz_B[TAMANHO_MATRIZ][TAMANHO_MATRIZ],
	matriz_resultante[TAMANHO_MATRIZ][TAMANHO_MATRIZ];

static void multiplica_matriz(int comeco, int lim){ //'comeco' define inicio da parte da thread, 'lim' indica o final da parte da thread
	for (linha = 0; linha < TAMANHO_MATRIZ; linha++){ //MULTIPLICA MATRIZES
		for(coluna = comeco; coluna < lim; coluna++){
			for(int k = 0; k < TAMANHO_MATRIZ; k++){
				matriz_resultante[linha][coluna] += (matriz_A[linha][k] * matriz_B[k][coluna]);
			}
		}
	}
}

int main()
{	
	vector<thread> tMatriz;
	srand(time(NULL));

	for (linha = 0; linha < TAMANHO_MATRIZ; linha++){ // Atribui valores entre 1 e 10 para cada espaço das matrizes
		for (coluna = 0; coluna < TAMANHO_MATRIZ; coluna++){
			matriz_A[linha][coluna] = randomico();
			matriz_B[linha][coluna] = randomico();
		}
	}

	int inicio = 0, // Ponto inicial da divisão das matrizes p/ cada thread
	   	limite = TAMANHO_MATRIZ/NUM_THREADS; // Ponto final da divisão das matrizes p/ cada thread

	for (int i = 0; i < NUM_THREADS; i++) {
		tMatriz.push_back(thread(multiplica_matriz, inicio, limite));
		inicio += TAMANHO_MATRIZ/NUM_THREADS; // Desloca ponto inicial para a proxima thread receber outra parte da matriz
		limite += TAMANHO_MATRIZ/NUM_THREADS; // Desloca ponto final para a proxima thread receber outra parte da matriz
	}
	for (int i = 0; i < NUM_THREADS; i++){
		tMatriz[i].join();
	}
	return 0;
}