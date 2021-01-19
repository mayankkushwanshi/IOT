#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 80
#define bufsize 1024
void func(int ssd)
{
char buff1[MAX], buff[MAX];
int n;
for(;;)
{
bzero(buff,MAX);
read(ssd,buff,sizeof(buff));
printf("From Client %s\t to Client:",buff);
n = 0;
bzero(buff1,MAX);
//n=0;
//__fpurge(stdin);
while((buff1[n++]=getchar())!='\n');
write(ssd,buff1,sizeof(buff1));
//printf("%s",buff1);
if(strcmp("exit",buff1)==0)
{
printf("Server Exit\n");
exit(1);
break;
}
}
}
int  main()
{
char buf[bufsize];
int ssd,ret,csd,backlog=5,n;
int portno=1900;
struct sockaddr_in serv_addr;				//server address	
struct sockaddr_in cli_addr;				//client address
ssd=socket(AF_INET,SOCK_STREAM,0);	//socket field descriptor,AF_INET=TCP PROTOCOL(domain)IPv4,SOCK_STREAM->tcp(type),0->protocol
if(ssd<0)
{
perror("socket");
exit(1);
}
serv_addr.sin_family=AF_INET;		
serv_addr.sin_port=htons(portno);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));//The bzero() function copies n bytes, each with a value of zero, into string s. 
size_t addrlen=sizeof(serv_addr);
ret=bind(ssd,(struct sockaddr*)&serv_addr,addrlen);
if(ret<0) 
{
 perror("bind"); 
bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));exit(2); 
}
ret=listen(ssd,backlog);
if(ret<0)
{
perror("listen");
exit(3);
}
socklen_t cli_addr_len=sizeof(cli_addr);
csd=accept(ssd,(struct sockaddr*)&cli_addr,&cli_addr_len);
if(csd<0)
{
 perror("accept");
 exit(4);
}
printf("a client got connected from ip address %s,port no.:%d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
func(csd);
close(ssd);
}
