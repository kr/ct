CFLAGS ?= -Werror -Wall

libs = msg.c
objs = $(libs:.c=.o)
testcs = $(wildcard *_test.c)
tests = $(testcs:.c=.o)

all: hello

hello: hello.o $(objs)

.PHONY: check
check: ct/_ctcheck
	ct/_ctcheck

ct/_ctcheck: ct/_ctcheck.o ct/ct.o $(objs) $(tests)

ct/_ctcheck.c: $(tests) ct/gen
	ct/gen $(tests) > $@.part
	mv $@.part $@

.PHONY: clean
clean:
	rm -f ct/_* *.o ct/*.o hello
