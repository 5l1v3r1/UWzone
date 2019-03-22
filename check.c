#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "UWzone.h"

void check_zone(char *cmd_start_ip, char *cmd_to_ip)
{
        if(sscanf(cmd_start_ip, "%d.%d.%d.%d", &start_ip.p1, &start_ip.p2, &start_ip.p3, &start_ip.p4) != 4)
        {
                fprintf(stderr, "[!] Start IP need to be regular\n");
                exit(EXIT_FAILURE);
	}
        if(start_ip.p1 > HIGH)
        {
		fprintf(stderr, "[!] Start IP zone 1 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(start_ip.p2 > HIGH)
	{
		fprintf(stderr, "[!]Start IP zone 2 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(start_ip.p3 > HIGH)
	{
		fprintf(stderr, "[!] Start IP zone 3 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(start_ip.p4 > HIGH)
	{
		fprintf(stderr, "[!] Start IP zone 4 is incorrect\n");
		exit(EXIT_FAILURE);
	}


        if(sscanf(cmd_to_ip, "%d.%d.%d.%d", &to_ip.p1, &to_ip.p2, &to_ip.p3, &to_ip.p4) != 4)
        {
                fprintf(stderr, "[!] To IP need to be regular\n");
                exit(EXIT_FAILURE);
	}
	if(to_ip.p1 > HIGH)
	{
		fprintf(stderr, "[!] To IP zone 1 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(to_ip.p2 > HIGH)
	{
		fprintf(stderr, "[!] To IP zone 2 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(to_ip.p3 > HIGH)
	{
		fprintf(stderr, "[!] To IP zone 3 is incorrect\n");
		exit(EXIT_FAILURE);
	}
	if(to_ip.p4 > HIGH)
	{
		fprintf(stderr, "[!] To IP zone 4 is incorrect\n");
		exit(EXIT_FAILURE);
	}

        start_ip.p1=fabs(start_ip.p1);
        start_ip.p2=fabs(start_ip.p2);
        start_ip.p3=fabs(start_ip.p3);
        start_ip.p4=fabs(start_ip.p4);
        to_ip.p1=fabs(to_ip.p1);
        to_ip.p2=fabs(to_ip.p2);
        to_ip.p3=fabs(to_ip.p3);
        to_ip.p4=fabs(to_ip.p4);

        if(start_ip.p1 != to_ip.p1)
                if(start_ip.p1 > to_ip.p1)
                {
                        fprintf(stderr, "[!] Start IP must be lower than to IP - zone1\n");
                        exit(EXIT_FAILURE);
                }

        if(start_ip.p2 != to_ip.p2)
                if((start_ip.p2 > to_ip.p2) && (start_ip.p1 == to_ip.p1))
                {
                        fprintf(stderr, "[!] Start IP must be lower than to IP - zone2\n");
                        exit(EXIT_FAILURE);
                }

        if(start_ip.p3 != to_ip.p3)
                if((start_ip.p3 > to_ip.p3) && (start_ip.p1 == to_ip.p1) && (start_ip.p2 == to_ip.p2))
                {
                        fprintf(stderr, "[!] Start IP must be lower than to IP - zone3\n");
                        exit(EXIT_FAILURE);
                }

        if(start_ip.p4 != to_ip.p4 )
                if((start_ip.p4 > to_ip.p4)  && (start_ip.p1 == to_ip.p1) && (start_ip.p2 == to_ip.p2) && (start_ip.p3 == to_ip.p3))
                {
                        fprintf(stderr, "[!] Start IP must be lower than to IP - zone4\n");
                        exit(EXIT_FAILURE);
                }
}
