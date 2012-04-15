#ifndef _PROTOCOL_H
#define _PROTOCOL_H

// A node in the network graph contains all information for 
// communicating in and out of the node
struct ctnode;

typedef struct ctnode * (*nodeCreator)(char *);
// Creates a node in the network graph, given the node's name
//struct ctnode * createNode(char * node);

typedef void (*nodeDeleter)(struct ctnode*);
// Frees the node and all pointers that it owns
//void deleteNode(struct ctnode *);

struct protocol {
  nodeCreator createNode;
  nodeDeleter deleteNode;
};

#endif
