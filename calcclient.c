#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define maxline 4096 //max text line length
#define port 3004
int main(int argc, char **argv)
 {
 int sockfd,res;
 struct sockaddr_in server_addr;
 char sendline[maxline];
 if(argc!=2)
  {
   perror("usage:tcp client <ip address of the server");
   exit(1);
  }

  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
     perror("problem in creating the socket");
     exit(2);
    }
   
  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=inet_addr(argv[1]);
 server_addr.sin_port=htons(port);
 
 if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
   {
    perror("problem in connecting to server ");
    exit(1);
   }
 
 while(fgets(sendline,maxline,stdin)!=NULL)
{
 write(sockfd,sendline,sizeof(sendline));
 bzero(sendline,sizeof(sendline));
 read(sockfd,&res,sizeof(res));
 printf("from Server :%d\n",res);
 if(strncmp(sendline,"exit",4)==0)
   {
    printf("client exit...\n");
    break;
   }
 
 }

}