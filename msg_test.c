#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "msg.h"
#include "ct/ct.h"

void
cttestset()
{
    char *m;

    set_message("foo");
    m = get_message();
    ASSERT(strcmp("foo", m) == 0, "message does not match");
}

void
cttestdefault()
{
    char *m;

    m = get_message();
    ASSERT(strcmp("default message", m) == 0, "message does not match");
}


void
cttestfailure()
{
    ASSERT(0, "bah");
}

void
cttestsegfault()
{
    *(int*)0 = 0;
}

void
cttestexit()
{
    exit(2);
}
