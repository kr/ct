#include <stdio.h>
#include "msg.h"

void
main() {
    set_message("hello, world");
    printf("%s\n", get_message());
}
