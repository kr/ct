#define TmpDirPat "/tmp/ct.XXXXXX"

typedef struct T T;

struct T {
    void (*f)(void);
    char *name;
    int  status;
    int  fd;
    int  pid;
    char dir[sizeof TmpDirPat];
};

extern T ctmain[];
