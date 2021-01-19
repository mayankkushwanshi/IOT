#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	
	int ssd, portno = 1500, ret, backlog = 5, csd, nbytes, nbyte, len;

	ssd = socket(AF_INET,SOCK_STREAM,0);	

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
	
	
		int f=0, i = 0, j=0;
	ret = listen(ssd,backlog);

	socklen_t cli_addr_len = sizeof(cli_addr);
	
	csd = accept(ssd,(struct sockaddr*)&cli_addr,&cli_addr_len);
	
	if(csd<0)
	{
		perror("Error in accept");
		exit(2);	
	}
	
	printf("A client is connected\n");
	while(1)
	{
	
	char str[20], buf[20], st[5] = "quit";	
	
	if(f==0)
	{
	nbytes = recv(csd,str,20,0);
		
		if(nbytes<0)
		{
			perror("Error in recv\n");
			exit(1);	
		}	
		printf("%s\n",str);
		f=1;
	}
	
	if(f==1)
	{
		gets(buf);
		nbyte = send(csd,buf,20,0);
		printf("in f==1\n");
		if(nbyte<0)
		{
			perror("Error in recv\n");
			exit(1);	
		}	
		f=0;	
		len = strcmp(buf,st);
		if(len == 0)
			break;
	}
	
	/*len = strlen(str);
	str[len] = '\0';
		while(str[i]!='\0')
		{
			if(str[i] == st[j])
			{
				f++;
				j++;
				i++;
				if(f==4)
				{
					close(ssd);
					close(csd);
					exit(0);					
				}	
			}
			else
			{
				i++;
				f=0;	
			}
		
		}*/
	
	}
	close(ssd);
	
	close(csd);
		
}

