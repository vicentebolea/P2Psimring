#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function (void* aux) {
	char name [128];
	pthread_t myself;
	myself = pthread_self ();
	printf ("Pthread name: %s %#08x\n", name,  myself);
	pthread_exit (EXIT_SUCCESS);
}

int main () {
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create (&thread, &attr, thread_function, NULL);
	pthread_join (thread, NULL);
	return 0;
}
