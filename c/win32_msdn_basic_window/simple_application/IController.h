#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include <windows.h>

namespace nApplication
{
    class IController
    {
    public:
	    virtual int CheckStatus() = 0;
	};
}

#endif ICONTROLLER_H_