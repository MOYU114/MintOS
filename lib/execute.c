/*************************************************************************//**
 *****************************************************************************
 * @file   execute.c
 * @brief  This file contains some executable code.
 * @author Li Jie
 * @date   2023
 *****************************************************************************
 *****************************************************************************/


#include "stdio.h"


PUBLIC void  echoString(int argc, char * argv[]) {
    int i;
	for (i = 1; i < argc; i++) {
		printf("%s%s", i == 1 ? "" : " ", argv[i]);
	}
	printf("\n");
}

PUBLIC void touch(int argc, char * argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		int fd = open((const char*)argv[i], O_CREAT);
		if (fd == -1) {
			printf("Failure to create file %s\n", argv[i]);
			continue;
		}
		printf("FILE %s is created, fd: %d\n", argv[i], fd);
		close(fd);
	}
}

PUBLIC void removeFile(int argc, char * argv[]) {
	int i;
    for (i = 1; i < argc; i++) {
        int retval = unlink(argv[i]);
        if (retval == -1)
            printf("Remove FILE %s failed\n", argv[i]);
        else
            printf("Success to remove FILE %s\n", argv[i]);
    }
}