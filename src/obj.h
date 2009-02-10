/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#ifndef OBJ_H
#define OBJ_H

#include "libutl.h"

#define objCLASS    struct objclass_s *parent; \
                    int   (*cmp)(void *a, void *b);\
                    void *(*new)(void); \
                    void *(*free)(void *a);\
                    void *(*cpy)(void *a, void *b)

typedef struct objclass_s {
  objCLASS;
} objclass_t;

typedef struct {
  objclass_t *class;
} obj_s;
 
typedef obj_s *obj_t; 

extern obj_t *obj_tmp;
 
#define objCpy(d,s) ((d)->class->cpy(d,s))
#define objDup(s)   ((s)->class->dup(s))
#define objNew(c) \
  (((obj_tmp=(obj_t)((c)->new())) \
                        ? ((obj_tmp)->class=c)\
                        : c)\
     , obj_tmp)
#define objCmp(a,b) ((a)->class->cmp(a,b))
#define objFree(o)  ((o)->class->free(o),NULL)

#define obj(o,m,...) o->class->m(o,__VA_ARGS__) 

#endif
