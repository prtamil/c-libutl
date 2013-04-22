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


#ifdef UTL_C
#define utl_extern(n,v) n v
#else
#define utl_extern(n,v) extern n
#endif
#define utl_initvoid ;

#define utl_trymax 16

#define utlTry(utl_env) \
               do {int utl_err = 0; int utlErr = 0;\
                   jmp_buf utl_jb; \
                   jmp_buf *utl_jb_prev = utl_env; \
                   utl_env = &utl_jb; \
                   for (;utl_err>=0; (utl_env = utl_jb_prev)) \
                     if (utl_err > 0) utlThrow(utl_env,utl_err); \
                     else switch ((utl_err = setjmp(*utl_env))) if (1) {case 0 :} goto x##__LINE__ ; { \
                            case 0 :
                          
#define utlCatch(e)         break; case e : utlErr = utl_err; utl_err = -1;

#define utlCatchAny         break; default : utlErr = utl_err; utl_err = -1;  
              
#define utlTryEnd    } \
                   } while(0)


#define utlThrow(env,err) (env? longjmp(*env, err): exit(utlErr))

typedef jmp_buf *utlEnv_t; 

void main()
{
          int k = 0;
          utlEnv_t jb = NULL;
          
          utlTry(jb)  { utlThrow(jb,7); }
          utlCatch(1) { k = 1; }
          utlCatch(2) { k = 2; }
          utlCatchAny { printf("%d - ",utlErr);k = 9; }
          utlTryEnd;
          
 printf("%d\n",k);
}
