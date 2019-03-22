#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <resolv.h>
#include "UWzone.h"

#define AF_INET 2

void resolve_host(void)
{
	struct hostent *host;
	struct sockaddr_in nameserver;
	char ip_to_resolv[4];
	int random = 0;

	srand(time(NULL));

	pthread_mutex_lock(&mut_zone_table);

	while(zone_table[random].resolved != 0)
		random=(int)((double)rand() / ((double)RAND_MAX + 1) * nbtotal);

	zone_table[random].resolved = 1;

	ip_to_resolv[0] = (char) zone_table[random].ip_addr.p1;
	ip_to_resolv[1] = (char) zone_table[random].ip_addr.p2;
	ip_to_resolv[2] = (char) zone_table[random].ip_addr.p3;
	ip_to_resolv[3] = (char) zone_table[random].ip_addr.p4;

	if(cmd_nameserver[0] != '\0')
	{
		nameserver.sin_addr.s_addr = getip(cmd_nameserver);	
		_res.options &= ~(RES_DNSRCH | RES_DEFNAMES);
		_res.nsaddr_list[0].sin_addr = nameserver.sin_addr;
	}

	host=gethostbyaddr(ip_to_resolv, sizeof(ip_to_resolv), AF_INET);

	if(host)
	{
		strncpy(zone_table[random].hostname_associated,
		(char *)host->h_name,
		sizeof(zone_table[random].hostname_associated) - 1);
	}

	pthread_mutex_unlock(&mut_zone_table);

	nbmiss--;
	pthread_exit(0);
}

unsigned long getip(char *hostname)
{
        struct hostent *he;
        long ipaddr;

        if ((ipaddr = inet_addr(hostname)) < 0)
                {
                if ((he = gethostbyname(hostname)) == NULL) {
                        fprintf(stderr, "[!] gethostbyname: host not found\n");;
                        exit(EXIT_FAILURE);
                }
                memcpy(&ipaddr, he->h_addr, he->h_length);
        } 
        return ipaddr;
}
