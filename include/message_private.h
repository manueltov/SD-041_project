#ifndef _MESSAGE_PRIVATE_H
#define _MESSAGE_PRIVATE_H

#include "sdmessage.pb-c.h"

/* Define os possíveis opcodes da mensagem */
OP_SIZE         10
OP_DEL          20
OP_GET          30
OP_PUT          40
OP_GETKEYS      50
OP_HEIGHT       60
/* opcode para representar retorno de erro da execução da operação*/
OP_ERROR        99
/* Define códigos para os possíveis conteúdos da mensagem (c_type) */
CT_KEY          10
CT_VALUE        20
CT_ENTRY        30
CT_KEYS         40
CT_RESULT       50
/* Opcode representativo de inexistência de content
* (e.g., getkeys e size */
CT_NONE         60

struct message_t{
  struct _MessageT *message;
};

int write_all(int sock, char *buf, int len);

int read_all(int sock, char *buf, int len);

#endif
