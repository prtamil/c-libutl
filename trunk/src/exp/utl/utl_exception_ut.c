/* 
**  (C) by Remo Dentato (rdentato@gmail.com)
** 
** This sofwtare is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php 
*/

#define UTL_C
#define UTL_UNITTEST

#include "utl.h"

FILE *f = NULL;
char buf[512];
int k=0;
int c=0;


void functhrow(tryenv env, int err)
{
    throw(env, err);
    TST("Returned to main",0); /* it's an error to be executed! */
}

int main (int argc, char *argv[])
{
  tryenv env;
  int err;
  
  TSTPLAN("utl unit test: try/catch") {
  
    TSTSECTION("Simple catch") {
      TSTGROUP("catch 1") {
        TSTCODE {
          k = 0;
          try(env,err)      { throw(env,1); }
          catch(1) : { k = 1; }
          catch(2) : { k = 2; }
          catchall :  { k = 9; } 
          tryend;
        } TSTEQINT("Exception 1 caught", 1,k);
      }
     
      TSTGROUP("catch 2") {
        TSTCODE {
          k = 0;
          try(env,err)      { throw(env,2); }
          catch(1) : { k = 1; }
          catch(2) : { k = 2; }
          catchall :  { k = 9; } 
          tryend;
        } TSTEQINT("Exception 2 caught", 2,k);
      }
      
      TSTGROUP("catch default") {
        TSTCODE {
          k = 0;
          try(env,err) { throw(env,3);  }
          catch(1) : { k = 1; }
          catch(2) : { k = 2; }
          catchall :  { k = 9; } 
          tryend;
        } TSTEQINT("Exception not caught", 9,k);
      }
    }
    
    TSTSECTION("Catch exceptions from functions") {
      TSTGROUP("catch 1") {
        TSTCODE {
          k = 0;
          try(env,err)       functhrow(env,1);
          catch(1) :  k = 1;
          catch(2) :  k = 2;
          tryend;
        } TSTEQINT("Exception 1 caught", 1,k);
      }
      
      TSTGROUP("catch 2") {
        TSTCODE {
          k = 0;
          try(env,err)       functhrow(env,2);
          catch(1) :  k = 1;
          catch(2) :  k = 2;
          tryend;
        }
        TSTEQINT("Exception 2 caught", 2,k);
      }
      
      TSTGROUP("catch default") {
        TSTCODE {
          k = 0;
          try(env,err)       functhrow(env,3);
          catch(1) :  k = 1;
          catch(2) :  k = 2;
          catchall :   k = 9; 
          tryend;
        }
        TSTEQINT("Exception not caught", 9,k);
        TSTFAILNOTE("Expected: %d got: %d",9,k);
      }
    }

    TSTSECTION("Nested") {
      TSTGROUP("2 levels") {
        TSTCODE {
          k = 0;
          try(env,err)      {
            try(env,err)    { functhrow(env,20); }
            catch(10) : {k += 10;}
            catch(20) : {k += 20;}
            tryend;
          }
          catch(1) : {k += 1;}
          catch(2) : {k += 2;}
          tryend;
        }
        TSTEQINT("Exception 20 caught", 20,k);
        
        TSTCODE {
          k = 0;
          try(env,err) {
            try(env,err)      { functhrow(env,2); }
            catch(10) : {k += 10;}
            catch(20) : {k += 20;}
            tryend;
        }
          catch(1) : {k += 1;}
          catch(2) : {k += 2;}
          tryend;
        }
        TSTEQINT("Exception 2 caught", 2,k);
      }
      
      TSTGROUP("Visibility") {
        TSTCODE {
          k = 0;
          try(env,err) {
            try(env,err)      { functhrow(env,2); }
            catch(10) : {k += 10;}
            catch(20) : {k += 20;}
            tryend;
          }
          catch(1) : {k += 1;}
          catch(2) : {k += 2; functhrow(env,10);}
          catchall :  {k += 100;} 
          tryend;
        }
        TSTEQINT("Inner try are invisible", 102,k);
        TSTEXPECTED("%d",102,"%d",k);
      }

    }
    
    TSTSECTION("Multiple throw") {
      TSTGROUP("Same try") {
        TSTCODE {
          k = 0;
          try(env,err)      { throw(env,2); }
          catch(1) : { k += 1; }
          catch(2) : { k += 2; functhrow(env,1);}
          catchall :  { k += 9; } 
          tryend;
        } TSTEQINT("Exception 2 then 1 caught", 3,k);
      }
        
      TSTGROUP("Nested try") {
        TSTCODE {
          k = 0;
          try(env,err)      {
            try(env,err)      { functhrow(env,20); }
            catch(10) : {k += 10; functhrow(env,2);}
            catch(20) : {k += 20; throw(env,10);}
            tryend;
          }
          catch(1) : {k += 1;}
          catch(2) : {k += 2;}
          tryend;
          
        }  TSTEQINT("Exception 10,20,2 caught", 32,k);
        
        TSTCODE {
          k = 0;
          try(env,err)      {
            try(env,err)      { functhrow(env,20); }
            catch(10) : {k += 10; functhrow(env,2);}
            catch(20) : {k += 20; throw(env,10);}
            tryend;
          }
          catch(1) : {k += 1;}
          catch(2) : {k += 2; functhrow(env,3);}
          catchall :  {k += 100; } 
          tryend;
        }  TSTEQINT("Exception 10,20,2,3 caught", 132,k);
      }
    }
    
  }
}
