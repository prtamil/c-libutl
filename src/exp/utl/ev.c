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

#define utl_lbl0(x,l)  x##l
#define utl_lbl(x,l)  utl_lbl0(x,l)

typedef struct utl_env_s {jmp_buf jb; struct utl_env_s *prev; int err;} utl_env_s;
typedef utl_env_s *utlEnv_t; 

#define try(utl_env) \
               do { struct utl_env_s utl_cur_env; int utlErr; \
                    utl_cur_env.err = 0; \
                    utl_cur_env.prev = utl_env; \
                    utl_env = &utl_cur_env; \
                    for (; utl_cur_env.err >= 0; (utl_env = utl_cur_env.prev)? utl_env->err = utl_cur_env.err : 0 ) \
                     if (utl_cur_env.err > 0) throw(utl_env,utl_cur_env.err); \
                     else if (!utl_env) break; \
                     else switch ((utl_cur_env.err = setjmp(utl_cur_env.jb)))  {\
                            case 0 :
                          
#define catch(e)         break; case e : utlErr = utl_cur_env.err; utl_cur_env.err = -1; \
                                goto utl_lbl(_try_ , __LINE__) ; utl_lbl(_try_ , __LINE__) 

#define catchall         break; default : utlErr = utl_cur_env.err; utl_cur_env.err = -1;  \
                                goto utl_lbl(_try_ , __LINE__) ; utl_lbl(_try_ , __LINE__)
              
#define tryend    } } while(0)

#define throw(env,err) (env? longjmp(env->jb, err): exit(err))

int functhr(utlEnv_t ee,int err) 
{
  throw(ee,err);
}

void main()
{
          int k = 0;
          utlEnv_t ee = NULL;
          
          try(ee)    { throw(ee,7); }
            catch(1) : { k = 1; }
            catch(2) : { k = 2; }
            catchall : { printf("%d - ",utlErr);k = 9; }
          tryend;
 printf("%d %p\n",k,ee);
          ee = NULL;
          try(ee)    { functhr(ee,5); }
            catch(1) : { k = 1; }
            catch(2) : { k = 2; }
            catchall : { printf("%d - ",utlErr);k = 9; }
          tryend;
          
 printf("%d %p\n",k,ee);
          ee = NULL;
          try(ee)    { functhr(ee,2); }
            catch(1) : { k = 1; }
            catch(2) : {
              k = 2;
              try(ee) {
                  k += 10;
                  throw(ee,200);
                }
                catch (200) : { k+=200;};
              tryend;
            }
            catchall : { printf("%d - ",utlErr);k = 9; }
          tryend;
          
 printf("%d %p\n",k,ee);

}
