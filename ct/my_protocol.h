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

struct ctnode * createNode(char *);
void deleteNode(struct ctnode *);

static const struct protocol theProtocol = { &createNode, &deleteNode };

#endif
