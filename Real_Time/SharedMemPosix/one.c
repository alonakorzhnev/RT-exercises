C program for Producer process illustrating POSIX shared-memory API. 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

int main() 
{ 
	const int SIZE = 4096; 
	const char* name = "OS";  

	int shm_fd; 
	int* ptr; 

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
	ftruncate(shm_fd, SIZE); 
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 

    

 
	return 0; 
} 
