/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

//Bibliotecas responsáveis pelos números aleatórios
#include <cstdlib>
#include <ctime>

using namespace std;

class Carro;
class Parque;

class Passageiro {
public:
	Passageiro(int id, Carro *c);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();

	void run();
private:
	int tempo;
	int id;
	int nVoltas;
	Carro *carro;
	Parque *parque;
};

#endif /* PASSAGEIRO_H_ */