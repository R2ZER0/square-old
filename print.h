/* print.h */
#ifndef _PRINT_H_
#define _PRINT_H_

#include "value.h"
#include <stdio.h>

/* Print a tree of Values */
void fprintvalue(FILE* file, value* val);

#endif /* _PRINT_H_ */