#ifndef _MY_PROTOCOL_H
#define _MY_PROTOCOL_H

#include "protocol.h"

#include <arpa/inet.h>
#include <sys/socket.h>

struct ctnode {
  int socket;
  struct sockaddr* addr;
  socklen_t addrLen;
};

struct ctnode * createMyNode(char *);
void deleteMyNode(struct ctnode *);

static const struct protocol theProtocol = { &createMyNode, &deleteMyNode };

#endif
