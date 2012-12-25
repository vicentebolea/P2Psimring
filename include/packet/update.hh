#ifndef __UPDATE_H_
#define __UPDATE_H_

#include <packet/packet.hh>

class Update: public Packet {
	public:
		int lower_bound, upper_bound;
		char neighbor_ip [32];

		Update(): Packet (UPDATE) {}
};

#endif
