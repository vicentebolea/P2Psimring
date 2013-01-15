/** ***************************************************//**
 * @author Vicente Adolfo Bolea Sanchez
 *         <vicente.bolea@gmail.com>,
 *         <vicente@unist.ac.kr>
 *
 * @class  dictionary
 * @brief  abstract class for dictionary ADT
/** ***************************************************//**
 *
 */

#ifndef __DICTIONARY_HH_
#define __DICTIONARY_HH_

#include <algorithm>
#include <stdexcept>
#include <stddef.h>

using std::out_of_range;

template <class key, class value>
class dictionary {

 public:
  dictionary () : size (0) {}
  virtual ~dictionary ();

  virtual void insert (const key& k, const value& v) = 0;
  virtual void remove (const key& k) = 0;
  virtual const value& lookup (const key& k)
   throw (out_of_range) = 0;

  size_t size () { return size; }

 protected:
  size_t size;
};
#endif
