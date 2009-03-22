# 1 "gr2D.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "gr2D.c"







# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 1 3
# 19 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/_mingw.h" 1 3
# 20 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 2 3






# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 1 3 4
# 213 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 3 4
typedef unsigned int size_t;
# 325 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 3 4
typedef short unsigned int wchar_t;
# 354 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 3 4
typedef short unsigned int wint_t;
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 2 3
# 27 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 2 3

# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdarg.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stdarg.h" 1 3 4
# 44 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdarg.h" 2 3
# 29 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 2 3
# 138 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
typedef struct _iobuf
{
 char* _ptr;
 int _cnt;
 char* _base;
 int _flag;
 int _file;
 int _charbuf;
 int _bufsiz;
 char* _tmpfname;
} FILE;
# 163 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
extern __attribute__ ((dllimport)) FILE _iob[];
# 178 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
 FILE* __attribute__((__cdecl__)) fopen (const char*, const char*);
 FILE* __attribute__((__cdecl__)) freopen (const char*, const char*, FILE*);
 int __attribute__((__cdecl__)) fflush (FILE*);
 int __attribute__((__cdecl__)) fclose (FILE*);

 int __attribute__((__cdecl__)) remove (const char*);
 int __attribute__((__cdecl__)) rename (const char*, const char*);
 FILE* __attribute__((__cdecl__)) tmpfile (void);
 char* __attribute__((__cdecl__)) tmpnam (char*);


 char* __attribute__((__cdecl__)) _tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) _rmtmp(void);


 char* __attribute__((__cdecl__)) tempnam (const char*, const char*);
 int __attribute__((__cdecl__)) rmtmp(void);



 int __attribute__((__cdecl__)) setvbuf (FILE*, char*, int, size_t);

 void __attribute__((__cdecl__)) setbuf (FILE*, char*);





 int __attribute__((__cdecl__)) fprintf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) printf (const char*, ...);
 int __attribute__((__cdecl__)) sprintf (char*, const char*, ...);
 int __attribute__((__cdecl__)) _snprintf (char*, size_t, const char*, ...);
 int __attribute__((__cdecl__)) vfprintf (FILE*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) vprintf (const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) vsprintf (char*, const char*, __gnuc_va_list);
 int __attribute__((__cdecl__)) _vsnprintf (char*, size_t, const char*, __gnuc_va_list);


int __attribute__((__cdecl__)) snprintf(char* s, size_t n, const char* format, ...);
extern __inline__ int __attribute__((__cdecl__))
vsnprintf (char* s, size_t n, const char* format, __gnuc_va_list arg)
  { return _vsnprintf ( s, n, format, arg); }
int __attribute__((__cdecl__)) vscanf (const char * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) vfscanf (FILE * __restrict__, const char * __restrict__,
       __gnuc_va_list);
int __attribute__((__cdecl__)) vsscanf (const char * __restrict__,
       const char * __restrict__, __gnuc_va_list);






 int __attribute__((__cdecl__)) fscanf (FILE*, const char*, ...);
 int __attribute__((__cdecl__)) scanf (const char*, ...);
 int __attribute__((__cdecl__)) sscanf (const char*, const char*, ...);




 int __attribute__((__cdecl__)) fgetc (FILE*);
 char* __attribute__((__cdecl__)) fgets (char*, int, FILE*);
 int __attribute__((__cdecl__)) fputc (int, FILE*);
 int __attribute__((__cdecl__)) fputs (const char*, FILE*);
 char* __attribute__((__cdecl__)) gets (char*);
 int __attribute__((__cdecl__)) puts (const char*);
 int __attribute__((__cdecl__)) ungetc (int, FILE*);







 int __attribute__((__cdecl__)) _filbuf (FILE*);
 int __attribute__((__cdecl__)) _flsbuf (int, FILE*);



extern __inline__ int __attribute__((__cdecl__)) getc (FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) *__F->_ptr++
    : _filbuf (__F);
}

extern __inline__ int __attribute__((__cdecl__)) putc (int __c, FILE* __F)
{
  return (--__F->_cnt >= 0)
    ? (int) (unsigned char) (*__F->_ptr++ = (char)__c)
    : _flsbuf (__c, __F);
}

extern __inline__ int __attribute__((__cdecl__)) getchar (void)
{
  return (--(&_iob[0])->_cnt >= 0)
    ? (int) (unsigned char) *(&_iob[0])->_ptr++
    : _filbuf ((&_iob[0]));
}

extern __inline__ int __attribute__((__cdecl__)) putchar(int __c)
{
  return (--(&_iob[1])->_cnt >= 0)
    ? (int) (unsigned char) (*(&_iob[1])->_ptr++ = (char)__c)
    : _flsbuf (__c, (&_iob[1]));}
# 297 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
 size_t __attribute__((__cdecl__)) fread (void*, size_t, size_t, FILE*);
 size_t __attribute__((__cdecl__)) fwrite (const void*, size_t, size_t, FILE*);





 int __attribute__((__cdecl__)) fseek (FILE*, long, int);
 long __attribute__((__cdecl__)) ftell (FILE*);
 void __attribute__((__cdecl__)) rewind (FILE*);
# 330 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
typedef long long fpos_t;




 int __attribute__((__cdecl__)) fgetpos (FILE*, fpos_t*);
 int __attribute__((__cdecl__)) fsetpos (FILE*, const fpos_t*);





 int __attribute__((__cdecl__)) feof (FILE*);
 int __attribute__((__cdecl__)) ferror (FILE*);
# 355 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
 void __attribute__((__cdecl__)) clearerr (FILE*);
 void __attribute__((__cdecl__)) perror (const char*);






 FILE* __attribute__((__cdecl__)) _popen (const char*, const char*);
 int __attribute__((__cdecl__)) _pclose (FILE*);


 FILE* __attribute__((__cdecl__)) popen (const char*, const char*);
 int __attribute__((__cdecl__)) pclose (FILE*);





 int __attribute__((__cdecl__)) _flushall (void);
 int __attribute__((__cdecl__)) _fgetchar (void);
 int __attribute__((__cdecl__)) _fputchar (int);
 FILE* __attribute__((__cdecl__)) _fdopen (int, const char*);
 int __attribute__((__cdecl__)) _fileno (FILE*);
 int __attribute__((__cdecl__)) _fcloseall(void);
 FILE* __attribute__((__cdecl__)) _fsopen(const char*, const char*, int);

 int __attribute__((__cdecl__)) _getmaxstdio(void);
 int __attribute__((__cdecl__)) _setmaxstdio(int);



 int __attribute__((__cdecl__)) fgetchar (void);
 int __attribute__((__cdecl__)) fputchar (int);
 FILE* __attribute__((__cdecl__)) fdopen (int, const char*);
 int __attribute__((__cdecl__)) fileno (FILE*);
