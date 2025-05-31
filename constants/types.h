#ifndef __TYPES__
#define __TYPES__

#include <utility>
#include "numbers.h"

typedef struct CLOSURE_HOLDER {
	
	pair<short, short> *closure;
	short closureCount;
	Color closureColor;
	
} ClosureHolder;

#endif
