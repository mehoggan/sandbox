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

int pipflag[2];
#define BUFFER 512

char input[BUFFER];

int argument_count;

#endif /* PRGM6_H_ */
