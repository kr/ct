typedef struct T T;


struct T {
    int status, fd;
    const char *name;
};


void ct_report(T ts[], int n);
void ct_run(T *t, int i, void(*f)(), const char *name);
