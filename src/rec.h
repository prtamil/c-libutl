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

struct rec_f_t {
  int size;
  int (*cmp)(void * , void *) ;
  t *(*cpy)(void * , void *) ;
  void (*free)(void *) ;
};
 
typedef struct { struct rec_f_t  *f; } rec_t;

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

#define recNew(t,r)  \
  (r = t##_new())

#define recFunFree(t,x)    void t##_free(t *a)
#define recFree(r)   \
  (r = (r ? ((r)->rec_f.free(r),free(r),NULL):NULL); 

#define recFunCpy(t,x,y)   int  t##_cpy(t *a, t *b)


#define recFunCmp(t,x,y)   int  t##_cmp(t *a, t *b)

#define recFunNew(t,x)    \
    static struct rec_##t##_f rec_##t##_func; \
    void t##_init(void *p);\
    void *t##_new() {\
      t *p = NULL;\
      rec_##t##_func.size = sizeof(t);\
      rec_##t##_func.cmp = t##_cmp;\
      rec_##t##_func.cpy = t##_cpy;\
      rec_##t##_func.free = t##_free;\
      p= calloc(1,sizeof(t));\
      if (p) {\
        p->rec_f = rec_##t##_func;\
        t##_init(p);\
      }\
      return p;\
    }\
    void t##_init(void *p)


/**** .h ****/
rec(pippo,
  int k;
  int v;
);

/**** .a ****/

void *rec_cpy(void *a, void *b) 
{
  if (b != a) { 
    if (b == NULL)  recFree(a);
    else if (a == NULL) {
      
      
    }
  }
  
  return a;
}

/**** .c ****/
recFunNew(pippo, a) { }
recFunCpy(pippo,a,b) { memcpy(a,b,sizeof(pippo));}
recFunCmp(pippo, a,b) { memcmp(a,b,sizeof(pippo));}
recFunFree(pippo, a) { }

int main()
{
  pippo *rr;
  
  recNew(pippo,r);
  recFree(r); 
}

