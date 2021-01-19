#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

#define PORT 8000
#define MAX 100
#define SERVER_IP "127.0.0.1"
int  main()
{
int ssd; //to create a socket.
struct sockaddr_in serv_addr; //client will connect on this.
int n;
char msg1[MAX];
char msg2[MAX];

//create socket.

ssd=socket(AF_INET,SOCK_STREAM,0);
//initialise the socket address.

memset(&serv_addr,0,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
//serv_addr.sin_addr.s_addr=inet_addr("192.168.5.147");
serv_addr.sin_port=htons(PORT);

//client connect to server on port
connect(ssd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
//send to server and recieve from server.
while(1)
{
printf("\nEnter message to server:\n");
fgets(msg1,MAX,stdin);
if(msg1[0]=='#')
break;
n=strlen(msg1)+1;
send(ssd,msg1,n,0);
n=recv(ssd,msg2,MAX,0);
printf("Recieved message from server:%s\n",msg2);
}
return 0;

}
