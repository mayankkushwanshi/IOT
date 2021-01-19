#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int cfd, ret, portno = 1500, nbytes, sfd, nbyte, i=0, f=0;
	
	char buff[] = "I am in server", st[100];	
	
	cfd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in cli_addr, serv_addr;

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(0);
	
	bzero(&cli_addr.sin_zero,sizeof(cli_addr.sin_zero));

	ret = bind(cfd,(struct sockaddr*)&cli_addr,sizeof(cli_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));

	sfd = connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	int fptr;
	
	if((fptr = open("/home/desd/iots3/Socket/clserv/2abc.txt",O_RDONLY|O_CREAT,0666)) == -1)
	{
		perror("Error in fopen\n");	
	}	
	read(fptr,&st,100);	
	puts(st);
	close(fptr);
	nbyte = send(cfd,st,100,0);
				
	if(nbyte<0)
	{
		perror("Error in recv\n");
		exit(1);	
	}	
	
	close(sfd);
	close(cfd);
		
}
