#include <pthread.h>

#define HIGH 255
#define LOW 0

char cmd_nameserver[32];

unsigned int thread_offset;
unsigned int thread_number;
pthread_mutex_t mut_zone_table;

unsigned long nbtotal;
unsigned long nbmiss;
unsigned int progress;
int percent;

struct IP_struct
{
   int p1;         /* XXX.x.x.x */
   int p2;         /* x.XXX.x.x */
   int p3;         /* x.x.XXX.x */
   int p4;         /* x.x.x.XXX */
};

struct IP_struct start_ip, to_ip;

struct zone_struct
{
	struct IP_struct	ip_addr;
	char			hostname_associated[256];
	int			resolved;
};

struct zone_struct *zone_table;

extern void check_zone(char *cmd_start_ip, char *cmd_to_ip);
extern void resolve_host(void);
extern unsigned long getip(char *hostname);
extern void construct_table(struct IP_struct start_ip, struct IP_struct to_ip);
extern void add_entry_table(int p1, int p2, int p3, int p4);
extern int my_rand_time(void);
extern void new_threads(void);
