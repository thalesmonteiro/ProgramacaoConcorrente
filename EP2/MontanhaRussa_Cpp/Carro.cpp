/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include <atomic>

atomic<bool> Carro::voltaAcabou = ATOMIC_VAR_INIT(false);
const int Carro::CAPACIDADE = 5;
atomic<int> Carro::numPassageiros = ATOMIC_VAR_INIT(0);
bool Carro::carroCheio = false;

atomic_flag lockEspera = ATOMIC_FLAG_INIT;

atomic<int>Carro::voltas = ATOMIC_VAR_INIT(0);
Carro::Carro() {
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	puts("esperando encher\n");
	printf ("numpassageiros: %d\n", Carro::numPassageiros.load(memory_order_relaxed));
	while (Carro::numPassageiros < Carro::CAPACIDADE){
		if(Parque::numPessoas.load(memory_order_relaxed) == false){
			pthread_exit(0);
		}
	}
	printf ("numpassageiros: %d\n", Carro::numPassageiros.load(memory_order_relaxed));
	puts("Dando uma volta");
}

void Carro::daUmaVolta() {
	// Dorme por um tempo fixo
	chrono::milliseconds time(5000);
	this_thread::sleep_for(time); // Espera o carrinho dar a volta na montanha russa por 5 segundos
	this->voltaAcabou = true;
}

void Carro::esperaEsvaziar() {
	printf("Esperando esvaziar\n");
	while (Carro::carroCheio){
		chrono::milliseconds time(100);
		this_thread::sleep_for(time); // Espera 100 ms para verificar se o carro já esvaziou
	}
	//carroCheio = false;
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	int contador = 0;
	while (Parque::numPessoas.load(memory_order_relaxed) > 0) {
		esperaEncher();
		
		daUmaVolta();

		esperaEsvaziar();
		
		this->voltaAcabou = false;
		voltas.fetch_add(1, memory_order_seq_cst);
	}
}