#ifndef __QUERY_H_
#define __QUERY_H_

#include <packet/packet.hh>
#include <sys/time.h>

class Query: public Packet {
	private:
		uint64_t fid, offset, length;
		struct timeval scheduledDate;
		struct timeval startDate;
		struct timeval finishedDate;

	public:
		//constructor & destructor
		Query (): Packet (QUERY) {}
		Query (const Packet&);
		Query (const Query&);

		bool operator== (const Packet&) const;
		bool operator!= (const Packet&) const;
		bool operator< (const Packet&) const;
		bool operator> (const Packet&) const;

		//setter
		void setStartDate ();
		void setFinishedDate ();

		//getter
		uint64_t getWaitTime ();
		uint64_t getExecTime ();

} __attribute__((aligned));

#endif
