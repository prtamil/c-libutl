/*
** .: (C) by Remo Dentato (rdentato@gmail.com)
** 
** This software is distributed under the terms of the BSD license:
**   http://creativecommons.org/licenses/BSD/
**   http://opensource.org/licenses/bsd-license.php
** .. 
*/

#include <stdio.h>

#ifdef WIN32
#include <winsock.h>
#endif

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>

struct req {
  int   sock;
  char *method;
  char *url;
  char *parms;
  char *mime;
  char *hdrs;
};

#ifdef WIN32
#define DIRSEP  '\\'
#else
#define DIRSEP '/'
#endif

int req_lua(struct req *r);
void close_lua(void);
void send_hdrs( int sock, int status, char *title, char *mime, char *extra);
void send_err( int sock, int status, char *title, char *text, char *extra);
void setdirsep(char *s);


void DieWithError(char *errorMessage);  /* Error handling function */
int  create_sock(unsigned short port,char *ipAddr); /* Create TCP server socket */
void handle_req(int sock, char *req);

void send_err(int sock, int status, char *title, char *text, char *extra);
void send_hdrs(int sock, int status, char *title, char *mime, char *extra);


#ifdef WIN32
#define close_sock(s) closesocket(s)
#else
#define close_sock(s) close(s)
#endif

char *rootdir="D:\\0_Works\\lhttp\\www";

char *emptystr="";

#ifdef WIN32
    WSADATA wsaData;                 /* Structure for WinSock setup communication */
#endif

int *servSock;                   /* Socket descriptors for server */
int noPorts;                     /* Number of port specified on command-line */

#define BUFSIZE 1024   /* Size of receive buffer */

char pbuf[BUFSIZE+128];

 struct mimetype {
  char *ext;
  char *mime;
};

static struct mimetype mimelist[] = {
  { "gif" ,"image/gif"},
  { "htm" ,"text/html; charset=iso-8859-1"},
  { "html","text/html; charset=iso-8859-1"},
  { "jpg" ,"image/jpeg"},
  { "jpeg","image/jpeg"},
  { "png" ,"image/png"},
  { "css" ,"text/css"},
  { "txt" ,"text/plain; charset=iso-8859-1"},
  { "lfn", "$lfn"},
  { "lhi", "$lhi"},
  { "lsp", "$lsp"},
  { "au"  ,"audio/basic"},
  { "avi" ,"video/x-msvideo"},
  { "mid" ,"audio/midi"},
  { "midi","audio/midi"},
  { "mov" ,"video/quicktime"},
  { "mp3" ,"audio/mpeg"},
  { "mpe" ,"video/mpeg"},
  { "mpeg","video/mpeg"},
  { "mpg" ,"video/mpeg"},
  { "pac" ,"application/x-ns-proxy-autoconfig"},
  { "qt"  ,"video/quicktime"},
  { "vrml","model/vrml"},
  { "wav" ,"audio/wav"},
  { "wrl" ,"model/vrml"},
  { NULL ,""}
};


static char *get_mime( char *name )
{
  char* dot;
  struct mimetype *m=mimelist;

  dot = strrchr( name, '.' );
  if (dot && dot[1]) {
    dot++;
    while (m->ext) {
      if (strcmp(dot,m->ext) == 0)
        return m->mime;
      m++;
    }
  }
  return emptystr;
}


static void cleanup()
{
  int port;

  for (port = 0; port < noPorts; port++)
     close_sock(servSock[port]);

  free(servSock);

#ifdef WIN32
    WSACleanup();  /* Cleanup Winsock */
#endif

}

static void sigcatch(int signal)
{
  printf("SIGNAL: %d\n",signal);
  fflush(stdout);
  cleanup();
  exit(0);
}


