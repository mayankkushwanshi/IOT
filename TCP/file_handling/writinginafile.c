#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
int main()
{
int fd;
int nbytes,len;
char str[]="ABCDEFGH";
fd=open("SAMPLE.txt",O_WRONLY|O_CREAT,0666);
if(fd<0)
{
perror("open");
exit(1);
}
len=strlen(str);
nbytes=write(fd,str,len);
if(nbytes<0)
{
perror("write");
exit(2);
}
close(fd);

}
