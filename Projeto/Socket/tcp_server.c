#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){

    char server_message[256] = "Parabéns, você conectou no servidor!";

    //Criando socket do servidor com protocolo TCP(Sock_Stream)
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Especificando endereço e informações básicas do socket do servidor
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000); // Foi definida a porta 3000 para o serviço
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Bind do socket para associar o IP e a Porta
    bind (server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    listen(server_socket, 5); //O valor 5 é apenas uma convenção

    int client_socket;
    //Os parâmetros estão NULL porque não quero saber o endereço do client, pois só está sendo enviada uma mensagem para ele
    //Procurar saber como faz o "FromAlgo" p/ pegar o endereço do client
    client_socket = accept(server_socket, NULL, NULL);

    //Enviando mensagem para o cliente
    send(client_socket, server_message, sizeof(server_message), 0);

    //Fechando socket
    close(server_socket);
    return 0;
}