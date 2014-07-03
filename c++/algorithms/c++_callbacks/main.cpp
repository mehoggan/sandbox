#include <iostream>
#include "CallBack.h"
#include "CallMe.h"
#include "TimerManager.h"

using namespace std;

int main()
{
    // This is the object I want to call
    CallMe a;

    // This is the template object that will call Call Me
    Callback<CallMe, void, int> *callback;
    callback = new Callback<CallMe, void, int>(&a, &CallMe::PrintMe);

    // The timer will use the call back object to call ours
    TimerManager<CallMe> tm;
    tm.addTimer(1000000 / 2, callback);
    tm.start();

    while(true)
    {
        sleep(1);
    }

    return 0;
}

