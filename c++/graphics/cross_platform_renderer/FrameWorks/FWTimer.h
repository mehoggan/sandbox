#ifndef FWTIMER_H
#define FWTIMER_H

#include "FWGlobals.h"

class FWTimer
{
public:
    FWTimer();
    FWTimer(unsigned long duration);
    ~FWTimer();
private:
    unsigned long duration;
};

#endif // FWTIMER_H
