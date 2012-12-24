#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <macros.h>

//networking
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <math.h>

//error handling
#include <errno.h>
#include <assert.h>

//standars libraries
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

//primitives
#include <stdint.h>
#include <inttypes.h>
#include <cfloat>

class Scheduler {
	private:
		static FILE* file;
		static Server server;
		pthread_t logger;
		pthread_t sender;

		//Method to be overrided with hash, bdema...
		int selectServer (void);
		void* logger_function (void* arg);
		void* sender_function (void* arg);

	public:
		Scheduler(int, char**);
		bool start();
		bool quit();

};

#endif
