#include <node.hh>

using namespace std;

Node::Node() {
	attributes = new Server (PORT, NSERVERS);
	scheduler = new Client (HOST);

	empty = PTHREAD_MUTEX_INTIALIZER;
	die_thread = false;
}

Node::~Node() {
	pthread_mutex_unlock (&empty);	
	delete attributes;
	delete scheduler;
	delete neighbor;
}

bool Node::init() {
	scheduler.connect();
}

bool Node::process() {
	pthread_mutex_lock (&empty);

	pthread_create (scheduler, NULL, tschedulerFunction, NULL);
	pthread_create (worker, NULL, tworkerFunction, NULL);
	pthread_create (neighbor, NULL, tneighborFunction, NULL);

	pthread_join (scheduler, NULL);
	pthread_join (neighbor, NULL);
	pthread_join (worker, NULL);
}

//ToDo
void Node::tneighborFunction(void *args) {}

void Node::tschedulerFunction (void *args) {



}

void Node::tworkerFunction (void *args) {

	uint64_t* hitmiss_count[2] = {&hitCount, &missCount};

	while (die_thread != true || Queue.empty() != true) {
		while (Queue.empty() && die_thread != true) 
			pthread_mutex_lock (&empty);
		if (die_thread == true)
			continue;

		Query* query = buffer_local.front();

		if (processQuery(query) == false) {
			buffer_neighbor.push(query);
			buffer_local.pop();

		} else {
			buffer_local.pop();
			delete query;
		}
	}
	pthread_exit (EXIT_SUCCESS);
}

bool Node::processQuery(Query* query) {
	assert (query != NULL);

	bool result;
	query->setStartDate();
	result = setCache.match (static_cast<packet*> (query), hitmiss_count);
	query->setFinishedDate();

	queryProcessed++;
	TotalExecTime += query->getExecTime();
	TotalWaitTime += query->getWaitTime();
	return result;
}

int main (int argc, char** argv) {



	return EXIT_SUCCESS;
}
