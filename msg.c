/* msg.c - keep track of a message */

#include "msg.h"

const char *msg = "default message";

void
set_message(const char *m)
{
    msg = m;
}

const char *
get_message(void)
{
    return msg;
}
