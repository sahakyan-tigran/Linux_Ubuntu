#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

bool is_prime(int number) {
	if(number == 1) {
		return false;
	}
	if(number == 2 || number == 3) {
		return true;
	}
	for(int i = 2; i <= number/2; ++i) {
		if(number % i == 0) {
			return false;
		}
	}
	return true;
}

void find_and_write(int fd, int point1, int point2) {
	int result = 0;
	for(int i = point1; i <  point2; ++i) {
		if(is_prime(i)) {
			++result;
		} 
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
	int n1 = 0, n2 = 0, m = 0;
	std::cin >> n1 >> n2 >> m;
	int length = (n2 - n1) / m;
	int fd[m + 1][2] = {};
	char buffer1[10];
	for(int i = 1; i < m + 1; ++i) {
		char s[10] = "Fifo";
		sprintf(buffer1,"%d", i);
		if(mkfifo(strcat(s,buffer1),S_IRWXU) == -1) {
			std::cout << strerror(errno) << std::endl; 
			return 1;
		}
	}
	int p[m + 1] = {};
	for(int i = 1; i < m + 1; ++i) { 
		char s[10] = "Fifo";
		sprintf(buffer1,"%d",i);
		p[i] = fork();
		if(p[i] == 0) { 
			if((fd[i][1] = open(strcat(s,buffer1),O_WRONLY)) == -1) {
				std::cout << strerror(errno) << std::endl;
				return 1;
			}
			int point1 = n1;
			int point2 = (i == m) ? (n2 + 1) : (n1 + length);
			find_and_write(fd[i][1], point1, point2);
			close(fd[i][1]);
			return 0;
		}
		else { 
			if((fd[i][0] = open(strcat(s,buffer1),O_RDONLY)) == -1) {
				std::cout << strerror(errno) << std::endl;
				return 1;
			} 
		}
		n1 += length;
	}
	int result = 0;
	for(int i = 1; i < m + 1; ++i) {
		result += read_and_return(fd[i][0]);
	}
	wait(0);
	std::cout << result << std::endl;
	for(int i = 1; i < m + 1; ++i) {
		close(fd[i][0]);
	}
	return 0;
}

