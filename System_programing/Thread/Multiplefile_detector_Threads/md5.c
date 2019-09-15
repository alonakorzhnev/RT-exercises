#include <openssl/md5.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char* file2md5(char* path){
	int fd;
    MD5_CTX c;
    char buf[512];
    ssize_t bytes;

    unsigned char* out = (unsigned char*)malloc(MD5_DIGEST_LENGTH * sizeof(unsigned char));
    if (!out)
        return NULL;
    //unsigned char out[MD5_DIGEST_LENGTH];

    MD5_Init(&c);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return NULL;
    bytes=read(fd, buf, 512); 
    while(bytes > 0)
    {
        MD5_Update(&c, buf, bytes);
        bytes=read(fd, buf, 512);
    }

    MD5_Final(out, &c);
	close(fd);
    return(out);  
}