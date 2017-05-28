//AZhilitskiy, P3211, spo4, tail

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define DEFAULT_LINES_COUNT 10

int tail(char *filename, int linesCount);
int usage(char* filename);
int print_err(char* msg, int err);
char* readPreviousLine(int fileDesc);

int main(int argc, char *argv[]){

	if (argc < 2)
	{
		usage(*argv);
		print_err("Too few arguments", errno);
	}
	else if (argc > 2)
	{
		usage(*argv);
		print_err("Too much arguments", errno);
	}
	else 
	{
		int linesCount = DEFAULT_LINES_COUNT;
		tail(argv[1], DEFAULT_LINES_COUNT);		
	}
	
	return 0;
}

int tail(char *filename, int linesCount){
	int fileDesc;
	int readedLinesCount, length;
	char* line;

	fileDesc = open(filename, O_RDONLY);
	if (fileDesc < 0 )
		print_err("Error while opening file", errno);

	lseek(fileDesc, 0L, SEEK_END);

	for(readedLinesCount = 0; readedLinesCount < linesCount; readedLinesCount++){
		line = readPreviousLine(fileDesc);

		length = strlen(line);
		if(write(STDOUT_FILENO, line, length) < 0)
		{
			print_err("Can't write to stdout!", errno);
		}
		
		free(line);
	}

	return 0;
}

char* readPreviousLine(int fileDesc){
	char* result;
	int bytesRead, i, head=0, posEOL, length;

	result = calloc(BUFFER_SIZE, sizeof(char));
	if (!result)
		print_err("Error while allocating memory", errno);
	
	if(lseek(fileDesc, -BUFFER_SIZE, SEEK_CUR) < 0)
		print_err("lseek error", errno);

	
	return result;	
}

static size_t findEOL(char* str, int length){
	int i;
	for(i = 0; i < length; i++)
	{
		if(str[i] == '\n')
		{
			return i;
		}
	}
	return -1;
}

int usage(char* filename)
{
	errno = EINVAL; /*invalid argument*/
	char* s = "usage:\n";
	char* s1 = " [file]\n";
	char* tab= "\t";
	write(STDERR_FILENO, s, strlen(s));
	write(STDERR_FILENO, tab, strlen(tab));
	write(STDERR_FILENO, filename, strlen(filename));
	write(STDERR_FILENO, s1, strlen(s1));
	return 0;
}

int print_err(char* msg, int err)
{
	char* colon = ": ";
	char* serr = strerror(err);
	char* newline = "\n";
	write(STDERR_FILENO, msg, strlen(msg));
	write(STDERR_FILENO, colon, strlen(colon));
	write(STDERR_FILENO, serr, strlen(serr));
	write(STDERR_FILENO, newline, strlen(newline));
	exit(1);
}
