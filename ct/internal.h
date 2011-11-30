typedef struct T T;

struct T {
    void (*f)(void);
    char *name;
    int  status;
    int  fd;
    void (*setup)(void);
    void (*teardown)(void);
};

extern T ctmain[];
