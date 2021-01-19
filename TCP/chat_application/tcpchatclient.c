#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80
#define BUFSIZE 1024
void func(int ssd)
{
char buff[MAX];
int n;
for(;;)
{
bzero(buff,sizeof(buff));
printf("Enter the string : ");
n=0;
while((buff[n++]=getchar())!='\n');
write(ssd,buff,sizeof(buff));
bzero(buff,MAX);
read(ssd,buff,sizeof(buff));
printf("From Server : %s\t",buff);
if(strncmp(buff,"exit",4)==0)
{
printf("Client Exit...\n");
exit(1);
break;
}
}
}
int  main()
{
int cfd,n,ret;
char buf[BUFSIZE];
int portno=1900;
struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
socklen_t addr_size;
cfd=socket(AF_INET,SOCK_STREAM,0);
if(cfd<0)
{
perror("socket");
exit(1);
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero); 
cli_addr.sin_family=AF_INET;
cli_addr.sin_port=htons(0);
cli_addr.sin_addr.s_addr=INADDR_ANY;
bzero(&cli_addr.sin_zero,sizeof(cli_addr.sin_zero));
size_t addrlen=sizeof(cli_addr);
ret=bind(cfd,(struct sockaddr*)&cli_addr,addrlen);
if(ret<0) 
{
perror("bind"); 
exit(2); 
}
bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));
ret=connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
if(ret<0) 
{
perror("bind"); 
exit(2);
}
func(cfd);
close(cfd);
}
