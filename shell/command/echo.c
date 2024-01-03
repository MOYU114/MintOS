#include "stdio.h"

int main(int argc, char * argv[])
{
	char* str = "Hello World\n";
	__asm__ __volatile__ ("movl $0, %%eax; movl %0, %%edx; int $0x90"::"m"(str));
	// echoString(argc, argv);
	return 0;
}