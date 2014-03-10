
TYPES

chs_t (equivalent to char *)
chssubfun_t function pointer: 

typedef char *(*chssubfun_t)(char *mtc, pmx_t cpt);

FUNCTIONS 
chs_t chsnew();
     
chs_t chsfree(chs_t s);
    
long chslen(chs_t s);     
char chschrat(chs_t s, long pos);   
           
chs_t chscpy(chs_t s, char *x);         
chs_t chscat(chs_t s, char *x);     
chs_t chsins(chs_t s, long pos, char *x);
     
chs_t chsncpy(chs_t s, char *x, long n);
chs_t chsncat(chs_t s, char *x, long n);    
chs_t chsnins(chs_t s, long pos, char *x, long n);    

           
chs_t chssetchr(chs_t s, long pos, char c);  
chs_t chscatchr(chs_t s, char c);  
chs_t chsinschr(chs_t s, long pos, char c);
           
chs_t chsdel(chs_t s,long from, long to);     
chs_t chstrim(chs_t s, char *left, char *right)    
           
chs_t chsupper(chs_t s);   
chs_t chslower(chs_t s);   
chs_t chsreverse(chs_t s); 
           
chs_t chsprintf(chs_t s, char *fmt, ...);  
chs_t chscpyf(chs_t s, char *fmt, ...);    
chs_t chscatf(chs_t s, char *fmt, ...);
chs_t chsinsf(chs_t s, long pos, char *fmt, ...);    
           
chs_t chsgetline(chs_t s, FILE *f); 
chs_t chscatline(chs_t s, FILE *f);
 
chs_t chscatfile(chs_t s, FILE *f);
chs_t chsgetfile(chs_t s, FILE *f); 
 
pmx_t chsmatch(chs_t s, long pos, char *pat);   
chs_t chssub(chs_t s, long pos, char *pat, char *rpl);     
chs_t chssubfun(chs_t s, long pos, char *pat, chssubfun_t f);  
           
chslines   
           