# 399 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/sys/types.h" 1 3
# 21 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/sys/types.h" 3
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 1 3 4
# 151 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 2 3
# 22 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/sys/types.h" 2 3





typedef long time_t;




typedef long long __time64_t;





typedef long _off_t;


typedef _off_t off_t;







typedef unsigned int _dev_t;





typedef _dev_t dev_t;






typedef short _ino_t;


typedef _ino_t ino_t;






typedef int _pid_t;


typedef _pid_t pid_t;






typedef unsigned short _mode_t;


typedef _mode_t mode_t;






typedef int _sigset_t;


typedef _sigset_t sigset_t;





typedef long _ssize_t;


typedef _ssize_t ssize_t;





typedef long long fpos64_t;




typedef long long off64_t;
# 400 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 2 3
extern __inline__ FILE* __attribute__((__cdecl__)) fopen64 (const char* filename, const char* mode)
{
  return fopen (filename, mode);
}

int __attribute__((__cdecl__)) fseeko64 (FILE*, off64_t, int);






extern __inline__ off64_t __attribute__((__cdecl__)) ftello64 (FILE * stream)
{
  fpos_t pos;
  if (fgetpos(stream, &pos))
    return -1LL;
  else
   return ((off64_t) pos);
}
# 428 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
 int __attribute__((__cdecl__)) fwprintf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) wprintf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) swprintf (wchar_t*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) _snwprintf (wchar_t*, size_t, const wchar_t*, ...);
 int __attribute__((__cdecl__)) vfwprintf (FILE*, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) vwprintf (const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) vswprintf (wchar_t*, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) _vsnwprintf (wchar_t*, size_t, const wchar_t*, __gnuc_va_list);
 int __attribute__((__cdecl__)) fwscanf (FILE*, const wchar_t*, ...);
 int __attribute__((__cdecl__)) wscanf (const wchar_t*, ...);
 int __attribute__((__cdecl__)) swscanf (const wchar_t*, const wchar_t*, ...);
 wint_t __attribute__((__cdecl__)) fgetwc (FILE*);
 wint_t __attribute__((__cdecl__)) fputwc (wchar_t, FILE*);
 wint_t __attribute__((__cdecl__)) ungetwc (wchar_t, FILE*);


 wchar_t* __attribute__((__cdecl__)) fgetws (wchar_t*, int, FILE*);
 int __attribute__((__cdecl__)) fputws (const wchar_t*, FILE*);
 wint_t __attribute__((__cdecl__)) getwc (FILE*);
 wint_t __attribute__((__cdecl__)) getwchar (void);
 wchar_t* __attribute__((__cdecl__)) _getws (wchar_t*);
 wint_t __attribute__((__cdecl__)) putwc (wint_t, FILE*);
 int __attribute__((__cdecl__)) _putws (const wchar_t*);
 wint_t __attribute__((__cdecl__)) putwchar (wint_t);
 FILE* __attribute__((__cdecl__)) _wfdopen(int, wchar_t *);
 FILE* __attribute__((__cdecl__)) _wfopen (const wchar_t*, const wchar_t*);
 FILE* __attribute__((__cdecl__)) _wfreopen (const wchar_t*, const wchar_t*, FILE*);
 FILE* __attribute__((__cdecl__)) _wfsopen (const wchar_t*, const wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) _wtmpnam (wchar_t*);
 wchar_t* __attribute__((__cdecl__)) _wtempnam (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) _wrename (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) _wremove (const wchar_t*);
 void __attribute__((__cdecl__)) _wperror (const wchar_t*);
 FILE* __attribute__((__cdecl__)) _wpopen (const wchar_t*, const wchar_t*);



int __attribute__((__cdecl__)) snwprintf (wchar_t* s, size_t n, const wchar_t* format, ...);
extern __inline__ int __attribute__((__cdecl__))
vsnwprintf (wchar_t* s, size_t n, const wchar_t* format, __gnuc_va_list arg)
  { return _vsnwprintf ( s, n, format, arg);}
int __attribute__((__cdecl__)) vwscanf (const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) vfwscanf (FILE * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
int __attribute__((__cdecl__)) vswscanf (const wchar_t * __restrict__,
         const wchar_t * __restrict__, __gnuc_va_list);
# 482 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdio.h" 3
 FILE* __attribute__((__cdecl__)) wpopen (const wchar_t*, const wchar_t*);






 wint_t __attribute__((__cdecl__)) _fgetwchar (void);
 wint_t __attribute__((__cdecl__)) _fputwchar (wint_t);
 int __attribute__((__cdecl__)) _getw (FILE*);
 int __attribute__((__cdecl__)) _putw (int, FILE*);


 wint_t __attribute__((__cdecl__)) fgetwchar (void);
 wint_t __attribute__((__cdecl__)) fputwchar (wint_t);
 int __attribute__((__cdecl__)) getw (FILE*);
 int __attribute__((__cdecl__)) putw (int, FILE*);
# 9 "gr2D.c" 2
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 1 3
# 16 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
       
# 17 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
# 118 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
extern __attribute__ ((dllimport)) double _HUGE;
# 128 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
struct _exception
{
 int type;
 char *name;
 double arg1;
 double arg2;
 double retval;
};

 double __attribute__((__cdecl__)) sin (double);
 double __attribute__((__cdecl__)) cos (double);
 double __attribute__((__cdecl__)) tan (double);
 double __attribute__((__cdecl__)) sinh (double);
 double __attribute__((__cdecl__)) cosh (double);
 double __attribute__((__cdecl__)) tanh (double);
 double __attribute__((__cdecl__)) asin (double);
 double __attribute__((__cdecl__)) acos (double);
 double __attribute__((__cdecl__)) atan (double);
 double __attribute__((__cdecl__)) atan2 (double, double);
 double __attribute__((__cdecl__)) exp (double);
 double __attribute__((__cdecl__)) log (double);
 double __attribute__((__cdecl__)) log10 (double);
 double __attribute__((__cdecl__)) pow (double, double);
 double __attribute__((__cdecl__)) sqrt (double);
 double __attribute__((__cdecl__)) ceil (double);
 double __attribute__((__cdecl__)) floor (double);
 double __attribute__((__cdecl__)) fabs (double);
 double __attribute__((__cdecl__)) ldexp (double, int);
 double __attribute__((__cdecl__)) frexp (double, int*);
 double __attribute__((__cdecl__)) modf (double, double*);
 double __attribute__((__cdecl__)) fmod (double, double);
# 204 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
struct _complex
{
 double x;
 double y;
};

 double __attribute__((__cdecl__)) _cabs (struct _complex);

 double __attribute__((__cdecl__)) _hypot (double, double);
 double __attribute__((__cdecl__)) _j0 (double);
 double __attribute__((__cdecl__)) _j1 (double);
 double __attribute__((__cdecl__)) _jn (int, double);
 double __attribute__((__cdecl__)) _y0 (double);
 double __attribute__((__cdecl__)) _y1 (double);
 double __attribute__((__cdecl__)) _yn (int, double);
 int __attribute__((__cdecl__)) _matherr (struct _exception *);
# 228 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
 double __attribute__((__cdecl__)) _chgsign (double);
 double __attribute__((__cdecl__)) _copysign (double, double);
 double __attribute__((__cdecl__)) _logb (double);
 double __attribute__((__cdecl__)) _nextafter (double, double);
 double __attribute__((__cdecl__)) _scalb (double, long);

 int __attribute__((__cdecl__)) _finite (double);
 int __attribute__((__cdecl__)) _fpclass (double);
 int __attribute__((__cdecl__)) _isnan (double);
# 248 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
 double __attribute__((__cdecl__)) j0 (double);
 double __attribute__((__cdecl__)) j1 (double);
 double __attribute__((__cdecl__)) jn (int, double);
 double __attribute__((__cdecl__)) y0 (double);
 double __attribute__((__cdecl__)) y1 (double);
 double __attribute__((__cdecl__)) yn (int, double);

 double __attribute__((__cdecl__)) chgsign (double);
 double __attribute__((__cdecl__)) scalb (double, long);
 int __attribute__((__cdecl__)) finite (double);
 int __attribute__((__cdecl__)) fpclass (double);
# 314 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
extern int __attribute__((__cdecl__)) __fpclassifyf (float);
extern int __attribute__((__cdecl__)) __fpclassify (double);

extern __inline__ int __attribute__((__cdecl__)) __fpclassifyl (long double x){
  unsigned short sw;
  __asm__ ("fxam; fstsw %%ax;" : "=a" (sw): "t" (x));
  return sw & (0x0100 | 0x0400 | 0x4000 );
}
# 337 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
extern __inline__ int __attribute__((__cdecl__)) __isnan (double _x)
{
  unsigned short sw;
  __asm__ ("fxam;"
    "fstsw %%ax": "=a" (sw) : "t" (_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000)))
    == 0x0100;
}

