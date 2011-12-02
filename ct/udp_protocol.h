#ifndef _UDP_PROTOCOL_H
#define _UDP_PROTOCOL_H

#include "protocol.h"

#include <arpa/inet.h>
#include <sys/socket.h>

struct ctnode {
  int socket;
  struct sockaddr* addr;
  socklen_t addrLen;
};

struct ctnode * createUdpNode(char *);
void deleteUdpNode(struct ctnode *);

static const struct protocol theProtocol = { &createUdpNode, &deleteUdpNode };

#endif
