#ifndef _NET_TEST_RUNNER_H
#define _NET_TEST_RUNNER_H

#include <netinet/in.h>

//TODO potentially add server functions that don't take addrs
typedef int(*clientFunction)(int socket, 
                              struct sockaddr *destAddr,
                              socklen_t destLen);

typedef struct netConnection {
  char * name;
  clientFunction function;
  char * dest;
} NetConnection;

int runSocketTests(NetConnection * connections);

#endif
