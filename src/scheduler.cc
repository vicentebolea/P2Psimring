#include <scheduler.h>

Scheduler::Scheduler(int argc, char** argv) {
	getopts (argc, argv, "");
}

void Scheduler::sender_function(void* arg) {

}

void Scheduler::logger_function(void* arg) {

}

bool Scheduler::start() {
	pthread_create (sender, NULL, sender_function, NULL);
	pthread_create (logger, NULL, logger_function, NULL);


}

bool Scheduler::quit() {


}
