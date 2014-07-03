/*
 * prgm6.h
 *
 *  Created on: Oct 3, 2009
 *      Author: Matthew
 */

#ifndef PRGM6_H_
#define PRGM6_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int pf[2];
#define BUFFER 512

int argument_count;

short cflag = 0;
short lflag = 0;
short wflag = 0;
int total_bytes = 0;
int total_lines = 0;
int total_words = 0;

char *pgname;

FILE *fp;

typedef struct
{
	int pid;
	int word;
	int lines;
	int bytes;
	char* file;
} wc_struct;

wc_struct* input;
int words = 0;
int bytes = 0;
int lines = 0;
char* file;
#endif /* PRGM6_H_ */
