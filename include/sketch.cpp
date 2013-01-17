		/** 
		 * @enum Type	
			* @brief Differents types which indicate the porpose of
			* the packet
			*/
		enum Type {
			QUERY  = 000, // 0000
			UPDATE = 001, // 0001
			STATS  = 002, // 0010
			INFO   = 004, // 0100
			QUIT   = 010  // 1000
		} __attribute__((packed()));


