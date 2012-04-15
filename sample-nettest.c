#include "ct/ct.h"
#include "ct/udp_protocol.h"

#include <stdio.h>

// This test creates a bidirectional connection between node running the
// two function below

// #define creates a connection from nettesta to nettestb.
// The uppercase equivilent of the function should be defined as a string
//  matching the function which will run at the node to connect to.
// This function will be called in the test with
//  from=nettesta node and to=nettestb node
#define NETTESTA "nettestb"
int nettesta(struct ctnode *from, struct ctnode *to) {
  printf("nettesta\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  assert(0);
  return 1;
}

#define NETTESTB "nettesta"
int nettestb(struct ctnode *from, struct ctnode *to) {
  printf("nettestb\n");
  printf("from-socket: %d\n", from->socket);
  printf("to-socket: %d\n", to->socket);
  return 1;
}
