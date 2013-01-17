#include <unittest++/UnitTest++.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <packet.hh>

SUITE (query) {
 TEST (constructor) {
  Packet packet (Packet::QUIT);
  CHECK_EQUAL (packet.getType(), Packet::QUIT);
 }

 TEST (Inheritance_constructor) {
  Packet& packet = new Query ();
  CHECK_EQUAL (packet.getType(), Packet::QUIT);
 }

 TEST (measuring_time) {


 }
}

int main () {
	return UnitTest::RunAllTests();
}
