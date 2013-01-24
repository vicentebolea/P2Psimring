#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <macros.h>
#define __VER__ "0.1"

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
	const char* optstring = "c:i:n:p:h";
	const char opt_help[] = 
  "Usage: scheduler [OPTION]...                         \n"
	 "-----------------------------------------------------\n" 
		"Options:                                             \n" 
	 " -c, --config <file>      Config file path           \n"
	 " -i, --input <file>       Input query file path, if  \n"
	 "                           it is not defined it will \n"
	 "                           read the standart input.  \n"
	 "                                                     \n"
	 " -n, --nnodes <number>    Number of nodes            \n"
	 " -p, --port <number>      Port number                \n"
	 " -h, --help               Show this dialog           \n" 
	 "-----------------------------------------------------\n" 
  "Examples:                                            \n"
	 "           scheduler                                 \n"
	 "           scheduler -c config.cfg                   \n"
	 "           scheduler -i in.input -n 100 -p 1234      \n"
	 "-----------------------------------------------------\n"
	 "                          Compiled at : " __DATE__  "\n"
	 "                          Version     : " __VER__   "\n"
	 "-----------------------------------------------------\n";

	const struct option opt_long[] = 
	{
		{"config", optional_argument, NULL, 'c'},
		{"input",  required_argument, NULL, 'i'},
		{"nnodes", required_argument, NULL, 'n'},
		{"port",   required_argument, NULL, 'p'},
		{"help",   no_argument,       NULL, 'h'},
		{NULL,     no_argument,       NULL,   0}
	};

	struct opt_arguments {
		bool need_config;
		bool need_input;
		bool need_help;

		char config_path [128];
		uint16_t scheduler_port;
		uint8_t number_nodes;

		opt_arguments () {
			need_input =	need_help = need_config = false;
			strncpy (config_path, default_config_path, 128);
			scheduler_port = 0;
			number_nodes = 0;
		}
	} opt;


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

	bool start (void);
	bool quit (void);

	//Method to be overrided with hash, bdema...
	int selectServer (void);

};

#endif