int hif_main(long timeout, int port)
{
    char buff[BUFSIZE];

    fd_set sockSet;                  /* Set of socket descriptors for select() */

    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in ClntAddr;     /* Client address */
    unsigned int clntLen;            /* Length of client address data structure */

    int recvMsgSize;

    struct timeval selTimeout;       /* Timeout for select() */
    int running = 1;                 /* 1 if server should be running; 0 otherwise */

    signal(SIGTERM,sigcatch);
    signal(SIGINT,sigcatch);

    noPorts = 1;             /* Number of ports is argument count minus 2 */

    /* Allocate list of sockets for incoming connections */
    servSock = (int *) malloc(noPorts * sizeof(int));

#ifdef WIN32
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) { /* Load Winsock 2.0 DLL */
      fprintf(stderr, "WSAStartup() failed");
      fflush(stderr);
      exit(1);
    }
#endif

    /* Create list of ports and sockets to handle ports */
    servSock[0] = create_sock(port,"127.0.0.1");

    while (running) {

      FD_ZERO(&sockSet);
      for (port = 0; port < noPorts; port++)
        FD_SET(servSock[port], &sockSet);

      selTimeout.tv_sec = timeout;
      selTimeout.tv_usec = 0;
      
printf("Waiting ...\n");
fflush(stdout);

      if (select(0, &sockSet, NULL, NULL, &selTimeout) == 0) {
        printf("No requests for %ld secs...Server still alive\n", timeout);
        fflush(stdout);
      }
      else {
        for (port = 0; port < noPorts; port++) {
          if (FD_ISSET(servSock[port], &sockSet)) {

            /* Wait for a client to connect */
            clntLen = sizeof(ClntAddr);
            clntSock = accept(servSock[port], (struct sockaddr *) &ClntAddr, &clntLen);

            if (clntSock < 0) DieWithError("accept() failed");

            recvMsgSize = recv(clntSock, buff, BUFSIZE-1, 0);

            if (recvMsgSize > 0)  {
              buff[recvMsgSize] = '\0';
              handle_req(clntSock, buff);
            }
            else
              close_sock(clntSock);    /* Close client socket */
          }
        }
      }
    }
    cleanup();
    return(0);
}

void DieWithError(char *errorMessage)
{
    fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError());
    fflush (stderr);
    exit(1);
}


#define MAXPENDING 10    /* Maximum outstanding connection requests */

