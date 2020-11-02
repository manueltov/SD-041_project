
#include <errno.h>

/*int testInput(int argc){
    if (argc != 4){
        printf("Uso: ./tree_client <hostname>:<porto_servidor>\n");
        printf("Exemplo de uso: ./tree_client 127.0.0.1:12345\n");
        return -1;
    }
    return 0;
}

int main(int argc, char **argv){
    int sockfd;
    struct sockaddr_in server;
    char str[MAX_MSG];
    int count, nbytes;

    // Verifica se foi passado algum argumento
    if (testInput(argc) < 0) return -1;

    // Copia os primeiros bytes da string (no máximo MAX_MSG-1) passada como argumento
    strncpy(str, argv[3], MAX_MSG-1);

    // Garante que a string tem terminação. Se era maior que MAX_MSG será truncada.
    str[MAX_MSG-1] = '\0';

    gets

    rtree_connect(argv[1]);

    // Envia string
    if((nbytes = write(sockfd,str,strlen(str))) != strlen(str)){
        perror("Erro ao enviar dados ao servidor");
        close(sockfd);
        return -1;
    }

    printf("À espera de resposta do servidor ...\n");

    // Recebe tamanho da string
    if((nbytes = read(sockfd,&count,sizeof(count))) != sizeof(count)){
        perror("Erro ao receber dados do servidor");
        close(sockfd);
        return -1;
    };

    printf("O tamanho da string é %d!\n", ntohl(count));

    close(sockfd); // Fecha o socket
    return 0; // Termina*/
