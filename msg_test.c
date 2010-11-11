#include <string.h>
#include "msg.h"
#include "ct/ct.h"

void
ct_setup_pq()
{
}

void
ct_test_set_message()
{
    char *m;

    set_message("foo");
    m = get_message();
    ASSERT(strcmp("foo", m) == 0, "message does not match");
}

void
ct_test_default_message()
{
    char *m;

    m = get_message();
    ASSERT(strcmp("default message", m) == 0, "message does not match");
}

void
ct_teardown_pq()
{
}
