void ctfail_(char * file, int line, char *exp, char *msg);
#define ctfail(e,m) ctfail_(__FILE__, __LINE__, (e), (m))
#define ASSERT(X,msg) do if (!(X)) { ctfail(#X,(msg)); } while (0)
