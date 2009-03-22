/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
*/

#include <stdio.h>
#include <math.h>
#include "libutl.h"

struct Point2D_s;

typedef struct {
  objCLASS;
  void (*draw)(struct Point2D_s *);
  void (*move)(struct Point2D_s *pt, float dx, float dy);
} Point2DClass;

Point2DClass *Point2D_Class = NULL;

typedef struct Point2D_s {
  Point2DClass *class;
  float x;
  float y;
} Point2D;


Point2D *Point2DNew()
{
  Point2D *pt;
  pt = malloc(sizeof(Point2D));
  if (pt) {
    pt->x = 0.0;
    pt->y = 0.0;
  }
  return pt;
}

Point2D *Point2DCpy(Point2D *dst, Point2D *src)
{
  if (src && src->class == Point2D_Class) {
    if (dst == NULL) dst = Point2DNew();
    if (dst != NULL) {
      dst->x = src->x;
      dst->y = src->y;
    } 
  }
  return dst;
} 

void Point2DDraw(Point2D *pt)
{
  if (pt && pt->class == Point2D_Class) {
    printf("DRAW POINT2D: (%.2f,%.2f)\n",pt->x,pt->y);
  }
} 

void Point2DMove(Point2D *pt,float dx, float dy)
{
  if (pt && pt->class == Point2D_Class) {
    pt->x += dx;
    pt->y += dy;
  }
} 

int Point2DCmp(Point2D *pt, Point2D *qt)
{
  if (pt && qt && pt->class == Point2D_Class && qt->class == Point2D_Class) {
    return (pt->x == qt->x) && (pt->y == qt->y);
  }
  return 0;
} 

void Point2DFree(Point2D *pt)
{
  if (pt && pt->class == Point2D_Class) {
    free(pt);
  }
} 


Point2DClass *Point2DClass_Init()
{
  if (Point2D_Class == NULL) {
    Point2D_Class = malloc(sizeof(Point2DClass));
  }
    
  if (Point2D_Class != NULL) {
    Point2D_Class->size = sizeof(Point2D);
    Point2D_Class->new = (objNewFun)Point2DNew;
    Point2D_Class->cpy = (objCpyFun)Point2DCpy;
    Point2D_Class->cmp = (objCmpFun)Point2DCmp;
    Point2D_Class->free= (objFreeFun)Point2DFree;
    
    Point2D_Class->draw = Point2DDraw;
    Point2D_Class->move = Point2DMove;
    
  }
  return Point2D_Class;
} 

int main(int argc, char *argv[])
{
  Point2D *p;
  Point2D *q;
  
  objClass(Point2D);

  p = objNew(Point2D);

  obj(p,draw);
  obj(p,move,3,-4.3);
  obj(p,draw);

  return (0);
}
