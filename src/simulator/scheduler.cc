#include <scheduler.hh>

/*
 *
	*/
Scheduler::Scheduler (int argc, char** argv) {
	bool read_ini_file = get_args (argc, argv);

	pthread_attr_set_detach (&logger_attr, PTHREAD_DETACH_JOINABLE);
	pthread_attr_set_detach (&sender_attr, PTHREAD_DETACH_JOINABLE);

	//In case that we want to use the config file
	if (opt.need_help) {
		printf ("%s", opt_help); 
		exit (EXIT_SUCCESS);

	} else if (read_ini_file) {

		if (!opt.need_config)
			read_ini.open (default_config_path);
		else
			read_ini.open (opt.config_path);

		opt.scheduler_port = 
		 read_ini.get_value_of ("scheduler", "scheduler_port");

		opt.number_nodes = 
		 read_ini.get_value_of ("scheduler", "number_nodes");

		read_init.close ();
	}
}


/* 
 * This method read the arguments passed in the
	* command line and fill the input symbol table
	*/
bool Scheduler::get_args (int argc, char** argv) {
	char out = getopts_long (argc, argv, optstring, opt_long, NULL);

	while (out =! -1) {
		switch (out) {
			case 'n': /* Number of nodes */ 
			 opt.number_nodes = atoi (optarg); 
				opt.config_file = false;
				break;

			case 'p': /* Port number */
			 opt.scheduler_port = atoi (optarg);
				opt.config_file = false;
				break;

			case 'f': /* Ini config file path */
			 strncpy (opt.config_path, optarg, 128);
				opt.config_file = true;
				break;

			case 'h': /* help... */
			 need_help = true;
				break;

			default: 
				opt.config_file = true;
				opt.not_config_file = true;
				break;
		}
		out = getopts_long (argc, argv, optstring, opt_long NULL);
	}
	return opt.config_file;
}


void Scheduler::sender_function (void* arg) {
}

void Scheduler::logger_function (void* arg) {
}

bool Scheduler::start () {
	pthread_create (sender, NULL, sender_function, NULL);
	pthread_create (logger, NULL, logger_function, NULL);
}

bool Scheduler::quit () {
}
