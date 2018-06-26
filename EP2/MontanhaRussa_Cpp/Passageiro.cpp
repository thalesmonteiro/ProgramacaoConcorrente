/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>

#define MAX_NUM_VOLTAS 6
#define TEST_NUMBER 10

int estagio[11] = {0};
int ultimo[11] = {0};

static int test = 0;
atomic_flag lock1 = ATOMIC_FLAG_INIT;
atomic_flag lockPrint = ATOMIC_FLAG_INIT;

Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
	this->nVoltas = 0;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {	
	for (int j = 1; j <= 10; j++){ //Parque::numPessoas
			estagio[id] = j;
			ultimo[j] = id;
			for (int k = 1; k <= 10; k++){
				if(k == id){
					continue;
				}	
				while (estagio[k] >= estagio[id] && ultimo[j] == id);
				while (carro->carroCheio);
			}
		}

		printf("Passageiro %d entrou no carro \n", id);
		Carro::numPassageiros.fetch_add(1, memory_order_seq_cst);
		//printf ("Passageiro [%d] incrementa numPassageiro: %d\n", this->id, carro->numPassageiros.load(memory_order_seq_cst));
		//
		if(carro->numPassageiros >= carro->CAPACIDADE){
			carro->carroCheio = true;
		}
		estagio[id] = 0;
		
}

void Passageiro::esperaVoltaAcabar() {
	printf("Esperando volta acabar");
	while (!carro->voltaAcabou){
		chrono::milliseconds time(100);
		this_thread::sleep_for(time);
	}
}

void Passageiro::saiDoCarro() {
	while(lockPrint.test_and_set());	
	printf("Passageiro %d saiu do carro\n", id);
	lockPrint.clear();
	Carro::numPassageiros.fetch_sub(1, memory_order_seq_cst);
	//printf ("Passageiro [%d] decrementa numPassageiro: %d\n", this->id, carro->numPassageiros.load(memory_order_seq_cst));

	while(lock1.test_and_set());
	if(Carro::numPassageiros == 0){
		carro->carroCheio = false;
		carro->voltaAcabou = false;
	}
	lock1.clear();
	this->nVoltas++;
	//printf("Passageiro [%d] deu %d voltas ate agora", this->id, this->nVoltas);
	// Protocolo de saida do Algoritmo Justo
}

void Passageiro::passeiaPeloParque() {
	printf("Thread [%d] foi passear no parque\n", this->id);
	// Dorme um tempo aleatorio
	int tempo = (rand() % 15) + 5; // Armazena tempo aleatório de passeio para cada passageiro
	chrono::seconds time(3);
	this_thread::sleep_for(time); // Espera passageiro passear
	//printf("Thread [%d] chegou do passeio no parque (demorou %d segundos)\n", this->id, tempo);
}

bool Passageiro::parqueFechado() {
	return !(carro->getNVoltas() < MAX_NUM_VOLTAS);
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida
		
		passeiaPeloParque(); // secao nao critica
	}

	Parque::numPessoas.fetch_sub(1, memory_order_seq_cst);
	while(lockPrint.test_and_set());
	printf ("Numero de voltas de [%d]: %d\n", this->id, this->nVoltas);
	//printf("parque fechou para a thread [%d]\n", this->id);
	lockPrint.clear();
	// decrementa o numero de pessoas no parque
}