/*
 * prgm6_2.c
 *
 *  Created on: Oct 3, 2009
 *      Author: Matthew
 */
#include "prgm6_2.h"
#define MSG 32
pid_t main_pid;
pid_t pid;
pid_t cpid;
int status;

void wc(int, int[], wc_struct*);

int main(int argc, char* argv[])
{
	int p[argc][2];
	argument_count = argc;
	wc_struct* data[argc];
	int x;
	char* cp;	

	cp = argv[1];
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
	
	if(!wflag && !lflag && !cflag)
	{
		wflag++;
		lflag++;
		cflag++;
	}	

	for(x = 0; x < argc; x++)
	{
		data[x] = (wc_struct*)malloc(sizeof(wc_struct));
	}
	
	for(x = 0; x < argc; x++)
	{		
		if(pipe(p[x]) == -1)
		{
			perror("Pipe failure\n");
			exit(10);
		}

		pid = fork();
		if(pid == 0)
		{
			file = argv[x];
			wc(x, p[x], data[x]);
			exit(0);
		}
		if((pid = wait(&status)) == -1)
		{
			perror("Wait failed\n");
			exit(2);
		}						
	}

	for(x = 0; x < argc; x++)
	{
		cp = argv[1];
		if(x > 0)
		{
			if(*cp == '-' && x==1)
			{
				continue;
			}
			close(p[x][1]);
			input = (wc_struct*)malloc(sizeof(wc_struct));
			read(p[x][0], input, sizeof(wc_struct));
			total_words = total_words + input->word;
			total_lines = total_lines + input->lines;
			total_bytes = total_bytes + input->bytes;
			if(lflag)
                	{
                       		printf("%4d ", input->lines);
                	}
			if(wflag)
			{
				printf("%4d ", input->word);
			}
			if(cflag)
			{
				printf("%4d ", input->bytes);
			}
			if(!lflag && !cflag && !wflag)
			{
				printf("%4d ", input->lines);
				printf("%4d ", input->word);
				printf("%4d ", input->bytes);
			}
			printf("%4s ", input->file);
			printf("%4d ", input->pid);
			printf("\n");
			free(input);
			free(data[x]);
		}
	}

	if(argc > 2)
	{
		if(lflag)
		{
			printf("%4d ", total_lines);
		}
                if(wflag)
                {
                        printf("%4d ", total_words);
                }
		if(cflag)
		{
			printf("%4d ", total_bytes);
		}
		if(!wflag && !cflag && !lflag)
		{
			printf("%4d ", total_lines);
			printf("%4d ", total_words);
			printf("%4d ", total_bytes);
		}
		printf("total\n");
	}
	exit(0);
}

void wc(int x, int p[2], wc_struct* data)
{
	words = 0;
	lines = 0;
	bytes = 0;

	close(p[0]);

	int prev_c;
	int c;

	fp = stdin;
	fp = fopen(file, "r");
	if(fp != NULL)
	{
		while((c = getc(fp)) != EOF)
		{
			if(c == ' ')
			{
				words++;
				bytes++;
			}
			else if(c == '\n')
			{
				if(prev_c != '\n')
				{
					words++;
				}
				bytes++;
				lines++;
			}
			else
			{
				bytes++;
			}
			prev_c = c;
		}
		data->pid = getpid();
        	data->word = words;
	        data->lines = lines;
	        data->bytes = bytes;
		data->file = file;
	}
	else
	{
		//printf("Error, could not find file (%s)\n", file);
	}
        write(p[1], data, sizeof(wc_struct));
}


