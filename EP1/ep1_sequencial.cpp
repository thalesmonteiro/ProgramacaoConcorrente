#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

//Bibliotecas responsáveis pelos números aleatórios
#include <cstdlib>
#include <ctime>

using namespace std;

#define TAMANHO_MATRIZ 200 //Qtde. de linhas e colunas da matriz

static int randomico(){ // Retorna número aleatório entre 1 e 10
	return (rand() % 10) + 1;
}

int matriz_A[TAMANHO_MATRIZ][TAMANHO_MATRIZ],
	matriz_B[TAMANHO_MATRIZ][TAMANHO_MATRIZ],
	matriz_resultante[TAMANHO_MATRIZ][TAMANHO_MATRIZ];

int main()
{
	int linha, coluna;
	srand(time(NULL));

	for (linha = 0; linha < TAMANHO_MATRIZ; linha++){ // Preenche elementos das matrizes com valores entre 1 e 10
		for (coluna = 0; coluna < TAMANHO_MATRIZ; coluna++){
			matriz_A[linha][coluna] = randomico();
			matriz_B[linha][coluna] = randomico();
		}
	}

	for (linha = 0; linha < TAMANHO_MATRIZ; linha++){ // Multiplica matriz_A e matriz_B, armazenando resultado na matriz_resultante
		for(coluna = 0; coluna < TAMANHO_MATRIZ; coluna++){
			for(int k = 0; k < TAMANHO_MATRIZ; k++){
				matriz_resultante[linha][coluna] = matriz_resultante[linha][coluna] + (matriz_A[linha][k] * matriz_B[k][coluna]);
			}
		}
	}

	return 0;
}