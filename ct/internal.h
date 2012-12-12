typedef struct T T;

struct T {
    void (*f)(void);
    char *name;
    int  status;
    int  fd;
    int  pid;
};

extern T ctmain[];
