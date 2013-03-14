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
#pragma once
#ifndef __NODE_H_
#define __NODE_H_

#define PORT 1234
#define HOST "locahost"

//Related classes
#include <messages.hh>
#include <query.hh>

//project's libraries
#include <network/server.hh>
#include <network/client.hh>

#include <lru/lru_map.hh>

//UNIX libraries
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//standard libraries
#include <iostream>
#include <assert.h>
#include <queue>
#include <stdint.h>
#include <inttypes.h>

using namespace tcp_socket;
using std::queue;

class Node {
 protected:
  //---------- static variables ----------//
  static Server* attributes;
  static Client* scheduler;
  static Client* neighbor;

  static lru_map<int, int>* cache;
  static queue<Query> buffer_local;
  static queue<Query*> buffer_neighbor;

  static bool die_thread;
  static uint32_t queryRecieves; 
  static uint32_t queryProcessed;
  static uint64_t hitCount;
  static uint64_t missCount;
  static uint64_t TotalExecTime; 
  static uint64_t TotalWaitTime;
  static uint64_t inshiftedQueries;
  static uint64_t outShiftedQueries;

  static int bound_lower, bound_upper;
  static struct timeval time_start, time_end;

  static pthread_t thread_neighbor;
  static pthread_t thread_scheduler;
  static pthread_t thread_worker;

  static pthread_mutex_t lock_scheduler_empty;
  static pthread_mutex_t lock_neighbor_empty;
  static pthread_cond_t cond_scheduler;
  static pthread_cond_t cond_neighbor;

  //---------- thread functions ----------//
  static void* thread_scheduler_fun (void*);
  static void* thread_neighbor_fun (void*);
  static void* thread_worker_fun (void*);

  //---------- Query functions ----------//
//void query_prepare   (Query*);
  bool query_process   (Query*);
//bool query_shift     (Query*);
//bool query_scheduler (Query*);

  void shutdown (void);

  Node (const Node&);
  const Node& operator= (const Node&);

 public:
  Node ();
  ~Node ();

  bool init (void);
  bool start (void);

  friend ostream& operator<< (ostream&, const Node&);
};

#endif