extern __inline__ int __attribute__((__cdecl__)) __isnanf (float _x)
{
  unsigned short sw;
  __asm__ ("fxam;"
     "fstsw %%ax": "=a" (sw) : "t" (_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000)))
    == 0x0100;
}

extern __inline__ int __attribute__((__cdecl__)) __isnanl (long double _x)
{
  unsigned short sw;
  __asm__ ("fxam;"
     "fstsw %%ax": "=a" (sw) : "t" (_x));
  return (sw & (0x0100 | 0x0400 | (0x0100 | 0x0400) | 0x4000 | (0x0400 | 0x4000)))
    == 0x0100;
}
# 373 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
extern __inline__ int __attribute__((__cdecl__)) __signbit (double x) {
  unsigned short stw;
  __asm__ ( "fxam; fstsw %%ax;": "=a" (stw) : "t" (x));
  return stw & 0x0200;
}

extern __inline__ int __attribute__((__cdecl__)) __signbitf (float x) {
  unsigned short stw;
  __asm__ ("fxam; fstsw %%ax;": "=a" (stw) : "t" (x));
  return stw & 0x0200;
}

extern __inline__ int __attribute__((__cdecl__)) __signbitl (long double x) {
  unsigned short stw;
  __asm__ ("fxam; fstsw %%ax;": "=a" (stw) : "t" (x));
  return stw & 0x0200;
}






extern float __attribute__((__cdecl__)) sinf (float);
extern long double __attribute__((__cdecl__)) sinl (long double);

extern float __attribute__((__cdecl__)) cosf (float);
extern long double __attribute__((__cdecl__)) cosl (long double);

extern float __attribute__((__cdecl__)) tanf (float);
extern long double __attribute__((__cdecl__)) tanl (long double);

extern float __attribute__((__cdecl__)) asinf (float);
extern long double __attribute__((__cdecl__)) asinl (long double);

extern float __attribute__((__cdecl__)) acosf (float);
extern long double __attribute__((__cdecl__)) acosl (long double);

extern float __attribute__((__cdecl__)) atanf (float);
extern long double __attribute__((__cdecl__)) atanl (long double);

extern float __attribute__((__cdecl__)) atan2f (float, float);
extern long double __attribute__((__cdecl__)) atan2l (long double, long double);


extern __inline__ float __attribute__((__cdecl__)) sinhf (float x)
  {return (float) sinh (x);}
extern long double __attribute__((__cdecl__)) sinhl (long double);

extern __inline__ float __attribute__((__cdecl__)) coshf (float x)
  {return (float) cosh (x);}
extern long double __attribute__((__cdecl__)) coshl (long double);

extern __inline__ float __attribute__((__cdecl__)) tanhf (float x)
  {return (float) tanh (x);}
extern long double __attribute__((__cdecl__)) tanhl (long double);



extern double __attribute__((__cdecl__)) acosh (double);
extern float __attribute__((__cdecl__)) acoshf (float);
extern long double __attribute__((__cdecl__)) acoshl (long double);


extern double __attribute__((__cdecl__)) asinh (double);
extern float __attribute__((__cdecl__)) asinhf (float);
extern long double __attribute__((__cdecl__)) asinhl (long double);


extern double __attribute__((__cdecl__)) atanh (double);
extern float __attribute__((__cdecl__)) atanf (float);
extern long double __attribute__((__cdecl__)) atanhl (long double);



extern __inline__ float __attribute__((__cdecl__)) expf (float x)
  {return (float) exp (x);}
extern long double __attribute__((__cdecl__)) expl (long double);


extern double __attribute__((__cdecl__)) exp2(double);
extern float __attribute__((__cdecl__)) exp2f(float);
extern long double __attribute__((__cdecl__)) exp2l(long double);




extern __inline__ float __attribute__((__cdecl__)) frexpf (float x, int* expn)
  {return (float) frexp (x, expn);}
extern long double __attribute__((__cdecl__)) frexpl (long double, int*);




extern int __attribute__((__cdecl__)) ilogb (double);
extern int __attribute__((__cdecl__)) ilogbf (float);
extern int __attribute__((__cdecl__)) ilogbl (long double);


extern __inline__ float __attribute__((__cdecl__)) ldexpf (float x, int expn)
  {return (float) ldexp (x, expn);}
extern long double __attribute__((__cdecl__)) ldexpl (long double, int);


extern float __attribute__((__cdecl__)) logf (float);
extern long double __attribute__((__cdecl__)) logl (long double);


extern float __attribute__((__cdecl__)) log10f (float);
extern long double __attribute__((__cdecl__)) log10l (long double);


