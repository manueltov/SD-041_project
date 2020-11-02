// SD-041
// João Figueiredo, nº 53524
// Manuel Tovar, nº 49522
// Mariana Bento, nº 53676

#ifndef _CLIENT_STUB_PRIVATE_H
#define _CLIENT_STUB_PRIVATE_H

#include "data.h"
#include "entry.h"
#include <netinet/in.h>

struct rtree_t{
  struct sockaddr_in *server_addr;
  int sockfd;
};

#endif
