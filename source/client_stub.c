#include "data.h"
#include "entry.h"
#include "message_private.h"
#include "sdmessage.pb-c.h"
#include "client_stub-private.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* Função para estabelecer uma associação entre o cliente e o servidor,
 * em que address_port é uma string no formato <hostname>:<port>.
 * Retorna NULL em caso de erro.
 */
struct rtree_t *rtree_connect(const char *address_port){
  if (address_port == NULL)
    return NULL;

  struct rtree_t *rtree = (struct rtree_t *)malloc(sizeof(struct rtree_t));
  char *addr_cpy= strdup(address_port);

  if( addr_cpy == NULL){
    return NULL;
  }

  if(rtree == NULL){
    free(addr_cpy);
    return NULL;
  }

  //address_port é uma string no formato <hostname>:<port>
  char *hostname = strtok(addr_cpy, ":"); //hostname
  char *port = strtok(NULL, "\0"); //port
  //int port = atoi(token);//converts string to integer

  //cria socket TCP
  if( (rtree->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
    perror("Erro ao criar socket\n");
    free(rtree);
    free(addr_cpy);
    return NULL;
  }

  //preenche a estrutura rtree para estabelecer conexao
  rtree->server_addr.sin_family = AF_INET;
  rtree->server_addr.sin_port = htons(atoi(port)); //atoi convert string to integer;

  if(inet_pton( AF_INET, hostname, &rtree->server_addr.sin_addr) == 0 ){
    printf("Erro ao converter IP\n"); //hostname=IP address
    free(addr_cpy);
    close(rtree->sockfd);
    free(rtree);
    return NULL;
  }

  //if valid hostname, estabelecer conexao entre client e server
  if( connect(rtree->sockfd, (struct sockaddr *)&rtree->server_addr, sizeof(rtree->server_addr)) < 0 ){
    printf("Erro ao conectar-se ao servidor\n");
    free(addr_cpy);
    close(rtree->sockfd);
    free(rtree);
    return NULL;
  }
  //free(addr_cpy);
  return rtree;
}

/* Termina a associação entre o cliente e o servidor, fechando a
 * ligação com o servidor e libertando toda a memória local.
 * Retorna 0 se tudo correr bem e -1 em caso de erro.
 */
int rtree_disconnect(struct rtree_t *rtree){

  if(rtree == NULL || close(rtree->sockfd) < 0){
    return -1;
  }

  free(rtree);
  return 0;
}

/* Função para adicionar um elemento na árvore.
 * Se a key já existe, vai substituir essa entrada pelos novos dados.
 * Devolve 0 (ok, em adição/substituição) ou -1 (problemas).
 */
int rtree_put(struct rtree_t *rtree, struct entry_t *entry){

  if(rtree == NULL || entry == NULL){
    return -1;
  }

  //preenche estrutura data
  struct message_t *msg = (struct message_t *) malloc(sizeof(struct message_t));

  msg->message->opcode = MESSAGE_T__OPCODE__OP_PUT;
  msg->message->c_type = MESSAGE_T__C_TYPE__CT_ENTRY;
  msg->message->key = entry->key;
  msg->message->data = entry->value;
  msg->message->data_size = entry->value->data->datasize;

  if( msg == NULL){
    return -1;
  }
}

/* Função para obter um elemento da árvore.
 * Em caso de erro, devolve NULL.
 */
struct data_t *rtree_get(struct rtree_t *rtree, char *key){

}

/* Função para remover um elemento da árvore. Vai libertar
 * toda a memoria alocada na respetiva operação rtree_put().
 * Devolve: 0 (ok), -1 (key not found ou problemas).
 */
int rtree_del(struct rtree_t *rtree, char *key){

}

/* Devolve o número de elementos contidos na árvore.
 */
int rtree_size(struct rtree_t *rtree){

}

/* Função que devolve a altura da árvore.
 */
int rtree_height(struct rtree_t *rtree){

}

/* Devolve um array de char* com a cópia de todas as keys da árvore,
 * colocando um último elemento a NULL.
 */
char **rtree_get_keys(struct rtree_t *rtree){

}

/* Liberta a memória alocada por rtree_get_keys().
 */
void rtree_free_keys(char **keys){

}