extern double __attribute__((__cdecl__)) log1p(double);
extern float __attribute__((__cdecl__)) log1pf(float);
extern long double __attribute__((__cdecl__)) log1pl(long double);


extern double __attribute__((__cdecl__)) log2 (double);
extern float __attribute__((__cdecl__)) log2f (float);
extern long double __attribute__((__cdecl__)) log2l (long double);


extern double __attribute__((__cdecl__)) logb (double);
extern float __attribute__((__cdecl__)) logbf (float);
extern long double __attribute__((__cdecl__)) logbl (long double);

extern __inline__ double __attribute__((__cdecl__)) logb (double x)
{
  double res;
  __asm__ ("fxtract\n\t"
       "fstp	%%st" : "=t" (res) : "0" (x));
  return res;
}

extern __inline__ float __attribute__((__cdecl__)) logbf (float x)
{
  float res;
  __asm__ ("fxtract\n\t"
       "fstp	%%st" : "=t" (res) : "0" (x));
  return res;
}

extern __inline__ long double __attribute__((__cdecl__)) logbl (long double x)
{
  long double res;
  __asm__ ("fxtract\n\t"
       "fstp	%%st" : "=t" (res) : "0" (x));
  return res;
}


extern float __attribute__((__cdecl__)) modff (float, float*);
extern long double __attribute__((__cdecl__)) modfl (long double, long double*);


extern double __attribute__((__cdecl__)) scalbn (double, int);
extern float __attribute__((__cdecl__)) scalbnf (float, int);
extern long double __attribute__((__cdecl__)) scalbnl (long double, int);

extern double __attribute__((__cdecl__)) scalbln (double, long);
extern float __attribute__((__cdecl__)) scalblnf (float, long);
extern long double __attribute__((__cdecl__)) scalblnl (long double, long);



extern double __attribute__((__cdecl__)) cbrt (double);
extern float __attribute__((__cdecl__)) cbrtf (float);
extern long double __attribute__((__cdecl__)) cbrtl (long double);


extern float __attribute__((__cdecl__)) fabsf (float x);
extern long double __attribute__((__cdecl__)) fabsl (long double x);


extern double __attribute__((__cdecl__)) hypot (double, double);
extern __inline__ float __attribute__((__cdecl__)) hypotf (float x, float y)
  { return (float) hypot (x, y);}
extern long double __attribute__((__cdecl__)) hypotl (long double, long double);


extern __inline__ float __attribute__((__cdecl__)) powf (float x, float y)
  {return (float) pow (x, y);}
extern long double __attribute__((__cdecl__)) powl (long double, long double);


extern float __attribute__((__cdecl__)) sqrtf (float);
extern long double __attribute__((__cdecl__)) sqrtl (long double);


extern double __attribute__((__cdecl__)) erf (double);
extern float __attribute__((__cdecl__)) erff (float);





extern double __attribute__((__cdecl__)) erfc (double);
extern float __attribute__((__cdecl__)) erfcf (float);





extern double __attribute__((__cdecl__)) lgamma (double);
extern float __attribute__((__cdecl__)) lgammaf (float);
extern long double __attribute__((__cdecl__)) lgammal (long double);


extern double __attribute__((__cdecl__)) tgamma (double);
extern float __attribute__((__cdecl__)) tgammaf (float);
extern long double __attribute__((__cdecl__)) tgammal (long double);


extern float __attribute__((__cdecl__)) ceilf (float);
extern long double __attribute__((__cdecl__)) ceill (long double);


extern float __attribute__((__cdecl__)) floorf (float);
extern long double __attribute__((__cdecl__)) floorl (long double);


extern double __attribute__((__cdecl__)) nearbyint ( double);
extern float __attribute__((__cdecl__)) nearbyintf (float);
extern long double __attribute__((__cdecl__)) nearbyintl (long double);



extern __inline__ double __attribute__((__cdecl__)) rint (double x)
{
  double retval;
  __asm__ ("frndint;": "=t" (retval) : "0" (x));
  return retval;
}

extern __inline__ float __attribute__((__cdecl__)) rintf (float x)
{
  float retval;
  __asm__ ("frndint;" : "=t" (retval) : "0" (x) );
  return retval;
}

extern __inline__ long double __attribute__((__cdecl__)) rintl (long double x)
{
  long double retval;
  __asm__ ("frndint;" : "=t" (retval) : "0" (x) );
  return retval;
}


