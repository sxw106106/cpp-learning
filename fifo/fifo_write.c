#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
//#include <fstream>

#define FIFO_SERVER "/tmp/myfifo"
#define OPENMODE (O_WRONLY|O_NONBLOCK)

int main(int argc ,char **argv)
{
	int fd;
	int nwrite;
	if((fd=open(FIFO_SERVER,OPENMODE))<0)
	{
		perror("open");
		exit(1);
	}
	if(argc==1)
	{
		printf("please send something\n");
		exit(1);
	}
	if ( nwrite = write(fd,argv[1], strlen(argv[1]) ) )
	{

		if(errno==EAGAIN)
		{
			printf("the fifo has not been read yet.try again\n");
			exit(1);
		}
		else
		{
			printf("write %s to fifo\n",argv[1]);
		}		
		return 0;
		
	}

}
