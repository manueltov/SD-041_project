// SD-041
// João Figueiredo, nº 53524
// Manuel Tovar, nº 49522
// Mariana Bento, nº 53676

#include "data.h"
#include "entry.h"
#include "message_private.h"
#include "sdmessage.pb-c.h"
#include "client_stub_private.h"
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
  rtree->server_addr->sin_family = AF_INET;
  rtree->server_addr->sin_port = htons(atoi(port)); //atoi convert string to integer;

  if(inet_pton( AF_INET, hostname, &rtree->server_addr->sin_addr) < 0 ){
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

  //preenche estrutura msg
  struct message_t *send_msg = (struct message_t *) malloc(sizeof(struct message_t));

  send_msg->message->opcode = MESSAGE_T__OPCODE__OP_PUT;
  send_msg->message->c_type = MESSAGE_T__C_TYPE__CT_ENTRY;
  send_msg->message->key = entry->key;
  send_msg->message->data = entry->value->data;
  send_msg->message->data_size = entry->value->datasize;

  if( send_msg == NULL){
    destroy_sentMsg(send_msg);
    return -1;
  }

  //envia send_msg para o server e recebe resposta
  struct message_t *receive_msg = network_send_receive(rtree, send_msg);
  if( receive_msg == NULL){
    return -1;
  }
  receive_msg->message->opcode = send_msg->message->opcode + 1;

  destroy_sentMsg(send_msg);
  destroy_rcvMsg(receive_msg);
  return 0;

}

/* Função para obter um elemento da árvore.
 * Em caso de erro, devolve NULL.
 */
struct data_t *rtree_get(struct rtree_t *rtree, char *key){

  struct message_t *send_msg, *rcv_msg;

  if( rtree == NULL || key == NULL){
    return NULL;
  }

  send_msg = (struct message_t *) malloc(sizeof(struct message_t));

  send_msg->message->opcode = MESSAGE_T__OPCODE__OP_GET;
  send_msg->message->c_type = MESSAGE_T__C_TYPE__CT_KEY;
  send_msg->message->key = key;

  if( send_msg == NULL){
    destroy_sentMsg(send_msg);
    return NULL;
  }

  //envia send_msg para o server e recebe resposta
  rcv_msg = network_send_receive(rtree, send_msg);

  if( rcv_msg == NULL){
    destroy_rcvMsg(rcv_msg);
    return NULL;
  }

  char * cpy_data = rcv_msg->message->data;

  if( cpy_data != NULL){
    return strdup(cpy_data);
  }else{
    return NULL;
  }

  struct data_t *data = data_create2( rcv_msg->message->data_size, rcv_msg->message->data);

  destroy_sentMsg(send_msg);
  destroy_rcvMsg(rcv_msg);

  return data;
}

/* Função para remover um elemento da árvore. Vai libertar
 * toda a memoria alocada na respetiva operação rtree_put().
 * Devolve: 0 (ok), -1 (key not found ou problemas).
 */
int rtree_del(struct rtree_t *rtree, char *key){

  if( rtree == NULL || key == NULL){
    return -1;
  }

  struct message_t *send_msg, *rcv_msg;

  send_msg = (struct message_t *) malloc(sizeof(struct message_t));

  send_msg->message->opcode = MESSAGE_T__OPCODE__OP_DEL;
  send_msg->message->c_type = MESSAGE_T__C_TYPE__CT_KEY;
  send_msg->message->key = key;

  if( send_msg == NULL){
    destroy_sentMsg(send_msg);
    return -1;
  }

  //envia send_msg para o server e recebe resposta
  rcv_msg = network_send_receive(rtree, send_msg);

  if( rcv_msg == NULL){
    destroy_rcvMsg(rcv_msg);
    return -1;
  }

  if( rcv_msg->message->opcode == MESSAGE_T__OPCODE__OP_ERROR ){
    destroy_sentMsg(send_msg);
    destroy_rcvMsg(rcv_msg);
    return -1;
  }

  destroy_sentMsg(send_msg);
  destroy_rcvMsg(rcv_msg);
  return 0;

}

/* Devolve o número de elementos contidos na árvore.
 */
int rtree_size(struct rtree_t *rtree){

  if( rtree == NULL) return 0;

  struct message_t *send_msg, *rcv_msg;

  send_msg = (struct message_t *) malloc(sizeof(struct message_t));

  send_msg->message->opcode = MESSAGE_T__OPCODE__OP_SIZE;
  send_msg->message->c_type = MESSAGE_T__C_TYPE__CT_NONE;

  if( send_msg == NULL){
    destroy_sentMsg(send_msg);
    return 0;
  }

  rcv_msg = network_send_receive( rtree, send_msg);

  if( rcv_msg == NULL){
    destroy_rcvMsg(rcv_msg);
    return 0;
  }

  int size = rcv_msg->message->data_size;

  destroy_sentMsg(send_msg);
  destroy_rcvMsg(rcv_msg);

  return size;
}

/* Função que devolve a altura da árvore.
 */
int rtree_height(struct rtree_t *rtree){

}

/* Devolve um array de char* com a cópia de todas as keys da árvore,
 * colocando um último elemento a NULL.
 */
char **rtree_get_keys(struct rtree_t *rtree){

  if( rtree == NULL) return NULL;

  struct message_t *send_msg, *rcv_msg;

  send_msg = (struct message_t *) malloc(sizeof(struct message_t));

  send_msg->message->opcode = MESSAGE_T__OPCODE__OP_GETKEYS;
  send_msg->message->c_type = MESSAGE_T__C_TYPE__CT_NONE;

  if(send_msg == NULL){
    destroy_sentMsg(send_msg);
    return NULL;
  }

  rcv_msg = network_send_receive( rtree, send_msg);

  if( rcv_msg == NULL){
    destroy_rcvMsg(rcv_msg);
    return NULL;
  }

  destroy_sentMsg(send_msg);

  int num_keys = rcv_msg->message->n_keys;
  char **keys = (char **) malloc(sizeof(char *) * (num_keys+1)); //save num_keys +1 blocks

  if( keys == NULL ) return NULL;

  for( int i = 0; i < num_keys; i++){ //cópia de todas as keys
    keys[i] = rcv_msg->message->keys[i];
  }
  keys[num_keys] = NULL;

  destroy_rcvMsg(rcv_msg);
  return keys;
}

/* Liberta a memória alocada por rtree_get_keys().
 */
void rtree_free_keys(char **keys){

  if( keys != NULL){
    for( int i = 0; keys[i] != NULL; i++){
      free(keys[i]);
    }
    free(keys);
  }
}
