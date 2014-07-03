#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

#ifndef STRINGCHECKER
#define STRINGCHECKER
class StringChecker 
{
public:
	StringChecker();
	StringChecker(string);
	~StringChecker();
	string checkString(string& val);
	bool isNumeric(string& val);
	bool isAlphaCaps(string& val);
	bool isAlpha(string& val);
private:
	string value;
};
#endif