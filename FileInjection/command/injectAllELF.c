#include "inject.h"

int main(int argc, char** argv) {
	if (injectAllELF())
        printf("inject All ELF Success!\n");
    else printf("error\n");

	return 0;
}
