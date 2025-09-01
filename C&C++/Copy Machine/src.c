#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <syscall.h>
#include <unistd.h>
#define PERMS 0644

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <source> <destination>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd1 = open(argv[1],O_RDONLY,PERMS);
    if(fd1==-1)
    {
        printf("Openning %s failed",argv[1]);
        exit(EXIT_FAILURE);
    }

    int fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,PERMS);
    if(fd2==-1)
    {
        printf("Openning %s failed",argv[2]);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = 1;
    ssize_t bytes_written = 0;
    char buf[BUFSIZ];

    while(bytes_read > 0)
    {
        bytes_read = read(fd1, buf, BUFSIZ );
        if(bytes_read ==-1)
        {
            perror("error happend while reading");
            exit(EXIT_FAILURE);
        }
        bytes_written = write(fd2, buf, bytes_read);
         if(bytes_written ==-1)
        {
            perror("error happend while writing");
            exit(EXIT_FAILURE);
        }
        if(bytes_read != bytes_written)
        {
            printf("something went wrong\n");
        }
        printf("\n%zu,%zu\n",bytes_read,bytes_written);
    }


    close(fd1);
    close(fd2);

    return 0;
}
