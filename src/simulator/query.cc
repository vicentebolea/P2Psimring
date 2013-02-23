#include <query.hh>

static uint64_t timediff (struct timeval *end_time, struct timeval *start_time) {
	return (end_time->tv_usec + 1000000 * end_time->tv_sec) 
		- (start_time->tv_usec + 1000000 * start_time->tv_sec);
}

Query::Query (const Query& that) {
  scheduledDate = that.scheduledDate;
  startDate = that.startDate;
  finishedDate = that.finishedDate;
}

void Query::setStartDate() {
  gettimeofday (&startDate, NULL);
}

void Query::setFinishedDate() {
  gettimeofday (&finishedDate, NULL);
}

uint64_t Query::getWaitTime() {
  return timediff (&startDate, &scheduledDate);
}

uint64_t Query::getExecTime() {
  return timediff (&finishedDate, &startDate);
}
