#include <stdio.h>

char *pgname;

short cflag = 0;
short lflag = 0;
short wflag = 0;
int total_bytes = 0;
int total_lines = 0;
int total_words = 0;

FILE *fp;

void readFromFile(int argc, char* file)
{
	int bytes = 0;
	int lines = 0;
	int words = 0;
	fp = fopen(file, "r");
	if(fp != NULL)
	{
		int c;
		int prev_c;
		while((c = getc(fp)) != EOF)
		{
			//printf("c is now %c\n", c);
			if(c == ' ')
			{
				total_words++;
				total_bytes++;
				words++;
				bytes++;
			}
			else if(c == '\n')
			{
				if(prev_c != '\n')
				{
					total_words++;
					words++;
				}
				total_bytes++;
				total_lines++;
				bytes++;
				lines++;
			}
			else
			{
				total_bytes++;
				bytes++;
			}
			prev_c = c;
		}
		if(lflag)
		{
			printf("%3d ", lines);
		}
		if(wflag)
		{
			printf("%3d ", words);
		}
		if(cflag)
		{
			printf("%3d ", bytes);
		}
		if(!cflag && !wflag && !lflag)
		{
			printf("%3d ", lines);
			printf("%3d ", words);
			printf("%3d ", bytes);
		}
		printf(" %3s\n", file);
	}
	else
	{
		printf("Error, could not find file (%s)\n", file);
		exit(1);
	}
}

void main(int argc, char* argv[])
{
	int i;
	char* file;
	char* cp;
	pgname = argv[0];

	fp = stdin;
	for(i = 1; i < argc; i++)
	{
		cp = argv[i];
		if(*cp == '-')
		{
			int count = 0;
			while(*++cp)
			{
				if(count >= 3)
				{
					printf("To many options\n");
					exit(1);
				}
				if(*cp != 'l' && *cp != 'c' && *cp != 'w')
				{
					printf("Invalid option\n");
					exit(1);
				}
				if(*cp == 'w' && !wflag)
				{
					wflag++;
				}
     				else if(*cp == 'l' && !lflag)
				{
					lflag++;
				}
				else if(*cp == 'c' && !cflag)
				{
					cflag++;
				}
				else
				{
					printf("Duplicate (%c) not allowed\n", *cp);
					exit(1);
				}
				count++;

			}
		}
		else
		{
			file = argv[i];
			readFromFile(i, file);
		}
	}
	if(argc > 3)
	{
		if(lflag)
		{
			printf("%3d ", total_lines);
		}
		if(wflag)
		{
			printf("%3d ", total_words);
		}
		if(cflag)
		{
			printf("%3d ", total_bytes);
		}
		if(!cflag && !wflag && !lflag)
		{
			printf("%3d ", total_lines);
			printf("%3d ", total_words);
			printf("%3d ", total_bytes);
		}
		printf("%3s\n", "total");
	}
}