int create_sock(unsigned short port, char *ipAddr)
{
    int sock;                        /* socket to create */
    struct sockaddr_in ServAddr; /* Local address */
    unsigned long ifAddr = INADDR_NONE;

    if (ipAddr && (*ipAddr != '\0'))
      ifAddr = inet_addr(ipAddr);
    else
      ifAddr = htonl(INADDR_ANY);

    if (ifAddr == INADDR_NONE)
      DieWithError("Invalid IP address");

    /* Create socket for incoming connections */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct local address structure */
    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = ifAddr;
    ServAddr.sin_port = htons(port);

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(sock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    return sock;
}


int prints( int sock, const char* format, ... )
{
  va_list ap;
  int r;

  va_start( ap, format );
  r = vsprintf( pbuf, format, ap );
  va_end( ap );
  if (*pbuf) {
    send(sock,pbuf,r,0);
  }
  return r;
}

static int hex( char c )
{
  if ( c >= '0' && c <= '9' ) return c - '0';
  if ( c >= 'a' && c <= 'f' ) return c - 'a' + 10;
  if ( c >= 'A' && c <= 'F' ) return c - 'A' + 10;
  return 0;
}

void decode(char *str)
{
  char *s=str;

  while (*str) {
    if (*str == '+')
      *s = ' ';
    else if (*str == '%') {
      if (isxdigit(str[1]) && isxdigit(str[2])) {
        *s=(hex(str[1]) *16) + hex(str[2]);
        str += 2;
      }
    }
    else *s = *str;
    str++; s++;
  }
  *s='\0';
}

void get_req(struct req *r,char *req)
{
  char *t, *u, *v, *p;

  r->method = emptystr;
  r->url    = emptystr;
  r->parms  = emptystr;
  r->mime   = emptystr;
  r->hdrs   = emptystr;

  t=strchr(req,' ');
  if (t) {
    r->method=req;
    *t='\0';

    u=strchr(t+1,' ');
    if (u) {
      r->url=t+1;
      *u='\0';

      t=strchr(r->url,'?');
      if (t) {
        r->parms=t+1;
        *t='\0';
      }
      u++;
      while(*u && (*u != '\n') && (*u!='\r')) u++;
      while(*u && isspace(*u)) u++;
      r->hdrs=u;
    }
  }

  decode(r->url);
  /*decode(r->parms);*/

  r->mime=get_mime(r->url);
}


void setdirsep(char *s)
{
  while (*s) {
    if (*s=='/') *s=DIRSEP;
    s++;
  }
  printf("filename=%s\n",pbuf);
  fflush(stdout);
}

FILE *getfile(char *url)
{
  FILE *f=NULL;
  char *s;

  sprintf(pbuf,"%s%s",rootdir,url);
  setdirsep(pbuf);
  f=fopen(pbuf,"r");

  return f;
}

void handle_req (int sock, char *req)
{

  FILE *f=NULL;
  int c;
  struct req r;

  /*
  printf("%s\n",req);
  fflush(stdout);
  */

  get_req(&r,req);
  r.sock=sock;

  printf("Meth: %s\n",r.method);
  printf("url:  %s\n",r.url);
  printf("parms:%s\n",r.parms);
  printf("mime: %s\n",r.mime);
  printf("hdrs: %s\n",r.hdrs);
  fflush(stdout);
  if ( r.mime[0] == '\0') {
    send_err(sock,404,"Unable to handle mime type",NULL,NULL);
  }
  else if ( (strcmp(r.method,"GET")==0) && (r.mime[0] != '$')) {
    f=getfile(r.url);
    if (f) {
      send_hdrs(sock,200,"OK", r.mime,NULL);
      c=getc(f);
      while (c != EOF) {
        *pbuf=c;

        if (send(sock,pbuf,1,0) <0) {
          c=EOF;
          printf("ERROR SENDING\n");
        }
        else
          c=getc(f);
      }
      fclose(f);
    }
    else
      send_err(sock,404,"File Not Found",NULL,NULL);
  }
  else {

    /*send_err(sock,404,"Lua function not found",NULL,NULL);*/
  }
  close_sock(sock);
}


#define SERVER_NAME "lhttpd"
#define PROTOCOL "HTTP/1.0"
#define RFC1123FMT "%a, %d %b %Y %H:%M:%S GMT"

void send_hdrs( int sock, int status, char *title, char *mime, char *extra)
{
  time_t now;
  static char timebuf[100];

  prints( sock, "%s %d %s\r\n", PROTOCOL, status, title );
  prints( sock, "Server: %s\r\n", SERVER_NAME );

  now = time( (time_t*) 0 );
  strftime( timebuf, sizeof(timebuf), RFC1123FMT, gmtime( &now ) );
  prints( sock, "Date: %s\r\n", timebuf );

  if ( extra && *extra )
    prints( sock, "%s\r\n", extra );

  if ( !(mime && *mime )) mime = "text/html";
  prints( sock, "Content-Type: %s\r\n", mime );

  prints( sock, "Expires: 0\r\n"\
                "Allow: GET\r\n"\
                "Connection: close\r\n\r\n" );

}

void send_err( int sock, int status, char *title, char *text, char *extra)
{
  send_hdrs( sock, 200, title, "text/html", extra);
  prints( sock, "<HTML><HEAD><TITLE>%d %s</TITLE></HEAD>\n<BODY BGCOLOR=\"#cccc99\"><H4>%d %s</H4>\n", status, title, status, title );
  if (!text) text=title;
  prints( sock, "%s\n", text );
  prints( sock, "<HR>\n</BODY></HTML>\n");
}



int main(int argc, char *argv[])
{

  if (argc < 3) {
    fprintf(stderr, "Usage:  %s <Timeout (secs.)> <Server Port 1> ...\n", argv[0]);
    fflush(stderr);
    exit(1);
  }

  hif_main(atol(argv[1]), atoi(argv[2]));
  exit(0);
}

