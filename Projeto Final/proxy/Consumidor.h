/*
 * Consumidor.h
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#ifndef INCLUDE_CONSUMIDOR_H_
#define INCLUDE_CONSUMIDOR_H_

#include <semaphore.h>
#include <thread>
#include <iostream>
#include "Produtor.h"
#include <cstring>
#include <netinet/in.h>


class Produtor;
class Consumidor {
public:
	static const int BUFFER_SIZE = 1024;

	Consumidor(Produtor& p);
	virtual ~Consumidor();

	int getFront();
	sem_t& getEmpty();
	sem_t& getFull();
	//static std::vector<char*> &getBufferLimitado();
	static char buffAuxiliar[BUFFER_SIZE]; // PASSAR PARA O RECVFROM
	
	void start(int porta);
	static int sock1;
	static std::vector<char*> bufferLimitado;
	static std::vector<char*>& getBufferLimitado();
	struct sockaddr_in client;

private:
	int front;
	sem_t full;
	sem_t empty;

	Produtor& produtor;
	std::thread *th_consumidor;

	void run();
};

#endif /* INCLUDE_CONSUMIDOR_H_ */
