#include "ct/ct.h"
#include "ct/udp_protocol.h"
#include <stdio.h>

#define NETTESTA "nettesta"
int nettesta(struct ctnode *from, struct ctnode *to) {
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  assert(0);
  return 1;
}
