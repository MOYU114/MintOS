/*************************************************************************//**
 *****************************************************************************
 * @file   execute.c
 * @brief  This file contains some executable code.
 * @author Li Jie
 * @date   2023
 *****************************************************************************
 *****************************************************************************/


#include "stdio.h"

PUBLIC void  hello() {
	printf("Welcome to MintOS!\n");
	
	printf("........,,,,........................\n"
           ".......':3'3;7',,...................\n"
           "......,7;'37,7l';3;',...............\n"
           "......73:7:l,3;3,;l;3;.,............\n"
           ".....77;7'':l',l,;l':l'7,...........\n"
           "....,;73':7;:3,3,'l':3;77:,.........\n"
           "....,3:'77::733;,::':l;;l::;........\n"
           "....;;:3:';:77l3,l,;77:733;3;.......\n"
           "....;7;,;:7::;:3l:':l;77ll;;l:,.....\n"
           "....,;:77:;'';;73l'3':l7o3;:l7:.....\n"
           ".....:7;'';:777::ol';::oo:;:l7:,....\n"
           ".....,;7777;;'';73o:;:7o;::3'::,....\n"
           "......;:::::7733373o::l;::3;;l;,....\n"
           ".......;7777:::::73lo7;;37,;3;,.....\n"
           "........,':7l3l77373oo7l;,;7,.......\n"
           "..........,,'73lllllobl7;7:,........\n"
           "..............,,':73oddll,..........\n"
           ".....................ll.............\n"
           "......................ll............\n");
}

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