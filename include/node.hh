/**
 * @class Node
 * 
 * SINGLETON PATTERN
 * This file contains the node class definition
 * this class should be executed in each node
 * server.
 *
 * @section EXAMPLE
 *  - Dataset      = (1, 5000]
 *  - Cache size   = 100
 *  - Number nodes = 5
 *
 * @verbatim 
 *  0  .. 1000 .. 2000 .. 3000 .. 4000 .. 5000
 *  |-------|-------|-------|-------|-------|
 *  |Node 1 |Node 2 |Node 3 | Node 4|Node 5 |
 *  |-------|-------|-------|-------|-------|
 *    100e    100e    100e    100e    100e
 * @endverbatim
 */

#ifndef __NODE_H_
#define __NODE_H_

//Classes
#include <macros.h>
#include <network/server.hh>
#include <network/client.hh>

//standard libraries
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <assert.h>
#include <queue>

class Node {
 protected:
  //To act as a server
  Server* attributes;
  Client* scheduler;
  Client* neighbor;

  static lru_map cache;
  static queue<Query*> buffer_local;
  static queue<Query*> buffer_neighbor;

  int lower_bound, upper_bound;
  struct timeval start, end;;

  pthread_t neighbor;
  pthread_t scheduler;
  pthread_t worker;

  pthread_mutex_t lock_scheduler_empty;
  pthread_mutex_t lock_neighbor_empty;
  pthread_cond_t cond_scheduler;
  pthread_cond_t cond_neighbor;

  static bool die_thread;

  static uint32_t queryRecieves = 0, queryProcessed = 0;
  static uint64_t hitCount = 0, missCount = 0;
  static uint64_t TotalExecTime = 0, TotalWaitTime = 0;
  static uint64_t inshiftedQueries = 0, outShiftedQueries = 0;

  //Threads functions
  void* tneighborFunction (void*);
  void* tschedulerFunction (void*);
  void* tworkerFunction (void*);

  bool processQuery (void);
  bool swiftQuery (void);
  bool schedulerQuery (void);

 protected:
  Node();
  ~Node();

 public:
  const Node& getInstance () {
   static Node singleton ();
   return singleton;
  }
  bool init ();
  bool start ();

  friend ostream& operator<< (ostream&, const Node&);
};

#endif
