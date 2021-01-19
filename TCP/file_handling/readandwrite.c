#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>

int main()
{
int nbytes,fd,len,max=20;
char buf[20];
fd=open("SAMPLE.txt",O_RDONLY);
if(fd<0)
{
perror("read");
exit(1);
}
nbytes=read(fd,buf,10);
if(nbytes<0)
{
perror("read");
}
fd=open("copy.txt",O_WRONLY|O_CREAT,0666);
nbytes=write(fd,buf,nbytes);
close(fd);
}
