/*************************************************************************//**
 *****************************************************************************
 * @file   stat.c
 * @brief  
 * @author Forrest Y. Yu
 * @date   Wed May 21 21:17:21 2008
 *****************************************************************************
 *****************************************************************************/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"


/*****************************************************************************
 *                                stat
 *************************************************************************//**
 * 
 * 
 * @param path 
 * @param buf 
 * 
 * @return  On success, zero is returned. On error, -1 is returned.
 *****************************************************************************/
PUBLIC int stat(const char *path, struct stat *buf)
{
	MESSAGE msg;

	msg.type	= STAT;

	msg.PATHNAME	= (void*)path;
	msg.BUF		= (void*)buf;
	msg.NAME_LEN	= strlen(path);

	send_recv(BOTH, TASK_FS, &msg);
	assert(msg.type == SYSCALL_RET);

	return msg.RETVAL;
}

PUBLIC int list()
{
	MESSAGE msg;

	char buf[DIR_ENTRY_SIZE*32];

	msg.type = LIST;

	msg.BUF = (void*)buf;

	send_recv(BOTH, TASK_FS, &msg);
	assert(msg.type == SYSCALL_RET);

	printf("INODE\t\t  FILENAME\n");
	printf("-----                ------------\n");
	struct dir_entry * pde = (struct dir_entry *)msg.BUF;
	int i;
	char filename[MAX_FILENAME_LEN+1] = {0};
	for(i = 0; i < msg.CNT; i++) {
		memcpy((void*)filename, (void*)pde->name, MAX_FILENAME_LEN);
		printf("%5d\t\t%s\n", pde->inode_nr, filename);
		pde++;
	}

	return msg.RETVAL;
}
