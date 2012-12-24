#ifndef __PACKET_H_
#define __PACKET_H_

/******************************************************
		Packet structure:
		~~~~~~~~~~~~~~~~~

		|--------|------------------------------------|
		| 1 Byte |          At most 160 bits          |
		|--------|------------------------------------|
		|  Type  |      Query / Update / stats        |
		|--------|------------------------------------|

		The first byte will indicate the type of the packet, 
		it can be:
		- Query, see at query.{hh,cc}
		- Update, see at update.{hh,cc}
		- Stats, see at stats.{hh,cc}
		- Quit
		- Info 

		This two last types has not class defined since they
		dont need aditional information.
	*******************************************************/

/**	Differents types which indicate
	*	the porpose of the packet
	*/
enum Type {
	query  = 000, // 0000
	update = 001, // 0001
	stats  = 002, // 0010
	quit   = 004, // 0100
	info   = 010  // 1000
} __attribute__((packed(1)));

/**	This Class will be inherited for each 
	*	kind of packet
	*/
class Packet {
	private:
		Type type; 

	public:

		Packet (Type type) {
			type = type;
		}

		Packet (const Packet& packet) {
			type = packet.type;
		}

		const Packet& operator= (const Packet& packet) {
			type = packet.type;
			return *this;
		}

		Type getType () const {
			return type;
		}
};

#endif
