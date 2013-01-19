#include <unittest++/UnitTest++.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <packet.hh>

using namespace tcp_socket;

SUITE (packet_suite) {
 TEST (constructor) {
  Packet<int> packet (1, 10);
  CHECK_EQUAL (packet.getType(), 1);
  CHECK_EQUAL (packet.getMessage(), 10);
  CHECK_EQUAL (packet.getSize(), (size_t)5);
 }
}

int main () {
	return UnitTest::RunAllTests();
}

