#include "my_protocol.h"

#include <stdlib.h>
#include "ct.h"

struct ctnode * createMyNode(__attribute__((unused)) char *name) {
  // Create socket
  int mySocket = socket(AF_INET, SOCK_DGRAM, 0);
  assert(mySocket != -1);

  // Create sockaddr
  struct sockaddr_in * channel = calloc(1, sizeof(struct sockaddr_in));
  channel->sin_family = AF_INET;
  channel->sin_addr.s_addr = INADDR_ANY;

  // Bind socket to sockaddr
  assert(bind(mySocket, (struct sockaddr *) channel, sizeof(*channel))==0);

  //Create NodeInfo
  struct ctnode * node = calloc(1, sizeof(struct ctnode));
  node->socket = mySocket;
  node->addr = (struct sockaddr *) channel;
  node->addrLen = sizeof(*channel);

  return node;
}

void deleteMyNode(struct ctnode *node) {
  free(node->addr);
  free(node);
}
