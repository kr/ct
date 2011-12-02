CFLAGS ?= -Wall -Wextra

libs = msg.c
objs = $(libs:.c=.o)

preTest	:= $(shell python ct/nettest.py)
tests = $(wildcard *-test.c)
tests += $(preTest)
tobjs := $(tests:.c=.o)

ntests = $(wildcard *-nettest.c)
nobjs = $(ntests:.c=.o)

protocols = ct/udp_protocol.c #insert protocols here
pobjs = $(protocols:.c=.o)

all: hello

hello: hello.o $(objs)

.PHONY: check
check: ct/_ctcheck
	ct/_ctcheck

ct/ct.o: ct/ct.h

ct/netTestRunner.o: ct/netTestRunner.h ct/netTestRunner.c

ct/_ctcheck: ct/_ctcheck.o ct/ct.o ct/netTestRunner.o $(objs) $(tobjs) $(nobjs) $(pobjs)

$(tobjs): $(tests) $(nobjs) $(pobjs)

ct/_ctcheck.c: $(tobjs) ct/gen
	ct/gen $(tobjs) > $@.part
	mv $@.part $@

.PHONY: clean
clean:
	rm -f ct/_* *.o _net_* ct/*.o hello
