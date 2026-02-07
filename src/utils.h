#ifndef _MBPOLL_UTILS_H_
#define _MBPOLL_UTILS_H_

#include <stdbool.h>

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

void vFailureExit (bool bHelp, const char *format, ...);

#define vSyntaxErrorExit(fmt,...) vFailureExit(true,fmt,##__VA_ARGS__)
#define vIoErrorExit(fmt,...) vFailureExit(false,fmt,##__VA_ARGS__)

int * iGetIntList (const char * name, const char * sList, int * iLen);
void vPrintIntList (int * iList, int iLen);

#endif /* _MBPOLL_UTILS_H_ */
