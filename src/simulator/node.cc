#include <node.hh>

using std::cout;
using std::cerr;
using std::endl;

// ------------------------------------------------------ //
//        STATIC MEMBER VARIABLES                         //
// ------------------------------------------------------ //

Server* Node::attributes;              //! Read from the neighbor
Client* Node::scheduler;               //! comm with the scheduler
Client* Node::neighbor;                //! shift queries

lru_map<int, int>* Node::cache;
queue<Query> Node::buffer_local;
queue<Query*> Node::buffer_neighbor;

bool Node::die_thread;
uint32_t Node::queryRecieves; 
uint32_t Node::queryProcessed;
uint64_t Node::hitCount;
uint64_t Node::missCount;
uint64_t Node::TotalExecTime; 
uint64_t Node::TotalWaitTime;
uint64_t Node::inshiftedQueries;
uint64_t Node::outShiftedQueries;

int Node::bound_lower;
int Node::bound_upper;

struct timeval Node::time_start;
struct timeval Node::time_end;

pthread_t Node::thread_neighbor;
pthread_t Node::thread_scheduler;
pthread_t Node::thread_worker;

pthread_mutex_t Node::lock_scheduler_empty;
pthread_mutex_t Node::lock_neighbor_empty;

pthread_cond_t Node::Node::cond_scheduler;
pthread_cond_t Node::cond_neighbor;

// ------------------------------------------------------ //
//               MEMBER METHODS                           //
// ------------------------------------------------------ //

Node::Node() {
	attributes = new Server (PORT);
	scheduler = new Client (PORT, HOST);

 attributes->setUp();
 attributes->bind();
 
 scheduler->setUp();
 
 Node::cache = new lru_map<int, int> (10000);
	Node::die_thread = false;

#ifdef DEBUG
 printf ("Done initialization\n");
#endif
}

Node::~Node() {
 shutdown();
}

bool Node::init () {
 try { 
  if (0 != pthread_mutex_lock (&lock_scheduler_empty))
   throw Exception ("Pthread_mutex");

  if (0 != pthread_mutex_lock (&lock_neighbor_empty))
   throw Exception ("Pthread_mutex");

  scheduler->connect();

 } catch (Socket::Exception& e) {
  cerr << e << endl << e.backtrace() << endl;
  return false;

 } catch (Exception& e) {
  cerr << e << endl; 
  return false;
 }
 return true;
}

void Node::shutdown() {
#ifdef DEBUG
 printf ("Starting destructor\n");
#endif

	pthread_mutex_unlock (&lock_scheduler_empty);	
	pthread_mutex_unlock (&lock_neighbor_empty);	

	delete attributes;
	delete scheduler;
	delete neighbor;
 delete cache;

#ifdef DEBUG
 printf ("FINISH\n");
#endif
}

bool Node::start () {
	pthread_create (&thread_scheduler, NULL, &thread_scheduler_fun , this);
	pthread_create (&thread_worker,    NULL, &thread_worker_fun,     this);
	pthread_create (&thread_neighbor,  NULL, &thread_neighbor_fun,   this);

	pthread_join (thread_scheduler, NULL);
	pthread_join (thread_neighbor,  NULL);
	pthread_join (thread_worker,    NULL);

 return true;
}

// ------------------------------------------------------ //
//              SHIFTING QUERIES SIDE                     //
// ------------------------------------------------------ //

//ToDo
void* Node::thread_neighbor_fun (void* args) {
 pthread_exit (EXIT_SUCCESS);
 return NULL; 
}

// ------------------------------------------------------ //
//              RECIEVING QUERIES SIDE                    //
// ------------------------------------------------------ //

void* Node::thread_scheduler_fun (void* args) { 
 pthread_exit (EXIT_SUCCESS);
 Node* node = static_cast<Node*> (args);

 socket_stream ss = node->scheduler->connect();
 while (true) {
  try {
   switch (ss.getType()) {
    case QUERY: node->buffer_local.push (ss.recieve<Query>());  break;
    case INFO:  /*node->inform_scheduler();*/                   break;
    case QUIT:  node->shutdown();                               break;
    default:    throw Exception ("Unknown message" + ss.getType());
   }
  } catch (Exception& e) {
   //Some routine to reset sockets and inform 
   //To scheduler some miss-wrong message and 
   //recieve back
  }
 }
 pthread_exit (EXIT_SUCCESS);
}

//void Node::prepare_query (void) {
 //buffer_local.push (ss.recieve<query>());
//}

// ------------------------------------------------------ //
//                PROCESSING QUERY SIDE                   //
// ------------------------------------------------------ //

void* Node::thread_worker_fun (void* args) {
 pthread_exit (EXIT_SUCCESS);
 Node* node = static_cast<Node*> (args);

 while (node->die_thread != true || node->buffer_local.empty() != true) {
  while (node->buffer_local.empty() && !node->die_thread) 
   pthread_mutex_lock (&node->lock_scheduler_empty);
  if (node->die_thread)
   continue;

  Query* query = &node->buffer_local.front ();

  if (!node->query_process (query)) {
   node->buffer_neighbor.push (query);
   node->buffer_local.pop ();  

  } else {
   node->buffer_local.pop ();
  }
  delete query;
 }
 pthread_exit (EXIT_SUCCESS);
}

bool Node::query_process (Query* query) {
 assert (query != NULL);

 bool result;
 query->setStartDate();
 //result = cache.match (static_cast<packet*> (query), hitmiss_count);
 query->setFinishedDate();

 queryProcessed++;
 TotalExecTime += query->getExecTime();
 TotalWaitTime += query->getWaitTime();
 return result;
}

// ------------------------------------------------------ //
//int main (int argc, char** argv) {
//
//return EXIT_SUCCESS;
//}
