#ifndef FWEVENT_H_
#define FWEVENT_H_

#include "FWGlobals.h"

class FWEvent
{
public:
	FWEvent(void);
	~FWEvent(void);
	bool sysKeys[40];
	bool regKeys[41];
	bool mouseEvents[14];
private:
};

#endif

