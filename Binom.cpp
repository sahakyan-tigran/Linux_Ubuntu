#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void calculate_and_write(int num, int fd) { 
	int result = 1;
	for(int i = 1; i <= num; ++i) {  
		result *= i;
	}
	const int size = 10;
	char buffer[size];
	sprintf(buffer, "%d", result);
	if(write(fd, buffer, size) == -1) { 
		std::cout << strerror(errno) << std::endl;
		return;
	}	
}

int read_and_return(int fd) { 
	const int size = 10;
	char buffer[size];
	if(read(fd, buffer, size) == -1) { 
		std::cout << strerror(errno) << std::endl;
		return -1;
	}
	return atoi(buffer);
} 

int main() { 
	int n = 0,k = 0,nk = 0;
	std::cin >> n >> k;
	nk = n - k;
	int n_pipe[2] = {};
	int k_pipe[2] = {};
	int nk_pipe[2] = {};
	if(pipe(n_pipe) == -1) { 
		std::cout << strerror(errno) <<std::endl;
		return 1;
	}
	if(pipe(k_pipe) == -1) { 
		std::cout << strerror(errno) <<std::endl;
		close(n_pipe[0]);
		close(n_pipe[1]);
		return 1;
	}
	if(pipe(nk_pipe) == -1) { 
		std::cout << strerror(errno) <<std::endl;
		close(n_pipe[0]);
		close(n_pipe[1]);
		close(k_pipe[0]);
		close(k_pipe[1]);
		return 1;
	}
	int p1 = fork();
	if(p1 == 0) { 
		close(n_pipe[0]);
		calculate_and_write(n, n_pipe[1]);
		return 0;
	}
	else {
		close(n_pipe[1]);
	}
	int p2 = fork();
	if(p2 == 0) { 
		close(k_pipe[0]);
		calculate_and_write(k, k_pipe[1]);
		return 0;
	}
	else {
		close(k_pipe[1]);
	}
	int p3 = fork();
	if(p3 == 0) { 
		close(nk_pipe[0]);
		calculate_and_write(nk, nk_pipe[1]);
		return 0;
	}
	else {
		close(nk_pipe[1]);
	}
	int result = 0;
	result = read_and_return(n_pipe[0]) / read_and_return(k_pipe[0]) / read_and_return(nk_pipe[0]);
	wait(0);
	std::cout << result << std::endl;
	return 0;
}
