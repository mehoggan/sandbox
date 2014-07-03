#include <iostream>
#include <string>
#include <iomanip>
#include "LinkedList.h"

using namespace std;

#ifndef TOKENIZER
#define TOKENIZER
class Tokenizer 
{
public:
	Tokenizer();
	Tokenizer(string tokenize);
	Tokenizer(string tokenize, char tokenStop);
	~Tokenizer();
	int getWord();
	string nextToken();
	bool hasMoreTokens();
	string getToken(int);
private:
	LinkedList<string>* chainOtOkens;
	string toBeTokenized;
	int word;
};
#endif