#ifndef _MY_PROTOCOL_H
#define _MY_PROTOCOL_H

#include "protocol.h"

#include <arpa/inet.h>
#include <sys/socket.h>

struct ctnode {
  // Insert node information here
};

// These functions should be uniquely named for your protocol
struct ctnode * createMyNode(char *name);
void deleteMyNode(struct ctnode *node);

// Don't rename this struct. 
// Make the function pointers inside match the names above
static const struct protocol theProtocol = { &createMyNode, &deleteMyNode };

#endif
