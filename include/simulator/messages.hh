#ifndef __MESSAGES_HH_
#define __MESSAGES_HH_

enum msg_table {
	QUERY = 0x0,
 EXIT  = 0x1,
	PING  = 0x2,
	INFO  = 0x4,	
	STAT  = 0x8,
	UPDATE= 0x10,
	// ...
	QUIT  = 0xFF
};

class Update {
	public:
		int lower_bound, upper_bound;
		char neighbor_ip [32];

		Update() {}
};

#endif
