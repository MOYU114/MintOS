#include "type.h"
#include "stdio.h"

int main(int argc, char * argv[])
{
    int i;
    for (i = 1; i < argc; i++) {
        unlink(argv[i]);
    }
    return 0;
}