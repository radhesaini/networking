#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define SIZE 4096 /*MAX TEXT LINE LENGTH*/
#define port 3002 /*PORT*/
#define LISTENQ 8 /*maximum number of client connections */
void write_file(int sockfd)
{
  int n;
  FILE *fp;
  char filename[10];
  printf("receive file name: ");
  scanf("%s",filename);
  char buffer[BUFSIZ];
  fp=fopen(filename,"wb");
  int i=0;
  long int m=0;
  while(1)
   { 
   
   i+=1;
   n=recv(sockfd,buffer,BUFSIZ,0);
   printf("recving packat:%d of size:%ld\n",i);
   //n=strlen(buffer);
    if(n==0)
      {
       printf("\n%ld",m);
       break;
      }
    fwrite(buffer,1,n,fp);
    //bzero(buffer,n);
    memset(buffer,'\0',n);
    //send(sockfd,"ok",10,0);
    }
    fclose(fp);
}

int main(int argc, char **argv)
  {
   int e;
   int listenfd,connfd,n;
   struct sockaddr_in server_addr,client_addr;
   socklen_t addr_size;
    
   listenfd=socket(AF_INET,SOCK_STREAM,0);
   if(listenfd<0)
     {
      perror("Error in Socket");
      exit(1);
     }
    printf("server socket created successfully\n");
    
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
    e=bind(listenfd ,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(e>0)
      {
       perror("binding successfully.\n");
      }
    if(listen(listenfd,LISTENQ)==0)
      { 
       printf("listening....\n");
       //exit(1);
      }
    printf("%s \n","server running ...waiting for connections.");
    addr_size=sizeof(client_addr);
    connfd=accept(listenfd,(struct sockaddr*)&client_addr,&addr_size);
    printf("Received request...");
    write_file(connfd);
    close(connfd);
    printf("data written in the file succesfully\n");
    close(listenfd);
    return 0;
}
