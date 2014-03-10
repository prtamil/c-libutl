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

typedef struct objclass_s {
  struct objclass_s *parent; 
  tbl_t meth;
} objclass_t;

typedef struct {
  objclass_t *class;
} obj_t;

objClass(pippo, pluto,
  int k;
  float c;
)


struct {
  struct objclass_s *parent; 
  tbl_t meth;
} cls_pippo;

struct objclass *cls_pippo_parent = cls_pluto;

typedef struct {
  objclass_t *obj_class;
  int k;
  float c;
} pippo


objNew(pippo,3)

o = (obj_t *)pippo_new(3)? (o->class =cls_pippo, 

#endif
