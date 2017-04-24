#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define STDERR 2

int usage(char* exec_name);

int main(int argc, char** argv)
{
	
	return 0;
}

int usage(char* exec_name)
{
	errno = EINVAL; /*invalid argument*/
	char* s = "usage:\n";
	char* s1 = " [file]";
	write(STDERR, s, strlen(s));
	write(STDERR, exec_name, strlen(exec_name));
	write(STDERR, s1, strlen(s1));
	return 0;
}

int print_err(char* msg, int err)
{
	char* colon = ": ";
	char* serr = strerror(err);
	char* newline = "\n";
	write(STDERR, msg, strlen(msg));
	write(STDERR, colon, strlen(colon));
	write(STDERR, serr, strlen(serr));
	write(STDERR, newline, strlen(newline));
	return 0;
}
