#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

static int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ERROR: stack full, can't push\n");
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("ERROR: stack empty\n");
        return 0.0;
    }
}
