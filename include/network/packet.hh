/**
	* @class Packet
	* @name Packet
	* @see Query Stats Server Client Client_e
	*
	* @section DESCRIPTION
	*	@subsection "Packet structure"
	* @verbatim
 *
	*	|--------|------------------------------------|
	*	| 1 Byte |          Message                   |
	*	|--------|------------------------------------|
	*	|  Type  |      Query / Update / stats        |
	*	|--------|------------------------------------|
 *
	* @endverbatim
	*
	*	The first byte will indicate the type of the packet, 
	*	it can be:
	*	- QUERY, see at query.{hh,cc}
	*	- UPDATE, see at update.{hh,cc}
	*	- STATS, see at stats.{hh,cc}
	*	- QUIT
	*	- INFO 
 *
	*	This two last types has not class defined since they
	*	dont need aditional information.
	*/

#ifndef __PACKET_H_
#define __PACKET_H_

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

namespace tcp_socket {
	template <class Message>
		class Packet {
			protected:
				uint8_t type; 
				Message message;

			public:

				//Packet (uint8_t t, const Message& m, size_t n): type(t) {
				//Message tmp [n];
				//for (size_t i = 0; i < n; i++)
				//tmp[i] = m[i];
				//}
				Packet (uint8_t t, const Message& m) : type(t), message(m) {}
				Packet (uint8_t t) : type(t) {}
				Packet (const Packet& packet) {
					type = packet.type;
					message = packet.message;
				}

				const Packet& operator= (const Packet& packet) {
					type = packet.type;
					message = packet.message;
					return *this;
				}

				uint8_t getType () const {
					return type;
				}

				const Message& getMessage() {
					return message;
				}

				size_t getSize() const {
					return (sizeof(uint8_t) + sizeof(Message));
				}
		};
}

#endif
