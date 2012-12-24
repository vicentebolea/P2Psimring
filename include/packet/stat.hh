#ifndef __STAT_H_
#define __STAT_H_

#include <packet/packet.hh>
#include <inttypes.h>
#include <stdint.h>

/*
	*
	*/
struct Stat: public Packet {
	uint32_t queryRecieves = 0, queryProcessed = 0;
	uint64_t hitCount = 0, missCount = 0;
	uint64_t TotalExecTime = 0, TotalWaitTime = 0;

	Stat (uint32_t qr, uint32_t qp, uint64_t hc, uint64_t mc, 
			uint64_t tet, uint64_t twt) : Packet (stats) {

		queryRecieves = qr;									
		queryProcessed = qp;									
		hitCount = hc;
		missCount = mc;
		TotalExecTime = tet;
		TotalWaitTime = twt;
	}
};

#endif
