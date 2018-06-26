/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include <chrono>
#include <thread>
#include <atomic>

using namespace std;

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static atomic<int> numPassageiros;
	static atomic<bool> voltaAcabou;
	static atomic_flag lock;
	static bool carroCheio;
	static atomic<int> voltas;

	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

private:
	
};

#endif /* CARRO_H_ */