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

#define try(utl_env) \
               do {int utl_err = 0; int utlErr = 0;\
                   jmp_buf utl_jb; \
                   jmp_buf *utl_jb_prev = utl_env; \
                   utl_env = &utl_jb; \
                   for (;utl_err>=0; (utl_env = utl_jb_prev)) \
                     if (utl_err > 0) throw(utl_env,utl_err); \
                     else switch ((utl_err = setjmp(*utl_env)))  {\
                            case 0 :
                          
#define catch(e)         break; case e : utlErr = utl_err; utl_err = -1; \
                                goto utl_lbl(_try_ , __LINE__) ; utl_lbl(_try_ , __LINE__) 

#define catchall         break; default : utlErr = utl_err; utl_err = -1;  \
                                goto utl_lbl(_try_ , __LINE__) ; utl_lbl(_try_ , __LINE__)
              
#define tryend    } } while(0)

#define throw(env,err) (env? longjmp(*env, err): exit(utlErr))

typedef jmp_buf *utlEnv_t; 

void main()
{
          int k = 0;
          utlEnv_t jb = NULL;
          
          try(jb)    { throw(jb,7); }
            catch(1) : { k = 1; }
            catch(2) : { k = 2; }
            catchall : { printf("%d - ",utlErr);k = 9; }
          tryend;
          
 printf("%d\n",k);
}
