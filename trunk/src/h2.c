#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <string.h>

#ifdef WIN32

  #include <winsock.h>
  #define close_sock(s) closesocket(s)
  WSADATA wsaData;

#else
  #include <sys/socket.h>
  #include <netinet/in.h>

  #define close_sock(s) close(s)
#endif


void error(char *msg)
{
    perror(msg);
    exit(1);
}



int hif_main(int portno)
{
  int sockfd, newsockfd, clilen;
  char buffer[256];
     
  struct sockaddr_in serv_addr, cli_addr;
  int n;

#ifdef WIN32
    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) { /* Load Winsock 2.0 DLL */
      fprintf(stderr, "WSAStartup() failed");
      fflush(stderr);
      exit(1);
    }
#endif

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
        error("ERROR opening socket");
        
  memset((char *) &serv_addr,0x0, sizeof(serv_addr));
  
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

  clilen = sizeof(cli_addr);
  
  listen(sockfd,5);
  while(1){
    newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);

    if (newsockfd < 0) error("ERROR on accept");

    memset(buffer,0x0,256);
    n = recv(newsockfd,buffer,255,0);
    if (n < 0) error("ERROR reading from socket");
    
    printf("Here is the message: %s\n",buffer); fflush(stdout);
    
    n = send(newsockfd,"I got your message",18,0);
    if (n < 0) error("ERROR writing to socket");
    
    close_sock(newsockfd);
    if (buffer[0]=='$') break;
  }
  close_sock(sockfd);
  
  #ifdef WIN32
  WSACleanup();  /* Cleanup Winsock */
  #endif
  
  return 0;
}

int main(int argc, char *argv[])
{
     
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
     
  hif_main(atoi(argv[1]));
  exit(0); 
}

