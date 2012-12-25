#ifndef __STAT_H_
#define __STAT_H_

#include <packet/packet.hh>
#include <inttypes.h>
#include <stdint.h>

/*
 *
 */
struct Stat: public Packet {
	uint32_t queryRecieves;
	uint32_t queryProcessed;
	uint64_t hitCount;
	uint64_t missCount;
	uint64_t TotalExecTime;
	uint64_t TotalWaitTime;

	Stat () : Packet (STATS) {}
	Stat 
		(
			uint32_t queryRecieves,
			uint32_t queryProcessed,
			uint64_t hitCount,
			uint64_t missCount,
			uint64_t TotalExecTime,
			uint64_t TotalWaitTime
		) : Packet (STATS) {

			this->queryRecieves  = queryRecieves;
			this->queryProcessed = queryProcessed;	
			this->hitCount       = hitCount;
			this->missCount      = missCount;
			this->TotalExecTime  = TotalExecTime;
			this->TotalWaitTime  = TotalWaitTime;
		}
};

#endif
