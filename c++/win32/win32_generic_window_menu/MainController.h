#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include <windows.h>
#include "IController.h"

class MainController : public IController
{
public:
	MainController();
	~MainController();
	int CheckStatus();
};

#endif //MAINCONTROLLER_H_