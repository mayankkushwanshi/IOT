#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define BUF_SIZE 50


int main()
{
	int i,cfd,ret,nbytes;
	int port_no = 1510;
	int backlog = 5;		
	int csd;
	char buf[BUF_SIZE];
	char str[]= "Thank you......";
	char stre[]="exit";

	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd<0)
	{
		perror("Error in cfd");
		exit(1);
	}
		
	struct sockaddr_in cli_addr;
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(0);
	cli_addr.sin_addr.s_addr = INADDR_ANY;
		
	bzero(&cli_addr.sin_zero,sizeof(cli_addr.sin_zero));
	size_t addrlen = sizeof(cli_addr);
		
	ret = bind(cfd,(struct sockaddr*)&cli_addr,addrlen);
	if(ret<0)
	{
		perror("Error in bind");
		exit(2);
	}
		
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1510);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));
	ret = connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret<0)
        {
                perror("Error in Connect"); 
                exit(3); 
        }
 
	while(1)
	{
		nbytes = read(1,buf,BUF_SIZE);
		buf[nbytes-1]='\0';
	//	printf("%s %d %d\n",buf,strlen(buf),strlen(stre));	
		nbytes = send(cfd,buf,strlen(buf),0);
		if(nbytes<0)
		{
			perror("Send");
			exit(5);
		}
	
		if((strlen(buf))==strlen(stre))
		{
			for(i=0;(stre[i]==buf[i])&&(i<strlen(stre));i++);
			if(stre[i]=='\0')
			{
				printf("Exiting\n");
				close(csd);
				close(cfd);
			}
		}
		nbytes = recv(cfd,buf,BUF_SIZE,0);
		if(nbytes<=0)
		{
			perror("Recieve");
			close(csd);
			close(cfd);
			exit(6);
		}
	}
		close(csd);
		close(cfd);
		return 0;
}










			
