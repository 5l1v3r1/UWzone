/*
 *   --=[UWzone]=--
 * UWzone is a multithreaded randomyzed reverse zoner
 * Dedicated to this really stupid saturday... 
 * Coded by csk <casek@uberwall.org>
 * UberWall security team
 * Feedbacks welcomes
 * Glop glop enjoy :p
 *
 *   --=[ Copyright ]=--
 *
 * Copyright (c) Uberwall 2003-2005
 * All rights reserved. All software redistribution and use
 * in source and binary forms, with or without modification, are
 * permitted provided that this copyright notice is retained.
 * All documentation belong to their respective authors.
 *
 *   --=[ Disclaimer ]=--
 *
 * We, authors gathered in the group "UberWall", can not be held
 * responsible for any use of the content available on its site,
 * "www.uberwall.org".
 *
 * Indeed, this group only aims to share knowledge and research
 * about computer security, and some elements presented may be
 * misused by malicious people.
 *
 * We warn again that anyone is responsible for his own behaviour,
 * and that unauthorized access to computer systems is illegal,
 * as well as any other activity assimilated to "cracking".
 *
 * We have absolutely no intention to break the law concerning any
 * resource or work detailed here.
 *
 *   --=[ Enjoy ]=--
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "UWzone.h"

void usage(char *soft)
{
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "%s [-S start IP] [-T to IP] options\n", soft);
        fprintf(stderr, "Options:\n");
	fprintf(stderr, "%s -N server           Set nameserver to use\n", soft);
        fprintf(stderr, "%s -t thread offset    Set minimal time between threads groups (default: 1)\n", soft);
        fprintf(stderr, "%s -n thread(s)        Set number of scanning threads (default: 1)\n",soft);
	fprintf(stderr, "PS: minimal time is because of time randomizing between offset value and +/- 10sec\n");
	fprintf(stderr, "PS: if the thread_offset value is set to 0, no time or random offset is used\n"); 
	fprintf(stderr, "PS: in the same ways IP queries are fully randomized in function of zone size\n");
 
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char cmdarg, cmd_startip[16], cmd_toip[16];
	int i;

        thread_offset = 1;
        thread_number = 1;

	if(argc < 3) usage(argv[0]);

	while((cmdarg = getopt(argc, argv, "S:T:N:t:n:")) != EOF)
	{	
		switch(cmdarg)
		{
			case 'S':
				memset(cmd_startip, 0, sizeof(cmd_startip));
				strncpy(cmd_startip, optarg, sizeof(cmd_startip));
				break;
			case 'T':
				memset(cmd_toip, 0, sizeof(cmd_toip));
				strncpy(cmd_toip, optarg, sizeof(cmd_toip));
				break;
			case 'N':
				memset(cmd_nameserver, 0, sizeof(cmd_nameserver));
				strncpy(cmd_nameserver, optarg, sizeof(cmd_nameserver));
				break;
			case 't':
				thread_offset = atoi(optarg);
				break;	
			case 'n':
				thread_number = atoi(optarg);
				break;
			default:
				usage(argv[0]);
		}
	}

	if(thread_number > 256)
	{
		fprintf(stderr, "[!] really.. more than 256 threads..\n");
		exit(EXIT_FAILURE);
	}

	check_zone(cmd_startip, cmd_toip);
	construct_table(start_ip, to_ip);
	progress=nbtotal/10;
	nbmiss=nbtotal;
	percent=1;
	fprintf(stderr, "[*]");
	while(nbmiss != 0) new_threads();
	fprintf(stderr, " 100%%... done\n");

	for(i=0; i<(int)nbtotal; i++)
	{
		if(zone_table[i].hostname_associated[0] != '\0')
			fprintf(stdout, "[%d.%d.%d.%d] %s\n", 
			zone_table[i].ip_addr.p1, zone_table[i].ip_addr.p2,
			zone_table[i].ip_addr.p3, zone_table[i].ip_addr.p4,
			zone_table[i].hostname_associated);
	}
	
	free(zone_table);
	exit(EXIT_SUCCESS);
}
