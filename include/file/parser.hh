#ifndef __PARSER_HH_
#define __PARSER_HH_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <minIni.h>

#include <exception.hh>

using std::cerr;
using std::endl;

/************************************************
 Example ini file:

 [network]
	 number_servers:      12
	 scheduler_address:   10.0.0.1
	 port:                1999
	
 [storage]	
  disk_page_size:      4K
	 cache_size:          1G
	 garbage_file:        /mnt/garbage/garbage1.trash

 # Options regarding output
	output_type:         sqlite|file
	log_file:            ./log/default_log.log

	*************************************************/


class Parser {
	public:
		class Exception: public ::Exception {
			public:
				Exception (const char* in) : ::Exception (__FILE__,in) {} 
		};

	protected:
		minIni*	 file_ini;

	public:
		Parser () {}
		Parser (const char* path) {
			open (path);
		}

		~Parser () {
			delete file_ini;
		}

		Parser (const char* path) {
			try {
				file_ini = new minIni (path);

			} catch (Exception& e) {
				cerr << e << endl;
			}
		}

		uint64_t get_value_of (const char* section, 
				const char* attribute,
				string str = string("NaN")) 
		{
			uint64_t out = (uint64_t)EXIT_SUCCESS;
			try {
				if (str == string("NaN")) {
					out = file_ini->getl (section, attribute, -1);
					if (out == -1)
						throw Exception ("Key not found");

				} else {
					str = file_ini->gets (section, attribute, "NAN");
					if (str == string("NAN"))
						throw Exception ("KEY not found");
				}
			} catch (Exception& e) {
				cerr << e << endl;
				exit (EXIT_FAILURE);
			}
			return out;
		}

		void close () {
			delete file_ini;
		}
};

#endif
