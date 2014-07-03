#include <stdio.h>

char *pgname;

short cflag = 0;
short lflag = 0;
short wflag = 0;

FILE *fp;

void readFromFile(int argc, char* file)
{
	int bytes = 0;
	int lines = 0;
	int chars = 0;
	int words = 0;
	printf("Going to read from file (%s)\n", file);
	fp = fopen(file, "r");
	if(fp != NULL)
	{
		int print_num = 1;
		int print = 1;
		int c;
		while((c = getc(fp)) != EOF)
		{
			if(print)
			{
				printf("%d\t", print_num++);
				print = 0;
			}
			if(c == '\n')
			{
				print = 1;
				printf("%c", c);
			}
			else
			{
				printf("%c", c);
			}
		}	
	}
	else
	{
		printf("Error, could not find file (%s)\n", file);
		exit(1);
	}
}

void main(argc, argv) int argc; char* argv[];
{
	int i;
	char* cp;
	pgname = argv[0];
	
	fp = stdin;
	for(i = 1; i < argc; i++)
	{
		readFromFile(i, argv[i]);
	}		
}
