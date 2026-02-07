#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#ifdef DEBUG
#define PDEBUG(fmt,...) printf("utils.c:%d: %s(): " fmt, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PDEBUG(...)
#endif

// -----------------------------------------------------------------------------
int *
iGetIntList (const char * name, const char * sList, int * iLen) {
  // 12,3,5:9,45

  int * iList = NULL;
  int i, iFirst = 0, iCount = 0;
  bool bIsLast = false;
  const char * p = sList;
  char * endptr;

  PDEBUG ("iGetIntList(%s)\n", sList);

  // Count and verify the integer list
  while (*p) {

    i = strtol (p, &endptr, 0);
    if (endptr == p) {

      vSyntaxErrorExit ("Illegal %s value: %s", name, p);
    }
    p = endptr;
    PDEBUG ("Integer found: %d\n", i);

    if (*p == ':') {

      // i is the first of a range first:last
      if (bIsLast) {
        // Cannot have 2 ':' in a row!
        vSyntaxErrorExit ("Illegal %s delimiter: '%c'", name, *p);
      }
      PDEBUG ("Is First\n");
      iFirst = i;
      bIsLast = true;
    }
    else if ( (*p == ',') || (*p == 0)) {

      if (bIsLast) {
        int iRange, iLast;

        // i is the last of a range first:last
        iLast = MAX (iFirst, i);
        iFirst = MIN (iFirst, i);
        iRange = iLast - iFirst + 1;
        PDEBUG ("Is Last, add %d items\n", iRange);
        iCount += iRange;
        bIsLast = false;
      }
      else {

        iCount++;
      }
    }
    else {

      vSyntaxErrorExit ("Illegal %s delimiter: '%c'", name, *p);
    }

    if (*p) {

      p++; // Skip the delimiter
    }
    PDEBUG ("iCount=%d\n", iCount);
  }

  if (iCount > 0) {
    int iIndex = 0;

    // Allocation
    iList = calloc (iCount, sizeof (int));
    if (iList == NULL) {
      vIoErrorExit ("Memory allocation failed for %s list", name);
    }

    // Assignment
    p = sList;
    while (*p) {

      i = strtol (p, &endptr, 0);
      p = endptr;

      if (*p == ':') {

        // i is the first of a range first:last
        iFirst = i;
        bIsLast = true;
      }
      else if ( (*p == ',') || (*p == 0)) {

        if (bIsLast) {

          // i is the last of a range first:last
          int iLast = MAX (iFirst, i);
          iFirst = MIN (iFirst, i);

          for (i = iFirst; i <= iLast; i++) {

            iList[iIndex++] = i;
          }
          bIsLast = false;
        }
        else {

          iList[iIndex++] = i;
        }
      }

      if (*p) {

        p++; // Skip the delimiter
      }
    }
#ifdef DEBUG
    // Removed dependency on ctx.bIsVerbose
    // if (ctx.bIsVerbose) {
    //   vPrintIntList (iList, iCount);
    //   putchar ('\n');
    // }
#endif
  }
  *iLen = iCount;
  return iList;
}

// -----------------------------------------------------------------------------
void
vPrintIntList (int * iList, int iLen) {
  int i;
  putchar ('[');
  for (i = 0; i < iLen; i++) {
    printf ("%d", iList[i]);
    if (i != (iLen - 1)) {
      putchar (',');
    }
    else {
      putchar (']');
    }
  }
}
