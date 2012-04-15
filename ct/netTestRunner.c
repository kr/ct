#include "netTestRunner.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <syslog.h>
#include "ct.h"
#include <stdio.h>

typedef struct namedNode {
  char * name;
  struct ctnode * node;
} NamedNode;

struct ctnode* getNodeByName(NamedNode *nodeList, int numNodes, char * name);

int runSocketTests(const struct protocol *prot, NetConnection * connections) {

  // Create counters
  int i;
  NetConnection * conCounter;

  //Count number of connections
  int numNodes = 0;
  conCounter = connections;
  while(conCounter->name != NULL) {
    numNodes++;
    conCounter++;
  }

  NamedNode *namedList = calloc(numNodes, sizeof(NamedNode));
  
  // Create sockets and ports for each function
  i = 0; conCounter = connections;
  while(conCounter->name != NULL) {
    namedList[i].name = conCounter->name;
    namedList[i].node = prot->createNode(conCounter->name);
    i++; conCounter++;
  }

  int *pids = calloc(numNodes, sizeof(int));

  // Fork and start each connection
  i = 0; conCounter = connections;
  while(conCounter->name != NULL) {
    pid_t pid = fork();
    assert(pid != -1);
    if(pid!=0) {
      pids[i] = pid;
    } else {
      struct ctnode * fromNode = 
        getNodeByName(namedList, numNodes, conCounter->name);
      assert(fromNode != NULL);
      struct ctnode * toNode = 
        getNodeByName(namedList, numNodes, conCounter->dest);
      assert(toNode != NULL);
      exit(conCounter->function(fromNode, toNode));
    }
    i++; conCounter++;
  }

  // Wait for and join all forked processes
  int status;
  i = 0;
  while(i < numNodes) {
    assert(waitpid(pids[i], &status, 0) == pids[i]);
    if(status != 0) {
      exit(status);
    }
    //TODO return any bad ones and give up note freeing things will result
    // in segfaults for still running processes
    i++;
  }

  // Free all connections
  i = 0;
  while(i < numNodes) {
    prot->deleteNode(namedList[i].node);
    i++;
  }
  free(namedList);
  free(pids);

  return 0;
}

struct ctnode * getNodeByName(NamedNode *namedList, int numNodes, char * name) {
  int i = 0;
  while(i < numNodes) {
    if(strcmp(namedList[i].name, name) == 0) {
      return namedList[i].node;
    }
    i++;
  }
  return NULL;
}
