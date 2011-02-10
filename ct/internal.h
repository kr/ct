typedef struct T {
    int status, fd;
    const char *name;
} T;

typedef void(*ct_fn)(void);

void ct_report(T ts[], int n);
void ct_run(T *t, int i, ct_fn f, const char *name);
