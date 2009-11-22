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
} object_t;

#endif
