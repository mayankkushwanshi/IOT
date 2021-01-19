#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
 
int main()
{
char buf[20];
int max=20,fd,nbytes;
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
exit(2);
}
write(1,buf,nbytes);
close(fd);
}
