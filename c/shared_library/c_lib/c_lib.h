#include <string.h>
#include <ctype.h>

#ifndef C_LIB_H_
#define C_LIB_H_
void Clib_trim(char s[]);
int Clib_get_typed_line_EOF(char s[], int lim);
double Clib_atof(char s[]);
int Clib_atoi(char s[]);
void Clib_itoa(int n, char s[]);
char *Clib_reverse(char s[]);
#endif //C_LIB_H_
