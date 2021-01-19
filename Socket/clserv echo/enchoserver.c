#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<error.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define ERROR -1
#define MAX_CLIENTS 5
#define MAX_DATA 1024

int main(int argc,char **argv)
{
struct sockaddr_in server;
struct sockaddr_in client;
int sock,new,ret;
int sockaddr_len=sizeof(struct sockaddr_in);
int data_len;
char data[MAX_DATA];

if((sock=socket(AF_INET,SOCK_STREAM,0))==ERROR)
	{
	perror("socket");
	exit(-1);
	}
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[1]));
server.sin_addr.s_addr=INADDR_ANY;
bzero(&server.sin_zero,8); // padding of structure

if((bind(sock,(struct sockaddr *)&server,sockaddr_len))==ERROR)
	{
	perror("bind");
	exit(-1);
	}
ret=listen(sock,MAX_CLIENTS);
while(1)
	{//better signal handling required
	new=accept(sock,(struct sockaddr*)&client,&sockaddr_len);
	if(new==ERROR)
	//for client new socket client structure use this new socket
	{
	perror("accept");
	exit(-1);
	}
printf("new client connected from port %d and IP is %s",ntohs(client.sin_port),inet_ntoa(client.sin_addr));

data_len=1;
while(data_len)
	{
	data_len=recv(new,data,MAX_DATA,0);

	if(data_len)
	{
	send(new,data,data_len,0);
	data[data_len]='\0';

	printf("sent msg: %s",data);

	}

	}

printf("client disconnected");
close(new);
}
}	
	


