/*
 * Produtor.h
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#ifndef INCLUDE_PRODUTOR_H_
#define INCLUDE_PRODUTOR_H_

#include <vector>
#include <semaphore.h>
#include <thread>
#include "Consumidor.h"


#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

class Consumidor;

class Produtor {
public:
	Produtor();
	virtual ~Produtor();

	int getRear();
	void addConsumidor(Consumidor *c);
    void start(int porta);
	int returnSocket();

private:
	int rear;

    // A estrutura sockaddr_in contem um endereco de internet
	struct sockaddr_in server;
	int sock, n;
    socklen_t fromlen;
	sem_t controle;
	std::vector<Consumidor*> consumidores;
	std::thread *th_produtor;

	void error(const char* msg);
	void run();
};

#endif /* INCLUDE_PRODUTOR_H_ */
