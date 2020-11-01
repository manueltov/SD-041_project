#include "network_client.h"
#include "client_stub.h"
#include "client_stub-private.h"
#include "client_stub.h"
#include "sdmessage.pb-c.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

/* Esta função deve:
 * - Obter o endereço do servidor (struct sockaddr_in) a base da
 *   informação guardada na estrutura rtree;
 * - Estabelecer a ligação com o servidor;
 * - Guardar toda a informação necessária (e.g., descritor do socket)
 *   na estrutura rtree;
 * - Retornar 0 (OK) ou -1 (erro).
 */
int network_connect(struct rtree_t *rtree){

  int sockfd;

  if( rtree == NULL){
    return -1;
  }

  // Cria socket TCP
  if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("Erro ao criar socket\n");
    return -1;
  }

  struct sockaddr_in *server = rtree->server_addr;

  server->sin_family = AF_INET;
  server->sin_port = htons(rtree->server_addr.sin_port);

  if(inet_pton( AF_INET, rtree->server_addr.sin_addr.s_addr, &server->sin_addr) < 1 ){
    printf("Erro ao converter IP\n");
    return -1;
  }

  //Estabele conexao
  if( connect(sockfd, (struct sockaddr_in *)&rtree->server_addr, sizeof(rtree->server_addr)) < 0 ){
    printf("Erro ao conectar-se ao servidor\n");
    close(sockfd);
    return -1;
  }

  rtree->sockfd = sockfd;
  return 0;
}

/* Esta função deve:
 * - Obter o descritor da ligação (socket) da estrutura rtree_t;
 * - Serializar a mensagem contida em msg;
 * - Enviar a mensagem serializada para o servidor;
 * - Esperar a resposta do servidor;
 * - De-serializar a mensagem de resposta;
 * - Retornar a mensagem de-serializada ou NULL em caso de erro.
 */
struct message_t *network_send_receive(struct rtree_t * rtree,
                                       struct message_t *msg){

}

/* A função network_close() fecha a ligação estabelecida por
 * network_connect().
 */
int network_close(struct rtree_t * rtree){

}
