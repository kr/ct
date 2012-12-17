#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "msg.h"
#include "ct/ct.h"

void
cttestset()
{
    char *m;

    set_message("foo");
    m = get_message();
    assert(strcmp("foo", m) == 0);
}

void
cttestdefault()
{
    char *m;

    m = get_message();
    assert(strcmp("default message", m) == 0);
}


void
cttestfailure()
{
    assert(1 == 2);
}

void
cttestfmt()
{
    int n = 1;
    assertf(n == 2, "n is %d", n);
}

void
cttestsegfault()
{
    *(volatile int*)0 = 0;
}

void
cttesttmpdir()
{
    assert(chdir(ctdir()) == 0);
    assert(open("x", O_CREAT|O_RDWR, 0777));
}

void
cttestexit()
{
    exit(2);
}
