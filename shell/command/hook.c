#include "type.h"
#include "stdio.h"

int main(int argc, char * argv[])
{
    if (argc != 2 )
        return -1;
    hook_syscall(atoi(argv[1]));
    return 0;
}