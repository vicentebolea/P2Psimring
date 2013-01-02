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
#include <getopt.h>

//primitives
#include <stdint.h>
#include <inttypes.h>
#include <cfloat>

//Project
#include <file/parser.hh>
#include <server/server.hh>

class Scheduler {

/*****************************************************
 Code needed for parsing the command line
 *****************************************************/
protect:
	const char* default_config_path = "config.ini";
	const char* optstring = "f:n:p:h";

	const struct option opt_long[] = 
	{
		{"config_path", required_argument, NULL, 'f'},
		{"number_nodes", required_argument, NULL, 'n'},
		{"scheduler_port", required_argument, NULL, 'p'},
		{"help", no_argument, NULL, 'h'},
		{NULL, no_argument, NULL, 0}
	};

	struct opt_arguments {
		bool config_file;
		char config_path [128];
		uint16_t scheduler_port;
		uint8_t number_nodes;
		bool need_help;
		bool not_config_file;

		opt_arguments () {
			need_help = config_file = not_config_file = false;
			bzero (&config_path, 128);
			scheduler_port = 0;
			number_nodes = 0;
		}
	} opt;

	const char* opt_help = 
		"a \n"
		"b \n" 
		"c \n"
		"Compiled at:" __DATE__ "\n";

protect:
	//Aggregated classes
	Server server;
	Parser read_ini;

	FILE* input;

	pthread_t logger;
	pthread_t sender;
	pthread_attr_t logger_attr;
	pthread_attr_t sender_attr;

	bool get_args (int, char**);
	void* logger_function (void* arg);
	void* sender_function (void* arg);

	public:
	Scheduler (int, char**);

	bool start ();
	bool quit ();

	//Method to be overrided with hash, bdema...
	int selectServer (void);

};

#endif
