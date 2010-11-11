CFLAGS ?= -Werror -Wall

libs = msg.c

all: hello

hello: hello.o $(libs:.c=.o)

tests = $(wildcard *_test.c)

.PHONY: check
check: ct/_ctcheck
	ct/_ctcheck

ct/_ctcheck: ct/_ctcheck.o ct/ct.o $(libs:.c=.o) $(tests:.c=.o)

ct/_ctcheck.c: $(tests) ct/ctgen
	ct/ctgen -o ct/_ctcheck.c $(tests)

.PHONY: clean
clean:
	rm -f ct/_* *.o ct/*.o ct/ctgen hello
