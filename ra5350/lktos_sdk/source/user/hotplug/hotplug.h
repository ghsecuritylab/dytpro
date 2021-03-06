/*
 * HotPlug definitions
 *
 * Copyright 2004, Broadcom Corporation
 * All Rights Reserved.                
 *                                     
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;   
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior      
 * written permission of Broadcom Corporation.                            
 *
 * $Id$
 */

#ifndef _hotplug_h_
#define _hotplug_h_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

#include <sys/wait.h>
#include <fcntl.h>      /* open */
#include <unistd.h>     /* exit */

#define RT2860_NVRAM    0

#define MOUNTPOINT "/var/mountpoint"

/* MC8780 modem */
extern int mc8780_flag;

/*helper routines*/
extern int bcmSystem (char *command);

/*net hotplug handler routine*/
extern int hotplug_net(void);
extern int hotplug_storage_mountpoint(void);
extern int hotplug_storage_mount(void);
extern int hotplug_storage_umount(void);

extern int notify_nas(char *type, char *ifname, char *action);

extern int _eval(char *const argv[], char *path, int timeout, int *ppid);

#ifdef DEBUG
#define cprintf(fmt, args...) do { \
        FILE *fp = fopen("/dev/ttyS1", "w"); \
        if (fp) { \
                fprintf(fp, fmt, ## args); \
                fclose(fp); \
        } \
} while (0)
#else
#define cprintf(fmt, args...)
#endif

/* Debug macros */
#ifdef BCMDBG
#define DBG(fmt, args...) printf("hotplug (wsu):: %s: " fmt "\n" , __FUNCTION__ , ## args);
#else
#define DBG(nas, fmt, args...)
#endif

#ifdef DEBUG
#define dprintf(fmt, args...) cprintf("%s: " fmt, __FUNCTION__, ## args)
#else
#define dprintf(fmt, args...)
#endif

#define getdtablesize() (64)

#define eval(cmd, args...) ({ \
	char *argv[] = { cmd, ## args, NULL }; \
	_eval(argv, ">/dev/console", 0, NULL); \
})

#endif
 