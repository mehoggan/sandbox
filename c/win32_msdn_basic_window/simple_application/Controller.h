#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <windows.h>
#include "IController.h"
#include "IApplication.h"

namespace nApplication
{
	class Controller : public IController
    {
    public:
	    Controller( IApplication *iApp );
	    virtual ~Controller();
	    virtual int CheckStatus();
    private:
	    Controller( Controller &c );
	    Controller& operator= ( Controller &c );
		IApplication *iApp;
	};
}

#endif //CONTROLLER_H_