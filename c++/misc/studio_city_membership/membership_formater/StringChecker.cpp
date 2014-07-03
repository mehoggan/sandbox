#include <string>
#include "StringChecker.h"

StringChecker::StringChecker()
{
}

StringChecker::StringChecker(string valPassed)
{
	value = valPassed;	
}

StringChecker::~StringChecker() 
{
}

string StringChecker::checkString(string& val) 
{
	return val;
}

bool StringChecker::isNumeric(string& val)
{
	bool ret = false;
	if(val == "0")
	{
		ret = true;
	}
	if(val == "1")
	{
		ret = true;
	}
	if(val == "2")
	{
		ret = true;
	}
	if(val == "3")
	{
		ret = true;
	}
	if(val == "4")
	{
		ret = true;
	}
	if(val == "5")
	{
		ret = true;
	}
	if(val == "6")
	{
		ret = true;
	}
	if(val == "7")
	{
		ret = true;
	}
	if(val == "8")
	{
		ret = true;
	}
	if(val == "9")
	{
		ret = true;
	}
	return ret;
}

bool StringChecker::isAlphaCaps(string& val)
{
	bool ret = false;
	if(val == "A")
	{
		ret = true;
	}
	if(val == "B")
	{
		ret = true;
	}
	if(val == "C")
	{
		ret = true;
	}
	if(val == "D")
	{
		ret = true;
	}
	if(val == "E")
	{
		ret = true;
	}
	if(val == "F")
	{
		ret = true;
	}
	if(val == "G")
	{
		ret = true;
	}
	if(val == "H")
	{
		ret = true;
	}
	if(val == "I")
	{
		ret = true;
	}
	if(val == "J")
	{
		ret = true;
	}
	if(val == "K")
	{
		ret = true;
	}
	if(val == "L")
	{
		ret = true;
	}
	if(val == "M")
	{
		ret = true;
	}
	if(val == "N")
	{
		ret = true;
	}
	if(val == "O")
	{
		ret = true;
	}
	if(val == "P")
	{
		ret = true;
	}
	if(val == "Q")
	{
		ret = true;
	}
	if(val == "R")
	{
		ret = true;
	}
	if(val == "S")
	{
		ret = true;
	}
	if(val == "T")
	{
		ret = true;
	}
	if(val == "U")
	{
		ret = true;
	}
	if(val == "V")
	{
		ret = true;
	}
	if(val == "W")
	{
		ret = true;
	}
	if(val == "X")
	{
		ret = true;
	}
	if(val == "Y")
	{
		ret = true;
	}
	if(val == "Z")
	{
		ret = true;
	}
	return ret;
}

bool StringChecker::isAlpha(string& val)
{
	bool ret = false;
	if(val == "a")
	{
		ret = true;
	}
	if(val == "b")
	{
		ret = true;
	}
	if(val == "c")
	{
		ret = true;
	}
	if(val == "d")
	{
		ret = true;
	}
	if(val == "e")
	{
		ret = true;
	}
	if(val == "f")
	{
		ret = true;
	}
	if(val == "g")
	{
		ret = true;
	}
	if(val == "h")
	{
		ret = true;
	}
	if(val == "i")
	{
		ret = true;
	}
	if(val == "j")
	{
		ret = true;
	}
	if(val == "k")
	{
		ret = true;
	}
	if(val == "l")
	{
		ret = true;
	}
	if(val == "m")
	{
		ret = true;
	}
	if(val == "n")
	{
		ret = true;
	}
	if(val == "o")
	{
		ret = true;
	}
	if(val == "p")
	{
		ret = true;
	}
	if(val == "q")
	{
		ret = true;
	}
	if(val == "r")
	{
		ret = true;
	}
	if(val == "s")
	{
		ret = true;
	}
	if(val == "t")
	{
		ret = true;
	}
	if(val == "u")
	{
		ret = true;
	}
	if(val == "v")
	{
		ret = true;
	}
	if(val == "w")
	{
		ret = true;
	}
	if(val == "x")
	{
		ret = true;
	}
	if(val == "y")
	{
		ret = true;
	}
	if(val == "z")
	{
		ret = true;
	}
	return ret;
}