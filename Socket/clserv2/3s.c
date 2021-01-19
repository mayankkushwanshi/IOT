#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int ssd, portno = 1500, ret, backlog = 5, csd, nbytes, nbyte, f=0, len;

	ssd = socket(AF_INET,SOCK_STREAM,0);
	
	char str[100], buf[] = "I am in child";	

	if(ssd<0)
	{
		perror("Error in socket");
		exit(1);
	}
	
	struct sockaddr_in serv_addr, cli_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));

	size_t addrlen = sizeof(serv_addr);
	ret = bind(ssd,(struct sockaddr*)&serv_addr,addrlen);
	printf("bind completed\n");
	ret = listen(ssd,backlog);

	socklen_t cli_addr_len = sizeof(cli_addr);
	
	csd = accept(ssd,(struct sockaddr*)&cli_addr,&cli_addr_len);
	
	if(csd<0)
	{
		perror("Error in accept");
		exit(2);	
	}
	
	printf("A client is connected\n");
	
	nbyte = recv(csd,str,100,0);
		
	if(nbyte<0)
	{
		perror("Error in send\n");
		exit(1);	
	}
	len = strlen(str);
	str[len] = '\0';

	int fptr;
	
	fptr = open("/home/desd/iots3/Socket/clserv2/abc.txt",O_WRONLY|O_CREAT,0666);
	
	if(fptr == -1)
	{
		perror("Error in fopen");
		exit(1);	
	}	
	
	write(fptr,&str,100);

	close(fptr);	
	
	puts(str);
	close(ssd);
	
	close(csd);
		
}

