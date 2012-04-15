#include "ct/ct.h"
#include "ct/udp_protocol.h"
#include <stdio.h>

#define NETTESTSERVER NULL
int nettestserver(struct ctnode *from, struct ctnode *to) {
  printf("server\n");
  // receive incoming messages using the from node
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  assert(0);
  return 1;
}

#define NETTESTCLIENT1 "nettestserver"
int nettestclient1(struct ctnode *from, struct ctnode *to) {
  // communicate with the server in the to node
  printf("client1\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  return 1;
}

#define NETTESTCLIENT2 "nettestserver"
int nettestclient2(struct ctnode *from, struct ctnode *to) {
  // communicate with the server in the to node
  printf("client2\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  return 1;
}
