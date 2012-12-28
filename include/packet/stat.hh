#ifndef __STAT_H_
#define __STAT_H_

#include <inttypes.h>
#include <stdint.h>

#include <packet/packet.hh>

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

	Stat (const Stat& that) : Packet (STATS) {
		this->queryRecieves  = that.queryRecieves;
		this->queryProcessed = that.queryProcessed;
		this->hitCount       = that.hitCount;
		this->missCount      = that.missCount;
		this->TotalExecTime  = that.TotalExecTime;
		this->TotalWaitTime  = that.TotalWaitTime;
	}

	const Stat& operator= (const Stat& that) {
		this->queryRecieves  = that.queryRecieves;
		this->queryProcessed = that.queryProcessed;
		this->hitCount       = that.hitCount;
		this->missCount      = that.missCount;
		this->TotalExecTime  = that.TotalExecTime;
		this->TotalWaitTime  = that.TotalWaitTime;
		return *this;
	}

	const Stat& operator+= (const Stat& that) {
		this->queryRecieves  += that.queryRecieves;
		this->queryProcessed += that.queryProcessed;
		this->hitCount       += that.hitCount;
		this->missCount      += that.missCount;
		this->TotalExecTime  += that.TotalExecTime;
		this->TotalWaitTime  += that.TotalWaitTime;
		return *this;
	}
};

#endif
