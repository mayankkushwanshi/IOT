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
	int i,ssd,ret,nbytes;
	int port_no = 1510;
	int backlog = 5;		
	int csd;
	char buf[BUF_SIZE];
	char str[]= "Thank you......";
	char strq[] = "quit";
	ssd = socket(AF_INET,SOCK_STREAM,0);
	if(ssd<0)
	{
		perror("Error in SSD");
		exit(1);
	}
		
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		
	bzero(&serv_addr.sin_zero,sizeof(serv_addr.sin_zero));
	size_t addrlen = sizeof(serv_addr);
		
	ret = bind(ssd,(struct sockaddr*)&serv_addr,addrlen);
	if(ret<0)
	{
		perror("Error in bind");
		exit(2);
	}
		
	ret = listen(ssd,backlog);	//to put Socket in Server Mode
	if(ret<0)
	{
        	perror("Error in listen"); 
                exit(3); 
        }
		
	struct sockaddr_in cli_addr;
	size_t cli_addr_len = sizeof(cli_addr);
		
	csd = accept(ssd,(struct sockaddr*)&cli_addr,&cli_addr_len);
	if(csd<0)
	{
        	perror("Error in Accept"); 
                exit(4); 
        }

	printf("\nA Client got Connected from ip address %s port number %d \n", inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
	while(1)
	{	
		//-----------Recieve----------------
		nbytes = recv(csd,buf,BUF_SIZE,0);
		if(nbytes<0)
		{
			perror("Recieve");
			close(csd);
			close(ssd);
			exit(5);
		}
		buf[nbytes]='\0';	
		printf("%s %d %d\n",buf,strlen(buf),strlen(strq));
		if((strlen(buf))==strlen(strq))
		{
			for(i=0;(strq[i]==buf[i]) && (i<strlen(strq));i++)
			{
				printf(" %c %c\n",strq[i],buf[i]);
			}
			if((strq[i]=='\0'))	
			{
				printf("\nQuiting.........\n");
				close(csd);
				close(ssd);
				break;
			}
		}
		//------------Send------------------
		nbytes = send(csd,str,strlen(str),0);
		if(nbytes<0)
		{
			perror("Send");
			close(csd);
			close(ssd);
			exit(6);
		}
	}
	close(csd);
	close(ssd);
	return 0;
}










			
