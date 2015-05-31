// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifdef __CYGWIN__
#include <windows.h>
#elif (defined WIN32) || (defined _WIN32) || (defined __WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "targetver.h"
#elif (defined __gnu_linux__) || (defined __linux__)
#endif



// TODO: reference additional headers your program requires here
