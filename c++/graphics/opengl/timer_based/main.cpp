#include <iostream>
#include "TimerManager.h"

using namespace std;

class Object
{
public:
    void print_me(int)
    {
        std::cout << "Example of how to use me" << std::endl;
    }
};

int main()
{
    Object a;

    // This is the template object that will call Call Me
    Callback<Object, void, int> *callback;
    callback = new Callback<Object, void, int>(&a, &Object::print_me);

    // The timer will use the call back object to call ours
    TimerManager<Object> tm;
    tm.addTimer(1000000 / 2, callback);
    tm.start();

    while(true)
    {
        sleep(1);
    }

    return 0;
}

