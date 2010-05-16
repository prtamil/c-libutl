/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/


#define UTL_MAIN
#ifdef UTL_MEMCHECK
#undef UTL_MEMCHECK
#endif
#include "libutl.h"



/*************************************/

FILE *log_file = NULL;
int logLevel = logOFF ;
/*
** These variables are used internally to compose and print log messages:
**
**  .['{=log_abbrev}] The string abbreviations for the levels. 
**  ..
*/

char *log_abbrev[] = {"ALL","DBG","INF","WRN","ERR","FTL","OFF"};

/* 
**  .['{=log_timestr}]  A buffer to compose current time.
**   ['{=log_time}]     A '|time_t| structure to compose current time. 
**  .. 
*/

char log_timestr[32];
time_t log_time = 0 ;



/*************************************/

static char *BEG_CHK = "\xBE\xEF\xF0\x0D";
static char *END_CHK = "\xDE\xAD\xC0\xDA";
static char *CLR_CHK = "\xDE\xFA\xCE\xD0";

#define CHK_NULL       -2
#define CHK_INVALID    -1
#define CHK_OVERFLOW    1
#define CHK_VALID       0

typedef struct {
   size_t size;
   char   chk[4];
   char   data[4];
} utl_mem_t;


static int chk(void *ptr)
{
  utl_mem_t *p;
  
  if (ptr == NULL) return CHK_NULL;
  p = (utl_mem_t *)((char *)ptr -  offsetof(utl_mem_t, data));
  if (memcmp(p->chk,BEG_CHK,4)) return CHK_INVALID; 
  if (memcmp(p->data+p->size,END_CHK,4)) return CHK_OVERFLOW;
  return CHK_VALID; 
}

void *utl_malloc (size_t size, char *file, int line )
{
  utl_mem_t *p;
  
  if (size == 0) utlError(91,"Shouldn't allocate 0 bytes [%s - %d]\n",file,line);
  p = malloc(sizeof(utl_mem_t) +size);
  if (p == NULL) utlError(92,"Out of Memory [%s - %d]\n",file,line);
  p->size = size;
  memcpy(p->chk,BEG_CHK,4);
  memcpy(p->data+p->size,END_CHK,4);
  logInfo("UTL malloc %p[%d] [%s - %d]",p->data,size,file,line);
  return p->data;
};

void *utl_calloc (size_t num, size_t size, char *file, int line)
{
  utl_mem_t *p;
  size = num * size;
  if (size == 0) utlError(91,"Shouldn't allocate 0 bytes [%s - %d]",file,line);
  p = malloc(sizeof(utl_mem_t) +size);
  if (p == NULL) utlError(92,"Out of Memory [%s - %d]",file,line);
  p->size = size;
  memcpy(p->chk,BEG_CHK,4);
  memcpy(p->data+p->size,END_CHK,4);
  memset(p->data,0x00,size);
  logInfo("UTL calloc %p[%d] [%s - %d]",p->data,size,file,line);
  return p->data;
};

void utl_free ( void *ptr, char *file, int line )
{
  utl_mem_t *p=NULL;
  
  switch (chk(ptr)) {
    case CHK_INVALID  : utlError(94,"Invalid or double free [%s - %d]",file,line);     break;
    case CHK_OVERFLOW : utlError(95,"Boundary overflow detected [%s - %d]",file,line); break;
    case CHK_VALID    : p = (utl_mem_t *)((char *)ptr - offsetof(utl_mem_t, data)); 
                        memcpy(p->chk,CLR_CHK,4);
              default : logInfo("UTL free(%p[%d]) [%s - %d]",ptr,p?p->size:0,file,line);
                        break;
  }
  free(p);
}

void *utl_realloc (void *ptr, size_t size, char *file, int line)
{
  utl_mem_t *p;
  
  if (size == 0) {
    dbgmsg("UTL realloc to 0 [%s - %d]\n",file,line);
    utl_free(ptr,file,line); 
  } 
  else {
    switch (chk(ptr)) {
      case CHK_NULL     : return utl_malloc(size,file,line);
      case CHK_INVALID  : utlError(94,"Invalid or double free [%s - %d]\n",file,line);     break;
      case CHK_OVERFLOW : utlError(95,"Boundary overflow detected [%s - %d]\n",file,line); break;
      case CHK_VALID    : p = (utl_mem_t *)((char *)ptr - offsetof(utl_mem_t, data));
                          p = realloc(p,sizeof(utl_mem_t) + size); 
                          if (p == NULL) utlError(92,"Out of Memory [%s - %d]\n",file,line);
                          logInfo("UTL realloc (%p[%d] -> %p[%d]) [%s - %d]",ptr, p->size, p->data, size, file,line);
                          p->size = size;
                          memcpy(p->chk,BEG_CHK,4);
                          memcpy(p->data+p->size,END_CHK,4);
                          ptr = p->data;
                          break;
    }
  }
  return ptr;
}


void *utl_strdup (void *ptr, char *file, int line)
{
  char *dest;
  size_t size;
  
  if (ptr == NULL) return NULL;
  size = strlen(ptr);
  
  dest = utl_malloc(size+1,file,line);
  memcpy(dest,ptr,size+1);
  logInfo("UTL strdup (%p[%d] -> %p) [%s - %d]",ptr, size, dest, file,line);
  return dest;
}
