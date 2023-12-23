/*************************************************************************//**
 *****************************************************************************
 * @file   execute.c
 * @brief  This file contains some executable code.
 * @author Li Jie
 * @date   2023
 *****************************************************************************
 *****************************************************************************/


#include "stdio.h"


void  echo_string(int argc, char * argv[]) {
    int i;
	for (i = 1; i < argc; i++) {
		printf("%s%s", i == 1 ? "" : " ", argv[i]);
	}
	printf("\n");
}

void touch(int argc, char * argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		int fd = open((const char*)argv[1], O_CREAT);
		if (fd == -1) {
			printf("Failure to create file %s\n", argv[i]);
			return;
		}
		printf("FILE %s is created, fd: %d\n", argv[i], fd);
		close(fd);
	}
}