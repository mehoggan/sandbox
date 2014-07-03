#include <string>
#include <iostream>

using namespace std;
#ifndef STRINGCHANGER
#define STRINGCHANGER
class StringChanger 
{
public:
	StringChanger::StringChanger();
	StringChanger::~StringChanger();
	string specialToCapsKeepFirstSevenNumbers(string& val);
private:
	string str;
};
#endif