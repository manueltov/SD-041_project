/*
 * Programa servidor:
 *   Recebe uma string do cliente e envia o tamanho dessa string.
 * Como compilar:
 *   gcc -Wall -g server.c -o server
 * Como executar:
 *   server_exemplo <porto_servidor>
 */

#include "inet.h"

int testInput(int argc){
    if (argc != 2){
	printf("Uso: ./server_exemplo <porto_servidor>\n");
        printf("Exemplo de uso: ./server_exemplo 12345\n");
        return -1;
    } 
    return 0;
}

int main(int argc, char **argv){
    int sockfd, connsockfd;
    struct sockaddr_in server, client;
    char str[MAX_MSG+1];
    int nbytes, count;
    socklen_t size_client;


    // Verifica se foi passado algum argumento
    if (testInput(argc) < 0) return -1;

    // Cria socket TCP
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("Erro ao criar socket");
        return -1;
    }

    // Preenche estrutura server com endereço(s) para associar (bind) à socket 
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1])); // Porta TCP
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Todos os endereços na máquina

    // Faz bind
    if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0){
        perror("Erro ao fazer bind");
        close(sockfd);
        return -1;
    }

    // Esta chamada diz ao SO que esta é uma socket para receber pedidos
    if (listen(sockfd, 0) < 0){
        perror("Erro ao executar listen");
        close(sockfd);
        return -1;
    }

    printf("Servidor à espera de dados\n");

    // accept bloqueia à espera de pedidos de conexão.
    // Quando retorna já foi feito o "three-way handshake" e connsockfd é uma
    // socket pronta a comunicar com o cliente.
    while ((connsockfd = accept(sockfd,(struct sockaddr *) &client, &size_client)) != -1) {

		// Lê string (no máximo MAX_MSG bytes) enviada pelo cliente
		// através da socket
		if((nbytes = read(connsockfd,str,MAX_MSG)) < 0){
			perror("Erro ao receber dados do cliente");
			close(connsockfd);
			continue;
		}
		// Coloca terminador de string
		str[nbytes] = '\0';

		// Conta número de carateres
		count = strlen(str);

		// Converte count para formato de rede
		count = htonl(count);

		// Envia tamanho da string ao cliente através da socket
		if((nbytes = write(connsockfd,&count,sizeof(count))) != sizeof(count)){
			perror("Erro ao enviar resposta ao cliente");
			close(connsockfd);
			continue;
		}

		// Fecha socket referente a esta conexão
		close(connsockfd);
    }
    // Fecha socket
    close(sockfd);
    return 0;
}
