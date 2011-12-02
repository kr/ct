#ifndef _NET_TEST_RUNNER_H
#define _NET_TEST_RUNNER_H

#include <netinet/in.h>
#include "protocol.h"

// The function type to be specified in nettest files.
// Should run some code at "from", sending to or receiving from "to".
// Returns 0 if no errors were encountered.
typedef int(*nettestFunction)(struct ctnode *from, struct ctnode *to);

// Defines a node name which runs function and is connected to the node dest.
typedef struct netConnection {
  char * name;
  nettestFunction function;
  char * dest;
} NetConnection;


// given a protocol's createNode and deleteNode functions
// creates each node by calling createNode(connection->name)
// for each connection in connections
//   forks and calls connection->function(connection->name, connection->dest)
// deletes each node by calling deleteNode(connection->name)
int runSocketTests(const struct protocol *prot, NetConnection * connections);

#endif
