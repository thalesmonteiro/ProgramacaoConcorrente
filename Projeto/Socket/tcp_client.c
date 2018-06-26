#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){

    //Criando socket com protocolo TCP(Sock_Stream)
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Especificando endereço e informações básicas do socket do cliente
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000); // Foi definida a porta 3000 para o serviço
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Momento em que ocorre a conexão com o servidor
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //Checa se ocorreu algum erro na conexão
    if (connection_status < 0){
        printf("Ocorreu algum erro na conexão com o socket!\n\n");
        return 0; //Encerra programa 
    }
        

    //Nesse momento nós recebemos dados do servidor
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //Printa na tela a resposta do servidor após conexão
    printf("Recebemos do servidor a mensagem: %s\n", server_response);

    //Fechando socket
    close(network_socket);
    return 0;
}