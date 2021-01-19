#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8000
#define MAX 100

int main()
{
int ssd; //to create socket
int csd; //to accept connection

struct sockaddr_in serv_addr; //server recieve on this address.
struct sockaddr_in cli_addr;  //server sends to cli on this address.
int n;
char msg[MAX];
int clientaddrlen;
int pid;

//create socket
ssd=socket(AF_INET,SOCK_STREAM,0);
//intialise socket address
memset(&serv_addr,0,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
//serv_addr.sin_addr.s_addr=inet_addr("192.168.5.147");
serv_addr.sin_port=htons(PORT);

//bind the socket with server address and port

bind(ssd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

//listen for connection from client.
listen(ssd,5);

while(1)
{
//parent process waiting to accept a new connnection.

clientaddrlen=sizeof(cli_addr);
csd=accept(ssd,(struct sockaddr*)&cli_addr,&clientaddrlen);
printf("connected to a client: %s\n",inet_ntoa(cli_addr.sin_addr));

//child process is created for serving each new client.
pid=fork();

if(pid==0)//child process rec and send.
{
while(1)
{
n=recv(csd,msg,MAX,0);
if(n==0)
{
close(csd);
break;
}
msg[n]=0;
send(csd,msg,n,0);
printf("Recieve and set:%s\n",msg);
}
exit(0);
}
else
close(csd); //sock is closed by parent.
}
return 0;
}
