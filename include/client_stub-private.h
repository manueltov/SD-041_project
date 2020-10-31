#ifndef _CLIENT_STUB_H
#define _CLIENT_STUB_H

#include "data.h"
#include "entry.h"
#include <netinet/in.h>

struct rtree_t{
  struct sockaddr_in server_addr;
  int sockfd;
  //unsigned short port;
  //char *hostname;
};

#endif
