#include<stdio.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

int main()
{
int rsd, portno = 1800, ret, backlog = 5, csd, nbytes, nbyte, f=0;

rsd=socket(AF_INET,SOCK_DGRAM,0);
char str[20], buf[]="abcd";

if(rsd<0)
	{
		perror("Error");
		exit(1);
	}

struct sockaddr_in src_addr, cli_addr;
//socklen_t src_len=sizeof(src_addr);
//recvfrom(rsd,buf,maxlen,0,&src_addr);

	src_addr.sin_family = AF_INET;
	src_addr.sin_port = htons(portno);
	src_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);

	bzero(&src_addr.sin_zero,sizeof(src_addr.sin_zero));


	size_t addrlen = sizeof(src_addr);
	ret = bind(rsd,(struct sockaddr*)&src_addr,addrlen);
	socklen_t src_len=sizeof(src_addr);
	recvfrom(rsd,buf,maxlen,0,&src_addr);
	printf("bind completed\n");
	ret = listen(rsd,backlog);


socklen_t cli_addr_len = sizeof(cli_addr);
	
	csd = accept(rsd,(struct sockaddr*)&cli_addr,&cli_addr_len);
	
	if(csd<0)
	{
		perror("Error in accept");
		exit(2);	
	}
	
	printf("A client is connected\n");
	
	nbyte = sendto(csd,buf,14,0);
		//f=0;
	if(nbyte<0)
	{
		perror("Error in send\n");
		exit(1);	
	}	
	
	


	close(rsd);
	
	close(csd);
		
}

