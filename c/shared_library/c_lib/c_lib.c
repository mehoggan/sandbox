#include "c_lib.h"
#include <string.h>
#include <limits.h>
#include <stdio.h>

void Clib_trim(char s[])
{
    int i;
    
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '\n') {
            int j;
            for (j = i + 1; j <= strlen(s); j++) {
                s[j - 1] = s[j];
            }
            s[j] = '\0';
        }
    }
}

int Clib_get_typed_line_EOF(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

double Clib_atof(char s[]) 
{
    double val, power, rtn;
    int i, sign;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') ++i;
    for (val = 0.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.') {
        ++i;
    }
    for (power = 1.0; isdigit(s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    rtn = (sign * val / (power));

    // Next work on exponent
    if (s[i] == 'e') {
        int j, esign;
        int eval = 0;
        fprintf(stdout, "e found\n");
        for (j = i + 1; isspace(s[j]); ++j);
        esign = (s[j] == '-') ? -1 : 1;
        if (s[j] == '+' || s[j] == '-') ++j;
        for (; isdigit(s[j]); ++j) {
            eval = 10 * eval + (s[j] - '0');
        }
        fprintf(stdout, "eval = %d\n", eval);
        int l;
        for (l = 0; l < eval; l++) {
            (esign >= 0) ? (rtn *= 10) : (rtn /= 10);
        }        
    }
    
    // Finally return the solution
    return rtn;
}

int Clib_atoi(char s[])
{
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') ++i;
    for (n = 0; isdigit(s[i]); ++i)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

void Clib_itoa(int n, char s[])
{    
    int min_int = 0;
    int i = 0, sign = 0;;
    
    if (INT_MIN == n) {
        min_int = 10;
        n++;
    }

    if ((sign = n) < 0) n = -n;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    if (min_int == 10) s[0]++;
    Clib_reverse(s);
}

char *Clib_reverse(char s[])
{
    int c, i, j;

    for (i=0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    
    s[strlen(s)] = '\0';
    return s;
}
