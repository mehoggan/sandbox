#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include <windows.h>

class IController
{
public:
	IController();
	virtual ~IController();
	virtual int CheckStatus() = 0;
};

//inline int Controller::CheckStatus() {return 0;}
#endif ICONTROLLER_H_