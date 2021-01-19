#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/socket.h>
#define PORT 1800
int main()
{
int cfd,nbytes;
char buffer[1024];
struct sockaddr_in serv_addr;
socklen_t addr_size;

cfd=socket(PF_INET,SOCK_DGRAM,0);
if(cfd<0)
{
perror("socket");
}
serv_addr.sin_family=AF_INET;
serv_addr.sin_port=htons(PORT);
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
bzero(serv_addr.sin_zero,sizeof(serv_addr.sin_zero));

addr_size=sizeof(serv_addr);
while(1)
{
printf("Type a sentence to send to server:\n");
fgets(buffer,1024,stdin);
printf("You typed: %s",buffer);
nbytes=strlen(buffer)+1;

sendto(cfd,buffer,nbytes,0,(struct sockaddr*)&serv_addr,addr_size);
nbytes=recvfrom(cfd,buffer,1024,0,NULL,NULL);
printf("Recieved from server:%s\n",buffer); 
}
return 0;
}

