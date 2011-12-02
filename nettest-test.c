#include "ct/netTestRunner.h"
#include <stdlib.h>
#include "ct/ct.h"
#include "ct/udp_protocol.h"

#include <stdio.h>

#define NETTESTA "nettesta"
int nettesta(struct ctnode *from, struct ctnode *to);

static struct netConnection connections[] = {
  {"nettesta", nettesta, NETTESTA},
  {NULL, NULL, NULL}
};

void cttest_nettesta() {
  printf("about to run socket tests\n");
  runSocketTests(&theProtocol, connections);
  assert(0);
}
