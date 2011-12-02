#include "my_protocol.h"

#include <stdlib.h>
#include "ct.h"

struct ctnode * createMyNode(__attribute__((unused)) char *name) {
  // Allocate space for a node and fill it up
  // The name argument matches the name of the function this node runs
  // If you would like to use the name argument remove "__attribute__((unused))"
}

void deleteMyNode(struct ctnode *node) {
  // Free the node and any other space you allocated in the create function
}
