AUTHOR                                         {#mainpage}
======
 - __AUTHOR:__      [Vicente Adolfo Bolea Sanchez] [me]
 - __EMAIL:__       vicente.bolea@gmail.com
 - __INSTITUTION:__ [DICL laboratory] [dicl] at UNIST.

- - -

PRELIMINARIES                                    
=============

This is an experiment for indexing data in a distribute
system. The model of this experiment is based on hybrid
peer-to-peer model, with a central scheduler and a set of
nodes.

These nodes are interconnected each others and connected
with the scheduler.

The porpose of this experiment is to run differents
algorithms in a distributed system using differents
technics.

Structure 
---------
 - bin/
 - config.ini
 - docs/
 - include/
 - lib/
 - Makefile
 - Makefile.vars
 - prototipes/
 - README.md
 - src/
 - tests/

7 directories, 5 files

Code 
----
The source code is stored in [github] [gh].


REQUIREMENTS
============
 - The source code is coded in *C++98* for linux with GNU
			extensions, using GCC, e.g., *GNU++98*. 

 - You will need in each node an enough big file of garbage
			to test the LRU cache throughput. the size of this file
			should be as big as the domain of the data set.

 - A bash terminal.


USAGE 
=====
To run the experiment you need to setup some variable in
Makefile.vars such as: number of servers, port, host, etc...
Then compile and execute the launcher script located in the
binary folder.
Here are the script's flags:

> launcher HELP/KILL/BDEMA/HASH/P2P

To add new algorithm you need to inheritance from scheduler
class and override "selector" method and add whatever you
need for your algorithm.

DATA STRUCTURES 
===============

Each node has a __LRU cache__ which store the retrieved data
in the previous operations. This __LRU cache__ is implements in
some way where all the operations have __O(1)__ time
complexity in the best case.

At the same time each node has two queues used as buffers
among the differents threads. The first one is used by the
reciever thread and the different.

Also the node class use a __mesa monitor__ to synchronize
the access of this queue.

ALGORITHMS 
==========
ToDo

RATIONALE  
=========
ToDo

<!-- Links -->
[dicl]:  http://dicl.unist.ac.kr
[me]:    https://github.com/vicentebolea
[gh]:    https://github.com/vicentebolea/p2p_distributed
