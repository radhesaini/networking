#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<ctype.h>


#define SIZE 4096
#define MAXLINE 4096 /*MAX TEXT LINE LENGTH*/
#define port 3002 /* PORT */


void send_file(FILE *fp, int sockfd,int left_data)
  {
   printf("%ld",left_data);
   char data[BUFSIZ],check[10];
   long int n,j=0;
   while(left_data>0)
    {
     j+=1;
     fread(data,1,BUFSIZ,fp);
     
     if((n=send(sockfd,data,BUFSIZ,0))==-1)
      {
       perror("error in sending file");
       exit(1);
      }
    printf("send packet :%d size: %d\n",j);
     left_data-=n;
     bzero(data,n);
   // if(!recv(sockfd,data,SIZE,0)){
     //   printf("\nsend %ld\n",n);
       // return;
      //}
    memset(data,'\0',SIZE);
   
   }  
}


int main(int argc, char **argv)
 {
  int e;
  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp,*fp1;
  char filename[10];
  printf("sending file name: ");
  scanf("%s",filename);
  
  //sockfd=socket(AF_INET, SOCK_STREAM,0);
  if(argc!=2)
    {
     perror("usage: tcp client <ip address of the server");
     exit(1);
    }
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
   {
   perror("problem in creating the socket");
   exit(1);
   }
  printf("socket created successfully\n");
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(port);
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);

  if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
   {
    perror("problem in connecting to server ");
    exit(1);
   }
 
  printf("Connected to Server. \n");
  
  fp=fopen(filename,"rb+");
  if(fp==NULL)
    {
     perror("Error in reading file.");
     exit(1);
    }
  fseek(fp,0L,SEEK_END);
  long int size=ftell(fp);
  fclose(fp);
  fp1=fopen(filename,"rb+");
  send_file(fp1, sockfd,size);
  printf("File data sent successfully\n");

  printf("closing connection\n");
  //close(sockfd);
  return 0;
} 

      