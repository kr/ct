# CT

**(Relatively) Easy Unit Testing for C**

## How to use

1. Copy subdirectory `ct` into your project.
2. Add some rules to your makefile. See [Makefile][] for an example.
3. Write some tests. See [msg_test.c][] for an example.
   Test functions are those whose names begin with "ct_test_".
   The test runner forks before each test, so global state
   from one test will not affect another.
4. Run `make check`

## Releases

There will be no releases of this tool. Just clone the latest source from git
and copy it into your project. If you want to update, copy the newer source
into your project.

## History

This is derived from [CUT][] by Billy Tanksley and Sam Falvo.

[CUT]: http://falvotech.com/content/cut/
[Makefile]: https://github.com/kr/ct/blob/master/Makefile
[msg_test.c]: https://github.com/kr/ct/blob/master/msg_test.c
