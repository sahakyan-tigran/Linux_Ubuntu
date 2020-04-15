#include <iostream>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

bool last_n_bits(const char* name1, const char* name2, int n) {
	int fd1 = open(name1, O_RDONLY);
	if(fd1 == -1) {
		std::cout << strerror(errno) << std::endl;
		return false;
	}
	int fd2 = open(name2, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if(fd2 == -1) {
		std::cout << strerror(errno) << std::endl;
		close(fd1);
		return false;
	}

	const int size = 10;
	char buffer[size];
	int r = -1,w = -1;
	int l = lseek(fd1, - n - 1, SEEK_END);
	if(l == -1) {
		std::cout << strerror(errno) << std::endl;
		close(fd1);
		close(fd2);
		return false;
	}
	while((r = read(fd1, buffer, size)) > 0) {
		w = write(fd2, buffer, r);
		if((w == -1) || (w != r)) {
			std::cout << strerror(errno) << std::endl;
			close(fd1);
			close(fd2);
			return false;
		}

	}
	if(r == -1) {
		close(fd1);
		close(fd2);
		std::cout << strerror(errno) << std::endl;
		return false;
	}
	
	close(fd1);
	close(fd2);
	return true;
}

int main(int argc, char* argv[]) {
	int n = 0;
	std::cin >> n;
	if((argc >= 3) && last_n_bits(argv[1], argv[2], n)) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "fail" << std::endl;
	}
	return 0;
} 













