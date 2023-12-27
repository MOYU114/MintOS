#include "inject.h"

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Please input a filepath!\n");
		return -1;
	}
    if(inject(argv[1]))
        printf("Inject Success!!!\n");
    else
    {
        printf("Cave Not Found!\n");
        return 0;
    }

	return 0;
}