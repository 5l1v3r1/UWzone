#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "UWzone.h"

#define RAND_OFFSET 5

struct th_id
{
        int flag;
        pthread_t th;
};

/* Bays and S.D.Durham algo */
int my_rand_time(void)
{
	static int tab[RAND_OFFSET];
	static int first = 0;
	int index;
	int rn;
	int i;

	if(first == 0)
	{
		srand(time(NULL));
		for(i=0; i < RAND_OFFSET; i++)
			tab[i] = rand();
		first=1;
	}

	index=(int)(rand() / RAND_MAX * (RAND_OFFSET - 1));
	rn=tab[index];
	tab[index]=rand();
	return(rn);
}

void new_threads(void)
{
	pthread_t id;
	void *th_ret;
	int i, random;
	struct th_id th_id[256];	

	memset(th_id, 0, sizeof(th_id));

	pthread_mutex_init(&mut_zone_table, NULL);

	if(nbmiss < thread_number) thread_number = nbmiss;

	for(i=0; i<(int)thread_number; i++)
	{
		if(pthread_create(&id, NULL, (void *)resolve_host, NULL) != 0)
		{
			fprintf(stderr, "[!] not enought ressources for thread creation\n");
			exit(EXIT_FAILURE);
		}
       
		th_id[i].flag = 1;
		th_id[i].th = id;
	}	

	for(i=0; i<(int)thread_number; i++)
	{
		if(th_id[i].flag == 1)
		{
			if(pthread_join(th_id[i].th, &th_ret) != 0)
			fprintf(stderr, "[!] thread %d has some pb to be joined\n", (int)th_id[i].th);
		}
	}        

	/* hahahahah fucking crapp... l33t c0de */
	if(nbmiss < (progress * (10 - percent)))
	{
		fprintf(stderr, " %d0%%..", percent);
		percent++;
	}

	random = (my_rand_time() % 10) + thread_offset;

	if(thread_offset != 0)
		sleep(random);
}
