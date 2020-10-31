#include "message_private.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

/*A função write não nos garante que consiga escrever a totalidade de bytes
que estamos a pedir. Portanto, criamos a write_all para garantir isso.
*buf= apontador para um buffer onde estão os bytes que queremos enviar
len= nº de bytes que queremos enviar
*/
int write_all(int sock, char *buf, int len){
  int bufsize = len;
  while( len > 0 ){ //quando len = 0, já enviou todos os bytes
    int res = write(sock, buf, len); //number of bytes written
    if( res < 0){
      if( errno==EINTR ) continue; //se a chamada for interrompida, volta a fazer a chamada
      perror("Write failed:");
      return res;
    }
    buf += res;//incrementar a posição do *buf para o nº de bytes que efetiva/ foram escritos
    len -= res;//decrementar a len(nº de bytes que ainda estão por enviar) os bytes que já foram enviados

  }
  return bufsize;
}

//Função que recebe strings
int read_all(int sock, char *buf, int len){
  int bufsize = len;
  while( len > 0 ){
    int res = read(sock, buf, len);//number of bytes read
    if( res == 0)
      return 0;
    if( res < 0){
      if( errno==EINTR ) continue; //se a chamada for interrompida, volta a fazer a chamada
      perror("Read failed:");
      return res;
    }
    buf += res;
    len -= res;
  }
  return bufsize;
}
