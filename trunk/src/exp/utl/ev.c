/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

typedef struct utl_env_s { 
  jmp_buf jb;
  struct utl_env_s  *prev;
  struct utl_env_s **orig;
  int err;
} utl_env_s, *tryenv; 

#define utl_lblx(x,l)  x##l
#define utl_lbl(x,l)   utl_lblx(x,l)

#define try(utl_env,x) \
            do { struct utl_env_s utl_cur_env; int utlErr; \
                 utl_cur_env.err = 0; \
                 utl_cur_env.prev = utl_env; \
                 utl_cur_env.orig = &utl_env; \
                 utl_env = &utl_cur_env; \
                 if ((utl_cur_env.err = setjmp(utl_cur_env.jb))==0) {\
                   x \
                 }   
                 
#define catch(y) else { \
                   utlErr = utl_cur_env.err; \
                   *utl_cur_env.orig = utl_cur_env.prev;\
                   if (utlErr == 0) break; \
                   else switch (utlErr) { \
                      y \
                   } \
                 } \
               } while(0)

                  

#define throw(env,err) (env? longjmp(env->jb, err): exit(err))
#define rethrow        (throw(utl_cur_env.prev,utlErr))

int functhr(tryenv ee,int err) 
{
  throw(ee,err);
}

void main()
{
          int k = 0;
          tryenv ee = NULL;
          
          try(ee , {
            throw(ee,7);
          }) 
          catch ({
             case 7 : k = 9;
                      break;
             default : rethrow ;
          });
          
 printf("%d %p\n",k,ee);
          ee = NULL; k = 9;
          try(ee, {
           functhr(ee,5);
          })
          catch ({
            case 5 : k = 1; break;
            case 2 : k = 2; break;
          });
          
 printf("%d %p\n",k,ee);
#if 0
          ee = NULL;
          try(ee)    { functhr(ee,2); }
            catch(1)  { k = 1; }
            catch(2)  {
              k = 2;
              try(ee) {
                  k += 10;
                  throw(ee,200);
                }
                catch (200)  { k+=200;};
              tryend;
            }
            catchall  { printf("%d - ",utlErr);k = 9; }
          tryend;
          
 printf("%d %p\n",k,ee);
#endif
}
