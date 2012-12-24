#ifndef __NODE_H_
#define __NODE_H_

/********************************************
		This file contains the node class definition
		this class should be executed in each node
		server 
	********************************************/

//Classes
#include <macros.h>
#include <server.hh>
#include <packet/packet.hh>
#include <packet/query.hh>
#include <packet/update.hh>
#include <packet/stat.hh>

//standard libraries
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <assert.h>
#include <queue>

class Node {
	private:
		//To act as a server
		Server* attributes;
		Client* scheduler;
		Client* neighbor;

		static LRUcache cache;
		static queue<Query*> buffer_local;
		static queue<Query*> buffer_neighbor;

		int lower_bound, upper_bound;
		struct timeval start, end;;

		pthread_t neighbor;	
		pthread_t scheduler;	
		pthread_t worker;	
		pthread_mutex_t empty;

		static bool die_thread;

		static	uint32_t queryRecieves = 0, queryProcessed = 0;
		static	uint64_t hitCount = 0, missCount = 0;
		static	uint64_t TotalExecTime = 0, TotalWaitTime = 0;
		static	uint64_t inshiftedQueries = 0, outShiftedQueries = 0;

		//Threads functions
		void tneighborFunction(void*);
		void tschedulerFunction(void*);
		void tworkerFunction(void*);

		bool processQuery();
		bool swiftQuery();
		bool schedulerQuery();

	public:
		Node();
		~Node();

		bool init();	
		bool process();
};

#endif
