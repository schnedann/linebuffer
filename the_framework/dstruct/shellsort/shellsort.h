#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "dtypes.h"

namespace sorting{

class shellsort{
private:
	
public:
	void fillran(uint16_t* data, uint16_t len);
	string List(uint16_t const * const data, uint16_t len);
  uint16_t Initgap(uint16_t len);
  void Sort(uint16_t* data, uint16_t len, uint16_t init);	
};

}
 
#endif
