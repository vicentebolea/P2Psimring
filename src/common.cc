#include <uniDQP.h>

void
toArray (char* line, long* token)
{
	token[0] = atol (strtok (line, " "));
	token[1] = atol (strtok (NULL, " "));
	token[2] = atol (strtok (NULL, " "));
	token[3] = atol (strtok (NULL, " "));
}

uint64_t
timediff (struct timeval *end_time, struct timeval *start_time)
{
	return 	(end_time->tv_usec + (1000000 * end_time->tv_sec)) 
				-	(start_time->tv_usec + (1000000 * start_time->tv_sec));
}
