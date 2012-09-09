# CT

**(Relatively) Easy Unit Testing for C**

## How to use

1. Copy subdirectory `ct` into your project.
2. Add some rules to your makefile. See [Makefile][] for an example.
3. Write some tests. See [msg-test.c][] for an example.
   Test functions are those whose names begin with "cttest".
   The test runner forks before each test, so global state
   from one test will not affect another.
4. Run `make check`

## Terminal Output

Running `make check` in the example supplied looks like this:

```
~/Projects/ct[master]: make check
cc -Werror -Wall   -c -o msg-test.o msg-test.c
ct/gen msg-test.o > ct/_ctcheck.c.part
mv ct/_ctcheck.c.part ct/_ctcheck.c
cc -Werror -Wall   -c -o ct/_ctcheck.o ct/_ctcheck.c
cc -Werror -Wall   -c -o ct/ct.o ct/ct.c
cc -Werror -Wall   -c -o msg.o msg.c
cc   ct/_ctcheck.o ct/ct.o msg.o msg-test.o   -o ct/_ctcheck
ct/_ctcheck
.EFFE.

cttestexit: error (exit status 2)

cttestfailure: failure
msg-test.c:30: test: 1 == 2

cttestfmt: failure
msg-test.c:37: test: n == 2
msg-test.c:37: n is 1

cttestsegfault: error (signal 11)

2 failures; 2 errors.
make: *** [check] Error 1
```

## Releases

There will be no releases of this tool. Just clone the latest source from git
and copy it into your project. If you want to update, copy the newer source
into your project.

## History

Inspired by [CUT][] 2.1 by Sam Falvo and Billy Tanksley.
Also with ideas from the [Go testing package][gotesting] and [gotest][].

[CUT]: http://falvotech.com/content/cut/
[Makefile]: https://github.com/kr/ct/blob/master/Makefile
[msg-test.c]: https://github.com/kr/ct/blob/master/msg-test.c
[gotesting]: http://golang.org/pkg/testing/
[gotest]: http://golang.org/cmd/go/#Test_packages
