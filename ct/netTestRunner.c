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
#include <assert.h>

typedef struct nodeInfo {
  char * name;
  int socket;
  struct sockaddr* addr;
  socklen_t addrLen;
} NodeInfo;

NodeInfo * createNode(NetConnection * connection);

NodeInfo * getNodeInfoByName(NodeInfo **nodeList, int numNodes, char * name);

int runSocketTests(NetConnection * connections) {

  // Create counters
  int i;
  NetConnection * conCounter;

  //Count number of connections
  int numNodes = 0;
  conCounter = connections;
  while(conCounter != NULL) {
    numNodes++;
    conCounter++;
  }

  NodeInfo **nodeList = calloc(numNodes, sizeof(NodeInfo*));
  
  // Create sockets and ports for each function
  i = 0; conCounter = connections;
  while(conCounter != NULL) {
    nodeList[i] = createNode(conCounter);
    i++; conCounter++;
  }

  int *pids = calloc(numNodes, sizeof(int));

  // Fork and start each connection
  i = 0; conCounter = connections;
  while(conCounter != NULL) {
    pid_t pid = fork();
    assert(pid != -1);
    if(pid!=0) {
      pids[i] = pid;
    } else {
      NodeInfo * myInfo = 
        getNodeInfoByName(nodeList, numNodes, conCounter->name);
      assert(myInfo != NULL);
      NodeInfo * connectedInfo = 
        getNodeInfoByName(nodeList, numNodes, conCounter->dest);
      assert(connectedInfo != NULL);
      return conCounter->function(myInfo->socket, 
          connectedInfo->addr, connectedInfo->addrLen);
    }
    i++; conCounter++;
  }

  // Wait for and join all forked processes
  int status;
  i = 0;
  while(i < numNodes) {
    assert(waitpid(pids[i], &status, 0) == pids[i]);
    //TODO return any bad ones and give up note freeing things will result
    // in segfaults for still running processes
    i++;
  }

  // Free all connections
  i = 0;
  while(i < numNodes) {
    free(nodeList[i]->addr);
    free(nodeList[i]);
    i++;
  }
  free(nodeList);
  free(pids);

  return 0;
}

NodeInfo * createNode(NetConnection * connection) {
  // Create socket
  int mySocket = socket(AF_INET, SOCK_DGRAM, 0);
  assert(mySocket != -1);

  // Set up blocking on socket
  struct timeval time;
  time.tv_sec = 1;
  time.tv_usec = 0;
  socklen_t len = sizeof(time);
  setsockopt(mySocket, SOL_SOCKET, SO_RCVTIMEO, &time, len);

  // Create sockaddr
  struct sockaddr_in * channel = calloc(1, sizeof(struct sockaddr_in));
  channel->sin_family = AF_INET;
  channel->sin_addr.s_addr = INADDR_ANY;
  
  // Bind socket to sockaddr
  assert(bind(mySocket, (struct sockaddr *) channel, sizeof(*channel))==0);

  //Create NodeInfo
  NodeInfo * node = calloc(1, sizeof(NodeInfo));
  node->name = connection->name;
  node->socket = mySocket;
  node->addr = (struct sockaddr *) channel;
  node->addrLen = sizeof(*channel);

  return node;
}

NodeInfo * getNodeInfoByName(NodeInfo **nodeList, int numNodes, char * name) {
  int i = 0;
  while(i < numNodes) {
    if(strcmp(nodeList[i]->name, name) == 0) {
      return nodeList[i];
    }
    i++;
  }
  return NULL;
}
