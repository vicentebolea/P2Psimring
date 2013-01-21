#include <node.hh>

using namespace std;

Node::Node() {
	attributes = new Server (PORT);
	scheduler = new Client (PORT, HOST);

 attributes.setUp();
 attributes.bind();
 
 scheduler.setUp();

	empty = PTHREAD_MUTEX_INTIALIZER;
	die_thread = false;
}

Node::~Node() {
 shutdown();
}

void Node::shutdown() {
	pthread_mutex_unlock (&lock_scheduler_empty);	
	pthread_mutex_unlock (&lock_neighbor_empty);	

	delete attributes;
	delete scheduler;
	delete neighbor;
}

bool Node::init () {
	pthread_mutex_lock (&lock_scheduler_empty);	
	pthread_mutex_lock (&lock_neighbor_empty);	

	scheduler.connect();
 return true;
}

bool Node::start () {
	pthread_create (scheduler, NULL, tschedulerFunction, NULL);
	pthread_create (worker, NULL, tworkerFunction, NULL);
	pthread_create (neighbor, NULL, tneighborFunction, NULL);

	pthread_join (scheduler, NULL);
	pthread_join (neighbor, NULL);
	pthread_join (worker, NULL);

 return true;
}

// ------------------------------------------------------ //
// Scheduler side                                         //
// ------------------------------------------------------ //

//ToDo
void Node::tneighborFunction (void* args) {}

// ------------------------------------------------------ //
//              RECIEVING QUERIES SIDE                    //
// ------------------------------------------------------ //

void Node::tschedulerFunction (void* args) { 

 while (true) {
  try {
   switch (ss.getType()) {
    case QUERY: prepare_query();    break;
    case INFO:  inform_scheduler(); break;
    case QUIT:  shutdown();         break;
    default:    throw Exception ("Unknown message");
   }
  } catch (Exception& e) {
   //Some routine to reset sockets and inform 
   //To scheduler some miss-wrong message and 
   //recieve back
  }
 }
}

void Node::prepare_query() {
 buffer_local.push (ss.recieve<query>());
}

// ------------------------------------------------------ //
//                PROCESSING QUERY SIDE                   //
// ------------------------------------------------------ //

void Node::tworkerFunction (void* args) {

 uint64_t* hitmiss_count[2] = {&hitCount, &missCount};

 while (die_thread != true || Queue.empty() != true) {
  while (Queue.empty() && !die_thread) 
   pthread_mutex_lock (&empty);
  if (die_thread)
   continue;

  Query* query = buffer_local.front();

  if (!processQuery(query)) {
   buffer_neighbor.push(query);
   buffer_local.pop();

  } else {
   buffer_local.pop();
  }
  delete query;
 }
 pthread_exit (EXIT_SUCCESS);
}

bool Node::processQuery(Query* query) {
 assert (query != NULL);

 bool result;
 query->setStartDate();
 result = cache.match (static_cast<packet*> (query), hitmiss_count);
 query->setFinishedDate();

 queryProcessed++;
 TotalExecTime += query->getExecTime();
 TotalWaitTime += query->getWaitTime();
 return result;
}

// ------------------------------------------------------ //
int main (int argc, char** argv) {

 return EXIT_SUCCESS;
}
