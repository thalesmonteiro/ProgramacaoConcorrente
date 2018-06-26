/*
 * Consumidor.cpp
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#include "Consumidor.h"
#include "Produtor.h"
int Consumidor::sock1;

std::vector<char*> Consumidor::bufferLimitado(BUFFER_SIZE); //verificar este tamanho

Consumidor::Consumidor(Produtor& p) : produtor(p) {
	bzero(&client, sizeof(client));
	front = 0;
	th_consumidor = NULL;
	sock1 = p.returnSocket();
}

Consumidor::~Consumidor() {
	// TODO Auto-generated destructor stub
}

int Consumidor::getFront() {
	return front;
}

void Consumidor::getThreadJoin(){
    th_consumidor->join();
}

sem_t& Consumidor::getEmpty() {
	return empty;
}

sem_t& Consumidor::getFull() {
	return full;
}

std::vector<char*>& Consumidor::getBufferLimitado() {
	return bufferLimitado;
}

void Consumidor::start(int porta) {
	//std::cout << "Consumidor ok" << std::endl;
    // Define a familia do endereco como do tipo Internet
    client.sin_family = AF_INET;
	client.sin_port = htons(porta);
    // Seta o endereco para localhost (127.0.0.1)
    client.sin_addr.s_addr = INADDR_ANY;
    // A funcao htons() converte o numero da porta para o padrao Little Endian.

	//std::cout << "numero da porta do consumidor " << htons(client[nClients].sin_port) << std::endl;
    th_consumidor = new std::thread(&Consumidor::run, this);

}

void Consumidor::run() {
	front = produtor.getRear();
	sem_init(&empty, 0, Consumidor::BUFFER_SIZE);
	sem_init(&full, 0, 0);

	int fromlen = sizeof(struct sockaddr_in);

	while (true) {
		sem_wait(&full);

        sendto(sock1, bufferLimitado[front], 1316, 0, (struct sockaddr *) &client, fromlen);
		//std::cout << "to no consumidor" << std::endl;
		front = (front + 1) % 1024;

		sem_post(&empty);
		//sem_post(&produtor.rcontrol());
	}
    Consumidor::getThreadJoin();
	sem_destroy(&empty);
	sem_destroy(&full);


}