extern __inline__ long __attribute__((__cdecl__)) lrint (double x)
{
  long retval;
  __asm__ __volatile__ ("fistpl %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}

extern __inline__ long __attribute__((__cdecl__)) lrintf (float x)
{
  long retval;
  __asm__ __volatile__ ("fistpl %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}

extern __inline__ long __attribute__((__cdecl__)) lrintl (long double x)
{
  long retval;
  __asm__ __volatile__ ("fistpl %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}

extern __inline__ long long __attribute__((__cdecl__)) llrint (double x)
{
  long long retval;
  __asm__ __volatile__ ("fistpll %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}

extern __inline__ long long __attribute__((__cdecl__)) llrintf (float x)
{
  long long retval;
  __asm__ __volatile__ ("fistpll %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}

extern __inline__ long long __attribute__((__cdecl__)) llrintl (long double x)
{
  long long retval;
  __asm__ __volatile__ ("fistpll %0" : "=m" (retval) : "t" (x) : "st"); return retval;


}



extern double __attribute__((__cdecl__)) round (double);
extern float __attribute__((__cdecl__)) roundf (float);
extern long double __attribute__((__cdecl__)) roundl (long double);


extern long __attribute__((__cdecl__)) lround (double);
extern long __attribute__((__cdecl__)) lroundf (float);
extern long __attribute__((__cdecl__)) lroundl (long double);

extern long long __attribute__((__cdecl__)) llround (double);
extern long long __attribute__((__cdecl__)) llroundf (float);
extern long long __attribute__((__cdecl__)) llroundl (long double);



extern double __attribute__((__cdecl__)) trunc (double);
extern float __attribute__((__cdecl__)) truncf (float);
extern long double __attribute__((__cdecl__)) truncl (long double);


extern float __attribute__((__cdecl__)) fmodf (float, float);
extern long double __attribute__((__cdecl__)) fmodl (long double, long double);


extern double __attribute__((__cdecl__)) remainder (double, double);
extern float __attribute__((__cdecl__)) remainderf (float, float);
extern long double __attribute__((__cdecl__)) remainderl (long double, long double);


extern double __attribute__((__cdecl__)) remquo(double, double, int *);
extern float __attribute__((__cdecl__)) remquof(float, float, int *);
extern long double __attribute__((__cdecl__)) remquol(long double, long double, int *);


extern double __attribute__((__cdecl__)) copysign (double, double);
extern float __attribute__((__cdecl__)) copysignf (float, float);
extern long double __attribute__((__cdecl__)) copysignl (long double, long double);


extern double __attribute__((__cdecl__)) nan(const char *tagp);
extern float __attribute__((__cdecl__)) nanf(const char *tagp);
extern long double __attribute__((__cdecl__)) nanl(const char *tagp);
# 722 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/math.h" 3
extern double __attribute__((__cdecl__)) nextafter (double, double);
extern float __attribute__((__cdecl__)) nextafterf (float, float);







extern double __attribute__((__cdecl__)) fdim (double x, double y);
extern float __attribute__((__cdecl__)) fdimf (float x, float y);
extern long double __attribute__((__cdecl__)) fdiml (long double x, long double y);







extern double __attribute__((__cdecl__)) fmax (double, double);
extern float __attribute__((__cdecl__)) fmaxf (float, float);
extern long double __attribute__((__cdecl__)) fmaxl (long double, long double);


extern double __attribute__((__cdecl__)) fmin (double, double);
extern float __attribute__((__cdecl__)) fminf (float, float);
extern long double __attribute__((__cdecl__)) fminl (long double, long double);



extern double __attribute__((__cdecl__)) fma (double, double, double);
extern float __attribute__((__cdecl__)) fmaf (float, float, float);
extern long double __attribute__((__cdecl__)) fmal (long double, long double, long double);
# 10 "gr2D.c" 2
# 1 "../../dist/libutl.h" 1
# 13 "../../dist/libutl.h"
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 1 3
# 22 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 1 3 4
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 2 3
# 23 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 2 3
# 72 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
extern int _argc;
extern char** _argv;




extern int* __attribute__((__cdecl__)) __p___argc(void);
extern char*** __attribute__((__cdecl__)) __p___argv(void);
extern wchar_t*** __attribute__((__cdecl__)) __p___wargv(void);
# 113 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
   extern __attribute__ ((dllimport)) int __mb_cur_max;
# 138 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
 int* __attribute__((__cdecl__)) _errno(void);


 int* __attribute__((__cdecl__)) __doserrno(void);
# 150 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
  extern char *** __attribute__((__cdecl__)) __p__environ(void);
  extern wchar_t *** __attribute__((__cdecl__)) __p__wenviron(void);
# 173 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
  extern __attribute__ ((dllimport)) int _sys_nerr;
# 197 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
extern __attribute__ ((dllimport)) char* _sys_errlist[];
# 210 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
extern unsigned __attribute__((__cdecl__)) int* __p__osver(void);
extern unsigned __attribute__((__cdecl__)) int* __p__winver(void);
extern unsigned __attribute__((__cdecl__)) int* __p__winmajor(void);
extern unsigned __attribute__((__cdecl__)) int* __p__winminor(void);







extern __attribute__ ((dllimport)) unsigned int _osver;
extern __attribute__ ((dllimport)) unsigned int _winver;
extern __attribute__ ((dllimport)) unsigned int _winmajor;
extern __attribute__ ((dllimport)) unsigned int _winminor;
# 261 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
 char** __attribute__((__cdecl__)) __p__pgmptr(void);

 wchar_t** __attribute__((__cdecl__)) __p__wpgmptr(void);
# 294 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
extern __attribute__ ((dllimport)) int _fmode;
# 304 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
 double __attribute__((__cdecl__)) atof (const char*);
 int __attribute__((__cdecl__)) atoi (const char*);
 long __attribute__((__cdecl__)) atol (const char*);

 int __attribute__((__cdecl__)) _wtoi (const wchar_t *);
 long __attribute__((__cdecl__)) _wtol (const wchar_t *);

 double __attribute__((__cdecl__)) strtod (const char*, char**);

extern __inline__ float __attribute__((__cdecl__)) strtof (const char *nptr, char **endptr)
  { return (strtod (nptr, endptr));}
long double __attribute__((__cdecl__)) strtold (const char * __restrict__, char ** __restrict__);


 long __attribute__((__cdecl__)) strtol (const char*, char**, int);
 unsigned long __attribute__((__cdecl__)) strtoul (const char*, char**, int);



 double __attribute__((__cdecl__)) wcstod (const wchar_t*, wchar_t**);

extern __inline__ float __attribute__((__cdecl__)) wcstof( const wchar_t *nptr, wchar_t **endptr)
{ return (wcstod(nptr, endptr)); }
long double __attribute__((__cdecl__)) wcstold (const wchar_t * __restrict__, wchar_t ** __restrict__);


 long __attribute__((__cdecl__)) wcstol (const wchar_t*, wchar_t**, int);
 unsigned long __attribute__((__cdecl__)) wcstoul (const wchar_t*, wchar_t**, int);



 size_t __attribute__((__cdecl__)) wcstombs (char*, const wchar_t*, size_t);
 int __attribute__((__cdecl__)) wctomb (char*, wchar_t);

 int __attribute__((__cdecl__)) mblen (const char*, size_t);
 size_t __attribute__((__cdecl__)) mbstowcs (wchar_t*, const char*, size_t);
 int __attribute__((__cdecl__)) mbtowc (wchar_t*, const char*, size_t);

 int __attribute__((__cdecl__)) rand (void);
 void __attribute__((__cdecl__)) srand (unsigned int);

 void* __attribute__((__cdecl__)) calloc (size_t, size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) malloc (size_t) __attribute__ ((__malloc__));
 void* __attribute__((__cdecl__)) realloc (void*, size_t);
 void __attribute__((__cdecl__)) free (void*);

 void __attribute__((__cdecl__)) abort (void) __attribute__ ((__noreturn__));
 void __attribute__((__cdecl__)) exit (int) __attribute__ ((__noreturn__));


int __attribute__((__cdecl__)) atexit (void (*)(void));

 int __attribute__((__cdecl__)) system (const char*);
 char* __attribute__((__cdecl__)) getenv (const char*);


 void* __attribute__((__cdecl__)) bsearch (const void*, const void*, size_t, size_t,
     int (*)(const void*, const void*));
 void __attribute__((__cdecl__)) qsort (void*, size_t, size_t,
     int (*)(const void*, const void*));

 int __attribute__((__cdecl__)) abs (int) __attribute__ ((__const__));
 long __attribute__((__cdecl__)) labs (long) __attribute__ ((__const__));
# 376 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

 div_t __attribute__((__cdecl__)) div (int, int) __attribute__ ((__const__));
 ldiv_t __attribute__((__cdecl__)) ldiv (long, long) __attribute__ ((__const__));







 void __attribute__((__cdecl__)) _beep (unsigned int, unsigned int);
 void __attribute__((__cdecl__)) _seterrormode (int);
 void __attribute__((__cdecl__)) _sleep (unsigned long);

 void __attribute__((__cdecl__)) _exit (int) __attribute__ ((__noreturn__));



typedef int (* _onexit_t)(void);
_onexit_t __attribute__((__cdecl__)) _onexit( _onexit_t );

 int __attribute__((__cdecl__)) _putenv (const char*);
 void __attribute__((__cdecl__)) _searchenv (const char*, const char*, char*);


 char* __attribute__((__cdecl__)) _ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) _fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) _gcvt (double, int, char*);

 void __attribute__((__cdecl__)) _makepath (char*, const char*, const char*, const char*, const char*);
 void __attribute__((__cdecl__)) _splitpath (const char*, char*, char*, char*, char*);
 char* __attribute__((__cdecl__)) _fullpath (char*, const char*, size_t);

 char* __attribute__((__cdecl__)) _itoa (int, char*, int);
 char* __attribute__((__cdecl__)) _ltoa (long, char*, int);
 char* __attribute__((__cdecl__)) _ultoa(unsigned long, char*, int);
 wchar_t* __attribute__((__cdecl__)) _itow (int, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) _ltow (long, wchar_t*, int);
 wchar_t* __attribute__((__cdecl__)) _ultow (unsigned long, wchar_t*, int);


 long long __attribute__((__cdecl__)) _atoi64(const char *);
 char* __attribute__((__cdecl__)) _i64toa(long long, char *, int);
 char* __attribute__((__cdecl__)) _ui64toa(unsigned long long, char *, int);
 long long __attribute__((__cdecl__)) _wtoi64(const wchar_t *);
 wchar_t* __attribute__((__cdecl__)) _i64tow(long long, wchar_t *, int);
 wchar_t* __attribute__((__cdecl__)) _ui64tow(unsigned long long, wchar_t *, int);

 wchar_t* __attribute__((__cdecl__)) _wgetenv(const wchar_t*);
 int __attribute__((__cdecl__)) _wputenv(const wchar_t*);
 void __attribute__((__cdecl__)) _wsearchenv(const wchar_t*, const wchar_t*, wchar_t*);
 void __attribute__((__cdecl__)) _wmakepath(wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
 void __attribute__((__cdecl__)) _wsplitpath (const wchar_t*, wchar_t*, wchar_t*, wchar_t*, wchar_t*);
 wchar_t* __attribute__((__cdecl__)) _wfullpath (wchar_t*, const wchar_t*, size_t);

 unsigned int __attribute__((__cdecl__)) _rotl(unsigned int, int) __attribute__ ((__const__));
 unsigned int __attribute__((__cdecl__)) _rotr(unsigned int, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) _lrotl(unsigned long, int) __attribute__ ((__const__));
 unsigned long __attribute__((__cdecl__)) _lrotr(unsigned long, int) __attribute__ ((__const__));




 int __attribute__((__cdecl__)) putenv (const char*);
 void __attribute__((__cdecl__)) searchenv (const char*, const char*, char*);

 char* __attribute__((__cdecl__)) itoa (int, char*, int);
 char* __attribute__((__cdecl__)) ltoa (long, char*, int);


 char* __attribute__((__cdecl__)) ecvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) fcvt (double, int, int*, int*);
 char* __attribute__((__cdecl__)) gcvt (double, int, char*);
# 461 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdlib.h" 3
void __attribute__((__cdecl__)) _Exit(int) __attribute__ ((__noreturn__));

extern __inline__ void __attribute__((__cdecl__)) _Exit(int status)
 { _exit(status); }


typedef struct { long long quot, rem; } lldiv_t;

lldiv_t __attribute__((__cdecl__)) lldiv (long long, long long) __attribute__ ((__const__));

extern __inline__ long long __attribute__((__cdecl__)) llabs(long long _j)
  {return (_j >= 0 ? _j : -_j);}

long long __attribute__((__cdecl__)) strtoll (const char* __restrict__, char** __restrict, int);
unsigned long long __attribute__((__cdecl__)) strtoull (const char* __restrict__, char** __restrict__, int);


long long __attribute__((__cdecl__)) atoll (const char *);


long long __attribute__((__cdecl__)) wtoll (const wchar_t *);
char* __attribute__((__cdecl__)) lltoa (long long, char *, int);
char* __attribute__((__cdecl__)) ulltoa (unsigned long long , char *, int);
wchar_t* __attribute__((__cdecl__)) lltow (long long, wchar_t *, int);
wchar_t* __attribute__((__cdecl__)) ulltow (unsigned long long, wchar_t *, int);


extern __inline__ long long __attribute__((__cdecl__)) atoll (const char * _c)
 { return _atoi64 (_c); }
extern __inline__ char* __attribute__((__cdecl__)) lltoa (long long _n, char * _c, int _i)
 { return _i64toa (_n, _c, _i); }
extern __inline__ char* __attribute__((__cdecl__)) ulltoa (unsigned long long _n, char * _c, int _i)
 { return _ui64toa (_n, _c, _i); }
extern __inline__ long long __attribute__((__cdecl__)) wtoll (const wchar_t * _w)
  { return _wtoi64 (_w); }
extern __inline__ wchar_t* __attribute__((__cdecl__)) lltow (long long _n, wchar_t * _w, int _i)
 { return _i64tow (_n, _w, _i); }
extern __inline__ wchar_t* __attribute__((__cdecl__)) ulltow (unsigned long long _n, wchar_t * _w, int _i)
 { return _ui64tow (_n, _w, _i); }
# 14 "../../dist/libutl.h" 2

# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 1 3
# 24 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 1 3 4
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 2 3
# 25 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 2 3
# 36 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
 void* __attribute__((__cdecl__)) memchr (const void*, int, size_t) __attribute__ ((__pure__));
 int __attribute__((__cdecl__)) memcmp (const void*, const void*, size_t) __attribute__ ((__pure__));
 void* __attribute__((__cdecl__)) memcpy (void*, const void*, size_t);
 void* __attribute__((__cdecl__)) memmove (void*, const void*, size_t);
 void* __attribute__((__cdecl__)) memset (void*, int, size_t);
 char* __attribute__((__cdecl__)) strcat (char*, const char*);
 char* __attribute__((__cdecl__)) strchr (const char*, int) __attribute__ ((__pure__));
 int __attribute__((__cdecl__)) strcmp (const char*, const char*) __attribute__ ((__pure__));
 int __attribute__((__cdecl__)) strcoll (const char*, const char*);
 char* __attribute__((__cdecl__)) strcpy (char*, const char*);
 size_t __attribute__((__cdecl__)) strcspn (const char*, const char*) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strerror (int);

 size_t __attribute__((__cdecl__)) strlen (const char*) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strncat (char*, const char*, size_t);
 int __attribute__((__cdecl__)) strncmp (const char*, const char*, size_t) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strncpy (char*, const char*, size_t);
 char* __attribute__((__cdecl__)) strpbrk (const char*, const char*) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strrchr (const char*, int) __attribute__ ((__pure__));
 size_t __attribute__((__cdecl__)) strspn (const char*, const char*) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strstr (const char*, const char*) __attribute__ ((__pure__));
 char* __attribute__((__cdecl__)) strtok (char*, const char*);
 size_t __attribute__((__cdecl__)) strxfrm (char*, const char*, size_t);





 char* __attribute__((__cdecl__)) _strerror (const char *);
 void* __attribute__((__cdecl__)) _memccpy (void*, const void*, int, size_t);
 int __attribute__((__cdecl__)) _memicmp (const void*, const void*, size_t);
 char* __attribute__((__cdecl__)) _strdup (const char*) __attribute__ ((__malloc__));
 int __attribute__((__cdecl__)) _strcmpi (const char*, const char*);
 int __attribute__((__cdecl__)) _stricmp (const char*, const char*);
 int __attribute__((__cdecl__)) _stricoll (const char*, const char*);
 char* __attribute__((__cdecl__)) _strlwr (char*);
 int __attribute__((__cdecl__)) _strnicmp (const char*, const char*, size_t);
 char* __attribute__((__cdecl__)) _strnset (char*, int, size_t);
 char* __attribute__((__cdecl__)) _strrev (char*);
 char* __attribute__((__cdecl__)) _strset (char*, int);
 char* __attribute__((__cdecl__)) _strupr (char*);
 void __attribute__((__cdecl__)) _swab (const char*, char*, size_t);


 int __attribute__((__cdecl__)) _strncoll(const char*, const char*, size_t);
 int __attribute__((__cdecl__)) _strnicoll(const char*, const char*, size_t);
# 90 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
 void* __attribute__((__cdecl__)) memccpy (void*, const void*, int, size_t);
 int __attribute__((__cdecl__)) memicmp (const void*, const void*, size_t);
 char* __attribute__((__cdecl__)) strdup (const char*) __attribute__ ((__malloc__));
 int __attribute__((__cdecl__)) strcmpi (const char*, const char*);
 int __attribute__((__cdecl__)) stricmp (const char*, const char*);
extern __inline__ int __attribute__((__cdecl__))
strcasecmp (const char * __sz1, const char * __sz2)
  {return _stricmp (__sz1, __sz2);}
 int __attribute__((__cdecl__)) stricoll (const char*, const char*);
 char* __attribute__((__cdecl__)) strlwr (char*);
 int __attribute__((__cdecl__)) strnicmp (const char*, const char*, size_t);
extern __inline__ int __attribute__((__cdecl__))
strncasecmp (const char * __sz1, const char * __sz2, size_t __sizeMaxCompare)
  {return _strnicmp (__sz1, __sz2, __sizeMaxCompare);}
 char* __attribute__((__cdecl__)) strnset (char*, int, size_t);
 char* __attribute__((__cdecl__)) strrev (char*);
 char* __attribute__((__cdecl__)) strset (char*, int);
 char* __attribute__((__cdecl__)) strupr (char*);

 void __attribute__((__cdecl__)) swab (const char*, char*, size_t);
# 120 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
 wchar_t* __attribute__((__cdecl__)) wcscat (wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcschr (const wchar_t*, wchar_t);
 int __attribute__((__cdecl__)) wcscmp (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) wcscoll (const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcscpy (wchar_t*, const wchar_t*);
 size_t __attribute__((__cdecl__)) wcscspn (const wchar_t*, const wchar_t*);

 size_t __attribute__((__cdecl__)) wcslen (const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcsncat (wchar_t*, const wchar_t*, size_t);
 int __attribute__((__cdecl__)) wcsncmp(const wchar_t*, const wchar_t*, size_t);
 wchar_t* __attribute__((__cdecl__)) wcsncpy(wchar_t*, const wchar_t*, size_t);
 wchar_t* __attribute__((__cdecl__)) wcspbrk(const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcsrchr(const wchar_t*, wchar_t);
 size_t __attribute__((__cdecl__)) wcsspn(const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcsstr(const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcstok(wchar_t*, const wchar_t*);
 size_t __attribute__((__cdecl__)) wcsxfrm(wchar_t*, const wchar_t*, size_t);
# 146 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
 wchar_t* __attribute__((__cdecl__)) _wcsdup (const wchar_t*);
 int __attribute__((__cdecl__)) _wcsicmp (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) _wcsicoll (const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) _wcslwr (wchar_t*);
 int __attribute__((__cdecl__)) _wcsnicmp (const wchar_t*, const wchar_t*, size_t);
 wchar_t* __attribute__((__cdecl__)) _wcsnset (wchar_t*, wchar_t, size_t);
 wchar_t* __attribute__((__cdecl__)) _wcsrev (wchar_t*);
 wchar_t* __attribute__((__cdecl__)) _wcsset (wchar_t*, wchar_t);
 wchar_t* __attribute__((__cdecl__)) _wcsupr (wchar_t*);


 int __attribute__((__cdecl__)) _wcsncoll(const wchar_t*, const wchar_t*, size_t);
 int __attribute__((__cdecl__)) _wcsnicoll(const wchar_t*, const wchar_t*, size_t);
# 167 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/string.h" 3
int __attribute__((__cdecl__)) wcscmpi (const wchar_t * __ws1, const wchar_t * __ws2);
extern __inline__ int __attribute__((__cdecl__))
wcscmpi (const wchar_t * __ws1, const wchar_t * __ws2)
  {return _wcsicmp (__ws1, __ws2);}
 wchar_t* __attribute__((__cdecl__)) wcsdup (const wchar_t*);
 int __attribute__((__cdecl__)) wcsicmp (const wchar_t*, const wchar_t*);
 int __attribute__((__cdecl__)) wcsicoll (const wchar_t*, const wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcslwr (wchar_t*);
 int __attribute__((__cdecl__)) wcsnicmp (const wchar_t*, const wchar_t*, size_t);
 wchar_t* __attribute__((__cdecl__)) wcsnset (wchar_t*, wchar_t, size_t);
 wchar_t* __attribute__((__cdecl__)) wcsrev (wchar_t*);
 wchar_t* __attribute__((__cdecl__)) wcsset (wchar_t*, wchar_t);
 wchar_t* __attribute__((__cdecl__)) wcsupr (wchar_t*);
# 16 "../../dist/libutl.h" 2
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdarg.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stdarg.h" 1 3 4
# 106 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stdarg.h" 2 3
# 17 "../../dist/libutl.h" 2
# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 1 3





# 1 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/include/stddef.h" 1 3 4
# 7 "C:/mingw/bin/../lib/gcc/mingw32/3.4.2/../../../../include/stddef.h" 2 3
# 18 "../../dist/libutl.h" 2
# 102 "../../dist/libutl.h"
void utlEmptyFun(void);






extern char *utlEmptyString ;
# 142 "../../dist/libutl.h"
extern FILE *utl_stderr ;
# 183 "../../dist/libutl.h"
extern char *utlErrInternal ;
# 806 "../../dist/libutl.h"
typedef size_t pmxMatches[10 +1][2];

typedef pmxMatches *pmxMatches_t;






pmxMatches_t pmxMatchStr(char *text, char *p);
# 824 "../../dist/libutl.h"
int pmxMatched (pmxMatches_t mtc);
pmxMatches_t pmxMatchStr(char *text, char *p);
size_t pmxLen (pmxMatches_t mtc, unsigned char n);
size_t pmxStart (pmxMatches_t mtc, unsigned char n);
size_t pmxEnd (pmxMatches_t mtc, unsigned char n);
# 851 "../../dist/libutl.h"
typedef int (*pmxScanFun_t)(char *txt, pmxMatches_t mtc);
int pmxScanStr(char* text, char *ptrn, pmxScanFun_t f);
# 918 "../../dist/libutl.h"
typedef struct {
  long size;
  long len;
  long cur;
  char chs[16];
} chsBlk;

typedef char *chs_t ;
# 934 "../../dist/libutl.h"
extern chsBlk *chs_blk_;
extern chs_t chs_tmp_;







chs_t chsNew() ;

int chsSeek (chs_t dst, long pos, int whence) ;
size_t chsTell (chs_t dst) ;
int chsEof (chs_t s) ;

chs_t chsSet (chs_t s, long ndx, char c) ;
char chsChrAt (chs_t s, long ndx) ;
int chsGetChr (chs_t s) ;

chs_t chsCpyL (chs_t dst, char *src, long len) ;
chs_t chsCpy (chs_t dst, char *src) ;
chs_t chsDup (char *src);

chs_t chsAddChr (chs_t dst, char c) ;
chs_t chsAddStrL (chs_t dst, char *src, long len) ;
chs_t chsAddStr (chs_t dst, char *src) ;

chs_t chsInsChr (chs_t dst, long ndx, char c) ;
chs_t chsInsStrL (chs_t dst, long ndx, char *src, long len) ;
chs_t chsInsStr (chs_t dst, long ndx, char *src) ;

chs_t chsDel (chs_t dst, long from, long to) ;

chs_t chs_read(chs_t dst, FILE *f, char how, char what);







pmxMatches_t chsMatch(chs_t s, long from, char *pat) ;

typedef char *(*chsSubF_t)(char *mtc, pmxMatches_t cpt);

chs_t chsSubStr(chs_t s, size_t pos, char *pat, char *rpl) ;
chs_t chsSubFun(chs_t s, size_t pos, char *pat, chsSubF_t f);
# 1030 "../../dist/libutl.h"
typedef union {
  void *p;
  char *s;
  long n;
  float f;
} val_u;
# 1048 "../../dist/libutl.h"
typedef struct {
  unsigned char flg[4];
  val_u val;
  val_u key;
  val_u aux;
} tbl_slot_t;






typedef struct {
  long count;
  long size;
  long cur;
  tbl_slot_t slot[1];
} tbl_ht_t;





typedef tbl_ht_t *tbl_t;

tbl_t tbl_new(long nslots);


val_u tbl_get(tbl_t tb, char tk, long nkey, void *pkey,
                        char tv, long ndef, void *pdef);
# 1099 "../../dist/libutl.h"
long tblNext (tbl_t tb, long start);
# 1114 "../../dist/libutl.h"
extern long tbl_i;
# 1131 "../../dist/libutl.h"
long tbl_find(tbl_t tb, char tk, long nkey, void *pkey);






tbl_t tbl_set(tbl_t tb, char tk, long nkey, void *pkey,
                        char tv, long nval, void *pval);
# 1161 "../../dist/libutl.h"
tbl_t tbl_free(tbl_t tb,char wipe);


tbl_t tbl_del(tbl_t tb, char tk, long nkey, void *pkey);






tbl_t tblMaxSlot(tbl_t tb, long nslots);






typedef struct {
  unsigned char flg[4];
  val_u val;
} vec_slot_t;

typedef struct {
  long count;
  long size;
  long cur;
  vec_slot_t slot[1];
} vec_st_t;

typedef vec_st_t *vec_t;

val_u vec_get(vec_t tb, long nkey, char tv, long ndef, void *pdef);
vec_t vec_set(vec_t tb, long nkey, char tv, long nval, void *pval);
vec_t vec_ins(vec_t tb, long nkey, char tv, long nval, void *pval);
vec_t vec_del(vec_t tb, long kfrom, long kto);

vec_t vecSetCount(vec_t vt, long max);
long vecCount(vec_t vt);

vec_t vec_new(long nslots);


vec_t vecDel(vec_t vt, long kfrom, long kto);
vec_t vecMove(vec_t vt, long kfrom, long kto);

vec_t vecFree(vec_t vt);
# 1243 "../../dist/libutl.h"
# 1 "../../dist/libutl.h" 1
# 1244 "../../dist/libutl.h" 2

typedef void *(*objCpyFun)(void *a, void *b);
typedef void *(*objNewFun)(void);
typedef void *(*objFreeFun)(void *a);
typedef int (*objCmpFun)(void *a, void *b);







typedef struct objclass_s {
  objCmpFun cmp; objNewFun new; objFreeFun free; objCpyFun cpy; int size;
} objclass_t;

typedef struct {
  objclass_t *class;
} obj_s;

typedef obj_s *obj_t;

extern obj_s *obj_tmp;
# 11 "gr2D.c" 2

struct Point2D_s;

typedef struct {
  objCmpFun cmp; objNewFun new; objFreeFun free; objCpyFun cpy; int size;
  void (*draw)(struct Point2D_s *);
  void (*move)(struct Point2D_s *pt, float dx, float dy);
} Point2DClass;

Point2DClass *Point2D_Class = ((void *)0);

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
    if (dst == ((void *)0)) dst = Point2DNew();
    if (dst != ((void *)0)) {
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
  if (Point2D_Class == ((void *)0)) {
    Point2D_Class = malloc(sizeof(Point2DClass));
  }

  if (Point2D_Class != ((void *)0)) {
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

  (Point2D_Class = Point2DClass_Init());

  p = (void *) (((obj_tmp = (Point2D_Class->new())) ? (obj_tmp->class = (void *)Point2D_Class) : ((void *)0)), obj_tmp);

  (p)->class->draw(p,);

  return (0);
}
