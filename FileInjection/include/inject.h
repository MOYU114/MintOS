#include "stdio.h"
#include "string.h"
#include "elf.h"
#include "type.h"

#define MAX_FILENAME_LEN 12

int inject(const char* pathname);
int injectAllELF();