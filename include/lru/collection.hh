/*
 * @class Collection
 * Simple interface of containers.
 * Expecify what it should do
 *
 */
#ifndef __COLLECTION_INL_
#define __COLLECTION_INL_

#include <stddef.h>

class Collection {
 protected:
  size_t size;

 public:
  Collection () : size(0) {}
  virtual ~Collection () {}

  inline size_t getSize () const { return size; }
  inline bool empty () const { return size == 0 ? true: false; }
};

#endif
