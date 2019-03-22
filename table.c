#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "UWzone.h"

void construct_table(struct IP_struct start_ip, struct IP_struct to_ip)
{
	int i, j, k, l, stoploop;
	
	nbtotal=stoploop=0;

	fprintf(stderr, "[*] Constructing zone table, can take a while...\n");

	zone_table = malloc(sizeof(struct zone_struct));
 
	for(i=start_ip.p1; i<=HIGH; i++)
	{
		if(stoploop==1) break;
		for(j=start_ip.p2; j<=HIGH; j++)
		{
			if(stoploop==1) break;
			for(k=start_ip.p3; k<=HIGH; k++)
			{
				if(stoploop==1) break;
				for(l=start_ip.p4; l<=HIGH; l++)
				{
					if(stoploop==1) break;
					add_entry_table(i, j, k, l);
					if((i == to_ip.p1) && (j == to_ip.p2) && (k == to_ip.p3) && (l == to_ip.p4)) stoploop=1;
					nbtotal++;
				}	
			}
		}
	}
}

void add_entry_table(int p1, int p2, int p3, int p4)
{
	struct zone_struct *ptr;

	if((ptr = realloc(zone_table, (nbtotal+1)*sizeof(struct zone_struct))) == NULL)
	{
		fprintf(stderr, "[!] realloc()\n");
		free(zone_table);
		exit(EXIT_FAILURE);
	}

	zone_table = ptr;

	zone_table[nbtotal].ip_addr.p1 = p1;
	zone_table[nbtotal].ip_addr.p2 = p2;
	zone_table[nbtotal].ip_addr.p3 = p3;
	zone_table[nbtotal].ip_addr.p4 = p4;

	zone_table[nbtotal].resolved = 0;
}
