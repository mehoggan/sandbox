#include "Controller.h"

namespace nApplication
{
    Controller::Controller( IApplication *iApp ) : iApp( iApp )
    {
	
    }

    Controller::~Controller()
    {
    }

    int Controller::CheckStatus()
    {
        return 0;
    }
}