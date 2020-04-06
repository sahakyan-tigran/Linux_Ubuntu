#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
                                                                                                                                                                        void copy_file_1(const char* name1,const char* name2,int n){                                                                                                                 int d1 = open(name1,O_RDONLY);
     int d2 = open(name2, O_CREAT | O_WRONLY | O_TRUNC);

        const int size=10;
        char buffer[size];
        int r = 0;
        while((r = read(d1,buffer,size))!=0){
                if(n > r) {
                   write(d2,buffer,r);
                }
                else
                {
                        write(d2,buffer,n);
                        break;
                }
                n -= r;
        }

        close(d1);
        close(d2);
}
void copy_file_2(const char* name1, const char* name2, int n) {
        int d1 = open(name1, O_RDONLY);
        int d2 = open(name2, O_CREAT | O_WRONLY | O_TRUNC);

        const int size = 10;
        char buffer[size];
        int r = 0;
        int k = 0;
	bool f=false;
        while((r = read(d1, buffer, size)) != 0) {
                 if(f) {
                        if(buffer[0] == ' ') {
                                ++n;
                        }
                        f = false;
                }
                if(buffer[size - 1] == ' ') { 
			f = true;
                }
		int n1 = n;
                int in_b = 0;
                for(int i = 0; i < size; ++i) {
                        if(buffer[i] == ' ') {
                                ++in_b;
                                --n;
                        }
                        if((buffer[i + 1] == ' ') && (buffer[i] == ' ')) {
                                --in_b;
                                ++n;
                        }
                        if(n == 0) {
                                k = i;
                                break;
                        }
                }
                if(n1 > in_b) {
                        write(d2, buffer, r);
                }
                else {
                        if(n1 != 0) {
                                write(d2, buffer, k);
                        }
                        break;
                }
        }
        close(d1);
        close(d2);
}
void copy_file_3(const char* name1, const char* name2, int n) {
        int d1 = open(name1, O_RDONLY);
        int d2 = open(name2, O_CREAT | O_WRONLY | O_TRUNC);

        const int size = 10;
        char buffer[size];
        int r = 0;
        int k = 0;
        while((r = read(d1, buffer, size)) != 0) {
                int n1 = n;
                int in_b = 0;
                for(int i = 0; i < size; ++i) {
                        if(buffer[i] == '\n') {
                                ++in_b;
                                --n;
                        }
                        if((buffer[i + 1] == '\n') && (buffer[i] == '\n')) {
                                --in_b;
                                ++n;
                        }
                        if(n == 0) {
                                k = i;
                                break;
                        }                                                                                                                                                               }
                if(n1 > in_b) {
                        write(d2, buffer, r);
                }
                else {
                       if(n1 != 0) 
                                {
  	    		 write(d2, buffer, k);
               		}
                         break;
                     }
        }
        close(d1);
        close(d2);
}
int main()
{ 	
	int i=0;
	std::cin>>i; 
        copy_file_3("f11","f22",i);
        return 0;
}
