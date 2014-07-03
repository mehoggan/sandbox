#include "FWEvent.h"


FWEvent::FWEvent(void)
{
	for (int i = 0; i < 40; i++)
	{
		sysKeys[i] = false;
	}
	for (int i = 0; i < 41; i++)
	{
		regKeys[i] = false;
	}
	for (int i = 0; i < 14; i++)
	{
		mouseEvents[i] = false;
	}
}


FWEvent::~FWEvent(void)
{
}
