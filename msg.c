/* msg.c - keep track of a message */

static char *msg = "default message";

void
set_message(char *m)
{
    msg = m;
}

char *
get_message()
{
    return msg;
}
