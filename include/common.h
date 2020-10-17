#ifndef COMMON_H
#define COMMON_H
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

typedef unsigned int uint;

/*Status code to represent respectively,
a negative answer,
a positive answer,
an almost positive answer
*/
typedef enum {
  NO,
  YES,
  ALMOST,
} e_status;

#endif /*COMMON*/
