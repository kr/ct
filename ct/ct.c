/* CT - (Relatively) Easy Unit Testing for C */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "internal.h"

static void
die(int code, const char *fmt, ...)
{
    va_list v;

    putc('\n', stderr);

    va_start(v, fmt);
    vfprintf(stderr, fmt, v);
    va_end(v);

    if (fmt && *fmt) fputs(": ", stderr);
    fprintf(stderr, "%s\n", strerror(errno));
    exit(code);
}

static int
failed(int s)
{
    return WIFEXITED(s) && (WEXITSTATUS(s) == 255);
}

void
ct_exit(T ts[], int n)
{
    int i, r, s;
    char buf[1024]; // arbitrary size
    int cf = 0, ce = 0;

    putchar('\n');
    for (i = 0; i < n; i++) {
        if (!ts[i].status) continue;

        printf("\n%s: ", ts[i].name);
        if (failed(ts[i].status)) {
            cf++;
            printf("failure");
        } else {
            ce++;
            printf("error");
            if (WIFEXITED(ts[i].status)) {
                printf(" (exit status %d)", WEXITSTATUS(ts[i].status));
            }
            if (WIFSIGNALED(ts[i].status)) {
                printf(" (signal %d)", WTERMSIG(ts[i].status));
            }
        }

        putchar('\n');
        lseek(ts[i].fd, 0, SEEK_SET);
        while ((r = read(ts[i].fd, buf, sizeof(buf)))) {
            s = fwrite(buf, 1, r, stdout);
            if (r != s) die(3, "fwrite");
        }
    }

    printf("\n%d tests; %d failures; %d errors.\n", n, cf, ce);
    exit(!!(cf + ce));
}

void
ct_fail_(char *file, int line, char *exp, char *msg)
{
  printf("  %s:%d: (%s) %s\n", file, line, exp, msg);
  fflush(stdout);
  fflush(stderr);
  exit(-1);
}

void
ct_run(T *t, int i, ct_fn f, const char *name)
{
    pid_t pid;
    int status, r, ofd;
    char c;
    FILE *out;

    t->name = name;

    out = tmpfile();
    if (!out) die(1, "tmpfile");
    ofd = fileno(out);

    fflush(stdout);
    fflush(stderr);

    pid = fork();
    if (pid < 0) {
        die(1, "fork");
    } else if (!pid) {
        r = dup2(ofd, 1); // send stdout to tmpfile
        if (r == -1) die(3, "dup2");

        r = close(ofd);
        if (r == -1) die(3, "fclose");

        r = dup2(1, 2); // send stderr to stdout
        if (r < 0) die(3, "dup2");

        f();
        exit(0);
    }

    r = waitpid(pid, &status, 0);
    if (r != pid) die(3, "wait");

    t->status = status;
    if (!status) {
        // Since we won't need the (potentially large) output,
        // free its disk space immediately.
        close(ofd);
        c = '.';
    } else if (failed(status)) {
        c = 'F';
    } else {
        c = 'E';
    }
    t->fd = ofd;

    if (i % 10 == 0) {
        if (i % 50 == 0) {
            putchar('\n');
        }
        printf("%5d", i);
    }

    putchar(c);
    fflush(stdout);
}
