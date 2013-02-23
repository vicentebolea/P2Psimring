#ifndef __QUERY_H_
#define __QUERY_H_

#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>


//! :TODO:
//enum query_type {
	//GET    = 0x0,
	//READ   = 0x1,
	//WRITE  = 0x2,
	//REMOVE = 0x4
//};

class Query {
	private:
		uint64_t fid, offset, length;
		struct timeval scheduledDate;
		struct timeval startDate;
		struct timeval finishedDate;

	public:
		//constructor & destructor
		Query () {}
		Query (const Query&);

		//bool operator== (const Packet&) const;
		//bool operator!= (const Packet&) const;
		//bool operator< (const Packet&) const;
		//bool operator> (const Packet&) const;

		//setter
		void setStartDate ();
		void setFinishedDate ();

		//getter
		uint64_t getWaitTime ();
		uint64_t getExecTime ();

} __attribute__((aligned));

#endif
