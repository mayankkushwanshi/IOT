#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	
	int cfd, ret, portno = 1500, nbytes, sfd, nbyte, i=0, f=0, len;
	
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
	while(1)
	{

	char buff[20], st[14], str[] = "exit";	
	
	if(f==0)
	{
		gets(buff);
		nbytes = send(cfd,buff,20,0);
	
		if(nbytes<0)
		{
			perror("Error in send\n");
			exit(1);	
		}	
		f=1;
	
		len = strcmp(buff,str);
	
		if(len==0)
		{
			break;		
		}
	}
	
	if(f==1)
	{
		nbyte = recv(cfd,st,20,0);
		printf("in f=1\n");
		if(nbyte<0)
		{
			perror("Error in recv\n");
			exit(1);	
		}	
			f=0;
		printf("%s\n",st);
	}
		
		printf("%d\n",f);
	}	
	close(sfd);
	close(cfd);
			
}
