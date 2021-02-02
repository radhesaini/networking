#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

#define MAXLINE 4096 /*MAX TEXT LINE LENGTH*/
#define SERV_PORT 3001 /* PORT */

int main(int argc,char **argv)

{
 int sockfd;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE],recvline[MAXLINE];

 if(argc !=2)
 {
  perror("usage: tcp client <ip address of the server");
  exit(1);
 }
  
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
 {
   perror("problem in creating the socket");
   exit(2);
  }
  
 memset(&servaddr,0,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=inet_addr(argv[1]);
 servaddr.sin_port=htons(SERV_PORT);
 
 if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
   {
    perror("problem in connecting to server ");
    exit(1);
   }
 
 while(fgets(sendline,MAXLINE,stdin)!=NULL)
{
 write(sockfd,sendline,sizeof(sendline));
 bzero(sendline,sizeof(sendline));
 read(sockfd,sendline,sizeof(sendline));
 printf("from Server :%s",sendline);
 if(strncmp(sendline,"exit",4)==0)
   {
    printf("client exit...\n");
    break;
   }
 
 }

}