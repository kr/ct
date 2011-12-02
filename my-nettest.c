#include "ct/ct.h"
#include "ct/my_protocol.h"
#include <stdio.h>

#define NETTESTC "nettestd"
int nettestc(struct ctnode *from, struct ctnode *to) {
  printf("nettestc\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  assert(0);
  return 1;
}

#define NETTESTD "nettestc"
int nettestd(struct ctnode *from, struct ctnode *to) {
  printf("nettestd\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  return 1;
}
