#ifndef _MESSAGE_PRIVATE_H
#define _MESSAGE_PRIVATE_H

#include "sdmessage.pb-c.h"

struct message_t{
  struct _MessageT *message;
};

int write_all(int sock, char *buf, int len);

int read_all(int sock, char *buf, int len);

void destroy_sentMsg(struct message_t *msg);

void destroy_rcvMsg(struct message_t *msg);

#endif
