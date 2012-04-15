CFLAGS ?= -Wall -Wextra

libs = msg.c
objs = $(libs:.c=.o)

tests = $(wildcard *-test.c)
tobjs = $(tests:.c=.o)

all: hello

hello: hello.o $(objs)

.PHONY: check
check: ct/_ctcheck
	ct/_ctcheck

ct/ct.o: ct/ct.h

$(tobjs): ct/ct.h

ct/_ctcheck: ct/_ctcheck.o ct/ct.o $(objs) $(tobjs)

ct/_ctcheck.c: $(tobjs) ct/gen
	ct/gen $(tobjs) > $@.part
	mv $@.part $@

.PHONY: clean
clean:
	rm -f ct/_* *.o ct/*.o hello
