/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#ifndef REC_H
#define REC_H

struct rec_f_t {
  int size;
  int   (*cmp)  (void * , void *) ;
  void *(*cpy)  (void * , void *) ;
  void  (*free) (void *) ;
};
 
typedef struct { struct rec_f_t  *rec_f; } rec_t;

#define rec(t,y) \
  struct rec_##t##_f;\
  typedef struct t { struct rec_##t##_f *rec_f; y } t; \
  struct rec_##t##_f {\
    int    size;\
    int  (*cmp)  (t * , t *) ;\
    t   *(*cpy)  (t * , t *) ;\
    void (*free) (t *) ;\
  }; \
  int    t##_cmp(t *a, t *b); \
  t     *t##_cpy(t *a, t *b);\
  void   t##_free(t *a); \
  void  *t##_init(t *);

#define recNew(t,r)  (r = t##_new())

#define recFunFree(t,x)    void t##_free(t *a)

#define recFree(r)   \
  (r = (r ? ((r)->rec_f.free(r),free(r),NULL):NULL); 


#define recFunCmp(t,x,y)   int  t##_cmp(t *a, t *b)

#define recCpy(a,b) rec_cpy(rec_t)

#define recFunCpy(t,x,y)   int  t##_cpy(t *a, t *b)

#define recFunNew(t,x)    \
    static struct rec_##t##_f rec_##t##_func; \
    void *t##_new() {\
      t *p = NULL;\
      rec_##t##_func.size = sizeof(t);\
      rec_##t##_func.cmp = t##_cmp;\
      rec_##t##_func.cpy = t##_cpy;\
      rec_##t##_func.free = t##_free;\
      p = calloc(1,sizeof(t));\
      if (p) {\
        p->rec_f = rec_##t##_func;\
        t##_init(p);\
      }\
      return p;\
    }\
    void t##_init(t *p)

#define recSize(a) ((a)->rec_f.size)

/**** .h ****/
rec(pippo,
  int k;
  int v;
);

/**** .a ****/

void *rec_cpy(rec_t *a, struct rec_t *b) 
{
  if (b != a) { 
    if (!b)  recFree(a);
    else {
      if (!a) a = malloc(recSize(b));
      if (!a) utlError(8912,utlErrInternal);
      memcpy(a,b,recSize(b));
      b->rec_f.cpy((void *)a,(void *)b);
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

#endif
