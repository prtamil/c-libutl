#if 0



rec(pippo,
  int k;
vec_t v;
)

typedef struct {
  size_t size;
  int (*)(void * , void *) cmp;
  void *(*)(void * , void *) cpy;
  void (*)(void *) free;
} rec_func_t;

typedef struct pippo  {
  rec_func_t *rec_func;
  int k;
  vec_t v;

} pippo; 

int pippo_cmp(void *a, void *b);
void *pippo_cpy(void *a, void *b);
void   pippo_free(void *a);

recFunCpy(pippo,x,y) 
{

}

#endif

#define rec(t,y) \
  struct rec_##t##_f;\
  typedef struct t { struct rec_##t##_f *rec_f; y } t; \
  struct rec_##t##_f {\
    int size;\
    int (*cmp)(t * , void *) ;\
    t *(*cpy)(t * , t *) ;\
    void (*free)(t *) ;\
  }; \
  int    t##_cmp(t *a, t *b); \
  t     *t##_cpy(t *a, t *b);\
  void   t##_free(t *a); \
  void   t##_init_func(void);\
  void  *t##_init(void *);

#define recNew(r,t)  (r = t##_new())
#define recFree() 

#define recFunCpy(t,x,y)   t *t##_cpy(t *a, t *b)
#define recFunCmp(t,x,y)   t *t##_cmp(t *a, t *b)
#define recFunFree(t,x,y)  t *t##_free(t *a, t *b)

#define recFunNew(t,x)    \
    static struct rec_##t##_f rec_##t##_func; \ 
    void *##t##_init(void *p);\
    void *##t##_new() {\
      ##t## *p = NULL;\
      rec_##t##_func.size = sizeof(##t##);\
      rec_##t##_func.cmp = ##t##_cmp;\
      rec_##t##_func.cpy = ##t##_cpy;\
      rec_##t##_func.free = ##t##_free;\
      p= calloc(1,rec_##t##_func.size);\
      if (p) {\
        p->rec_f = rec_##t##_func;\
        ##t##_init(p);\
      }\
      return p;\
    }


/**** .h ****/
rec(pippo,
  int k;
  int v;
);

/**** .c ****/
recFunNew(r, pippo) { }
recFunCpy(r,a,b) { memcpy(a,b,sizeof(r));}
recFunCmp(r, pippo) { memcmp(a,b,sizeof(r));}
recFunFree(r, pippo) { free(}

int main()
{
  pippo *rr;
  
  recNew(rr,pippo);
   
}

