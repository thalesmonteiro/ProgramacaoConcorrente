/*
 * Produtor.cpp
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#include "Produtor.h"
#include "Consumidor.h"



Produtor::Produtor() {
	rear = 0;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	th_produtor = NULL;
    
	for(int i = 0; i <= Consumidor::BUFFER_SIZE; i++){
		Consumidor::getBufferLimitado()[i] = new char[1316];
	}
}

Produtor::~Produtor() {
	// TODO Auto-generated destructor stub
}

void Produtor::error(const char *msg) {
    perror(msg);
    exit(0);
}

int Produtor::getRear() {
	return rear;
}

void getThread(){
	//TALVEZ UM JOIN :)	
}

int Produtor::returnSocket(){
	return sock;
}

void Produtor::addConsumidor(Consumidor *c) {
	consumidores.push_back(c);
}

void Produtor::start() {
	fromlen = sizeof(server);
	// Zera a estrutura "server"
    bzero(&server, fromlen);
    // Define a familia do endereco como do tipo Internet
	server.sin_family = AF_INET;
	// Seta o endereco para localhost (127.0.0.1)
	server.sin_port = htons(1234);
	server.sin_addr.s_addr = INADDR_ANY;
	//server.sin_addr.s_addr = inet_addr("127.0.0.1"); // COLOCANDO O IP COMO O LOCAL HOST    
	// A funcao htons() converte o numero da porta para o padrao Little Endian.
    
	
	bind(sock, (struct sockaddr *) &server, sizeof(server));

    th_produtor = new std::thread(&Produtor::run, this);
}

void Produtor::run() {
	
	while (true) {
		//sem_wait(&controle);
		for (int i = 0; i < consumidores.size(); i++)
			sem_wait(&consumidores[i]->getEmpty()); // H� UM DECREMENTO

			//std::cout << "to no while do produtor . debug" << std::endl;

		// A funcao recvfrom() bloqueia o programa ate que um pacote seja lido.
        // Quando isso acontece, o pacote e' armazenado em um buffer passado por
        // parametro. Parametros: socket, buffer, tamanho do buffer, flags,
        // endereco da maquina que enviou o pacote, tamanho da estrutura do endereco.
        // Retorna o numero de bytes recebidos.
        n = recvfrom(sock, Consumidor::bufferLimitado[rear], 1316, 0, (struct sockaddr *) &server, &fromlen);

        rear = (rear + 1) % 1024;

        if (n < 0) error("recvfrom");

		//std::cout << "ja dei o recvfrom do produtor" << consumidores.size() << std::endl;

		for (int i = 0; i < consumidores.size(); i++)
			sem_post(&consumidores[i]->getFull()); // H� UM INCREMENTO
	}
}

