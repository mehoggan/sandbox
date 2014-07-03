#ifndef IWINDOW_H_
#define IWINDOW_H_

#include <Windows.h>
#include "IController.h"

namespace nApplication
{
	class IWindow
	{
	public:
	    virtual void Init() = 0;
	    virtual void Display( ) = 0;
	private:
	};
}
#endif /* IWINDOW_H_ */