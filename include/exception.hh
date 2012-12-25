#ifndef __EXCEPTION_HH_
#define __EXCEPTION_HH_

#include <iostream>
#include <exception>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//UNIX dependent error libraries
#include <errno.h>
#include <error.h>
#include <execinfo.h>

#define pot(x) 1<<(x)

using std::string;
using std::ostream;
using std::exception;

class Exception: public exception {
	protected:
		char message [128]; // enought for log message 

	public:

	Exception () {
		snprintf (message, 128, "EXCEPTION::");
	}
	Exception (const char* in) {
		snprintf (message, 128, "EXCEPTION: %s", in);
	}

	Exception (const string& in) {
		snprintf (message, 128, "EXCEPTION: %s", in.c_str());
	}

	~Exception() throw() {}

	Exception (const Exception& e) {
		strncpy (message, e.message, pot(7));
	}

	const char* what () const throw() {
		return message;
	}

	const char* backTrace () const {
		size_t size;
		void *trace[1<<6];
		char **strings;
		static char bt_output [(1<<10)];
		
		size = backtrace (trace, 1<<6);
		strings = backtrace_symbols (trace, 1<<6);
		
		strcpy (bt_output, "=====BACKTRACE=====\n");
		for (size_t i = 0; i < size; i++) {
			strncat (bt_output, strings[i], 1<<8);
			strncat (bt_output, "\n", 1<<8);
		}
		free (strings);

		return bt_output;
	}

	friend ostream& operator<< (ostream& in, Exception& e) {
		in << e.message;
		return in;
	}
};

class NetException: public Exception {
	public:

		NetException (const char* in): Exception() {
			char tmp [100], hostn[100];

			gethostname (hostn, 100);
			snprintf (tmp, 100,
			 "NETWORKING [ERRNO: %i] [STR: %s] [REASON: %s] [HOSTNAME: %s]",
			  errno, strerror(errno), in, hostn);
			strncat (message, tmp, 100);
		}
};

//class LinkedListException {
//	public:
//		LinkedListException (const char* in) {
//			char tmp [1<<7], hostn [1<<7];
//			gethostname (hostn, 100);
//			snprintf (tmp, 1<<7, "LINKEDLIST [ERRNO: %i] [STR: %s] [HOSTNAME: %s]",
//				errno, strerror(errno), hostn);
//			strncat (message, tmp, 1<<7);
//		}
//
//	private:
//};

#endif
