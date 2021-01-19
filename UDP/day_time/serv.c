#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/time.h>
#define PORT 1800
int day_time()
{
	char    *ctime();
	time_t    now;
	(void) time(&now);
    	printf("The time at which client sent data is %s\n", ctime(&now));
}

int main()
{int sfd,nbytes;
char buffer[1024];
struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
struct sockaddr_storage serv_str;
socklen_t addr_size,cli_addr_size;
sfd=socket(PF_INET,SOCK_DGRAM,0);
if(sfd<0)
{
perror("socket");
}
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(PORT);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));
bind(sfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
addr_size=sizeof(serv_str);
while(1)
{
nbytes=recvfrom(sfd,buffer,1024,0,(struct sockaddr*)&serv_str,&addr_size);
if(nbytes>0)
{
day_time();
}
sendto(sfd,buffer,nbytes,0,(struct sockaddr*)&serv_str,addr_size);
}
return 0;
} 
