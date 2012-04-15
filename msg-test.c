#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "msg.h"
#include "ct/ct.h"


/* this function will run before each cttest in this file */
void ctsetup(){
    ;
}

/* this function will run after each cttest in this file */
void ctteardown(){
    ;
}

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
    *(int*)0 = 0;
}

void
cttestexit()
{
    exit(2);
}
