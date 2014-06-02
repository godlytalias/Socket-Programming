#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>


pthread_t thread;



void error (char *msg){
 perror(msg);
 exit(0);
 }


void* receive(void* d)
{
int sockfd=*((int *)d);
int a;
char buf[256];

while(1)
{
bzero(buf,256);
a=recv(sockfd,buf,255,0);
if(a<=0)
error("Error reading from socket");
else
printf("\n %s\n ",buf);
}
close(sockfd);
pthread_exit(NULL);
}

  
 int main (int argc, char *argv[]) {
  int sockfd, portno, n,newsockfd,userno;
char user[100],pass[30];
  struct sockaddr_in addr_in, serv_addr;
  struct hostent *server;
  char buffer[256];
  FILE *file;
  

   if (argc<3) {
   fprintf (stderr,"Usage %s Host Name Port\n", argv[0]);
   exit(0);
   }
   
   portno=atoi(argv[2]);
   sockfd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    if (sockfd<0)
   error("ERROR Opening Socket");
   
   server=gethostbyname(argv[1]);
   
   if (server==NULL) {
    fprintf(stderr, "ERROR, No Such Host\n");
    exit(0);
    }
    
    bzero((char*)&serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family=AF_INET;
    bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port=htons(portno);
    newsockfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (newsockfd<0)
    error("ERROR Connecting");
    

else
{
reg:
bzero(user,100);
username:
printf("\nENTER THE USERNAME  : ");
fgets(user,100,stdin);
if(strncmp(user,"user-",5)!=0)
{
printf("USERNAME FORMAT NOT CORRECT  (FORMAT - user-<no>)");
goto username;
}
n=send(sockfd, user, strlen(user), 0);
printf("\nENTER THE PASSWORD  : ");
fgets(pass,30,stdin);
n=send(sockfd, pass, strlen(pass), 0);
bzero(buffer,256);
n=recv(sockfd,buffer,255,0);
if(n>0)
printf("%s\n",buffer);
if(strcmp(buffer,"USERNAME EXISTS")==0)
goto reg;
}
file=fopen("user.txt","a+");
char str[100];
bzero(str,100);
printf("\nLOGGED IN USERS\n");
while(fscanf(file,"%s",str)!=EOF)
{
if(str[0]=='u')
printf("\n%s\n",str);
fscanf(file,"%s",str);
}
if(strcmp(buffer,"USER REGISTERED")==0)
{
fprintf(file,"%s",user);
fprintf(file,"\n%s\n",pass);}
fclose(file);


pthread_create(&thread,NULL,receive,(void*)&sockfd);
while(1)
{

enter:

     printf("\nPlease Enter The Message: ");
    
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    
if((strncmp(buffer,"To user-",8)==0)||(strncmp(buffer,"bye",3)==0))
{
sprintf(buffer,"%s|%s",buffer,user);
n=send(sockfd, buffer, strlen(buffer), 0);
    
    if(n<0)
    error("ERROR Writing To Socket");
   if(strncmp(buffer,"bye",3)==0)
  break;   
    
    
}
else
{
printf("\nMESSAGE FORMAT NOT CORRECT\n");
goto enter;}

     }
    close(sockfd); 
   
   return 0;
   
  }
