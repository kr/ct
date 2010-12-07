void ct_fail_(char * file, int line, char *exp, char *msg);
#define ct_fail(e,m) ct_fail_(__FILE__, __LINE__, (e), (m))
#define ASSERT(X,msg) do if (!(X)) { ct_fail(#X,(msg)); } while (0)
